#!/usr/bin/env python

# -*- coding: utf-8 -*-

# FT232RL :	 1 TXD
# 		 3 RTS (-> Reset)
# 		 5 RXD
# 		 4 VCCIO
# 		 7 GND
# 		17 3V3out
# 		18 GND
# 		20 VCC

import serial
import time
from utils import *


#  Return a list of available ttys among /dev/ttyUSB0..7 and /dev/stty0..7,
#  excluding the 'avoid' one
#
def list(avoid=()):
    ports=[]
    names=[]

    #  Standard serial devices (/dev/ttyS??, COM?? ...)
    #
    for n in range(8):
        d = serial.device(n)
        names.append(d)

    #  Linux USB adapter devices
    #
    for n in range(8):
        d = '/dev/ttyUSB%d' % n
        names.append(d)

    #  Check the availability of each device
    #
    for name in names:
        try:
            if not name in avoid:
                com=serial.Serial(name)
                com.close()
                ports.append(name)
        except serial.SerialException, e:
            pass
    return ports


def add_arguments(parser):
    """
    Put serial tty arguments into the parser
    """
    parser.add_argument('-t', '--tty', help="serial tty to use (/dev/ttyUSB0)",
                        default='/dev/ttyUSB0')
    parser.add_argument('-b', '--bps', help="baudrate (115200)", type=int,
                        default='115200')
    parser.add_argument('-w', '--wires', help="how many wires for rx/tx "
                        "(0 for autodetection)",
                        type=int, choices=range(3), default=0)
    parser.add_argument('-r', '--reset', help="signal used to reset the "
                        "device", choices=['','dtr','rts'], default='dtr')
    parser.add_argument('-d', '--reset-length', help="how long reset is "
                        "asserted in seconds (0.01)", metavar='SECONDS',
                        type=float, default='0.01')
    parser.add_argument('--keep-txd-low', help="how long TXD is "
                        "set low after RESET in seconds (0.0)", metavar='SECONDS',
                        type=float, default='0.0')
    parser.add_argument('-s', '--sync',
                        help="synchronization method (\"5/1\", default is \"\")",
                        default="")


class Com(serial.Serial):
    def __init__(self, **kwargs):
        print kwargs

        serial.Serial.__init__(self, kwargs['tty'], kwargs['bps'])
        self.timeout = max(0.001, 10.0/self.baudrate)
        # self.interCharTimeout = 1000e-6 # not implemented?
        self.wires = kwargs['wires']
        self.txbuf = ""
        self.reset_signal = kwargs['reset']
        self.reset_length = kwargs['reset_length']
        self.read = None	# Disable read (use rx)
        self.write = None	# Disable write (use tx)

        syncs = { '': None, '5/1': self.sync_5_1, '10/1': self.sync_10_1 }
        self.sync = syncs[kwargs['sync']]
        # cout(_("Timeout: %.2f ms\n" % (1000*self.timeout)))

        #  Reset the device. TXD must be maintained low while Diabolo computes
        #  the CRC of the application.
        #
        if self.reset_signal:
            cout(_("Resetting device using signal %s for %.2f s.\n" %
                   (self.reset_signal.upper(), self.reset_length)))
            self.setBreak(True)
            if self.reset_signal == "dtr":
                self.setDTR(True)
                time.sleep(self.reset_length)
                self.setDTR(False)
            elif self.reset_signal == "rts":
                self.setRTS(True)
                time.sleep(self.reset_length)
                self.setRTS(False)
            else:
                raise Exception(_("Unknown signal \"%s\" to drive reset." % self.reset_signal))

            #  Give Diabolo enough time to process the application CRC
            #
            # time.sleep(0.5)
            time.sleep(kwargs['keep_txd_low'])
            self.setBreak(False)

        #  Flush the input buffer.
        #
        serial.Serial.flush(self)
        while serial.Serial.read(self,1): pass

        #  Detect how many wires are used
        #
        if self.wires == 0:
            cout(_("Tty wires:"))
            # self.flush()
            # while serial.Serial.read(self,1): pass
            to = self.timeout
            self.timeout = 0.1
            serial.Serial.write(self,'?')
            r = serial.Serial.read(self,2)
            if r.startswith('?'):
                self.wires = 1
            else:
                self.wires = 2
            self.timeout = to
            cout(" %d\n" % self.wires)
            #self.flush()

        #  Synchronize device
        #
        if self.sync:
            self.sync()


    #  Flush the buffers
    #
    def flush(self):
        self.flushOutput()
        self.flushInput()
        self.txbuf = ""

    #  Send 10 low bits
    #    This is acheived by adding an even parity bit
    #
    def low10(self):
        self.setParity(serial.PARITY_EVEN)
        self.tx('\0')
        self.setParity(serial.PARITY_NONE)

    #  Synchronize the UART of the other side:
    #    send 10 bits low, followed by 1 bit low.
    #
    def sync_10_1(self):
        trace()
        for i in range(4):
            self.flush()
            self.low10()
            self.tx('\xFF')
            r = self.rx(10)
            if r != "":
                return True
        return False

    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):
        trace()
        cout("SYNC 5/1: ")
        # self.nresyncs += 1
        while serial.Serial.read(self,1): pass # flush
        for i in range(64):
            cout('.')
            flushout()
            Com.tx(self,'A')
            r = Com.rx(self,1)
            if len(r):
                # cout(' OK (0x%02X) after %d bytes sent.\n' % (ord(r[0]), i+1))
                return r[0]
        # cout(' FAILED after %d bytes sent.\n' % (i+1))
        # return False
        raise Exception("Synchronization failed")

    #  Send a string
    #    In one-wire mode, remove the echo
    #
    def rem_tx(self, s):
        self.flush()
        # trace(s2hex(s))
        serial.Serial.write(self,s)
        if self.wires==1:
            r = serial.Serial.read(self,len(s))
            if r != s:
                die("no echo.\n")

    def tx(self, s):
        serial.Serial.write(self,s)
        if self.wires==1:
            r = ""
            n = 0
            l = len(s)
            timeouts = 0
            while n<l:
                c = serial.Serial.read(self,1)
                if c !="" :
                    r += c
                    n += 1
                    timeouts = 0
                else:
                    timeouts += 1
                    if timeouts == 100:
                        raise Exception("timeout waiting echo")
            if r != s:
                raise Exception("wrong echo")


    #  Receive n bytes or until there's a timeout
    #
    def rem_rx(self, n):
        return serial.Serial.read(self,n)


    def rx(self, n):
        #
        #  Wait up to 100 timeouts for the beginning of reception
        #
        r = ""
        timeouts = 0
        while timeouts < 100:
            c = serial.Serial.read(self,1)
            if c !="" :
                r += c
                break
            timeouts += 1

        #  Wait for the completion of reception, accept up to 2 consecutive
        #  timeouts
        #
        timeouts = 0
        while len(r)<n and timeouts<2:
            c = serial.Serial.read(self,1)
            if c != "":
                r += c
                timeouts = 0
            else:
                timeouts += 1

        # if n>0 and len(r)<n: cout(" rx(%d):timeout(%d) " % (n,len(r))) ; flushout()

        return r


