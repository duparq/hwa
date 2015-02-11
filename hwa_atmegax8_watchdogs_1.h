
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Class & methods
 */
#define hw_class_wdogB
#define _hw_pop_wdogB(c,n,i,a,...)	__VA_ARGS__

/*	Instance			class, name, id, address
 */
#define hw_watchdog0			wdogB, watchdog0, 109, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_watchdog0		irq, 6, watchdog0, wdie, wdif

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw_wdogB_csr			crg, 8, 0x60, 0xFF, 0x80
#define  hw_wdogB_wdif			 cb1, csr, 1, 7
#define  hw_wdogB_wdie			 cb1, csr, 1, 6
#define  hw_wdogB_wdp			 cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define  hw_wdogB_wdce			 cb1, csr, 1, 4
#define  hw_wdogB_wde			 cb1, csr, 1, 3

#define  hw_wdogB_wdifie		 cb1, csr, 2, 6 /* convenient for clearing irq */
#define  hw_wdogB_wdall			 cb1, csr, 7, 0 /* convenient for turning wd off */


#if !defined __ASSEMBLER__

typedef struct {
  uint8_t	action, timeout ;
  hwa_r8_t 	csr ;
} hwa_wdogB_t ;

#define HWA_DCL_WATCHDOGS		hwa_wdogB_t watchdog0

#endif /* !defined __ASSEMBLER__ */
