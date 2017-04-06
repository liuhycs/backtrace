#ifndef SRG_BACKTRACE_H
#define SRG_BACKTRACE_H

#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "unwind/common/backtrace.h"
#include "frame.h"

typedef struct {
  sigjmp_buf jb;
} sigjmp_buf_t;

typedef void siglongjmp_fcn(sigjmp_buf, int);
siglongjmp_fcn *hpcrun_get_real_siglongjmp(void);

void thread_data_init(thread_data_t* td); 
frame_t* hpcrun_expand_btbuf(thread_data_t* td);
void hpcrun_ensure_btbuf_avail(thread_data_t* td);
void backtrace_init();

#endif
