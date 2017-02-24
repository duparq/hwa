#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../../python"))

import premain
from utils import s2hex, hexdump
import xserial
import time


parser = xserial.ArgumentParser()
options = parser.parse_args()
options.bps = 9600
serial = xserial.get_serial(options)
serial.reset_device()
serial.detect_wires()

while True:
    cout(serial.rx(1))
    flushout()
