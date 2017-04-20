#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import premain
from utils import s2hex, hexdump
import xserial
import time

import operator
import pickle
from utils import s2hex


def region(string):
    print "Region: ", string
    return string


class Application():
    def __init__(self):
        self.data = {}

        parser = xserial.ArgumentParser()
        subparsers = parser.add_subparsers(help='sub-command help', dest="command")

        #  Stat command
        #
        parser_stat = subparsers.add_parser('stat', help='display the status of the device')

        #  Sample command
        #
        parser_sample = subparsers.add_parser('sample', help='sample data and store them '\
                                              'to a file if a name is provided')
        parser_sample.add_argument('--threshold',
                                   help="maximum period of the clear channel to "
                                   "validate a sample",
                                   type=int, default="65536")
        parser_sample.add_argument('-o', '--output-file',
                                   help="store data to file" )
        # parser_sample.add_argument('--gauges', help="show sampled values with graphical gauges",
        #                            action='store_true')

        #  Set-threshold command
        #
        parser_threshold = subparsers.add_parser('set-threshold', help='set_threshold help')
        parser_threshold.add_argument('threshold', help="threshold value", type=int)

        #  Set-region command
        #
        parser_region = subparsers.add_parser('set-region',
                                                 help='set a region in the device')
        parser_region.add_argument('region', help="region number", type=int)
        parser_region.add_argument('radius', help="region radius (tolerance)", type=int)
        parser_region.add_argument('pred', help="level of red", type=int)
        parser_region.add_argument('pgreen', help="level of green", type=int)
        parser_region.add_argument('pblue', help="level of blue", type=int)
        parser_region.add_argument('result', help="result the device must produce", type=int)

        self.options = parser.parse_args()

        self.serial = xserial.get_serial(self.options)
        self.serial.reset_device()
        self.serial.detect_wires()
        time.sleep(0.2)  # Give Diabolo enough time to compute the CRC of the application
        self.serial.sync()
        self.prompt = self.serial.lastchar


    def get_regions(self):
        #
        #  Send command and wait for reply (the device may be busy processing
        #  the samples)
        #
        self.serial.tx('r')
        r=""
        to=time.time()+0.1
        while time.time() < to:
            c = self.serial.rx(1)
            if c == '\n':
                rn     = int(r[ 0: 2], 16)
                radius = int(r[ 2: 4], 16)
                red    = int(r[ 4: 6], 16)
                green  = int(r[ 6: 8], 16)
                blue   = int(r[ 8:10], 16)
                result = int(r[10:12], 16)
                cout("Region %2d: radius=%-3d red=%-3d green=%-3d blue=%-3d result=%d\n"
                     % (rn, radius, red, green, blue, result ))
                r=""
                to=time.time()+0.1
                continue
            r += c


    def set_region(self):
        if self.options.region > 15:
            die("Region must be in 0..15.\n")
        #
        #  Send first command byte and wait for reply (the device may be busy
        #  processing the samples)
        #
        self.serial.tx('R')
        to=time.time()+1.0
        while self.serial.rx(1)!=' ' and time.time() < to:
            time.sleep(0.01)

        frame = "%02X%02X%02X%02X%02X%02X" \
                % (self.options.region, self.options.radius, self.options.pred,
                   self.options.pgreen, self.options.pblue, self.options.result)
        cout("%s: (%d bytes)" % (frame, len(frame)))
        flushout()

        self.serial.tx(frame+'\n')

        to=time.time()+1.0
        r=""
        while time.time()<to:
            r=self.serial.rx(1)
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


    def get_threshold(self):
        #
        #  Send command and wait for reply (the device may be busy processing
        #  the samples)
        #
        self.serial.tx('l')
        r=""
        to=time.time()+0.1
        while time.time() < to:
            c = self.serial.rx(1)
            if c == '\n':
                threshold = int(r[0:4], 16)
                cout("Threshold=%4d\n" % threshold)
                break
            r += c


    def set_threshold(self):
        #
        #  Send first command byte and wait for reply (the device may be busy
        #  processing the samples)
        #
        self.serial.tx('L')
        to=time.time()+1.0
        while self.serial.rx(1)!=' ' and time.time() < to:
            time.sleep(0.001)
        if time.time() > to:
            die("Timeout for 'L' command.\n")

        frame = "%04X" % (self.options.threshold)
        cout("%s: (%d bytes)" % (frame, len(frame)))
        flushout()

        self.serial.tx(frame+'\n')
        r=""
        to=time.time()+1.0
        while time.time()<to:
            r=self.serial.rx(1)
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


    def sample(self):
        x_nosignal = False
        while True:
            #
            # Ask for a sample
            #
            self.serial.tx('s')
            r=""
            while True:
                c = self.serial.rx(1)
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
                # if fclear > self.options.fmin:
                if tclear < self.options.threshold:
                    key = "%02x%02x%02x" % (xred, xgreen, xblue)
                    if not self.data.has_key(key):
                        self.data[key]=1
                        cout(" *** NEW ***\n")
                    else:
                        self.data[key] += 1
                        cout(" %d\n" % self.data[key])
                else:
                    cout(" -\r")
                    flushout()

            elif r==".":
                if not x_nosignal:
                    x_nosignal = True
                    cout("No signal.\n")
            else:
                cout("Bad reply.\n")


    def run(self):
        try:
            #self.connect( self.sync_5_1 )

            if self.options.command=='stat':
                self.get_threshold()
                self.get_regions()
            elif self.options.command=='sample':
                self.sample()
            elif self.options.command=='set-region':
                self.set_region()
            elif self.options.command=='set-threshold':
                self.set_threshold()
            else:
                die("Unknown command.\n")
        except KeyboardInterrupt:
            cout("\n")
            if len(self.data):
                cout("%d samples collected:\n" % len(self.data))
                sorted_data = sorted( self.data.items(), key=operator.itemgetter(1) )
                col = 0
                for k,v in sorted_data:
                    cout("%4d:%s " % (v,k))
                    col += 12
                    if col == 72:
                        col = 0
                        cout("\n")
                cout("\n")
                if self.options.output_file:
                    f=open(self.options.output_file, "w")
                    pickle.dump(self.data, f)
                    f.close()
                    cout("%d samples stored into %s.\n"
                         % (len(self.data), self.options.output_file))
                else:
                    cout("No filename provided to store data.\n")
            else:
                cout("No sample collected.\n")
            print self.options
        finally:
            self.serial.close()


if __name__ == "__main__":
    Application().run()
