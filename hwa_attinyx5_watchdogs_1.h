
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#include "hwa_atmelavr__wdoga_1.h"

#define HWA_DCL_WATCHDOGS		hwa_wdoga_t watchdog0


/*	Instance			class, name, id, address
 */
#define hw_watchdog0			_wdoga, watchdog0, 901, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_watchdog0		irq, 12, watchdog0, wdie, wdif

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__wdoga_csr			crg, 8, 0x41, 0xFF, 0x80

#define hw__wdoga_wdif			cb1, csr, 1, 7
#define hw__wdoga_wdie			cb1, csr, 1, 6
#define hw__wdoga_wdp			cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw__wdoga_wdce			cb1, csr, 1, 4
#define hw__wdoga_wde			cb1, csr, 1, 3

#define hw__wdoga_wdeie			cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define hw__wdoga_wdifie		cb1, csr, 2, 6 /* convenient for clearing irq */
#define hw__wdoga_wdall			cb1, csr, 7, 0 /* convenient for turning wd off */

#define hw__wdoga_wdrf			irg, hw_core0, wdrf /* convenient */
