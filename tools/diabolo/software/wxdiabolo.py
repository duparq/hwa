#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2013-12-28 16:36:03 -*-

import wx
#import com
#import xcom
import diabolo
#import math
import os
import platform
import thread

#from w_options import WOptions


THREAD_NONE = 0
THREAD_EXIT = 1
THREAD_LISTEN = 2


def alert(msg):
    parent = wx.GetApp().frame
    dlg = wx.MessageDialog(parent, msg, _("Error"), wx.OK | wx.ICON_ERROR)
    dlg.ShowModal()
    dlg.Destroy()


#class WGrid(wx.Panel):
class WGrid(wx.Window):
    CELLSIZE = 16

    class State:
        def __init__(self, text, color):
            self.text = text
            self.color = color

    STATE_UNKNOWN = State('Unknown', 0)
    #STATE_HIDDEN = State('Hidden', 0)
    STATE_DATA = State('Data', wx.Colour(0x00,0x7F,0x7F))
    STATE_BOOT = State('Boot', wx.Colour(0x40, 0x80, 0xFF, 0x40))
    STATE_VIRGIN = State('Virgin', 0)

    def __init__(self, parent):
        self.parent = parent
        self.bmp = None
        self.ncols = 0
        self.nrows = 0
        self.cells = None
        self.dc = wx.MemoryDC()
        self.psize = (0,0)
        self.x = 0
        self.y = 0
        self.trace = False
        wx.Window.__init__(self, parent, -1)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        bg = self.GetBackgroundColour()
        r, g, b = bg.Get()
        g+= (0xFF - g)/2
        WGrid.STATE_VIRGIN.color = wx.Colour(r, g, b)
        WGrid.STATE_UNKNOWN.color = bg
        #self.SetMinSize((16*self.CELLSIZE, self.CELLSIZE))
        # self.SetSizeHints(16*self.CELLSIZE, self.CELLSIZE, -1, -1,
        #                   self.CELLSIZE, self.CELLSIZE)

    #  Initialise la grille
    #    Rend toutes les cellules transparentes et peint celles du bootloader
    #
    def InitFromDevice(self, device):
        self.cells = [WGrid.STATE_UNKNOWN for i in range(device.flashsize / device.pagesize)]
        boot = device.bladdr
        if boot:
            for c in range(boot/device.pagesize, device.flashsize / device.pagesize):
                self.cells[c] = self.STATE_BOOT
        #self.ncols = 0	# Will force redrawing
        self.Resize()

    #  Fixe le nombre de cellules et leurs couleurs
    #
    def SetCells(self, cells):
        self.cells = cells
        #self.ncols = 0	# Will force redrawing
        self.Resize()

    #  Rend toutes les cellules transparentes
    #
    def Clear(self):
        if self.cells:
            self.cells = [ WGrid.STATE_UNKNOWN for i in self.cells ]
            self.Redraw()

    #  Recopie la bitmap de la grille sur l'écran
    #
    def OnPaint(self, evt):
        dc = wx.PaintDC(self)
        # csx, csy = self.GetClientSize()
        # w, h = self.GetSize()
        # w = self.ncols * self.CELLSIZE
        # h = self.nrows * self.CELLSIZE
        # dx = (csx-w)/2
        # dy = (csy-h)/2
        # trace(u"PAINT %d×%d %d×%d" % (csx, csy, w, h, dx, dy))
        dc.BeginDrawing()
        i = wx.RegionIterator( self.GetUpdateRegion() )
        while i:
            (x,y,dx,dy) = i.GetRect()
            dc.Blit(x, y, dx, dy, self.dc, x, y)
            i.Next()
        dc.EndDrawing()

    #  Recalcule la taille de la grille
    #
    def OnSize(self, ev):
        if self.cells:
            self.Resize()

    def Resize(self):
        w, h = self.GetClientSize()
        ncols = int(math.log(w / self.CELLSIZE, 2))
        ncols = int(math.pow(2, ncols))
        ncells = len(self.cells)
        if ncols > ncells:
            ncols = ncells
        # if ncols < 16:
        #     ncols = 16
        nrows = ncells / ncols

        if nrows > 4*ncols:
            if self.trace:
                trace()
            return

        #  Change la pixmap
        #
        self.ncols = ncols
        self.nrows = nrows
        dx = ncols * self.CELLSIZE
        dy = nrows * self.CELLSIZE
        self.x = (w-dx)/2
        self.y = (h-dy)/2

        minw = dx
        minh = dy
        if dy <= h/2:
            minw = dx/2
        if dx <= w/2:
            minh = dy/2
        if w < dx:
            trace()
            minw = dx*2
        if h < dy:
            minh = dy*2

        if self.GetMinSize() != (minw, minh):
            self.SetMinSize((minw, minh))
            if self.trace:
                trace("MINSIZE %d %d" % (minw, minh))
            self.parent.Layout()
            wx.Yield()
            return

        if self.trace:
            trace("PIXMAP %d %d" % (dx, dy))

        if self.bmp:
            self.dc.SelectObject(wx.NullBitmap)
            del self.bmp

        self.bmp = wx.EmptyBitmap(w, h)
        self.dc.SelectObject(self.bmp)
        self.dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
        self.dc.Clear()
        self.Redraw()

    #  Redessine la grille dans la pixmap
    #
    def Redraw(self):
        for row in range(self.nrows):
            for col in range(self.ncols):
                self.DrawCell(col, row)
        self.Refresh()

        #  Colore les pages du bootloader en semi-transparent
        #
        # if 0 and self.boot:
        #     gc = wx.GraphicsContext.Create(self.dc)
        #     gc.SetPen(wx.Pen(wx.BLACK, 0))
        #     gc.SetBrush(wx.Brush(wx.Colour(0x00, 0x40, 0xFF, 0x40)))
        #     for c in range(self.boot/self.psize, len(self.cells)):
        #         row = c / self.ncols
        #         col = c - row * self.ncols
        #         r = wx.Rect(col*self.CELLSIZE+1, row*self.CELLSIZE+1,
        #                     self.CELLSIZE-2, self.CELLSIZE-2)
        #         gc.DrawRectangle(*r)
        #     del gc

    def DrawCell(self, col, row):
        #csx, csy = self.GetClientSize()
        # w, h = self.GetSize()
        # dx = self.ncols * self.CELLSIZE
        # dy = self.nrows * self.CELLSIZE
        # x = (w-dx)/2
        # y = (h-dy)/2

        self.dc.SetPen(wx.BLACK_PEN)
        self.dc.SetBrush(wx.Brush(self.cells[row*self.ncols+col].color))
        r = wx.Rect(self.x+col*self.CELLSIZE+1, self.y+row*self.CELLSIZE+1,
                       self.CELLSIZE-2, self.CELLSIZE-2)
        self.dc.DrawRectangle(*r)
        return r

    def SetCell(self, n, state):
        row = n / self.ncols
        col = n - row * self.ncols
        self.cells[row*self.ncols+col] = state
        self.RefreshRect(self.DrawCell(col, row))

    #  Draw a rectangle around the cell
    #
    def SelectCell(self, n, state):
        row = n / self.ncols
        col = n - row * self.ncols
        if state:
            color = self.GetBackgroundColour()
            self.dc.SetPen(wx.Pen(color, 1))
            self.dc.SetBrush(wx.Brush(color, wx.SOLID))
            r = wx.Rect(self.x+col*self.CELLSIZE+1, self.y+row*self.CELLSIZE+1,
                        self.CELLSIZE-2, self.CELLSIZE-2)
        else:
            r = self.DrawCell(col, row)
        self.dc.DrawRectangle(*r)
        self.RefreshRect(r)


