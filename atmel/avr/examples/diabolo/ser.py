#!/usr/bin/env python3

import sys
import os.path

sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import premain
import builtins

import link
import time


class App:
  def run(self,options):
    self.options = options
    self.link = link.Link(self.options)

    #  Reset the device connected to the serial interface
    #
    self.link.set_TXD(0)
    self.link.set_RESET(0)

    if self.options.reset_length:
      time.sleep(self.options.reset_length)

    self.link.set_RESET(1)
    self.link.set_TXD(0)

    #  Just reset the device and quit?
    #
    if self.options.reset_and_exit:
        return

    if self.options.keep_txd_low == 0:
      cout("WARNING: target will probably not remain in Diabolo if TXD is not "
           "maintained low long enough!\n")
    else:
      time.sleep(self.options.keep_txd_low)

    self.link.set_TXD(1)
    time.sleep(0.5)

    #  This is the best moment for detecting how many wires are used for the
    #  serial communication since the target device is supposed to be
    #  waiting in Diabolo for the synchronization.
    #
    #  It is safe to send data on the serial line now even if the RESET
    #  signal is used to drive the power supply (sending data while the
    #  device is not powered could cause troubles).
    #
    self.link.detect_wires(b'?')
    cout(_("Tty wires: %d\n") % self.link.wires)

    #  We can now send synchronization sequences
    #
    if not self.link.sync():
      die(_("Synchronization failed.\n"))

    # self.link.set_TXD(0)
    # self.link.set_RESET(0)
    # self.link.detect_wires(b'?')
    # time.sleep(0.01)
    # self.link.set_RESET(1)
    # time.sleep(0.8)
    # self.link.set_TXD(1)

    # if not self.link.sync():
    #   die(_("Synchronization failed.\n"))


    while True:
      self.link.tx(b'p')
      time.sleep(0.1)
      cout('.')
      flushout()
      

#  Create command line arguments parser
#
import argparse
parser = argparse.ArgumentParser()

#  Arguments about serial port
#
link.add_arguments(parser)

#  Target options
#
parser.add_argument('-m', '--mcu', help="target device")

#  Actions
#
group = parser.add_mutually_exclusive_group()
group.add_argument('-x', '--reset-and-exit',
                   help="only reset the device, do not try to connect.",
                   action='store_true')
group.add_argument('--stat', help="size and CRC of the application",
                   action='store_true')
group.add_argument('-c', '--crc', help="CRC of the application",
                   action='store_true')
group.add_argument('-s', '--size', help="size of the application",
                   action='store_true')
group.add_argument('--crc32', help="CRC32 of file", action='store_true')
group.add_argument('--fwcrc', help="CRC of Diabolo firmware", action='store_true')
group.add_argument('--read-flash', help="read flash memory", action='store_true')
group.add_argument('--burn-flash', help="burn flash memory", action='store_true')
group.add_argument('--clear-flash', help="clear flash memory", action='store_true')
group.add_argument('--verify-flash', help="verify flash memory", action='store_true')

group.add_argument('--read-eeprom', help="read eeprom memory", action='store_true')
group.add_argument('--burn-eeprom', help="burn eeprom memory", action='store_true')
group.add_argument('--clear-eeprom', help="clear eeprom memory", action='store_true')
group.add_argument('--verify-eeprom', help="verify eeprom memory", action='store_true')

#  Options
#
parser.add_argument('--cache', help="name of cache file")
parser.add_argument('--full', help="read full content (Diabolo code included)",
                    action='store_true')
parser.add_argument('--hexdump', help="hexdump content", action='store_true')

parser.add_argument('-q', '--quiet', help="do not write on standard output "
                    "if not necessary", action='store_true')
parser.add_argument('--diag', help="display diagnostic values",
                    action='store_true')
parser.add_argument('--debug', help="print debugging messages",
                    action='store_true')
parser.add_argument('--show-fuses', help="show fuse values", action='store_true')
parser.add_argument('--decode-fuses', help="decode fuse values", action='store_true')


#  Files
#
parser.add_argument('filename', nargs='?')

args = parser.parse_args()

try:
    App().run(args)
except KeyboardInterrupt:
    cout('\n')
    pass
