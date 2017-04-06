#!/usr/bin/env python
# FILE: dfs.py
# AUTHOR: Mark Charney <mark.charney@intel.com>
#BEGIN_LEGAL
#Copyright 2004-2015 Intel Corporation. Use of this code is subject to
#the terms and conditions of the What If Pre-Release License Agreement,
#which is available here:
#https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
#or refer to the LICENSE.txt file.
#END_LEGAL

"""This file provides a node_t type and a dfs() routine that prints out
cycles found in a graph represented as a list of node_t objects.
"""

_dfs_verbose = False

class node_t(object):
    def __init__(self,name='no-name-for-node'):
        self.name = name
        self.afters = []
        self.befores = []
        self.zero()

        # The colors are:
        #    0 = white (unvisited),
        #    1=grey (discovered, visiting),
        #    2=black (finalized)
        self.color = 0
                
        self.discover = 0
        self.finalize = 0
        self.predecessor = None
    def zero(self):
        self.color = 0
    def add_successor(self, s):
        self.afters.append(s)
        s.befores.append(self)
    def add_ancestor(self, s):
        self.befores.append(s)
        s.afters.append(self)
    def __str__(self):
        s = []
        s.append("TARGET: %s\n\t" % self.name)
        s.append("discovered %d  finalized %d\n\t" % (self.discover, self.finalize))
        s.extend(map(lambda(x): "\t\n%s" % x.name, self.afters))
        return ''.join(s)



def _print_cycle(last_visit, grey_loop_closer):
    pad = ''
    p = last_visit
    while 1:
        print pad, p.name
        if p == grey_loop_closer:
            break
        p = p.predecessor
        pad += '    '

def _visit(n):
    global _dfs_time
    n.color = 1
    n.discover = _dfs_time
    if _dfs_verbose:
        print "visiting %s" % str(n)
    _dfs_time += 1
    retval = False
    for a in n.afters:
        if a.color == 0:
            a.predecessor = n
            retval |= _visit(a)
        elif a.color == 1:
            # a back-edge
            print "cycle"
            _print_cycle(n,a)
            retval = True
    n.color = 2
    n.finalize = _dfs_time
    _dfs_time += 1
    return retval
            
def dfs(nodes):
    """Depth first search a list of node_t objects. Print out cycles.
    @rtype: bool
    @return: True if cycles were detected.
    """
    global _dfs_time
    _dfs_time = 0
    for t in nodes:
        t.zero()
    cycle = False
    for n in nodes:
        if n.color == 0:
            cycle |= _visit(n)
    return cycle

#######################################################

# stuff for a strongly connected components algorithm -- currently
# unused.

def _node_cmp(aa,bb):
    return aa.finalize.__cmp__(bb.finalize)

def _visit_transpose(n):
    global _dfs_time
    n.color = 1
    if _dfs_verbose:
        print "visiting %s" % str(n)
    for a in n.befores:
        if a.color == 0:
            _visit_transpose(a)
    n.color = 2


def dfs_transpose(nodes):
    global _dfs_time
    _dfs_time = 0
    for t in nodes:
        t.zero()
    nodes.sort(cmp=_node_cmp)
    for n in nodes:
        if n.color == 0:
            _visit_transpose(n)
            if _dfs_verbose:
                print "===="

####################################################
            
def _test_dfs():
    node1 = node_t('1')
    node2 = node_t('2')
    node3 = node_t('3')
    node4 = node_t('4')
    node1.add_successor(node2)
    node1.add_successor(node3)
    node3.add_successor(node4)
    node4.add_successor(node1)

    nodes = [ node1, node2, node3, node4 ]
    cycle = dfs(nodes)
    if cycle:
        print "CYCLE DETECTED"
    #print "VISIT TRANSPOSE"
    #dfs_transpose(nodes)

    # print "NODES\n", "\n".join(map(str,nodes))

if __name__ == '__main__':
    _test_dfs()
