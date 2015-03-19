
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#include "hwa_atmelavr__wdogb_1.h"

#define HWA_DCL_WATCHDOGS		hwa_wdogb_t watchdog0


/*	Instance			class, name, id, address
 */
#define hw_watchdog0			_wdogb, watchdog0, 109, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_watchdog0		irq, 6, watchdog0, wdie, wdif

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__wdogb_csr			crg, 8, 0x60, 0xFF, 0x80

#define _hw__wdogb_wdif			cb1, csr, 1, 7
#define _hw__wdogb_wdie			cb1, csr, 1, 6
#define _hw__wdogb_wdp			cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw__wdogb_wdce			cb1, csr, 1, 4
#define _hw__wdogb_wde			cb1, csr, 1, 3

#define _hw__wdogb_wdeie			cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw__wdogb_wdifie		cb1, csr, 2, 6 /* convenient for clearing irq */
#define _hw__wdogb_wdall			cb1, csr, 7, 0 /* convenient for turning wd off */

#define _hw__wdogb_wdrf			irg, hw_core0, wdrf /* convenient */
