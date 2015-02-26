
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Atmel AVR core model 'a'
 *
 *	Used in: ATtinyX4
 *		 ATtinyX5
 */


/*  Class & methods
 */
#define hw_class__corea
#define _hw_pop__corea(c,n,i,a,...)	__VA_ARGS__


/*  Register definitions
 */
#define hw__corea_bods		cb1, mcucr, 1, 7
#define hw__corea_pud		cb1, mcucr, 1, 6
#define hw__corea_se		cb1, mcucr, 1, 5
#define hw__corea_sm		cb1, mcucr, 2, 3
#define hw__corea_bodse		cb1, mcucr, 1, 2
#define hw__corea_isc0		cb1, mcucr, 2, 0

#define hw__corea_wdrf		cb1, mcusr, 1, 3
#define hw__corea_borf		cb1, mcusr, 1, 2
#define hw__corea_extrf		cb1, mcusr, 1, 1
#define hw__corea_porf		cb1, mcusr, 1, 0
#define hw__corea_allrf		cb1, mcusr, 4, 0	/* convenient */

#define hw__corea_int0		cb1, gimsk, 1, 6
#define hw__corea_pcie1		cb1, gimsk, 1, 5
#define hw__corea_pcie0		cb1, gimsk, 1, 4

#define hw__corea_intf0		cb1, gifr, 1, 6
#define hw__corea_pcif1		cb1, gifr, 1, 5
#define hw__corea_pcif0		cb1, gifr, 1, 4

#define hw__corea_prtim1	cb1, prr, 1, 3
#define hw__corea_prtim0	cb1, prr, 1, 2
#define hw__corea_prusi		cb1, prr, 1, 1
#define hw__corea_pradc		cb1, prr, 1, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t sreg ;
  hwa_r8_t gimsk ;
  hwa_r8_t gifr ;
  hwa_r8_t mcucr ;
  hwa_r8_t mcusr ;
  hwa_r8_t osccal ;
  hwa_r8_t gpior2 ;
  hwa_r8_t gpior1 ;
  hwa_r8_t gpior0 ;
  hwa_r8_t prr ;
} hwa_corea_t ;

#endif
