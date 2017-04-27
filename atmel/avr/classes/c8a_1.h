
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_c8a Class _c8a: 8-bit counter/timer
 *
 * A class `_c8a` object is an 8-bit counting unit that has 3 relative objects:
 *
 *  * one prescaler of class @ref atmelavr_psca "_psca":
 *    * `HW_RELATIVE( counter0, prescaler )`
 *
 *  * two compare units with waveform generators, of class @ref atmelavr_cmp8a "_cmp8a":
 *    * `HW_RELATIVE( counter0, compare0 )` and <br>
 *	`HW_RELATIVE( counter0, compare1 )`
 *
 * It is used in:
 *
 *  * @ref attinyx4 : `counter0`
 *  * @ref attinyx5 : `counter0`
 *  * @ref atmegax8 : `counter0`
 *  * @ref atmegaxu4 : `counter0`
 */
#define _hw_class__c8a

/**
 * @page atmelavr_c8a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( counter0 ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mtd_HW_BITS__c8a		, _hw_bn_c8a
#define _hw_bn_c8a(o,i,a,...)		8

/**
 * @page atmelavr_c8a
 * @par Interrupts
 *
 * Class `_c8a` objects can trigger the following IRQs:
 *
 *  * `counter0` or `counter0,overflow`: counter overflow
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, countmode, top, overflow ;
  } config ;

  /*  Computed logical register values
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_c8a_t ;

#endif
