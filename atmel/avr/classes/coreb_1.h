
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @page atmelavr_coreb Class _coreb: core of the device
 *
 * A class `_coreb` object is a core of the device.
 *
 * It is used in:
 *
 * * @ref atmegax8 : `hw_core0`
 */
#define _hw_class__coreb

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t smcr ;
  hwa_r8_t osccal ;
} hwa_coreb_t ;

#endif
