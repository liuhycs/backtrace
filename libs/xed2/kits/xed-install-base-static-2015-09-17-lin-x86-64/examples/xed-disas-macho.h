/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-disas-macho.H
#if !defined(_XED_DISAS_MACHO_H_)
# define _XED_DISAS_MACHO_H_

# if defined(__APPLE__)
#  include "xed-interface.h" 
#  include "xed-examples-util.h" 

void
xed_disas_macho(xed_disas_info_t* fi);
# endif
#endif
