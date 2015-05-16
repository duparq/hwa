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
        #
        #  Commands
        #
        self.parser.add_argument('region',   help="region number", type=int)
        self.parser.add_argument('radius',   help="square radius", type=int)
        self.parser.add_argument('red',      help="red contribution", type=int)
        self.parser.add_argument('green',    help="green contribution", type=int)
        self.parser.add_argument('blue',     help="blue contribution", type=int)
        self.parser.add_argument('decision', help="decision", type=int)
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

        if self.options.region > 15:
            die("Region must be in 0..15.\n")

        #  The device may be busy processing the samples
        #
        self.tx('R')
        to=time.time()+1.0
        while self.rx(1)!=' ' and time.time() < to:
            time.sleep(0.01)

        frame = "%02X%02X%02X%02X%02X%02X" \
                % (self.options.region, self.options.radius, self.options.red,
                   self.options.green, self.options.blue, self.options.decision)
        cout("%s: (%d bytes)" % (frame, len(frame)))
        flushout()

        self.tx(frame+'\n')

        to=time.time()+1.0
        r=""
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
