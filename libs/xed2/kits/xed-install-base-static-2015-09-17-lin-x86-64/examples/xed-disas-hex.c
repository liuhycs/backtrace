/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */

// to avoid empty compilation unit on no-decoder compiles
#include "xed-interface.h" 

#if defined(XED_DECODER)
#include "xed-portability.h"
#include "xed-examples-util.h"
#include "xed-disas-hex.h"

#include <stdlib.h>
#include <assert.h>



static FILE*
open_file(char const* const  path, char const* const mode)
{
    FILE* f;
#if defined(XED_MSVC8_OR_LATER) && !defined(PIN_CRT)
    errno_t err;
    err = fopen_s(&f,path, mode);
#else
    int err=0;
    f = fopen(path, mode);
    err = (f==0);
#endif
    if (err) {
       fprintf(stderr, "Could not open file: %s\n", path);
       exit(1);
    }
    return f;
}

static int read_byte(FILE* f, xed_uint8_t* b) {
    int  r;
    unsigned int i;
#if defined(_WIN32) && !defined(PIN_CRT)
    r = fscanf_s(f,"%2x", &i);
#else
    r = fscanf(f,"%2x", &i);
#endif
    if (b)
        *b = (xed_uint8_t)i;
    return r;
}

void
xed_disas_hex(xed_disas_info_t* fi)
{
    xed_uint8_t* region = 0;
    unsigned int len = 0;
    unsigned int i = 0;
    xed_uint8_t b = 0;
    FILE* f = 0;

    // read file once to get length
    f = open_file(fi->input_file_name, "r");
    while (read_byte(f,0) != -1)
    {
        len++;
    }
    fclose(f);

    region = (xed_uint8_t*) malloc(len);
    if (region == 0) {
        fprintf(stderr,"ERROR: Could not malloc region for hex file\n");
        exit(1);
    }

    // read file again to read the bytes
    f = open_file(fi->input_file_name, "r");
    while (read_byte(f,&b) != -1)
    {
       assert(i < len);
       region[i++] = b;
    }
    fclose(f);
    assert(i==len);

    fi->s =  (unsigned char*)region;
    fi->a = (unsigned char*)region;
    fi->q = (unsigned char*)(region) + len; // end of region
    fi->runtime_vaddr = 0;
    fi->runtime_vaddr_disas_start = 0;
    fi->runtime_vaddr_disas_end = 0;
    fi->symfn = 0;
    fi->caller_symbol_data = 0;
    fi->line_number_info_fn = 0;
    xed_disas_test(fi);
    if (fi->xml_format == 0)
        xed_print_decode_stats(fi);
}
 
#endif
