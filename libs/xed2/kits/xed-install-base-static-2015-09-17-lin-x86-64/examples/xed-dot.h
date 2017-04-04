/*BEGIN_LEGAL 
Copyright 2004-2015 Intel Corporation. Use of this code is subject to
the terms and conditions of the What If Pre-Release License Agreement,
which is available here:
https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
or refer to the LICENSE.txt file.
END_LEGAL */
#if !defined(_XED_DOT_H_)
# define _XED_DOT_H_

#include "xed-interface.h"
#include <stdio.h>

typedef struct xed_dot_node_s {
    char* name;
    struct xed_dot_node_s* next;
} xed_dot_node_t;

typedef enum {
    XED_DOT_EDGE_SOLID,
    XED_DOT_EDGE_DASHED,
    XED_DOT_EDGE_DOTTED
} xed_dot_edge_style_t;


typedef struct xed_dot_edge_s {
    xed_dot_node_t* src;
    xed_dot_node_t* dst;
    xed_dot_edge_style_t style;
    struct xed_dot_edge_s* next;
} xed_dot_edge_t;

typedef struct {
    xed_dot_edge_t* edges;
    xed_dot_node_t* nodes;
} xed_dot_graph_t;


xed_dot_graph_t* xed_dot_graph(void);
void xed_dot_graph_deallocate(xed_dot_graph_t* gg);

xed_dot_node_t* xed_dot_node(xed_dot_graph_t* g,
                             char const* const name);

void xed_dot_edge(xed_dot_graph_t* g,
                  xed_dot_node_t* src,
                  xed_dot_node_t* dst,
                  xed_dot_edge_style_t style);

void xed_dot_dump(FILE* f, xed_dot_graph_t* g);
#endif
