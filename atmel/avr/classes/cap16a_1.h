
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_cap16a Class _cap16a: 16-bit capture unit
 *
 * A class `_cap16a` object is a 16-bit capture unit. It has the following
 * relative objects:
 *
 *  * one counter, whose name is given by `HW_REL( capture0, counter )`
 *
 *  * one input pin, whose name is given by `HW_REL( capture0, pin )`
 *
 * It is used in:
 *
 *  * @ref attinyx4 : `capture10`
 *  * @ref atmegax8 : `capture10`
 */
#define _hw_class__cap16a

/**
 * @page atmelavr_cap16a
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the capture
 * register:
 *
 * @code
 * #if HW_BITS( capture0 ) != 16
 * #  error A 16-bit capture unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__cap16a		, _hw_bn_cap16a
#define _hw_bn_cap16a(o,i,a,...)			16


/**
 * @page atmelavr_cap16a
 * @par Interrupts
 *
 * The capture unit can trigger an @ref using_interrupts "anonymous IRQ" when
 * a capture event occurs.
 *
 * @code
 * HW_ISR( capture0 )
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

} hwa_cap16a_t ;

#endif
