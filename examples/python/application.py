#!/usr/bin/env python
# -*- coding: utf-8 -*-

import com
import time


class Application:
    """
    This is a base for the applications provided with the examples
    """
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
        self.parser = parser
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

    #  Synchronize UART with 5/1 low-level sequences
    #
    def sync_5_1(self):
        cout("SYNC 5/1: ")
        self.nresyncs += 1
        while self.com.rx(1): pass # flush
        for i in range(64):
            cout('.')
            flushout()
            self.tx('A')
            r = self.rx(1)
            if len(r):
                cout(' OK (0x%02X) after %d bytes sent.\n' % (ord(r[0]), i+1))
                return r[0]
        cout(' FAILED after %d bytes sent.\n' % (i+1))
        return False

    #  Establish communication
    #
    def connect(self, sync):
        #
        #  Open the communication
        #
        self.com = com.Com(self.options.tty, self.options.bps, self.options.wires)
        cout(_("Interface: %s (%d bps)\n" % (self.options.tty, self.options.bps)))

        #  Reset the device
        #
        #    This is the moment to detect how many wires are used for
        #    communication
        #
        cout(_("Resetting device with signal %s low for %.2f s.\n" %
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
        while self.com.rx(1): pass # flush
        prompt = sync()
        if not prompt:
            die(_("Could not synchronize.\n"))
        return prompt

    def get_prompt(self, p):
        to = time.time()+0.5
        while time.time() < to:
            if self.lastchar == p:
                return True
            self.tx('\n')
            self.rx(1)
        return False
