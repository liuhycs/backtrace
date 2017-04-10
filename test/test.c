#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "srg_backtrace.h"

#define __USE_GNU
#include <dlfcn.h>
#include <execinfo.h>

void c(){
  
  fprintf(stderr, "==============backtrace=================>\n");
  void* array[256];
  int frames;
  frames = backtrace(array, 256);
  int i;
  for(i = 0; i < frames; i++) {
    fprintf(stderr, "%p ", array[i]);
  }
  fprintf(stderr, "\n==============backtrace end=================>\n");

  thread_data_t td;
  thread_data_init(&td);
  backtrace_info_t bt;
  ucontext_t ut;
  getcontext(&ut);
  hpcrun_generate_backtrace(&td, &bt, &ut);  

  frame_t* _it = td.btbuf_beg;
  frame_t* _cur = td.btbuf_cur;

  while(_it != _cur){
    fprintf(stderr, "ip_norm.lm_id = %d, and ip_norm.lm_ip = %lx \n", _it->ip_norm.lm_id, _it->ip_norm.lm_ip);
    Dl_info info;
    if(dladdr((void*)_it->ip_norm.lm_ip, &info))
      fprintf(stderr, "dli_fname %s, dli_fbase %p, dli_sname %s\n", info.dli_fname, info.dli_fbase, info.dli_sname);
    _it++;
  }

  char* ptr = malloc(10);
  *ptr = 'c';
  free(ptr);
}

void b(){
  c();
  char* ptr = malloc(10);
  *ptr = 'b';
  free(ptr);
}

void a(){
  b();
  char* ptr = malloc(10);
  *ptr = 'a';
  free(ptr);
}

int main() {
  backtrace_init((void*)__builtin_frame_address(0));
  a();
  char* ptr = malloc(10);
  *ptr = 'm';
  free(ptr);
  //while(1);
}
