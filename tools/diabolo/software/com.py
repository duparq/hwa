#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2015-02-05 22:33:34 -*-

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


#  Com is a derivation of 'serial'
#
class Com:
    def __init__(self, port, baud, wires):
        # trace(port)
        self.baud = baud
        self.port = port
        self.wires = wires
        self.serial = None
        self.lastchar = None
        self.txbuf = ""
        self.rxbuf = ""
        self.lock = threading.Lock()
        self.rxevent = threading.Event()
        self.receiving = False
        self.error = ""

        try:
            self.open()
        except ValueError:
            cerr(_("Value error\n"))
        if not self.is_open():
            raise Exception(self.error)


    #  Receiver thread
    #    self.serial has a timeout so that self.alive is regularly checked
    #
    def __receiver_task(self):
        self.flush()
        # while self.serial.read(1) != None:
        #     pass
        while self.alive:
            r = self.serial.read(1)
            # trace(s2hex(r))
            if r:
                self.receiving = True
                with self.lock:
                    if self.txbuf:
                        s = self.txbuf[0]
                        self.txbuf = self.txbuf[1:]
                        if r != s:
                            cerr("  Echo mismatch: %02X != %02X\n" % (ord(r), ord(s)))
                        # else:
                        #     dbg("  Echo match: %02X\n" % ord(r))
                    else:
                        self.rxbuf += r
                        # dbg("RXBUF: %s\n" % s2hex(self.rxbuf))
            else:
                self.receiving = False
            self.rxevent.set()


    #  Open preferred or first serial port
    #
    def open(self):
        port = self.port
        if not port:
            ports=Com.listports()
            if ports:
                port=ports[0]
        if not port:
            raise Exception("No tty port to open")

        self.serial = serial.serial_for_url(port, self.baud)
        #self.btimeout = max(0.01, 20.0/self.baud)
        self.btimeout = max(0.01, 11.0/self.baud)
        self.serial.timeout = self.btimeout

        # Start receiver thread
        #
        self.alive = True
        self.receiver = threading.Thread(target=self.__receiver_task)
        self.receiver.setDaemon(1)
        self.receiver.start()


    #  List of available ttys among /dev/ttyUSB0..7 and /dev/stty0..7,
    #  excluding the 'avoid' one
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


    def close(self):
        # self.serial.close()
        self.alive = False
        self.rxevent.set()
        dbg("JOIN\n")
        self.receiver.join()
        dbg("JOINED\n")


    def detect_wires(self):
        if self.wires == 0:
            cout(_("Tty wires:"))
            self.tx('?')
            r = self.rx(2)
            if r==None or r=='' or r=='!':
                self.wires = 2
            elif r=='?' or r == '?!':
                self.wires = 1
            else:
                raise Exception("Can not handle reply: \"%s\" %s." % (r,s2hex(r)))
            cout(" %d\n" % self.wires)


    def is_open(self):
        return self.serial and self.serial.isOpen()

    def set_DTR(self, x):
        self.serial.setDTR(x)

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
        # while self.rx(1):
        #     pass

    #  Emet un BREAK (10 bits à 0)
    #
    def brk(self):
        dbg(" BRK ")
        t = time.time()
        self.serial.setParity(serial.PARITY_EVEN)
        self.tx('\0') # BREAK
        # self.serial.write('\0')
        self.serial.setParity(serial.PARITY_NONE)
        t = time.time()-t
        dbg(' %d ms\n' % (t*1000))

    #  Emet une chaîne
    #    Ajoute la chaîne au tampon d'émission en mode "one-wire"
    #
    def tx(self, s):
        # t = time.time()
        # dbg("TX: %s\n" % s2hex(s))
        if self.wires==1:
            with self.lock:
                self.txbuf += s
        self.serial.write(s)
        if self.wires==1:
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
        if n==0 or len(self.rxbuf) < n:
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
