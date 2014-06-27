
/* This file is part of the HWA project.
 * Copyright (c) 2012 Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1: Atmel AVR 16-bits timer-counters model 'a'
 *
 *	Used in:	ATtinyX4 Timer 1
 *			ATmegaX8 Timer 1
 */


#define hw_c16a_clk_none		0
#define hw_c16a_clk_syshz		1
#define hw_c16a_clk_syshz_div_1		1
#define hw_c16a_clk_syshz_div_8		2
#define hw_c16a_clk_syshz_div_64	3
#define hw_c16a_clk_syshz_div_256	4
#define hw_c16a_clk_syshz_div_1024	5
#define hw_c16a_clk_ext_rising_edge	6
#define hw_c16a_clk_ext_falling_edge	7

#define hw_c16a_ocmode_disconnected	0
#define hw_c16a_ocmode_toggle		1
#define hw_c16a_ocmode_clear_on_match	2
#define hw_c16a_ocmode_set_on_match	3


/**
 * \todo
 */
#ifndef __ASSEMBLER__
typedef struct {
  hwa_r8_t  ccra ;
  hwa_r8_t  ccrb ;
  hwa_r8_t  ccrc ;
  hwa_r16_t count ;
  hwa_r16_t ocra ;
  hwa_r16_t ocrb ;
  hwa_r16_t icr ;
  hwa_r8_t  imsk ;
  hwa_r8_t  ifr ;
} hwa_c16a_t ;
#endif
