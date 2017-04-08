#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "srg_backtrace.h"

void c(){
  thread_data_t td;
  thread_data_init(&td);
  backtrace_info_t bt;
  ucontext_t ut;
  getcontext(&ut);
  hpcrun_generate_backtrace(&td, &bt, &ut);
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
}
