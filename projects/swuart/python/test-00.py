#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-04-22 12:02:39 -*-

# FT232RL :	 1 TXD
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
                      dest="comdev", 
                      help="set com speed (default 115200)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=115200, dest="combps", 
                      help="set com speed (default 115200)")
    (options, args) = parser.parse_args()    

    #options.combps = 10000
    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    com.setTimeout(0.01)
    com.reset_device()
    time.sleep(0.3)

    com.tx('A')
    com.tx('A')

    # while True:
    #     com.tx('A')
    #     r=com.rx(100)
    #     if r=='\x55':
    #         break
    #     time.sleep(0.01)

    n = 0
    while True:
        com.tx(struct.pack('<H', n))
        com.rx(100)
        n+=1
        time.sleep(0.01)

    # n=0
    # while True:
    #     s=''
    #     for i in range(500):
    #         s+=chr(n)
    #     com.tx(s)
    #     n+=1
    #     if n == 256:
    #         n=0
    #     time.sleep(0.1)

    n=0
    while True:
        # com.reset_device()
        # time.sleep(0.3)
        # com.flushInput()
        # com.flushOutput()

        # com.brk()
        # com.tx('\xFF')
        # com.tx('A')
        # com.brk()
        # com.tx('\xFF')

        # r = com.rx(100)

        # if len(r)==2:
        #     print struct.unpack('<H', r)[0]
        # elif r:
        #     print "R: ", s2hex(r)

        # com.tx('\xFF')
        # r = com.rx(100)
        # if r: print "R: ", s2hex(r)

        # com.brk()
        # r = com.rx(100)
        # if r: print "R: ", s2hex(r)

        # com.tx('\xFF')
        # r = com.rx(100)
        # if r: print "R: ", s2hex(r)

        # com.tx('\xAA')
        # r = com.rx(100)
        # if r: print "R: ", s2hex(r)

        while com.rx(10)!='\x55':
            com.tx('\x55')

        com.tx(struct.pack('<H', 0x0000))
        print "NUM: ", s2hex(com.rx(2))

        # com.tx(struct.pack('<H', 0x0101))
        # print "DEN: ", s2hex(com.rx(2))

        # print "X: ", s2hex(com.rx(2))

        print

        # 1011 1010

        # r = com.rx(100)
        # if len(r)==2:
        #     print struct.unpack('<H', r)[0]
        # elif r:
        #     print "R: ", s2hex(r)

        n+=1
        # print n
        time.sleep(0.5)

    while True:
        pass

    while True:
        com.tx('X')
        r = com.rx(1)
        print r
        time.sleep(1)

    sys.exit(0)

    time.sleep(0.1)
    for c in 'Coucou':
        com.tx(c)
        print com.rx(1)
    # time.sleep(0.5)
    # com.tx("Coucou")
    # print com.rx()


main()
