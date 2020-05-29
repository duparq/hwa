#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import builtins
import premain
from utils import hexdump
import time

enable_trace()

import link


#  Create command line arguments parser
#
import argparse
parser = argparse.ArgumentParser()

#  Arguments about serial port
#
link.add_arguments(parser)

args = parser.parse_args()

try:
    serial = link.get(args)
except link.serial.SerialException as e:
    die(str(e))


#  Release the RESET signal and detect how many wires are used (this will make
#  Diabolo start the application as soon as it has computed the CRC).
#
serial.set_RESET(0)
time.sleep(0.01)
serial.set_RESET(1)
serial.detect_wires(b'?')
cout("Wires: %d\n" % serial.wires)

#  Give Diabolo enough time to compute the CRC before it starts the application.
#
time.sleep(0.5)


#  Application
#
def run():
    import struct
    t0 = 0
    tick=time.time()
    resyncs = 0
    n = 20
    while True:
        if n==20:
            n=0
            resyncs += 1
            serial.tx(b'x') # Force resync
            try:
                cout("Resync #%d: " % resyncs)
                serial.sync_51()
            except:
                die(_("Could not get the application prompt.\n"))
            continue
        serial.tx(b'A')
        r = serial.rx(5)
        if len(r) != 5 or r[-1]!=ord('$'):
            cout("ERROR: %d bytes received: %s\n" % (len(r), r.hex()))
            serial.rx(10)
        else:
            n+=1
            dt0 = int.from_bytes(r[0:2], byteorder='little')
            dtn = int.from_bytes(r[2:4], byteorder='little')
            cout("dt0=%d dtn=%d\n" % (dt0, dtn) )

        tick += 0.05
        if tick > time.time():
            time.sleep( tick - time.time() )


try:
    run()
except KeyboardInterrupt:
    cout("\n")
    serial.close()
