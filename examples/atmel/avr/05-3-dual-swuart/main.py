#!/usr/bin/env python
# -*- coding: utf-8 -*-


errors = 0


class Application:
    def __init__(self):

        import argparse
        parser = argparse.ArgumentParser()

        #  Serial tty arguments
        #
        parser.add_argument('-t', '--tty', help="serial tty to use (/dev/ttyUSB0)",
                            default='/dev/ttyUSB0')
        parser.add_argument('-b', '--bps', help="baudrate (115200)", type=int,
                            default='115200')
        parser.add_argument('-w', '--wires', help="how many wires for rx/tx "
                            "(0 for autodetection)",
                            type=int, choices=range(3), default=0)
        parser.add_argument('-r', '--reset', help="signal used to reset the "
                            "device", choices=['dtr','rts'], default='dtr')
        parser.add_argument('-d', '--reset-length', help="how long reset is "
                            "asserted in seconds (0.01)", metavar='SECONDS',
                            type=float, default='0.01')

        self.options = parser.parse_args()

        self.lastchar = ''
        self.nresumes = 0
        self.nresyncs = 0

    def set_reset(self, state):
        if self.options.reset == "dtr":
            self.com.set_DTR(state)
        elif self.options.reset == "rts":
            self.com.set_RTS(state)
        else:
            raise Exception("No signal to drive reset.")

    #  Transmit data
    #
    def tx ( self, data ):
        self.lastchar=None
        self.com.tx(data)
        #  Atmel devices need about 50 cycles to compute the CRC between each
        #  received byte
        # for d in data:
        #     self.com.tx(d)
        #     time.sleep(0.000005)

    #  Transmit 10 bits low
    #
    def tx_10low ( self ):
        self.com.brk()

    #  Receive data
    #
    def rx ( self, n ):
        # timeout = max( 0.1, n*10.0/self.com.baud )
        # r = self.com.rx(n, timeout)
        r = self.com.rx(n)
        if r:
            self.lastchar = r[-1]
        # cout("RX %d: %d, %s\n" % (n, len(r), s2hex(r)))
        return r

    #  Synchronize UART with 10/1 low-level sequences
    #
    def sync_10_1(self):
        cout("SYNC 10/1: ")
        self.nresyncs += 1
        for i in range(64):
            cout('.')
            flushout()
            if i%2 == 0:
                self.tx_10low()
            else:
                self.tx('\xFF')
            r = self.rx(10)
            if r.endswith('!'):
                self.tx('\n')
                r = self.rx(10)
            if r.endswith('#'):
                cerr(' received Diabolo prompt. Application is not installed '
                     'or Flash memory is corrupted.\n')
                return False
            if len(r):
                cout(' OK after %d bytes sent.\n' % (i+1))
                return r[-1]
        cout(' FAILED after %d bytes sent.\n' % (i+1))
        return False

    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):
        cout("SYNC 5/1: ")
        self.nresyncs += 1
        for i in range(64):
            cout('.')
            flushout()
            self.tx('A')
            r = self.rx(10)
            if len(r)==1:
                cout(' OK (0x%02X) after %d bytes sent.\n' % (ord(r[0]), i+1))
                return r[0]
        cout(' FAILED after %d bytes sent.\n' % (i+1))
        return False


    def run(self, method):

        if method=="10_1":
            self.sync = self.sync_10_1
        elif method=="5_1":
            self.sync = self.sync_5_1
        else:
            cout("Sync method '%s' not supported.\n" % method)
            sys.exit(1)

        #  Open the communication
        #
        self.com = Com(self.options.tty, self.options.bps, self.options.wires)
        cout(_("Interface: %s (%d bps)\n" % (self.options.tty, self.options.bps)))

        #  Reset the device
        #
        #    This is the moment to detect how many wires are used for
        #    communication
        #
        cout(_("Resetting device using signal %s for %.2f s.\n" %
               (self.options.reset.upper(), self.options.reset_length)))
        self.set_reset(True)
        self.com.detect_wires()
        time.sleep(self.options.reset_length)
        self.set_reset(False)

        #  Give Diabolo enough time to check the CRC of the application and
        #  start it
        #
        time.sleep(0.1)

        #  Get prompt
        #
        # if not self.get_prompt('$'):
        #     die(_("Could not get the application prompt.\n"))
        # cout('Application prompt: $\n')

        if not self.sync():
            die(_("Could not get the application prompt.\n"))
        cout('Application prompt: \n')

        dt = 100.0/self.options.bps
        cout("tick=%f\n" % dt)

        import struct
        t0 = 0
        tick=time.time()
        global errors
        n = 0
        col = 0
        byte = 0
        while True:
            if n==128:
                n=0
                self.tx_10low()
                if not self.sync():
                    die(_("Could not get the application prompt.\n"))
                continue
            self.tx(chr(byte))
            n+=1
            r = self.rx(1)
            if len(r) != 1 or r[-1]!=chr(byte):
            #     # die("Could not get dt.\n")
            #     cout("ERROR: %d bytes received: %s\n" % (len(r), s2hex(r)))
            #     errors += 1
                self.rx(10)
            #     self.tx_10low()
            # elif ord(r[0]) != byte:
                cout('x')
            else:
                cout('.')
            flushout()
            if byte % 64 == 63:
                cout('\n%.3f: ' % tick)
            byte = (byte+1)%256
            tick += dt
            dtime = max(0.001, tick-time.time())
            time.sleep( dtime )
        self.com.close()


if __name__ == "__main__":
    import sys
    import os.path
    import __builtin__

    sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))

    import premain
    from com import Com
    from utils import s2hex, hexdump
    import time

    #  Get the sync method to use
    #
    import subprocess
    subprocess.call(["make", "sync"])

    f=open("build/sync", "r")
    s = f.read()
    f.close()

    s = s.replace('\n','').split("=")
    if s[0]!="SYNC":
        cout("Synchronization method not found.\n")
        sys.exit(1)

    #  Start application
    #
    try:
        Application().run(s[1])
    except KeyboardInterrupt:
        cout("\nErrors: %d\n" % errors)
    # except Exception, e:
    #     cerr(str(e)+'\n')
