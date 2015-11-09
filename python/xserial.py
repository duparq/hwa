#!/usr/bin/env python

# -*- coding: utf-8 -*-


"""This is an extension of the PySerial module. It provides detection of the
number of wires and synchronization methods for use with HWA example projects
companion applications.

3 types of extensions are provided to have non-blocking reads:

 * use serial.timeout
 * use a separate thread and a timer
 * use a separate thread and events

Performances greatly vary depending on the type of extension used, the serial
interface driver and the platform. For example, the reading rate in bytes per
second of 32 KiB of Flash memory with Diabolo on a NanoDCCDuino:

                             Linux                 Windows XP VirtualBoxed

                    serial   thread   thread      serial   thread   threaded
                    timeout  timed    event       timeout  timed    event

PL2303 460800 Bps   25057    20262    15894        6981     4980     5932
PL2303 230400 Bps   16505    15219    14554        6183     4472     5538
PL2303 115200 Bps    9442     9081     9428        5248     4980     4540

CH340  460800 Bps   26436    23829    17288        1386     3410     1149
CH340  230400 Bps   16515    15255    14316        1254     2872     4674
CH340  115200 Bps    9439     8832     9015        5437     4012     4907

"""

import serial
import time
from utils import *


def add_arguments(parser):
    """
    Put serial tty arguments into the parser
    """
    parser.add_argument('-t', '--tty', help="serial tty to use (last of availables)") # (/dev/ttyUSB0)" )
#                        default='/dev/ttyUSB0')
    parser.add_argument('-b', '--bps', help="baudrate (115200)", type=int,
                        default='115200')
    parser.add_argument('--inter-char-delay', help="delay between transmitted characters",
                        type=float, default='0.0')
    parser.add_argument('-w', '--wires', help="how many wires for rx/tx "
                        "(0 for autodetection)",
                        type=int, choices=range(3), default=0)
    parser.add_argument('-r', '--reset-signal', help="signal used to reset the "
                        "device", choices=['','dtr','rts'], default='dtr')
    parser.add_argument('-d', '--reset-length', help="how long reset is "
                        "asserted in seconds, 0 means forever (default: 0.01)",
                        metavar='SECONDS', type=float, default='0.01')
    parser.add_argument('--keep-txd-low', help="how long TXD is "
                        "maintained low after RESET (0.0)", metavar='SECONDS',
                        type=float, default='0.0')
    parser.add_argument('--sync', choices=['5+1','10+1'],
                        help="synchronization method", default='')
    parser.add_argument('--threaded-timed',
                        help="use a separate thread and a timer for serial interface",
                        action='store_true')
    parser.add_argument('--threaded-event',
                        help="use a separate thread and events for serial interface",
                        action='store_true')


#  Return an arguments parser with XSerial arguments preloaded
#
def ArgumentParser():
    import argparse
    parser = argparse.ArgumentParser()
    add_arguments(parser)
    return parser


#  Return a list of available ttys among /dev/ttyUSB0..7 and /dev/stty0..7,
#  excluding the 'avoid' one
#
def list_ttys(avoid=()):
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
                xserial=serial.Serial(name)
                xserial.close()
                ports.append(name)
        except serial.SerialException, e:
            pass
    return ports


#  Return the last available serial interface among /dev/ttyUSB0..7 and /dev/stty0..7,
#  excluding the 'avoid' ones
#
def default(avoid=()):

    #  Standard serial devices (/dev/ttyS??, COM?? ...)
    #
    names=[ serial.device(n) for n in range(8) ]

    #  Linux USB adapter devices
    #
    for n in range(8):
        d = '/dev/ttyUSB%d' % n
        names.append(d)

    #  Check the availability of each device
    #
    for name in reversed(names):
        try:
            if not name in avoid:
                xserial=serial.Serial(name)
                xserial.close()
                return name
        except serial.SerialException, e:
            pass
    return None


#  Return a XSerial object according to arguments provided
#
def get_serial(args):
    if args.threaded_timed:
        serial = ThreadedTimed(args)
    elif args.threaded_event:
        serial = ThreadedEvent(args)
    elif args.tty and args.tty.startswith("net:"):
        import telnetlib
        serial = telnetlib.Telnet()
        serial.open("192.168.1.78")
        serial.write("?\r\n")
        serial.close()
        die("")
    else:
        serial = XSerial(args)
    return serial


