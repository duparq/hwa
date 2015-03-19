
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


#include "hwa_atmelavr__ocua_1.h"


/*  Class & methods
 */
#define _hw_class__c8a
//#define _hw_pop__c8a(p,i,a,...)		__VA_ARGS__

#define hw_mthd_hw_bn__c8a		, _hw_bn_c8a
#define _hw_bn_c8a(p,i,a)		8


/*  Registers
 */
#define _hw__c8a_coma			_cb1, ccra, 2, 6
#define _hw__c8a_com0			_cb1, ccra, 2, 6 /* convenient */
#define _hw__c8a_comb			_cb1, ccra, 2, 4
#define _hw__c8a_com1			_cb1, ccra, 2, 4 /* convenient */
#define _hw__c8a_wgm			_cb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define _hw__c8a_foca			_cb1, ccrb, 1, 7
#define _hw__c8a_focb			_cb1, ccrb, 1, 6
#define _hw__c8a_cs			_cb1, ccrb, 3, 0

#ifndef HW_DEVICE_ATTINYX5
#define _hw__c8a_ocieb			_cb1, imsk, 1, 2
#define _hw__c8a_ociea			_cb1, imsk, 1, 1
#define _hw__c8a_oie			_cb1, imsk, 1, 0

#define _hw__c8a_ocfb			_cb1, ifr, 1, 2
#define _hw__c8a_ocfa			_cb1, ifr, 1, 1
#define _hw__c8a_ov			_cb1, ifr, 1, 0
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
    hwa_r8_t	compare0 ;
  };
  union {
    hwa_r8_t	ocrb ;
    hwa_r8_t	compare1 ;
  };
#ifndef HW_DEVICE_ATTINYX5
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;
#endif

  /*  Registers for high-level configuration
   */
  uint8_t	clock, countmode, top, overflow ;
  uint8_t	compare0_update, compare0_output ;
  uint8_t	compare1_update, compare1_output ;
  /* hwa_ocua_t	compare0, compare1 ; */

} hwa_c8a_t ;

#endif
