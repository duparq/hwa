
/*	HWA Atmel AVR test device
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_1.h"
#include "hwa_atmelavr__testclassa_1.h"

#define HWA_DCL					\
  hwa_obja_t	hw_object0a ;


/*******************************************************************************
 *									       *
 *	Object0 definition						       *
 *									       *
 *******************************************************************************/

/*  object0: class 'classa', id = 1000, base address = 0x0010
 *
 *					class, id, base address
 */
#define hw_hw_object0			_classa, 1000, 0x0010

/*  classa/register0: 8 bits at offset 0x02, all bits writeable, no flags
 *
 * 					rt, rw, ra, rwm, rfm
 */
#define _hw__classa_register0		_crg, 8, 0x02, 0xFF, 0x00

/*  classa/register1: 8 bits at offset 0x03, bits 3..0 writeable, no flags
 *
 * 					rt, rw, ra, rwm, rfm
 */
#define _hw__classa_register1		_crg, 8, 0x03, 0x0F, 0x00

/*  classa/reg01: bit 7 in register0
 *
 *					rt, register, bn, bp
 */
#define _hw__classa_reg01		_cb1, register0, 1, 7

/*  classa/reg02: bits 6 and 5 in register0
 *
 *					rt, register, bn, bp
 */
#define _hw__classa_reg02		_cb1, register0, 2, 5

/*  classa/reg03: bit2      -> bit4 in register0,
 *                bit1,bit0 -> bit3, bit2 in register 1
 *
 *					rt, r1, rbn1, rbp1, vbp1, r2, rbn2, rbp2, vbp2
 */
#define _hw__classa_reg03		_cb2, register0, 1, 4, 2, register1, 2, 2, 0
