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


//***************************************************************************
// system include files
//***************************************************************************

#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include <sys/types.h>
#include <ucontext.h>

#include <string.h>


//***************************************************************************
// local include files
//***************************************************************************

#include <unwind/common/unw-throw.h>

#include <trampoline/common/trampoline.h>
#include <dbg_backtrace.h>

//***************************************************************************
// local constants & macros
//***************************************************************************

//***************************************************************************
// interface functions
//***************************************************************************

  frame_t*
hpcrun_bt_reset(backtrace_t* bt)
{
  bt->cur = bt->beg;
  bt->len = 0;
  return bt->cur;
}

  void
hpcrun_bt_init(backtrace_t* bt, size_t size)
{
  bt->beg   = (frame_t*) hpcrun_malloc(sizeof(frame_t) * size);
  bt->end   = bt->beg + (size - 1);
  bt->size  = size;
  hpcrun_bt_reset(bt);
}

  void
hpcrun_dump_bt(backtrace_t* bt)
{
  for(frame_t* _f = bt->beg; _f < bt->beg + bt->len; _f++) {
    TMSG(BT, "ip_norm.lm_id = %d, and ip_norm.lm_ip = %p ", _f->ip_norm.lm_id,
        _f->ip_norm.lm_ip);
  }
}

//
// Generate a backtrace, store it in the thread local data
// Return true/false success code
// Also, return (via reference params) backtrace beginning, backtrace end,
//  and whether or not a trampoline was found.
//
// NOTE: This routine will stop the backtrace if a trampoline is encountered,
//       but it will NOT update the trampoline data structures.
//
  bool
hpcrun_generate_backtrace_no_trampoline(thread_data_t* td, backtrace_info_t* bt,
    ucontext_t* context,
    int skipInner)
{
  TMSG(BT, "Generate backtrace (no tramp), skip inner = %d", skipInner);
  bt->has_tramp = false;
  bt->trolled  = false;
  bt->n_trolls = 0;
  bt->fence = FENCE_BAD;
  bt->bottom_frame_elided = false;
  bt->partial_unwind = true;

  bool tramp_found = false;

  step_state ret = STEP_ERROR; // default return value from stepper

  //--------------------------------------------------------------------
  // note: these variables are not local variables so that if a SIGSEGV 
  // occurs and control returns up several procedure frames, the values 
  // are accessible to a dumping routine that will tell us where we ran 
  // into a problem.
  //--------------------------------------------------------------------

  td->btbuf_cur   = td->btbuf_beg; // innermost
  td->btbuf_sav   = td->btbuf_end;

  hpcrun_unw_cursor_t cursor;
  hpcrun_unw_init_cursor(&cursor, context);

  int unw_len = 0;
  while (true) {
    void* ip;
    hpcrun_unw_get_ip_unnorm_reg(&cursor, &ip);

    if (hpcrun_trampoline_interior((void*) ip)) {
      // bail; we shouldn't be unwinding here. hpcrun is in the midst of 
      // counting a return from a sampled frame using a trampoline.
      // drop the sample. 
      // FIXME: sharpen the information to indicate why the sample is 
      //        being dropped.
      hpcrun_unw_drop();
    }

    if (hpcrun_trampoline_at_entry((void*) ip)) {
      if (unw_len == 0){
        // we are about to enter the trampoline code to synchronously 
        // record a return. for now, simply do nothing ...
        // FIXME: with a bit more effort, we could charge 
        //        the sample to the return address in the caller. 
        hpcrun_unw_drop();
      }
      else {
        // we have encountered a trampoline in the middle of an unwind.
        bt->has_tramp = (tramp_found = true);
        TMSG(TRAMP, "--CURRENT UNWIND FINDS TRAMPOLINE @ (sp:%p, bp:%p", cursor.sp, cursor.bp);
        // no need to unwind further. the outer frames are already known.

        bt->fence = FENCE_TRAMP;
        ret = STEP_STOP;
        break;
      }
    }

    hpcrun_ensure_btbuf_avail(td);

    td->btbuf_cur->cursor = cursor;
    //Broken if HPC_UNW_LITE defined
    hpcrun_unw_get_ip_norm_reg(&td->btbuf_cur->cursor,
        &td->btbuf_cur->ip_norm);
    td->btbuf_cur->ra_loc = NULL;

    td->btbuf_cur->the_function = cursor.the_function;

    frame_t* prev = td->btbuf_cur;
    td->btbuf_cur++;
    unw_len++;

    ret = hpcrun_unw_step(&cursor);
    if (ret == STEP_TROLL) {
      bt->trolled = true;
      bt->n_trolls++;
    }
    if (ret <= 0) {
      if (ret == STEP_ERROR) {
        hpcrun_stats_num_samples_dropped_inc();
      }
      else { // STEP_STOP
        bt->fence = cursor.fence;
      }
      break;
    }
    prev->ra_loc = hpcrun_unw_get_ra_loc(&cursor);
  }

  TMSG(FENCE, "backtrace generation detects fence = %s", fence_enum_name(bt->fence));

  frame_t* bt_beg  = td->btbuf_beg;      // innermost, inclusive
  frame_t* bt_last = td->btbuf_cur - 1; // outermost, inclusive

  if (skipInner) {
    if (ENABLED(USE_TRAMP)){
      //
      // FIXME: For the moment, ignore skipInner issues with trampolines.
      //        Eventually, this will need to be addressed
      //
      TMSG(TRAMP, "WARNING: backtrace detects skipInner != 0 (skipInner = %d)", 
          skipInner);
    }
    TMSG(BT, "* BEFORE Skip inner correction, bt_beg = %p", bt_beg);
    // adjust the returned backtrace according to the skipInner
    bt_beg = hpcrun_skip_chords(bt_last, bt_beg, skipInner);
    TMSG(BT, "* AFTER Skip inner correction, bt_beg = %p", bt_beg);
  }

  bt->begin = bt_beg;         // returned backtrace begin
  // is buffer beginning
  bt->last  = bt_last;        // returned backtrace last is
  // last recorded element
  // soft error mandates returning false
  if (! (ret == STEP_STOP)) {
    TMSG(BT, "** Soft Failure **");
    return false;
  }

  TMSG(BT, "succeeds");
  bt->partial_unwind = false;
  return true;
}

