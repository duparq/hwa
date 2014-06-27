#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2014-06-15 22:42:03 -*-

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
                      default=19200, dest="combps", 
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

    #  Get prompt
    #
    if not device.get_prompt():
        cerr(_("Could not get prompt: %s.\n" % device.error))
        return
    cout(_("Prompt\n"))

    for i in range(20):
        device.tx(chr(0x30+i%10))
        time.sleep(0.1)
        cout(device.rx(10)+'\n')

    com.close()
    # cout(_("%d commands, %d fails, %d resumes, %d resyncs\n" % 
    #        (device.ncmds, device.ncmdfails, device.nresumes, device.nresyncs)))


if __name__ == "__main__":
    from premain import *
    try:
        run()
    except KeyboardInterrupt:
        cout("\n")
