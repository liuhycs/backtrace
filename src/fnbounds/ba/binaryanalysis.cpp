// -*-Mode: C++;-*-

// * BeginRiceCopyright *****************************************************
//
// $HeadURL$
// $Id$
//
// --------------------------------------------------------------------------
// Part of HPCToolkit (hpctoolkit.org)
//
// Information about sources of support for research and development of
// HPCToolkit is at 'hpctoolkit.org' and in 'README.Acknowledgments'.
// --------------------------------------------------------------------------
//
// Copyright ((c)) 2002-2017, Rice University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of Rice University (RICE) nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// This software is provided by RICE and contributors "as is" and any
// express or implied warranties, including, but not limited to, the
// implied warranties of merchantability and fitness for a particular
// purpose are disclaimed. In no event shall RICE or contributors be
// liable for any direct, indirect, incidental, special, exemplary, or
// consequential damages (including, but not limited to, procurement of
// substitute goods or services; loss of use, data, or profits; or
// business interruption) however caused and on any theory of liability,
// whether in contract, strict liability, or tort (including negligence
// or otherwise) arising in any way out of the use of this software, even
// if advised of the possibility of such damage.
//
// ******************************************************* EndRiceCopyright *

//*****************************************************************************
// system includes
//*****************************************************************************

#include <vector>
#include <string>

#include <climits>
#include <cstdio>
#include <cstdlib>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h>
//*****************************************************************************
// HPCToolkit Externals Include
//*****************************************************************************

#include <libdwarf.h>

//*****************************************************************************
// local includes
//*****************************************************************************

#include "code-ranges.h"
#include "process-ranges.h"
#include "function-entries.h"
#include "binaryanalysis.h"
#include "syserv-mesg.h"
#include "Symtab.h"
#include "Symbol.h"

using namespace std;
using namespace Dyninst;
using namespace SymtabAPI;

//*****************************************************************************
// macros
//*****************************************************************************

#define SECTION_SYMTAB ".symtab"
#define SECTION_INIT   ".init"
#define SECTION_FINI   ".fini"
#define SECTION_TEXT   ".text"
#define SECTION_PLT    ".plt"

#define PATHSCALE_EXCEPTION_HANDLER_PREFIX "Handler."
#define USE_PATHSCALE_SYMBOL_FILTER
#define USE_SYMTABAPI_EXCEPTION_BLOCKS

#define STRLEN(s) (sizeof(s) - 1)

#define DWARF_OK(e) (DW_DLV_OK == (e))

//should be page aligned 
#define ADDR_SIZE   (64 * 4096)

static void** addr_buf;
static void** cur_addr_buf;
static size_t addrbuf_size; 
static long  num_addrs;
static long  total_num_addrs;
static long  max_num_addrs;

static int ba_success;
static struct syserv_fnbounds_info fnb_info;

//*****************************************************************
// interface operations
//*****************************************************************

extern "C" {
// we don't care about demangled names. define
// a no-op that meets symtabAPI semantic needs only
char * cplus_demangle(char *s, int opts) {
  return strdup(s);
}

};

//*****************************************************************
// private operations
//*****************************************************************

static bool matches_prefix(string s, const char *pre, int n) {
  const char *sc = s.c_str();
  return strncmp(sc, pre, n) == 0;
}

#ifdef __PPC64__
static bool matches_contains(string s, const char *substring) {
  const char *sc = s.c_str();
  return strstr(sc, substring) != 0;
}
#endif

static bool pathscale_filter(Symbol *sym) {
  bool result = false;
  // filter out function symbols for exception handlers
  if (matches_prefix(sym->getMangledName(), 
        PATHSCALE_EXCEPTION_HANDLER_PREFIX, 
        STRLEN(PATHSCALE_EXCEPTION_HANDLER_PREFIX))) 
    result = true;
  return result;
}

static bool report_symbol(Symbol *sym) {
#ifdef USE_PATHSCALE_SYMBOL_FILTER
  if (pathscale_filter(sym)) return false;
#endif
  return true;
}

static string * code_range_comment(string &name, string section, const char *which) {
  name = which; 
  name = name + " " + section + " section";
  return &name;
}

static void note_code_range(Region *s, long memaddr, DiscoverFnTy discover) {
  char *start = (char *) s->getDiskOffset();
  char *end = start + s->getDiskSize();
  string ntmp;
  new_code_range(start, end, memaddr, discover);

  add_function_entry(start, code_range_comment(ntmp, s->getRegionName(), "start"), true /* global */);
  add_function_entry(end, code_range_comment(ntmp, s->getRegionName(), "end"), true /* global */);
}

