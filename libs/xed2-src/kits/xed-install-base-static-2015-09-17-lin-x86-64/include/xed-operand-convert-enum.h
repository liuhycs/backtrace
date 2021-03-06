/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-operand-convert-enum.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_OPERAND_CONVERT_ENUM_H_)
# define _XED_OPERAND_CONVERT_ENUM_H_
#include "xed-common-hdrs.h"
typedef enum {
  XED_OPERAND_CONVERT_INVALID,
  XED_OPERAND_CONVERT_ZEROSTR,
  XED_OPERAND_CONVERT_SAESTR,
  XED_OPERAND_CONVERT_ROUNDC,
  XED_OPERAND_CONVERT_BCASTSTR,
  XED_OPERAND_CONVERT_LAST
} xed_operand_convert_enum_t;

/// This converts strings to #xed_operand_convert_enum_t types.
/// @param s A C-string.
/// @return #xed_operand_convert_enum_t
/// @ingroup ENUM
XED_DLL_EXPORT xed_operand_convert_enum_t str2xed_operand_convert_enum_t(const char* s);
/// This converts strings to #xed_operand_convert_enum_t types.
/// @param p An enumeration element of type xed_operand_convert_enum_t.
/// @return string
/// @ingroup ENUM
XED_DLL_EXPORT const char* xed_operand_convert_enum_t2str(const xed_operand_convert_enum_t p);

/// Returns the last element of the enumeration
/// @return xed_operand_convert_enum_t The last element of the enumeration.
/// @ingroup ENUM
XED_DLL_EXPORT xed_operand_convert_enum_t xed_operand_convert_enum_t_last(void);
#endif