class WFirmware(wx.StaticBoxSizer):
    def __init__(self, parent):
        self.parent = parent
        self.data = None	# Firmware data
        self.stat = None	# Firmware stats

        def VBox1(self):
            def HBox1(self):
                self.w_path = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_size = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_crc = wx.StaticText(parent, wx.ID_ANY, "-")
                hs = wx.BoxSizer(wx.HORIZONTAL)
                vs = wx.BoxSizer(wx.VERTICAL)
                vs.AddMany([
                        (wx.StaticText(parent, wx.ID_ANY, "File:"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY, "Size:"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY, "CRC:"), 0, wx.EXPAND),
                        ])
                hs.Add(vs)
                vs = wx.BoxSizer(wx.VERTICAL)
                vs.AddMany([
                        (self.w_path, 0, wx.EXPAND),
                        (self.w_size, 0, wx.EXPAND),
                        (self.w_crc, 0, wx.EXPAND),
                        ])
                hs.Add(vs, 1, wx.LEFT|wx.EXPAND, 5)
                return hs

            def HBox2(self):
                self.w_grid = WGrid(parent)
                self.w_grid.Hide()
                #self.w_grid.trace = True
                return self.w_grid

            vs = wx.BoxSizer(wx.VERTICAL)
            vs.Add(HBox1(self), 0, wx.ALL|wx.EXPAND, 5)
            vs.Add(HBox2(self), 1, wx.TOP|wx.EXPAND, 5)
            return vs

        def VBox2(self):
            self.w_bpath = wx.Button(parent, -1, _("File"))
            self.w_reload = wx.Button(parent, -1, _("Reload"))
            self.w_reload.Enable(False)
            vs = wx.BoxSizer(wx.VERTICAL)
            vs.Add(self.w_bpath)
            vs.Add(self.w_reload)
            parent.Bind(wx.EVT_BUTTON, self.OnFile, self.w_bpath)
            parent.Bind(wx.EVT_BUTTON, self.OnReload, self.w_reload)
            return vs

        bx = wx.StaticBox(parent, -1, _("Firmware"))
        wx.StaticBoxSizer.__init__(self, bx, wx.HORIZONTAL)
        self.Add(VBox1(self), 1, wx.ALL|wx.EXPAND, 0)
        self.Add(VBox2(self), 0, wx.LEFT, 5)

        if wx.GetApp().path:
            self.OnReload()

    #  Check for firmware update
    #
    def Check(self):
        path = wx.GetApp().path
        if path and os.path.isfile(path) \
                and self.stat \
                and self.stat.st_mtime != os.stat(path).st_mtime:
            self.w_reload.Enable(True)

    #  Open/change firmware path
    #
    def OnFile(self, ev):
        tlp = wx.GetApp().GetTopWindow()
        path = wx.GetApp().path
        if path:
            cwd = os.path.dirname(path)
        else:
            cwd = os.getcwd()
        path = None
        dlg = wx.FileDialog(
            tlp, message = _("Choose a file"),
            defaultDir = cwd,
            defaultFile = "",
            wildcard = "Binary (*.bin)|*.bin|Intel Hex (*.hex)|*.hex|All (*.*)|*.*",
            style = wx.OPEN | wx.CHANGE_DIR )

        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPaths()[0]
        dlg.Destroy()

        if path:
            self.w_path.SetLabel(path)
            wx.GetApp().path=path
            self.OnReload()

    #  Open/change firmware path
    #
    def OnReload(self, ev=None):
        self.Load()
        self.UpdateCRC()

    def Load(self):
        path = wx.GetApp().path

        if not os.path.isfile(path):
            alert(_("File %s does not exist." % path))
            return
        if not path.endswith('.bin'):
            alert(_("File format not handled."))
            return

        self.stat = os.stat(path)
        f = open(path, 'rb')
        data = f.read()
        f.close()

        # from utils import hexdump
        # trace(hexdump(0,data))

        for i in range(len(data)-1, -1, -1):
            if ord(data[i])!=0xFF:
                # trace("0x%04X: %02X" % (i, ord(data[i])))
                break
        i+=1

        self.w_reload.Enable(False)
        self.data = data
        self.w_path.SetLabel(path)
        self.w_size.SetLabel("%d/%d" % (i, len(self.data)))

    #  Recompute firmware CRC
    #
    def UpdateCRC(self):
        path = wx.GetApp().path
        if path and not self.stat:
            self.Load()
        diabolo = wx.GetApp().diabolo
        if self.data:
            data = self.data
            dsize = len(data)
            # crc = diabolo.crc.check(data)
            crc = diabolo.crc.check_app(data[2:])
            self.crc = crc
            self.w_crc.SetLabel("0x%04X" % crc)
            if diabolo.device:
                device = diabolo.device
                boot = device.bladdr
                psize = device.pagesize
                vp = '\xFF'*psize
                cells = [WGrid.STATE_UNKNOWN for i in range(dsize/psize)]
                # if boot and device.mflash:
                # if boot:
                #     crc = diabolo.crc.check(data[2:boot])
                #     self.crc = crc
                #     self.w_crc.SetLabel("0x%04X" % crc)
                for n in range(dsize/psize):
                    if data[n*psize:(n+1)*psize] == vp:
                        cells[n] = WGrid.STATE_VIRGIN
                    else:
                        cells[n] = WGrid.STATE_DATA
                self.w_grid.SetCells(cells)
                self.w_grid.Show()
                tlp = wx.GetTopLevelParent(self.w_path)
                tlp.GetSizer().SetSizeHints(tlp)
                self.parent.Layout()
                wx.Yield()


