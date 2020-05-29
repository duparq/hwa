#!/usr/bin/env python
# -*- coding: utf-8 -*-

#  Use the pySerial-3.0 serial module
#
import sys
import os.path
#sys.path.insert(1,os.path.normpath(sys.path[0]+"/pyserial-3.0"))

import serial
import time
from utils import *


if os.name == 'nt':  # sys.platform == 'win32':
    from serial.tools.list_ports_windows import comports
elif os.name == 'posix':
    from serial.tools.list_ports_posix import comports
else:
    raise ImportError("Sorry: no implementation available for '%s'" % (os.name,))


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
                        type=int, choices=(0,1,2), default=0)
    parser.add_argument('-r', '--reset-signal', help="signal used to reset the "
                        "device", choices=['','dtr','rts'], default='dtr')
    parser.add_argument('-d', '--reset-length', help="how long reset is "
                        "asserted in seconds, 0 means forever (default: 0.01)",
                        metavar='SECONDS', type=float, default='0.01')
    parser.add_argument('--keep-txd-low', help="how long TXD is "
                        "maintained low after RESET (0.5)", metavar='SECONDS',
                        type=float, default='0')
    parser.add_argument('--sync', choices=['51','91','101'],
                        help="synchronization method", default='')
    parser.add_argument('--threaded-timed',
                        help="use a separate thread and a timer for serial interface",
                        action='store_true')
    parser.add_argument('--threaded-event',
                        help="use a separate thread and events for serial interface",
                        action='store_true')


#  Return an arguments parser with Link arguments preloaded
#
def ArgumentParser():
    import argparse
    parser = argparse.ArgumentParser()
    add_arguments(parser)
    return parser


#  Return a list of available serial ports
#
def list():
    return sorted([ i[0] for i in comports() ])


#  Return the last available serial port
#
def default(avoid=()):
    for name in reversed(list()):
        if not name in avoid:
            return name
    return None


#  Return a Link object according to arguments provided
#
def get(args):
    if args.threaded_timed:
        serial = ThreadedTimed(args)
    elif args.threaded_event:
        serial = ThreadedEvent(args)
    else:
        serial = Link(args)
    return serial


