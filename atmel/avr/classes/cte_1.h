
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 16-bit counter with three compare units and one capture unit
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_cte Class _cte: 16-bit counter with three compare units and one capture unit
 *
 * This is the same as class @ref atmelavr_ctd "_ctd" except that it handles 3
 * compare outputs.
 *
 * This class is used by:
 *
 *  * @ref atmegaxu4 : `counter1`, `counter3`
 *
 * @section atmelavr_cterl Relatives
 *
 *  * `(COUNTER,prescaler)`: class @ref atmelavr_psa "_psa" prescaler;
 *  * `(COUNTER,compare0)`: class @ref atmelavr_occ "_occ" compare unit with waveform generator;
 *  * `(COUNTER,compare1)`: class @ref atmelavr_occ "_occ" compare unit with waveform generator;
 *  * `(COUNTER,compare2)`: class @ref atmelavr_occ "_occ" compare unit with waveform generator;
 *  * `(COUNTER,capture0)`: class @ref atmelavr_ica "_ica" capture unit.
 *
 * @section atmelavr_cteirq Interrupts
 *
 *  * `(COUNTER,irq)`, `(COUNTER,irq,overflow)`: triggered when the counter
 *    counts from "max" to 0 (`after_max`) in `up_loop` counting mode, or when
 *    it counts from 0 to 1 (`after_bottom`) in `updown_loop` counting mode.
 */
#define hw_class__cte

#define HW_BITS__cte			, _hw_bits_cte
#define _hw_bits_cte(o,a,...)		16

/*  Return the counting register of a _cte
 */
#define hw__cte_reg			, _hw_cte_reg
#define _hw_cte_reg(o,a)		HW_XOR(o,count)		/* HW_CODR is blued */


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
