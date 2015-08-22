#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Cadran rond wx.graphics (cairo / gdiplus)
# Application test : affiche une aiguille mobile en fonction du temps

# XP-Pro : 
#     DoubleBuffered == 0 : scintillements
#     DoubleBuffered == 1 : fenêtre très mal rafraîchie
#     L'utilisation des pixmaps ne réduit pas le scintillement.
#
# Vista :
#     Par défaut, DoubleBuffered == 0, scintillements, résolus par fgpixmap.
#
# X11 :
#     Par défaut, DoubleBuffered == 1, OK.

import sys
import wx
import colorsys
from math import cos, sin, radians
import time


# Un cadran rond.
#
class Dial(wx.Panel):

    def __init__(self, parent, ranges=(0,10,1,5), name="Dial"):
        wx.Panel.__init__(self, parent, -1)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.ranges = ranges
        self.name = name
        self.value = 0
        self.vstring = None
        self.need_refresh = 0
        self.size = None
        self.ray = None
        self.bgpixmap = None
        self.fgpixmap = None
        self.SetProperties()
        if 'wxMSW' in wx.PlatformInfo:
            self.use_fgpixmap = True
        else:
            self.use_fgpixmap = False
        #self.paint_time = 0

    # Paramètres de dessin, proportionnels au rayon du cadran
    #
    def SetProperties(self):

        self.BorderAngleStart = radians(-240)
        self.BorderAngleEnd   = radians(60)
        self.ScaleAngleStart  = radians(-225)
        self.ScaleAngleEnd    = radians(45)

        self.DialPenColour = (255, 255, 255, 224)
        self.DialPenWidth = 0.012
        self.DialBrushColour = (64, 32, 32, 240)
        # self.DialBrushColour = (32, 16, 48, 224)

        self.Scale1Colour = (255, 255, 255, 240)
        self.Scale1Width = 0.020
        self.Scale1Length1 = 0.91
        self.Scale1Length2 = 1.0
        self.Scale1Cap = wx.CAP_BUTT
        self.Scale1TextSize = 0.1
        self.Scale1TextClear = 0.025
        self.Scale1TextColour = self.Scale1Colour
        self.Scale1Font = (wx.FONTFAMILY_SWISS, wx.FONTSTYLE_NORMAL,
                          wx.FONTWEIGHT_NORMAL )

        self.Scale2Colour = (255, 255, 255, 192)
        self.Scale2Width = 0.015
        self.Scale2Length1 = 0.96
        self.Scale2Length2 = 1.0
        self.Scale2Cap = wx.CAP_BUTT

        self.NeedleSupportPenColour = (255, 255, 255, 192)
        # self.NeedleSupportPenWidth = 0.005
        self.NeedleSupportPenWidth = 0
        self.NeedleSupportBrushColour = (0, 0, 0, 128)

        self.NeedleSupportRay = 0.1
        self.NeedlePenColour = (255, 0, 0, 255)
        self.NeedleBrushColour = (255, 64, 64, 160)
        self.NeedlePenWidth = 0.005
        self.NeedleWidth1 = 0.016
        self.NeedleWidth2 = 0.008
        self.NeedleLength1 = 0.15
        self.NeedleLength2 = 0.95

        self.NamePos = (0, -0.25)
        self.TextSize = 0.1
        self.TextColour = self.Scale1Colour
        self.TextFont = (wx.FONTFAMILY_SWISS, wx.FONTSTYLE_NORMAL,
                         wx.FONTWEIGHT_BOLD )

    # Change l'intervalle d'affichage
    #
    def SetRanges(self, ranges):
        self.ranges = ranges
        self.DrawBackground()
        self.Refresh()

    # Change la valeur affichée
    #
    def SetValue(self, value, vstring=None):
        if self.value != value or self.vstring != vstring:
            # print "** Dial SetValue"
            self.value = value
            self.vstring = vstring
            if self.use_fgpixmap:
                dc = wx.MemoryDC(self.fgpixmap)
                dc.DrawBitmap(self.bgpixmap, 0, 0)
                gc = wx.GraphicsContext.Create(dc)
                self.DrawForeground( gc )
            self.Refresh()

    # Changement de taille de la fenêtre
    #
    def OnSize(self, evt):
        csw, csh  = self.GetClientSize()

        # Les événements SIZE peuvent arriver par paquets,
        # évitons de faire 2 fois le même boulot !
        #
        size = min(csw, csh)
        if size == self.size:
            return
        self.size = size

        self.bgpixmap = wx.EmptyBitmap( size, size )

        if self.use_fgpixmap:
            if self.fgpixmap:
                del self.fgpixmap
            self.fgpixmap = wx.EmptyBitmap( size, size )

        ray = (size - size*self.DialPenWidth) * 0.5
        self.ray = ray
        self.NeedlePen =  wx.Pen(wx.Colour(*self.NeedlePenColour),
                                 self.ray * self.NeedlePenWidth)
        self.NeedleBrush = wx.Brush(wx.Colour(*self.NeedleBrushColour))
        self.DrawBackground()
        if self.use_fgpixmap:
            dc = wx.MemoryDC(self.fgpixmap)
            dc.DrawBitmap(self.bgpixmap, 0, 0)
            gc = wx.GraphicsContext.Create(dc)
            self.DrawForeground( gc )
        self.Refresh()

    # Redessine le fond du compteur dans la bitmap de fond
    #
    def DrawBackground(self):
        size = self.size
        # print "NEW BITMAP", size
        dc = wx.MemoryDC(self.bgpixmap)
        gc = wx.GraphicsContext.Create(dc)

        # Fond de fenêtre
        #
        bgcolour = self.GetBackgroundColour()
        gc.SetBrush(wx.Brush(bgcolour))
        # gc.SetPen(wx.Pen(bgcolour))
        gc.DrawRectangle(0,0,size,size)
        ray = self.ray
        gc.Translate(self.size/2, self.size/2)

        # Fond de compteur
        #
        path = gc.CreatePath()
        path.AddArc( 0, 0, ray, self.BorderAngleStart, self.BorderAngleEnd )
        path.CloseSubpath()
        gc.SetPen(wx.Pen(wx.Colour(*self.DialPenColour),
                         self.ray * self.DialPenWidth))
        gc.SetBrush(wx.Brush(wx.Colour(*self.DialBrushColour)))
        gc.DrawPath(path)

        # Graduations
        #
        pen1 = wx.Pen(wx.Colour(*self.Scale1Colour), ray*self.Scale1Width)
        pen1.SetCap( self.Scale1Cap )
        pen2 = wx.Pen(wx.Colour(*self.Scale2Colour), ray*self.Scale2Width)
        pen2.SetCap( self.Scale2Cap )
        gc.SetFont( wx.Font( ray*self.Scale1TextSize, *self.Scale1Font ),
                    wx.Colour(*self.Scale1TextColour) )
        vmin, vmax, step, ssteps = self.ranges
        for i in range(vmin, vmax+1, step):
            for j in range(ssteps):
                angle = (i+j*1.0*step/ssteps - vmin) * (self.ScaleAngleEnd - self.ScaleAngleStart)/ \
                    (vmax - vmin) + self.ScaleAngleStart
                if j == 0:
                    if self.Scale1Width:
                        gc.SetPen( pen1 )
                        gc.StrokeLine( ray*self.Scale1Length1*cos(angle),
                                       ray*self.Scale1Length1*sin(angle),
                                       ray*self.Scale1Length2*cos(angle),
                                       ray*self.Scale1Length2*sin(angle) )
                    s = "%d" % i
                    tx, ty = gc.GetTextExtent(s)
                    tr = max(tx, ty)/2 + ray*self.Scale1TextClear
                    x = (ray*self.Scale1Length1 - tr)*cos(angle)
                    y = (ray*self.Scale1Length1 - tr)*sin(angle)
                    gc.DrawText( s, x - tx/2, y - ty/2 )
                elif i < vmax and self.Scale2Width :
                    gc.SetPen( pen2 )
                    gc.StrokeLine( ray*self.Scale2Length1*cos(angle),
                                   ray*self.Scale2Length1*sin(angle),
                                   ray*self.Scale2Length2*cos(angle),
                                   ray*self.Scale2Length2*sin(angle) )

        # Cercle central
        #
        gc.SetPen(wx.Pen(wx.Colour(*self.NeedleSupportPenColour),
                         self.ray * self.NeedleSupportPenWidth))
        gc.SetBrush(wx.Brush(wx.Colour(*self.NeedleSupportBrushColour)))
        r = ray * self.NeedleSupportRay
        gc.DrawEllipse( -r, -r, 2*r, 2*r )

        # Nom
        #
        gc.SetFont( wx.Font( ray*self.TextSize, *self.TextFont ),
                    wx.Colour(*self.TextColour) )
        s=self.name
        tx, ty = gc.GetTextExtent(s)
        x = ray*self.NamePos[0] - tx/2
        y = ray*self.NamePos[1] - ty/2
        gc.DrawText(s, x, y)

    # Dessine l'avant du cadran : aiguille, texte...
    #
    def DrawForeground( self, gc ):
        ray = self.ray
        gc.Translate(self.size/2, self.size/2)
        vmin, vmax, step, ssteps = self.ranges

        # Texte
        #
        font = wx.Font( ray/10, wx.FONTFAMILY_TELETYPE, wx.FONTSTYLE_NORMAL,
                        wx.FONTWEIGHT_BOLD )
        gc.SetFont(font, wx.Colour(255, 255, 255, 255))

        y = ray*sin(radians(-240.0))-ray/40
        if self.vstring:
            tx, ty = gc.GetTextExtent(self.vstring)
            gc.DrawText(self.vstring, -tx/2, y-ty)

        # Aiguille
        # La rotation est calculée par le GC, ça évite de se casser la tête.
        # FIXME : la mise à l'échelle par le GC pose un problème avec la largeur du crayon.
        #
        gc.SetPen(self.NeedlePen)
        gc.SetBrush(self.NeedleBrush)
        angle = (self.value - vmin)*(self.ScaleAngleEnd - self.ScaleAngleStart)/(vmax - vmin) \
            + self.ScaleAngleStart + radians(180)
        gc.Rotate(angle)
        # gc.Scale(ray, ray)

        path = gc.CreatePath()
        path.MoveToPoint( ray*(self.NeedleLength1-self.NeedleWidth1), ray*self.NeedleWidth1 )
        path.AddLineToPoint( ray*(-self.NeedleLength2+self.NeedleWidth2),
                             ray*self.NeedleWidth2 )
        path.AddArc( ray*(-self.NeedleLength2+self.NeedleWidth2), 0, ray*self.NeedleWidth2,
                      radians(90), radians(270))
        path.AddLineToPoint( ray*(self.NeedleLength1-self.NeedleWidth1), ray*(-self.NeedleWidth1) )
        path.AddArc( ray*(self.NeedleLength1-self.NeedleWidth1), 0, ray*self.NeedleWidth1,
                     radians(270), radians(90))

        path.CloseSubpath()
        gc.DrawPath(path)

    # Redessine le compteur :
    # recopie la bitmap de fond, puis dessine le texte et l'aiguille par dessus
    #
    def OnPaint(self, evt):
        # print "** Dial OnPaint"
        # t=time.time()
        # print round(t-self.paint_time, 3)
        # self.paint_time = t

        if self.fgpixmap:
            dc = wx.BufferedPaintDC(self, self.fgpixmap)
        else:
            dc = wx.PaintDC(self)
            dc.DrawBitmap(self.bgpixmap, 0, 0, False)
            gc = wx.GraphicsContext.Create(dc)
            self.DrawForeground( gc )


