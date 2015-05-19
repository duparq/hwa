#!/usr/bin/env python
# -*- coding: utf-8 -*-


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

    #  Get the '#' prompt
    #
    #    This can be necessary after entering the error state or if the
    #    synchronization has been lost or was not done yet
    #
    def get_prompt(self):
        # trace()

        #  Resume from error?
        #
        if self.lastchar == '!':
            self.nresumes += 1
            self.tx('\n')
            self.rx(1)
        if self.lastchar == '#':
            return True

        #  Synchronize
        #
        #    Send 10 bits / 1 bit low bytes alternately to make the device
        #    synchronize its UART
        #
        cout("SYNC: ")
        self.nresyncs += 1
        for i in range(64):
            cout('.')
            flushout()
            if i%2 == 0:
                self.tx_10low()
            else:
                self.tx('\xFF')
            # time.sleep(0.2)
            r = self.rx(10)
            if r.endswith('!'):
                self.tx('\n')
                r = self.rx(10)
            if r.endswith('#'):
                cout(' OK after %d bytes sent.\n' % (i+1))
                return True
        cout(' FAILED after %d bytes sent.\n' % (i+1))
        return False

    def run(self):
        #
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

        #  Let enough time to Diabolo to check the CRC of the application and
        #  start it
        #
        time.sleep(0.1)

        #  Test
        #
        col = 0
        while True:
            c = self.com.rx(1)
            if c:
                cout(c)
                flushout()
                col += 1
                if col == 64:
                    col = 0
                    cout('\n')


if __name__ == "__main__":
    import sys
    import os.path
    import __builtin__

    sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))

    import premain
    from com import Com
    from utils import s2hex, hexdump
    import time

    try:
        Application().run()
    except KeyboardInterrupt:
        cout("\n")
    except Exception, e:
        cerr(str(e)+'\n')
