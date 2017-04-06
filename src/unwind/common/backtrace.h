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

#ifndef hpcrun_backtrace_h
#define hpcrun_backtrace_h

//***************************************************************************
// file: backtrace.h
//
// purpose:
//     an interface for performing stack unwinding 
//
//***************************************************************************


//***************************************************************************
// system include files 
//***************************************************************************

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <ucontext.h>

//***************************************************************************
// local include files 
//***************************************************************************

#include <ip-normalized.h>
#include <unwind/common/unw-datatypes.h>
#include <unwind/common/backtrace_info.h>
#include <frame.h>

//
// backtrace_t type is a struct holding begin, end, current ptrs
//  to frames
//

typedef struct backtrace_t {
  size_t   size;   // size of backtrace
  size_t   len;    // # of frames used
  frame_t* beg;    // base memory chunk
  frame_t* end;    // the last available slot
  frame_t* cur;    // current insertion position
} backtrace_t;

typedef struct thread_data_t {

  frame_t* btbuf_cur;  // current frame when actively constructing a backtrace
  frame_t* btbuf_beg;  // beginning of the backtrace buffer 
                       // also, location of the innermost frame in
                       // newly recorded backtrace (although skipInner may
                       // adjust the portion of the backtrace that is recorded)
  frame_t* btbuf_end;  // end of the current backtrace buffer

  backtrace_t bt;     // backtrace used for unwinding

  // ----------------------------------------
  // trampoline
  // ----------------------------------------
  bool    tramp_present;   // TRUE if a trampoline installed; FALSE otherwise
  void*   tramp_retn_addr; // return address that the trampoline replaced
  void*   tramp_loc;       // current (stack) location of the trampoline
  size_t  cached_frame_count; // (sanity check) length of cached frame list
  frame_t* cached_bt;         // the latest backtrace (start)
  frame_t* cached_bt_end;     // the latest backtrace (end)
  frame_t* cached_bt_buf_end; // the end of the cached backtrace buffer
  frame_t* tramp_frame;       // (cached) frame assoc. w/ cur. trampoline loc.

} thread_data_t;

frame_t* hpcrun_bt_reset(backtrace_t* bt);

void hpcrun_bt_init(backtrace_t* bt, size_t size);

void hpcrun_dump_bt(backtrace_t* bt);

bool hpcrun_generate_backtrace(thread_data_t* td, backtrace_info_t* bt, ucontext_t* context);
//bool hpcrun_generate_backtrace(thread_data_t* td, backtrace_info_t* bt, ucontext_t* context, int skipInner);

bool hpcrun_generate_backtrace_no_trampoline(thread_data_t* td, backtrace_info_t* bt, ucontext_t* context);
//bool hpcrun_generate_backtrace_no_trampoline(thread_data_t* td, backtrace_info_t* bt, ucontext_t* context, int skipInner);

#endif // hpcrun_backtrace_h
