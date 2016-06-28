#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))
sys.path.insert(2,os.path.normpath(sys.path[1]+"/pyserial-3.0"))

import __builtin__
import premain
from utils import s2hex, hexdump
import time

import link

#  Command line arguments
#
import argparse
parser = argparse.ArgumentParser()

#  Add arguments about serial port
#
link.add_arguments(parser)

args = parser.parse_args()

#  Open serial interface
#
serial = link.get( args )

#  Release the RESET signal and detect how many wires are used (this will make
#  Diabolo start the application as soon as it has computed the CRC).
#
serial.set_RESET(1)
serial.detect_wires('?')
cout("Wires: %d\n" % serial.wires)
time.sleep(0.5)
serial.sync()

#  Application
#
try:
    import struct
    t0 = 0
    tick=time.time()
    n = 0
    while True:
        if n==20:
            n=0
            serial.tx('x') # Force resync
            try:
                serial.sync()
            except:
                die(_("Could not get the application prompt.\n"))
            continue
        serial.tx('A')
        r = serial.rx(5)
        if len(r) != 5 or r[-1]!='$':
            cout("ERROR: %d bytes received: %s\n" % (len(r), s2hex(r)))
            serial.rx(10)
        else:
            n+=1
            dtn, dt0 = struct.unpack('<HH', r[0:4])
            cout("dt0=%d dtn=%d\n" % (dt0, dtn) )

        tick += 0.05
        if tick > time.time():
            time.sleep( tick - time.time() )

except KeyboardInterrupt:
    pass

serial.close()
