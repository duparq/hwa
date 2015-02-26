
/*	Atmel AVR 8-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter0
 *			ATtinyX5 counter0
 *			ATmegaX8 counter0
 *
 *	Note: ATtinyX5 has a different cabling of masks and flags.
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*  Class & methods
 */
#define hw_class__c8a
#define _hw_pop__c8a(c,n,i,a,...)	__VA_ARGS__

#define hw_def_hw_bn__c8a		, _hw_bn_c8a
#define _hw_bn_c8a(c,n,i,a)		8


/*  Registers
 */
#define hw__c8a_coma			cb1, ccra, 2, 6
#define hw__c8a_com0			cb1, ccra, 2, 6 /* convenient */
#define hw__c8a_comb			cb1, ccra, 2, 4
#define hw__c8a_com1			cb1, ccra, 2, 4 /* convenient */
#define hw__c8a_wgm			cb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw__c8a_foca			cb1, ccrb, 1, 7
#define hw__c8a_focb			cb1, ccrb, 1, 6
#define hw__c8a_cs			cb1, ccrb, 3, 0

#ifndef HW_DEVICE_ATTINYX5
#define hw__c8a_ocieb			cb1, imsk, 1, 2
#define hw__c8a_ociea			cb1, imsk, 1, 1
#define hw__c8a_oie			cb1, imsk, 1, 0

#define hw__c8a_ocfb			cb1, ifr, 1, 2
#define hw__c8a_ocfa			cb1, ifr, 1, 1
#define hw__c8a_ov			cb1, ifr, 1, 0
#endif


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  union {
    hwa_r8_t	ocra ;
    hwa_r8_t	output0 ;
  };
  union {
    hwa_r8_t	ocrb ;
    hwa_r8_t	output1 ;
  };
#ifndef HW_DEVICE_ATTINYX5
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;
#endif

  /*  Registers for high-level configuration
   */
  uint8_t	clock, countmode, top, update, overflow ;
  uint8_t	output0_mode ;
  uint8_t	output1_mode ;

} hwa_c8a_t ;

#endif
