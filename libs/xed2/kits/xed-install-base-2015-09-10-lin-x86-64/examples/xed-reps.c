/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-min.c
/// @brief a minimal toy example of using the decoder. 

#include "xed-interface.h"
#include <stdio.h>

int main(int argc, char** argv);

int xtest(xed_iclass_enum_t a, xed_iclass_enum_t b)
{
    if (a != b) {
        printf("MISMATCH: %s %s\n",
               xed_iclass_enum_t2str(a),
               xed_iclass_enum_t2str(b));
        return 1;
    }
    printf("MATCH: %s %s\n",
           xed_iclass_enum_t2str(a),
           xed_iclass_enum_t2str(b));
    return 0;
}

int main(int argc, char** argv)
{
    xed_uint_t i=0;
    int r=0;

    const xed_iclass_enum_t repe[] = {
        XED_ICLASS_REPE_CMPSB,
        XED_ICLASS_REPE_CMPSD,
        XED_ICLASS_REPE_CMPSQ,
        XED_ICLASS_REPE_CMPSW,
        XED_ICLASS_REPE_SCASB,
        XED_ICLASS_REPE_SCASD,
        XED_ICLASS_REPE_SCASQ,
        XED_ICLASS_REPE_SCASW,
        XED_ICLASS_INVALID };
    const xed_iclass_enum_t repne[] = {
        XED_ICLASS_REPNE_CMPSB,
        XED_ICLASS_REPNE_CMPSD,
        XED_ICLASS_REPNE_CMPSQ,
        XED_ICLASS_REPNE_CMPSW,
        XED_ICLASS_REPNE_SCASB,
        XED_ICLASS_REPNE_SCASD,
        XED_ICLASS_REPNE_SCASQ,
        XED_ICLASS_REPNE_SCASW,
        XED_ICLASS_INVALID };
    const xed_iclass_enum_t rep[] = {
        XED_ICLASS_REP_INSB,
        XED_ICLASS_REP_INSD,
        XED_ICLASS_REP_INSW,
        XED_ICLASS_REP_LODSB,
        XED_ICLASS_REP_LODSD,
        XED_ICLASS_REP_LODSQ,
        XED_ICLASS_REP_LODSW,
        XED_ICLASS_REP_MOVSB,
        XED_ICLASS_REP_MOVSD,
        XED_ICLASS_REP_MOVSQ,
        XED_ICLASS_REP_MOVSW,
        XED_ICLASS_REP_OUTSB,
        XED_ICLASS_REP_OUTSD,
        XED_ICLASS_REP_OUTSW,
        XED_ICLASS_REP_STOSB,
        XED_ICLASS_REP_STOSD,
        XED_ICLASS_REP_STOSQ,
        XED_ICLASS_REP_STOSW,
        XED_ICLASS_INVALID };


    xed_tables_init();

    for (i=0; repe[i]!=XED_ICLASS_INVALID; i++) {
        xed_iclass_enum_t norep = xed_norep_map(repe[i]);
        xed_iclass_enum_t xr  = xed_repe_map(norep);
        r  |= xtest(repe[i],xr);
    }
    for (i=0; repne[i]!=XED_ICLASS_INVALID; i++) {
        xed_iclass_enum_t norep = xed_norep_map(repne[i]);
        xed_iclass_enum_t xr  = xed_repne_map(norep);
        r |= xtest(repne[i],xr);
    }
    for (i=0; rep[i]!=XED_ICLASS_INVALID; i++) {
        xed_iclass_enum_t norep = xed_norep_map(rep[i]);
        xed_iclass_enum_t xr  = xed_rep_map(norep);
        r |= xtest(rep[i],xr);
    }

    return r;
    (void) argc; (void) argv; //pacify compiler
}
