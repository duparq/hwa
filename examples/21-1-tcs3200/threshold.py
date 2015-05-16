#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))
import premain
import application
import time
from utils import s2hex


class Application(application.Application):
    def __init__(self):
        application.Application.__init__(self)
        self.options = self.parser.parse_args()

    def run(self):
        self.connect( self.sync_5_1 )

        #  Want a '\n' reply to '\n'
        #
        to=time.time()+1.0
        while time.time() < to:
            self.tx('\n')
            time.sleep(0.1)
            if self.rx(1)=='\n':
                break
        if time.time() >= to:
            die("Did not process '\n' correctly.\n")

        #  Send command a wait for reply (the device may be busy processing the
        #  samples)
        #
        self.tx('l')
        r=""
        to=time.time()+0.1
        while time.time() < to:
            c = self.rx(1)
            if c == '\n':
                threshold = int(r[0:4], 16)
                cout("Threshold=%4d\n" % threshold)
                break
            r += c

        self.com.close()


if __name__ == "__main__":
    try:
        Application().run()
    except KeyboardInterrupt:
        cout("\n")
