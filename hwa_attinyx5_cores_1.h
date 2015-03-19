
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__corea_1.h"

//#define HWA_DCL_CORES		hwa_corea_t core0


/*	Instance	        class, name, id, address
 */
#define hw_core0		_corea, core0, 101, 0


/*	Class regs		class, rw, ra, rwm, rfm
 */
#define _hw__corea_sreg		crg, 8, 0x5F, 0xFF, 0x00
#define _hw__corea_sph		crg, 8, 0x5E, 0x03, 0x00
#define _hw__corea_spl		crg, 8, 0x5D, 0xFF, 0x00
#define _hw__corea_gimsk		crg, 8, 0x5B, 0x60, 0x00
#define _hw__corea_gifr		crg, 8, 0x5A, 0x60, 0x60
#define _hw__corea_mcucr		crg, 8, 0x55, 0xFF, 0x00
#define _hw__corea_mcusr		crg, 8, 0x54, 0x0F, 0x00
#define _hw__corea_osccal	crg, 8, 0x51, 0xFF, 0x00
#define _hw__corea_gpior2	crg, 8, 0x33, 0xFF, 0x00
#define _hw__corea_gpior1	crg, 8, 0x32, 0xFF, 0x00
#define _hw__corea_gpior0	crg, 8, 0x31, 0xFF, 0x00
#define _hw__corea_prr		crg, 8, 0x40, 0x0F, 0x00

/* #define _hw__corea_bods		cb1, mcucr, 1, 7 */
/* #define _hw__corea_pud		cb1, mcucr, 1, 6 */
/* #define _hw__corea_se		cb1, mcucr, 1, 5 */
/* #define _hw__corea_sm		cb1, mcucr, 2, 3 */
/* #define _hw__corea_bodse		cb1, mcucr, 1, 2 */
/* #define _hw__corea_isc0		cb1, mcucr, 2, 0 */

/* #define _hw__corea_wdrf		cb1, mcusr, 1, 3 */
/* #define _hw__corea_borf		cb1, mcusr, 1, 2 */
/* #define _hw__corea_extrf		cb1, mcusr, 1, 1 */
/* #define _hw__corea_porf		cb1, mcusr, 1, 0 */
/* #define _hw__corea_allrf		cb1, mcusr, 4, 0	/\* convenient *\/ */

/* #define _hw__corea_int0		cb1, gimsk, 1, 6 */
/* #define _hw__corea_pcie		cb1, gimsk, 1, 5 */

/* #define _hw__corea_intf0		cb1, gifr, 1, 6 */
/* #define _hw__corea_pcif		cb1, gifr, 1, 5 */

/* #define _hw__corea_prtim1	cb1, prr, 1, 3 */
/* #define _hw__corea_prtim0	cb1, prr, 1, 2 */
/* #define _hw__corea_prusi		cb1, prr, 1, 1 */
/* #define _hw__corea_pradc		cb1, prr, 1, 0 */


/*	INT0 class
 */
#define _hw_class_int0


/*	INT0 instance	        class, name, id, address
 */
#define hw_pin_int0		int0, pin_int0, 102, core0, pin_pb2
