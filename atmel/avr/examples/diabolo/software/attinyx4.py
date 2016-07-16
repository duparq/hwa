
# -*- coding: utf-8 -*- 

import devices

class attinyx4(devices.Device):

    def s_fuse_eb(self, fuses):
        fuse = ord(fuses[2])
        s_selfprgen = { 0: "enabled", 1: "disabled" }
        selfprgen = fuse & 0x01
        s =  _("  Fuses ext byte: 0x%02X\n" % fuse)
        s += _("    SELFPRGEN:          %s\n" % s_selfprgen[selfprgen])
        return s

    def s_fuse_hb(self, fuses):
        fuse = ord(fuses[3])
        rstdsbl = (fuse & 0x80)>>7
        dwen    = (fuse & 0x40)>>6
        spien   = (fuse & 0x20)>>5
        wdton   = (fuse & 0x10)>>4
        eesave  = (fuse & 0x08)>>3
        bod     = (fuse & 0x07)

        s_rstdsbl = { 0: "disabled", 1: "enabled" }
        s_dwen = { 0: "enabled", 1: "disabled" }
        s_spien = { 0: "enabled", 1: "disabled" }
        s_wdton = { 0: "yes", 1: "no" }
        s_eesave = { 0: "yes", 1: "no" }
        s_bod = { 4: "4100_4500mV", 5: "2500_2900mV", 6: "1700_2000mV", 7: "off" }

        s =  _("  Fuses high byte: 0x%02X\n" % fuse)
        s += _("    EXTERNAL_RESET:     %s\n" % s_rstdsbl[rstdsbl])
        s += _("    DEBUG_WIRE:         %s\n" % s_dwen[dwen])
        s += _("    SERIAL_PROGRAMMING: %s\n" % s_spien[spien])
        s += _("    WATCHDOG_ALWAYS_ON: %s\n" % s_wdton[wdton])
        s += _("    PRESERVE_EEPROM:    %s\n" % s_eesave[eesave])
        s += _("    BODLEVEL:           %s\n" % s_bod[bod])
        return s

    def s_fuse_lb(self, fuses):
        fuse = ord(fuses[0])
        ckdiv8  = (fuse & 0x80)>>7 ; s_ckdiv8 = { 0: "8", 1: "1" }
        ckout   = (fuse & 0x40)>>6 ; s_ckout = { 0: "enabled", 1: "disabled" }
        sut     = (fuse & 0x30)>>4 ; 
        cksel31 = (fuse & 0x0E)>>1
        cksel0  = (fuse & 0x01)
        cksel   = (fuse & 0x0F)
        xsut = (cksel0<<2) + sut

        s_ckhz = None

        if cksel == 0:
            s_cksel = "external"
            s_xsut = { 0: "6CK_14CK",
                       1: "6CK_14CK_4ms",
                       2: "6CK_14CK_64ms" }
        elif cksel == 2:
            s_cksel = "rc_8MHz"
            s_xsut = { 0: "6CK_14CK",
                       1: "6CK_14CK_4ms",
                       2: "6CK_14CK_64ms" }
        elif cksel == 4:
            s_cksel = "rc_128kHz"
            s_xsut = { 0: "6CK_14CK",
                       1: "6CK_14CK_4ms",
                       2: "6CK_14CK_64ms" }
        elif cksel == 6:
            s_cksel = "low_freq_xosc"
            s_xsut = { 0: "1KCK_4ms",
                       1: "1KCK_64ms",
                       2: "32KCK_64ms" }
        else:
            s_cksel = "xosc"
            if cksel31 == 4:
                s_ckhz = "400..900 kHz"
            elif cksel31 == 5:
                s_ckhz = "0.9..3 MHz"
            elif cksel31 == 6:
                s_ckhz = "3..8 MHz"
            elif cksel31 == 7:
                s_ckhz = "8..16 MHz"
            s_xsut = { 0: "258CK_14CK_4ms",
                       1: "258CK_14CK_64ms",
                       2: "1KCK_14CK",
                       3: "1KCK_14CK_4ms",
                       4: "1KCK_14CK_64ms",
                       5: "16KCK_14CK",
                       6: "16KCK_14CK_4ms",
                       7: "16KCK_14CK_64ms" }

        s =  _("  Fuses low byte: 0x%02X\n" % fuse)
        s += _("    CLK_PSC:            %s\n" % s_ckdiv8[ckdiv8])
        s += _("    CLK_SRC:            %s\n" % s_cksel)
        if s_ckhz:
            s += _("    CLK_SRC_HZ      %s\n" % s_ckhz)
        s += _("    STARTUP_DELAYS:     %s\n" % s_xsut[xsut])
        return s

    def s_fuse_lk(self, fuses):
        fuse = ord(fuses[1])
        lbx   = (fuse & 0x03)
        s_lbx = { 0: "no_program_no_verify "\
                  "(Programming and verification of Flash and EEPROM are "\
                  "disabled, and Boot Lock bits and fuse bits are locked in "\
                  "parallel and serial programming mode.)",
                  2: "no_program "\
                  "(Programming and verfication of Flash and EEPROM are "\
                  "disabled, and fuse bits are locked in "\
                  "parallel and serial programming mode.)",
                  3: "no_locking"  }

        s =  _("  Fuses lock bits: 0x%02X\n" % fuse)
        s += _("    MEMORY_LOCK:        %s\n" % s_lbx[lbx] )
        return s


class attiny44(attinyx4):
    def __init__(self):
        attinyx4.__init__(self,'ATtiny44','1E9207',64,4096,512,False)

devices.devices["attiny44"] = attiny44
devices.devices["attiny44a"] = attiny44
devices.devices['1E9207'] = attiny44

class attiny84(attinyx4):
    def __init__(self):
        attinyx4.__init__(self,'ATtiny84','1E930C',64,8192,512,False)

devices.devices["attiny84"] = attiny84
devices.devices["attiny84a"] = attiny84
devices.devices['1E930C'] = attiny84
