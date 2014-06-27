#!/usr/bin/env python

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
                      help="set com speed (default 230400)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=230400, dest="combps", 
                      help="set com speed (default 115200)")
    (options, args) = parser.parse_args()    

    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    com.setTimeout(20*10.0/options.combps)
    com.reset_device()
    time.sleep(0.3)

    com.reset_device()

    while True:
        cout( com.rx(200) )
        flushout()

main()
