
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
#define _hw_class__c16a
//#define _hw_pop__c16a(p,i,a,...)	__VA_ARGS__

#define hw_mthd_hw_bn__c16a		, _hw_bn__c16a
#define _hw_bn__c16a(p,i,a)		16


/*  Registers
 */
#define _hw__c16a_coma			_cb1, ccra, 2, 6
#define _hw__c16a_com0			_cb1, ccra, 2, 6
#define _hw__c16a_comb			_cb1, ccra, 2, 4
#define _hw__c16a_com1			_cb1, ccra, 2, 4

#define _hw__c16a_icnc			_cb1, ccrb, 1, 7
#define _hw__c16a_ices			_cb1, ccrb, 1, 6
#define _hw__c16a_cs			_cb1, ccrb, 3, 0
#define _hw__c16a_wgm			_cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define _hw__c16a_foca			_cb1, ccrc, 1, 7
#define _hw__c16a_focb			_cb1, ccrc, 1, 6

#define _hw__c16a_icie			_cb1, imsk, 1, 5
#define _hw__c16a_ocieb			_cb1, imsk, 1, 2
#define _hw__c16a_ociea			_cb1, imsk, 1, 1
#define _hw__c16a_oie			_cb1, imsk, 1, 0

#define _hw__c16a_icf			_cb1, ifr, 1, 5
#define _hw__c16a_ocfb			_cb1, ifr, 1, 2
#define _hw__c16a_ocfa			_cb1, ifr, 1, 1
#define _hw__c16a_ov			_cb1, ifr, 1, 0


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
    hwa_r16_t	compare0 ;
  };
  union {
    hwa_r16_t	ocrb ;
    hwa_r16_t	compare1 ;
  };
  union {
    hwa_r16_t	icr ;
    hwa_r16_t	capture0 ;
  };
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers for high-level configuration
   */
  uint8_t	clock, countmode, top, overflow ;
  uint8_t	compare0_update ;
  uint8_t	compare0_output ;
  uint8_t	compare1_update ;
  uint8_t	compare1_output ;
  uint8_t	icr_input, icr_edge, icr_filter ;

} hwa_c16a_t ;

#endif
