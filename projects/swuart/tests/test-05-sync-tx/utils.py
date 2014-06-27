#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2012-01-31 10:53:53 -*-


def hexdump(address, data):
    for c in data:
        if address % 16 == 0:
            cout('%04X:' % address)
        elif address % 8 == 0:
            cout (' --')
        address += 1
        cout(' %02X' % ord(c))
        if address % 16 == 0:
            cout('\n')
    if address % 16 != 0:
        cout('\n')


def s2hexdump(data):
    s = ""
    col = 0
    for c in data:
        if col == 8:
            s += ' --'
        col += 1
        s += ' %02X' % ord(c)
        if col == 16:
            col = 0
            s += '\n'
    return s


def s2hex(data):
    s = ""
    for c in data:
        s += ' %02X' % ord(c)
    return s[1:]
