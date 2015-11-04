#!/usr/bin/env python
# -*- coding: utf-8 -*-

    #  Atmel devices can need up to 50 cycles (~6.25 µs @ 8MHz) to process the
    #  first received byte and 30 cycles to process the followings. This must be
    #  done between the sampling of the stop bit and the next start condition,
    #  i.e. in 1.5 bit time since the CRC computation begins after sampling the
    #  last data bit.
    #
    #  At 115200 bps, the elapsed time between the middle of the last data bit
    #  and the next start bit is 13 µs. That should be enough.
    #
    #  It seems that pyserial's `interCharTimeout` is not implemented.
    #
    #  Adding one stop bit could also do the job but reconfiguring the serial
    #  port takes much more time than a small sleep.

import sys
import os.path

sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../../python"))

import premain
import __builtin__

from utils import hexdump

from crc_ccitt import CRC

import struct
import time
import devices
import xserial


class Application:
    def __init__(self, options):
        self.options = options
        self.mcu = None
        self.serial = None
        self.device = None
        self.curaddr = -1		# Current memory address

    #  Read a binary file
    #
    def read_file(self, filename):
        if not os.path.isfile(filename):
            die(_("File %s does not exist.\n" % filename))
        if not filename.endswith('.bin'):
            die(_("File format not handled."))
        f = open(filename, 'rb')
        data = f.read()
        f.close()
        if not self.options.quiet and len(data)==0:
            cout(_("%s is void.\n" % filename))
        else:
            cout(_("Loaded %d bytes from %s.\n" % (len(data), filename)))
        return data


    #  Write a binary file
    #
    def write_file(self, filename, data):
        f = open(filename, 'wb')
        f.write(data)
        f.close()
        cout(_("Stored %d bytes into %s.\n" % (len(data), filename)))


    #  Read flash memory
    #
    def read_flash(self):
        t = timer()
        cout("\nReading flash:")
        s=''
        if self.device.protocol == 4:
            vp = '\xFF'*self.device.pagesize
        else: # protocol 5
            vp = '\xFF'*256
        col=0
        for a in range(0, self.device.flashsize, len(vp)):
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
        t = timer()-t
        # crc, x = appstat(s[:self.device.bladdr], self.device.bootsection)
        x, crc = self.device.appstat(s)
        cout(_("\nRead %d bytes in %d ms (%d Bps): %d application bytes, CRC=0x%04X.\n"
               % (len(s), t*1000, len(s)/t, x, crc)))
        return s


    #  Write flash memory
    #
    def write_flash(self, data, cache):
        t = timer()
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
                if r == 'C':
                    cout(_(" CRC! "))
                    redo.append(a)
                elif r == 'T':
                    cout(_(" Timeout!\n"))
                    return
                elif r == 'P': # should be '!'
                    redo.append(a)
                elif r == 'L':
                    redo.append(a)
                    # cerr(self.device.error+'\n')
                elif r == '!':
                    redo.append(a)
                if r != '-':
                    pg += 1
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
        t = timer()-t
        if pg:
            cout(_("Programmed %d pages (%d bytes) in %d ms (%d Bps).\n" %\
                   (pg, pg*self.device.pagesize, t*1000, pg*self.device.pagesize/t)))
        cout("\n")


    #  Read eeprom memory
    #
    def read_eeprom(self):
        t = timer()
        cout("\nReading EEPROM:")
        s=''
        col=0
        for a in range(0, self.device.eepromsize, 64):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            p = self.device.read_eeprom_bytes(a,64)
            if p == None:
                cerr(_("\nRead failed at 0x%04X.\n" % a))
                return False
            cout('.')
            flushout()
            s += p
        t = timer()-t
        cout(_("\nRead %d bytes in %d ms (%d Bps).\n" % (len(s), t*1000, len(s)/t)))
        return s


    def run(self):
        flash = None			# Data to burn into flash

        start_time = timer()

        #  Compute a CRC?
        #
        if self.options.stat or self.options.crc or self.options.size:
            if not self.options.filename:
                die(_("Input file is required for CRC computation.\n"))
            if not self.options.mcu:
                die(_("Target device is required for CRC computation.\n"))

            try:
                self.device = devices.devices[self.options.mcu.lower()]()
            except:
                die(_("\"%s\": no such device.\n" % self.options.mcu.lower()));

            data = self.read_file(self.options.filename)
            x, crc = self.device.appstat(data)
            if self.options.stat:
                #
                #  Use sys.stdout.write instead of cout to bypass '--quiet'
                #
                sys.stdout.write(_("%s: %d /%d application bytes, CRC=0x%04X.\n" %
                                   (self.options.filename, x, len(data), crc)))
            elif self.options.crc:
                sys.stdout.write("%04X\n" % crc )
            else:
                sys.stdout.write("%d\n" % x )
            return


        #  Compute a CRC32?
        #
        if self.options.crc32:
            if not self.options.filename:
                die(_("Input file is required for CRC32 computation.\n"))

            import binascii
            s = open(self.options.filename,'rb').read()
            crc32 = binascii.crc32(s)
            sys.stdout.write("%08x\n" % (crc32 & 0xFFFFFFFF))
            return

        #  List available ttys?
        #
        if self.options.tty == "list":
            ttys = xserial.list()
            cout(_("Available ttys:\n" + str(ttys)))
            return

        #  Open the communication channel
        #
        try:
            self.xserial = xserial.get_serial(self.options)
            # if self.options.threaded_timed:
            #     self.xserial = xserial.ThreadedTimed(self.options)
            # elif self.options.threaded_event:
            #     self.xserial = xserial.ThreadedEvent(self.options)
            # else:
            #     self.xserial = xserial.XSerial(self.options)
        except xserial.serial.SerialException, e:
            die(str(e))

        #  Reset the device connected to the serial interface
        #
        self.xserial.reset_device()

        #  Just reset the device and quit?
        #
        if self.options.reset_and_exit:
            return

        #  This is the best moment for detecting how many wires are used for the
        #  serial communication
        #
        self.xserial.detect_wires()

        #  We can now send synchronization sequences
        #
        try:
            self.xserial.sync()
        except Exception, e:
            die(_("Synchronization failed."))

        #  Identify device
        #
        self.device = devices.get_device(self.xserial)
        cout(_("Connected to device (protocol %d):\n" % self.device.protocol))
        cout(self.device.str(self.options.show_fuses, self.options.decode_fuses))

        #  Check target name
        #
        if self.options.mcu and self.device.name.lower() != self.options.mcu.lower():
            die(_("Target mismatch: connected to %s, %s expected.\n" %
                  (self.device.name, self.options.mcu)))

        #  Compute the CRC of the firmware?
        #
        if self.options.fwcrc:
            cout("\nReading firmware flash: ")
            data=''
            if self.device.protocol == 4:
                l = self.device.pagesize
            else: # protocol 5
                l = 256
            data = '\xFF'*self.device.bladdr
            # data = '\xFF'*l
            for a in range(self.device.bladdr, self.device.flashsize, l):
                p = self.device.read_flash_page(a)
                if p == None:
                    cerr(_("\nRead page failed at 0x%04X.\n" % a))
                    return False
                cout('.')
                flushout()
                data += p

            #  Compute the CRC
            #
            crc = CRC.init()
            i = len(data)-1
            while i>=0 and data[i]=='\xFF':
                i -= 1
            while i>=0:
                crc = CRC.add(crc, data[i])
                i -= 1

            # x, crc = self.device.appstat(data)
            cout(_("\nRead %d bytes of firmware, CRC=0x%04X.\n"
                   % (len(data), crc)))
            return


        #  Read flash memory?
        #
        if self.options.read_flash:
            data = self.read_flash()
            if self.options.hexdump:
                sys.stdout.write(hexdump(0,data)+"\n")
            if self.options.cache:
                self.write_file(self.options.cache, data)
            #return

        #  Read eeprom memory?
        #
        if self.options.read_eeprom:
            data = self.read_eeprom()
            if self.options.hexdump:
                sys.stdout.write(hexdump(0,data)+"\n")
            if self.options.cache:
                self.write_file(self.options.cache, data)
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
                    cache = self.read_file(self.options.cache)
                    if len(cache)<self.device.bladdr:
                        cout(_("Wrong cache size. Dropping cache data.\n"))
                        cache = None
                    else:
                        x, cache_crc = self.device.appstat(cache)
                        if self.device.appcrc != cache_crc:
                            cout(_("Cache CRC (%04X) does not match device CRC. "\
                                   "Dropping cache data.\n" % cache_crc))
                            cache = None
                else:
                    cout(_("Cache file does not exist yet, reading flash"
                           " memory is required.\n"))
            if cache == None:
                cache = self.read_flash()
                if self.options.cache:
                    self.write_file(self.options.cache, cache)

            x, cache_crc = self.device.appstat(cache)
            flash = self.read_file(self.options.filename)
            if len(flash) < self.device.bladdr:
                cout(_("Padding data with 0xFF bytes\n"))
                flash = flash + "\xFF"*(self.device.bladdr - len(flash))

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
                       "setting RESET vector to computed opcode: %02x %02x\n")
                     % (byte0, byte1))
                flash = chr(byte0)+chr(byte1)+flash[2:]

            x, flash_crc = self.device.appstat(flash)
            if flash_crc == cache_crc:
                cout(_("Cache and data CRC match, nothing to program in Flash memory.\n"))
                if self.device.eeappcrc != flash_crc:
                    self.device.write_eeprom_appcrc(flash_crc)
                    cout(_("Updated application CRC in EEPROM: 0x%04X\n" % flash_crc))
                x_restart = True
            else:
                self.write_flash(flash,cache)

            x_restart = False
            if self.device.flash_changed:
                # trace()
                self.device.write_eeprom_pgmcount(self.device.pgmcount+1)
                cout(_("Set program count to %d\n" % self.device.pgmcount))
                x_restart = True

            if self.device.eeappcrc != flash_crc:
                # trace()
                self.device.write_eeprom_appcrc(flash_crc)
                cout(_("Stored application CRC in EEPROM: 0x%04X\n" % flash_crc))
                x_restart = True

            if x_restart:
                # trace()
                #cout(_("Reset device's Diabolo\n"))
                self.device.resume()
                self.xserial.tx('*') # Send a bad command to force CRC re-computation
                #
                #  Wait up to 1 s for CRC computation (~50 cycles/byte)
                #
                t = timer()+1.0
                while timer() < t and not self.xserial.rx(1): pass
                if timer() >= t:
                    raise Exception("timeout waiting CRC recomputation")
                if self.xserial.lastchar != '!':
                    raise Exception("unexpected reply (0x%02X) to '*' command" % ord(c))
                self.xserial.tx('\n') # Resume
                self.xserial.rx(1)
                self.device = self.device.identify()
                cout("  Application CRC:\n")
                cout(_("    computed: 0x%04X\n" % self.device.appcrc))
                cout(_("      EEPROM: 0x%04X\n" % self.device.eeappcrc))
                cout(_("  Programmings: %d\n" % self.device.pgmcount))
                        

            #  Update flash cache
            #
            if self.options.cache:
                # trace()
                self.write_file(self.options.cache, flash)

        #  Start application
        #
        if self.device.appcrc == self.device.eeappcrc \
           and self.device.appcrc != 0xFFFF:
            if self.device.start_application():
                cout("Target started its application.\n")
            else:
                cout("ERROR: target did not start its application.\n")

        self.xserial.close()

        if self.options.diag:
            cout(_("%d commands, %d fails, %d resumes, %d crc errors, total time: %.1f s.\n" % 
                   (self.device.ncmds, self.device.ncmdfails, self.device.nresumes,
                    self.device.ncrcerrors, timer()-start_time+0.05)))


