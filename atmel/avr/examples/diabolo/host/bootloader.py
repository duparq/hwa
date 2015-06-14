
from com import Com
from crc_ccitt import CRC
from utils import s2hex, hexdump

import struct
import time
import devices


def dbg(s):
    cout(s)
    pass


def cmdwithcrc ( s ):
    crc = CRC.check(s)
    return s + struct.pack('>H', crc)


class Diabolo:

    #  Create the new device
    #
    def __init__(self, com):
        self.com = com			# Serial communication channel
        self.error = ""
        self.lastchar = ''
        self.nresyncs  = 0
        self.nresumes  = 0
        self.ncmdfails = 0
        self.ncmds     = 0

        self.device = None

        self.protocol = 0		# Bootloader protocol
        self.bladdr = 0			# Bootloader address
        self.curaddr = -1		# Current memory address
        self.appcrc = None		# Application CRC (computed)
        self.eeappcrc = None		# Application CRC (in EEPROM)
        self.appstat = None		# Application status (0 is OK)
        self.fuses = None		# Fuses
        self.pgmcount = None		# Programming count
        self.flash = None		# Flash memory content
        self.flash_changed = False	# Need to change CRC in EEPROM if true

        self.reset_signal = 'DTR'	# TTY signal used to reset the target
        self.reset_length = 0.01	# Reset pulse duration


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


    #  Atmel devices need about 50 cycles to compute the CRC between each
    #  received byte
    #
    def tx ( self, data ):
        self.lastchar=None
        for d in data:
            self.com.tx(d)
            time.sleep(0.000005)


    def txbrk ( self ):
        self.com.brk()


    def set_reset(self, state):
        if self.reset_signal == "dtr":
            self.com.set_DTR(state)
        elif self.reset_signal == "rts":
            self.com.set_RTS(state)
        else:
            raise Exception("No signal to drive reset.")


    #  Reset the device
    #  Note: DTR is asserted as the com is opened
    #
    def reset(self):
        cout(_("Resetting device using signal %s for %.2f s.\n" %
               (self.reset_signal.upper(), self.reset_length)))
        self.set_reset(True)
        time.sleep(self.reset_length)
        self.set_reset(False)


    #  Establish the communication with the device
    #    Pull TX down by sending a break
    #    Reset the device
    #    Keep TX down to force the device to stay in Diabolo after reset
    #    Flush the RX buffer:
    #      RX is not pulled-up while reset is asserted through RTS/DTR. This
    #      causes reception of weird bytes we need to remove
    #    Detect wires if needed
    #    Get the prompt
    #
    def connect(self):
        self.com.set_BRK(True)
        self.reset()
        time.sleep(0.5)
        self.com.set_BRK(False)
        while self.com.rx(1): pass
        self.com.detect_wires()
        return self.get_prompt()


    #  Get the prompt
    #
    def get_prompt(self):
        # trace()

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
        for i in range(64):
            if i%2 == 0:
                self.txbrk()
            else:
                self.tx('\xFF')
            r = self.rx(0)
            if r.endswith('!'):
                self.tx('\n')
                r = self.rx(0)
            if r.endswith('#'):
                return True
        return False


    #  Send a command, wait for rlen reply bytes
    #
    def execute ( self, cmdstr, rlen ):
        if not self.get_prompt():
            return None
        self.lastchar = None
        #trace('> '+s2hex(cmdstr))
        self.tx(cmdstr)
        r = self.rx(rlen)
        #trace('< '+s2hex(r))
        self.ncmds += 1
        if self.lastchar!='#':
            dbg("CMDFAIL: %s -> %s\n" % (s2hex(cmdstr), s2hex(r)))
            self.ncmdfails += 1
        return r


    #  Device identification
    #
    def identify(self):
        if not self.get_prompt():
            return None

        # Give the device enough time to compute the CRC of application
        #
        t = time.time() + 1.0
        r = ""
        self.lastchar = None
        self.tx('i')
        while time.time() <= t:
            x = self.rx(1)
            if not x and self.lastchar =='#':
                break
            r += x

        if self.lastchar != '#':
            self.error = _('can not decode string \'%s\'' % s2hex(r))
            self.ncmdfails += 1
            return False

        #trace("i: %s\n" % s2hex(r))

        crc = CRC.check('i'+r[:-1])
        if crc != 0:
            self.error = _('CRC = %04X' % crc)
            return False

        self.protocol = ord(r[0])
        if self.protocol < 2 or self.protocol > 4:
            self.error = _('protocol #%d not supported' % self.protocol)
            return False

        signature=s2hex(r[1:4]).replace(' ','') ; r = r[4:]

        self.device = devices.get(signature)
        if not self.device:
            self.error = _("Unknown device with signature %s" % signature)
            return False

        if self.protocol < 4:
            self.device.bladdr = struct.unpack('<H', r[0:2])[0] ; r = r[2:]
        else:
            self.device.blpages = struct.unpack('B', r[0])[0] ; r = r[1:]
            self.device.bladdr = self.device.flashsize-self.device.blpages*self.device.pagesize
        self.device.appcrc = struct.unpack('>H', r[0:2])[0] ; r = r[2:]
        if self.protocol < 3:
            self.device.appstat = ord(r[0])
            self.device.fuses = r[1:5] ; r = r[5:]
        else:
            self.device.fuses = r[0:4] ; r = r[4:]
        self.device.eeappcrc = self.read_eeprom_appcrc()
        if self.device.eeappcrc is None:
            self.error = _('could not get EEPROM application CRC')
            return False
        self.device.pgmcount = self.read_eeprom_pgmcount()
        if self.device.pgmcount is None:
            self.error = _('could not get EEPROM programmings count')
            return False
        if self.device.pgmcount == 0xFFFFFFFF:
            self.device.pgmcount = 0
        return self.device


    def read_flash_page(self, address):
        t = time.time() + 1.0
        while time.time() <= t:
            if self.protocol < 3:
                if self.curaddr != address:
                    self.set_address(address)
                else:
                    r = self.execute('f', self.pagesize+2+1)
                    if len(r)==self.device.pagesize+2+1 and r[-1]=='#':
                        self.curaddr += self.device.pagesize
                        if CRC.check('f'+r[:-1]) == 0:
                            return r[:-3]
                    else:
                        self.curaddr = -1
            else:
                ah = (address >>  8) & 0xFF
                al = address & 0xFF
                s = 'f'+chr(al)+chr(ah)
                r = self.execute(s, self.device.pagesize+2+1)
                if len(r)==self.device.pagesize+2+1 and r[-1]=='#':
                    if CRC.check(s+r[:-1]) == 0:
                        return r[:-3]
        return None


    def read_eeprom(self, address, n):
        t = time.time() + 1.0
        while time.time() <= t:
            if self.protocol < 3:
                if self.curaddr != address:
                    self.set_address(address)
                else:
                    s = 'e'+chr(n)
                    r = self.execute( s, n+3 )
                    if len(r)==n+3 and r[-1]=='#':
                        self.curaddr += n
                        if CRC.check(s+r[:-1]) == 0:
                            return r[0:-3]
                    else:
                        self.curaddr = -1
            else:
                ah = (address >>  8) & 0xFF
                al = address & 0xFF
                s = 'e'+chr(al)+chr(ah)+chr(n)
                r = self.execute( s, n+3 )
                if len(r)==n+3 and r[-1]=='#':
                    if CRC.check(s+r[:-1]) == 0:
                        return r[0:-3]
        return None

    def read_eeprom_appcrc(self):
        crc = self.read_eeprom( self.device.eepromsize-8, 2 )
        if crc != None:
            crc = struct.unpack('>H', crc)[0]
        return crc


    def read_eeprom_pgmcount(self):
        pcount = self.read_eeprom( self.device.eepromsize-4, 4 )
        if pcount != None:
            pcount = struct.unpack('>L', pcount)[0]
        return pcount


    def write_flash_page_p3(self, address, data):
        if len(data) != self.pagesize:
            self.error = _('got %d bytes of data for flash page write, expected %d' %
                           (len(data), self.pagesize))
            return 'L'

        #  Do not write a page known to be left unchanged
        #
        if self.flash:
            if address == 0 and self.flash[2:self.pagesize] == data[2:self.pagesize]:
                return '-'
            if self.flash[address:address+self.pagesize] == data:
                return '-'

        s = 'F'+data
        crc = CRC.check(s)
        s += struct.pack('>H', crc)

        t = time.time() + 1.0
        while time.time() < t:
            if self.set_address(address):
                #self.resume()
                if not self.get_prompt():
                    return False
                self.tx(s)
                # print len(s), ": ", s2hex(s)
                # self.push_timeout(0.2)
                r = self.rx(2)
                # self.pop_timeout()
                # print s2hex(r)
                if r and len(r)==2 and r[-1]=='#':
                    x = ord(r[-2])
                    if x & 0xF0 == 0:
                        #
                        #  Update the known content of the flash
                        #
                        if self.flash:
                            self.flash = self.flash[:address] \
                                + data \
                                + self.flash[address+self.pagesize:]
                        #     flash = self.flash[:address]
                        # elif address == 0:
                        #     flash = ''
                        # flash += data
                        # if self.flash:
                        #     flash += self.flash[address+self.pagesize:]
                        # self.flash = flash

                        if x == 0x00:
                            return '-'	# Unchanged
                        self.flash_changed = True
                        if x == 3:
                            return 'W'	# Erased + Programmed
                        if x == 1:
                            return 'e'	# Erased
                        if x == 2:
                            return 'w'	# Programmed
                    trace("Code: %02X" % x)
                    if x == 0x80:
                        # self.curaddr = None
                        return 'C'		# CRC error
                    if x == 0x40:
                        # self.curaddr = None
                        return 'A'		# Address error
                    if x == 0x11:
                        return 'E'		# Erase error
                    if x == 0x12 or x == 0x13 :
                        self.flash_changed = True
                        return 'P'		# Write error
                    return '<%02X>' % x	# Unknown error
                #trace(s2hex(s+r))
            # self.error=_('write_flash_page: failed at 0x%04X.' % self.curaddr)
        trace("Timeout")
        return 'T'

    def write_flash_page(self, address, data):
        if self.protocol < 4:
            return self.write_flash_page_p3(address, data)

        if address >= self.bladdr:
            return 'A'

        if address % self.pagesize != 0:
            return 'A'

        if len(data) != self.pagesize:
            self.error = _('got %d bytes of data for flash page write, expected %d' %
                           (len(data), self.pagesize))
            return 'L'

        #  Do not write a page known to be left unchanged
        #
        if self.flash and self.flash[address:address+self.pagesize] == data:
            return '-'

        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = 'F'+chr(al)+chr(ah)+data
        crc = CRC.check(s)
        s += struct.pack('>H', crc)

        t = time.time() + 1.0
        while time.time() < t:
            if 0:
                r = self.execute(s, 1+1)
            else:
                r = ""
                self.ncmds += 1
                if not self.get_prompt():
                    return 'T'
                self.lastchar = None
                self.tx(s)
                while len(r) < 2:
                    r += self.rx(1)
                if self.lastchar!='#':
                    dbg("CMDFAIL: %s -> %s\n" % (s2hex(cmdstr), s2hex(r)))
                    self.ncmdfails += 1

            if len(r)==2 and r[-1]=='#':
                x = ord(r[-2])
                if x & 0xF0 == 0:
                    #
                    #  No error, update the known content of the flash
                    #
                    if self.flash:
                        self.flash = self.flash[:address] \
                            + data \
                            + self.flash[address+self.pagesize:]
                    #
                    #  Return a code of what has been done
                    #
                    self.flash_changed = True
                    if x == 0x01:
                        return '*'	# Erased
                    if x == 0x02:
                        return 'w'	# Programmed
                    if x == 0x03:
                        return 'W'	# Erased + Programmed
                trace("\nError code: %02X in programming flash page at 0x%04X" %
                      (x,address))
                if x == 0x80:
                    return 'C'		# CRC error
                if x & 0x10:
                    return '!'		# Programming failed
                return '<%02X>' % x	# Unknown error
        trace("Timeout")
        return 'T'


    def write_eeprom_p3(self, address, data):
        s = 'E'+chr(len(data))+data
        crc = CRC.check(s)
        s += struct.pack('>H', crc)

        t = time.time() + 1.0
        while time.time() <= t:
            if self.set_address(address):
                self.tx(s)
                time.sleep(0.2)
                r = self.rx(2)
                if r == '\x03#':
                    return True
                    # len(r)==2 and r[-1]=='#':
                    # if ord(r[-2]) == 0x03:
                    #     return True
        return False
        # self.error = _('write_eeprom: failed at 0x%04X.' % self.curaddr)


    def rem_write_eeprom(self, address, data):
        if len(data)==0 or len(data)>255:
            return '!'
        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = 'E'+chr(al)+chr(ah)+chr(len(data))+data
        crc = CRC.check(s)
        s += struct.pack('>H', crc)

        t = time.time() + 1.0
        while time.time() < t:
            r = self.execute(s, 1)
            if len(r)==1 and r[-1]=='#':
                return ''
        return 'T'


    def write_eeprom(self, address, data):
        if len(data)==0 or len(data)>255:
            return '!'
        if not self.get_prompt():
            return False
        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = 'E'+chr(al)+chr(ah)+chr(len(data))+data
        crc = CRC.check(s)
        s += struct.pack('>H', crc)
        self.tx(s)
        r = ""
        t = time.time() + 1.0
        while time.time() < t:
            r += self.rx(1)
            if self.lastchar=='#':
                return True
        return False


    def write_eeprom_pgmcount(self, n):
        if self.write_eeprom( self.eepromsize-4, struct.pack('>L', n) ):
            self.pgmcount = n
            return True
        return False


    def write_eeprom_appcrc(self, crc):
        if self.write_eeprom( self.eepromsize-8, struct.pack('>H', crc) ):
            self.eeappcrc = crc
            return True
        return False

    def run(self):
        if not self.get_prompt():
            return False
        self.ncmds += 1
        self.tx('X'+struct.pack('>H', CRC.check('X')))
        self.rx(1)
        return self.lastchar == '\0'
