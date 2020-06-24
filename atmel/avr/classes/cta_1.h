
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit counter with two compare units
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_cta Class _cta: 8-bit counter with two compare units
 *
 * This class is used by:
 *
 *  * @ref attinyx4 : `counter0`
 *  * @ref attinyx5 : `counter0`
 *  * @ref atmegax8 : `counter0`
 *  * @ref atmegaxu4 : `counter0`
 *
 * @section atmelavr_ctarl Relatives
 *
 *  * `(COUNTER,prescaler)`: class @ref atmelavr_psa "_psa" prescaler;
 *  * `(COUNTER,compare0)`: class @ref atmelavr_oca "_oca" compare unit with waveform generator;
 *  * `(COUNTER,compare1)`: class @ref atmelavr_oca "_oca" compare unit with waveform generator.
 *
 * @section atmelavr_ctairq Interrupts
 *
 *  * `(COUNTER,irq)`, `(COUNTER,irq,overflow)`: triggered when the counter
 *    counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 *    it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode.
 */
#define hw_class__cta

#define HW_BITS__cta			, _hw_bits_cta
#define _hw_bits_cta(...)		8

/*  Return the counting register of a _cta
 */
#define hw__cta_reg			, _hw_cta_reg
#define _hw_cta_reg(o,a)		HW_XOR(o,count) /* HW_CODR is blued */


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
