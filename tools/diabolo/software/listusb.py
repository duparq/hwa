#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2013-12-27 13:12:58 -*-

#from premain import *
import premain
import usb

#busses = usb.busses()
#usblist = []

for bus in usb.busses():
        for dev in bus.devices:
                cout("%s: %04x-%04x\n" % (dev.filename, dev.idVendor, dev.idProduct))

# for bus in busses:
#         devices = bus.devices
#         for dev in devices:
# 		print "Device:", dev.filename
#                 print "  Device class:",dev.deviceClass
#                 print "  Device sub class:",dev.deviceSubClass
#                 print "  Device protocol:",dev.deviceProtocol
#                 print "  Max packet size:",dev.maxPacketSize
#                 print "  idVendor: %d (0x%04x)" % (dev.idVendor, dev.idVendor)
#                 print "  idProduct: %d (0x%04x)" % (dev.idProduct, dev.idProduct)
#                 print "  Device Version:",dev.deviceVersion
# 		for config in dev.configurations:
#                 	print "  Configuration:", config.value
#                 	print "    Total length:", config.totalLength 
#                 	print "    selfPowered:", config.selfPowered
#                 	print "    remoteWakeup:", config.remoteWakeup
#                 	print "    maxPower:", config.maxPower
#                 	for intf in config.interfaces:
#                 		print "    Interface:",intf[0].interfaceNumber
#                 		for alt in intf:
#                 			print "    Alternate Setting:",alt.alternateSetting
#                 			print "      Interface class:",alt.interfaceClass
#                 			print "      Interface sub class:",alt.interfaceSubClass
#                 			print "      Interface protocol:",alt.interfaceProtocol
#                 			for ep in alt.endpoints:
#                 				print "      Endpoint:",hex(ep.address)
#                 				print "        Type:",ep.type
#                 				print "        Max packet size:",ep.maxPacketSize
#                 				print "        Interval:",ep.interval

# usb_vendor=0x067B
# usb_product=0x2303

# # find our device
# dev = usb.core.find(idVendor=usb_vendor, idProduct=usb_product)

# # was it found?
# if dev is None:
#     raise ValueError('Device not found')
# else:
#     print 'Device found!'

# # set the active configuration. With no arguments, the first
# # configuration will be the active one
# dev.set_configuration()

# # get an endpoint instance
# cfg = dev.get_active_configuration()
# intf = cfg[(0,0)]

# ep = usb.util.find_descriptor(
#     intf,
#     # match the first OUT endpoint
#     custom_match = \
        #     lambda e: \
        #         usb.util.endpoint_direction(e.bEndpointAddress) == \
        #         usb.util.ENDPOINT_OUT
# )

# assert ep is not None

# # write the data
# ep.write('test')
