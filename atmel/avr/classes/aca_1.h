
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Analog Comparator
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_aca Class _aca: analog comparator
 *
 * A class `_aca` object is an analog comparator.
 *
 * It is used in:
 *
 * * @ref attinyx4 : `acmp0`
 * * @ref atmegax8 : `acmp0`
 */
#define hw_class__aca

/**
 * @addtogroup atmelavr_aca
 * @par Interrupts
 *
 * Class `_aca` objects can trigger the following IRQs:
 *
 *  * `HW_IRQ(acmp0)`: comparator output event
 */

/*	Class logical registers
 */
#define hw__aca_acd			_cb1, csr, 1, 7
#define hw__aca_acbg			_cb1, csr, 1, 6
#define hw__aca_aco			_cb1, csr, 1, 5
#define hw__aca_if			_cb1, csr, 1, 4
#define hw__aca_ie			_cb1, csr, 1, 3
#define hw__aca_acic			_cb1, csr, 1, 2
#define hw__aca_acis			_cb1, csr, 2, 0


#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_aca_t ;

#endif