class WDevice(wx.StaticBoxSizer):
    def __init__(self, parent):
        self.parent = parent

        def VBox1(self):
            def HBox1(self):
                hs = wx.BoxSizer(wx.HORIZONTAL)
                hs.Add((0,0), 1)
                vs = wx.BoxSizer(wx.VERTICAL)
                vs.AddMany([
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Circuit:"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Signature:"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Bootloader:"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Application CRC (Computed):"), 0, wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Application CRC (EEPROM):"), 0, wx.EXPAND),
                        ])
                hs.Add(vs, 0, wx.EXPAND)
                vs = wx.BoxSizer(wx.VERTICAL)
                self.w_dev = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_sig = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_bootload = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_pgmcnt = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_appcrc = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_eeappcrc = wx.StaticText(parent, wx.ID_ANY, "-")
                vs.AddMany([
                        (self.w_dev, 0, wx.ALL|wx.EXPAND),
                        (self.w_sig, 0, wx.ALL|wx.EXPAND),
                        (self.w_bootload, 0, wx.ALL|wx.EXPAND),
                        (self.w_appcrc, 0, wx.ALL|wx.EXPAND),
                        (self.w_eeappcrc, 0, wx.ALL|wx.EXPAND),
                        ])
                hs.Add(vs, 0, wx.LEFT|wx.EXPAND, 5)
                hs.Add((0,0), 1)
                vs = wx.BoxSizer(wx.VERTICAL)
                vs.AddMany([
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Fuse Low Byte:"), 0, wx.ALL|wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Fuse High Byte:"), 0, wx.ALL|wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Fuse Entended Byte:"), 0, wx.ALL|wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Lock bits:"), 0, wx.ALL|wx.EXPAND),
                        (wx.StaticText(parent, wx.ID_ANY,
                                       "Programmings:"), 0, wx.EXPAND),
                        ])
                hs.Add(vs, 0, wx.LEFT|wx.EXPAND, 10)

                vs = wx.BoxSizer(wx.VERTICAL)
                self.w_fuselb = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_fusehb = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_fuseeb = wx.StaticText(parent, wx.ID_ANY, "-")
                self.w_lockbits = wx.StaticText(parent, wx.ID_ANY, "-")
                vs.AddMany([
                        (self.w_fuselb, 0, wx.ALL|wx.EXPAND),
                        (self.w_fusehb, 0, wx.ALL|wx.EXPAND),
                        (self.w_fuseeb, 0, wx.ALL|wx.EXPAND),
                        (self.w_lockbits, 0, wx.ALL|wx.EXPAND),
                        (self.w_pgmcnt, 0, wx.ALL|wx.EXPAND),
                        ])
                hs.Add(vs, 0, wx.LEFT|wx.EXPAND, 5)
                hs.Add((0,0), 1)
                return hs

            def HBox2(self):
                self.w_grid = WGrid(parent)
                self.w_grid.Hide()
                return self.w_grid

            vs = wx.BoxSizer(wx.VERTICAL)
            vs.Add(HBox1(self), 0, wx.ALL|wx.EXPAND, 5)
            vs.Add(HBox2(self), 1, wx.TOP|wx.EXPAND, 5)
            return vs

        def VBox2(self):
            self.w_reset = wx.Button(parent, -1, _("Reset"))
            self.w_connect = wx.Button(parent, -1, _("Connect"))
            self.w_run  = wx.Button(parent, -1, _("Run"))
            self.w_burn = wx.Button(parent, -1, _("Burn"))
            self.w_read = wx.Button(parent, -1, _("Read"))
            self.w_save = wx.Button(parent, -1, _("Save"))
            self.w_options = wx.Button(parent, -1, _("Options"))
            self.w_eeread = wx.Button(parent, -1, _("EEPROM"))

            self.w_run.Enable(False)
            self.w_burn.Enable(False)
            self.w_read.Enable(False)
            self.w_save.Enable(False)
            self.w_eeread.Enable(False)

            parent.Bind(wx.EVT_BUTTON, self.OnReset, self.w_reset)
            parent.Bind(wx.EVT_BUTTON, self.OnConnect, self.w_connect)
            parent.Bind(wx.EVT_BUTTON, self.OnRun, self.w_run)
            parent.Bind(wx.EVT_BUTTON, self.OnBurn, self.w_burn)
            parent.Bind(wx.EVT_BUTTON, self.OnRead, self.w_read)
            parent.Bind(wx.EVT_BUTTON, self.OnSave, self.w_save)
            parent.Bind(wx.EVT_BUTTON, self.OnOptions, self.w_options)
            parent.Bind(wx.EVT_BUTTON, self.OnEERead, self.w_eeread)

            b = wx.BoxSizer(wx.HORIZONTAL)
            v = wx.BoxSizer(wx.VERTICAL)
            v.AddMany([ self.w_reset, self.w_options, self.w_read, self.w_save ])
            b.Add(v)
            v = wx.BoxSizer(wx.VERTICAL)
            v.AddMany([ self.w_connect, self.w_burn, self.w_run, self.w_eeread, ((0,0), 1)])
            b.Add(v)
            return b

        bx = wx.StaticBox(parent, -1, _("Device"))
        wx.StaticBoxSizer.__init__(self, bx, wx.HORIZONTAL)
        self.Add(VBox1(self), 1, wx.ALL|wx.EXPAND, 5)
        self.Add(VBox2(self), 0, wx.EXPAND, 5)
        self.wpath = os.getcwd()

    def update(self):
        device = wx.GetApp().diabolo.device
        if device:
            self.w_dev.SetLabel(device.name)
            self.w_sig.SetLabel(device.signature)
            self.w_bootload.SetLabel("0x%04X" % device.bladdr)
            self.w_pgmcnt.SetLabel("%d" % device.pgmcount)
            self.w_fuselb.SetLabel("0x%02X" % ord(device.fuses[0]))
            self.w_fusehb.SetLabel("0x%02X" % ord(device.fuses[3]))
            self.w_fuseeb.SetLabel("0x%02X" % ord(device.fuses[2]))
            self.w_lockbits.SetLabel("0x%02X" % ord(device.fuses[1]))
            self.w_appcrc.SetLabel("0x%04X" % device.appcrc)
            self.w_eeappcrc.SetLabel("0x%04X" % device.eeappcrc)
            self.w_grid.InitFromDevice(device)
            self.w_grid.Show()
            tlp = wx.GetTopLevelParent(self.w_dev)
            #tlp = wx.GetApp().frame
            tlp.GetSizer().SetSizeHints(tlp)
            #self.parent.SetSizeHints(self.parent)
            self.parent.Layout()
            wx.Yield()
            # tlp.GetSizer().SetSizeHints(tlp)
            #self.parent.w_firmware.UpdateCRC()

    #  Reset device
    #
    def OnReset(self, ev=None):
        diabolo = wx.GetApp().diabolo
        com = diabolo.com
        com.init()
        if not com.isOpen():
            alert(_("Can not open connection."))
            return
        com.reset_device()

        self.w_run.Enable(False)
        self.w_burn.Enable(False)
        self.w_read.Enable(False)
        self.w_save.Enable(False)
        self.w_eeread.Enable(False)
        self.parent.Update()


    #  Initialize diabolo communication
    #
    def OnConnect(self, ev=None):
        diabolo = wx.GetApp().diabolo
        com = diabolo.com

        wx.BeginBusyCursor()
        self.w_run.Enable(False)
        self.w_burn.Enable(False)
        self.w_read.Enable(False)
        self.w_save.Enable(False)
        self.w_eeread.Enable(False)
        self.w_grid.Clear()
        self.parent.Update()

        com.init()
        if not com.isOpen():
            wx.EndBusyCursor()
            alert(_("Can not open connection."))
            return

        self.start()
        self.w_run.Enable(True)
        self.w_burn.Enable(True)
        self.w_read.Enable(True)
        self.w_save.Enable(True)
        self.w_eeread.Enable(True)
        wx.EndBusyCursor()

        if diabolo.error:
            alert(diabolo.error)
            diabolo.error = None
        else:
            self.update()
            self.parent.w_firmware.UpdateCRC()
            self.OnRead(None)


    #  Start Diabolo
    #
    def start(self):
        diabolo = wx.GetApp().diabolo
        com = diabolo.com
        com.setBreak(True)
        com.reset_device()
        # time.sleep(0.1)
        time.sleep(0.5)
        com.setBreak(False)
        com.sync()
        if com.lastchar is None:
            alert(_("Synchronisation failed."))
            return

        diabolo.getprompt()
        if com.lastchar != '#':
            alert(_("Can not get prompt."))
            return
        diabolo.ident()


    #  Run application
    #
    def OnRun(self, ev):
        #wx.BeginBusyCursor()
        diabolo = wx.GetApp().diabolo
        diabolo.run_application()
        if diabolo.error:
            alert(diabolo.error)
            diabolo.error = None
            return
        self.w_run.Enable(False)
        self.w_burn.Enable(False)
        self.w_read.Enable(False)
        self.w_eeread.Enable(False)

        run_cmd = wx.GetApp().run_cmd
        if not run_cmd:
            return

        #trace(run_cmd)
        import subprocess
        subprocess.call(run_cmd)
        self.w_run.Enable(True)
        self.w_burn.Enable(True)
        self.w_read.Enable(True)
        self.w_eeread.Enable(True)

        #trace("Done")
        #self.OnInit(None)
        self.start()
        if diabolo.error:
            alert(diabolo.error)
            diabolo.error = None
        #wx.EndBusyCursor()


    # def take_serial(self, serial):
    #     self.serial = serial
    #     self.thread_command = THREAD_LISTEN
    #     thread.start_new_thread( self.thread_listen, () )

    # def release_serial(self):
    #     self.thread_command = THREAD_EXIT
    #     while self.thread_status != THREAD_EXIT:
    #         time.sleep(0.1)
    #     self.serial = None

    # def thread_listen(self):
    #     """Thread that handles the serial traffic."""
    #     self.last_char=''
    #     while self.thread_command == THREAD_LISTEN:
    #         self.thread_status = THREAD_LISTEN
    #         text = self.serial.read(1)          #read one, with timout
    #         if text:                            #check if not timeout
    #             n = self.serial.inWaiting()     #look if there is more to read
    #             if n:
    #                 text = text + self.serial.read(n) #get it
    #             self.last_char = text[-1]
    #             self.message("SERIAL", text)
    #         else:
    #             ## '+' is the Diabolo prompt. Get memory image and update
    #             ## firmware if any available.
    #             ##
    #             if self.last_char == '+':
    #                 self.last_char = None
    #                 if not self.memory:
    #                     self.read_memory()
    #                     if self.firmware and not os.path.isfile(self.firmware):
    #                         self.memory_to_file()
    #                 self.update_firmware()
    #     self.thread_status = THREAD_EXIT


    def OnRead(self, ev):
        diabolo = wx.GetApp().diabolo
        if not diabolo.device:
            return
        s = ''
        wx.BeginBusyCursor()
        psize = diabolo.device.pagesize
        vp = '\xFF'*psize
        grid = self.w_grid
        for a in range(0, diabolo.device.flashsize, psize):
            n = a/psize
            grid.SelectCell(n, True )
            grid.Update()
            diabolo.set_address(a)
            if diabolo.error:
                wx.EndBusyCursor()
                alert(diabolo.error)
                diabolo.error = None
                return
            device = diabolo.device
            p = diabolo.read_flash_page()
            if diabolo.error:
                wx.EndBusyCursor()
                alert(diabolo.error)
                diabolo.error = None
                return
            if a < device.bladdr:
                if p != vp:
                    grid.SetCell(n, grid.STATE_DATA)
                else:
                    grid.SetCell(n, grid.STATE_VIRGIN)
            else:
                grid.SetCell(n, grid.STATE_BOOT)
            grid.SelectCell(n, False)
            grid.Update()
            s += p
        wx.EndBusyCursor()
        device.mflash = s


    def OnEERead(self, ev):
        diabolo = wx.GetApp().diabolo
        device = diabolo.device
        if not device:
            return
        s = ''
        wx.BeginBusyCursor()
        psize = device.pagesize
        vp = '\xFF'*psize
        if device.eepromsize > 255:
            n = 128
        else:
            n = device.eepromsize
        for a in range(0, device.eepromsize, n):
            diabolo.set_address(a)
            if diabolo.error:
                wx.EndBusyCursor()
                alert(diabolo.error)
                diabolo.error = None
                return
            b = diabolo.read_eeprom(n)
            if diabolo.error:
                wx.EndBusyCursor()
                alert(diabolo.error)
                diabolo.error = None
                return
            s += b
        wx.EndBusyCursor()
        from utils import hexdump
        hexdump(0, s)


    def OnBurn(self, ev):
        firmware=wx.GetApp().frame.w_firmware
        if not firmware.data:
            return
        diabolo = wx.GetApp().diabolo
        if not diabolo.device:
            return
        firmware.UpdateCRC()
        diabolo.flash_changed = False
        device=diabolo.device

        wx.BeginBusyCursor()

        grid = self.w_grid
        psize = device.pagesize
        vp = '\xFF'*psize
        for a in range(0, device.bladdr, psize):
            p=firmware.data[a:a+psize]

            n = a/psize
            grid.SelectCell(n, True )
            grid.Update()

            r=diabolo.write_flash_page(a, p)
            if diabolo.error:
                wx.EndBusyCursor()
                alert(diabolo.error)
                diabolo.error = None
                return
            #trace(repr(r))

            if p == vp:
                grid.SetCell(n, grid.STATE_VIRGIN)
            else:
                grid.SetCell(n, grid.STATE_DATA)
            grid.SelectCell(n, False)
            grid.Update()

        x_init = False

        if diabolo.flash_changed:
            diabolo.set_eeprom_pgmcount(device.pgmcount+1)
            # diabolo.set_eeprom_pgmcount(160)
            if diabolo.error:
                trace()
                alert(diabolo.error)
                wx.EndBusyCursor()
                return
            x_init = True

        # crc = diabolo.get_eeprom_appcrc()
        # if diabolo.error:
        #     alert(diabolo.error)
        #     wx.EndBusyCursor()
        #     return

        # if crc != firmware.crc:
        if device.eeappcrc != firmware.crc:
            diabolo.set_eeprom_appcrc(firmware.crc)
            if diabolo.error:
                alert(diabolo.error)
                wx.EndBusyCursor()
                return
            x_init = True

        # Restart Diabolo to make it compute the new CRC
        #
        if x_init:
            # time.sleep(0.2) # Need to wait after writing?
            # diabolo.ident()
            # if diabolo.error:
            #     alert(diabolo.error)
            #     wx.EndBusyCursor()
            #     return
            self.OnConnect()
            #self.update()

        # if diabolo.flash_changed:
        #     diabolo.device.mflash=firmware.data[:device.bladdr]
        wx.EndBusyCursor()

    #  Save file
    #
    def OnSave(self, ev):
        tlp = wx.GetApp().GetTopWindow()
        path = None
        if os.path.isdir(self.wpath):
            wdir = self.wpath
            wfile = ""
        else:
            wdir = os.path.dirname(self.wpath)
            wfile = os.path.basename(self.wpath)
        dlg = wx.FileDialog(
            tlp, message = _("Choose a file"),
            defaultDir = wdir,
            defaultFile = wfile,
            wildcard = "Binary (*.bin)|*.bin|Intel Hex (*.hex)|*.hex|All (*.*)|*.*",
            style = wx.FD_SAVE | wx.FD_CHANGE_DIR | wx.FD_OVERWRITE_PROMPT)

        if dlg.ShowModal() == wx.ID_OK:
            path = dlg.GetPaths()[0]
            #trace(path)
        dlg.Destroy()

        if not path:
            return

        if not path.endswith('.bin'):
            alert(_("File format not handled."))
            return
        
        self.wpath = path
        f = open(path, 'wb')
        f.write(wx.GetApp().diabolo.device.mflash)
        f.close()

    #  Change settings
    #
    def OnOptions(self, ev):
        dlg = WOptions(self.parent)
        baud = dlg.baud
        port = dlg.port
        onewire = dlg.onewire
        r = dlg.ShowModal()
        dlg.Destroy()
        if r == wx.ID_OK and (baud != dlg.baud or
                              port != dlg.port or
                              onewire != dlg.onewire):
            #trace("Port: %s, baud: %s\n" % (dlg.port, dlg.baud))
            com = wx.GetApp().com
            #com = self.parent.com
            com.preferred_port = dlg.port
            com.baudrate = dlg.baud
            com.onewire = dlg.onewire
            trace(com.onewire)
            self.OnConnect(ev)


