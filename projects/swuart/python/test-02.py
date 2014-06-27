#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-05-01 11:58:45 -*-

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


def test(com, i, j):
    dec=2
    dev=1.0/2**(dec+2)
    for x in [1.0-dev, 1.0, 1.0+dev]:
    # for x in [1.0]:
        num=i*j
        den=i*x
        com.tx(struct.pack('<HHB', num, den, dec))
        rs=com.rx(10)
        if len(rs)==4:
            r=struct.unpack('<HH', rs)
            q=r[0]
            t=r[1]-12
            cout("%d %d %d/%d -> %d (%s) (%d cycles)\n" % (i, j, num, den, q, s2hex(rs[:2]), t))
        else:
            cout("%d/%d -> ERROR (%s)\n" % (num, den, s2hex(rs)))


def test2(com, dt1, n):
    dec=2
    dtn = dt1 * n
    # for num in [dtn-dt1/4-dt1/8, dtn-dt1/4+dt1/8, dtn, dtn+dt1/4-dt1/8, dtn+dt1/4+dt1/8]:
    # for num in [dtn-dt1/4-dt1/8-1, dtn-dt1/4-dt1/8+1,
    #             dtn-dt1/4+dt1/8-1, dtn-dt1/4+dt1/8+1,
    #             dtn,
    #             dtn+dt1/4-dt1/8-1, dtn+dt1/4-dt1/8+1,
    #             dtn+dt1/4+dt1/8-1, dtn+dt1/4+dt1/8+1]:
    for num in [dtn-dt1/4-1, dtn-dt1/4, dtn-dt1/4+1,
                dtn,
                dtn+dt1/4-1, dtn+dt1/4, dtn+dt1/4+1]:
        com.tx(struct.pack('<HHB', num, dt1, dec))
        rs=com.rx(10)
        if len(rs)==4:
            r=struct.unpack('<HH', rs)
            q=r[0]
            t=r[1]-12
            qf=1.0*q/(2**dec)
            cout("%d %d %d -> %d (%s) (%d cycles) %f\n" % (n, dt1, num, q, s2hex(rs[:2]), t, qf))
        else:
            cout("%d %d %d -> ERROR (%s)\n" % (n, dt1, num, s2hex(rs)))


def main():
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEVICE", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com speed (default 115200)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=115200, dest="combps", 
                      help="set com speed (default 115200)")
    (options, args) = parser.parse_args()    

    options.combps = 10000
    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    # com.setTimeout(12*10.0/options.combps)
    com.setTimeout(2*12*10.0/options.combps)
    com.reset_device()
    time.sleep(0.3)

    # Synchro
    #
    com.tx('A')
    #com.tx('A')
    if com.rx(1) != '\x55':
        cerr("SYNC ERROR.\n")
        sys.exit(1)

    r=com.rx(4)
    if len(r) != 4:
        cerr("DT ERROR.\n")
        sys.exit(1)

    dtn, dt0 = struct.unpack('<HH', r)
    cout("dtn=%d, dt0=%d\n" % (dtn, dt0))

    test2(com, 160, 5)
    test2(com, 1600, 10)

    # for i in [160, 1600]:
    #     for j in [5, 6, 7, 8, 9, 10]:
    #         test2(com, i, j)

main()
