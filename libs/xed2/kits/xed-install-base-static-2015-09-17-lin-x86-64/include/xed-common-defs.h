/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-common-defs.h 
/// @brief some pervasive defines



#ifndef _XED_COMMON_DEFS_H_
# define _XED_COMMON_DEFS_H_

////////////////////////////////////////////////////////////////////////////

#define XED_MAX_OPERANDS 11
#define XED_MAX_NONTERMINALS_PER_INSTRUCTION 20 // FIXME somewhat arbitrary

 // for most things it is 4, but one 64b mov allows 8
#define XED_MAX_DISPLACEMENT_BYTES  8

 // for most things it is max 4, but one 64b mov allows 8.
#define XED_MAX_IMMEDIATE_BYTES  8

#define XED_MAX_INSTRUCTION_BYTES  15


#define XED_BYTE_MASK(x) ((x) & 0xFF)
#define XED_BYTE_CAST(x) (XED_STATIC_CAST(xed_uint8_t,x))

////////////////////////////////////////////////////////////////////////////
// used for defining bit-field widths
// Microsoft's compiler treats enumerations as signed and if you pack
// the bit-field with values, when you assign it to a full-width enumeration,
// you get junk-- a big negative number. This compensates for cases that I've
// encountered
#if defined(__GNUC__)
#  define XED_BIT_FIELD_PSEUDO_WIDTH4 4
#  define XED_BIT_FIELD_PSEUDO_WIDTH8 8
#else
#  define XED_BIT_FIELD_PSEUDO_WIDTH4 8
#  define XED_BIT_FIELD_PSEUDO_WIDTH8 16
#endif


#endif









