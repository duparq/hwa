
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	Atmel AVR 8-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 Timer 0
 *			ATtinyX5 Timer 0
 *			ATmegaX8 Timer 0
 */



/*	8-bit counter class 'c8a'
 */
#define hw_c8a_countmode_loop_up		, 1
#define hw_c8a_countmode_loop_up_pwm		, 2
#define hw_c8a_countmode_loop_updown_pwm	, 3

#define hw_c8a_top_fixed_0xFF			, 1
#define hw_c8a_top_register_compare_a		, 2

#define hw_c8a_clock_0ne			, 0
#define hw_c8a_clock_stop			, 0
#define hw_c8a_clock_syshz			, 1
#define hw_c8a_clock_syshz_div_8		, 2
#define hw_c8a_clock_syshz_div_64		, 3
#define hw_c8a_clock_syshz_div_256		, 4
#define hw_c8a_clock_syshz_div_1024		, 5
#define hw_c8a_clock_ext_rising			, 6
#define hw_c8a_clock_ext_falling		, 7


/*	Generic functions
 */
#define hw_class_c8a

#define hw_fn_hw_addr_c8a		, _hw_addr_ctr
#define hw_fn_hw_bits_c8a		, _hw_bits

#define hw_fn_hw_bn_c8a			, _hw_bn_c8a
#define _hw_bn_c8a(cc,cn,ci,ca)		8


/**
 * \todo
 */
#if !defined __ASSEMBLER__
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t ocrb ;
  hwa_r8_t imsk ;
  hwa_r8_t ifr ;
  hwa_r8_t ocra ;
  hwa_r8_t ccrb ;
  hwa_r8_t count ;
  hwa_r8_t ccra ;

  /*  Software registers for configuration
   */
  uint8_t config, countmode, top, clock ;
} hwa_c8a_t ;

#endif