//
// Do all of the raw backtrace generation, plus
// update the trampoline cached backtrace.
//
  bool
hpcrun_generate_backtrace(thread_data_t* td, backtrace_info_t* bt,
    ucontext_t* context, int skipInner)
{
  bool ret = hpcrun_generate_backtrace_no_trampoline(bt,
      context,
      skipInner);
  if (! ret ) return false;

  bool tramp_found = bt->has_tramp;
  frame_t* bt_beg  = bt->begin;
  frame_t* bt_last = bt->last;

  frame_t* bt_end  = bt_last + 1;    // outermost, exclusive
  size_t new_frame_count = bt_end - bt_beg;

  if (ENABLED(USE_TRAMP)) {
    if (tramp_found) {
      TMSG(BACKTRACE, "tramp stop: conjoining backtraces");
      TMSG(TRAMP, " FOUND TRAMP: constructing cached backtrace");
      //
      // join current backtrace fragment to previous trampoline-marked prefix
      // and make this new conjoined backtrace the cached-backtrace
      //
      frame_t* prefix = td->tramp_frame;
      TMSG(TRAMP, "Check: tramp prefix ra_loc = %p, addr@ra_loc = %p (?= %p tramp), retn_addr = %p",
          prefix->ra_loc, *((void**) prefix->ra_loc), hpcrun_trampoline, td->tramp_retn_addr);
      size_t old_frame_count = td->cached_bt_end - prefix;
      TMSG(TRAMP, "Check: Old frame count = %d ?= %d (computed frame count)",
          old_frame_count, td->cached_frame_count);

      size_t n_cached_frames = new_frame_count - 1;
      hpcrun_cached_bt_adjust_size(n_cached_frames + old_frame_count);
      TMSG(TRAMP, "cached trace size = (new frames) %d + (old frames) %d = %d",
          n_cached_frames, old_frame_count, n_cached_frames + old_frame_count);
      // put the old prefix in place
      memmove(td->cached_bt + n_cached_frames, prefix,
          sizeof(frame_t) * old_frame_count);

      // put the new suffix in place
      memcpy(td->cached_bt, bt_beg, sizeof(frame_t) * n_cached_frames);

      // update the length of the conjoined backtrace
      td->cached_bt_end = td->cached_bt + n_cached_frames + old_frame_count;
      // maintain invariants
      td->cached_frame_count = n_cached_frames + old_frame_count;
      td->tramp_frame = td->cached_bt + n_cached_frames;
      TMSG(TRAMP, "Check: tramp prefix ra_loc = %p, addr@ra_loc = %p (?= %p tramp), retn_addr = %p",
          prefix->ra_loc, *((void**) prefix->ra_loc), hpcrun_trampoline, td->tramp_retn_addr);
    }
    else {
      TMSG(TRAMP, "No tramp found: cached backtrace size = %d", new_frame_count);
      hpcrun_cached_bt_adjust_size(new_frame_count);
      size_t n_cached_frames = new_frame_count - 1;
      TMSG(TRAMP, "Confirm: ra_loc(last bt frame) = %p", (bt_beg + n_cached_frames)->ra_loc);
      memmove(td->cached_bt, bt_beg, sizeof(frame_t) * n_cached_frames);

      td->cached_bt_end = td->cached_bt + n_cached_frames;
      td->cached_frame_count = n_cached_frames;
    }
    if (ENABLED(TRAMP)) {
      TMSG(TRAMP, "Dump cached backtrace from backtrace construction");
    }
  }

  return true;
}

// debug variant of above routine
//
//
// Generate a backtrace, store it in the thread local data
// Return true/false success code
// Also, return (via reference params) backtrace beginning, backtrace end,
//  and whether or not a trampoline was found.
//

  bool
