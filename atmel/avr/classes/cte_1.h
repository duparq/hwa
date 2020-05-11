
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit counter
 */

/*	This is the same as _ctd but handles 3 compare outputs. May be the same
 *	code could handle both classes.
 */

/**
 * @page atmelavr_cte Class _cte: 16-bit counter/timer
 *
 * A class `_cte` object is a 16-bit counting unit. It has the following
 * relatives:
 *
 *  * one prescaler, of class @ref atmelavr_psa "_psa": `prescaler`
 *
 *  * three compare units with waveform generators, of class @ref atmelavr_oca
 *    "_occ": `compare0`, `compare1`, and `compare2`
 *
 *  * one capture unit, of class @ref atmelavr_ica "_ica": `capture`
 *
 * It is used in:
 *
 *  * @ref atmegaxu4 : `counter1`, `counter3`
 */
#define hw_class__cte


/**
 * @page atmelavr_cte
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
#define HW_BITS__cte			, _hw_bits_cte
#define _hw_bits_cte(o,a,...)		16

#define hw__cte_bits			, _hw_bits_cte


/*  Return the counting register of a _cte
 *    HW_CODR is blued.
 */
#define hw__cte_reg			, _hw_cte_reg
#define _hw_cte_reg(o,a)		HW_XOR(o,count)


/**
 * @page atmelavr_cte
 * @par Interrupts
 *
 * Class `_cte` objects can trigger the following IRQs:
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

} hwa_cte_t ;

#endif
