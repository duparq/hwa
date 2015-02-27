
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__coreb_1.h"

#define HWA_DCL_CORES		hwa_coreb_t core0


/*	Instance	        class, name, id, address
 */
#define hw_core0		_coreb, core0, 101, 0


/*	Class regs		class, rw, ra, rwm, rfm
 *				 cb1, cr, bn, bp
 */
#define hw__coreb_osccal	crg, 8, 0x66, 0xFF, 0x00
#define hw__coreb_prr		crg, 8, 0x64, 0xEF, 0x00
#define hw__coreb_sreg		crg, 8, 0x5F, 0xFF, 0x00
#define hw__coreb_sph		crg, 8, 0x5E, 0x03, 0x00
#define hw__coreb_spl		crg, 8, 0x5D, 0xFF, 0x00
#define hw__coreb_mcucr		crg, 8, 0x55, 0x73, 0x00
#define hw__coreb_mcusr		crg, 8, 0x54, 0x0F, 0x00
#define hw__coreb_smcr		crg, 8, 0x53, 0x0F, 0x00
#define hw__coreb_gpior2	crg, 8, 0x4B, 0xFF, 0x00
#define hw__coreb_gpior1	crg, 8, 0x4A, 0xFF, 0x00
#define hw__coreb_gpior0	crg, 8, 0x3E, 0xFF, 0x00
#define hw__coreb_eimsk		crg, 8, 0x3D, 0x03, 0x00
#define hw__coreb_eifr		crg, 8, 0x3C, 0x03, 0x03

#define hw__coreb_bods		cb1, mcucr, 1, 6
#define hw__coreb_bodse		cb1, mcucr, 1, 5
#define hw__coreb_pud		cb1, mcucr, 1, 4
#define hw__coreb_ivsel		cb1, mcucr, 1, 1
#define hw__coreb_ivce		cb1, mcucr, 1, 0

#define hw__coreb_wdrf		cb1, mcusr, 1, 3
#define hw__coreb_borf		cb1, mcusr, 1, 2
#define hw__coreb_extrf		cb1, mcusr, 1, 1
#define hw__coreb_porf		cb1, mcusr, 1, 0
#define hw__coreb_allrf		cb1, mcusr, 4, 0	/* convenient */

#define hw__coreb_sm		cb1, smcr, 3, 1
#define hw__coreb_se		cb1, smcr, 1, 0

#define hw__coreb_int1		cb1, eimsk, 1, 1
#define hw__coreb_int0		cb1, eimsk, 1, 0

#define hw__coreb_intf1		cb1, eifr, 1, 1
#define hw__coreb_intf0		cb1, eifr, 1, 0

#define hw__coreb_prtwi		cb1, prr, 1, 7
#define hw__coreb_prtim2	cb1, prr, 1, 6
#define hw__coreb_prtim0	cb1, prr, 1, 5
#define hw__coreb_prtim1	cb1, prr, 1, 3
#define hw__coreb_prspi		cb1, prr, 1, 2
#define hw__coreb_prusart	cb1, prr, 1, 1
#define hw__coreb_pradc		cb1, prr, 1, 0
