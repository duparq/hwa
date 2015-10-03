#!/usr/bin/env python
# -*- coding: utf-8 -*- Last modified: 2015-09-23 17:10:55 -*-


def rem_hexdump(address, data):
    s = ""
    for c in data:
        if address % 16 == 0:
            s += '\n%04X:' % address
        elif address % 8 == 0:
            s += ' --'
        address += 1
        s += ' %02X' % ord(c)
    return s[1:]


def hexdump(address, data):
    s = ""
    line = ""
    oldline = ""
    for c in data:
        if address % 16 == 0:
            line = "\n%08x " % address
        else:
            if address % 8 == 0:
                # line += ' --'
                line += ' '

        line += " %02x" % ord(c)
        address += 1

        if address % 16 == 0:
            if line[10:] == oldline[10:]:
                if not s.endswith("*"):
                    s += "\n*"
            else:
                s += line
                oldline = line
    if address % 16 != 0:
        s += line
    return s[1:]


def s2hex(data):
    if data is None:
        return ""
    s = ""
    for c in data:
        s += ' %02X' % ord(c)
    return s[1:]
