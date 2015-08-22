#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import __builtin__
import premain
from utils import s2hex, hexdump
import time

#  Command line arguments
#
import argparse
parser = argparse.ArgumentParser()

import xserial
xserial.add_arguments(parser)

args = parser.parse_args()

#  Extract the sync method to use from the source
#
# import subprocess
# subprocess.call(["make", "BOARD=attiny84", "build/sync"])

# f=open("build/sync", "r")
# s = f.read()
# f.close()

# s = s.replace('\n','').split("=")
# if s[0]!="SYNC":
#     die(_("synchronization method not found.\n"))
# if s[1]=="sync_5_1":
#     args.sync=="5+1"
# elif s[1]=="sync_10_1":
#     args.sync=="10+1"
# else:
#     die(_("unknown synchronization method \"%s\"."))

#  Open serial interface
#
serial = xserial.get_serial(args)
serial.reset_device()
serial.detect_wires()
time.sleep(0.2)	# Leave Diabolo anough time to check the CRC and start the application
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
            serial.tx('x')
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
