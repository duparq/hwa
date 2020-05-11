
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_ocb Class _ocb: 8-bit compare unit with waveform generator
 *
 * Class `_ocb` objects are 8-bit compare units with waveform generator. They
 * are named using the notation (COUNTER,COMPARE),
 * e.g. (counter0,compare0). They have the following relative objects:
 *
 *  * one counter: `((counter0,compare0), counter)`
 *  * one output pin: `((counter0,compare0), pin_h)`
 *  * one complementary output pin: `((counter0,compare0), pin_l)`
 *
 * They are used in:
 *
 * * @ref attinyx5 : `(counter1,compare0)`, `(counter1,compare1)`
)`
 */
#define hw_class__ocb


/**
 * @page atmelavr_ocb
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
#define HW_BITS__ocb			, _hw_bn_ocb
#define _hw_bn_ocb(o,a,...)		8


/*  Return the compare register of a _ocb
 *    HW_CODR is blued.
 */
#define hw__ocb_reg			, _hw_ocb_reg
#define _hw_ocb_reg(oo,ct,cp)		HW_XOR(ct,ocr##cp)


/**
 * @page atmelavr_ocb
 * @par Interrupts
 *
 * The compare unit can trigger an @ref using_interrupts IRQ when the
 * compare-match flag is set, one counter clock cycle after the compare register
 * matches the counting register.
 *
 * @code
 * HW_ISR(counter0,compare0)	   // "compare0" IRQ of counter 0
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

typedef struct {

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	outputh, outputl ;
  } config ;

} hwa_ocb_t ;

#endif
