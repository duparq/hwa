
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
#define hw_c8a_countmode_loop_up		ok, 1
#define hw_c8a_countmode_loop_up_pwm		ok, 2
#define hw_c8a_countmode_loop_updown_pwm	ok, 3

#define hw_c8a_top_fixed_0xFF			ok, 1
#define hw_c8a_top_register_compare_a		ok, 2

#define hw_c8a_clock_0ne			ok, 0
#define hw_c8a_clock_stop			ok, 0
#define hw_c8a_clock_syshz			ok, 1
#define hw_c8a_clock_syshz_div_8		ok, 2
#define hw_c8a_clock_syshz_div_64		ok, 3
#define hw_c8a_clock_syshz_div_256		ok, 4
#define hw_c8a_clock_syshz_div_1024		ok, 5
#define hw_c8a_clock_ext_rising			ok, 6
#define hw_c8a_clock_ext_falling		ok, 7


/*	Number of bits
 */
#define hw_bn_c8a_isfn
#define hw_bn_c8a(...)				8


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