#  This class encapsulates a serial link object. That can be a real serial port,
#  a USB converter, or a network connection...
#
class Link:
    def __init__(self, args):
        #
        #  CH340/CH341 support seems very buggy! Occasionnally, reception is
        #  delayed for a long time. It seems that openning the device with a
        #  default baudrate, then changing it for the baudrate actually wanted
        #  avoids this strange behavior. That does not cause trouble for other
        #  devices so let's do it always that way.
        #

        #  Choose a default tty if none specified
        #
        if args.tty is None:
            tty = default()
            if tty:
                args.tty = tty
            else:
                die("No tty available")

        self.serial = serial.serial_for_url(args.tty, do_not_open=True)
        self.lastrxtime = 0
        self.args = args
        self.inter_char_delay = args.inter_char_delay
        self.wires = args.wires
        self.reset_signal = args.reset_signal
        self.reset_length = args.reset_length
        self.keep_txd_low = args.keep_txd_low
        self.read = None	# Disable read (must use rx)
        self.write = None	# Disable write (must use tx)
        self.lastchar = None

        self.serial.timeout = max(0.001, 10.0/args.bps)

        self.serial.baudrate = self.args.bps
        self.serial.open()

        cout(_("Serial port: %s (%d bps)\n" % (args.tty, args.bps)))


    def rem_reset_device(self):
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
                self.serial.break_condition = True

            if self.reset_signal == "dtr":
                self.serial.dtr = True
                time.sleep(self.reset_length)
                self.serial.dtr = False
            elif self.reset_signal == "rts":
                self.serial.rts = True
                time.sleep(self.reset_length)
                self.serial.rts = False
            else:
                raise Exception(_("Unknown signal \"%s\" to drive reset." % self.reset_signal))

            if self.reset_length==0:
                cout(_("Leaving reset signal %s low.\n" % self.reset_signal.upper()))
                if self.reset_signal == "dtr":
                    self.serial.dtr = True
                else:
                    self.serial.rts = True

            if self.keep_txd_low>0:
                cout("Keeping TXD low for %.3f s\n" % self.keep_txd_low)
                time.sleep(self.keep_txd_low)
            self.serial.break_condition = False

    def set_RESET(self, state):
        if not self.reset_signal:
            raise Exception(_("No signal \"%s\" to drive reset." % self.reset_signal))

        if self.reset_signal == "dtr":
            if state == 0:
                cout(_("Resetting device using signal %s.\n" %
                       self.reset_signal.upper()))
                self.serial.dtr = True
            else:
                self.serial.dtr = False
        elif self.reset_signal == "rts":
            if state == 0:
                cout(_("Resetting device using signal %s.\n" %
                       self.reset_signal.upper()))
                self.serial.rts = True
            else:
                self.serial.rts = False
        else:
            raise Exception(_("Unknown signal \"%s\" to drive reset." % self.reset_signal))

    def set_TXD(self, state):
        if state == 0:
            self.serial.break_condition = True
        else:
            self.serial.break_condition = False


    #  Detect how many wires are used
    #
    def detect_wires(self, char):
        self.flush()
        if self.wires == 0:
            self.serial.write(char)
            t=timer()+0.1
            wires=2
            while timer()<t:
                r = self.serial.read(1)
                if r==char:
                    while self.serial.read(1): pass
                    wires = 1
                    break
            self.wires = wires


    #  Flush the buffers
    #
    def flush(self):
        self.serial.flushOutput()
        self.serial.flushInput()
        while self.serial.read(1): pass


    #  Send 10 low bits
    #    This is acheived by adding an even parity bit
    #
    #    NOTE: this does not work with CH340/CH341 under linux-3.13.0-60
    #          because of a bug in the kernel driver
    #
    def tx10low(self):
        self.serial.parity =  serial.PARITY_EVEN
        self.tx(b'\x00')
        self.serial.parity =  serial.PARITY_NONE

    #  Synchronize the UART of the other side:
    #    send 10 bits low, followed by 1 bit low.
    #
    def sync_101(self):
        cout("Synchronizing (101): ")
        while self.serial.read(1): pass # flush
        for i in range(4):
            cout('.')
            flushout()
            self.flush()
            self.tx10low()
            r = self.rx(1,1,1)
            if len(r)==0:
                self.tx(b'\xFF')
                r = self.rx(1,1,1)
            if len(r):
                cout(" OK after %d tries: 0x%02X.\n" % (i+1, r[0]))
                self.lastchar = r[0]
                return True
            time.sleep(0.1)
        cout('\n')
        return False


    #  Synchronize UART with 9/1 low-level sequences
    #
    def sync_91(self):
        cout("Synchronizing (91): ")
        while self.serial.read(1): pass # flush
        for i in range(4):
            cout('.')
            flushout()
            self.tx(b'\0')
            r = self.rx(1,1,1)
            if len(r)==0:
                self.tx(b'\xFF')
                r = self.rx(1,1,1)
            if len(r):
                cout(" OK after %d tries: '%c' (0x%02X).\n" % (i+1, r[0], ord(r[0])))
                self.lastchar = r[0]
                return True
        cout('\n')
        return False


    #  Synchronize UART with 5/1 low-level sequences
    #    Several possibilities:
    #
    #      'A' (0x41): 1 low + 1 high + 5 low + 1 high + 1 low, the first bit
    #		       low requires the device to be quick enough to detect the
    #		       following 5 low bits
    #
    #      'p' (0x70): 5 low + 3 high + 1 low, may be the most efficient
    #
    #      0xF0 / 0xFF: 5 low + many high + 1 low, good for slowest devices
    #
    def sync_51(self):
        #trace()
        cout("Synchronizing (51): ")
        while self.serial.read(1): pass # flush
        for i in range(4):
            cout('.')
            flushout()
            self.tx(b'\x70')
            r = self.rx(1,1,1)
            if len(r):
                cout(" OK after %d bytes sent: 0x%02X.\n" % (i+1, r[0]) )
                self.lastchar = r[0]
                return True
        cout('\n')
        return False


    #  Default synchronization method: try 51, then 91, then 101
    #
    def sync(self):
        #trace()
        if self.args.sync=="" or self.args.sync=="51":
            if self.sync_51():
                return True
        if self.args.sync=="" or self.args.sync=="91":
            if self.sync_91():
                return True
        if self.args.sync=="" or self.args.sync=="101":
            if self.sync_101():
                return True
        return False


    #  Send bytes
    #    In one-wire mode, wait for the echo and remove it
    #
    def tx(self, bs):
        if repr(type(bs))=="<class 'str'>":
            import inspect
            caller = inspect.stack()[1]
            print("Warning: using str instead of bytes (from %s in %s:%s)\n" % \
                  (caller[3], os.path.basename(caller[1]), caller[2]))
        if not self.inter_char_delay:
            self.serial.write(bs)
        else:
            self.serial.write(bs[0])
            for b in bs[1:]:
                time.sleep(self.inter_char_delay)
                cout(c)
                self.serial.write(b)
                return True
        if self.wires==1:
            br = bytes()
            self.lastrxtime = timer()
            while len(br)<len(bs):
                b = self.serial.read(1)
                if len(b)==0:
                    if timer()-self.lastrxtime > 0.1:
                        raise Exception("One-wire echo timeout")
                elif len(b)==1:
                    #trace("echo len(bs)=%d len(br)=%d, %d: %s" % (len(bs),len(br),len(b),repr(b)))
                    br += b
                    self.lastrxtime = timer()
                else:
                    raise Exception("several bytes received instead of one.")
            if br == bs:
                return True
            raise Exception("One-wire wrong echo\n  S: %s\n  R: %s" % (bs.hex(),br.hex()))


    #  Receive l bytes or until there's a timeout
    #
    def rx(self, l, t1=100, t2=1):
        #
        #  Wait up to n1 timeouts for the beginning of reception
        #
        r = bytearray()
        for i in range(t1):
            c = self.serial.read(1)
            if len(c):
                #trace("received %d bytes: %s\n" % (len(c),c.hex()) )
                r.extend(c)
                self.lastchar = ord(c)
                self.lastrxtime = timer()
                break

        if len(r):
            #
            #  Wait for the completion of reception.
            #  Accept up to t2 consecutive timeouts.
            #
            timeouts = 0
            while len(r)<l:
                c = self.serial.read(1)
                if len(c):
                    r.extend(c)
                    self.lastchar = ord(c)
                    self.lastrxtime = timer()
                    timeouts = 0
                elif timeouts > t2:
                    break
                else:
                    timeouts += 1
        return bytes(r)


    #  Return all received data until t2 bytes duration has elapsed without
    #  reception
    #
    def rx_until_idle(self, t2=1):
        r = bytearray()
        timeouts = 0
        while True:
            c = self.serial.read(1)
            if c != '':
                r.extend(c)
                self.lastrxtime = timer()
                timeouts = 0
            else:
                timeouts += 1
                if timeouts > t2:
                    return r


    def close(self):
        self.serial.close()


