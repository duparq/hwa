#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
import __builtin__

sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import premain
from utils import s2hex, hexdump
import time

import xserial

serial = xserial.get_serial( xserial.ArgumentParser().parse_args() )
serial.reset_device()

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
