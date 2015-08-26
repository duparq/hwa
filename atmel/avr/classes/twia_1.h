
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 2-wire interface
 */

/**
 * @page atmelavr_twia Class _twia: 2-wire interface
 *
 * A class `_twia` object is a 2-wire interface.
 *
 * It is used in:
 *
 *  * @ref atmegax8 : `hw_twi0`
 */
#define _hw_class__twia


/**
 * @page atmelavr_twia
 * @par Interrupts
 *
 * Class `_twia` objects can trigger the following IRQs:
 *
 *  * `TWI_NAME`
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	br ;
  hwa_r8_t 	cr ;
  hwa_r8_t 	sr ;
  hwa_r8_t 	ar ;
  hwa_r8_t 	amr ;
} hwa_twia_t ;

#endif
