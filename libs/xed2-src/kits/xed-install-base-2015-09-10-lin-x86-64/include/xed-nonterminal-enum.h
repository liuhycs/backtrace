/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-nonterminal-enum.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_NONTERMINAL_ENUM_H_)
# define _XED_NONTERMINAL_ENUM_H_
#include "xed-common-hdrs.h"
typedef enum {
  XED_NONTERMINAL_INVALID,
  XED_NONTERMINAL_AR10,
  XED_NONTERMINAL_AR11,
  XED_NONTERMINAL_AR12,
  XED_NONTERMINAL_AR13,
  XED_NONTERMINAL_AR14,
  XED_NONTERMINAL_AR15,
  XED_NONTERMINAL_AR8,
  XED_NONTERMINAL_AR9,
  XED_NONTERMINAL_ARAX,
  XED_NONTERMINAL_ARBP,
  XED_NONTERMINAL_ARBX,
  XED_NONTERMINAL_ARCX,
  XED_NONTERMINAL_ARDI,
  XED_NONTERMINAL_ARDX,
  XED_NONTERMINAL_ARSI,
  XED_NONTERMINAL_ARSP,
  XED_NONTERMINAL_ASZ_NONTERM,
  XED_NONTERMINAL_AVX512_ROUND,
  XED_NONTERMINAL_AVX_INSTRUCTIONS,
  XED_NONTERMINAL_AVX_SPLITTER,
  XED_NONTERMINAL_BND_B,
  XED_NONTERMINAL_BND_B_CHECK,
  XED_NONTERMINAL_BND_R,
  XED_NONTERMINAL_BND_R_CHECK,
  XED_NONTERMINAL_BRANCH_HINT,
  XED_NONTERMINAL_BRDISP32,
  XED_NONTERMINAL_BRDISP8,
  XED_NONTERMINAL_BRDISPZ,
  XED_NONTERMINAL_CR_B,
  XED_NONTERMINAL_CR_R,
  XED_NONTERMINAL_CR_WIDTH,
  XED_NONTERMINAL_DF64,
  XED_NONTERMINAL_DR_B,
  XED_NONTERMINAL_DR_R,
  XED_NONTERMINAL_ESIZE_128_BITS,
  XED_NONTERMINAL_ESIZE_16_BITS,
  XED_NONTERMINAL_ESIZE_1_BITS,
  XED_NONTERMINAL_ESIZE_2_BITS,
  XED_NONTERMINAL_ESIZE_32_BITS,
  XED_NONTERMINAL_ESIZE_4_BITS,
  XED_NONTERMINAL_ESIZE_64_BITS,
  XED_NONTERMINAL_ESIZE_8_BITS,
  XED_NONTERMINAL_EVEX_INSTRUCTIONS,
  XED_NONTERMINAL_EVEX_SPLITTER,
  XED_NONTERMINAL_FINAL_DSEG,
  XED_NONTERMINAL_FINAL_DSEG1,
  XED_NONTERMINAL_FINAL_DSEG1_MODE64,
  XED_NONTERMINAL_FINAL_DSEG1_NOT64,
  XED_NONTERMINAL_FINAL_DSEG_MODE64,
  XED_NONTERMINAL_FINAL_DSEG_NOT64,
  XED_NONTERMINAL_FINAL_ESEG,
  XED_NONTERMINAL_FINAL_ESEG1,
  XED_NONTERMINAL_FINAL_SSEG,
  XED_NONTERMINAL_FINAL_SSEG0,
  XED_NONTERMINAL_FINAL_SSEG1,
  XED_NONTERMINAL_FINAL_SSEG_MODE64,
  XED_NONTERMINAL_FINAL_SSEG_NOT64,
  XED_NONTERMINAL_FIX_ROUND_LEN128,
  XED_NONTERMINAL_FIX_ROUND_LEN512,
  XED_NONTERMINAL_FORCE64,
  XED_NONTERMINAL_GPR16_B,
  XED_NONTERMINAL_GPR16_R,
  XED_NONTERMINAL_GPR16_SB,
  XED_NONTERMINAL_GPR32_B,
  XED_NONTERMINAL_GPR32_R,
  XED_NONTERMINAL_GPR32_SB,
  XED_NONTERMINAL_GPR32_X,
  XED_NONTERMINAL_GPR64_B,
  XED_NONTERMINAL_GPR64_R,
  XED_NONTERMINAL_GPR64_SB,
  XED_NONTERMINAL_GPR64_X,
  XED_NONTERMINAL_GPR8_B,
  XED_NONTERMINAL_GPR8_R,
  XED_NONTERMINAL_GPR8_SB,
  XED_NONTERMINAL_GPRM_B,
  XED_NONTERMINAL_GPRM_R,
  XED_NONTERMINAL_GPRV_B,
  XED_NONTERMINAL_GPRV_R,
  XED_NONTERMINAL_GPRV_SB,
  XED_NONTERMINAL_GPRY_B,
  XED_NONTERMINAL_GPRY_N,
  XED_NONTERMINAL_GPRY_R,
  XED_NONTERMINAL_GPRZ_B,
  XED_NONTERMINAL_GPRZ_R,
  XED_NONTERMINAL_IGNORE66,
  XED_NONTERMINAL_IMMUNE66,
  XED_NONTERMINAL_IMMUNE66_LOOP64,
  XED_NONTERMINAL_IMMUNE_REXW,
  XED_NONTERMINAL_INSTRUCTIONS,
  XED_NONTERMINAL_ISA,
  XED_NONTERMINAL_MASK1,
  XED_NONTERMINAL_MASK_B,
  XED_NONTERMINAL_MASK_I3,
  XED_NONTERMINAL_MASK_N,
  XED_NONTERMINAL_MASK_R,
  XED_NONTERMINAL_MEMDISP,
  XED_NONTERMINAL_MEMDISP16,
  XED_NONTERMINAL_MEMDISP32,
  XED_NONTERMINAL_MEMDISP8,
  XED_NONTERMINAL_MEMDISPV,
  XED_NONTERMINAL_MMX_B,
  XED_NONTERMINAL_MMX_R,
  XED_NONTERMINAL_MODRM,
  XED_NONTERMINAL_MODRM16,
  XED_NONTERMINAL_MODRM32,
  XED_NONTERMINAL_MODRM64ALT32,
  XED_NONTERMINAL_NELEM_EIGHTHMEM,
  XED_NONTERMINAL_NELEM_FULL,
  XED_NONTERMINAL_NELEM_FULLMEM,
  XED_NONTERMINAL_NELEM_GPR_READER,
  XED_NONTERMINAL_NELEM_GPR_READER_BYTE,
  XED_NONTERMINAL_NELEM_GPR_READER_SUBDWORD,
  XED_NONTERMINAL_NELEM_GPR_READER_WORD,
  XED_NONTERMINAL_NELEM_GPR_WRITER_LDOP,
  XED_NONTERMINAL_NELEM_GPR_WRITER_LDOP_D,
  XED_NONTERMINAL_NELEM_GPR_WRITER_LDOP_Q,
  XED_NONTERMINAL_NELEM_GPR_WRITER_STORE,
  XED_NONTERMINAL_NELEM_GPR_WRITER_STORE_BYTE,
  XED_NONTERMINAL_NELEM_GPR_WRITER_STORE_SUBDWORD,
  XED_NONTERMINAL_NELEM_GPR_WRITER_STORE_WORD,
  XED_NONTERMINAL_NELEM_GSCAT,
  XED_NONTERMINAL_NELEM_HALF,
  XED_NONTERMINAL_NELEM_HALFMEM,
  XED_NONTERMINAL_NELEM_MEM128,
  XED_NONTERMINAL_NELEM_MOVDDUP,
  XED_NONTERMINAL_NELEM_QUARTERMEM,
  XED_NONTERMINAL_NELEM_SCALAR,
  XED_NONTERMINAL_NELEM_TUPLE1,
  XED_NONTERMINAL_NELEM_TUPLE1_BYTE,
  XED_NONTERMINAL_NELEM_TUPLE1_SUBDWORD,
  XED_NONTERMINAL_NELEM_TUPLE1_WORD,
  XED_NONTERMINAL_NELEM_TUPLE2,
  XED_NONTERMINAL_NELEM_TUPLE4,
  XED_NONTERMINAL_NELEM_TUPLE8,
  XED_NONTERMINAL_OEAX,
  XED_NONTERMINAL_ONE,
  XED_NONTERMINAL_ORAX,
  XED_NONTERMINAL_ORBP,
  XED_NONTERMINAL_ORDX,
  XED_NONTERMINAL_ORSP,
  XED_NONTERMINAL_OSZ_NONTERM,
  XED_NONTERMINAL_OVERRIDE_SEG0,
  XED_NONTERMINAL_OVERRIDE_SEG1,
  XED_NONTERMINAL_PREFIXES,
  XED_NONTERMINAL_REFINING66,
  XED_NONTERMINAL_REMOVE_SEGMENT,
  XED_NONTERMINAL_RFLAGS,
  XED_NONTERMINAL_RIP,
  XED_NONTERMINAL_SAE,
  XED_NONTERMINAL_SEG,
  XED_NONTERMINAL_SE_IMM8,
  XED_NONTERMINAL_SIB,
  XED_NONTERMINAL_SIB_BASE0,
  XED_NONTERMINAL_SIMM8,
  XED_NONTERMINAL_SIMMZ,
  XED_NONTERMINAL_SRBP,
  XED_NONTERMINAL_SRSP,
  XED_NONTERMINAL_UIMM16,
  XED_NONTERMINAL_UIMM32,
  XED_NONTERMINAL_UIMM8,
  XED_NONTERMINAL_UIMM8_1,
  XED_NONTERMINAL_UIMMV,
  XED_NONTERMINAL_UISA_SE_IMM8,
  XED_NONTERMINAL_UISA_VMODRM_XMM,
  XED_NONTERMINAL_UISA_VMODRM_YMM,
  XED_NONTERMINAL_UISA_VMODRM_ZMM,
  XED_NONTERMINAL_UISA_VSIB_BASE,
  XED_NONTERMINAL_UISA_VSIB_INDEX_XMM,
  XED_NONTERMINAL_UISA_VSIB_INDEX_YMM,
  XED_NONTERMINAL_UISA_VSIB_INDEX_ZMM,
  XED_NONTERMINAL_UISA_VSIB_XMM,
  XED_NONTERMINAL_UISA_VSIB_YMM,
  XED_NONTERMINAL_UISA_VSIB_ZMM,
  XED_NONTERMINAL_VGPR32_B,
  XED_NONTERMINAL_VGPR32_B_32,
  XED_NONTERMINAL_VGPR32_B_64,
  XED_NONTERMINAL_VGPR32_N,
  XED_NONTERMINAL_VGPR32_N_32,
  XED_NONTERMINAL_VGPR32_N_64,
  XED_NONTERMINAL_VGPR32_R,
  XED_NONTERMINAL_VGPR32_R_32,
  XED_NONTERMINAL_VGPR32_R_64,
  XED_NONTERMINAL_VGPR64_B,
  XED_NONTERMINAL_VGPR64_N,
  XED_NONTERMINAL_VGPR64_R,
  XED_NONTERMINAL_VGPRV_N,
  XED_NONTERMINAL_VMODRM_XMM,
  XED_NONTERMINAL_VMODRM_YMM,
  XED_NONTERMINAL_VSIB_BASE,
  XED_NONTERMINAL_VSIB_INDEX_XMM,
  XED_NONTERMINAL_VSIB_INDEX_YMM,
  XED_NONTERMINAL_VSIB_XMM,
  XED_NONTERMINAL_VSIB_YMM,
  XED_NONTERMINAL_X87,
  XED_NONTERMINAL_XMM_B,
  XED_NONTERMINAL_XMM_B3,
  XED_NONTERMINAL_XMM_B3_32,
  XED_NONTERMINAL_XMM_B3_64,
  XED_NONTERMINAL_XMM_B_32,
  XED_NONTERMINAL_XMM_B_64,
  XED_NONTERMINAL_XMM_I3,
  XED_NONTERMINAL_XMM_N,
  XED_NONTERMINAL_XMM_N3,
  XED_NONTERMINAL_XMM_N3_32,
  XED_NONTERMINAL_XMM_N3_64,
  XED_NONTERMINAL_XMM_N_32,
  XED_NONTERMINAL_XMM_N_64,
  XED_NONTERMINAL_XMM_R,
  XED_NONTERMINAL_XMM_R3,
  XED_NONTERMINAL_XMM_R3_32,
  XED_NONTERMINAL_XMM_R3_64,
  XED_NONTERMINAL_XMM_R_32,
  XED_NONTERMINAL_XMM_R_64,
  XED_NONTERMINAL_XMM_SE,
  XED_NONTERMINAL_XMM_SE32,
  XED_NONTERMINAL_XMM_SE64,
  XED_NONTERMINAL_XOP_INSTRUCTIONS,
  XED_NONTERMINAL_YMM_B,
  XED_NONTERMINAL_YMM_B3,
  XED_NONTERMINAL_YMM_B3_32,
  XED_NONTERMINAL_YMM_B3_64,
  XED_NONTERMINAL_YMM_B_32,
  XED_NONTERMINAL_YMM_B_64,
  XED_NONTERMINAL_YMM_I3,
  XED_NONTERMINAL_YMM_N,
  XED_NONTERMINAL_YMM_N3,
  XED_NONTERMINAL_YMM_N3_32,
  XED_NONTERMINAL_YMM_N3_64,
  XED_NONTERMINAL_YMM_N_32,
  XED_NONTERMINAL_YMM_N_64,
  XED_NONTERMINAL_YMM_R,
  XED_NONTERMINAL_YMM_R3,
  XED_NONTERMINAL_YMM_R3_32,
  XED_NONTERMINAL_YMM_R3_64,
  XED_NONTERMINAL_YMM_R_32,
  XED_NONTERMINAL_YMM_R_64,
  XED_NONTERMINAL_YMM_SE,
  XED_NONTERMINAL_YMM_SE32,
  XED_NONTERMINAL_YMM_SE64,
  XED_NONTERMINAL_ZMM_B3,
  XED_NONTERMINAL_ZMM_B3_32,
  XED_NONTERMINAL_ZMM_B3_64,
  XED_NONTERMINAL_ZMM_I3,
  XED_NONTERMINAL_ZMM_N3,
  XED_NONTERMINAL_ZMM_N3_32,
  XED_NONTERMINAL_ZMM_N3_64,
  XED_NONTERMINAL_ZMM_R3,
  XED_NONTERMINAL_ZMM_R3_32,
  XED_NONTERMINAL_ZMM_R3_64,
  XED_NONTERMINAL_LAST
} xed_nonterminal_enum_t;

/// This converts strings to #xed_nonterminal_enum_t types.
/// @param s A C-string.
/// @return #xed_nonterminal_enum_t
/// @ingroup ENUM
XED_DLL_EXPORT xed_nonterminal_enum_t str2xed_nonterminal_enum_t(const char* s);
/// This converts strings to #xed_nonterminal_enum_t types.
/// @param p An enumeration element of type xed_nonterminal_enum_t.
/// @return string
/// @ingroup ENUM
XED_DLL_EXPORT const char* xed_nonterminal_enum_t2str(const xed_nonterminal_enum_t p);

/// Returns the last element of the enumeration
/// @return xed_nonterminal_enum_t The last element of the enumeration.
/// @ingroup ENUM
XED_DLL_EXPORT xed_nonterminal_enum_t xed_nonterminal_enum_t_last(void);
#endif