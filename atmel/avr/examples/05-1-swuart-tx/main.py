#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import builtins
import premain
from utils import hexdump
import time

enable_trace()

import link


#  Create command line arguments parser
#
import argparse
parser = argparse.ArgumentParser()

#  Arguments about serial port
#
link.add_arguments(parser)

args = parser.parse_args()


class App():
    def __init__(self, args):
        self.args = args

        try:
            self.link = link.get(args)
        except link.serial.SerialException as e:
            die(str(e))


        # self.link.set_RESET(0)
        # time.sleep(0.01)
        self.link.set_RESET(1)

        col = 0
        while True:
            c = self.link.rx(1)
            if c:
                cout(chr(c[0]))
                flushout()
                col += 1
                if col == 64:
                    col = 0
                    cout('\n')


try:
    App(args).run()
except KeyboardInterrupt:
    cout("\n")