class ThreadedTimed(Link):
    """This is a threaded version of Link. Serial.timeout seems to be buggy under
    Windows. This version uses serial.timeout only for the receiver thread not
    to be blocked on reception and then being able to terminate when asked. Each
    time a byte is received, its arrival time is memorized for later timeouts
    computings.

    """
    def __init__(self, args):
        Link.__init__(self, args)

        import threading
        self.rxbuf = ""
        self.txbuf = ""
        self.lock = threading.Lock()

        #  Receiver thread
        #    
        def thread():
            while self.receiver_alive:
                #
                #  Wait for one byte or timeout.
                #  The timeout value is set in the base class.
                #
                r = self.serial.read(1)
                if r:
                    #
                    #  Append received byte to the input buffer.
                    #
                    with self.lock:
                        self.lastrxtime = timer()
                        if self.txbuf:
                            #
                            #  In one-wire mode, the output buffer (txbuf)
                            #  contains characters that have been sent and
                            #  that must be discarded when received back.
                            #
                            s = self.txbuf[0]
                            self.txbuf = self.txbuf[1:]
                            if r != s:
                                die("one-wire echo mismatch: TX=%02X, RX=%02X\n" \
                                    % (ord(s), ord(r)))
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
            Link.close(self)


    def detect_wires(self):
        #
        #  Detect how many wires are used
        #
        self.flush()
        if self.wires == 0:
            self.tx('?')
            self.lastrxtime = timer()
            r = self.rx(1, 0.1)
            if r=='?':
                self.wires = 1
            elif r=='':
                self.wires = 2
            else:
                die("Bad echo")

    #  Flush the buffers
    #
    def flush(self):
        with self.lock:
            Link.flush(self)
            self.txbuf = ""
            self.rxbuf = ""


    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_51(self):
        cout("Synchronizing with 5+1 low bits (ASCII 'A'): ")
        for i in range(4):
            self.tx('A')
            r = self.rx(1, 0.1)
            cout('.')
            flushout()
            if len(r):
                cout(" received '%c' (0x%02X) after %d tries.\n" % (r[0], ord(r[0]), i+1))
                self.lastchar = r[0]
                return
        raise Exception("synchronization failed")

    #  Send a string
    #    In one-wire mode, remove the echo
    #
    def tx(self, s):

        #  There should not be waiting bytes in the output buffer
        #
        with self.lock:
            if len(self.txbuf):
                raise Exception

        #  In one-wire mode, the string is appended to the output buffer
        #  so that the receiver can discard the echo
        #  
        if self.wires==1:
            with self.lock:
                self.txbuf += s

        self.serial.write(s)

        #  Wait that all data has been echoed back
        #
        if self.wires==1:
            t=timer()
            l0=len(self.txbuf)
            while timer()-t < 1.0:
                l = len(self.txbuf)
                if l != l0:
                    l0=l
                    if l0==0:
                        break
                    t=timer()
                time.sleep(self.serial.timeout)
            if l0:
                raise Exception


    #  Receive n bytes or until there's a timeout
    #
    def rx(self, n, t1=1.0, t2=0.001):

        #  Wait up to t1 seconds for something to read
        #
        t=timer()
        while len(self.rxbuf)<n and timer()-t < t1:
            time.sleep(self.serial.timeout)

        #  Wait for the completion of reception: when all the wanted data bytes
        #  have arrived or when nothing has been received t2 seconds
        #
        while len(self.rxbuf)<n and timer()-self.lastrxtime < t2:
            time.sleep(self.serial.timeout)

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


