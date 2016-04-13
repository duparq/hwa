
# -*- coding: utf-8 -*- 

import sys
import __builtin__
import os


#  Globals
#
__builtin__.__dict__['cout'] = sys.stdout.write
__builtin__.__dict__['flushout'] = sys.stdout.flush
__builtin__.__dict__['cerr'] = sys.stderr.write
__builtin__.__dict__['dbg'] = id


#  Platform adaptations
#
import time
import platform
system = platform.system()
if system == "Linux":
#    __builtin__.__dict__['_'] = lambda x: x.encode('utf8')
    __builtin__.__dict__['_'] = lambda x: x
    __builtin__.__dict__['timer'] = time.time
elif system == "Windows":
    __builtin__.__dict__['_'] = lambda x: x.encode('cp850')
    __builtin__.__dict__['timer'] = time.clock
else:
#    print "Unknown platform %s\n" % system
    __builtin__.__dict__['_'] = lambda x: x
    __builtin__.__dict__['timer'] = time.clock


#  Trace function
#
tracetime = timer()

#  Disable trace
#
x_trace = False

def enable_trace():
    global x_trace
    x_trace = True

def disable_trace():
    global x_trace
    x_trace = False

def trace(arg=""):
    global x_trace
    if not x_trace:
        return
    import inspect
    caller = inspect.stack()[1]
    global tracetime
    t = timer()
    dt = max(0, round((t-tracetime)*1000))
    tracetime = t
    cout("%08dms %s() %s:%d: %s\n" % \
         (dt, caller[3], os.path.basename(caller[1]),
          caller[2], arg))
__builtin__.__dict__['trace'] = trace
__builtin__.__dict__['enable_trace'] = enable_trace
__builtin__.__dict__['disable_trace'] = disable_trace


#  Print error message and exit with error code 1
#
def die(s):
    sys.stderr.write("\nFatal: "+s+'\n')
    sys.exit(1)

__builtin__.__dict__['die'] = die
