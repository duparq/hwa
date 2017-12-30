
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit counter
 */

/**
 * @page atmelavr_c16a Class _c16a: 16-bit counter/timer
 *
 * A class `_c16a` object is a 16-bit counting unit that has 4 relative objects:
 *
 *  * one prescaler of class @ref atmelavr_psca "_psca":
 *    * `HW_RELATIVE( counter0, prescaler )`
 *
 *  * two compare units with waveform generators, of class @ref atmelavr_cmp16a "_cmp16a":
 *    * `HW_RELATIVE( counter0, compare0 )` and <br>
 *	`HW_RELATIVE( counter0, compare1 )`
 *
 *  * one capture unit of class @ref atmelavr_cap16a "_cap16a":
 *    * `HW_RELATIVE( counter0, capture0 )`
 *
 * It is used by:
 *
 *  * @ref attinyx4 : `counter1`
 *  * @ref atmegax8 : `counter1`
 */
#define _hw_class__c16a


/**
 * @page atmelavr_c16a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( counter0 ) != 16
 * #  error You must choose a 16-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_BITS__c16a		, _hw_bn_c16a
#define _hw_bn_c16a(o,i,a,...)		16

/**
 * @page atmelavr_c16a
 * @par Interrupts
 *
 * Class `_c16a` objects can trigger the following IRQs:
 *
 *  * `counter0` or `counter0,overflow`: counter overflow
 */


#if 0
/*  Class registers
 */
#define _hw_reg__c16a_compare0_mode	_cb1, ccra, 2, 6	/* COMA */
#define _hw_reg__c16a_compare1_mode	_cb1, ccra, 2, 4	/* COMB */

#define _hw_reg__c16a_icnc		_cb1, ccrb, 1, 7
#define _hw_reg__c16a_ices		_cb1, ccrb, 1, 6
#define _hw_reg__c16a_cs		_cb1, ccrb, 3, 0
#define _hw_reg__c16a_wgm		_cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define _hw_reg__c16a_foca		_cb1, ccrc, 1, 7
#define _hw_reg__c16a_focb		_cb1, ccrc, 1, 6

#define _hw_reg__c16a_ieic		_cb1, imsk, 1, 5
#define _hw_reg__c16a_iecm1		_cb1, imsk, 1, 2
#define _hw_reg__c16a_iecm0		_cb1, imsk, 1, 1
#define _hw_reg__c16a_ieov		_cb1, imsk, 1, 0

#define _hw_reg__c16a_ific		_cb1, ifr, 1, 5
#define _hw_reg__c16a_ifcm1		_cb1, ifr, 1, 2
#define _hw_reg__c16a_ifcm0		_cb1, ifr, 1, 1
#define _hw_reg__c16a_ifov		_cb1, ifr, 1, 0
#endif


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	ccrc ;
  hwa_r16_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock,countmode, top, overflow ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_c16a_t ;

#endif
