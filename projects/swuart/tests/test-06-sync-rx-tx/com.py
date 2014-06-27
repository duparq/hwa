#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2014-06-14 10:55:31 -*-

# FT232RL :	 1 TXD
# 		 3 RTS (-> Reset)
# 		 5 RXD
# 		 4 VCCIO
# 		 7 GND
# 		17 3V3out
# 		18 GND
# 		20 VCC

import serial
import threading
import time
from utils import *


def dbg(s):
    # cout(s)
    pass


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
        except:
            pass
    return ports


#  Com is a derivation of 'serial'
#
class Com:
    def __init__(self, port, baud):
        # trace(port)
        self.baud = baud
        self.port = port
        self.serial = None
        self.onewire = False
        self.lastchar = None
        self.txbuf = ""
        self.rxbuf = ""
        self.lock = threading.Lock()
        self.rxevent = threading.Event()
        self.receiving = False

    #  Open preferred or first serial port
    #
    def open(self):
        port = self.port
        if not port:
            ports=listports()
            if ports:
                port=ports[0]
        if port:
            try:
                self.serial = serial.serial_for_url(port, self.baud)
                # dbg(_("Openned serial port %s at %d bps\n" % (self.port, self.baudrate)))
                self.btimeout = max(0.01, 20.0/self.baud)
                self.serial.timeout = self.btimeout
                # self.serial.timeout = 20.0/self.baud
                #
                # Start receiver thread
                #
                self.alive = True
                self.receiver = threading.Thread(target=self.receive)
                self.receiver.setDaemon(1)
                self.receiver.start()
                return True
            except serial.SerialException, e:
                return False

    def close(self):
        # self.serial.close()
        self.alive = False
        self.rxevent.set()
        dbg("JOIN\n")
        self.receiver.join()
        dbg("JOINED\n")

    #  Receiver thread
    #    self.serial has a timeout so that self.alive is regularly checked
    #
    def receive(self):
        while self.alive:
            r = self.serial.read(1)
            if r:
                self.receiving = True
                with self.lock:
                    if self.txbuf:
                        s = self.txbuf[0]
                        self.txbuf = self.txbuf[1:]
                        if r != s:
                            dbg("  Echo mismatch: %02X != %02X\n" % (ord(r), ord(s)))
                        # else:
                        #     dbg("  Echo match: %02X\n" % ord(r))
                    else:
                        self.rxbuf += r
                        # dbg("RXBUF: %s\n" % s2hex(self.rxbuf))
            else:
                self.receiving = False
            self.rxevent.set()

    def is_open(self):
        return self.serial and self.serial.isOpen()

    def set_RTS(self, x):
        self.serial.setRTS(x)

    def set_BRK(self, x):
        self.serial.setBreak(x)

    def flush(self):
        dbg("FLUSH\n")
        self.serial.flushOutput()
        self.serial.flushInput()
        self.txbuf = ""
        self.rxbuf = ""

    #  Emet un BREAK (10 bits à 0)
    #
    def brk10(self):
        dbg(" BRK ")
        t = time.time()
        self.serial.setParity(serial.PARITY_EVEN)
        self.tx('\0') # BREAK
        self.serial.setParity(serial.PARITY_NONE)
        t = time.time()-t
        dbg(' %d ms\n' % (t*1000))


    def sync_10_1(self, to):
        i = 0
        to += time.time()
        self.serial.setParity(serial.PARITY_EVEN)
        while time.time() < to:
            self.tx('\x00\xFF')
            r = self.rx(0)
            cout("%d: %s\n" % (i, s2hex(r)))
            if r:
                return True
            i += 1
            time.sleep(50.0/self.baud)
        self.serial.setParity(serial.PARITY_NONE)
        return False


    #  Emet une chaîne
    #    Ajoute la chaîne au tampon d'émission en mode "one-wire"
    #
    def tx(self, s):
        # t = time.time()
        # dbg("TX: %s\n" % s2hex(s))
        if self.onewire:
            with self.lock:
                self.txbuf += s
        self.serial.write(s)
        if self.onewire:
            while len(self.txbuf):
                self.rxevent.wait()
                self.rxevent.clear()
        else:
            time.sleep(len(s)*11.0/self.baud)
        # t = time.time()-t
        # cout("tx(%s): %d ms\n" % (s2hex(s), t*1000))

    #  Receive n bytes or until there's a timeout
    #
    def rx(self, n):
        if n ==0 or len(self.rxbuf) < n:
            #
            #  Wait an rxevent or a timeout
            #
            self.rxevent.wait()
            self.rxevent.clear()

        #  Wait end of reception
        #
        while self.receiving:
            if n and len(self.rxbuf)>=n:
                break
            self.rxevent.wait()
            self.rxevent.clear()

        with self.lock:
            #
            #  Retreive data
            #
            if n and len(self.rxbuf) > n:
                r = self.rxbuf[:n]
                self.rxbuf = self.rxbuf[n:]
            else:
                r = self.rxbuf
                self.rxbuf = ""
        return r


if __name__ == "__main__":

    from premain import *

    comargs={'port':None, 'baudrate':None}
    for arg in sys.argv[1:]:
        if "=" in  arg:
            c, a = arg.split('=')
            if c in comargs:
                comargs[c]=a
    com = Com(**comargs)
    print com.ports

    com.setRTS(1)
    time.sleep(0.1)
    com.setRTS(0)
    com.setBreak(True)
    time.sleep(0.4)
    com.setBreak(False)
    # com.setDTR(0)
    # time.sleep(1.0)
    # com.setBreak(False)
    # com.setRTS(0)
    # com.setDTR(1)

    #com.open()
    #com.close()