static void note_section(Symtab *syms, const char *sname, DiscoverFnTy discover) {
  long memaddr = (long) syms->mem_image();
  Region *s;
  if (syms->findRegion(s, sname) && s) 
    note_code_range(s, memaddr - syms->imageOffset(), discover);
}

static void note_code_ranges(Symtab *syms, DiscoverFnTy fn_discovery) {
  //TODO: instead of just considering specific segments below
  //      perhaps we should consider all segments marked executable.
  //      binaries could include "bonus" segments we don't
  //      know about explicitly as having code within.
  note_section(syms, SECTION_INIT, fn_discovery);
  note_section(syms, SECTION_PLT,  DiscoverFnTy_Aggressive);
  note_section(syms, SECTION_TEXT, fn_discovery);
  note_section(syms, SECTION_FINI, fn_discovery);
}

// collect function start addresses from eh_frame info
// (part of the DWARF info)
// enter these start addresses into the reachable function
// data structure

static void seed_dwarf_info(int dwarf_fd) {
  Dwarf_Debug dbg = NULL;
  Dwarf_Error err;
  Dwarf_Handler errhand = NULL;
  Dwarf_Ptr errarg = NULL;

  // Unless disabled, add eh_frame info to function entries
  if(getenv("EH_NO")) {
    close(dwarf_fd);
    return;
  }

  if ( ! DWARF_OK(dwarf_init(dwarf_fd, DW_DLC_READ,
          errhand, errarg,
          &dbg, &err))) {
    fprintf(stderr, "dwarf init failed !!\n");
    return;
  }

  Dwarf_Cie* cie_data = NULL;
  Dwarf_Signed cie_element_count = 0;
  Dwarf_Fde* fde_data = NULL;
  Dwarf_Signed fde_element_count = 0;

  int fres =
    dwarf_get_fde_list_eh(dbg, &cie_data,
        &cie_element_count, &fde_data,
        &fde_element_count, &err);
  if ( ! DWARF_OK(fres)) {
    fprintf(stderr, "failed to get eh_frame element from DWARF\n");
    return;
  }

  for (int i = 0; i < fde_element_count; i++) {
    Dwarf_Addr low_pc = 0;
    Dwarf_Unsigned func_length = 0;
    Dwarf_Ptr fde_bytes = NULL;
    Dwarf_Unsigned fde_bytes_length = 0;
    Dwarf_Off cie_offset = 0;
    Dwarf_Signed cie_index = 0;
    Dwarf_Off fde_offset = 0;

    int fres = dwarf_get_fde_range(fde_data[i],
        &low_pc, &func_length,
        &fde_bytes,
        &fde_bytes_length,
        &cie_offset, &cie_index,
        &fde_offset, &err);
    if (fres == DW_DLV_ERROR) {
      fprintf(stderr, " error on dwarf_get_fde_range\n");
      return;
    }
    if (fres == DW_DLV_NO_ENTRY) {
      fprintf(stderr, " NO_ENTRY error on dwarf_get_fde_range\n");
      return;
    }
    if(getenv("EH_SHOW")) {
      fprintf(stderr, " ---potential fn start = %p\n", reinterpret_cast<void*>(low_pc));
    }

    if (low_pc != (Dwarf_Addr) 0) add_function_entry(reinterpret_cast<void*>(low_pc), NULL, false, 0);
  }
  if ( ! DWARF_OK(dwarf_finish(dbg, &err))) {
    fprintf(stderr, "dwarf finish fails ???\n");
  }
  close(dwarf_fd);
}

static void dump_symbols(int dwarf_fd, Symtab *syms, vector<Symbol *> &symvec, DiscoverFnTy fn_discovery) {
  note_code_ranges(syms, fn_discovery);

  //-----------------------------------------------------------------
  // collect function start addresses and pair them with a comment
  // that indicates what function (or functions) map to that start 
  // address. enter them into a data structure for reachable function
  // processing
  //-----------------------------------------------------------------
  for (unsigned int i = 0; i < symvec.size(); i++) {
    Symbol *s = symvec[i];
    Symbol::SymbolLinkage sl = s->getLinkage();
    if (report_symbol(s) && s->getOffset() != 0) {
      string mname = s->getMangledName();
      add_function_entry((void *) s->getOffset(), &mname,
          ((sl & Symbol::SL_GLOBAL) ||
           (sl & Symbol::SL_WEAK)));
    }
  }

  seed_dwarf_info(dwarf_fd);

  process_code_ranges();

  //-----------------------------------------------------------------
  // dump the address and comment for each function  
  //-----------------------------------------------------------------
  dump_reachable_functions();
}

