#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2015-02-11 17:43:59 -*-


import sys
import os.path

from com import Com
from utils import s2hex, hexdump
import time

from crc_ccitt import CRC
from device import Device
from cscont import CsCont
from csmod import CsMod
from parse import get_args


#  Load a file
#
def read_file(filename):
    if not os.path.isfile(filename):
        die(_("File %s does not exist.\n" % filename))
    if not filename.endswith('.bin'):
        die(_("File format not handled."))
    f = open(filename, 'rb')
    data = f.read()
    f.close()
    if len(data)==0:
        cout(_("%s is void.\n" % filename))
    else:
        cout(_("Loaded %d bytes from %s.\n" % (len(data), filename)))
    return data


#  Write a binary file
#
def write_file(filename, data):
    f = open(filename, 'wb')
    f.write(data)
    f.close()
    cout(_("Stored %d bytes into %s.\n" % (len(data), filename)))


#  Get the device object
#
def get_device(options):
    #
    #  Open the communication interface
    #
    if options.carspy >= 0:
        options.bps = 230400
    com = Com(options.tty, options.bps, options.wires)
    cout(_("Interface: %s (%d bps)\n" % (options.tty, options.bps)))
    #
    #  Reach proper device
    #
    if options.carspy==-1:
        cout(_("Standard device\n"))
        device = Device(com)
        device.reset_signal = options.reset
        device.reset_length = options.reset_length
        return device
    #
    #  Carspy controller or module
    #
    device = CsCont(com)
    if not device.connect():
        cout(_("  No carspy controller found. Already running Diabolo?\n\n"))
        device = Device(com)
        if options.carspy > 0:
            return device
    else:
        cout(_("  Found Carspy controller: "))
        if not device.identify():
            die(_("could not identify!\n"))
        cout(_("reference %04X, firmware %04X\n" % (device.ref, device.crc)))
        if options.carspy == 0:
            if not device.diabolo():
                die(_("    Could not launch Diabolo!\n"))
            cout(_("    Diabolo launched.\n\n"))
            device = Device(com)
        else:
            device = CsMod(com, options.carspy)
            if not device.connect():
                cout(_("    Carspy module %d not found. Already running Diabolo?\n\n"
                       % options.carspy))
                # return
            else:
                cout(_("    Found Carspy module %d:" % options.carspy))
                cout(_("reference %04X, firmware %04X\n" % (device.ref, device.crc)))
                if not device.diabolo():
                    die(_("      Could not launch Diabolo!\n"))
                cout(_("      Diabolo launched.\n\n"))
    return device


#  Compute application CRC and length of application code
#
#    The CRC is computed from the end to the beginning of the memory, skipping
#    the 0xFF bytes at the end.
#
#    For devices without boot section, 'end' should be 1 so that the first two
#    bytes of reset vector (rjmp to Diabolo) are not computed.
#
def appstat ( data, bootsection ):
    crc = CRC.init()
    if not bootsection:
        end = 1
    else:
        end = -1
    for x in range(len(data)-1, end, -1):
        if data[x] != '\xFF':
            break
    for i in range(x, end, -1):
        crc = CRC.add(crc, data[i])
    return crc, x+1


