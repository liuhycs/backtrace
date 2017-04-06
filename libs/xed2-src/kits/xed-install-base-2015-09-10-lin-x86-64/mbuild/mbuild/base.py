#!/usr/bin/env python
# -*- python -*-
# Mark Charney 
#BEGIN_LEGAL
#Copyright 2004-2015 Intel Corporation. Use of this code is subject to
#the terms and conditions of the What If Pre-Release License Agreement,
#which is available here:
#https://software.intel.com/en-us/articles/what-if-pre-release-license-agreement
#or refer to the LICENSE.txt file.
#END_LEGAL
"""Base functionality: messages, verbosity, python version checking"""

import os
import sys
import traceback

_mbuild_verbose_level = 1
def verbose(level=0):
  """Return True if the configured message level supplied is >= the
  level arguement
  @param level: int
  @param level: the verbosity level at which this function should return True
  
  @rtype: bool
  @return: True iff the level argument is >= current verbosity level
  """
  global _mbuild_verbose_level
  if _mbuild_verbose_level >= level:
    return True
  return False
def set_verbosity(v):
  """Set the global verbosity level. 0=quiet, 99=very very noisy"""
  global _mbuild_verbose_level
  _mbuild_verbose_level = v

def get_verbosity():
  """Return the global verbosity level. 0=quiet, 99=very very noisy"""
  global _mbuild_verbose_level
  return _mbuild_verbose_level

def bracket(s,m=''):
  """add a bracket around s and append m.
  @rtype: string
  @return: a bracketed string s and a suffixed message m
  """
  return '[%s] %s' % (s,str(m))

def error_msg(s,t):
  """Emit '[s] t' to stderr with a newline"""
  sys.stderr.write(bracket(s,t) + "\n")

def msg(s, pad=''):
  """Emit s to stdout with a newline"""
  sys.stdout.write(pad)
  sys.stdout.write(s)
  sys.stdout.write("\n")
  
def msgn(s, pad=''):
  """Emit s to stdout without a newline"""
  sys.stdout.write(pad)  
  sys.stdout.write(s)

def msgb(s,t='',pad=''):
  """a bracketed  string s  sent to stdout, followed by a string t"""
  msg(bracket(s,t), pad=pad)

def vmsgb(v,s,t='',pad=''):
  """If verbosity v is sufficient, emit a bracketed string s sent to
  stdout, followed by a string t"""
  if verbose(v):
    msg(bracket(s,t),pad=pad)

def cond_die(v, cmd, msg):
  """Conditionally die, if v is not zero. Print the msg and the cmd.
  @type v: int
  @param v: we die if v is not 0

  @type cmd: string
  @param cmd: a command to print

  @type msg: string
  @param msg: a message to print before the command
  """
  if v != 0:
    s = msg + "\n  [CMD] " + cmd
    die(s)

def die(m,s=''):
  """Emit an error message m (and optionally s) and exit with a return value 1"""
  msgb("MBUILD ERROR", "%s %s\n\n" % (m,s) )
  traceback.print_exc(file=sys.stdout)
  sys.exit(1)
def warn(m):
  """Emit an warning message"""
  msgb("MBUILD WARNING", m)

def get_python_version():
  """Return the python version as an integer
  @rtype: int
  @return: major * 100000 + minor + 1000 + fixlevel
  """
  tuple = sys.version_info
  major = int(tuple[0])
  minor = int(tuple[1])
  fix  = int(tuple[2])
  vnum = major *100000 + minor * 1000 + fix
  return vnum

def get_python_version_tuple():
  """Return the python version as a tuple (major,minor,fixlevel)
  @rtype: tuple
  @return: (major,minor,fixlevel)
  """
  
  tuple = sys.version_info
  major = int(tuple[0])
  minor = int(tuple[1])
  fix  = int(tuple[2])
  return (major,minor,fix)

def check_python_version(maj,minor,fix=0):
  """Return true if the current python version at least the one
  specified by the arguments.
  @rtype: bool
  @return: True/False
  """
  t = get_python_version_tuple()
  if t[0] > maj:
    return True
  if t[0] == maj and t[1] > minor:
    return True
  if t[0] == maj and t[1] == minor and t[2] >= fix:
    return True
  return False
  


try:
  if check_python_version(2,4) == False:
    die("MBUILD error: Need Python version 2.4 or later.")
except:
  die("MBUILD error: Need Python version 2.4 or later.")

import platform # requires python 2.3
_on_mac = False
_on_native_windows = False
_on_windows = False # cygwin or native windows
_on_cygwin = False
_on_linux  = False
_on_freebsd = False
_operating_system_name = platform.system()
if _operating_system_name.find('CYGWIN') != -1:
   _on_cygwin = True
   _on_windows = True
elif  _operating_system_name == 'Microsoft' or  _operating_system_name == 'Windows':
   _on_native_windows = True
   _on_windows = True
elif _operating_system_name == 'Linux':
   _on_linux = True
elif _operating_system_name == 'FreeBSD':
   _on_freebsd = True
elif _operating_system_name == 'Darwin':
   _on_mac = True
else:
   die("Could not detect operating system type: " + _operating_system_name)

def on_native_windows():
  """
  @rtype: bool
  @return: True iff on native windows win32/win64
  """
  global _on_native_windows
  return _on_native_windows

def on_windows(): 
  """
  @rtype: bool
  @return: True iff on  windows cygwin/win32/win64
  """
  global _on_windows
  return _on_windows
