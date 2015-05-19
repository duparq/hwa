#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os.path
sys.path.insert(1,os.path.normpath(sys.path[0]+"../../python"))
import application


#  Description of nRF24L01+ registers
#    ('NAME', command/address code, number of bytes to read)
#
nrf_registers = [ ("CONFIG",	 '\x00', 1),
		  ("EN_AA",	 '\x01', 1),
		  ("EN_RX_ADDR", '\x02', 1),
		  ("SETUP_AW",	 '\x03', 1),
		  ("SETUP_RETR", '\x04', 1),
		  ("RF_CH",	 '\x05', 1),
		  ("RF_SETUP",	 '\x06', 1),
		  ("STATUS",	 '\x07', 1),
		  ("RX_ADDR_P0", '\x0A', 5),
		  ("RX_ADDR_P1", '\x0B', 5),
		  ("DYNPD",	 '\x1C', 1),
		  ("FEATURE",	 '\x1D', 1) ]


class Application(application.Application):
    def __init__(self):
        application.Application.__init__(self)
        self.options = self.parser.parse_args()


    def run(self):
        prompt = self.connect( self.sync_5_1 )
        try:
            #
            #  Get all registers content
            #
            for r in nrf_registers:
                self.get_prompt(prompt)
                rn, stx, nrx = r
                ntx = len(stx)
                ra = ord(stx[0])
                cout("Register %-10s: 0x%02X = " % (rn,ra))
                flushout()
                self.tx('='+chr(ntx)+chr(nrx)+stx)
                r = self.rx(nrx+1)
                if r:
                    if r.endswith(prompt):
                        cout( s2hex(r[:-1])+'\n' )
                    else:
                        cerr(" received `%s`\n" % r)
                else:
                    cerr("no response.\n")
                    break
        except KeyboardInterrupt:
            cout("\n")
        finally:
            self.com.close()


if __name__ == "__main__":
    import __builtin__

    import premain
    from utils import s2hex, hexdump
    import time

    Application().run()
