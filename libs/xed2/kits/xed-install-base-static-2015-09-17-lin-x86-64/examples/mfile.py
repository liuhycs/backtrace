#!/usr/bin/env python
# -*- python -*-
#BEGIN_LEGAL
#Copyright 2004-2015 Intel Corporation. Use of this code is subject to
#the terms and conditions of the What If Pre-Release License Agreement,
#which is available here:
#https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
#or refer to the LICENSE.txt file.
#END_LEGAL

import sys
import os

def _find_dir(d):
    dir = os.getcwd()
    last = ''
    while dir != last:
        target_dir = os.path.join(dir,d)
        if os.path.exists(target_dir):
            return target_dir
        last = dir
        (dir,tail) = os.path.split(dir)
    return None

def _fatal(m):
    sys.stderr.write("\n\nXED build error: %s\n\n" % (m) )
    sys.exit(1)

def _try_mbuild_import():
    try:
        import mbuild
        return True
    except:
        return False
    
def _find_add_import(dir):
    p = _find_dir(dir)
    if p and os.path.exists(p):
        sys.path = [p] + sys.path
        return
    _fatal("Could not find {} directory".format(d))
    
def _find_mbuild_import():
    if _try_mbuild_import():
        return
    _find_add_import('mbuild')
    
def _find_scripts():
    _find_add_import('scripts')
    
def _find_common():
    p = os.path.dirname(_find_dir('xed_build_common.py'))
    if p and os.path.exists(p):
        sys.path = [p] + sys.path
        return
    _fatal("Could not find xed_build_common.py")

def setup():
    if sys.version_info[0] >= 3:
        _fatal("Python version 3.x not supported.")
    if sys.version_info[0] == 2 and sys.version_info[1] < 7:        
        _fatal("Need python version 2.7 or later.")
    _find_mbuild_import()
    # when building in the source tree the xed_build_common.py file is
    # in the parent directory of the examples. When building in the
    # kit that file is in the example source directory.
    _find_common() 
    _find_scripts()  # for elf_sizes

    
def work():
    import xed_build_common
    import xed_examples_mbuild
    try:
        retval = xed_examples_mbuild.execute()
    except Exception, e:
        xed_build_common.handle_exception_and_die(e)
    return retval
    
if __name__ == "__main__":
    setup()
    retval = work()
    sys.exit(retval)
 
