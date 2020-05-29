
# -*- coding: utf-8 -*- 

from crc_ccitt import CRC
import struct
from utils import hexdump


class Device():
    def __init__(self, name, signature, pagesize, flashsize, eepromsize, bootsection):
        self.name=name
        self.signature=signature
        self.pagesize=pagesize
        self.flashsize=flashsize
        self.eepromsize=eepromsize
        self.bootsection=bootsection

        #self.flash = None		# Flash memory content
        self.bladdr = self.flashsize	# For CRC computation
        self.blpages = None
        self.fuses = None
        self.appcrc = None
        self.eeappcrc = None
        self.pgmcount = None

        self.protocol   = 0		# Bootloader protocol
        self.nresumes   = 0
        self.ncmdfails  = 0
        self.ncrcerrors = 0
        self.ncmds      = 0
        self.flash_changed = False	# Need to change CRC in EEPROM if true

    def str(self, show_fuses=False, decode_fuses=False):
        """
        Build device informations string.
        """
        s =  _("  Signature: %s \"%s\"\n" % (self.signature.hex(), self.name))
        s += _("  Bootloader: 0x%04X (%d bytes for application)\n" % (self.bladdr, self.bladdr))
        s += _("  Application CRC:\n")
        s += _("    computed: 0x%04X\n" % self.appcrc)
        s += _("      EEPROM: 0x%04X\n" % self.eeappcrc)
        s += _("  Programmings: %d\n" % self.pgmcount)
        if decode_fuses:
            s += self.s_fuses(self.fuses)
        elif show_fuses:
            s += _("  Fuses ext byte: 0x%02X\n" % ord(self.fuses[2]))
            s += _("  Fuses high byte: 0x%02X\n" % ord(self.fuses[3]))
            s += _("  Fuses low byte: 0x%02X\n" % ord(self.fuses[0]))
            s += _("  Fuses lock bits: 0x%02X\n" % ord(self.fuses[1]))
        return s

    def s_fuses(self, fuses):
        """
        Display fuses
        """
        return self.s_fuse_eb(fuses)+self.s_fuse_hb(fuses) \
            +self.s_fuse_lb(fuses)+self.s_fuse_lk(fuses)

    def s_fuse_eb(self, fuses):
        return _("  Fuses ext byte: 0x%02X\n" % ord(fuses[2]))

    def s_fuse_hb(self, fuses):
        return _("  Fuses high byte: 0x%02X\n" % ord(fuses[3]))

    def s_fuse_lb(self, fuses):
        return _("  Fuses low byte: 0x%02X\n" % ord(fuses[0]))

    def s_fuse_lk(self, fuses):
        return _("  Fuses lock bits: 0x%02X\n" % ord(fuses[1]))


    def appstat(self, data):
        """
        Compute length of application code and CRC.

        The CRC is computed from the end to the beginning of the memory, skipping
        the 0xFF bytes at the end.

        For devices without boot section the first two bytes of reset vector
        (rjmp to Diabolo) are not computed.

        """
        crc = CRC.init()
        if not self.bootsection:
            end = 1
        else:
            end = -1

        top = min( len(data), self.bladdr )-1
        for x in range(top, end, -1):
            if data[x] != 0xFF:
                break
        for i in range(x, end, -1):
            crc = CRC.add(crc, data[i])
        return x+1, crc

    #  Get the prompt
    #
    #    The device can be waiting for a bunch of bytes to complete a
    #    command. 256 bytes should be enough to get a reply.
    #
    def resume(self):
        for i in range(256):
            if self.link.lastchar == ord('#'):
                return True
            if self.link.lastchar == ord('!'):
                self.nresumes += 1
                self.link.lastchar=None # lastchar is not set by self.link.rx(1) if there is no reply
            self.link.tx(b'\n')
            r = self.link.rx(1)
            if len(r):
                dbg("RESUME: tx('\\n') -> %s (0x%02X)\n" % (r,ord(r)))
            else:
                dbg("RESUME: tx('\\n') -> no reply\n")
        die(_("Could not get prompt.\n"))


    def execute ( self, cmdstr, rlen, repeats=4, **kwargs ):
        """
        Send a command, wait for rlen reply bytes.
        If rlen > 2, check the CRC of the reply.
        Return the reply without the CRC nor the prompt.

        A void reply for the 'write_flash_page' command can mean that the
        inter-char delay is not sufficient and the device has not enough time to
        compute the CRC.

        Repeated CRC errors can mean that the device estimated the baudrate not
        accurately enough.
        """
        dbg("EXECUTE(%s,%d,%d,%s)\n" % (cmdstr.hex(), rlen, repeats, repr(kwargs)))
        built = None
        crcerrors = 0
        for repeat in range(repeats):
            # if repeat>0:
            #     trace()
            self.resume()
            self.link.lastchar=None
            dbg("EXECUTE: tx(0x%s) -> " % (cmdstr.hex()))
            self.link.tx(cmdstr)
            self.ncmds += 1
            if rlen == 0:
                return None

            if 'timeout' in kwargs:
                #
                #  Wait for a reply until timeout
                #
                r=bytearray()
                t=timer()+kwargs['timeout']
                while len(r) < rlen and timer() < t:
                    c=self.link.rx(1)
                    if c:
                        t=timer()+kwargs['timeout']
                        r.extend(c)
                #     if r!= "":
                #         break
                # if r=="":
                #     for i in range(256):
                #         self.com.tx('\n')
                #         c = self.com.rx(1)
                #         if c=='!':
                #             dbg("Sent %d \\n\n" % (i+1))
                #             break
                #     # raise Exception("\nCOMMAND FAIL: [%s] -> [%s]\n" % (s2hex(cmdstr), s2hex(r)))
                # else:
                #     # r += self.com.rx(rlen-1)
                #     prev=timer()
                #     while len(r)<rlen and timer() < t:
                #         r += self.com.rx(1)
                #         last=timer()
                #         if last-prev > 0.001:
                #             trace()
                #         prev=last
                        
            else:
                r = self.link.rx(rlen)

            if r:
                dbg("%s\n" % r.hex())
            else:
                dbg("no reply\n")

            if self.link.lastchar != ord('#'):
                dbg("  COMMAND FAILED\n")
                self.ncmdfails += 1
                continue

            r = r[:-1]
            if rlen <= 2:
                return r
            else:
                crc = CRC.check(cmdstr+r)
                if crc == 0:
                    if built:
                        dbg("\nBUILT REPLY:  %s:" % built.hex())
                        for i in range(rlen-1):
                            if built[i] != r[i]:
                                dbg(" #%d" % i)
                        dbg("\nGOOD REPLY:   %s\n\n" % r.hex())
                    return r[:-2]
                dbg("  CRC ERROR: 0x%04X\n" % crc)
                #
                #  CRC error, try to correct it.
                #
                #  Bytes are transfered least significant bit
                #  first. Inaccurate synchronization of the device can lead
                #  to the last transmitted bit (msb) of bytes to be
                #  defective:
                #
                #   * If the device estimated the baudrate a little too
                #     high, the host can sample the stop bit (1) instead of
                #     the msb. This leads to an error only if the original
                #     msb is 0, then it is corrected by setting the msb back
                #     to 0. Only bytes whose received msb is high are
                #     concerned.
                #
                #   * If the device estimated the baudrate a little too low,
                #     the host can sample bit b6 instead of the msb. This
                #     leads to an error only if the original b6 and b7 (msb)
                #     are different, then it is corrected by setting b7 to
                #     the opposite of b6.
                #

                crcerrors += 1
                self.ncrcerrors += 1

                if len(r) != rlen-1:
                    # dbg("  BAD REPLY #%d: %s\n" % (repeat,s2hex(r)))
                    continue

                if not built:
                    #
                    #  Display a rule to make finding bytes easier
                    #
                    dbg("\n             ")
                    for i in range(rlen-1):
                        dbg(" %02d" % i)
                dbg("  BAD REPLY #%d: %s\n" % (repeat,r.hex()))

                updated = False
                if not built:
                    built = r
                    updated = True
                else:
                    #
                    #  Try to build the correct frame with bytes whose b7,b6
                    #  bits are different
                    #
                    positions=[]
                    for p in range(rlen-1):
                        if ( (built[p] & 0xC0) == 0xC0
                             or (built[p] & 0xC0) == 0x00 )\
                             and r[p] != built[p]:
                            positions.append(p)
                            built = built[:p] + r[p] + built[p+1:]
                            dbg(" #%d" % p)
                            updated = True
                    if updated:
                        # dbg("\nUPDATED BYTES:")
                        # for p in positions:
                        #     dbg(" #%d" % p)
                        if CRC.check(cmdstr+built) == 0:
                            dbg("\nFRAME FULLY CORRECTED\n\n")
                            return built[:-2]
                        dbg("\n")

                #  Device a little too low?
                #  Try setting b7 to the opposite of b6
                #
                if updated:
                    for p in range(rlen-1):
                        old = built[p]
                        if (old & 0xC0) == 0x00 or (old & 0xC0) == 0xC0:
                            new = old ^ 0x80
                            x = built[:p] + new + built[p+1:]
                            crc = CRC.check(cmdstr+x)
                            if crc == 0:
                                dbg("\nbyte #%d has been corrected "
                                    "from %02X to %02X\n" % (p,old,new))
                                return x[:-2]

        # s = "\nCOMMAND [%s] FAILED." % s2hex(cmdstr)
        if len(cmdstr) > 8:
            s = "\nCOMMAND [%s ... %s] (%d bytes) FAILED." \
                % (cmdstr[:4].hex(), cmdstr[-2:].hex(), len(cmdstr))
        else:
            s = "\nCOMMAND [%s] FAILED." % cmdstr.hex()
        if crcerrors > 3:
            s += _("\nMany CRC unrecoverable errors detected. Your baudrate setting (%d) "\
                   "may be too high for the device.\n" % self.link.serial.baudrate)
        die(s)


    def identify(self):
        """
        Identify the device.
        """
        r = self.execute(b'i', 1000)
        #trace("i: %s\n" % s2hex(r))
        self.protocol = r[0]

        if self.protocol != 4 and self.protocol != 5:
            die(_('protocol #%d not supported' % self.protocol))

        signature=r[1:4]

        try:
            device = devices[signature]()
        except KeyError:
            die(_("Unknown device with signature %s" % signature))

        device.link = self.link
        device.protocol = self.protocol
        device.blpages = r[4]
        device.bladdr = device.flashsize-device.blpages*device.pagesize
        device.appcrc = int.from_bytes(r[5:7], byteorder='big')
        device.fuses = r[7:11]

        device.eeappcrc = device.read_eeprom_appcrc()
        if device.eeappcrc is None:
            raise Exception(_('could not get EEPROM application CRC'))

        device.pgmcount = device.read_eeprom_pgmcount()
        if device.pgmcount is None:
            raise Exception(_('could not get EEPROM programmings count'))

        if device.pgmcount == 0xFFFFFFFF:
            device.pgmcount = 0

        return device


    def read_flash_page(self, address):
        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = bytes([ord('f'),al,ah])
        if self.protocol == 4:
            return self.execute(s, self.pagesize+2+1, timeout=0.5)
        else: # protocol 5
            return self.execute(s, 256+2+1, timeout=0.5)

    def read_eeprom_bytes(self, address, n):
        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = bytes([ord('e'),al,ah,n])
        return self.execute( s, n+3 )

    def read_eeprom_appcrc(self):
        crc = self.read_eeprom_bytes( self.eepromsize-8, 2 )
        crc = int.from_bytes(crc[0:2], byteorder='big')
        return crc


    def read_eeprom_pgmcount(self):
        pcount = self.read_eeprom_bytes( self.eepromsize-4, 4 )
        pcount = int.from_bytes(pcount[0:4], byteorder='big')
        return pcount

    def write_flash_page(self, address, data):
        if address >= self.bladdr:
            return 'A'

        if address % self.pagesize != 0:
            return 'A'

        if len(data) != self.pagesize:
            dbg(_('got %d bytes of data for flash page write, expected %d' %
                  (len(data), self.pagesize)))
            return 'L'

        #  Do not write a page known to be left unchanged
        #
        # if self.flash and self.flash[address:address+self.pagesize] == data:
        #     return '-'

        ah = (address >>  8) & 0xFF
        al = address & 0xFF
        s = bytearray([ord('F'),al,ah])+data
        crc = CRC.check(s)
        s += crc.to_bytes(2, byteorder='big')
        x = self.execute(s, 1+1, 1, timeout=0.1)[0]
        if x & 0xF0 == 0:
            #
            #  No error, update the known content of the flash
            #
            # if self.flash:
            #     self.flash = self.flash[:address] \
            #         + data \
            #         + self.flash[address+self.pagesize:]
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
        #trace("\nError code: %02X in programming flash page at 0x%04X" % (x,address))
        if x == 0x80:
            return 'C'		# CRC error
        if x & 0x10:
            return '!'		# Programming failed
        return '<%02X>' % x	# Unknown error


    def write_eeprom(self, address, data):
        if len(data)==0 or len(data)>255:
            die()
        s = bytearray(b'E')
        s.extend( address.to_bytes(2,byteorder='little') )
        s.append(len(data))
        s.extend(data)
        s.extend( CRC.check(s).to_bytes(2, byteorder='big') )
        self.execute(s, 1, timeout=0.1)

    def write_eeprom_pgmcount(self, n):
        self.write_eeprom( self.eepromsize-4, n.to_bytes(4,byteorder='big'))
        self.pgmcount = n


    def write_eeprom_appcrc(self, crc):
        enable_trace()
        self.write_eeprom( self.eepromsize-8, crc.to_bytes(2,byteorder='big'))
        self.eeappcrc = crc


    def start_application(self):
        self.resume()
        self.ncmds += 1
        s = bytearray(b'X')
        s.extend( CRC.check(b'X').to_bytes(2,byteorder='big') )
        self.link.tx(s) # execute would read more than 1 byte
        r = self.link.rx(1)
        return r[0]==0


def get_device(link):
    """
    Return a device object corresponding to the one the serial
    interface is connected to.
    """
    device = Device("",0,0,0,0,0)
    device.link = link
    return device.identify()


#  Import devices (will populate the devices dictionnary)
#
devices = {}
import attinyx4
import attinyx5
import atmegax8
import atmegaxu4
