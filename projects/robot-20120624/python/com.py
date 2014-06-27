#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-04-22 11:47:37 -*-

# FT232RL :	 1 TXD
# 		 5 RXD
# 		 4 VCCIO
# 		 7 GND
# 		17 3V3out
# 		18 GND
# 		20 VCC

import serial
import time
from utils import *
import termios


#  Renvoie la liste les périphériques disponibles
#    Ne touche pas à avoid.
#
def listports(avoid=None):
    ports=[]
    names=[]
    for n in range(8):
        d = '/dev/ttyUSB%d' % n
        names.append(d)
    for n in range(8):
        d = serial.device(n)
        names.append(d)
    for name in names:
        try:
            if name != avoid:
                com=serial.Serial(name)
                com.open()
                com.close()
            ports.append(name)
                #trace(name+" OK")
        except:
                #trace(name+" FAIL")
            pass
    return ports


#  Com is a derivation of 'serial'
#
class Com(serial.Serial):
    def __init__(self, port, baud):
        # trace(port)
        serial.Serial.__init__(self)
        self.trace = False
        self.onewire = True
        self.preferred_port=port
        if port:
            self.setPort(port)
        if baud:
            self.baudrate=baud
        else:
            self.baudrate="115200"
        self.lastchar=None

    #  Open preferred or first serial port
    #
    def init(self):
        if self.isOpen():
            self.close()
        port=self.preferred_port
        if not port:
            ports=listports()
            if ports:
                port=ports[0]
        if port:
            self.setPort(port)
            try:
                self.open()
                self.setRTS(0) # Release RESET
                return 1
            except serial.serialutil.SerialException:
                pass
        return 0

    #  Reset device by setting RTS low
    #    Sending a BREAK will prevent diabolo from starting the user application
    #
    def reset_device(self):
        self.setRTS(1)
        time.sleep(0.01)
        self.setRTS(0)

    #  Emet un BREAK
    #    Un octet 0 + 1 bit de parité
    #
    def _brk(self, n):
        self.setParity(serial.PARITY_EVEN)
        while(n):
            cout(" BRK ")
            flushout()
            self.tx('\0') # BREAK
            self.flush()
            time.sleep(0.001)
            n-=1
        self.setParity(serial.PARITY_NONE)
        cout('\n')

    #  Send 10 bits low. In 1-wire mode, we'll receive this byte
    #
    def brk(self):
        self.setParity(serial.PARITY_EVEN)
        self.tx('\0') # BREAK
        self.setParity(serial.PARITY_NONE)

    def brk10(self):
        iflag, oflag, cflag, lflag, ispeed, ospeed, cc = termios.tcgetattr(self.fd)
        cflag &= ~(termios.PARODD)
        cflag |=  (termios.PARENB)
        termios.tcsetattr(self.fd, termios.TCSAFLUSH,
                          [iflag, oflag, cflag, lflag, ispeed, ospeed, cc])
        serial.Serial.write(self, '\x00')
        serial.Serial.read(self, 1)
        cflag &= ~(termios.PARENB|termios.PARODD)
        termios.tcsetattr(self.fd, termios.TCSANOW,
                          [iflag, oflag, cflag, lflag, ispeed, ospeed, cc])
        if self.onewire:
            serial.Serial.read(self, 1)

    #  Synchronise serial communication
    #    Send bytes such as 0x0A and 0x00 to let diabolo compute the baudrate
    #
    def sync(self, n=9):
        self.flushInput()
        self.flushOutput()
        self.lastchar=None
        for i in range(10):
            if n==5:
                self.tx('\x41')
                if self.rx(1): return True
            else:
                self.tx('\n')
                if self.rx(1): return True
                if n == 10:
                    self.brk(1)
                elif n == 9:
                    self.tx('\x00')
                else:
                    self.tx('\x80')
                if self.rx(1): return True
        return False

    #  Emet une chaîne
    #    Vérifie l'émission en mode "one-wire"
    #
    def tx(self, s):
        if self.trace:
            trace(repr(s))
        serial.Serial.write(self, s)
        if self.onewire:
            r = serial.Serial.read(self, len(s))
            if r != s:
                if self.trace:
                    trace()
                return False
        return True

    def rx(self, n=0):
        r = serial.Serial.read(self, n)
        if len(r):
            if self.trace:
                trace(repr(r))
            self.lastchar=r[-1]
        return r