#  Create command line arguments parser
#
import argparse
parser = argparse.ArgumentParser()

#  Arguments about serial port
#
xserial.add_arguments(parser)

#  Target options
#
parser.add_argument('-m', '--mcu', help="target device")

#  Actions
#
group = parser.add_mutually_exclusive_group()
group.add_argument('-x', '--reset-and-exit',
                   help="only reset the device, do not try to connect.",
                   action='store_true')
group.add_argument('--stat', help="size and CRC of the application",
                   action='store_true')
group.add_argument('-c', '--crc', help="CRC of the application",
                   action='store_true')
group.add_argument('-s', '--size', help="size of the application",
                   action='store_true')
group.add_argument('--crc32', help="CRC32 of file", action='store_true')
group.add_argument('--fwcrc', help="CRC of Diabolo firmware", action='store_true')
group.add_argument('--read-flash', help="read flash memory", action='store_true')
group.add_argument('--burn-flash', help="burn flash memory", action='store_true')
group.add_argument('--clear-flash', help="clear flash memory", action='store_true')
group.add_argument('--verify-flash', help="verify flash memory", action='store_true')

group.add_argument('--read-eeprom', help="read eeprom memory", action='store_true')
group.add_argument('--burn-eeprom', help="burn eeprom memory", action='store_true')
group.add_argument('--clear-eeprom', help="clear eeprom memory", action='store_true')
group.add_argument('--verify-eeprom', help="verify eeprom memory", action='store_true')

#  Options
#
parser.add_argument('--cache', help="name of cache file")
parser.add_argument('--full', help="read full content (Diabolo code included)",
                    action='store_true')
parser.add_argument('--hexdump', help="hexdump content", action='store_true')

parser.add_argument('-q', '--quiet', help="do not write on standard output "
                    "if not necessary", action='store_true')
parser.add_argument('--diag', help="display diagnostic values",
                    action='store_true')
parser.add_argument('--debug', help="print debugging messages",
                    action='store_true')
parser.add_argument('--show-fuses', help="show fuse values", action='store_true')
parser.add_argument('--decode-fuses', help="decode fuse values", action='store_true')


#  Files
#
parser.add_argument('filename', nargs='?')

args = parser.parse_args()

if args.quiet:
    __builtin__.__dict__['cout'] = id

if args.debug:
    __builtin__.__dict__['dbg'] = cout

enable_trace()

Application(args).run()
