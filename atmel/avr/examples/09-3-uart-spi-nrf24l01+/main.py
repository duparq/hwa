#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../../python"))

import premain
from utils import s2hex, hexdump
import xserial
import time


#  Description of nRF24L01+ registers
#    ('NAME', command/address code, number of bytes to read)
#
nrf_registers = [ ("CONFIG",	 '\x00', 1),
		  ("EN_AA",	 '\x01', 1),
		  ("EN_RX_ADDR", '\x02', 1),
		  ("SETUP_AW",	 '\x03', 1),
		  ("SETUP_RETR", '\x04', 1),
		  ("RF_CH",	 '\x05', 1),
		  ("RF_SETUP",	 '\x06', 1),
		  ("STATUS",	 '\x07', 1),
		  ("RX_ADDR_P0", '\x0A', 5),
		  ("RX_ADDR_P1", '\x0B', 5),
		  ("DYNPD",	 '\x1C', 1),
		  ("FEATURE",	 '\x1D', 1) ]


#  Parse command line, open the communication
#
import argparse
parser = argparse.ArgumentParser()
xserial.add_arguments(parser)
options = parser.parse_args()
if options.wires == 0:
    options.wires = 2
serial = xserial.get_serial(options) # resets the device


prompt = serial.rx(1)
if prompt == '$':
    #
    #  Get all registers content
    #
    for r in nrf_registers:
        rn, stx, nrx = r
        ntx = len(stx)
        ra = ord(stx[0])
        cout("Register %-10s: 0x%02X = " % (rn,ra))
        flushout()
        serial.tx('='+chr(ntx)+chr(nrx)+stx)
        r = serial.rx(nrx+1)
        if r:
            if r.endswith(prompt):
                cout( s2hex(r[:-1])+'\n' )
            else:
                die(" received `%s`\n" % s2hex(r))
        else:
            cout("no response.\n")
else:
    cout("Unexpected prompt: %s\n" % s2hex(prompt))

serial.close()
