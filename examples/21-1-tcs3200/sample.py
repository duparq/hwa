#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))
import premain
import application
import pickle
import operator
import math
import time
from utils import s2hex


class Application(application.Application):
    def __init__(self):
        application.Application.__init__(self)
        #
        #  Commands
        #
        self.parser.add_argument('-f', '--fmin',
                                 help="required minimum frequency of 'clear'"
                                 " channel to record a sample.",
                                 type=int, default="0")
        self.parser.add_argument('datafile', help='output file')
        self.options = self.parser.parse_args()

    def run(self):
        self.connect( self.sync_5_1 )
        x_nosignal = False
        try:
            data = {}
            while True:
                #
                # Ask for a sample
                #
                self.tx('s')
                r=""
                while True:
                    c = self.rx(1)
                    if c == '\n':
                        break
                    r += c

                # Process the reply
                #
                if len(r)==24:
                    x_nosignal = False
                    #
                    # Parse periods
                    #
                    tclear = int(r[ 2: 4]+r[ 0: 2], 16)
                    tred   = int(r[ 6: 8]+r[ 4: 6], 16)
                    tgreen = int(r[10:12]+r[ 8:10], 16)
                    tblue  = int(r[14:16]+r[12:14], 16)

                    pred   = int(r[16:18], 16)
                    pgreen = int(r[18:20], 16)
                    pblue  = int(r[20:22], 16)

                    region = int(r[22:24], 16)

                    #
                    # Compute frequency for 'clear' channel
                    # This is used for sampling threshold
                    #
                    fclear = int( 4e6 / tclear )
                    #
                    # Compute relative intensities in [0..255]
                    #
                    tclear256 = 256 * tclear
                    xred   = (tclear256 + tred/2)   / tred
                    xgreen = (tclear256 + tgreen/2) / tgreen
                    xblue  = (tclear256 + tblue/2)  / tblue
                    #
                    # Display relative intensities
                    #
                    cout("%s " % r)
                    cout(" %04x:%04x:%04x:%04x" % (tclear, tred, tgreen, tblue))
                    cout(" %02x-%02x-%02x" % (pred, pgreen, pblue))
                    cout(": %5d %02x-%02x-%02x:" % (fclear, xred, xgreen, xblue))
                    #
                    # Record new data
                    #
                    if fclear > self.options.fmin:
                        key = "%02x%02x%02x" % (xred, xgreen, xblue)
                        if not data.has_key(key):
                            data[key]=0
                            cout(" new")
                        data[key] += 1
                        cout(" %d\n" % data[key])
                    else:
                        cout(" -\r")
                        flushout()

                elif r==".":
                    if not x_nosignal:
                        x_nosignal = True
                        cout("No signal.\n")
                else:
                    cout("Bad reply.\n")

        except KeyboardInterrupt:
            cout("\n")
            if len(data):
                cout("%d samples collected:\n" % len(data))
                sorted_data = sorted( data.items(), key=operator.itemgetter(1) )
                col = 0
                for k,v in sorted_data:
                    cout("%4d:%s " % (v,k))
                    col += 12
                    if col == 72:
                        col = 0
                        cout("\n")
                cout("\n")
                if self.options.datafile:
                    f=open(self.options.datafile, "w")
                    pickle.dump(data, f)
                    f.close()
                    cout("%d samples stored into %s.\n"
                         % (len(data), self.options.datafile))
                else:
                    cout("No filename provided to store data.\n")
            else:
                cout("No sample collected.\n")
        finally:
            self.com.close()


if __name__ == "__main__":
    Application().run()
