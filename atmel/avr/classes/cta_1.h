
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_cta Class _cta: 8-bit counter/timer
 *
 * `_cta` objects are 8-bit counter/timers used by:
 *
 *  * @ref attinyx4 : `counter0`
 *  * @ref attinyx5 : `counter0`
 *  * @ref atmegax8 : `counter0`
 *  * @ref atmegaxu4 : `counter0`
 *
 * @code
 * #if HW_BITS( counter0 ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 *
 * @par Relatives
 *
 * * `(COUNTER,prescaler)`: @ref atmelavr_psa "_psa" prescaler;
 * * `(COUNTER,compare0)`, `(COUNTER,compare1)`: @ref atmelavr_oca "_oca"
 *   compare units with waveform generators.
 *
 */
#define hw_class__cta

#define HW_BITS__cta			, _hw_bits_cta
#define _hw_bits_cta(...)		8

//#define hw__cta_bits			, _hw_bits_cta


/*  Return the counting register of a _cta
 *    HW_CODR is blued.
 */
#define hw__cta_reg			, _hw_cta_reg
#define _hw_cta_reg(o,a)		HW_XOR(o,count)


/**
 * @page atmelavr_cta
 * @par Interrupts
 *
 *  * `(COUNTER,irq)`, `(COUNTER,irq,overflow)`: triggered when the counter
 *    counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 *    it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode;
 *  * `(COUNTER,irq,compare0)`, `(COUNTER,compare0,irq)`: triggered on compare match A
 *  * `(COUNTER,irq,compare1)`, `(COUNTER,compare1,irq)`: triggered on compare match B
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;
  hwa_r8_t	ocr0 ;
  hwa_r8_t	ocr1 ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, direction, top, overflow ;
  } config ;

  /*  Computed logical register values
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

  hwa_oca_t	compare0 ;
  hwa_oca_t	compare1 ;

} hwa_cta_t ;

#endif
