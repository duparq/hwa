
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
 * `_c8b` objects are 8-bit counting units that have 4 relative objects:
 *  * one @ref atmelavr_pscb "_pscb" prescaler: `(COUNTER,prescaler)`
 *  * two @ref atmelavr_cmp8b "_cmp8b" compare units with waveform generators:
 *    `(COUNTER,compare0)` and `(COUNTER,compare1)`
 *  * one @ref atmelavr_dtga "_dtga" dead time generator: `(COUNTER,dtg)`
 *
 * They are used in:
 *  * @ref attinyx5 : `counter1`
 */
#define hw_class__c8b

/**
 * @page atmelavr_c8b
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
#define HW_BITS__c8b		, _hw_bn_c8b
#define _hw_bn_c8b(o,i,a,...)		8

/**
 * @page atmelavr_c8b
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
 * The compare units @ref atmelavr_cmp8b "_cmp8b" can also trigger IRQs.
 */

#if !defined __ASSEMBLER__

/*	Context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccr ;
  hwa_r8_t	count ;
  hwa_r8_t	compare2 ;

} hwa_c8b_t ;

#endif
