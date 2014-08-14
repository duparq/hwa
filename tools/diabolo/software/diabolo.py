#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2014-08-14 12:15:40 -*-


import struct
# import com
from com import Com
from utils import s2hex, hexdump
import time

from crc_ccitt import CRC
from device import Device
from cscont import CsCont
from csmod import CsMod


def parse_options():
    from optparse import OptionParser
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEV", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com device (default /dev/ttyUSB0)")
    parser.add_option("-b", "--bps", metavar="BPS", type="int",
                      default=115200, dest="combps", 
                      help="set com speed (default 115200)")
    parser.add_option("-1", "--one-wire", action="store_true",
                      default=True, dest="onewire",
                      help="RX/TX on the same communication wire")
    parser.add_option("-2", "--two-wires", action="store_false",
                      default=True, dest="onewire",
                      help="RX/TX on separate communication wires")
    parser.add_option("-m", "--mcu", metavar="MCU", type="string",
                      default=None, dest="mcu",
                      help="target microcontroller")
    parser.add_option("--read-flash", action="store_true",
                      default=False, dest="read_flash",
                      help="Force reading of flash memory")
    parser.add_option("--full", action="store_true",
                      default=False, dest="full",
                      help="process full content (include bootloader code)")
    parser.add_option("--hexdump", action="store_true",
                      default=False, dest="hexdump",
                      help="Hexdump read content")
    parser.add_option("--flash-file", metavar="FILE", type="string",
                      default=None, dest="flash_file",
                      help="binary or hex file to burn into flash")
    parser.add_option("--flash-cache", metavar="FILE", type="string",
                      dest="flash_cache",
                      help="binary file used to store flash content")
    parser.add_option("-F", "--erase-flash", action="store_true",
                      default=False, dest="erase_flash",
                      help="Erase flash memory")
    # parser.add_option("-x", "--run", metavar="FILE", type="string",
    #                   dest="run_cmd",
    #                   help="command to start when the 'run' button is pressed")
    parser.add_option("--carspy", metavar="MODULE", type="int", default=-1,
                      dest="carspy",
                      help="address (0..30) of Carspy module to access (0 for carspy controller)")
    parser.add_option("-c", "--crc", action="store_true",
                      default=False, dest="crc",
                      help="compute firmware crc")
    parser.add_option("-r", "--reset-only", action="store_true",
                      default=False, dest="reset",
                      help="reset the device with RTS and exit")
    (options, args) = parser.parse_args()
    if len(args) == 1:
        options.flash_file = args[0]
    return options


#  Open the communication device
#    Return the com device if OK, None otherwise
#
def open_com(options):
    # trace()

    # import os, stat
    # if stat.S_ISFIFO(os.stat(self.options.comdev).st_mode):
    #     cout( "File: %s is a FIFO\n" % self.options.comdev )
    # elif stat.S_ISSOCK(os.stat(self.options.comdev).st_mode):
    #     cout( "File: %s is a SOCKET\n" % self.options.comdev )

    com = Com( options.comdev, options.combps )
    # if com == None:
    #     cerr(_("Can not get serial port\n"))
    #     return None

    try:
        com.open()
    except ValueError:
        cerr(_("Value error\n"))
    if not com.is_open():
        cerr(_("Can not open serial port\n"))
        return None

    com.onewire = options.onewire
    #com.set_timeout( max( 0.01, 20.0/options.combps) )
    #com.setTimeout( 40.0/options.combps )
    return com


#  Application CRC and length
#
#    The CRC is computed from the end to the beginning of the memory, skipping
#    the 0xFF bytes at the end and the first 2 bytes (jump to diabolo).
#
def appstat ( data ):
    crc = CRC.init()
    for x in range(len(data)-1, -1, -1):
        if data[x] != '\xFF':
            break
    for i in range(x, 1, -1):
        crc = CRC.add(crc, data[i])
    # x += 1
    x -= 1
    return crc, x


