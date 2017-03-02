
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Watchdog timer
 */

/**
 * @page atmelavr_wdoga Class _wdoga: watchdog timer
 *
 * A class `_wdiga` object is a watchdog timer.
 *
 * It is used in:
 *
 * * @ref attinyx4 : `watchdog0`
 * * @ref attinyx5 : `watchdog0`
 */
#define _hw_class__wdoga


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t	csr ;

  struct {
    uint8_t	action, timeout ;
  } config ;

} hwa_wdoga_t ;

#endif
