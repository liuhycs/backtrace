#ifndef SRG_BACKTRACE_H
#define SRG_BACKTRACE_H

#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "frame.h"
#include "unwind/common/backtrace.h"

typedef struct {
  sigjmp_buf jb;
} sigjmp_buf_t;

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

