/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */

#if !defined(_XED_SYMBOL_TABLE_H_)
#define _XED_SYMBOL_TABLE_H_

#include "xed-interface.h"
#include "xed-examples-util.h"
#include "avltree.h"
#include <stdlib.h>

typedef struct  {
    avl_tree_t atree;
} xed_local_symbol_table_t;

void xed_local_symbol_table_init(xed_local_symbol_table_t* p);

typedef struct  {
    xed_local_symbol_table_t gtab;
    /* section number maps to a local symbol table */
    avl_tree_t avl_lmap;
    /* the symbol table for the current section */
    xed_local_symbol_table_t* curtab;

} xed_symbol_table_t;

void xed_symbol_table_init(xed_symbol_table_t* p);

xed_local_symbol_table_t* xst_get_local_map(xed_symbol_table_t* p,
                                            xed_uint32_t section);

xed_local_symbol_table_t* xst_make_local_map(xed_symbol_table_t* p,
                                             xed_uint32_t section);
    
void xst_set_current_table(xed_symbol_table_t* p,
                           xed_uint32_t section);

void xst_add_local_symbol(xed_symbol_table_t* p,
                          xed_uint64_t addr, char* name,
                          xed_uint32_t section);

void xst_add_global_symbol(xed_symbol_table_t* p,
                           xed_uint64_t addr, char* name);

////////////////////////////////////////////////////////////////

char* get_symbol(xed_uint64_t a, void* symbol_table);

int xed_disassembly_callback_function(
    xed_uint64_t address,
    char* symbol_buffer,
    xed_uint32_t buffer_length,
    xed_uint64_t* offset,
    void* caller_data);
#endif