class Frame(wx.Frame):
    title = "Diabolo"
    def __init__(self):
        wx.Frame.__init__(self, None, title = Frame.title)

        vs = wx.BoxSizer(wx.VERTICAL)
        self.w_firmware = WFirmware(self)
        vs.Add(self.w_firmware, 0, wx.ALL|wx.EXPAND, 5)
        self.w_device = WDevice(self)
        vs.Add(self.w_device, 1, wx.ALL|wx.EXPAND, 5)

        self.SetSizer(vs)
        self.SetAutoLayout(True)
        vs.SetSizeHints(self)
        self.Show()
        self.timer = wx.Timer(self)
        self.timer.Start(500)
        self.Bind(wx.EVT_TIMER, self.OnTimer)

    def OnTimer(self, ev):
        #trace()
        self.w_firmware.Check()


class App(wx.App):
    def __init__(self):
        self.path = None

    # def __init__(self, options):
    #     self.cs_mod      = options.cs_mod
    #     self.path        = options.flash_burn
    #     self.run_cmd     = options.run_cmd

    #     if self.cs_mod:
    #         self.com = xcom.XCom(options.comdev, options.combps)
    #     else:
    #         self.com = com.Com(options.comdev, options.combps)
    #     self.com.onewire = options.onewire
    #     self.com.setTimeout(0.01)

    #     self.diabolo     = diabolo.Diabolo(self.com)

    #     if self.run_cmd:
    #         self.run_cmd = self.run_cmd.split(' ')

    def OnInit(self):
        # global diabolo
        # self.com = com.Com(None, "100000")
        # self.com.setTimeout(0.01)
        # self.diabolo = diabolo.Diabolo(self.com)
        self.frame = Frame() # Top window
        #self.diabolo.msg = self.frame.msg
        return 1

    def run(self):
        if platform.system() == "Linux":
            # import wx.lib.inspection
            # wx.lib.inspection.InspectionTool().Show()
            wx.App.__init__(self, 0)
        else:
            wx.App.__init__(self, redirect=False, filename="diabolog.txt", useBestVisual=True)
        self.MainLoop()


