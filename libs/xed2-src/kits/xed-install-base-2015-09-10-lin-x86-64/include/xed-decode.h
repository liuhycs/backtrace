/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-decode.h 


#ifndef _XED_DECODE_H_
# define _XED_DECODE_H_

#include "xed-decoded-inst.h"
#include "xed-error-enum.h"

/// This is the main interface to the decoder.
///  @param xedd the decoded instruction of type #xed_decoded_inst_t . Mode/state sent in via xedd; See the #xed_state_t
///  @param itext the pointer to the array of instruction text bytes
///  @param bytes  the length of the itext input array. 1 to 15 bytes, anything more is ignored.
///  @return #xed_error_enum_t indiciating success (#XED_ERROR_NONE) or failure. Note failure can be due to not
///  enough bytes in the input array.
///
/// The maximum instruction is 15B and XED will tell you how long the
/// actual instruction is via an API function call
/// xed_decoded_inst_get_length().  However, it is not always safe or
/// advisable for XED to read 15 bytes if the decode location is at the
/// boundary of some sort of protection limit. For example, if one is
/// decoding near the end of a page and the XED user does not want to cause
/// extra page faults, one might send in the number of bytes that would
/// stop at the page boundary. In this case, XED might not be able to
/// decode the instruction and would return an error. The XED user would
/// then have to decide if it was safe to touch the next page and try again
/// to decode with more bytes.  Also sometimes the user process does not
/// have read access to the next page and this allows the user to prevent
/// XED from causing process termination by limiting the memory range that
/// XED will access.  
///
/// @ingroup DEC
XED_DLL_EXPORT xed_error_enum_t
xed_decode(xed_decoded_inst_t* xedd, 
           const xed_uint8_t* itext, 
           const unsigned int bytes);


#endif