class Threaded(Com):
    """
    This is a threaded version of Com.
    """
    def __init__(self, **kwargs):
        Com.__init__(self, **kwargs)

        import threading
        self.rxbuf = ""
        self.lock = threading.Lock()
        self.rxevent = threading.Event()
        self.x_flush = False
        self.receiving = False

        self.nreads = 0
        self.treads = 0

        #  Receiver thread
        #    
        #    In one-wire mode, the output buffer (txbuf) contains characters that
        #    have been sent and that must be discarded when received back.
        #
        #    Since self.serial has a timeout, self.receiver_alive is checked and an
        #    rxevent is sent regularly even when no data is received.
        #
        def thread():
            while self.receiver_alive:
                t=timer()
                r = serial.Serial.read(self,1)	# Get one byte or "" if timeout
                if r != '':
                    #
                    #  Append received bytes to the input buffer.
                    #  Remove echo bytes.
                    #
                    with self.lock:
                        self.receiving = True
                        if self.txbuf:
                            s = self.txbuf[0]
                            self.txbuf = self.txbuf[1:]
                            # cout("<E%02X>" % ord(r)) ; flushout()
                            if r != s:
                                cerr("  Echo mismatch: rx=%02X, tx=%02X\n" % (ord(r), ord(s)))
                        else:
                            # cout("<RX%02X>" % ord(r)) ; flushout()
                            self.rxbuf += r
                else:
                    self.nreads += 1
                    self.treads += timer()-t
                    # if self.receiving: cout(" RX") ; flushout()
                    with self.lock:
                        self.receiving = False
                self.rxevent.set()

        self.receiver = threading.Thread(target=thread)
        self.receiver.setDaemon(1)
        self.receiver_alive = True
        self.receiver.start()


    def close(self):
        if self.receiver_alive:
            self.receiver_alive = False
            self.receiver.join()
            Com.close(self)
            cout("Average read timeout: %f\n" % (1.0*self.treads/self.nreads))

    #  Flush the buffers
    #    This is done by the receiver thread
    #
    def flush(self):
        # self.x_flush = True
        # while self.x_flush:
        #     self.rxevent.wait()
        #     self.rxevent.clear()
        while self.rx(1): pass

    #  Send a string
    #    In one-wire mode, the string is appended to the output buffer
    #    so that the receiver can discard the echo
    #
    def tx(self, s):

        if self.wires==1:
            with self.lock:
                if len(self.txbuf)>0:
                    raise Exception("txbuf not empty!")
                self.txbuf += s

        # cout("<TX%s>" % s2hex(s))
        serial.Serial.write(self,s)

        # self.rxevent.wait()
        # self.rxevent.clear()

        t=timer()
        if self.wires==1:
            # This does block with Python / Windows XP / Virtualbox
            # with self.lock:
            #     if len(self.txbuf) == 0:
            #         raise Exception("txbuf empty?")
            while len(self.txbuf)>0:
                if timer()-t > 0.1:
                    raise Exception("timeout")
                self.rxevent.wait()
                self.rxevent.clear()
        #cout("<%.2f ms>" % ((timer()-t)*1000)) ; flushout()

    #  Receive n bytes or until there's a timeout
    #
    def rx(self, n):

        if len(self.txbuf) > 0:
            with self.lock:
                raise Exception("txbuf not empty!", "[%s]" % s2hex(self.txbuf))

        #  Wait 100 timeouts for the beginning of reception
        #
        timeouts = 0
        while timeouts<100:
            self.rxevent.wait()
            self.rxevent.clear()
            if self.receiving:
                break
            timeouts += 1

        #  Wait for the completion of reception, accept up to 2 consecutive
        #  timeouts
        #
        timeouts = 0
        while len(self.rxbuf)<n and timeouts<2:
            self.rxevent.wait()
            self.rxevent.clear()
            if self.receiving:
                timeouts = 0
            else:
                timeouts += 1

        #  Retreive data
        #
        l=min(n,len(self.rxbuf))
        if l:
            with self.lock:
                r = self.rxbuf[:l]
                self.rxbuf = self.rxbuf[l:]
        else:
            r=""

        if n>0 and l<n: cout(" rx(%d):timeout(%d) " % (n,l))

        return r
