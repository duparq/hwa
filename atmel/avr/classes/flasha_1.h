
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Flash memory
 */

/**
 * @page atmelavr_flasha Class _flasha: Flash memory
 *
 * A class `_flasha` object is a Flash memory.
 *
 * It is used in:
 *  * @ref attinyx4 : `hw_flash0`
 *  * @ref attinyx5 : `hw_flash0`
 *  * @ref atmegax8 : `hw_flash0`
 *  * @ref atmegaxu4 : `hw_flash0`
 */
#define _hw_class__flasha

/*	Class logical registers
 */					
#define _hw_reg__flasha_spmie		_cb1, csr, 1, 7
#define _hw_reg__flasha_rwwsb		_cb1, csr, 1, 6
#define _hw_reg__flasha_sigrd		_cb1, csr, 1, 5
#define _hw_reg__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw_reg__flasha_blbset		_cb1, csr, 1, 3
#define _hw_reg__flasha_pgwrt		_cb1, csr, 1, 2
#define _hw_reg__flasha_pgers		_cb1, csr, 1, 1
#define _hw_reg__flasha_spmen		_cb1, csr, 1, 0