static void dump_file_symbols(int dwarf_fd, Symtab *syms, vector<Symbol *> &symvec,
    DiscoverFnTy fn_discovery) {
  dump_symbols(dwarf_fd, syms, symvec, fn_discovery);
}

// We call it "header", even though it comes at end of file.
//
static void dump_header_info(int is_relocatable, uintptr_t ref_offset) {
  syserv_add_header(is_relocatable, ref_offset);
}

static void assert_file_is_readable(const char *filename) {
  struct stat sbuf;
  int ret = stat(filename, &sbuf);
  if (ret != 0 || !S_ISREG(sbuf.st_mode)) {
    fprintf(stderr, "hpcfnbounds: unable to open file: %s\n", filename);
    exit(-1);
  } 
}

void dump_file_info(const char *filename, DiscoverFnTy fn_discovery) {
  Symtab *syms;
  string sfile(filename);
  vector<Symbol *> symvec;
  uintptr_t image_offset = 0;

  assert_file_is_readable(filename);

  if (!Symtab::openFile(syms, sfile)) {
    fprintf(stderr,
        "!!! INTERNAL hpcfnbounds-bin error !!!\n"
        "  -- file %s is readable, but Symtab::openFile fails !\n",
        filename);
    exit(1);
  }
  int relocatable = 0;

  // open for dwarf usage
  int dwarf_fd = open(filename, O_RDONLY);

#ifdef USE_SYMTABAPI_EXCEPTION_BLOCKS 
  //-----------------------------------------------------------------
  // ensure that we don't infer function starts within try blocks or
  // at the start of catch blocks
  //-----------------------------------------------------------------
  vector<ExceptionBlock *> exvec;
  syms->getAllExceptions(exvec);

  for (unsigned int i = 0; i < exvec.size(); i++) {
    ExceptionBlock *e = exvec[i];

#ifdef DUMP_EXCEPTION_BLOCK_INFO
    printf("tryStart = %p tryEnd = %p, catchStart = %p\n", e->tryStart(), 
        e->tryEnd(), e->catchStart()); 
#endif // DUMP_EXCEPTION_BLOCK_INFO
    //-----------------------------------------------------------------
    // prevent inference of function starts within the try block
    //-----------------------------------------------------------------
    add_protected_range((void *) e->tryStart(), (void *) e->tryEnd());

    //-----------------------------------------------------------------
    // prevent inference of a function start at the beginning of a
    // catch block. the extent of the catch block is unknown.
    //-----------------------------------------------------------------
    long cs = e->catchStart(); 
    add_protected_range((void *) cs, (void *) (cs + 1));
  }
#endif // USE_SYMTABAPI_EXCEPTION_BLOCKS 

  syms->getAllSymbolsByType(symvec, Symbol::ST_FUNCTION);

#ifdef __PPC64__
  {
    //-----------------------------------------------------------------
    // collect addresses of trampolines for long distance calls as per
    // ppc64 abi. empirically, the linker on BG/Q enters these symbols
    // with the type NOTYPE and a name that contains the substring 
    // "long_branch"
    //-----------------------------------------------------------------
    vector<Symbol *> vec;
    syms->getAllSymbolsByType(vec, Symbol::ST_NOTYPE);
    for (unsigned int i = 0; i < vec.size(); i++) {
      Symbol *s = vec[i];
      string mname = s->getMangledName();
      if (matches_contains(mname, "long_branch") && s->getOffset() != 0) {
        add_function_entry((void *) s->getOffset(), &mname, true);
      }
    }
  }
#endif

  if (syms->getObjectType() != obj_Unknown) {
    dump_file_symbols(dwarf_fd, syms, symvec, fn_discovery);
    relocatable = syms->isExec() ? 0 : 1;
    image_offset = syms->imageOffset();
  }
  dump_header_info(relocatable, image_offset);

  //-----------------------------------------------------------------
  // free as many of the Symtab objects as we can
  //-----------------------------------------------------------------

  close(dwarf_fd);

  Symtab::closeSymtab(syms);
}

//*****************************************************************
// Mmap Helper Functions
//*****************************************************************

/*
// Returns: 'size' rounded up to a multiple of the mmap page size.
static size_t page_align(size_t size) {
static size_t pagesize = 0;

if (pagesize == 0) {
pagesize = 4096;

#if defined(_SC_PAGESIZE)
long ans = sysconf(_SC_PAGESIZE);
if (ans > 0) {
pagesize = ans;
}
#endif
}

return ((size + pagesize - 1)/pagesize) * pagesize;
}
*/

