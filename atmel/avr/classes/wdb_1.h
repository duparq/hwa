
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Watchdog timer
 */

/**
 * @page atmelavr_wdb Class _wdb: watchdog timer
 *
 * A class `_wdb` object is a watchdog timer.
 *
 * It is identical to the class @ref atmelavr_wda "_wda" except that it uses
 * a different method for applying changes to the configuration.
 *
 * It is used in:
 *
 * * @ref atmegax8 : `watchdog0`
 * * @ref atmegaxu4 : `watchdog0`
 */
#define hw_class__wdb

/*	Class logical registers
 */
#define hw__wdb_if			_cb1, csr, 1, 7
#define hw__wdb_ie			_cb1, csr, 1, 6
#define hw__wdb_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw__wdb_wdce			_cb1, csr, 1, 4
#define hw__wdb_wde			_cb1, csr, 1, 3

#define hw__wdb_eie			_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define hw__wdb_ifie			_cb1, csr, 2, 6 /* convenient for clearing irq */
#define hw__wdb_wdall			_cb1, csr, 7, 0 /* convenient for turning wd off */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t	csr ;

  struct {
    uint8_t	action, timeout ;
  } config ;

} hwa_wdb_t ;

#endif
