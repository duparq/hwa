
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Class & methods
 */
#define hw_class_wdog
#define HW_POP_wdog(c,n,i,a,...)	__VA_ARGS__

/*	Instance			class, name, id, address
 */
#define hw_watchdog0			wdog, watchdog0, 901, 0x41

/*	Interrupts			class, vector, controller, enable, flag
 */
#define hw_irq_watchdog0		irq, 4, watchdog0, wdie, wdif

/*	Class registers			class, rw, ra, riv, rwm, rfm
 */
#define hw_wdog_csr			crg, 8, 0x41-0x41, 0x00, 0x7F, 0x80

#define hw_wdog_wdif			cb1, csr, 1, 7
#define hw_wdog_wdie			cb1, csr, 1, 6
#define hw_wdog_wdp			cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw_wdog_wdce			cb1, csr, 1, 4
#define hw_wdog_wde			cb1, csr, 1, 3
#define hw_wdog_wdcee			cb1, csr, 2, 3 /* convenience for disabling */
//#define hw_wdog_wdeie			cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* for config */

#if !defined __ASSEMBLER__

/*	Watchdog class methods
 */
#define hw_def_hw_turn_wdog		, _hw_turn_wdog
#define hw_def_hwa_turn_wdog		, _hwa_turn_wdog
#define hw_def_hw_clear_wdog		, _hw_clear_wdog
#define hw_def_hwa_clear_wdog		, _hwa_clear_wdog
#define hw_def_hwa_config_wdog		, _hwa_config_wdog

typedef struct {
  hwa_r8_t csr ;
} hwa_wdog_t ;

#define HWA_DCL_WATCHDOGS	hwa_wdog_t watchdog0

#endif /* !defined __ASSEMBLER__ */
