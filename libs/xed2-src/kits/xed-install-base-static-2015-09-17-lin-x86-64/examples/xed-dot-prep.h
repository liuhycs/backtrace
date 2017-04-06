/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */

#if !defined(_XED_DOT_PREP_H_)
# define _XED_DOT_PREP_H_
#include "xed-interface.h"
#include "xed-dot.h"

typedef struct {
    xed_syntax_enum_t syntax;
    xed_dot_graph_t* g;
    
    // node that is last writer of the register
    xed_dot_node_t* xed_reg_to_node[XED_REG_LAST];
    
    xed_dot_node_t* start;
} xed_dot_graph_supp_t;

xed_dot_graph_supp_t* xed_dot_graph_supp_create(
    xed_syntax_enum_t arg_syntax);

void xed_dot_graph_supp_deallocate(
    xed_dot_graph_supp_t* gg);

void xed_dot_graph_add_instruction(
    xed_dot_graph_supp_t* gg,
    xed_decoded_inst_t* xedd,
    xed_uint64_t runtime_instr_addr,
    void* caller_data,
    xed_disassembly_callback_fn_t disas_symbol_cb);

void xed_dot_graph_dump(
    FILE* f,
    xed_dot_graph_supp_t* gg);

#endif
