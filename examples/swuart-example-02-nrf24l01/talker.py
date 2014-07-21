#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2014-07-21 11:34:32 -*-

from com import Com
from utils import s2hex
import time

from device import Device


def parse_options():
    from optparse import OptionParser
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEV", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com device (default /dev/ttyUSB0)")
    parser.add_option("-b", "--bps", metavar="BPS", type="int",
                      default=115200, dest="combps", 
                      help="set com speed (default 115200)")
    parser.add_option("-1", "--one-wire", action="store_true",
                      default=True, dest="onewire",
                      help="RX/TX on the same communication wire")
    parser.add_option("-2", "--two-wires", action="store_false",
                      default=True, dest="onewire",
                      help="RX/TX on separate communication wires")
    (options, args) = parser.parse_args()
    if len(args) == 1:
        options.flash_file = args[0]
    return options


#  Open the communication device
#    Return the com device if OK, None otherwise
#
def open_com(options):
    com = Com( options.comdev, options.combps )
    try:
        com.open()
    except ValueError:
        cerr(_("Value error\n"))
    if not com.is_open():
        cerr(_("Can not open serial port\n"))
        return None

    com.onewire = options.onewire
    return com


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


def run():
    options = parse_options()

    #  Open the communication interface
    #
    com = open_com(options)
    if not com:
        cout(_("Could not open %s\n" % options.comdev))
        return
    cout(_("Interface: %s (%d bps)\n" % (options.comdev, options.combps)))

    #  Connect
    #
    device = Device(com)
    if not device.connect():
        cerr(_("Could not connect.\n"))
        return
    cout(_("Connected to device \n"))

    #  Get all registers content
    #
    for r in nrf_registers:

        if not device.get_prompt():
            cerr(_("Could not get prompt: %s.\n" % device.error))
            break

        rn, stx, nrx = r[0], r[1], r[2]
        ntx = len(stx)
        ra = ord(stx[0])
        cout("Register %-10s: 0x%02X: " % (rn,ra))
        flushout()
        device.tx('='+chr(ntx)+chr(nrx)+stx)
        r = device.rx(nrx+1)
        if r:
            if r.endswith('#'):
                cout( s2hex(r[:-1])+'\n' )
            else:
                cerr(" received `%s`\n" % r)
        else:
            cerr("no response.\n")
            break

    com.close()
    cout(_("%d resumes\n" % device.nresumes))


if __name__ == "__main__":
    from premain import *
    try:
        run()
    except KeyboardInterrupt:
        cout("\n")
