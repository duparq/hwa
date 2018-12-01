
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit counter
 */

/*	This is the same as _c16a but handles 3 compare outputs. May be the same
 *	code could handle both classes.
 */

/**
 * @page atmelavr_c16b Class _c16b: 16-bit counter/timer
 *
 * A class `_c16b` object is a 16-bit counting unit. It has the following
 * relatives:
 *
 *  * one prescaler, of class @ref atmelavr_psca "_psca": `prescaler`
 *
 *  * three compare units with waveform generators, of class @ref atmelavr_cmp8a
 *    "_cmp16a": `compare0`, `compare1`, and `compare2`
 *
 *  * one capture unit, of class @ref atmelavr_cap16a "_cap16a": `capture`
 *
 * It is used in:
 *
 *  * @ref atmegaxu4 : `counter1`, `counter3`
 */
#define hw_class__c16b


/**
 * @page atmelavr_c16b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( counter0 ) != 16
 * #  error You must choose a 16-bit counter!
 * #endif
 * @endcode
 */
#define HW_BITS__c16b		, _hw_bn_c16b
#define _hw_bn_c16b(o,i,a,...)		16

/**
 * @page atmelavr_c16b
 * @par Interrupts
 *
 * Class `_c16b` objects can trigger the following IRQs:
 *
 *  * `counter0` or `counter0,overflow`: counter overflow
 */


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	ccrc ;
  hwa_r16_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, direction, top, overflow ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_c16b_t ;

#endif
