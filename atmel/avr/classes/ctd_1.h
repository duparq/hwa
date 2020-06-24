
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 16-bit counter with two compare units and one capture unit
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_ctd Class _ctd: 16-bit counter with two compare units and one capture unit
 *
 * This class is used by:
 *
 *  * @ref attinyx4 : `counter1`
 *  * @ref atmegax8 : `counter1`
 *
 * @section atmelavr_ctdrl Relatives
 *
 *  * `(COUNTER,prescaler)`: class @ref atmelavr_psa "_psa" prescaler;
 *  * `(COUNTER,compare0)`: class @ref atmelavr_occ "_occ" compare unit with waveform generator;
 *  * `(COUNTER,compare1)`: class @ref atmelavr_occ "_occ" compare unit with waveform generator;
 *  * `(COUNTER,capture0)`: class @ref atmelavr_ica "_ica" capture unit.
 *
 * @section atmelavr_ctdirq Interrupts
 *
 *  * `(COUNTER,irq)`, `(COUNTER,irq,overflow)`: triggered when the counter
 *    counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 *    it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode.
 */
#define hw_class__ctd

#define HW_BITS__ctd			, _hw_bits_ctd
#define _hw_bits_ctd(...)		16

/*  Return the counting register of a _ctd
 */
#define hw__ctd_reg			, _hw_ctd_reg
#define _hw_ctd_reg(o,a)		HW_XOR(o,count)		/* HW_CODR is blued */


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r16_t	ocr0 ;
  hwa_r16_t	ocr1 ;
  hwa_r16_t	icr0 ;		/* can store top count value */
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

  hwa_occ_t	compare0 ;
  hwa_occ_t	compare1 ;
  hwa_ica_t	capture0 ;

} hwa_ctd_t ;

#endif