class XSerial(serial.Serial):
    def __init__(self, args):
        #
        #  CH340/CH341 support seems very buggy! Occasionnally, reception is
        #  delayed for a long time. It seems that openning the device with a
        #  default baudrate, then changing it for the baudrate actually wanted
        #  avoids this strange behavior. That does not cause trouble for other
        #  devices so always do it that way.
        #

        #  Choose a default tty if none specified
        #
        if args.tty is None:
            tty = default()
            if tty:
                args.tty = tty
            else:
                die("No tty available")

        serial.Serial.__init__(self, args.tty, 1200)
        self.lastrxtime = 0
        # self.timeout = max(0.001, 10.0/self.baudrate)
        self.args = args
        self.inter_char_delay = args.inter_char_delay
        self.wires = args.wires
        self.reset_signal = args.reset_signal
        self.reset_length = args.reset_length
        self.keep_txd_low = args.keep_txd_low
        self.read = None	# Disable read (must use rx)
        self.write = None	# Disable write (must use tx)
        self.lastchar = None

        # syncs = { '': self.sync_none, '5+1': self.sync_5_1, '10+1': self.sync_10_1 }
        # self.sync = syncs[args.sync]

        self.baudrate = args.bps
        self.timeout = max(0.001, 10.0/args.bps)

        cout(_("Serial port: %s (%d bps)\n" % (args.tty, args.bps)))


    def reset_device(self):
        #
        #  Reset the device. To enter the Diabolo bootloader, TXD must be
        #  maintained low while Diabolo computes the CRC of the application.
        #
        #  With CH340, DTR is asserted ~2 ms before TXD goes low and is
        #  automatically reasserted, seemingly by hardware, after it has been
        #  released. So, to have the device see TXD low as soon as reset is
        #  asserted, we assert DTR once again before starting to compute the
        #  time TXD is low. Also, we leave DTR asserted as Arduino boards have
        #  DTR connected to RESET through a high-pass filter.
        #
        if self.reset_signal:
            if self.reset_length:
                cout(_("Resetting device using signal %s for %.3f s.\n" %
                       (self.reset_signal.upper(), self.reset_length)))
            else:
                cout(_("Resetting device using signal %s.\n" %
                       self.reset_signal.upper()))

            if self.keep_txd_low != 0:
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

            if self.reset_length==0:
                cout(_("Leaving reset signal %s low.\n" % self.reset_signal.upper()))
                if self.reset_signal == "dtr":
                    self.setDTR(True)
                else:
                    self.setRTS(True)

            if self.keep_txd_low>0:
                cout("Keeping TXD low for %.3f s\n" % self.keep_txd_low)
                time.sleep(self.keep_txd_low)
            self.setBreak(False)

    def detect_wires(self):
        #  Flush the input buffer.
        #
        # serial.Serial.flush(self)
        while serial.Serial.read(self,1): pass

        #  Detect how many wires are used
        #
        if self.wires == 0:
            cout(_("Tty wires:"))
            serial.Serial.write(self,'?')
            t=timer()+0.1
            wires=2
            while timer()<t:
                r = serial.Serial.read(self,1)
                if r=='?':
                    while serial.Serial.read(self,1): pass
                    wires = 1
                    break
            self.wires = wires
            cout(" %d\n" % self.wires)


    #  Flush the buffers
    #
    def flush(self):
        self.flushOutput()
        self.flushInput()
        while serial.Serial.read(self,1): pass # flush
        # self.txbuf = ""

    #  Send 10 low bits
    #    This is acheived by adding an even parity bit
    #
    #    NOTE: this does not work with CH340/CH341 under Linux (3.13.0-60)
    #          because the driver is buggy
    #
    def tx10low(self):
        self.setParity(serial.PARITY_EVEN)
        self.tx('\0')
        self.setParity(serial.PARITY_NONE)

    #  Synchronize the UART of the other side:
    #    send 10 bits low, followed by 1 bit low.
    #
    def sync_10_1(self):
        cout("Synchonizing with 10+1 low bits: ")
        while serial.Serial.read(self,1): pass # flush
        for i in range(4):
            cout('.')
            flushout()
            XSerial.flush(self)
            XSerial.tx10low(self)
            time.sleep(0.001)
            XSerial.tx(self,'\xFF')
            r = XSerial.rx(self,1)
            if len(r):
                cout(" OK after %d tries: '%c' (0x%02X).\n" % (i+1, r[0], ord(r[0])))
                self.lastchar = r[0]
                return
        raise Exception("synchronization failed")

    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):
        # trace()
        cout("Synchonizing with 5+1 low bits (ASCII 'A'): ")
        # self.nresyncs += 1
        while serial.Serial.read(self,1): pass # flush
        for i in range(4):
            cout('.')
            flushout()
            XSerial.tx(self,'A')
            r = XSerial.rx(self,1)
            if len(r):
                cout(" OK after %d bytes sent: '%c' (0x%02X).\n" % (i+1, r[0], ord(r[0])))
                self.lastchar = r[0]
                return
        raise Exception("synchronization failed")


    #  Default synchronization method: try 5+1, then 10+1
    #
    def sync(self):
        if self.args.sync=="" or self.args.sync=="5+1":
            try:
                self.sync_5_1()
                return
            except:
                cout('\n')
        if self.args.sync=="" or self.args.sync=="10+1":
            try:
                self.sync_10_1()
                return
            except:
                cout('\n')
        raise Exception("synchronization failed")


    #  Send a string
    #    In one-wire mode, remove the echo
    #
    def tx(self, s):
        if not self.inter_char_delay:
            serial.Serial.write(self,s)
        else:
            serial.Serial.write(self,s[0])
            for c in s[1:]:
                time.sleep(self.inter_char_delay)
                serial.Serial.write(self,c)
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
                    self.lastrxtime = timer()
                    timeouts = 0
                else:
                    timeouts += 1
                    if timeouts == 100:
                        raise Exception("timeout waiting echo")
            if r != s:
                raise Exception("wrong echo")


    #  Receive n bytes or until there's a timeout
    #
    def rx(self, n):
        #
        #  Wait up to 100 timeouts for the beginning of reception
        #
        #trace()
        r = ""
        for i in range(100):
            # trace()
            # if self.timeout > 0.001:
            #     raise Exception("timeout=%f" % self.timeout)
            c = serial.Serial.read(self,1)
            if c !="" :
                r += c
                self.lastchar = c
                self.lastrxtime = timer()
                break

        if r != "":
            #
            #  Wait for the completion of reception, accept up to 2 consecutive
            #  timeouts
            #
            timeouts = 0
            while len(r)<n:
                c = serial.Serial.read(self,1)
                if c != "":
                    r += c
                    self.lastchar = c
                    self.lastrxtime = timer()
                    timeouts = 0
                elif timeouts > 1:
                    # trace("RX TIMEOUT")
                    break
                else:
                    timeouts += 1
        # if n>0 and len(r)<n: cout(" rx(%d):timeout(%d) " % (n,len(r))) ; flushout()

        return r


    #  Return all received data until an nto2 bytes duration has elapsed without
    #  reception
    #
    def rx_until_idle(self, nto2=2):
        r = ""
        timeouts = 0
        while True:
            c = serial.Serial.read(self,1)
            if c != '':
                r += c
                self.lastrxtime = timer()
                timeouts = 0
            else:
                timeouts += 1
                if timeouts >= nto2:
                    return r


    def command(self, command, reply_length, timeout=0):
        """
        Send 'command' and wait for a reply of 'reply_length' bytes.
        Timeout occurs when there is no reception for more than 'timeout' seconds.
        """
        self.tx(command)
        if timeout==0:
            return self.xserial.rx(reply_length)
        else:
            to=timer()+timeout
            reply=""
            while len(reply)<reply_length and timer()<to:
                c=self.rx(1)
                if c:
                    to=timer()+timeout
                    reply += c
            return reply


