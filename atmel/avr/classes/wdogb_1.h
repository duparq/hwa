
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
 * * @ref atmegax8 : `watchdog0`
 * * @ref atmegaxu4 : `watchdog0`
 */
#define _hw_class__wdogb

/*	Class logical registers
 */
#define _hw_reg__wdogb_if		_cb1, csr, 1, 7
#define _hw_reg__wdogb_ie		_cb1, csr, 1, 6
#define _hw_reg__wdogb_wdp		_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw_reg__wdogb_wdce		_cb1, csr, 1, 4
#define _hw_reg__wdogb_wde		_cb1, csr, 1, 3

#define _hw_reg__wdogb_eie		_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw_reg__wdogb_ifie		_cb1, csr, 2, 6 /* convenient for clearing irq */
#define _hw_reg__wdogb_wdall		_cb1, csr, 7, 0 /* convenient for turning wd off */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t	csr ;

  struct {
    uint8_t	action, timeout ;
  } config ;

} hwa_wdogb_t ;

#endif
