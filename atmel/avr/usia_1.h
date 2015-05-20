
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_usia Class _usia: Universal Serial Interface
 *
 * A class `_usia` object is an USI.
 */
#define _hw_class__usia


/**
 * @page atmelavr_usia_spimaster_swclk Class _usia_spimaster_swclk: software clocked SPI master over USI
 *
 * A class `_usia_spimaster_swclk` object is an SPI master clocked by software
 * implemented on top of the USI interface.
 *
 * Clocking is handle by HWA when `hw_write(...)` is executed.
 */
#define _hw_class__usia_spimaster_swclk


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t cr ;
} hwa_usia_t ;

#endif
