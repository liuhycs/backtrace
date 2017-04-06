# -*- python -*-
# Mark Charney 
#BEGIN_LEGAL
#Copyright 2004-2015 Intel Corporation. Use of this code is subject to
#the terms and conditions of the What If Pre-Release License Agreement,
#which is available here:
#https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
#or refer to the LICENSE.txt file.
#END_LEGAL

"""Function for header include scanning"""

import re
import os
import sys
import base
import util

class mbuild_header_record_t:
    """Stores information about headers that we find"""
    def __init__(self, fn, found=True):
        self.file_name = fn
        self.system = False
        self.found = found
    def __str__(self):
        s = ''
        s = self.file_name
        if self.system:
            s += ' system'
        if not self.found:
            s += ' not-found'
        return s

def mbuild_compute_path(hname, search_path):
    """Return the full path of the header hname, if found and None
    otherwise. Search the path in order and see if we find the file"""
    for p in search_path:
        tname = util.join(p,hname)
        tname = os.path.realpath(tname)
        #mbuild_base.msgb("TESTING", tname)
        if os.path.exists(tname):
            return tname
    return None

# FIXME: ignoring system headers for now.            
mbuild_include_pattern = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"(?P<hdr>[^"]+)"')
mbuild_nasm_include_pattern = re.compile(r'^[ \t]*%include[ \t]+"(?P<hdr>[^"]+)"')

def mbuild_scan(fn, search_path):
    """Given a file name fn, and a list of search paths, scan for
    headers in fn and return a list of mbuild_header_record_t's. The
    header records indicate if the file is a system include based on
    <> symbols or if the file was missing. If the file cannot be
    found, we assume it is in the assumed_directory."""
    global mbuild_include_pattern
    global mbuild_nasm_include_pattern
    
    all_names = []

    if not os.path.exists(fn):
        return all_names

    source_path = os.path.dirname(fn)
    if source_path == '':
        source_path = '.'
    aug_search_path = [source_path] + search_path
        
    for line in file(fn).readlines():
        #print line
        hgroup = mbuild_include_pattern.match(line)
        if not hgroup:
            hgroup = mbuild_nasm_include_pattern.match(line)
        if hgroup:
            hname =  hgroup.group('hdr')
            #print hname
            full_name = mbuild_compute_path(hname, aug_search_path)
            if full_name:
                hr = mbuild_header_record_t(full_name)
            else:
                hr = mbuild_header_record_t(hname, found=False)
            all_names.append(hr)
    return all_names



def _test_scan():
    paths = ["/home/mjcharne/proj/learn/" ]
    all_headers = mbuild_scan("/home/mjcharne/proj/learn/foo.cpp", paths)
    for hr in all_headers:
        print hr

if __name__ == '__main__':
    _test_scan()

