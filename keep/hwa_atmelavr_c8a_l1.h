
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


/*	Timers count modes
 */
#define hw_c8a_countmode_loop_up		ok, 1
#define hw_c8a_countmode_loop_up_pwm		ok, 2
#define hw_c8a_countmode_loop_updown_pwm	ok, 3

#define hw_c8a_toptype_max			ok, 1
#define hw_c8a_toptype_reg			ok, 2

#define hw_c8a_clk_none				ok, 0
#define hw_c8a_clk_stop				ok, 0
#define hw_c8a_clk_syshz			ok, 1
#define hw_c8a_clk_syshz_div_1			ok, 1
#define hw_c8a_clk_syshz_div_8			ok, 2
#define hw_c8a_clk_syshz_div_64			ok, 3
#define hw_c8a_clk_syshz_div_256		ok, 4
#define hw_c8a_clk_syshz_div_1024		ok, 5
#define hw_c8a_clk_ext_rising_edge		ok, 6
#define hw_c8a_clk_ext_falling_edge		ok, 7

/*	Output-compare unit mode for both oca & ocb
 */
#define hw_c8a_ocmode_disconnected				ok, 1
#define hw_c8a_ocmode_toggled_on_match				ok, 2
#define hw_c8a_ocmode_cleared_on_match				ok, 3
#define hw_c8a_ocmode_set_on_match				ok, 4
#define hw_c8a_ocmode_set_at_bottom_cleared_on_match		ok, 5
#define hw_c8a_ocmode_cleared_at_bottom_set_on_match		ok, 6
#define hw_c8a_ocmode_cleared_on_match_up_set_on_match_down	ok, 7
#define hw_c8a_ocmode_set_on_match_up_cleared_on_match_down	ok, 8


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
  uint8_t config, countmode, toptype, clk ;
} hwa_c8a_t ;


/** \brief	Configuration of output-compare pin
 */
typedef struct {
  uint8_t 	config, mode ;
} hwa_c8aoc_t ;
#endif
