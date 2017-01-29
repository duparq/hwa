
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_ic16a Class _ic16a: 16-bit capture unit
 *
 * A class `_ic16a` object is a 16-bit capture unit. It has the following
 * relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( CAPTURE_NAME, counter )`
 *
 *  * one input pin, whose name is given by `HW_REL( CAPTURE_NAME, pin )`
 *
 * It is used in:
 *
 *  * @ref attinyx4 : `hw_ic10`
 *  * @ref atmegax8 : `hw_ic10`
 */
#define _hw_class__ic16a

/**
 * @page atmelavr_ic16a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the capture
 * register:
 *
 * @code
 * #if HW_BITS( CAPTURE_NAME ) != 16
 * #  error A 16-bit capture unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__ic16a			, _hw_bn_ic16a
#define _hw_bn_ic16a(o,i,a,_)			16


/**
 * @page atmelavr_ic16a
 * @par Interrupts
 *
 * The capture unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a capture event occurs.
 *
 * @code
 * HW_ISR( CAPTURE_NAME )
 * {
 *    // Process capture event
 * }
 * @endcode
 */


#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  hwa_r16_t	reg ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	input, edge, filter ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	acic, ices, icnc ;
  } solved ;

} hwa_ic16a_t ;

#endif