class Diabolo:
    def __init__(self, options):
        self.options = options
        self.device = None
        self.mcu = None

    #  Read flash memory
    #
    def read_flash(self):
        t = time.time()
        cout("\nReading flash:")
        s=''
        vp = '\xFF'*self.device.pagesize
        col=0
        for a in range(0, self.device.flashsize, self.device.pagesize):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            if a < self.device.bladdr or self.options.full:
                p = self.device.read_flash_page(a)
                if p == None:
                    cerr(_("\nRead page failed at 0x%04X.\n" % a))
                    return False
            if a < self.device.bladdr:
                if (a != 0 and p != vp) or (a == 0 and p[2:] != vp[2:]):
                    cout('X')
                else:
                    cout('.')
            else:
                if self.options.full:
                    cout('*')
                else:
                    cout('-')
                    p = vp		# Do not store Diabolo code in cache file
            flushout()
            s += p
        t = time.time()-t
        crc, x = appstat(s[:self.device.bladdr],self.device.bootsection)
        cout(_("\nRead %d bytes in %d ms (%d Bps): %d application bytes, CRC=0x%04X.\n"
               % (len(s), t*1000, len(s)/t, x, crc)))
        return s


    #  Write flash memory
    #
    def write_flash(self, data, cache):
        t = time.time()
        pg = 0
        col = 0
        redo = []
        errors = 0
        cout("\nProgramming flash:")
        for a in range(0, self.device.bladdr, self.device.pagesize):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            if cache \
               and data[a:a+self.device.pagesize] != cache[a:a+self.device.pagesize]:
                r = self.device.write_flash_page(a, data[a:a+self.device.pagesize])
                if r == 'T':
                    cout(_(" Timeout!\n"))
                    return
                if r == 'P':
                    redo.append(a)
                if r != '-':
                    pg += 1
                if r == 'L':
                    cerr(self.device.error+'\n')
            else:
                r = '-'
            cout(r)
            flushout()
        cout("\n")
        #
        #  Reprogram pages that failed
        #
        pv = '\xFF'*self.device.pagesize
        for a in redo:
            cout("\n")
            cout("Need to reprogram page at 0x%04X.\n" % a)
            p1 = data[a:a+self.device.pagesize]
            cout("To be programmed:\n%s\n" % hexdump(a, p1))
            p0 = self.device.read_flash_page(a)
            if p0 != pv:
                r = self.device.write_flash_page(a, pv)
                cout("Erasing: %s\n" % r )
                p0 = self.device.read_flash_page(a)
                if p0 != pv:
                    cerr("Erasing failed.\n")
                    return
            if p0 != p1:
                r = self.device.write_flash_page(a, p1)
                cout("Programming: %s\n" % r )
                p0 = self.device.read_flash_page(a)
                if p0 != p1:
                    cerr(_("Contains:\n%s\n" % hexdump(a, p0)))
                    die("Programming failed.\n")
            cout("\n")

        #cout("\n")
        t = time.time()-t
        if pg:
            cout(_("Programmed %d pages (%d bytes) in %d ms (%d Bps).\n" %\
                   (pg, pg*self.device.pagesize, t*1000, pg*self.device.pagesize/t)))
        cout("\n")


    #  Read eeprom memory
    #
    def read_eeprom(self):
        t = time.time()
        cout("\nReading EEPROM:")
        s=''
        col=0
        for a in range(0, self.device.eepromsize, 64):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            p = self.device.read_eeprom(a,64)
            if p == None:
                cerr(_("\nRead failed at 0x%04X.\n" % a))
                return False
            cout('.')
            flushout()
            s += p
        t = time.time()-t
        cout(_("\nRead %d bytes in %d ms (%d Bps).\n" % (len(s), t*1000, len(s)/t)))
        return s


    def run(self):
        flash = None			# Data to burn into flash

        start_time = time.time()

        #  Compute a CRC?
        #
        if self.options.crc:
            if not self.options.filename:
                die(_("Input file is required for CRC computation.\n"))
            if not self.options.mcu:
                die(_("Target device is required for CRC computation.\n"))
            device = None
            for d in Device.dtbl:
                if d[0].lower() == self.options.mcu.lower():
                    device = d
            if not device:
                die(_("Unrecognized device name.\n"));

            data = read_file(self.options.filename)
            crc, x = appstat(data, d[5])
            cout(_("%s: %d /%d application bytes, CRC=0x%04X.\n" %
                   (self.options.filename, x, len(data), crc)))
            return

        #  Get the proper device
        #
        self.device = get_device(self.options)

        #  Just reset the device and quit?
        #
        if self.options.reset_and_quit:
            self.device.reset()
            return

        #  Connect to the device
        #
        if not self.device.connect():
            die(_("Could not connect.\n"))
        cout(_("Connected to device \n"))

        #  Get Diabolo prompt
        #
        if not self.device.get_prompt():
            die(_("Could not get prompt: %s.\n" % self.device.error))

        #  Identify device
        #
        if not self.device.identify():
            die(_("Could not identify: %s.\n" % self.device.error))

        #  Display device informations
        #
        # display(device)
        cout("Device identification:\n")
        cout(_("  Protocol: %d\n" % self.device.protocol))
        cout(_("  Signature: %s \"%s\"\n" %
               (self.device.signature, self.device.name)))
        cout(_("  Bootloader: 0x%04X (%d bytes for application)\n" %
               (self.device.bladdr, self.device.bladdr)))
        cout(_("  Fuses ext byte: 0x%02X\n" % ord(self.device.fuses[2])))
        cout(_("  Fuses high byte: 0x%02X\n" % ord(self.device.fuses[3])))
        cout(_("  Fuses low byte: 0x%02X\n" % ord(self.device.fuses[0])))
        cout(_("  Fuses lock bits: 0x%02X\n" % ord(self.device.fuses[1])))
        cout(_("  Application CRC:\n"))
        cout(_("    computed: 0x%04X\n" % self.device.appcrc))
        cout(_("      stored: 0x%04X\n" % self.device.eeappcrc))
        if self.device.protocol < 3:
            cout(_("      status: %02X\n" % self.device.appstat))
        cout(_("  Programmings: %d\n" % self.device.pgmcount))

        if not self.device.protocol in [2,3,4]:
            die(_("\nProtocol not supported\n"))

        #  Check target name
        #
        if self.options.mcu and self.device.name.lower() != self.options.mcu.lower():
            die(_("Target mismatch: connected to %s, %s expected.\n" %
                  (self.device.name, self.options.mcu)))

        #  Read flash memory?
        #
        if self.options.read_flash:
            data = self.read_flash()
            if self.options.hexdump:
                cout(hexdump(0,data)+"\n")
            if self.options.cache:
                write_file(self.options.cache, data)
            #return

        #  Read eeprom memory?
        #
        if self.options.read_eeprom:
            data = self.read_eeprom()
            if self.options.hexdump:
                cout(hexdump(0,data)+"\n")
            if self.options.cache:
                write_file(self.options.cache, data)
            #return

        #  Erase flash memory?
        #
        if self.options.clear_flash:
            flash = '\xFF'*self.device.flashsize

        #  Write flash memory?
        #
        if self.options.burn_flash:
            if not self.options.filename:
                die(_("Input file is required to program flash memory.\n"))
            cache = None
            if self.options.cache:
                if os.path.isfile(self.options.cache):
                    cache = read_file(self.options.cache)
                    cache_crc, x = appstat(cache[:self.device.bladdr],
                                                self.device.bootsection)
                    if self.device.appcrc != cache_crc:
                        cout(_("Cache CRC does not match device CRC. Dropping cache data.\n"))
                        cache = None
                else:
                    cout(_("Cache file does not exist yet, reading flash"
                           " memory is required.\n"))
            if cache == None:
                cache = self.read_flash()
            cache_crc, x = appstat(cache[:self.device.bladdr],
                                        self.device.bootsection)
            flash = read_file(self.options.filename)

        #  Program flash memory
        #
        if flash:
            #
            #  Override RESET vector for device without bootsection
            #    RJMP opcode: 1111 aaaa aaaa aaaa = 0xC000 + Addr
            #
            if not self.device.bootsection:
                addr = self.device.bladdr/2 - 1
                if addr > 0x0FFF:
                    die(_("Can not set RESET vector opcode.\n"))
                opcode = 0xC000 + addr
                byte0 = opcode & 0xFF
                byte1 = opcode >> 8
                cout(_("Device without bootsection, "
                       "changed RESET vector opcode: %02x %02x\n")
                     % (byte0, byte1))
                flash = chr(byte0)+chr(byte1)+flash[2:]

            flash_crc, x = appstat(flash[:self.device.bladdr],
                                       self.device.bootsection)
            if flash_crc == cache_crc:
                cout(_("Cache and data CRC match. Nothing to do.\n"))
            else:
                self.write_flash(flash,cache)

            x_restart = False
            if self.device.flash_changed:
                self.device.write_eeprom_pgmcount(self.device.pgmcount+1)
                cout(_("Set program count to %d\n" % self.device.pgmcount))
                x_restart = True

            if self.device.eeappcrc != flash_crc:
                self.device.write_eeprom_appcrc(flash_crc)
                cout(_("Set stored application CRC to 0x%04X\n" % flash_crc))
                x_restart = True

            if x_restart:
                #cout(_("Reset device's Diabolo\n"))
                self.device.tx('!') # Send a bad command to force CRC re-computation
                self.device.get_prompt()
                self.device.identify()
                cout("  Application CRC:\n")
                cout(_("    computed: 0x%04X\n" % self.device.appcrc))
                cout(_("      stored: 0x%04X\n" % self.device.eeappcrc))
                cout(_("  Programmings: %d\n" % self.device.pgmcount))

            #  Update flash cache
            #
            if self.options.cache:
                write_file(self.options.cache, flash)

        #  Start application
        #
        if self.device.appcrc == self.device.eeappcrc \
           and self.device.appcrc != 0xFFFF:
            #
            #  FIXME: with --read-flash --hexdump, device.run fails.
            #         device.identify makes it succeed. Why?
            #
            self.device.identify()
            if self.device.run():
                cout("Application started.\n")
            else:
                cout("Run failed.\n")

        self.device.com.close()
        cout(_("%d commands, %d fails, %d resumes, %d resyncs, total time: %.1f s.\n" % 
               (self.device.ncmds, self.device.ncmdfails, self.device.nresumes,
                self.device.nresyncs, time.time()-start_time+0.05)))


if __name__ == "__main__":
    import premain
    try:
        options = get_args()
        #print options
        Diabolo(options).run()
    except KeyboardInterrupt:
        cout("\n")