class ThreadedTimed(XSerial):
    """This is a threaded version of XSerial. Serial.timeout seems to be buggy under
    Windows. This version uses serial.timeout only for the receiver thread not
    to be blocked on reception and then being able to terminate when asked. Each
    time a byte is received, its arrival time is monitored and that is used to
    compute timeouts.

    """
    def __init__(self, args):
        XSerial.__init__(self, args)

        import threading
        self.rxbuf = ""
        self.txbuf = ""
        self.lock = threading.Lock()

        self.lastrxtime = 0
        self.tbyte = max(0.001, 10.0/self.baudrate)

        #  For the receiver thread not to be blocked by read()
        #
        self.timeout = self.tbyte

        #  Receiver thread
        #    
        def thread():
            while self.receiver_alive:
                #
                # Wait for one byte or timeout
                #
                r = serial.Serial.read(self,1)
                if r:
                    #
                    #  Append received bytes to the input buffer.
                    #
                    with self.lock:
                        self.lastrxtime = timer()
                        if self.txbuf:
                            #
                            #    In one-wire mode, the output buffer (txbuf)
                            #    contains characters that have been sent and
                            #    that must be discarded when received back.
                            #
                            s = self.txbuf[0]
                            self.txbuf = self.txbuf[1:]
                            if r != s:
                                cerr("  Echo mismatch: rx=%02X, tx=%02X\n" % (ord(r), ord(s)))
                        else:
                            self.rxbuf += r

        self.receiver = threading.Thread(target=thread)
        self.receiver.setDaemon(1)
        self.receiver_alive = True
        self.receiver.start()


    def close(self):
        if self.receiver_alive:
            self.receiver_alive = False
            self.receiver.join()
            XSerial.close(self)


    def detect_wires(self):
        #
        #  Detect how many wires are used
        #
        if self.wires == 0:
            cout(_("Tty wires:"))
            self.flush()
            self.tx('?')
            # for i in range(2):
            #     time.sleep(self.tbyte)
            #     if len(self.rxbuf):
            #         break
            # if len(self.rxbuf):
            #     # r = self.rx(1)
            r = self.rx_until_idle(1)
            if r=='?':
                wires = 1
            elif r=='':
                self.wires = 2
            else:
                die("Bad echo")
            cout(" %d\n" % self.wires)

    #  Flush the buffers
    #
    def flush(self):
        with self.lock:
            r = self.rxbuf
            self.rxbuf = ""


    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):

        cout("Synchonizing with 5+1 low bits (ASCII 'A'): ")

        self.flush()
        for i in range(4):
            cout('.')
            flushout()
            self.tx('A')
            r = self.rx(1)
            if len(r):
                cout(" received '%c' (0x%02X) after %d tries.\n" % (r[0], ord(r[0]), i+1))
                self.lastchar = r[0]
                return
        raise Exception("synchronization failed")

    #  Send a string
    #
    #    In one-wire mode, the string is appended to the output buffer
    #    so that the receiver can discard the echo
    #
    def tx(self, s):

        if self.wires==1:
            with self.lock:
                if len(self.txbuf)>0:
                    raise Exception("txbuf not empty!")
                self.txbuf += s

        serial.Serial.write(self,s)

        if self.wires==1:
            for i in range(len(s)+1):
                if len(self.txbuf) == 0:
                    break
                time.sleep(self.tbyte)


    #  Receive n bytes or until there's a timeout
    #    nto1: number of byte duration until reception has begun
    #    nto2: number of byte duration the reception is idle
    #
    def rx(self, n, nto1=100, nto2=2):

        if len(self.txbuf) > 0:
            with self.lock:
                raise Exception("txbuf not empty!", "[%s]" % s2hex(self.txbuf))

        #  Wait up to nto1 byte durations for something to read
        #
        for i in range(nto1):
            if len(self.rxbuf)>0:
                break
            time.sleep(self.tbyte)

        #  Wait for the completion of reception: when all the wanted data bytes
        #  have arrived or when nothing has been received for the duration of
        #  nto2 bytes
        #
        while len(self.rxbuf) < n:
            t=timer()
            if t > self.lastrxtime + nto2*self.tbyte:
                break
            time.sleep(max(0,t-(self.lastrxtime+self.tbyte)))

        #  Retrieve data
        #
        l=min(n,len(self.rxbuf))
        if l:
            with self.lock:
                r = self.rxbuf[:l]
                self.rxbuf = self.rxbuf[l:]
                self.lastchar = r[-1]
        else:
            r=""

        return r

    #  Return all received data until an nto2 bytes duration has elapsed without
    #  reception
    #
    def rx_until_idle(self, nto2=2):
        while True:
            t=timer()
            with self.lock:
                if t > self.lastrxtime + nto2*self.tbyte:
                    r = self.rxbuf
                    self.rxbuf = ""
                    if len(r):
                        self.lastchar = r[-1]
                    return r
            time.sleep(max(0,t-(self.lastrxtime+self.tbyte)))