if __name__ == "__main__":

    class MyApp(wx.App):
        def OnInit(self):
            self.idle = 0
            frame = wx.Frame(None)
            self.dial = Dial(frame)
            self.dial.SetBackgroundColour(wx.BLACK)
            self.SetTopWindow( frame )
            frame.SetMinSize(( 100, 100 ))
            frame.SetSize(( 600, 600 ))

            print "DoubleBuffered:", self.dial.IsDoubleBuffered()
            # frame.SetBackgroundStyle(wx.BG_STYLE_CUSTOM)
            print "BackgroundStyle == Custom:", \
                self.dial.GetBackgroundStyle()==wx.BG_STYLE_CUSTOM
#            self.dial.SetBackgroundColour(wx.Colour(0, 0, 0, 0))
            print "CanSetTransparent:", \
                self.dial.CanSetTransparent()

            self.Bind(wx.EVT_TIMER, self.OnTimer)
            self.timer = wx.Timer(self)
            self.timer.Start(40)

            frame.Bind(wx.EVT_CLOSE, self.OnClose)
            frame.Show()
            return 1

        def OnTimer(self, ev):
            # print "** Timer"
            t=time.time()*10 % 100
            value = round(t/10.0, 2)
            vstring = "%02.1f" % value
            self.dial.SetValue(value, vstring)

        # Risque de problème sous WinXP si le timer n'est pas détruit
        # avant la fermeture de la fenêtre
        #
        def OnClose( self, ev ):
            # print "** CLOSE"
            del self.timer
            ev.Skip()

    app = MyApp(0)
    app.MainLoop()