if __name__ == "__main__":
    import premain
    #from premain import *
    #from utils import *
    #import __builtin__

    #__builtin__.__dict__['msg'] = lambda *s : id
    #sys.stdout.close()
    #sys.stderr.close()

    # from optparse import OptionParser
    # parser = OptionParser(usage="usage: %prog [options] [firmware]")
    # parser.add_option("-d", "--dev", metavar="DEVICE", type="string",
    #                   default="/dev/ttyUSB0", dest="comdev", 
    #                   help="set com device (default /dev/ttyUSB0)")
    # parser.add_option("-b", "--bps", metavar="SPEED", type="int",
    #                   default=115200, dest="combps", 
    #                   help="set com speed (default 115200)")
    # parser.add_option("-1", "--single-wire", action="store_true",
    #                   default=False, dest="onewire",
    #                   help="RX/TX on the same communication wire")
    # parser.add_option("-2", "--two-wires", action="store_false",
    #                   default=False, dest="onewire",
    #                   help="RX/TX on separate communication wires")
    # parser.add_option("-f", "--file", metavar="FILE", type="string",
    #                   dest="file",
    #                   help="binary or hex file to burn")
    # parser.add_option("-x", "--runapp", metavar="FILE", type="string",
    #                   dest="run_cmd",
    #                   help="command to start when the 'run' button is pressed")
    # parser.add_option("-m", "--carspy_module", metavar="MODULE", type="int",
    #                   dest="cs_mod",
    #                   help="address (1..30) of module to access through carspy controller")
    # (options, args) = parser.parse_args()

    # (options, args) = diabolo.parse_options()

    # if len(args) == 1:
    #     options.file = args[0]

    # elif len(args) > 1:
    #     parser.print_help()
    #     sys.exit(1)

    # app = App(options)
    # app.run()

    App().run()
