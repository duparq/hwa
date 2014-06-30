
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	ATtinyX4 cores
 */

/*	Controller	        'ctr', class, name, address
 */
#define hw_core0		ctr, core, core0, 0x0000


/*	Class registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_core_sreg		mem, reg, 8, 0x5F, 0x00, 0xFF
#define hw_core_gimsk		mem, reg, 8, 0x5B, 0x00, 0xFF
#define hw_core_gifr		mem, reg, 8, 0x5A, 0x00, 0x70
#define hw_core_mcucr		mem, reg, 8, 0x55, 0x00, 0xFF
#define hw_core_osccal		mem, reg, 8, 0x51, 0x00, 0xFF
#define hw_core_gpior0		mem, reg, 8, 0x33, 0x00, 0xFF

#define hw_core_bods		mem, regb, mcucr, 1, 7
#define hw_core_pud		mem, regb, mcucr, 1, 6
#define hw_core_se		mem, regb, mcucr, 1, 5
#define hw_core_sm		mem, regb, mcucr, 2, 3
#define hw_core_bodse		mem, regb, mcucr, 1, 2
#define hw_core_isc0		mem, regb, mcucr, 2, 0

#define hw_core_int0		mem, regb, gimsk, 1, 6
#define hw_core_pcie1		mem, regb, gimsk, 1, 5
#define hw_core_pcie0		mem, regb, gimsk, 1, 4

#define hw_core_intf0		mem, regb, gifr, 1, 6
#define hw_core_pcif1		mem, regb, gifr, 1, 5
#define hw_core_pcif0		mem, regb, gifr, 1, 4


/*	Low-level interrupt pin INT0
 */
#define hw_pin_int0		ctr, int0, pin_int0, pin_5, hw_core0


#if !defined __ASSEMBLER__
typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t osccal ;
  //  hwa_r8_t pcmsk1 ;
  hwa_r8_t gpior0 ;
  //  hwa_r8_t pcmsk0 ;
} hwa_core_t ;

#define HWA_DCL_CORES		hwa_core_t core0 ;

#endif /* !defined __ASSEMBLER__ */
