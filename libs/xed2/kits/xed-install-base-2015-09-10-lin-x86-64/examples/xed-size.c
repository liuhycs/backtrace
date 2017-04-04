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
int main(int argc, char** argv) {
    /* I use this to keep track of the size of my per-instruction data structures */
    xed_decoded_inst_t x;
    /*xed_tables_init();  */
    printf("xed_decoded_inst_t         %12d\n", (int)sizeof(xed_decoded_inst_t));
    printf("xed_inst_t                 %12d\n", (int)sizeof(xed_inst_t));    
    printf("xed_operand_t              %12d\n", (int)sizeof(xed_operand_t));
    printf("xed_iform_info_t           %12d\n", (int)sizeof(xed_iform_info_t));    
    return 0;
    (void) argc; (void) argv; //pacify compiler
    (void) x;
}
