#ifndef SRG_BACKTRACE_H
#define SRG_BACKTRACE_H

#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "unwind/common/backtrace.h"
#include "fnbounds/fnbounds_interface.h"
#include "frame.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  sigjmp_buf jb;
} sigjmp_buf_t;

typedef void siglongjmp_fcn(sigjmp_buf, int);
siglongjmp_fcn *hpcrun_get_real_siglongjmp(void);

extern void hpcrun_unw_init();

void backtrace_init(void* fb);
void thread_data_init(thread_data_t* td); 
frame_t* hpcrun_expand_btbuf(thread_data_t* td);
void hpcrun_ensure_btbuf_avail(thread_data_t* td);
void hpcrun_cached_bt_adjust_size(thread_data_t *td, size_t n);

#ifdef __cplusplus
};
#endif

#endif
