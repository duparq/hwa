#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-08-20 09:57:02 -*-

# FT232RL :	 1 TXD
#	         3 RTS (-> RESET)
# 		 5 RXD
# 		 4 VCCIO
# 		 7 GND
# 		17 3V3out
# 		18 GND
# 		20 VCC

import struct
import serial
import time
from utils import *
import termios
from com import *
from premain import *
from optparse import OptionParser


def main():
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEVICE", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com speed (default 115200)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=115200, dest="combps", 
                      help="set com speed (default 115200)")
    (options, args) = parser.parse_args()    

    options.combps = 57600
    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    com.setTimeout(12*10.0/options.combps)
    com.reset_device()
    time.sleep(0.3)


    # Reset
    #
    com.reset_device()
    time.sleep(0.3)

    # Synchro
    #
    chars=['\0','\xFF']
    nchar=0
    tries=0
    while True:
        tries+=1
        com.tx(chars[nchar])
        nchar+=1
        if nchar==len(chars):
            nchar=0
        r = com.rx(1)
        if r=='\x55':
            break
        elif r:
            cout(" %s\r" % s2hex(r))
            flushout()
        time.sleep(.2)

    r=com.rx(4)
    if len(r) != 4:
        cerr("Synchro answer error.\n")
        sys.exit(1)

    dtn, dt0 = struct.unpack('<HH', r)
    cout("Synchro: %d tries, dt0=%d, dtn=%d\n" % (tries, dt0, dtn))

    n = 0
    nbad = 0
    t = time.time()
    while True:
        n+=1
        ts=struct.pack('<H', n&65535)
        com.tx(ts)
        if 1:
            rs=com.rx(2)
        else:
            rs=''
            while True:
                c=com.rx(1)
                if not c:
                    break
                rs+=c
        r=None
        if len(rs)==2:
            r=struct.unpack('<H', rs)[0]
        if r!=(n&65535):
            nbad+=1
            cout("[BAD %d/%d] %s -> %s\n" % (nbad, n, s2hex(ts), s2hex(rs)))
        else:
            cout(" %d\r" % n)
            flushout()
        com.setTimeout(12*10.0/options.combps)
        t+=20*10.0/options.combps
        while time.time()<t:
            pass
        # time.sleep(0.005)

main()
