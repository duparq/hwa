
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Class & methods
 */
#define hw_class_wdog
#define _hw_pop_wdog(c,n,i,a,...)	__VA_ARGS__

/*	Instance			class, name, id, address
 */
#define hw_watchdog0			wdog, watchdog0, 901, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_watchdog0		irq, 12, watchdog0, wdie, wdif

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw_wdog_csr			crg, 8, 0x41, 0xFF, 0x80

#define hw_wdog_wdif			cb1, csr, 1, 7
#define hw_wdog_wdie			cb1, csr, 1, 6
#define hw_wdog_wdp			cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw_wdog_wdce			cb1, csr, 1, 4
#define hw_wdog_wde			cb1, csr, 1, 3

#define hw_wdog_wdifie			cb1, csr, 2, 6 /* convenient for clearing irq */
#define hw_wdog_wdall			cb1, csr, 7, 0 /* convenient for turning wd off */
//#define hw_wdog_wdcee			cb1, csr, 2, 3 /* convenient for disabling */
//#define hw_wdog_wdeie			cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* for config */

#if !defined __ASSEMBLER__

typedef struct {
  uint8_t	state ;
  hwa_r8_t 	csr ;
} hwa_wdog_t ;

#define HWA_DCL_WATCHDOGS	hwa_wdog_t watchdog0

#endif /* !defined __ASSEMBLER__ */
