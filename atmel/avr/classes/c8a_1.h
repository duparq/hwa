
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
 *    * `hw_rel( COUNTER_NAME, prescaler )`
 *
 *  * two compare units with waveform generators, of class @ref atmelavr_oc8a "_oc8a":
 *    * `hw_rel( COUNTER_NAME, compare0 )` and <br>
 *      `hw_rel( COUNTER_NAME, compare1 )`
 *
 * It is used in:
 *
 *  * @ref attinyx4 : `hw_counter0`
 *  * @ref attinyx5 : `hw_counter0`
 *  * @ref atmegax8 : `hw_counter0`
 *  * @ref atmegaxu4 : `hw_counter0`
 */
#define _hw_class__c8a

/**
 * @page atmelavr_c8a
 * @par Instructions that do not produce C code
 *
 * The `hw_bn()` instruction retrieves the number of bits of the counting register:
 *
 * @code
 * #if hw_bn( COUNTER_NAME ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__c8a		, _hw_bn_c8a
#define _hw_bn_c8a(o,i,a,...)		8

/**
 * @page atmelavr_c8a
 * @par Interrupts
 *
 * Class `_c8a` objects can trigger the following IRQs:
 *
 *  * `COUNTER_NAME` or `COUNTER_NAME,overflow`: counter overflow
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;

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
