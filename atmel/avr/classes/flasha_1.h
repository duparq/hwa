
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
 *  * @ref attinyx4 : `flash0`
 *  * @ref attinyx5 : `flash0`
 *  * @ref atmegax8 : `flash0`
 *  * @ref atmegaxu4 : `flash0`
 */
#define hw_class__flasha

/*	Class logical registers
 */					
#define hw__flasha_spmie		_cb1, csr, 1, 7
#define hw__flasha_rwwsb		_cb1, csr, 1, 6
#define hw__flasha_sigrd		_cb1, csr, 1, 5
#define hw__flasha_rwwsre		_cb1, csr, 1, 4
#define hw__flasha_blbset		_cb1, csr, 1, 3
#define hw__flasha_pgwrt		_cb1, csr, 1, 2
#define hw__flasha_pgers		_cb1, csr, 1, 1
#define hw__flasha_spmen		_cb1, csr, 1, 0
