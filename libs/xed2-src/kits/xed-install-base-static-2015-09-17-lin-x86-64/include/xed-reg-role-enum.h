/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-reg-role-enum.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_REG_ROLE_ENUM_H_)
# define _XED_REG_ROLE_ENUM_H_
#include "xed-common-hdrs.h"
typedef enum {
  XED_REG_ROLE_INVALID,
  XED_REG_ROLE_NORMAL, ///< Register is a normal register
  XED_REG_ROLE_SEGREG0, ///< The segment register associated with the first memop
  XED_REG_ROLE_SEGREG1, ///< The segment register associated with the second memop
  XED_REG_ROLE_BASE0, ///< The base register associated with the first memop
  XED_REG_ROLE_BASE1, ///< The base register associated with the second memop
  XED_REG_ROLE_INDEX, ///< The index register associated with the first memop
  XED_REG_ROLE_LAST
} xed_reg_role_enum_t;

/// This converts strings to #xed_reg_role_enum_t types.
/// @param s A C-string.
/// @return #xed_reg_role_enum_t
/// @ingroup ENUM
XED_DLL_EXPORT xed_reg_role_enum_t str2xed_reg_role_enum_t(const char* s);
/// This converts strings to #xed_reg_role_enum_t types.
/// @param p An enumeration element of type xed_reg_role_enum_t.
/// @return string
/// @ingroup ENUM
XED_DLL_EXPORT const char* xed_reg_role_enum_t2str(const xed_reg_role_enum_t p);

/// Returns the last element of the enumeration
/// @return xed_reg_role_enum_t The last element of the enumeration.
/// @ingroup ENUM
XED_DLL_EXPORT xed_reg_role_enum_t xed_reg_role_enum_t_last(void);
#endif