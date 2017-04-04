
#include "srg_backtrace.h"


void thread_data_init(thread_data_t* td) {
  // ----------------------------------------
  // backtrace buffer
  // ----------------------------------------
  td->btbuf_cur = NULL;
  td->btbuf_beg = hpcrun_malloc(sizeof(frame_t) * BACKTRACE_INIT_SZ);
  td->btbuf_end = td->btbuf_beg + BACKTRACE_INIT_SZ;

  hpcrun_bt_init(&(td->bt), NEW_BACKTRACE_INIT_SZ);

  // ----------------------------------------
  // trampoline
  // ----------------------------------------
  td->tramp_present     = false;
  td->tramp_retn_addr   = NULL;
  td->tramp_loc         = NULL;
  td->cached_bt         = hpcrun_malloc(sizeof(frame_t)
      * CACHED_BACKTRACE_SIZE);
  td->cached_bt_end     = td->cached_bt;          
  td->cached_bt_buf_end = td->cached_bt + CACHED_BACKTRACE_SIZE;
  td->tramp_frame       = NULL;
  td->tramp_cct_node    = NULL;

}

void hpcrun_cached_bt_adjust_size(size_t n) {
  thread_data_t *td = hpcrun_get_thread_data();
  if ((td->cached_bt_buf_end - td->cached_bt) >= n) {
    return; // cached backtrace buffer is already big enough
  }

  frame_t* newbuf = hpcrun_malloc(n * sizeof(frame_t));
  memcpy(newbuf, td->cached_bt, (void*)td->cached_bt_buf_end - (void*)td->cached_bt);
  size_t idx            = td->cached_bt_end - td->cached_bt;
  td->cached_bt         = newbuf;
  td->cached_bt_buf_end = newbuf+n;
  td->cached_bt_end     = newbuf + idx;
}

frame_t* hpcrun_expand_btbuf(thread_data_t* td) {
  frame_t* unwind = td->btbuf_cur;

  /* how big is the current buffer? */
  size_t sz = td->btbuf_end - td->btbuf_beg;
  size_t newsz = sz*2;
  /* how big is the current backtrace? */
  size_t btsz = td->btbuf_end - td->btbuf_sav;
  /* how big is the backtrace we're recording? */
  size_t recsz = unwind - td->btbuf_beg;
  /* get new buffer */
  frame_t *newbt = hpcrun_malloc(newsz*sizeof(frame_t));

  if(td->btbuf_sav > td->btbuf_end) {
    EMSG("Invariant btbuf_sav > btbuf_end violated");
    abort();
  }

  /* copy frames from old to new */
  memcpy(newbt, td->btbuf_beg, recsz*sizeof(frame_t));
  memcpy(newbt+newsz-btsz, td->btbuf_end-btsz, btsz*sizeof(frame_t));

  /* setup new pointers */
  td->btbuf_beg = newbt;
  td->btbuf_end = newbt+newsz;
  td->btbuf_sav = newbt+newsz-btsz;

  /* return new unwind pointer */
  return newbt+recsz;
}

void hpcrun_ensure_btbuf_avail(thread_data_t* td) {
  if (td->btbuf_cur == td->btbuf_end) {
    td->btbuf_cur = hpcrun_expand_btbuf(td);
    td->btbuf_sav = td->btbuf_end;
  }
}


