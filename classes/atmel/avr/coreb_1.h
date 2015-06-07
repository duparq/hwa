
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions for Atmel AVR core model 'b' that do not produce C code
 *
 *	Used in: ATmegaX8
 */

/**
 * @page atmelavr_coreb Class _coreb: core of the device
 * A class `_coreb` object is a core of the device.
 */
#define _hw_class__coreb

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t eimsk ;
  hwa_r8_t eifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t smcr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_coreb_t ;

#endif
