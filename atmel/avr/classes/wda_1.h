
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR Watchdog timer
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_wda Class _wda: watchdog timer
 *
 * This is used by:
 *
 * * @ref attinyx4 : `watchdog0`
 * * @ref attinyx5 : `watchdog0`
 *
 * @section Interrupts
 *
 *  * `(watchdog0,irq)`: watchdog overflow
 */
#define hw_class__wda


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t	csr ;

  struct {
    uint8_t	action, timeout ;
  } config ;

} hwa_wda_t ;

#endif
