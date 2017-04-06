/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-disas-elf.h

#if !defined(_XED_DISAS_ELF_H_)
# define _XED_DISAS_ELF_H_
#if defined(__linux) || defined(__linux__) || defined(__FreeBSD__)
# define XED_ELF_READER
#endif
# if defined(XED_ELF_READER)


#include "xed-interface.h"
#include "xed-examples-util.h"

void xed_disas_elf(xed_disas_info_t* fi);

# endif
#endif
