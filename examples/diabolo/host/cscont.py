
import serial
from com import Com
from device import Device
from utils import s2hex, hexdump

import struct
import time


class CsCont( Device ):

    def __init__ ( self, com ):
        Device.__init__(self, com)
        self.ref = 0
        self.crc = 0


    #  Establish the communication with the device
    #
    #    The controller can be in any status among:
    #      - scanning (sends "P..." lines)
    #      - idle (sends '\n' chars, i.e. "" lines repeatedly)
    #      - in Diabolo waiting for synchronization
    #      - in Diabolo waiting for command
    #      - in undeterminable state 8-(
    #
    def connect(self):

        # RTS (reset) is asserted as the com is opened
        # Release it and let Diabolo enough time to start the application
        #
        # self.com.setRTS(False)
        # time.sleep(0.1)

        #  Listen for 1 second to what the controller sends
        #
        try:
            t = time.time() + 1.0
            nl = 0
            while time.time() <= t:
                r = self.com.readline()
                if r == '\n':
                    nl += 1
                    if nl == 2:		#  Two consecutive '\n'
                        return True
                elif r != '':
                    nl = 0
                    if r.startswith("P"):
                        self.com.tx("S\n")	#  Stop any pending scanning
        except serial.serialutil.SerialException:
            cerr(_("Can not read or write from device.\n"))
            # self.com.close()
            return False


    #  Get the controller identifier, this will give the CRC required to
    #  launch Diabolo
    #
    def identify ( self ):

        self.com.tx("I\n")
        r = self.com.readline()
        if len(r)<9 or not r.startswith('I'):
            # cerr(_("Bad controller answer: \"%s\"\n" % r))
            return False

        self.ref = int(r[3:5]+r[1:3], 16)
        self.crc = int(r[5:9], 16)

        return True


    #  Have the controller launch its Diabolo
    #
    def diabolo ( self ):
        s = "#%04X\n" % self.crc
        self.com.tx(s)
        r = self.com.readline()
        return r == s
