#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import __builtin__
import premain
from utils import s2hex, hexdump
import time

import platform
system = platform.system()

import xserial

parser = xserial.ArgumentParser()

args = parser.parse_args()

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
    dt = 100.0/serial.baudrate
    cout("tick=%f\n" % dt)

    import struct
    t0 = 0
    tick=time.time()

    n = 0
    col = 0
    byte = 0
    while True:
        if n==128:
            n=0
            # serial.rx_until_idle(10)
            serial.tx10low()
            serial.sync()
            if serial.lastchar != '$':
                if serial.lastchar:
                    cout(_(" SYNC BAD REPLY (0x%02X) " % ord(serial.lastchar) ))
                else:
                    cout(_(" SYNC BAD REPLY () " ))
                if system == "Linux":
                    cout(_(" WARNING: CH340 driver is buggy under Linux and "\
                           "the UART never resynchronizes.\n"))
            continue
        serial.tx(chr(byte))
        n+=1
        r = serial.rx(1)
        if len(r) != 1 or r[-1]!=chr(byte):
            serial.rx(10)
            cout('x')
        else:
            cout('.')
        flushout()
        if byte % 64 == 63:
            cout('\n%.3f: ' % tick)
        byte = (byte+1)%256
        tick += dt
        dtime = max(0.001, tick-time.time())
        time.sleep( dtime )
    serial.close()

except KeyboardInterrupt:
    pass
