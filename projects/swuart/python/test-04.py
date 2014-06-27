#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-06-01 21:05:27 -*-

# FT232RL :	 1 TXD
#	         3 RTS (-> RESET)
# 		 5 RXD
# 		 4 VCCIO
# 		 7 GND
# 		17 3V3out
# 		18 GND
# 		20 VCC

# 4-Wire fans
#
#	Blue	PWM Command	3.3 V	40 µs / 25 kHz
#	Green	Hall Sensor	3.3 V
#	Yellow	+12 V
#	Black	GND
#
# CPU:	High 17.5/40 µs -> 74 Hz (13.5 ms)
# Box:	High 14.8/40 µs -> 60 Hz (16.5 ms)

import struct
import serial
import time
from utils import *
import termios
from com import *
from premain import *
from optparse import OptionParser
import wx



class Frame(wx.Frame):
    title = "Dual PWM"
    v = [0,0,0]
    def __init__(self):
        wx.Frame.__init__(self, None, title = Frame.title)

        vs = wx.BoxSizer(wx.HORIZONTAL)
        self.slider1 = wx.Slider(self, wx.ID_ANY, 1, 0, 255,
                                 wx.DefaultPosition, (-1, 200),
                                 wx.SL_VERTICAL | wx.SL_INVERSE | wx.SL_LABELS);
        self.slider2 = wx.Slider(self, wx.ID_ANY, 1, 0, 255,
                                 wx.DefaultPosition, (-1, 200),
                                 wx.SL_VERTICAL | wx.SL_INVERSE | wx.SL_LABELS);
        vs.Add(self.slider1, 1, wx.ALL|wx.EXPAND, 5)
        vs.Add(self.slider2, 1, wx.ALL|wx.EXPAND, 5)

        self.gauges = []
        for i in range(3):
            g = wx.Gauge(self, wx.ID_ANY, 1024,
                         wx.DefaultPosition, wx.DefaultSize,
                         wx.GA_VERTICAL)
            self.gauges.append( g )
            vs.Add(g, 1, wx.ALL|wx.EXPAND, 5)

        self.SetSizer(vs)
        self.SetAutoLayout(True)
        vs.SetSizeHints(self)
        self.Show()

        self.timer = wx.Timer(self)
        self.timer.Start(20)
        self.Bind(wx.EVT_TIMER, self.OnTimer)

    def OnTimer(self, ev):
        v1 = self.slider1.GetValue()
        v2 = self.slider2.GetValue()
        # print v1, v2
        com=wx.GetApp().com
        com.tx(chr(v1)+chr(v2))
        r=com.rx(100)
        if len(r)!=7 or r[0]!='\0':
            if r:
                r=s2hex(r)
            else:
                r=''
            cout("\n")
            trace("ERROR (%s)" % r)
        else:
            v = struct.unpack('<HHH', r[1:])
            for i in range(3):
                self.v[i] = (self.v[i] * 7 + v[i])/8
                self.gauges[i].SetValue(self.v[i])
            cout(" ADC: %04d %04d %04d\r" % v)
        flushout()


class App(wx.App):
    def OnInit(self):
        self.frame = Frame() # Top window
        return 1


def main():
    parser = OptionParser(usage="usage: %prog [options] [firmware]")
    parser.add_option("-d", "--dev", metavar="DEVICE", type="string",
                      default="/dev/ttyUSB0", dest="comdev", 
                      help="set com device (default /dev/ttyUSB0)")
    parser.add_option("-b", "--bps", metavar="SPEED", type="int",
                      default=100000, dest="combps", 
                      help="set com speed (default 100000)")
    (options, args) = parser.parse_args()    

    options.combps = 50000
    com = Com(options.comdev, options.combps)

    print com.port

    com.open()
    com.onewire = True
    #com.setTimeout(12*10.0/options.combps)
    com.setTimeout(2*12*10.0/options.combps)
    com.reset_device()
    time.sleep(0.3)

    # SyncD
    #
    chars=['\0','\xFF']
    nchar=0
    tries=0
    while True:
        tries+=1
        com.tx(chars[nchar])
        nchar+=1
        if nchar==len(chars):
            nchar=0
        r = com.rx(1)
        if r=='\x55':
            break
        elif r:
            cout(" %d %s\r" % (tries, s2hex(r)))
            flushout()
        else:
            cout(" ''\r")
            flushout()
        time.sleep(.2)

    r = com.rx(2)
    dtn = struct.unpack('<H', r)[0]
    cout("%d tries, dtn=%d\n" % (tries, dtn))

    # com.tx('\0')
    # sys.exit(0)

    app = App(0)
    app.com = com
    app.MainLoop()


main()