class rem_ThreadedEvent(Link): # THIS HAS TO BE REWRITTEN
    """Use a seperate thread for serial communication and events to signal
    reception (or timeout).

    """
    def __init__(self, args):
        Link.__init__(self, args)

        import threading
        self.rxbuf = ""
        self.txbuf = ""
        self.lock = threading.Lock()

        # self.tbyte = max(0.001, 10.0/self.serial.baudrate)

        #  For the receiver thread not to be blocked by read()
        #
        # self.timeout = 0.01
        # self.serial.timeout = self.tbyte

        self.rxevent = threading.Event()
        self.receiving = False

        #  Receiver thread
        #
        #    Each time serial.read() returns, self.receiving is updated and an
        #    rxevent is set.
        #
        def thread():
            while self.receiver_alive:
                r = self.serial.read(1)	# Wait for one byte or timeout
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
            Link.close(self)


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
                self.wires = 1
            elif r=='':
                self.wires = 2
            else:
                die("Bad echo")
            cout(" %d\n" % self.wires)

    #  Flush the buffers
    #
    def flush(self):
        Link.flush(self)
        with self.lock:
            self.rxbuf = ""


    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_51(self):

        cout("Synchronizing with 5+1 low bits (ASCII 'A'): ")

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

        self.serial.write(s)

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


if __name__ == '__main__':
    import premain
    import argparse
    parser = argparse.ArgumentParser()
    add_arguments(parser)
    args = parser.parse_args()

    enable_trace()

    link = Link(args)
    link.detect_wires()
    cout(_("Tty wires: %d\n") % link.wires)
    link.tx("Hello World!")
    link.reset_device()
