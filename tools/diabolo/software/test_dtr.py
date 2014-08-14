#!/usr/bin/env python
# -*- coding: utf-8 -*-


from com import Com
import serial
import time
import os

def x_run():
    com = Com( "/dev/ttyUSB0", 115200 )
    com.onewire = True
    #com.dsrdtr = False

    try:
        com.open()
    except ValueError:
        cerr(_("Value error\n"))
    if not com.is_open():
        cerr(_("Can not open serial port\n"))
        return None

def y_run():
    com = serial.Serial()
    com.port = "/dev/ttyUSB0"
    com.baudrate = 115200
    com.timeout = 1
    com.setDTR(False)
    com.open()

def run():
    # ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)
    # ser.setDTR(False)
    # time.sleep(0.5)

    fd = os.open("/dev/ttyUSB0", os.O_RDWR|os.O_NOCTTY|os.O_NONBLOCK)


if __name__ == "__main__":
    # from premain import *
    import premain
    try:
        run()
    except KeyboardInterrupt:
        cout("\n")
