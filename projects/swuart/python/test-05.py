#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-06-02 17:34:39 -*-

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
    m1 = 0
    m2 = 0
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
            g = wx.Gauge(self, wx.ID_ANY, 255,
                         wx.DefaultPosition, wx.DefaultSize,
                         wx.GA_VERTICAL)
            self.gauges.append( g )
            vs.Add(g, 1, wx.ALL|wx.EXPAND, 5)

        self.mg1 = wx.Gauge(self, wx.ID_ANY, 255,
                            wx.DefaultPosition, wx.DefaultSize,
                            wx.GA_VERTICAL)
        self.mg1.SetBackgroundColour(wx.Color(255,0,0))
        self.mg1.SetValue(20)
        vs.Add(self.mg1, 1, wx.ALL|wx.EXPAND, 5)

        self.mg2 = wx.Gauge(self, wx.ID_ANY, 255,
                            wx.DefaultPosition, wx.DefaultSize,
                            wx.GA_VERTICAL)
        self.mg2.SetBackgroundColour(wx.Color(0,255,0))
        self.mg2.SetValue(20)
        vs.Add(self.mg2, 1, wx.ALL|wx.EXPAND, 5)

        self.SetSizer(vs)
        self.SetAutoLayout(True)
        vs.SetSizeHints(self)
        self.Show()

        self.timer = wx.Timer(self)
        self.timer.Start(20)
        self.Bind(wx.EVT_TIMER, self.OnTimer)

    def OnTimer(self, ev):
        # v1 = self.slider1.GetValue()
        # v2 = self.slider2.GetValue()
        # print v1, v2
        com=wx.GetApp().com
        com.tx(chr(self.m1)+chr(self.m2))
        r=com.rx(100)
        if len(r)!=4 or r[0]!='\0':
            if r:
                r=s2hex(r)
            else:
                r=''
            cout("\n")
            trace("ERROR (%s)" % r)
        else:
            v = struct.unpack('BBB', r[1:])
            for i in range(3):
                self.v[i] = (self.v[i] * 7 + v[i])/8
                self.gauges[i].SetValue(self.v[i])
            # cout(" ADC: %04d %04d %04d\r" % v)
        # flushout()

        # Calcul de trajectoire
        #
        # 000	noir partout (impossible)	arrêter
        # 001   ligne un peu à gauche		ralentir gauche × 1
        # 010	impossible			arrêter
        # 011	ligne très à gauche		ralentir gauche × 2
        # 100	ligne un peu à droite		ralentir droit × 1
        # 101	ligne au centre			accélérer gauche et droit
        # 110	ligne très à droite		ralentir droit × 2
        # 111	pas de ligne			arrêter
        # 
        m1 = self.m1
        m2 = self.m2
        smax = max(self.v)
        smean = smax * 0.8
        s1 = self.v[0] > smean
        s2 = self.v[1] > smean
        s3 = self.v[2] > smean
        s = "%d%d%d" % (s1, s2, s3)
        xm1 = m1
        xm2 = m2
        if smax < 150 or s=="000" or s=="010" or s=="111":
            xm1 = xm2 = 0
        elif s=="001":
            xm1 = m1/2
            if m2 < 127:
                xm2 += (127-m2)/2
        elif s=="011":
            xm1 = 0
            if m2 < 127:
                xm2 += (127-m2)/2
        elif s=="100":
            xm2 = m2/2
            if m1 < 127:
                xm1 += (127-m1)/2
        elif s=="110":
            xm2 = 0
            if m1 < 127:
                xm1 += (127-m1)/2
        else:
            xm1 = 127
            xm2 = 127

        # m1 = (m1 * 31 + xm1)/32
        # m2 = (m2 * 31 + xm2)/32
        m1 = (m1 * 7 + xm1)/8
        m2 = (m2 * 7 + xm2)/8
        self.m1 = m1
        self.m2 = m2
        msg = s
        cout(msg+'\r')
        flushout()
        self.mg1.SetValue(m1)
        self.mg2.SetValue(m2)


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

    options.combps = 20000
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