def run():
    import os.path

    pdata = None
    options = parse_options()

    #  Load file to burn into flash if any
    #
    if options.flash_file:
        if not os.path.isfile(options.flash_file):
            cerr(_("File %s does not exist.\n" % options.flash_file))
            return
        if not options.flash_file.endswith('.bin'):
            cerr(_("File format not handled."))
            return

        f = open(options.flash_file, 'rb')
        pdata = f.read()
        f.close()

        pdata_crc, x = appstat(pdata)
        cout(_("%s: %d / %d bytes for application, CRC=0x%04X.\n" %
               (options.flash_file, x+2, len(pdata), pdata_crc)))

    #  Stop here if just for CRC
    #
    if options.crc:
        return

    #  Open the communication interface
    #
    if options.carspy >= 0:
        options.combps = 230400
    com = open_com(options)
    if not com:
        cout(_("Could not open %s\n" % options.comdev))
        return
    cout(_("Interface: %s (%d bps)\n" % (options.comdev, options.combps)))

    #  Only reset the device ?
    #
    if options.reset:
        # com.set_RTS(True)
        com.set_DTR(True)
        time.sleep(0.01)
        # com.set_RTS(False)
        com.set_DTR(False)
        return

    #  Reach proper device
    #
    if options.carspy >= 0:
        options.combps = 230400
        device = CsCont(com)
        if not device.connect():
            cout(_("  No carspy controller found. Already running Diabolo?\n\n"))
            device = Device(com)
            if options.carspy > 0:
                return
        else:
            cout(_("  Found Carspy controller: "))
            if not device.identify():
                cout(_("could not identify!\n"))
                return
            cout(_("reference %04X, firmware %04X\n" % (device.ref, device.crc)))
            if options.carspy == 0:
                if not device.diabolo():
                    cout(_("    Could not launch Diabolo!\n"))
                    return
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
                        cout(_("      Could not launch Diabolo!\n"))
                        return
                    cout(_("      Diabolo launched.\n\n"))
    else:
        cout(_("Standard device\n"))
        device = Device(com)
        if not device.connect():
            cerr(_("Could not connect.\n"))
            return
        cout(_("Connected to device \n"))

    #  Get Diabolo prompt
    #
    if not device.get_prompt():
        cerr(_("Could not get prompt: %s.\n" % device.error))
        return

    #  Identify device
    #
    if not device.identify():
        cerr(_("Could not identify: %s.\n" % device.error))
        return

    #  Display device informations
    #
    # display(device)
    cout("Device identification:\n")
    cout(_("  Protocol: %d\n" % device.protocol))
    cout(_("  Signature: %s \"%s\"\n" % (device.signature, device.name)))
    cout(_("  Bootloader: 0x%04X (%d bytes for application)\n" % (device.bladdr, device.bladdr)))
    cout(_("  Fuses low byte: 0x%02X\n" % ord(device.fuses[0])))
    cout(_("  Fuses high byte: 0x%02X\n" % ord(device.fuses[3])))
    cout(_("  Fuses ext byte: 0x%02X\n" % ord(device.fuses[2])))
    cout(_("  Fuses lock bits: 0x%02X\n" % ord(device.fuses[1])))

    cout("  Application CRC:\n")
    cout(_("    computed: 0x%04X\n" % device.appcrc))
    cout(_("      EEPROM: 0x%04X\n" % device.eeappcrc))
    if device.protocol < 3:
        cout(_("      status: %02X\n" % device.appstat))
    cout(_("  Programmings: %d\n" % device.pgmcount))

    if not device.protocol in [2,3]:
        cout(_("\nProtocol not supported\n"))
        return

    #  Check target
    #
    if options.mcu:
        if device.name.lower() != options.mcu.lower():
            cerr(_("Target mismatch: connected to %s, %s expected.\n" %
                   (device.name, options.mcu)))
            return

    #  Load cache for flash data if wanted
    #
    flash_cache = None
    if options.flash_cache:
        if os.path.isfile(options.flash_cache):
            if not options.flash_cache.endswith('.bin'):
                cerr(_("File format not handled."))
                return
            f = open(options.flash_cache, 'rb')
            flash_cache = f.read()
            f.close()

            crc, x = appstat(flash_cache[:device.bladdr])
            cout(_("Loaded %d bytes of flash memory from %s (%d application bytes), CRC=0x%04X.\n"
                   % (len(flash_cache), options.flash_cache, x-2, crc)))
        else:
            options.read_flash = True

    #  Read flash memory if needed
    #
    if options.read_flash:
        t = time.time()
        cout("\nReading flash:")
        s=''
        vp = '\xFF'*device.pagesize
        col=0
        if options.full:
        # if options.hexdump_fullflash:
            end=device.flashsize
        else:
            end=device.bladdr
        for a in range(0, end, device.pagesize):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            p = device.read_flash_page(a)
            if p == None:
                cerr(_("\nRead page failed at 0x%04X.\n" % a))
                return False
            if a < device.bladdr:
                if (a != 0 and p != vp) or (a == 0 and p[2:] != vp[2:]):
                    cout('X')
                else:
                    cout('.')
            else:
                cout('-')
                if not options.full:
                    p = vp		# Do not store Diabolo code in cache file
            flushout()
            s += p
        device.flash = s
        t = time.time()-t
        crc, x = appstat(device.flash[:device.bladdr])
        cout(_("\nRead %d bytes in %d ms (%d Bps): %d application bytes, CRC=0x%04X.\n"
               % (len(device.flash), t*1000, len(device.flash)/t, x, crc)))

        if crc != device.appcrc:
            cout(_("Application CRC mismatch!\n"))
            return

        if options.flash_cache:
            flash_cache = device.flash

        if options.hexdump:
            cout(hexdump(0,device.flash)+"\n")
    else:
        device.flash = flash_cache

    #  Erase flash
    #
    if options.erase_flash:
        if pdata:
            cerr(_("Can not erase flash when data are to be burned!\n"))
            return
        pdata = '\xFF'*device.flashsize
        pdata_crc = 0xFFFF
        # cout("\nErasing flash:\n")
        # for a in range(0, device.bladdr, device.pagesize):
        #     r = device.write_flash_page(a, '\xFF'*device.pagesize)
        #     if r == 'T':
        #         cout(_("Timeout\n"))
        #         return
        #     cout(r)
        #     flushout()
        # cout("\n\n")

    #  Perform programming
    #
    if pdata:
        t = time.time()
        pg = 0
        col = 0
        redo = []
        errors = 0
        cout("\nProgramming flash:")
        for a in range(0, device.bladdr, device.pagesize):
            if col==0 :
                cout('\n')
            col += 1
            if col==64:
                col=0
            r = device.write_flash_page(a, pdata[a:a+device.pagesize])
            if r == 'T':
                cout(_("Timeout\n"))
                return
            if r == 'P':
                redo.append(a)
            if r != '-':
                pg += 1
            if r == 'L':
                cerr(device.error+'\n')
            cout(r)
            flushout()
        cout("\n")
        #
        #  Reprogram pages that failed
        #
        for a in redo:
            cout("\n")
            cout("Need to reprogram page at 0x%04X.\n" % a)
            cout("Contains:\n%s\n" % hexdump(a, device.read_flash_page(a)))
            cout("To be programmed:\n%s\n" % hexdump(a, pdata[a:a+device.pagesize]))
            cout("Erasing: %s\n" % device.write_flash_page(a, '\xFF'*device.pagesize) )
            cout("Contains:\n%s\n" % hexdump(a, device.read_flash_page(a)))
            cout("Programming: %s\n" % device.write_flash_page(a, pdata[a:a+device.pagesize]) )
            cout("Contains:\n%s\n" % hexdump(a, device.read_flash_page(a)))
            cout("\n")

        #cout("\n")
        t = time.time()-t
        if pg:
            cout(_("Programmed %d pages (%d bytes) in %d ms (%d Bps).\n" %\
                   (pg, pg*device.pagesize, t*1000, pg*device.pagesize/t)))
        cout("\n")

        x_restart = False
        if device.flash_changed:
            #trace()
            device.write_eeprom_pgmcount(device.pgmcount+1)
            cout(_("Set program count to %d\n" % device.pgmcount))
            #crc, x = appstat(pdata)
            x_restart = True

        if device.eeappcrc != pdata_crc:
        #if device.flash_changed or device.eeappcrc != crc:
            #trace()
            device.write_eeprom_appcrc(pdata_crc)
            cout(_("Set EEPROM application CRC to 0x%04X\n" % pdata_crc))
            x_restart = True

        if x_restart:
            cout(_("Reset device's Diabolo\n"))
            device.tx('!') # Force CRC computation
            time.sleep(0.2)
            device.tx('\n')
            #device.rx(1)
            device.get_prompt()
            device.identify()
            # device.display()
            cout("  Application CRC:\n")
            cout(_("    computed: 0x%04X\n" % device.appcrc))
            cout(_("      EEPROM: 0x%04X\n" % device.eeappcrc))
            cout(_("  Programmings: %d\n" % device.pgmcount))

    #  Update cache
    #
    if options.flash_cache and flash_cache:
        f = open(options.flash_cache, 'wb')
        f.write(flash_cache)
        f.close()
        cout(_("Stored %d bytes of flash cache into %s.\n"
               % (len(flash_cache), options.flash_cache)))

    #  Start application
    #
    if device.appcrc == device.eeappcrc and \
            device.appcrc != 0xFFFF:
        if device.run():
            cout("Device launched its application\n")
        else:
            cout("Run failed.\n")

    com.close()
    cout(_("%d commands, %d fails, %d resumes, %d resyncs\n" % 
           (device.ncmds, device.ncmdfails, device.nresumes, device.nresyncs)))


if __name__ == "__main__":
    # from premain import *
    import premain
    try:
        run()
    except KeyboardInterrupt:
        cout("\n")
