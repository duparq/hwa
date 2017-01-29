
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_c8b Class _c8b: 8-bit counter/timer
 *
 * A class `_c8b` object is an 8-bit counting unit that has 4 relative objects:
 *
 *  * one prescaler of class @ref atmelavr_pscb "_pscb":
 *    * `HW_REL( COUNTER_NAME, prescaler )`
 *
 *  * two compare units with waveform generators, of class @ref atmelavr_oc8b "_oc8b":
 *    * `HW_REL( COUNTER_NAME, compare0 )` and <br>
 *      `HW_REL( COUNTER_NAME, compare1 )`
 *
 *  * one dead time generator of class @ref atmelavr_dtga "_dtga":
 *    * `HW_REL( COUNTER_NAME, dtg )`
 *
 * It is used in:
 *
 * * @ref attinyx5 : `hw_counter1`
 */
#define _hw_class__c8b

/**
 * @page atmelavr_c8b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( COUNTER_NAME ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__c8b		, _hw_bn_c8b
#define _hw_bn_c8b(o,i,a,...)		8

/**
 * @page atmelavr_c8b
 * @par Interrupts
 *
 * Class `_c8b` objects can trigger the following IRQs:
 *
 *  * `COUNTER_NAME` or `COUNTER_NAME,overflow`: counter overflow
 */

#if !defined __ASSEMBLER__

/*	Context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccr ;
  hwa_r8_t	count ;
  hwa_r8_t	compare2 ;

} hwa_c8b_t ;

#endif
