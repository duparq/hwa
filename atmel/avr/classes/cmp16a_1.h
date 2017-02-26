
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit compare unit
 */

/**
 * @page atmelavr_cmp16a Class _cmp16a: counter compare unit with waveform generator
 *
 * A class `_cmp16a` object is a 16-bit counter compare unit with waveform
 * generator. It has the following relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( COMPARE_NAME, counter )`
 *
 *  * one output pin, whose name is given by `HW_REL( COMPARE_NAME, pin )`
 *
 * It is used in:
 *
 * * @ref attinyx4 : `compare10`, `compare11`
 * * @ref atmegax8 : `compare10`, `compare11`
 */
#define _hw_class__cmp16a


/**
 * @page atmelavr_cmp16a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the compare
 * register:
 *
 * @code
 * #if HW_BITS( COMPARE_NAME ) != 16
 * #  error A 16-bit compare unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__cmp16a			, _hw_bn_cmp16a
#define _hw_bn_cmp16a(o,i,a,...)			16


/**
 * @page atmelavr_cmp16a
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

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r16_t 	reg ;

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

} hwa_cmp16a_t ;

#endif
