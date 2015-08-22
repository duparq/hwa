
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @page atmelavr_pscb Class _pscb: clock prescaler
 *
 * A class `_pscb` object is a resettable clock prescaler that can be connected
 * to one of 3 possible clocks:
 *
 *  * `system`;
 *  * `pll_32MHz`;
 *  * `pll_64MHz`;
 *
 * It is used in:
 *
 * * @ref attinyx5 : `hw_psc1`
 */
#define _hw_class__pscb


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	pllcsr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock ;
  } config ;

} hwa_pscb_t ;

#endif
