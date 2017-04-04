/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-error-enum.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_ERROR_ENUM_H_)
# define _XED_ERROR_ENUM_H_
#include "xed-common-hdrs.h"
typedef enum {
  XED_ERROR_NONE, ///< There was no error
  XED_ERROR_BUFFER_TOO_SHORT, ///< There were not enough bytes in the given buffer
  XED_ERROR_GENERAL_ERROR, ///< XED could not decode the given instruction
  XED_ERROR_INVALID_FOR_CHIP, ///< The instruciton is not valid for the specified chip
  XED_ERROR_BAD_REGISTER, ///< XED could not decode the given instruction because an invalid register encoding was used.
  XED_ERROR_BAD_LOCK_PREFIX, ///< A lock prefix was found where none is allowed.
  XED_ERROR_BAD_REP_PREFIX, ///< An F2 or F3 prefix was found where none is allowed.
  XED_ERROR_BAD_LEGACY_PREFIX, ///< A 66, F2 or F3 prefix was found where none is allowed.
  XED_ERROR_BAD_REX_PREFIX, ///< A REX prefix was found where none is allowed.
  XED_ERROR_BAD_EVEX_UBIT, ///< An illegal value for the EVEX.U bit was present in the instruction.
  XED_ERROR_BAD_MAP, ///< An illegal value for the MAP field was detected in the instruction.
  XED_ERROR_BAD_EVEX_V_PRIME, ///< EVEX.V'=0 was detected in a non-64b mode instruction.
  XED_ERROR_NO_OUTPUT_POINTER, ///< The output pointer for xed_agen was zero
  XED_ERROR_NO_AGEN_CALL_BACK_REGISTERED, ///< One or both of the callbacks for xed_agen were missing.
  XED_ERROR_BAD_MEMOP_INDEX, ///< Memop indices must be 0 or 1.
  XED_ERROR_CALLBACK_PROBLEM, ///< The register or segment callback for xed_agen experienced a problem
  XED_ERROR_GATHER_REGS, ///< The index, dest and mask regs for AVX2 gathers must be different.
  XED_ERROR_INSTR_TOO_LONG, ///< Full decode of instruction would exeed 15B.
  XED_ERROR_INVALID_MODE, ///< The instruction was not valid for the specified mode
  XED_ERROR_LAST
} xed_error_enum_t;

/// This converts strings to #xed_error_enum_t types.
/// @param s A C-string.
/// @return #xed_error_enum_t
/// @ingroup ENUM
XED_DLL_EXPORT xed_error_enum_t str2xed_error_enum_t(const char* s);
/// This converts strings to #xed_error_enum_t types.
/// @param p An enumeration element of type xed_error_enum_t.
/// @return string
/// @ingroup ENUM
XED_DLL_EXPORT const char* xed_error_enum_t2str(const xed_error_enum_t p);

/// Returns the last element of the enumeration
/// @return xed_error_enum_t The last element of the enumeration.
/// @ingroup ENUM
XED_DLL_EXPORT xed_error_enum_t xed_error_enum_t_last(void);
#endif
