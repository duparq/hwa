
# -*- coding: utf-8 -*- 

class Device():
    def __init__(self, name, signature, pagesize, flashsize, eepromsize, bootsection):
        self.name=name
        self.signature=signature
        self.pagesize=pagesize
        self.flashsize=flashsize
        self.eepromsize=eepromsize
        self.bootsection=bootsection

        self.bladdr = None
        self.fuses = None
        self.appcrc = None
        self.eeappcrc = None
        self.appstat = None
        self.pgmcount = None

    def identify(self):
        """
        Display device informations
        """
        s =  _("  Signature: %s \"%s\"\n" % (self.signature, self.name))
        s += _("  Bootloader: 0x%04X (%d bytes for application)\n" % (self.bladdr, self.bladdr))
        s += self.s_fuses()
        s += _("  Application CRC:\n")
        s += _("    computed: 0x%04X\n" % self.appcrc)
        s += _("      stored: 0x%04X\n" % self.eeappcrc)
        if self.appstat is not None:
            s += _("      status: %02X\n" % self.appstat)
        s += _("  Programmings: %d\n" % self.pgmcount)
        return s

    def s_fuses(self):
        """
        Display fuses
        """
        return self.s_fuse_eb()+self.s_fuse_hb()+self.s_fuse_lb()+self.s_fuse_lk()

    def s_fuse_eb(self):
        return _("  Fuses ext byte: 0x%02X\n" % ord(self.fuses[2]))

    def s_fuse_hb(self):
        return _("  Fuses high byte: 0x%02X\n" % ord(self.fuses[3]))

    def s_fuse_lb(self):
        return _("  Fuses low byte: 0x%02X\n" % ord(self.fuses[0]))

    def s_fuse_lk(self):
        return _("  Fuses lock bits: 0x%02X\n" % ord(self.fuses[1]))



class ATtiny44(Device):
    def __init__(self):
        Device.__init__(self,'ATtiny44','1E9207',64,4096,256,False)

class ATtiny84(Device):
    def __init__(self):
        Device.__init__(self,'ATtiny84','1E930C',64,8192,512,False)

class ATtiny45(Device):
    def __init__(self):
        Device.__init__(self,'ATtiny45','1E9206',64,4096,256,False)

class ATtiny85(Device):
    def __init__(self):
        Device.__init__(self,'ATtiny85','1E930B',64,8192,512,False)

class ATmega48(Device):
    def __init__(self):
        Device.__init__(self,'ATmega48','1E9205',64,4096,256,False)

class ATmega48P(Device):
    def __init__(self):
        Device.__init__(self,'ATmega48P','1E920A',64,4096,256,False)

import atmega328p

devices = { '1E9207': ATtiny44,
            '1E9205': ATtiny45,
            '1E930C': ATtiny84,
            '1E930B': ATtiny85,
            '1E9205': ATmega48,
            '1E920A': ATmega48P,
            '1E950F': atmega328p.device
}


def get(signature):
    return devices[signature]()
