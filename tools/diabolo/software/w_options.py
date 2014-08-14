#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-12-22 16:57:54 -*-

import wx
import com


class WOptions(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, wx.ID_ANY, _("Options"))

        self.port=wx.GetApp().com.getPort()
        self.baud=wx.GetApp().com.baudrate
        self.onewire=wx.GetApp().com.onewire
        ports=com.listports(self.port)

        self.portbtns=[] # [ wx.ToggleButton(self, -1, p) for p in ports ]
        self.baudbtns=[] # [ wx.ToggleButton(self, -1, b) for b in bauds ]
        self.portbtn=None
        self.baudbtn=None

        vs=wx.BoxSizer(wx.VERTICAL)

        # Port box
        #
        bx=wx.StaticBox(self, -1, _("Port"))
        bs=wx.StaticBoxSizer(bx, wx.HORIZONTAL)
        #trace(port)
        for p in ports:
            btn=wx.ToggleButton(self, -1, p)
            self.portbtns.append(btn)
            if p==self.port:
                self.portbtn=btn
            self.Bind(wx.EVT_TOGGLEBUTTON, self.OnPort, btn)
            bs.Add(btn)
        vs.Add(bs, 0, wx.ALL, 5)

        #  Baudrate box
        #
        bx=wx.StaticBox(self, -1, _("Speed"))
        bs=wx.StaticBoxSizer(bx, wx.VERTICAL)
        hs=wx.BoxSizer(wx.HORIZONTAL)
        for s in ["19200", "38400", "57600"]:
            btn=wx.ToggleButton(self, -1, s)
            if int(s)==self.baud:
                btn.SetValue(True)
                self.baudbtn=btn
            self.baudbtns.append(btn)
            self.Bind(wx.EVT_TOGGLEBUTTON, self.OnBaud, btn)
            hs.Add(btn)
        bs.Add(hs)
        hs=wx.BoxSizer(wx.HORIZONTAL)
        for s in ["100000", "115200", "230400"]:
            btn=wx.ToggleButton(self, -1, s)
            if int(s)==self.baud:
                self.baudbtn=btn
            self.baudbtns.append(btn)
            self.Bind(wx.EVT_TOGGLEBUTTON, self.OnBaud, btn)
            hs.Add(btn)
        bs.Add(hs)
        vs.Add(bs, 0, wx.ALL|wx.EXPAND, 5)

        #  Wires box
        #
        cb=wx.CheckBox(self, -1, _("Single wire"))
        if self.onewire:
            cb.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.OnWires, cb)
        vs.Add(cb, 0, wx.ALL, 5)

        if not self.portbtn and self.portbtns:
            self.portbtn=self.portbtns[0]
        if self.portbtn:
            self.portbtn.SetValue(True)

        if not self.baudbtn and self.baudbtns:
            self.baudbtn=self.baudbtns[0]
        if self.baudbtn:
            self.baudbtn.SetValue(True)

        #vs.Add(wx.StaticLine(self, -1), 0, wx.ALL|wx.ALIGN_CENTER|wx.EXPAND, 5)
        hs =  self.CreateButtonSizer(wx.CANCEL|wx.OK)
        vs.Add(hs, 0, wx.ALL|wx.ALIGN_RIGHT, 5)

        self.SetSizer(vs)
        self.SetAutoLayout(True)
        vs.SetSizeHints(self)


    def OnPort(self, ev):
        btn=ev.GetEventObject()
        if self.portbtn:
            self.portbtn.SetValue(False)
        self.portbtn=btn
        self.port=btn.GetLabel()

    def OnBaud(self, ev):
        btn=ev.GetEventObject()
        if self.baudbtn:
            self.baudbtn.SetValue(False)
        self.baudbtn=btn
        self.baud=btn.GetLabel()

    def OnWires(self, ev):
        obj=ev.GetEventObject()
        self.onewire = obj.GetValue() ;
