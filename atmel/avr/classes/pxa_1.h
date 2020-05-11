
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Pin change interrupt controller
 */

/**
 * @page atmelavr_pxa Class _pxa: pin change interrupt controller
 *
 * A class `_pxa` object is a pin change interrupt controller.
 *
 * It is used in:
 *
 * * @ref attinyx4 : `pcic0`, `pcic1`
 * * @ref attinyx5 : `pcic0`
 * * @ref atmegax8 : `pcic0`, `pcic1`, `pcic2`
 */
#define hw_class__pxa


/**
 * @page atmelavr_pxa
 * @par Interrupts
 *
 * Class `_pxa` objects can trigger the following IRQs as soon as the state of
 * one of its monitored pins changes:
 *
 *  * `pcic0`: monitored pin change event
 */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t	msk ;
} hwa_pxa_t ;

#endif
