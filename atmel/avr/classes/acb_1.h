
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
 * @defgroup atmelavr_acb Class _acb: analog comparator
 *
 * A class `_acb` object is an analog comparator.
 *
 * It is used in:
 *
 * * @ref attinyx5 : `acmp0`
 */
#define hw_class__acb

/**
 * @addtogroup atmelavr_acb
 * @par Interrupts
 *
 * Class `_acb` objects can trigger the following IRQs:
 *
 *  * `HW_IRQ(acmp0)`: comparator output event
 */

#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acb_t ;

#endif
