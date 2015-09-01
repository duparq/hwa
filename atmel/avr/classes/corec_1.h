
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @page atmelavr_corec Class _corec: core of the device
 *
 * A class `_corec` object is a core of the device.
 *
 * It is used in:
 *
 * * @ref atmegaxu4 : `hw_core0`
 */
#define _hw_class__corec

#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t smcr ;
  hwa_r8_t osccal ;
} hwa_corec_t ;

#endif
