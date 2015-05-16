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
        self.parser.add_argument('tmax',   help="region number", type=int)
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

        #  The device may be busy processing the samples
        #
        self.tx('L')
        to=time.time()+1.0
        while self.rx(1)!=' ' and time.time() < to:
            time.sleep(0.001)
        if time.time() > to:
            die("Timeout for 'L' command.\n")

        frame = "%04X" % (self.options.tmax)
        cout("%s: (%d bytes)" % (frame, len(frame)))
        flushout()

        self.tx(frame+'\n')
        r=""
        to=time.time()+1.0
        while time.time()<to:
            r=self.rx(1)
            if r=='\n' or r=='!':
                break

        if r=='\n':
            cout(" success!\n")
        elif r=='!':
            cout(" error.\n")
        elif r:
            cout(" bad reply (%s).\n" % s2hex(r))
        else:
            cout(" no reply.\n")

        self.com.close()


if __name__ == "__main__":
    try:
        Application().run()
    except KeyboardInterrupt:
        cout("\n")
