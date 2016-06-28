#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
import __builtin__

sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))
sys.path.insert(2,os.path.normpath(sys.path[1]+"/pyserial-3.0"))

import premain
from utils import s2hex, hexdump
import time

import link

#  Create command line arguments parser
#
import argparse
parser = argparse.ArgumentParser()

#  Add arguments about serial port
#
link.add_arguments(parser)

args = parser.parse_args()

serial = link.get( args )

#  Release the RESET signal
#
serial.set_RESET(1)

try:
    col = 0
    while True:
        c = serial.rx(1)
        if c:
            cout(c)
            flushout()
            col += 1
            if col == 64:
                col = 0
                cout('\n')
except KeyboardInterrupt:
    cout("\n")
except Exception, e:
    cerr(str(e)+'\n')
