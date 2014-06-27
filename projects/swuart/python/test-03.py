#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-08-21 19:35:30 -*-

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


def test3(com, dt1, n):
    for num in range(dt1*4-dt1/2, dt1*11+dt1/2, 10):
        com.tx(struct.pack('<HH', num, dt1))
        rs=com.rx(10)
        if len(rs)==2:
            q=struct.unpack('<H', rs)[0]
            cout("%d %d -> %d\n" % (dt1, num, q))
        else:
            cout("%d %d -> ERROR (%s)\n" % (dt1, num, s2hex(rs)))


def main():
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEVICE", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com device (default /dev/ttyUSB0)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=100000, dest="combps", 
                      help="set com speed (default 100000)")
    (options, args) = parser.parse_args()    

    options.combps = 57600
    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    com.setTimeout(12*10.0/options.combps)

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

    r = com.rx(2)
    dtn = struct.unpack('<H', r)[0]
    cout("%d tries, dtn=%d\n" % (tries, dtn))

    print "OK"

    test3(com, 160, 5)


main()
