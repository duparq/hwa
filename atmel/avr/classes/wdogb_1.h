
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Watchdog timer
 */

/**
 * @page atmelavr_wdogb Class _wdogb: watchdog timer
 *
 * A class `_wdogb` object is a watchdog timer.
 *
 * It is identical to the class @ref atmelavr_wdoga "_wdoga" except that it uses
 * a different method for applying changes to the configuration.
 *
 * It is used in:
 *
 * * @ref atmegax8 : `hw_wdog0`
 */
#define _hw_class__wdogb


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t 	csr ;

  struct {
    uint8_t	action, timeout ;
  } config ;

} hwa_wdogb_t ;

#endif
