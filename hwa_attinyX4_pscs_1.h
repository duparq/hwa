
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Timers prescaler
 */


#define hw_class_psc
#define HW_POP_psc(c,n,i,a,...)		__VA_ARGS__

/*	Instance			class, name, id, address
 */
#define hw_prescaler0			psc, prescaler0, 500, 0

/*	Registers			class, rw, ra, rwm, rfm
 */
#define hw_psc_cr			crg, 8, 0x43, 0x81, 0x00

/*	Bits
 */
#define hw_psc_tsm			cb1, cr, 1, 7
#define hw_psc_psr			cb1, cr, 1, 0


#define hw_def_hw_clear_psc		, _hw_clear_psc
#define _hw_clear_psc(c,n,i,a)		_hw_write_reg(c,n,i,a, psr, 1)

#define hw_def_hw_lock_to_zero_psc	, _hw_lock0_psc
#define _hw_lock0_psc(c,n,i,a)		_hw_write_reg(c,n,i,a, tsm, 1)

#define hw_def_hw_release_psc		, _hw_release_psc
#define _hw_release_psc(c,n,i,a)	_hw_write_reg(c,n,i,a, tsm, 0)