class ThreadedEvent(XSerial):
    """Use a seperate thread for serial communication and events to signal
    reception (or timeout).

    """
    def __init__(self, args):
        XSerial.__init__(self, args)

        import threading
        self.rxbuf = ""
        self.txbuf = ""
        self.lock = threading.Lock()

        self.tbyte = max(0.001, 10.0/self.baudrate)

        #  For the receiver thread not to be blocked by read()
        #
        # self.timeout = 0.01
        self.timeout = self.tbyte

        self.rxevent = threading.Event()
        self.receiving = False

        #  Receiver thread
        #
        #    Each time serial.read() returns, self.receiving is updated and an
        #    rxevent is set.
        #
        def thread():
            while self.receiver_alive:
                r = serial.Serial.read(self,1)	# Wait for one byte or timeout
                if r=='':
                    self.receiving = False
                else:
                    #  Append received bytes to the input buffer.
                    #  Remove echo bytes.
                    #
                    with self.lock:
                        self.receiving = True
                        if self.txbuf:
                            #    
                            #    In one-wire mode, the output buffer (txbuf)
                            #    contains characters that have been sent and
                            #    that must be discarded when received back.
                            #
                            s = self.txbuf[0]
                            self.txbuf = self.txbuf[1:]
                            if r != s:
                                cerr("  Echo mismatch: rx=%02X, tx=%02X\n" % (ord(r), ord(s)))
                        else:
                            self.rxbuf += r
                self.rxevent.set()

        self.receiver = threading.Thread(target=thread)
        self.receiver.setDaemon(1)
        self.receiver_alive = True
        self.receiver.start()


    def close(self):
        if self.receiver_alive:
            self.receiver_alive = False
            self.receiver.join()
            XSerial.close(self)


    def detect_wires(self):
        #
        #  Detect how many wires are used
        #
        if self.wires == 0:
            cout(_("Tty wires:"))
            self.flush()
            self.tx('?')
            r = self.rx_until_idle(1)
            if r=='?':
                wires = 1
            elif r=='':
                self.wires = 2
            else:
                die("Bad echo")
            cout(" %d\n" % self.wires)

    #  Flush the buffers
    #
    def flush(self):
        with self.lock:
            r = self.rxbuf
            self.rxbuf = ""


    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):

        cout("Synchonizing with 5+1 low bits (ASCII 'A'): ")

        self.flush()
        for i in range(4):
            cout('.')
            flushout()
            self.tx('A')
            r = self.rx(1)
            if len(r):
                cout(" received '%c' (0x%02X) after %d tries.\n" % (r[0], ord(r[0]), i+1))
                self.lastchar = r[0]
                return
        raise Exception("synchronization failed")

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

        serial.Serial.write(self,s)

        if self.wires==1:
            while len(self.txbuf):
                self.rxevent.wait()
                self.rxevent.clear()


    #  Receive n bytes or until there's a timeout
    #    nto1: number of byte duration until reception has begun
    #    nto2: number of byte duration the reception is idle
    #
    def rx(self, n, nto1=100, nto2=2):

        if len(self.txbuf):
            with self.lock:
                raise Exception("txbuf not empty!", "[%s]" % s2hex(self.txbuf))

        #  Wait up to nto1 byte durations for something to read
        #
        timeouts = 0
        while timeouts<nto1 and len(self.rxbuf)==0:
            self.rxevent.wait()
            self.rxevent.clear()
            timeouts += 1

        #  Wait for the completion of reception: when all the wanted data bytes
        #  have arrived or when nothing has been received for the duration of
        #  nto2 bytes
        #
        timeouts = 0
        while len(self.rxbuf)<n:
            self.rxevent.wait()
            self.rxevent.clear()
            if self.receiving:
                timeouts = 0
            else:
                timeouts += 1
                if timeouts >= nto2:
                    break

        #  Retrieve data
        #
        l=min(n,len(self.rxbuf))
        if l:
            with self.lock:
                r = self.rxbuf[:l]
                self.rxbuf = self.rxbuf[l:]
                self.lastchar = r[-1]
        else:
            r=""

        return r

    #  Return all received data until an nto2 bytes duration has elapsed without
    #  reception
    #
    def rx_until_idle(self, nto2=2):
        timeouts = 0
        while True:
            self.rxevent.wait()
            self.rxevent.clear()
            if self.receiving:
                timeouts = 0
            else:
                timeouts += 1
                if timeouts >= nto2:
                    r = self.rxbuf
                    self.rxbuf = ""
                    if len(r):
                        self.lastchar = r[-1]
                    return r
