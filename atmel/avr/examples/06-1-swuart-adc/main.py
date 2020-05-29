#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Display the values sent by the swuart-adc example.

If the command line contains --gfx, display a graphical gauge. Otherwise display
on text console.

If the command line contains --lpf, apply a low-pass filter on received values.
"""

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../../../../python"))

import builtins
import premain
from utils import hexdump
import time

enable_trace()

import link


import argparse
parser = argparse.ArgumentParser()

#  Arguments about serial port
#
link.add_arguments(parser)

parser.add_argument('--lpf', help="low-pass filter on received data", action='store_true')
parser.add_argument('--gfx', help="graphical gauge", action='store_true')

args = parser.parse_args()


if args.gfx:
    #
    #  Try to start a graphical application
    #
    import wx
    import dial

    class Application(wx.App):
        def __init__(self, args):
            self.args = args
            self.serial = serial
            self.lpf = 0
            wx.App.__init__(self, 0)
    
        def run(self):
            # trace()
            self.MainLoop()

        def OnInit(self):
            #self.idle = 0
            frame = wx.Frame(None)
            #self.dial = dial.Dial(frame)
            self.dial = dial.Dial(frame, ranges=(0,1000,100,5), name="ADC")
            self.dial.SetBackgroundColour(wx.BLACK)
            self.SetTopWindow( frame )
            frame.SetMinSize(( 100, 100 ))
            frame.SetSize(( 400, 400 ))

            dbg("DoubleBuffered: %s" % repr(self.dial.IsDoubleBuffered()))
            # frame.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
            dbg("BackgroundStyle == Custom: %s" % \
                repr(self.dial.GetBackgroundStyle()==wx.BG_STYLE_CUSTOM))
#            self.dial.SetBackgroundColour(wx.Colour(0, 0, 0, 0))
            dbg("CanSetTransparent: %s" % repr(self.dial.CanSetTransparent()))

            self.Bind(wx.EVT_TIMER, self.OnTimer)
            self.serial.flush()
            self.timer = wx.Timer(self)

            self.timer = wx.CallLater(20, self.OnTimer)

            frame.Bind(wx.EVT_CLOSE, self.OnClose)
            frame.Show()
            return 1

        def OnTimer(self):
            #
            #  Get device data until nothing has been received for 1 byte time
            #
            r = self.serial.rx_until_idle(1)
            if len(r) < 2:
                self.timer.Restart(10)
                return

            #  Decode last two byte
            #
            # trace(s2hex(r))
            adc = ord(r[-2])+256*ord(r[-1])
            if self.args.lpf:
                self.lpf = self.lpf - (self.lpf+2)/4 + adc # low-pass filter
                adc = (self.lpf+2)/4
            self.dial.SetValue(adc, "%04d"%adc)
            if self.serial.lastrxtime:
                self.timer.Restart( min(0.01,timer()-(self.serial.lastrxtime+0.025)) )
            else:
                self.timer.Restart( 0.02 )


        #  Under Windows XP, it seems that it is a problem if the timer
        #  is not destroyed before the window is closed
        #
        def OnClose( self, ev ):
            # del self.timer
            self.timer.Stop()
            ev.Skip()

else:
    #
    #  Console application
    #
    class Application():
        def __init__(self, args):
            self.args = args

            try:
                self.link = link.get(args)
            except link.serial.SerialException as e:
                die(str(e))


            self.link.set_RESET(0)
            time.sleep(0.01)
            self.link.set_RESET(1)
            self.link.detect_wires(b'?')
            cout(_("Tty wires: %d\n") % self.link.wires)

            time.sleep(0.2)	# Leave Diabolo enough time to check the CRC and start the application

            if not self.link.sync():
                die(_("Synchronization failed.\n"))

        def run(self):
            #
            #  Display what the device sends
            #
            # anim="|/-\\|/-\\"
            anim=("o---------",
                  "-o--------",
                  "--o-------",
                  "---o------",
                  "----o-----",
                  "-----o----",
                  "------o---",
                  "-------o--",
                  "--------o-",
                  "---------o")
            lpf = 0
            n = 0
            while True:
                #
                #  Get device data until nothing has been received for 1 byte time
                #
                r = self.link.rx_until_idle(1)
                if len(r)>=2:
                    #
                    #  Decode last two byte
                    #
                    adc = ord(r[-2])+256*ord(r[-1])
                    if self.args.lpf:
                        lpf = lpf - (lpf+2)/4 + adc # low-pass filter
                        adc = (lpf+2)/4
                    # trace("ADC=%04d" % ((adc+2)/4))
                    cout("\r%s ADC=%04d " % (anim[int(len(anim)*timer())%len(anim)],adc))
                    flushout()
                    n+=1
                    time.sleep(0.05)

#serial = com.Threaded(args)

try:
    Application(args).run()
except KeyboardInterrupt:
    cout("\n")
#    except Exception, e:
#        cerr(str(e)+'\n')
#import application
#except ImportError:

