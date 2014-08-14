#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2013-12-27 15:34:21 -*-

import wx
#import usb
import usb.legacy as usb
#import usb.core

def usbdevices():
    devs = []
    for bus in usb.busses():
        for dev in bus.devices:
            devs.append("%s: %04x-%04x\n" % (dev.filename, dev.idVendor, dev.idProduct))
    return devs


class App(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, title="USB Devices")
        frame.SetMinSize((200,100))

        tc = wx.TextCtrl(frame, wx.ID_ANY, "USB Devices:\n", style=wx.TE_MULTILINE)
        try:
            for d in usbdevices():
                tc.AppendText(d)
        except Exception, e :
            tc.AppendText("Exception:" + str(e))

        frame.Show()
        return 1


    def run(self):
        self.MainLoop()


if __name__ == "__main__":
    App().run()
