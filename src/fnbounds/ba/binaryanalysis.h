#ifndef _FNBOUNDS__H_
#define _FNBOUNDS__H_

#include <stdint.h>
#include "code-ranges.h"
#include "fnbounds/fnbounds_file_header.h"

#ifdef __cplusplus
extern "C" {
#endif
  void* ba_fnbounds(struct fnbounds_file_header* fh, char* filename);
#ifdef __cplusplus
};
#endif

void dump_file_info(const char *filename, DiscoverFnTy fn_discovery);

void syserv_add_addr(void *, long);

void syserv_add_header(int is_relocatable, uintptr_t ref_offset);

#endif  // _FNBOUNDS_H_
