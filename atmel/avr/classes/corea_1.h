
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @page atmelavr_corea Class _corea: core of the device
 *
 * A class `_corea` object is a core of the device.
 *
 * It is used in:
 *
 * * @ref attinyx4 : `core0`
 * * @ref attinyx5 : `core0`
 */
#define hw_class__corea

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t osccal ;
} hwa_corea_t ;

#endif
