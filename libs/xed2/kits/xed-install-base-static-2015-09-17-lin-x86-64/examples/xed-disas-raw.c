/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
/// @file disas-raw.c

#include "xed-interface.h" 
#if defined(XED_DECODER)
#include "xed-portability.h"
#include "xed-examples-util.h"
#include "xed-disas-raw.h"

void xed_disas_raw(xed_disas_info_t* fi)
{
    void* region = 0;
    unsigned int len = 0;
    xed_map_region(fi->input_file_name, &region, &len);
 
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
