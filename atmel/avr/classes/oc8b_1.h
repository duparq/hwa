
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_oc8b Class _oc8b: 8-bit compare unit with waveform generator
 *
 * A class `_oc8b` object is an 8-bit compare unit with waveform generator that
 * drives two complementary outputs. It has the following relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( COMPARE_NAME, counter )`
 *
 *  * one output pin, whose name is given by `HW_REL( COMPARE_NAME, pin_h )`
 *
 *  * one complementary output pin, whose name is given by `HW_REL( COMPARE_NAME, pin_l )`
 *
 * It is used in:
 *
 * * @ref attinyx5 : `hw_oc10`, `hw_oc11`
 */
#define _hw_class__oc8b


/**
 * @page atmelavr_oc8b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the compare
 * register:
 *
 * @code
 * #if HW_BITS( COMPARE_NAME ) != 8
 * #  error A 8-bit compare unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__oc8b			, _hw_bn_oc8b
#define _hw_bn_oc8b(o,i,a,...)			8


/**
 * @page atmelavr_oc8b
 * @par Interrupts
 *
 * The compare unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a compare event occurs:
 *
 * @code
 * HW_ISR( COMPARE_NAME )
 * {
 *    // Process compare event
 * }
 * @endcode
 */


#if !defined __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	reg ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	outputh, outputl ;
  } config ;

} hwa_oc8b_t ;

#endif
