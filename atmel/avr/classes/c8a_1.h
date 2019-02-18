
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
 * `_c8a` objects are 8-bit counting units that have 3 relative objects:
 *  * one @ref atmelavr_psca "_psca" prescaler: `(counter0,prescaler)`
 *  * two @ref atmelavr_cmp8a "_cmp8a" compare units with waveform generators:
 *    `(COUNTER,compare0)` and `(COUNTER,compare1)`
 *
 * They are used in:
 *
 *  * @ref attinyx4 : `counter0`
 *  * @ref attinyx5 : `counter0`
 *  * @ref atmegax8 : `counter0`
 *  * @ref atmegaxu4 : `counter0`
 */
#define hw_class__c8a

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
#define HW_BITS__c8a			, _hw_bits_c8a
#define _hw_bits_c8a(...)		8

/**
 * @page atmelavr_c8a
 * @par Interrupts
 *
 * The counting unit can trigger an @ref using_interrupts "`overflow` IRQ" when
 * it counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 * it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode.
 *
 * @code
 * HW_ISR(counter0)
 * {
 *    // Process overflow event
 * }
 * @endcode
 *
 * @code
 * HW_ISR(counter0,overflow)
 * {
 *    // Process overflow event
 * }
 * @endcode
 *
 * The compare units @ref atmelavr_cmp8a "_cmp8a" can also trigger IRQs.
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
    uint8_t	clock, direction, top, overflow ;
  } config ;

  /*  Computed logical register values
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_c8a_t ;

#endif