// Returns: address of anonymous mmap() region, else MAP_FAILED on
// failure.
static void * mmap_anon(size_t size) {
  int flags, prot;

  //size = page_align(size);
  prot = PROT_READ | PROT_WRITE;
#if defined(MAP_ANONYMOUS)
  flags = MAP_PRIVATE | MAP_ANONYMOUS;
#else
  flags = MAP_PRIVATE | MAP_ANON;
#endif

  return mmap(NULL, size, prot, flags, -1, 0);
}
//*************************************************

void expendAddrBuf(){

  size_t origsize = addrbuf_size;
  addrbuf_size += ADDR_SIZE; 
  // mmap a new chunk
  void* addr = mmap_anon(addrbuf_size);
  if (addr == MAP_FAILED) {
    fprintf(stderr, "mmap failed in expendAddrBuf()\n");
    abort();
  }

  // copy old data to new buf
  memcpy(addr, addr_buf, origsize);
  munmap(addr_buf, origsize);

  // set addr_buf and cur_addr_buf
  addr_buf = (void **)addr;
  cur_addr_buf = (void **)(addr_buf + origsize);
}

// Called from dump_function_entry().
void syserv_add_addr(void *addr, long func_entry_map_size) {

  // ser address number, this is for padding address
  if (! ba_success) {
    max_num_addrs = func_entry_map_size + 1;
    ba_success = 1;
  }

  // see if buffer needs to be flushed
  if (num_addrs >= ADDR_SIZE) {
    expendAddrBuf();
    num_addrs = 0;
  }

  cur_addr_buf[num_addrs] = addr;
  num_addrs++;
  total_num_addrs++;
}

// Called from dump_header_info().
void syserv_add_header(int is_relocatable, uintptr_t ref_offset) {
  fnb_info.is_relocatable = is_relocatable;
  fnb_info.reference_offset = ref_offset;
}

//*****************************************************************
// The server side of the new fnbounds server.  Hpcrun creates a pipe
// and then forks and execs hpcfnbounds in server mode (-s).  The file
// descriptors are passed as command-line arguments.
//
// This file implements the server side of the pipe.  Read messages
// over the pipe, process fnbounds queries and write the answer
// (including the array of addresses) back over the pipe.  The file
// 'syserv-mesg.h' defines the API for messages over the pipe.
//
// Notes:
// 1. The server only computes fnbounds queries, not general calls to
// system(), use monitor_real_system() for that.
//
// 2. Catch SIGPIPE.  Writing to a pipe after the other side has
// exited triggers a SIGPIPE and terminates the process.  If this
// happens, it probably means that hpcrun has prematurely exited.
// So, catch SIGPIPE in order to write a more useful error message.
//
// 3. It's ok to write error messages to stderr.  After hpcrun forks,
// it dups the hpcrun log file fd onto stdout and stderr so that any
// output goes to the log file.
//
// 4. The server runs outside of hpcrun and libmonitor.
//
// Todo:
// 1. The memory leak is fixed in symtab 8.0.

//*****************************************************************

extern "C" {
void* ba_fnbounds(struct fnbounds_file_header* fh, char* filename) {
  DiscoverFnTy fn_discovery = DiscoverFnTy_Aggressive;
  long k;

  num_addrs = 0;
  total_num_addrs = 0;
  max_num_addrs = 0;
  ba_success = 0;

  memset(&fnb_info, 0, sizeof(fnb_info));
  code_ranges_reinit();
  function_entries_reinit();

  addrbuf_size = ADDR_SIZE; 
  addr_buf = (void **)mmap_anon(addrbuf_size);
  if (addr_buf == MAP_FAILED) {
    return NULL;
  }
  cur_addr_buf = addr_buf;

  dump_file_info(filename, fn_discovery);

  // pad list of addrs in case there are fewer function addrs than
  // size of map.
  fnb_info.num_entries = total_num_addrs;
  for (k = total_num_addrs; k < max_num_addrs; k++) {
    syserv_add_addr(NULL, 0);
  }

  fh->num_entries = fnb_info.num_entries;
  fh->reference_offset = fnb_info.reference_offset;
  fh->is_relocatable = fnb_info.is_relocatable;
  fh->mmap_size = addrbuf_size;

  if (num_addrs > 0) {
    num_addrs = 0;
    return addr_buf;
  }
  return NULL;
}
};
