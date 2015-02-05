#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2015-02-04 15:36:18 -*-

import sys

def get_args():
    import argparse
    parser = argparse.ArgumentParser()

    #  Serial tty arguments
    #
    parser.add_argument('-t', '--tty', help="serial tty to use (/dev/ttyUSB0)",
                        default='/dev/ttyUSB0')
    parser.add_argument('-b', '--bps', help="baudrate (115200)", type=int,
                        default='115200')
    parser.add_argument('-w', '--wires', help="how many wires for rx/tx "
                        "(0 for autodetection)",
                        type=int, choices=range(3), default=0)
    parser.add_argument('-r', '--reset', help="signal used to reset the "
                        "device", choices=['dtr','rts'], default='dtr')
    parser.add_argument('-d', '--reset-length', help="how long reset is "
                        "asserted in seconds (0.01)", metavar='SECONDS',
                        type=float, default='0.01')

    #  Target options
    #
    parser.add_argument('-m', '--mcu', help="target device if target checking"
                        " is wanted")
    parser.add_argument('--carspy', help="Carspy target number",
                        type=int, choices=range(31), default=-1)

    #  Actions
    #
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-q', '--reset-and-quit', help="only reset the device",
                       action='store_true')
    group.add_argument('-c', '--crc', help="only compute the CRC of given file",
                       action='store_true')
    group.add_argument('--read-flash', help="read flash memory", action='store_true')
    group.add_argument('--burn-flash', help="burn flash memory", action='store_true')
    group.add_argument('--clear-flash', help="clear flash memory", action='store_true')
    group.add_argument('--verify-flash', help="verify flash memory", action='store_true')

    group.add_argument('--read-eeprom', help="read eeprom memory", action='store_true')
    group.add_argument('--burn-eeprom', help="burn eeprom memory", action='store_true')
    group.add_argument('--clear-eeprom', help="clear eeprom memory", action='store_true')
    group.add_argument('--verify-eeprom', help="verify eeprom memory", action='store_true')

    parser.add_argument('--cachename', help="name of cache file")
    parser.add_argument('--full', help="read full content (Diabolo code included)",
                        action='store_true')
    parser.add_argument('--hexdump', help="hexdump content", action='store_true')

    #  Files
    #
    parser.add_argument('filename', nargs='?')

    return parser.parse_args()


if __name__ == "__main__":
    # from premain import *
    import premain
    import com
    options = get_args()

    print options

    com = com.Com(options.tty, options.bps, options.wires)

    print com
