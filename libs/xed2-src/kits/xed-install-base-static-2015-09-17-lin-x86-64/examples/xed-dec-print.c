/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-dec-print.c
// decode and print

#include "xed-interface.h"
#include "xed-examples-util.h"
#include <stdio.h>

int main(int argc, char** argv);

int 
main(int argc, char** argv)
{
    xed_error_enum_t xed_error;
    xed_decoded_inst_t xedd;
#define BUFLEN  1000
    char buffer[BUFLEN];
    xed_bool_t ok;
    xed_machine_mode_enum_t mmode;
    xed_address_width_enum_t stack_addr_width;

    // example instructions
    xed_uint_t   bytes = 2;
    xed_uint8_t  itext[XED_MAX_INSTRUCTION_BYTES] = { 0x00, 0x00 };

    xed_tables_init();
    
    mmode=XED_MACHINE_MODE_LEGACY_32;
    stack_addr_width =XED_ADDRESS_WIDTH_32b;
    xed_decoded_inst_zero(&xedd);
    xed_decoded_inst_set_mode(&xedd, mmode, stack_addr_width);
    xed_error = xed_decode(&xedd, itext,bytes);
    if (xed_error == XED_ERROR_NONE)
    {
        ok = xed_format_context(XED_SYNTAX_ATT, &xedd, buffer, BUFLEN, 0, 0, 0);
        if (ok) {
            printf("%s\n", buffer);
            return 0;
        }
        printf("Error disassembling\n");
        return 1;
    }
    printf("Decoding error\n");
    return 1;
    (void) argv; (void)argc;
}
