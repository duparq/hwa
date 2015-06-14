#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))
import application

def auto_int(x):
    return int(x,0)


class Application(application.Application):
    def __init__(self):
        application.Application.__init__(self)
        #
        #  Commands
        #
        parser = self.parser
        parser.add_argument('command', help='read or write', choices=['read','write'])
        parser.add_argument('address', help='address to read or write', type=auto_int)
        parser.add_argument('value', help='how many byte to read, or value to write',
                            type=auto_int)
        self.options = parser.parse_args()


    def run(self):
        self.connect( self.sync_5_1 )
        if self.options.command == 'write':
            #
            #  Program eeprom
            #
            self.eewrite( self.options.address, self.options.value )
        else:
            #
            #  Read eeprom
            #
            self.eeread( self.options.address, self.options.value )
        self.com.close()


    def eewrite(self, address, value):
        al = (address & 0x00FF) >> 0
        ah = (address & 0xFF00) >> 8
        self.tx('E'+chr(al)+chr(ah)+chr(value)+'\n')
        r = self.rx(1)
        cout("Write 0x%02X at 0x%04X: %s (%s)\n" % (address, value, r, s2hex(r)))


    def eeread(self, address, n):
        cout("Reading %d bytes of EEPROM starting at 0x%04X: " % (n,address))
        mem = ""
        a = address
        while n:
            al = (a & 0x00FF) >> 0
            ah = (a & 0xFF00) >> 8
            l = min(n, 64)
            cout('.')
            flushout()
            self.tx('e'+chr(al)+chr(ah)+chr(l)+'\n')
            r = self.rx(l+1)
            if len(r) == l+1 and r[-1]=='$':
                mem += r[:-1]
                n -= l
                a += l
            else:
                cout(" Error reading %d bytes of EEPROM starting at 0x%04X.\n" % (l,a))
                break
        cout('\n')
        cout(hexdump(address, mem)+'\n')


if __name__ == "__main__":
    import __builtin__

    import premain
    from utils import s2hex, hexdump
    import time

    try:
        Application().run()
    except KeyboardInterrupt:
        cout("\n")
