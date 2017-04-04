/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-encoder-iforms.h

// This file was automatically generated.
// Do not edit this file.

#if !defined(_XED_ENCODER_IFORMS_H_)
# define _XED_ENCODER_IFORMS_H_
#include "xed-types.h"
typedef struct xed_encoder_iforms_s {
    xed_uint32_t x_MEMDISPv;
    xed_uint32_t x_SIBBASE_ENCODE_SIB1;
    xed_uint32_t x_VEX_MAP_ENC;
    xed_uint32_t x_SIB_NT;
    xed_uint32_t x_UIMM8_1;
    xed_uint32_t x_SIBBASE_ENCODE;
    xed_uint32_t x_VEX_ESCVL_ENC;
    xed_uint32_t x_PREFIX_ENC;
    xed_uint32_t x_VEXED_REX;
    xed_uint32_t x_REMOVE_SEGMENT;
    xed_uint32_t x_VSIB_ENC;
    xed_uint32_t x_EVEX_REXB_ENC;
    xed_uint32_t x_MODRM_RM_ENCODE_EA64_SIB0;
    xed_uint32_t x_VEX_REXXB_ENC;
    xed_uint32_t x_EVEX_REXRR_ENC;
    xed_uint32_t x_AVX512_EVEX_BYTE3_ENC;
    xed_uint32_t x_EVEX_REXW_VVVV_ENC;
    xed_uint32_t x_VEX_REG_ENC;
    xed_uint32_t x_UISA_SE_IMM8;
    xed_uint32_t x_SIMM8;
    xed_uint32_t x_XOP_MAP_ENC;
    xed_uint32_t x_MODRM_RM_ENCODE_EA32_SIB0;
    xed_uint32_t x_UIMM8;
    xed_uint32_t x_MODRM_RM_ENCODE_EA16_SIB0;
    xed_uint32_t x_XOP_REXXB_ENC;
    xed_uint32_t x_EVEX_MAP_ENC;
    xed_uint32_t x_MEMDISP8;
    xed_uint32_t x_MODRM_RM_ENCODE;
    xed_uint32_t x_REX_PREFIX_ENC;
    xed_uint32_t x_UIMM16;
    xed_uint32_t x_VEX_TYPE_ENC;
    xed_uint32_t x_EVEX_UPP_ENC;
    xed_uint32_t x_VEX_REXR_ENC;
    xed_uint32_t x_BRDISP32;
    xed_uint32_t x_MEMDISP32;
    xed_uint32_t x_MEMDISP16;
    xed_uint32_t x_SIBINDEX_ENCODE;
    xed_uint32_t x_SE_IMM8;
    xed_uint32_t x_UIMM32;
    xed_uint32_t x_SIMMz;
    xed_uint32_t x_UIMMv;
    xed_uint32_t x_EVEX_62_REXR_ENC;
    xed_uint32_t x_DISP_NT;
    xed_uint32_t x_MODRM_MOD_ENCODE;
    xed_uint32_t x_MEMDISP;
    xed_uint32_t x_VSIB_ENC_BASE;
    xed_uint32_t x_BRDISP8;
    xed_uint32_t x_BRDISPz;
    xed_uint32_t x_EVEX_REXX_ENC;
    xed_uint32_t x_XOP_TYPE_ENC;
} xed_encoder_iforms_t;
#endif
