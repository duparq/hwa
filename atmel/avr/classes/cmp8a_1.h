
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
 * A class `_cmp8a` object is an 8-bit compare unit with waveform generator. It
 * has the following relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( compare0, counter )`
 *
 *  * one output pin, whose name is given by `HW_REL( compare0, pin )`
 *
 * It is used in:
 *
 * * @ref attinyx4 : `compare00`, `compare01`
 * * @ref attinyx5 : `compare00`, `compare01`
 * * @ref atmegax8 : `compare00`, `compare01`, `compare20`, `compare21`
 */
#define _hw_class__cmp8a


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
#define _hw_mthd_HW_BITS__cmp8a		, _hw_bn_cmp8a
#define _hw_bn_cmp8a(o,i,a,...)			8


/**
 * @page atmelavr_cmp8a
 * @par Interrupts
 *
 * The compare unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a compare event occurs:
 *
 * @code
 * HW_ISR( compare0 )
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
