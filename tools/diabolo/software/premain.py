#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2015-02-14 17:04:08 -*-

import sys
import platform
import __builtin__
import os


# Fonction de traçage
#
import inspect
import time
tracetime = time.time()
msgtime = time.time()


def trace(arg=""):
    caller = inspect.stack()[1]
    global tracetime
    t = time.time()
    dt = round((t-tracetime)*1000)
    tracetime = t
    s = "%08dms %s() %s:%d: %s\n" % (dt, caller[3], os.path.basename(caller[1]),
                                     caller[2], arg)
    cout(_(s))


#  Print error message and exit with error code 1
#
def die(s):
    sys.stderr.write('Fatal: '+s+'\n')
    #sys.stdin.readline()
    sys.exit(1)


def msg(*args):
    global msgtime
    t = time.time()
    dt = round((t-msgtime)*1000)
    msgtime = t
    sys.stdout.write(TTY_BLUE+'%08dms: '%dt+' '.join(args)+TTY_NORMAL+'\n')
    # sys.stdout.flush()


# Définitions globales
#
__builtin__.__dict__['cout'] = sys.stdout.write
__builtin__.__dict__['flushout'] = sys.stdout.flush
__builtin__.__dict__['cerr'] = sys.stderr.write
__builtin__.__dict__['dbg'] = id
__builtin__.__dict__['trace'] = trace
__builtin__.__dict__['die'] = die
__builtin__.__dict__['msg'] = msg


# Adaptations à la plateforme
#
system = platform.system()
if system == "Linux":
    TTY_NORMAL	= "[0;39m"
    TTY_CRE	= "\13[K"
    TTY_RED	= "[1;31m"
    TTY_GREEN	= "[1;32m"
    TTY_YELLOW	= "[1;33m"
    TTY_BLUE	= "[1;34m"
    TTY_MAGENTA	= "[1;35m"
    TTY_CYAN	= "[1;36m"
    TTY_WHITE	= "[1;37m"
    __builtin__.__dict__['_'] = lambda x: x.encode('utf8')
elif system == "Windows":
    TTY_NORMAL	= ""
    TTY_CRE	= ""
    TTY_RED	= ""
    TTY_GREEN	= ""
    TTY_YELLOW	= ""
    TTY_BLUE	= ""
    TTY_MAGENTA	= ""
    TTY_CYAN	= ""
    TTY_WHITE	= ""
    __builtin__.__dict__['_'] = lambda x: x.encode('cp850')
else:
    print "Unknown platform %s\n" % system
    __builtin__.__dict__['_'] = lambda x: x

try:
    base = __file__
    basepath = os.path.abspath(os.path.dirname(base))
    sys.path.append(os.path.join(basepath, 'modules'))
except:
    basepath = os.path.abspath(os.path.dirname(sys.executable))