hpcrun_dbg_generate_backtrace(thread_data_t* td, backtrace_info_t* bt,
    ucontext_t* context, int skipInner)
{
  bt->has_tramp = false;
  bt->trolled  = false;
  bt->n_trolls = 0;
  bt->bottom_frame_elided = false;
  bt->partial_unwind = true;

  bool tramp_found = false;

  step_state ret = STEP_ERROR; // default return value from stepper

  hpcrun_unw_cursor_t cursor;
  hpcrun_dbg_unw_init_cursor(&cursor, context);

  //--------------------------------------------------------------------
  // note: these variables are not local variables so that if a SIGSEGV 
  // occurs and control returns up several procedure frames, the values 
  // are accessible to a dumping routine that will tell us where we ran 
  // into a problem.
  //--------------------------------------------------------------------

  td->btbuf_cur   = td->btbuf_beg; // innermost
  td->btbuf_sav   = td->btbuf_end;

  int unw_len = 0;
  while (true) {
    void* ip;
    hpcrun_unw_get_ip_unnorm_reg(&cursor, &ip);

    if (hpcrun_dbg_trampoline_interior((void*) ip)) {
      // bail; we shouldn't be unwinding here. hpcrun is in the midst of 
      // counting a return from a sampled frame using a trampoline.
      // drop the sample. 
      // FIXME: sharpen the information to indicate why the sample is 
      //        being dropped.
      hpcrun_unw_throw();
    }

    if (hpcrun_dbg_trampoline_at_entry((void*) ip)) {
      if (unw_len == 0){
        // we are about to enter the trampoline code to synchronously 
        // record a return. for now, simply do nothing ...
        // FIXME: with a bit more effort, we could charge 
        //        the sample to the return address in the caller. 
        hpcrun_unw_throw();
      }
      else {
        // we have encountered a trampoline in the middle of an unwind.
        bt->has_tramp = (tramp_found = true);

        // no need to unwind further. the outer frames are already known.
        break;
      }
    }

    hpcrun_ensure_btbuf_avail(td);

    td->btbuf_cur->cursor = cursor;
    //Broken if HPC_UNW_LITE defined
    hpcrun_unw_get_ip_norm_reg(&td->btbuf_cur->cursor,
        &td->btbuf_cur->ip_norm);
    td->btbuf_cur->ra_loc = NULL;
    frame_t* prev = td->btbuf_cur;
    td->btbuf_cur++;
    unw_len++;

    ret = hpcrun_dbg_unw_step(&cursor);
    if (ret == STEP_TROLL) {
      bt->trolled = true;
      bt->n_trolls++;
    }
    if (ret <= 0) {
      break;
    }
    prev->ra_loc = hpcrun_unw_get_ra_loc(&cursor);
  }

  frame_t* bt_beg  = td->btbuf_beg;      // innermost, inclusive
  frame_t* bt_last = td->btbuf_cur - 1; // outermost, inclusive

  bt->begin        = bt_beg;         // returned backtrace begin
  // is buffer beginning
  bt->last         = bt_last;        // returned backtrace end is
  // last recorded element

  frame_t* bt_end  = bt_last + 1;    // outermost, exclusive
  size_t new_frame_count = bt_end - bt_beg;

  // soft error mandates returning false
  if (! (ret == STEP_STOP)) {
    return false;
  }

  if (tramp_found) {
    TMSG(BACKTRACE, "tramp stop: conjoining backtraces");
    //
    // join current backtrace fragment to previous trampoline-marked prefix
    // and make this new conjoined backtrace the cached-backtrace
    //
    frame_t* prefix = td->tramp_frame + 1; // skip top frame
    size_t old_frame_count = td->cached_bt_end - prefix;

    hpcrun_cached_bt_adjust_size(new_frame_count + old_frame_count);

    // put the old prefix in place
    memmove(td->cached_bt + new_frame_count, prefix, 
        sizeof(frame_t) * old_frame_count);

    // put the new suffix in place
    memcpy(td->cached_bt, bt_beg, sizeof(frame_t) * new_frame_count);

    // update the length of the conjoined backtrace
    td->cached_bt_end = td->cached_bt + new_frame_count + old_frame_count;
  }
  else {
    hpcrun_cached_bt_adjust_size(new_frame_count);
    memmove(td->cached_bt, bt_beg, sizeof(frame_t) * new_frame_count);

    td->cached_bt_end = td->cached_bt + new_frame_count;
  }

  if (skipInner) {
    if (ENABLED(USE_TRAMP)){
      //
      // FIXME: For the moment, ignore skipInner issues with trampolines.
      //        Eventually, this will need to be addressed
      //
      EMSG("WARNING: backtrace detects skipInner != 0 (skipInner = %d)", 
          skipInner);
    }
    // adjust the returned backtrace according to the skipInner
    bt->begin = hpcrun_skip_chords(bt_last, bt_beg, skipInner);
  }

  bt->partial_unwind = false;
  return true;
}

