
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_oc8a Class _oc8a: 8-bit compare unit with waveform generator
 *
 * A class `_oc8a` object is an 8-bit compare unit with waveform generator. It
 * has the following relative objects:
 *
 *  * one counter, whose name is given by `hw_rel( COMPARE_NAME, counter )`
 *
 *  * one output pin, whose name is given by `hw_rel( COMPARE_NAME, pin )`
 *
 * It is used in:
 *
 * * @ref attinyx4 : `hw_oc00`, `hw_oc01`
 * * @ref attinyx5 : `hw_oc00`, `hw_oc01`
 * * @ref atmegax8 : `hw_oc00`, `hw_oc01`, `hw_oc20`, `hw_oc21`
 */
#define _hw_class__oc8a


/**
 * @page atmelavr_oc8a
 * @par Instructions that do not produce C code
 *
 * The `hw_bn()` instruction retrieves the number of bits of the compare
 * register:
 *
 * @code
 * #if hw_bn( COMPARE_NAME ) != 8
 * #  error A 8-bit compare unit is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__oc8a			, _hw_bn_oc8a
#define _hw_bn_oc8a(o,i,a,_)			8


/**
 * @page atmelavr_oc8a
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
  hwa_r8_t 	reg ;

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

} hwa_oc8a_t ;

#endif
