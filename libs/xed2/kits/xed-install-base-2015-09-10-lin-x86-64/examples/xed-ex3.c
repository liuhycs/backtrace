/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file xed-ex3.c
/// Encoder example

#include "xed-interface.h"
#include "xed-examples-util.h"
#include "xed-enc-lang.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv);


void
usage(char* progname)
{
    fprintf(stderr,"Usage: %s [-16|-32|-64] [-s16|-s32] encode-string\n",
            progname);
    exit(1);
}

ascii_encode_request_t
parse_args(unsigned int argc, char** argv)
{
    char const* c = 0;
    unsigned int i = 1;
    ascii_encode_request_t r;
    if (argc == 1)
        usage(argv[0]);
    r.dstate.mmode = XED_MACHINE_MODE_LEGACY_32;
    r.dstate.stack_addr_width = XED_ADDRESS_WIDTH_32b;
    
    for( ; i< argc; i++)
        if (strcmp(argv[i],"-16")==0) 
            r.dstate.mmode = XED_MACHINE_MODE_LEGACY_16;
        else if (strcmp(argv[i],"-32")==0) 
            r.dstate.mmode = XED_MACHINE_MODE_LEGACY_32;
        else if (strcmp("-64", argv[i]) == 0) {
            r.dstate.mmode = XED_MACHINE_MODE_LONG_64;
        }
        else if (strcmp("-32", argv[i]) == 0)
            r.dstate.mmode = XED_MACHINE_MODE_LEGACY_32;
        else if (strcmp("-16", argv[i]) == 0)
            r.dstate.mmode = XED_MACHINE_MODE_LEGACY_16;
        else if (strcmp(argv[i],"-s32")==0) 
            r.dstate.stack_addr_width = XED_ADDRESS_WIDTH_32b;
        else if (strcmp(argv[i],"-s16")==0) 
            r.dstate.stack_addr_width = XED_ADDRESS_WIDTH_16b;
        else
            break;

    if (i == argc)
        usage(argv[0]);
    
    c = xed_strdup(argv[i++]);
    for( ;i<argc;i++) {
        c = xedex_append_string(c, " ");
        c = xedex_append_string(c, argv[i]);
    }
    r.command = c;
    return r;
}

int main(int argc, char** argv) {
#define XED_EX3_BUFLEN 5000
    char buf[XED_EX3_BUFLEN];
    unsigned int ilen = XED_MAX_INSTRUCTION_BYTES;
    unsigned int olen;
    xed_uint8_t array[XED_MAX_INSTRUCTION_BYTES];
    ascii_encode_request_t areq;
    xed_encoder_request_t req;
    xed_error_enum_t xed_error;
    xed_bool_t encode_okay;

    xed_tables_init();
    areq = parse_args(argc,argv);
    req = parse_encode_request(areq);
    
    printf("Encode request:\n");
    xed_encode_request_print(&req, buf, XED_EX3_BUFLEN);
    printf("%s\n",buf);

    xed_error =  xed_encode(&req, array, ilen, &olen);
    encode_okay = ( xed_error == XED_ERROR_NONE);
    if (!encode_okay)     {
        printf("Could not encode\n");
        return 1;
    }
    xed_print_hex_line(buf, array, olen, XED_EX3_BUFLEN);
    printf("Encodable! %s\n",buf);
    return 0;
}
