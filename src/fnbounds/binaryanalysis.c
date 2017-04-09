// -*-Mode: C++;-*- // technically C99

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

// The client side of the new fnbounds server.  Hpcrun creates a pipe
// and then forks and execs hpcfnbounds in server mode (-s).  The file
// descriptors are passed as command-line arguments.
//
// This file implements the client side of the pipe.  For each query,
// send the file name to the server.  On success, mmap space for the
// answer, read the array of addresses from the pipe and read the
// extra info in the fnbounds file header.  The file 'syserv-mesg.h'
// defines the API for messages over the pipe.
//
// Notes:
// 1. Automatically restart the server if it fails.
//
// 2. Automatically restart short reads.  Reading from a pipe can
// return a short answer, especially if the other side buffers the
// writes.
//
// 3. Catch SIGPIPE.  Writing to a pipe after the other side has
// exited triggers a SIGPIPE and terminates the process.  It's
// important to catch (or ignore) SIGPIPE in the client so that if the
// server crashes, it doesn't also kill hpcrun.
//
// 4. We don't need to lock queries to the server.  Calls to
// hpcrun_syserv_query() already hold the FNBOUNDS_LOCK.
//
// 5. Dup the hpcrun log file fd onto stdout and stderr to prevent
// stray output from the server.
//
// 6. The bottom of this file has code for an interactive, stand-alone
// client for testing hpcfnbounds in server mode.
//
// Todo:
// 1. The memory leak is fixed in symtab 8.0.
//
// 2. Kill Zombies!  If the server exits, it will persist as a zombie.
// That's mostly harmless, but we could clean them up with waitpid().
// But we need to do it non-blocking.

//***************************************************************************

// To build an interactive, stand-alone client for testing:
// (1) turn on this #if and (2) fetch copies of syserv-mesg.h
// and fnbounds_file_header.h.

//***************************************************************************

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <syserv-mesg.h>
#include "binaryanalysis.h"
#include "disabled.h"
#include "fnbounds_file_header.h"
#include "messages/messages.h"

//*****************************************************************
// Mmap Helper Functions
//*****************************************************************

// Returns: 'size' rounded up to a multiple of the mmap page size.
static size_t
page_align(size_t size)
{
  static size_t pagesize = 0;

  if (pagesize == 0) {
#if defined(_SC_PAGESIZE)
    long ans = sysconf(_SC_PAGESIZE);
    if (ans > 0) {
      pagesize = ans;
    }
#endif
    if (pagesize == 0) {
      pagesize = 4096;
    }
  }

  return ((size + pagesize - 1)/pagesize) * pagesize;
}


// Returns: address of anonymous mmap() region, else MAP_FAILED on
// failure.
static void *
mmap_anon(size_t size)
{
  int flags, prot;

  size = page_align(size);
  prot = PROT_READ | PROT_WRITE;
#if defined(MAP_ANONYMOUS)
  flags = MAP_PRIVATE | MAP_ANONYMOUS;
#else
  flags = MAP_PRIVATE | MAP_ANON;
#endif

  return mmap(NULL, size, prot, flags, -1, 0);
}

//*****************************************************************
// Query the System Server
//*****************************************************************

// Returns: pointer to array of void * and fills in the file header,
// or else NULL on error.
//
void *
hpcrun_syserv_query(const char *fname, struct fnbounds_file_header *fh)
{
  struct syserv_mesg mesg;
  void *addr;

  if (fname == NULL || fh == NULL) {
    //EMSG("SYSTEM_SERVER ERROR: passed NULL pointer to %s", __func__);
    return NULL;
  }

  TMSG(SYSTEM_SERVER, "query: %s", fname);

  size_t len = strlen(fname) + 1;

  // Send the file name (including \0) and wait for the initial answer
  // (OK or ERR).  At this point, errors are pretty much fatal.
  //
  if (write_all(fdout, fname, len) != SUCCESS) {
    //EMSG("SYSTEM_SERVER ERROR: lost contact with server");
    shutdown_server();
    return NULL;
  }
  if (read_mesg(&mesg) != SUCCESS) {
    //EMSG("SYSTEM_SERVER ERROR: lost contact with server");
    shutdown_server();
    return NULL;
  }
  if (mesg.type != SYSERV_OK) {
    //EMSG("SYSTEM_SERVER ERROR: query failed: %s", fname);
    return NULL;
  }

  // Mmap a region for the answer and read the array of addresses.
  // Note: mesg.len is the number of addrs, not bytes.
  //
  size_t num_bytes = mesg.len * sizeof(void *);
  size_t mmap_size = page_align(num_bytes);
  addr = mmap_anon(mmap_size);
  
  if (addr == MAP_FAILED) {
    // Technically, we could keep the server alive in this case.
    // But we would have to read all the data to stay in sync with
    // the server.
    //EMSG("SYSTEM_SERVER ERROR: mmap failed");
    return NULL;
  }
  if (read_all(fdin, addr, num_bytes) != SUCCESS) {
    //EMSG("SYSTEM_SERVER ERROR: lost contact with server");
    return NULL;
  }

  // Read the trailing fnbounds file header.
  struct syserv_fnbounds_info fnb_info;
  int ret = read_all(fdin, &fnb_info, sizeof(fnb_info));
  if (ret != SUCCESS || fnb_info.magic != FNBOUNDS_MAGIC) {
    //EMSG("SYSTEM_SERVER ERROR: lost contact with server");
    shutdown_server();
    return NULL;
  }
  if (fnb_info.status != SYSERV_OK) {
    //EMSG("SYSTEM_SERVER ERROR: query failed: %s", fname);
    return NULL;
  }
  fh->num_entries = fnb_info.num_entries;
  fh->reference_offset = fnb_info.reference_offset;
  fh->is_relocatable = fnb_info.is_relocatable;
  fh->mmap_size = mmap_size;

  fprintf(stderr, "addr: %p, [%s]\nsymbols: %ld, offset: 0x%lx, reloc: %d\n",
       addr, (char*)addr, (long) fh->num_entries, (long) fh->reference_offset,
       (int) fh->is_relocatable);
  fprintf(stderr, "server memsize: %ld Meg", fnb_info.memsize / 1024);

  return addr;
}

#endif  // STAND_ALONE_CLIENT
