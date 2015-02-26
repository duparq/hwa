
/*	Atmel AVR 16-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter1
 *			ATmegaX8 counter1 ?
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*  Class & methods
 */
#define hw_class__c16a
#define _hw_pop__c16a(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_bn__c16a		, _hw_bn__c16a
#define _hw_bn__c16a(c,n,i,a)		16


/*  Registers
 */
#define hw__c16a_coma			cb1, ccra, 2, 6
#define hw__c16a_comb			cb1, ccra, 2, 4

#define hw__c16a_icnc			cb1, ccrb, 1, 7
#define hw__c16a_ices			cb1, ccrb, 1, 6
#define hw__c16a_cs			cb1, ccrb, 3, 0
#define hw__c16a_wgm			cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define hw__c16a_foca			cb1, ccrc, 1, 7
#define hw__c16a_focb			cb1, ccrc, 1, 6

#define hw__c16a_icie			cb1, imsk, 1, 5
#define hw__c16a_ocieb			cb1, imsk, 1, 2
#define hw__c16a_ociea			cb1, imsk, 1, 1
#define hw__c16a_oie			cb1, imsk, 1, 0

#define hw__c16a_icf			cb1, ifr, 1, 5
#define hw__c16a_ocfb			cb1, ifr, 1, 2
#define hw__c16a_ocfa			cb1, ifr, 1, 1
#define hw__c16a_ov			cb1, ifr, 1, 0


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	ccrc ;
  hwa_r16_t	count ;
  union {
    hwa_r16_t	ocra ;
    hwa_r16_t	output0 ;
  };
  union {
    hwa_r16_t	ocrb ;
    hwa_r16_t	output1 ;
  };
  union {
    hwa_r16_t	icr ;
    hwa_r16_t	input0 ;
  };
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers for high-level configuration
   */
  uint8_t	clock, countmode, top, update, overflow ;
  uint8_t	output0_mode ;
  uint8_t	output1_mode ;
  uint8_t	icr_input, icr_edge, icr_filter ;

} hwa_c16a_t ;

#endif
