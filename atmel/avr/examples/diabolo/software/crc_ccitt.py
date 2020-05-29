#!/usr/bin/env python3
# -*- coding: utf-8 -*- Last modified: 2020-05-26 19:53:58 -*-


class CRC:

    @staticmethod
    def init():
        return 0xFFFF

    @staticmethod
    def add(value, v):
        tmp = (value >> 8) ^ v
        value = ((value << 8) ^ CRC.tab[tmp]) & 0xFFFF
        return value

    @staticmethod
    def check(data):
        if not isinstance(data, (bytes,bytearray)):
            raise Exception("type is %s, not bytes" % repr(type(data)))
        value = 0xFFFF
        for c in data:
            tmp = (value >> 8) ^ c
            value = ((value << 8) ^ CRC.tab[tmp]) & 0xFFFF
        return value


#  Executed when module is loaded
#    Initialize the CRC table
#
CRC.tab=256*[[]]
for i in range(256):
    crc=0
    c = i << 8
    for j in range(8):
        if (crc ^ c) & 0x8000:
            crc = (crc << 1) ^ 0x1021
        else:
            crc = crc << 1
        c = c << 1
        crc = crc & 0xffff
    CRC.tab[i]=crc

# cout("CRC table:\n")
# s = ""
# for i in xrange(256):
#     s += "%04X " % self.tab[i]
#     if i%16 == 15:
#         s += "\n"
# cout(s)
