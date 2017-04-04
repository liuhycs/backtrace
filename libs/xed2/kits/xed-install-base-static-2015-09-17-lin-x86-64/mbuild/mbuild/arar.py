#!/usr/bin/env python
# -*- python -*-
# Repackage a bunch of static libs as one big static library.
#BEGIN_LEGAL
#Copyright 2004-2015 Intel Corporation. Use of this code is subject to
#the terms and conditions of the What If Pre-Release License Agreement,
#which is available here:
#https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
#or refer to the LICENSE.txt file.
#END_LEGAL
import os
import sys
import shutil
import re

class arar_error(Exception):
    def __init__(self, value):
        self.value = value
    def _str__(self):
        return repr(self.value)

def repack(files, ar='ar', target='liball.a', verbose=False):
    """For linux only. Repackage the list of files using ar as the
    archiver program. The input files list can contain .a or .o
    files. The output library name is supplied by the target keyword
    argument. This will raise an exception arar_error in the event of
    a problem, setting the exception value field with an explanation."""
    import glob
    pid= os.getpid()
    #error=os.system(ar + " --version")
    tdir = 'tmp.arar.%d' % (pid)
    if os.path.exists(tdir):
        raise arar_error('Conflict with existing temporary directory: %s' % \
                         (tdir))
    os.mkdir(tdir)
    # work in a temporary subdirectory
    os.chdir(tdir)
    doto = []
    for arg in files:
        if re.search(r'[.]o$', arg):
            if arg[0] == '/':
                doto.append(arg)
            else:
                doto.append(os.path.join('..',arg))
            continue
        if arg[0] == '/':
            cmd = "%s x %s" % (ar,arg)
        else:
            cmd = "%s x ../%s" % (ar,arg)
        if verbose:
            print "EXTRACTING %s" % (cmd)
        error= os.system(cmd)
        if error:
            raise arar_error('Extract failed for command %s' % (cmd))
    files = glob.glob('*.o') + doto
    local_target = os.path.basename(target)
    cmd = "%s rcv %s %s" % (ar, local_target, " ".join(files))
    if verbose:
        print "RECOMBINING %s" % (cmd)
    error=os.system(cmd)
    if error:
        raise arar_error('Recombine failed')

    os.chdir('..')
    os.rename(os.path.join(tdir,local_target), target)
    if verbose:
        print "CREATED %s" % (target)
    shutil.rmtree(tdir)


