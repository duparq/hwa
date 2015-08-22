
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Serial Peripheral Interface
 */

/**
 * @page atmelavr_spia Class _spia: Serial Peripheral Interface
 *
 * A class `_spia` object is a Serial Peripheral Interface. It has the following
 * @ref relatives "relatives":
 *
 *  * `pin_mosi`: the MOSI pin
 *  * `pin_miso`: the MISO pin
 *  * `pin_sck`: the SCK pin
 *  * `pin_ss`: the SS pin
 *
 * It is used by:
 *
 *  * @ref atmegax8 : `hw_spi0`
 */
#define _hw_class__spia


/**
 * @page atmelavr_spia
 * @par Interrupts
 *
 * Class `_spia` objects can trigger the following IRQs:
 *
 *  * `SPI_NAME`: transfer complete
 */


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	cr ;
  hwa_r8_t	sr ;
} hwa_spia_t ;

#endif
