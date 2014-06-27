
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	ATtinyX4 cores
 */

/*	Controller	        'per', name, class, address
 */
#define hw_core0		per, core0, core, 0x0000


/*	Class registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_core_sreg		reg, sreg, 8, 0x5F, 0x00, 0xFF
#define hw_core_gimsk		reg, gimsk, 8, 0x5B, 0x00, 0xFF
#define hw_core_gifr		reg, gifr, 8, 0x5A, 0x00, 0x70
#define hw_core_mcucr		reg, mcucr, 8, 0x55, 0x00, 0xFF
#define hw_core_osccal		reg, osccal, 8, 0x51, 0x00, 0xFF
#define hw_core_pcmsk1		reg, pcmsk1, 8, 0x40, 0x00, 0x0F
#define hw_core_gpior0		reg, gpior0, 8, 0x33, 0x00, 0xFF
#define hw_core_pcmsk0		reg, pcmsk0, 8, 0x32, 0x00, 0xFF

#define hw_core_bods		regb, hw_core_mcucr, 1, 7
#define hw_core_pud		regb, hw_core_mcucr, 1, 6
#define hw_core_se		regb, hw_core_mcucr, 1, 5
#define hw_core_sm		regb, hw_core_mcucr, 2, 3
#define hw_core_bodse		regb, hw_core_mcucr, 1, 2
#define hw_core_isc0		regb, hw_core_mcucr, 2, 0
#define hw_core_pcint11		regb, hw_core_pcmsk1, 1, 3
#define hw_core_pcint10		regb, hw_core_pcmsk1, 1, 2
#define hw_core_pcint9		regb, hw_core_pcmsk1, 1, 1
#define hw_core_pcint8		regb, hw_core_pcmsk1, 1, 0

#define hw_core_pcint7		regb, hw_core_pcmsk0, 1, 7
#define hw_core_pcint6		regb, hw_core_pcmsk0, 1, 6
#define hw_core_pcint5		regb, hw_core_pcmsk0, 1, 5
#define hw_core_pcint4		regb, hw_core_pcmsk0, 1, 4
#define hw_core_pcint3		regb, hw_core_pcmsk0, 1, 3
#define hw_core_pcint2		regb, hw_core_pcmsk0, 1, 2
#define hw_core_pcint1		regb, hw_core_pcmsk0, 1, 1
#define hw_core_pcint0		regb, hw_core_pcmsk0, 1, 0

#define hw_core_int0		regb, hw_core_gimsk, 1, 6
#define hw_core_pcie1		regb, hw_core_gimsk, 1, 5
#define hw_core_pcie0		regb, hw_core_gimsk, 1, 4


#if !defined __ASSEMBLER__
typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t osccal ;
  hwa_r8_t pcmsk1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t pcmsk0 ;
} hwa_core_t ;

#define HWA_DCL_CORES		hwa_core_t core0 ;

#endif /* !defined __ASSEMBLER__ */
