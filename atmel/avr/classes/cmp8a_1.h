
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_cmp8a Class _cmp8a: 8-bit compare unit with waveform generator
 *
 * Class `_cmp8a` objects are 8-bit compare units with waveform generator. They
 * are named using the notation (COUNTER,COMPARE),
 * e.g. (counter0,compare0). They have the following relative objects:
 *  * one counter: `((counter0,compare0), counter)`
 *  * one output pin: `((counter0,compare0), pin)`
 *
 * They are used in:
 *
 * * @ref attinyx4 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref attinyx5 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref atmegax8 : `(counter0,compare0)`, `(counter0,compare1)`, `(counter2,compare0)`, `(counter2,compare1)`
 */
#define hw_class__cmp8a


/**
 * @page atmelavr_cmp8a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the compare
 * register:
 *
 * @code
 * #if HW_BITS( compare0 ) != 8
 * #  error A 8-bit compare unit is required!
 * #endif
 * @endcode
 */
#define HW_BITS__cmp8a			, _hw_bits_cmp8a
#define _hw_bits_cmp8a(...)		8


/**
 * @page atmelavr_cmp8a
 * @par Interrupts
 *
 * The compare unit can trigger an @ref using_interrupts IRQ when the
 * compare-match flag is set, one counter clock cycle after the compare register
 * matches the counting register.
 *
 * @code
 * HW_ISR(counter0,compare0)       // "compare0" IRQ of counter 0
 * {
 *    // Process compare event
 * }
 * @endcode
 *
 * @code
 * HW_ISR( (counter0,compare0) )   // IRQ of (counter0,compare0)
 * {
 *    // Process compare event
 * }
 * @endcode
 */


#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	reg ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	update ;
    uint8_t	output ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	com ;
  } solved ;

} hwa_cmp8a_t ;

#endif
