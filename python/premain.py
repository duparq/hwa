
# -*- coding: utf-8 -*- 

import sys
import builtins
import os


#  Globals
#
builtins.__dict__['cout'] = sys.stdout.write
builtins.__dict__['flushout'] = sys.stdout.flush
builtins.__dict__['cerr'] = sys.stderr.write
builtins.__dict__['dbg'] = id


#  Platform adaptations
#
import time
import platform
system = platform.system()
if system == "Linux":
#    __builtin__.__dict__['_'] = lambda x: x.encode('utf8')
    builtins.__dict__['_'] = lambda x: x
    builtins.__dict__['timer'] = time.time
elif system == "Windows":
    builtins.__dict__['_'] = lambda x: x.encode('cp850')
    builtins.__dict__['timer'] = time.clock
else:
#    print "Unknown platform %s\n" % system
    builtins.__dict__['_'] = lambda x: x
    builtins.__dict__['timer'] = time.clock


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
builtins.__dict__['trace'] = trace
builtins.__dict__['enable_trace'] = enable_trace
builtins.__dict__['disable_trace'] = disable_trace


#  Print error message and exit with error code 1
#
def die(s):
    sys.stderr.write("\nFatal: "+s+'\n')
    sys.exit(1)

builtins.__dict__['die'] = die
