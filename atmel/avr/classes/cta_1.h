
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_cta Class _cta: 8-bit counter/timer
 *
 * `_cta` objects are 8-bit counting units that have 3 relative objects:
 *  * one @ref atmelavr_psa "_psa" prescaler: `(COUNTER,prescaler)`
 *  * two @ref atmelavr_oca "_oca" compare units with waveform generators:
 *    `(COUNTER,compare0)` and `(COUNTER,compare1)`
 *
 * They are used in:
 *
 *  * @ref attinyx4 : `counter0`
 *  * @ref attinyx5 : `counter0`
 *  * @ref atmegax8 : `counter0`
 *  * @ref atmegaxu4 : `counter0`
 */
#define hw_class__cta

/**
 * @page atmelavr_cta
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
#define HW_BITS__cta			, _hw_bits_cta
#define _hw_bits_cta(...)		8

#define hw__cta_bits			, _hw_bits_cta


/*  Return the counting register of a _cta
 *    HW_CODR is blued.
 */
#define hw__cta_reg			, _hw_cta_reg
#define _hw_cta_reg(o,a)		HW_XOR(o,count)


/**
 * @page atmelavr_cta
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
 * The compare units @ref atmelavr_oca "_oca" can also trigger IRQs.
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
  hwa_r8_t	ocr0 ;
  hwa_r8_t	ocr1 ;

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

  hwa_oca_t	compare0 ;
  hwa_oca_t	compare1 ;

} hwa_cta_t ;

#endif
