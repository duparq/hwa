
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_usia _usia
 *
 * A class `_usia` object is an USI.
 */
#define _hw_class__usia


/**
 * @page atmelavr_usia_spimaster_swclk _usia_spimaster_swclk
 *
 * A class `_usia_spimaster_swclk` object is an SPI master clocked by software.
 */
#define _hw_class__usia_spimaster_swclk


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t cr ;
} hwa_usia_t ;

#endif
