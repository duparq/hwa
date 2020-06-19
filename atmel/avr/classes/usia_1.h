
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal Serial Interface
 */

/**
 * @page atmelavr_usia Class _usia: Universal Serial Interface
 *
 * A class `_usia` object is an USI.
 */
#define hw_class__usia


/**
 * @page atmelavr_usia_spimaster_swclk Class _usia_spimaster_swclk: software clocked SPI master over USI
 *
 * A class `_usia_spimaster_swclk` object is an SPI master clocked by software
 * implemented on top of the USI interface.
 *
 * Clocking is handle by HWA when `hw(write,...)` is executed.
 *
 * @note This needs to be rewritten.
 */
/*  FIXME: need a constructor HW_SPI( interface, USI, ... ) and seperate files for implementation.
 */
#define hw_class__usia_spimaster_swclk


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t cr ;
} hwa_usia_t ;

#endif
