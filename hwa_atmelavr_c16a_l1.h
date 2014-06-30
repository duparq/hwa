
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1: Atmel AVR 16-bits timer-counters model 'a'
 *
 *	Used in:	ATtinyX4 Timer 1
 *			ATmegaX8 Timer 1
 */


/*	16-bit counter class 'c16a'
 */
#define hw_c16a_countmode_loop_up		ok, 1
/* #define hw_c16a_countmode_loop_up_pwm		ok, 2 */
/* #define hw_c16a_countmode_loop_updown_pwm	ok, 3 */
#define hw_c16a_countmode_loop_updown	ok, 3
/* #define hw_c16a_countmode_loop_updown_pafcpwm	ok, 4 */

#define hw_c16a_top_fixed_0xFF			ok, 1
#define hw_c16a_top_fixed_0x1FF			ok, 2
#define hw_c16a_top_fixed_0x3FF			ok, 3
#define hw_c16a_top_fixed_0xFFFF		ok, 4
#define hw_c16a_top_register_capture		ok, 5
#define hw_c16a_top_register_compare_a		ok, 6

#define hw_c16a_clock_none			ok, 0
#define hw_c16a_clock_syshz			ok, 1
#define hw_c16a_clock_syshz_div_8		ok, 2
#define hw_c16a_clock_syshz_div_64		ok, 3
#define hw_c16a_clock_syshz_div_256		ok, 4
#define hw_c16a_clock_syshz_div_1024		ok, 5
#define hw_c16a_clock_ext_rising		ok, 6
#define hw_c16a_clock_ext_falling		ok, 7


/*	Number of bits
 */
#define hw_bn_c16a_isfn
#define hw_bn_c16a(...)				16


/*	Registers for c16a controller
 */
#ifndef __ASSEMBLER__
typedef struct {
  hwa_r8_t  ccra ;
  hwa_r8_t  ccrb ;
  hwa_r8_t  ccrc ;
  hwa_r16_t count ;
  hwa_r16_t ocra ;
  hwa_r16_t ocrb ;
  union {
    hwa_r16_t icr ;
    hwa_r16_t capture ;
  };
  hwa_r8_t  imsk ;
  hwa_r8_t  ifr ;

  /*  Registers for high-level configuration
   */
  uint8_t config, countmode, top, clock, overflow_irq, update_compares ;
} hwa_c16a_t ;
#endif
