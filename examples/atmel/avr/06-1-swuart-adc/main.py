#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))
import application


class Application(application.Application):
    def __init__(self):
        application.Application.__init__(self)
        self.options = self.parser.parse_args()

    def run(self):
        self.connect( self.sync_5_1 )

        #  Display what the device sends
        #
        adc = 0
        while True:
            r = self.rx(2)
            if len(r)==2:
                x = ord(r[0])+256*ord(r[1])
                adc = adc - (adc+2)/4 + x # low-pass filter
                cout("\r%04d " % ((adc+2)/4))
            flushout()

        self.com.close()



if __name__ == "__main__":
    import __builtin__

    import premain
    from utils import s2hex, hexdump
    import time

    try:
        Application().run()
    except KeyboardInterrupt:
        cout("\n")
#    except Exception, e:
#        cerr(str(e)+'\n')
