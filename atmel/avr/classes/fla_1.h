
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR Flash memory
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_fla Class _fla: Flash memory
 *
 * This class is used by:
 *  * @ref attinyx4 : `flash0`
 *  * @ref attinyx5 : `flash0`
 *  * @ref atmegax8 : `flash0`
 *  * @ref atmegaxu4 : `flash0`
 */
#define hw_class__fla


/*	Class logical registers
 */					
#define hw__fla_spmie		_cb1, csr, 1, 7
#define hw__fla_rwwsb		_cb1, csr, 1, 6
#define hw__fla_sigrd		_cb1, csr, 1, 5
#define hw__fla_rwwsre		_cb1, csr, 1, 4
#define hw__fla_blbset		_cb1, csr, 1, 3
#define hw__fla_pgwrt		_cb1, csr, 1, 2
#define hw__fla_pgers		_cb1, csr, 1, 1
#define hw__fla_spmen		_cb1, csr, 1, 0
