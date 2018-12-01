
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Analog Comparator
 */

/**
 * @page atmelavr_acmpb Class _acmpb: analog comparator
 *
 * A class `_acmpb` object is an analog comparator.
 *
 * It is used in:
 *
 * * @ref attinyx5 : `acmp0`
 */
#define hw_class__acmpb

/**
 * @page atmelavr_acmpb
 * @par Interrupts
 *
 * Class `_acmpb` objects can trigger the following IRQs:
 *
 *  * `HW_IRQ(acmp0)`: comparator output event
 */

#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acmpb_t ;

#endif
