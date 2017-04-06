/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */

/// @file xed-enc-lang.h

#if !defined(_XED_ENC_LANG_H_)
# define _XED_ENC_LANG_H_

#include "xed-interface.h" 

typedef  struct 
{
    xed_state_t dstate;
    char const* command;
} ascii_encode_request_t;


xed_encoder_request_t
parse_encode_request(ascii_encode_request_t areq);

#endif
