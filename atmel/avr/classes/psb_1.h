
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_psb Class _psb: clock prescaler
 *
 * A class `_psb` object is a resettable clock prescaler that can be connected
 * to one of 3 possible clocks:
 *
 *  * `ioclk`;
 *  * `pll_32MHz`;
 *  * `pll_64MHz`;
 *
 * It is used in:
 *
 * * @ref attinyx5 : `prescaler1`
 */
#define hw_class__psb


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	pllcsr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock ;
  } config ;

} hwa_psb_t ;

#endif
