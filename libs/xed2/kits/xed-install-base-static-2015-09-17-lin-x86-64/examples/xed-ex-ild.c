/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */


#include "xed-interface.h"
#include <stdio.h>

int main(int argc, char** argv);

int main(int argc, char** argv)
{
    xed_bool_t long_mode = 1;
    xed_decoded_inst_t xedd;
    xed_state_t dstate;
    unsigned char itext[15] = { 0xf2, 0x2e, 0x4f, 0x0F, 0x85, 0x99,
                                0x00, 0x00, 0x00 };

    xed_tables_init(); // one time per process

    if (long_mode) 
        dstate.mmode=XED_MACHINE_MODE_LONG_64;
    else 
        dstate.mmode=XED_MACHINE_MODE_LEGACY_32;

    xed_decoded_inst_zero_set_mode(&xedd, &dstate);
    xed_ild_decode(&xedd, itext, XED_MAX_INSTRUCTION_BYTES);
    printf("length = %u\n",xed_decoded_inst_get_length(&xedd));
    
    return 0;
    (void) argc; (void) argv; //pacify compiler

}
