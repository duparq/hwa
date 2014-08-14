
from com import Com
from device import Device
from utils import s2hex, hexdump

import struct
import time


def CMD_IDENT(x):
    return (x<<3) + 0x00

def CMD_BLDR(x):
    return (x<<3) + 0x07


class CsMod( Device ):

    def __init__ ( self, com, address ):
        Device.__init__(self, com)
        self.address = address
        #self.pending = ""
        self.ref = 0
        self.crc = 0

    def rx(self, n):
        #trace()
        pending = ""
        t = time.time() + self.com.timeout
        #t = time.time() + 0.1
        while True:
            if len(pending)>=n or time.time()>t:
                r = pending
                pending = ""
                if r:
                    self.lastchar = r[-1]
                #cout("RX %d: %d, %s\n" % (n, len(r), s2hex(r)))
                # cout("RX lastchar: %s\n" % self.lastchar)
                return r
            s = self.com.readline()
            if s:
                #cout(">"+s+"\n")
                t = time.time() + self.com.timeout
                if len(s)>=4 and s[0]=='X' and s[3]=='=':
                    #cout("RX ok: %s\n" % s)
                    s = s[4:-1]
                elif len(s)%2==1 and s[-1]=='\n':
                    s = s[:-1]
                elif len(s)%2==0 and s[-1]!='\n':
                    pass
                else:
                    cout("!>%s\n" % s2hex(s))
                    continue
                try:
                    while s:
                        c = chr(int(s[0:2], 16))
                        s = s[2:]
                        pending += c
                    #cout("  PENDING: %s\n" % s2hex(self.pending))
                except ValueError:
                    pass


    #  Send data to the module through the controller
    #
    #    Split the data string into "XHH\n" commands
    #    Check what the controller or the module returned
    #
    def tx(self, s):
        for c in s:
            ss = "X%02X\n" % ord(c)
            self.com.write(ss)
            # trace( repr(ss) )
            #cout("TX %d, %s\n" % (len(ss), s2hex(ss)))


    #  Identify the module
    #
    def connect ( self ):
        # self.pending=""
        # self.com.flush()
        # self.com.flushInput()
        # self.com.flushOutput()
        self.com.tx("XBR\n")
        self.tx( "%c" % chr(CMD_IDENT(self.address)) )
        r = self.rx(100)
        if not r or len(r) < 4:
            return False
        self.ref = struct.unpack('<H', r[0:2])[0]
        self.crc = struct.unpack('<H', r[2:4])[0]
        return True

    def diabolo ( self ):
        # self.pending=""
        # self.com.flush()
        # self.com.flushInput()
        # self.com.flushOutput()
        self.com.tx("XBR\n")
        self.tx("%c%c%c" % (chr(CMD_BLDR(self.address)),
                            chr(self.crc>>8),
                            chr(self.crc & 0xFF)))
        return self.rx(100)==chr(1)
