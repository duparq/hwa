
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit counter with two compare units and one dead-time generator
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_ctb Class _ctb: 8-bit counter with two compare units and one dead-time generator
 *
 * This class is used by:
 *
 *  * @ref attinyx5 : `counter1`
 *
 * @section atmelavr_ctbrl Relatives
 *
 *  * `(COUNTER,prescaler)`: class @ref atmelavr_psb "_psb" prescaler
 *  * `(COUNTER,compare0)`: class @ref atmelavr_ocb "_ocb" compare unit with waveform generator
 *  * `(COUNTER,compare1)`: class @ref atmelavr_ocb "_ocb" compare unit with waveform generator
 *  * `(COUNTER,dtg)`: class @ref atmelavr_dtga "_dtga" dead time generator
 *
 * @section atmelavr_ctbirq Interrupts
 *
 *  * `(COUNTER,irq)`, `(COUNTER,irq,overflow)`: triggered when the counter
 *    counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 *    it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode.
 */
#define hw_class__ctb

#define HW_BITS__ctb			, _hw_bits_ctb
#define _hw_bits_ctb(o,a,...)		8

#define hw__ctb_bits			, _hw_bits_ctb


/*  Return the counting register of a _ctb
 */
#define hw__ctb_reg			, _hw_ctb_reg
#define _hw_ctb_reg(o,a)		HW_XOR(o,count)		/* HW_CODR is blued */


#if !defined __ASSEMBLER__

/*	Context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccr ;
  hwa_r8_t	count ;
  hwa_r8_t	ocr0 ;
  hwa_r8_t	ocr1 ;
  hwa_r8_t	ocr2 ;
  hwa_r8_t	dta ;
  hwa_r8_t	dtb ;
  hwa_r8_t	dtps ;

  hwa_ocb_t	compare0 ;
  hwa_ocb_t	compare1 ;
} hwa_ctb_t ;

#endif
