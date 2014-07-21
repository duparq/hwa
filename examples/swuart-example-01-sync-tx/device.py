
from com import Com
from utils import s2hex, hexdump

import struct
import time


def dbg(s):
    #cout(s)
    pass


class Device:

    #  Create the new device
    #
    def __init__(self, com):
        self.com = com			# Serial communication channel
        self.lastchar = ''
        self.nresyncs  = 0
        self.nresumes  = 0
        # self.ncmdfails = 0
        # self.ncmds     = 0


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


    #  Atmel devices need about 20 cycles to compute the CRC between each
    #  received byte
    #
    def tx ( self, data ):
        for d in data:
            self.com.tx(d)
            time.sleep(0.000005)


    def txbrk ( self ):
        self.com.brk10()

    #  Establish the communication with the device
    #
    def rem_connect(self):
        # RTS (reset) is asserted as the com is opened
        self.com.set_RTS(True)		# Assert the RESET pin
        time.sleep(0.01)
        self.com.set_RTS(False)		# Release RESET
        return self.get_prompt()

    def connect(self):
        # DTR (reset) is asserted as the com is opened
        self.com.set_DTR(True)		# Assert the RESET pin
        time.sleep(0.01)
        self.com.set_DTR(False)		# Release RESET
        return self.get_prompt()

    #  Get the prompt
    #
    def get_prompt(self):
        #trace()

        #  Resume from error
        #
        if self.lastchar == '!':
            self.nresumes += 1
            self.tx('\n')
            self.rx(1)

        if self.lastchar == '#':
            return True

        #  Resynchronize
        #
        self.nresyncs += 1
        self.com.flush()

        for i in range(64):
            if i%2 == 0:
                self.txbrk()
            else:
                self.tx('\xFF')
            r = self.rx(1)
            # if r: trace(s2hex(r))
            if r.endswith('!'):
                self.tx('\n')
                r = self.rx(1)
            if r.endswith('#'):
                return True

        cerr(_("Device did not synchronize.\n"))
        return False
