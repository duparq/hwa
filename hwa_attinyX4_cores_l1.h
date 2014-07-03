
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	ATtinyX4 core & int0
 */


/*	Core class & methods
 */
#define hw_class_core
#define hw_fn_hw_bits_core		, _hw_bits


/*	Core instance	        class, name, id, address
 */
#define hw_core0		core, core0, 1, 0x0000


/*	Core class regs		'reg', rw, ra, riv, rwm
 */
#define hw_core_sreg		reg, 8, 0x5F, 0x00, 0xFF
#define hw_core_gimsk		reg, 8, 0x5B, 0x00, 0xFF
#define hw_core_gifr		reg, 8, 0x5A, 0x00, 0x70
#define hw_core_mcucr		reg, 8, 0x55, 0x00, 0xFF
#define hw_core_osccal		reg, 8, 0x51, 0x00, 0xFF
#define hw_core_gpior0		reg, 8, 0x33, 0x00, 0xFF

#define hw_core_bods		rb1, mcucr, 1, 7
#define hw_core_pud		rb1, mcucr, 1, 6
#define hw_core_se		rb1, mcucr, 1, 5
#define hw_core_sm		rb1, mcucr, 2, 3
#define hw_core_bodse		rb1, mcucr, 1, 2
#define hw_core_isc0		rb1, mcucr, 2, 0

#define hw_core_int0		rb1, gimsk, 1, 6
#define hw_core_pcie1		rb1, gimsk, 1, 5
#define hw_core_pcie0		rb1, gimsk, 1, 4

#define hw_core_intf0		rb1, gifr, 1, 6
#define hw_core_pcif1		rb1, gifr, 1, 5
#define hw_core_pcif0		rb1, gifr, 1, 4


/*	Int0 class & methods
 */
#define hw_class_int0


/*	Int0 instance	        class, name, id, address
 */
#define hw_pin_int0		int0, pin_int0, 2,
#define hw_pin_int0_ext		hw_core0, pin_5


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior0 ;
} hwa_core_t ;

#define HWA_DCL_CORES		hwa_core_t core0 ;

#endif /* !defined __ASSEMBLER__ */
