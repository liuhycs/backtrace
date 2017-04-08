/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-flag-enum.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_FLAG_ENUM_H_)
# define _XED_FLAG_ENUM_H_
#include "xed-common-hdrs.h"
typedef enum {
  XED_FLAG_INVALID,
  XED_FLAG_of, ///<< overflow flag
  XED_FLAG_sf, ///< sign flag
  XED_FLAG_zf, ///< zero flag
  XED_FLAG_af, ///< auxilliary flag
  XED_FLAG_pf, ///< parity flag
  XED_FLAG_cf, ///< carry flag
  XED_FLAG_df, ///< direction flag
  XED_FLAG_vif, ///< virtual interrupt flag
  XED_FLAG_iopl, ///< I/O privilege level
  XED_FLAG_if, ///< interrupt flag
  XED_FLAG_ac, ///< alignment check
  XED_FLAG_vm, ///< virtual-8086 mode
  XED_FLAG_rf, ///< resume flag
  XED_FLAG_nt, ///< nested task
  XED_FLAG_tf, ///< traf flag
  XED_FLAG_id, ///< ID flag
  XED_FLAG_vip, ///< virtual interrupt pending
  XED_FLAG_fc0, ///< x87 FC0 flag
  XED_FLAG_fc1, ///< x87 FC1 flag
  XED_FLAG_fc2, ///< x87 FC2 flag
  XED_FLAG_fc3, ///< x87 FC3 flag
  XED_FLAG_LAST
} xed_flag_enum_t;

/// This converts strings to #xed_flag_enum_t types.
/// @param s A C-string.
/// @return #xed_flag_enum_t
/// @ingroup ENUM
XED_DLL_EXPORT xed_flag_enum_t str2xed_flag_enum_t(const char* s);
/// This converts strings to #xed_flag_enum_t types.
/// @param p An enumeration element of type xed_flag_enum_t.
/// @return string
/// @ingroup ENUM
XED_DLL_EXPORT const char* xed_flag_enum_t2str(const xed_flag_enum_t p);

/// Returns the last element of the enumeration
/// @return xed_flag_enum_t The last element of the enumeration.
/// @ingroup ENUM
XED_DLL_EXPORT xed_flag_enum_t xed_flag_enum_t_last(void);
#endif