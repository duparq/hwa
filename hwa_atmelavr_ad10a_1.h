
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Atmel AVR 10-bit analog-digital converter model 'a'
 *
 *	Used in:	ATtinyX4
 */


/*	Symbols
 */
#define hw_is_trigger_trigger			, 1
#define hw_is_vref_vref				, 1
#define hw_is_align_align			, 1
#define hw_is_polarity_polarity			, 1
#define hw_is_input_mode_input_mode		, 1
#define hw_is_input_input			, 1
#define hw_is_gain_gain				, 1
#define hw_is_positive_input_positive_input	, 1
#define hw_is_negative_input_negative_input	, 1

#define hw_ad10a_clock_syshz_div_2		, 1	/* , ps */
#define hw_ad10a_clock_syshz_div_4		, 2
#define hw_ad10a_clock_syshz_div_8		, 3
#define hw_ad10a_clock_syshz_div_16		, 4
#define hw_ad10a_clock_syshz_div_32		, 5
#define hw_ad10a_clock_syshz_div_64		, 6
#define hw_ad10a_clock_syshz_div_128		, 7

#define hw_ad10a_trigger_manual			, 0, 0	/* , ate, ts */
#define hw_ad10a_trigger_auto			, 1, 0
#define hw_ad10a_trigger_acmp0			, 1, 1
#define hw_ad10a_trigger_int0			, 1, 2
#define hw_ad10a_trigger_counter0_compare_a	, 1, 3
#define hw_ad10a_trigger_counter0_overflow	, 1, 4
#define hw_ad10a_trigger_counter1_compare_b	, 1, 5
#define hw_ad10a_trigger_counter1_overflow	, 1, 6
#define hw_ad10a_trigger_counter1_capture	, 1, 7

#define hw_ad10a_vref_vcc			, 0	/* , refs */
#define hw_ad10a_vref_pin_aref			, 1
#define hw_ad10a_vref_bandgap			, 2

#define hw_ad10a_align_left			, 1	/* , lar */
#define hw_ad10a_align_right			, 0

#define hw_ad10a_input_mode_single_end		, im1	/* drive the parser */
#define hw_ad10a_input_mode_differential	, im2

#define hw_ad10a_input_pin_adc0			, 0
#define hw_ad10a_input_pin_adc1			, 1
#define hw_ad10a_input_pin_adc2			, 2
#define hw_ad10a_input_pin_adc3			, 3
#define hw_ad10a_input_pin_adc4			, 4
#define hw_ad10a_input_pin_adc5			, 5
#define hw_ad10a_input_pin_adc6			, 6
#define hw_ad10a_input_pin_adc7			, 7


/*	Class & methods
 */
#define hw_class_ad10a

#define hw_def_hw_bn_ad10a		, _hw_bn_ad10a
#define _hw_bn_ad10a(c,n,i,a)		10

#define hw_def_hw_read_ad10a		, _hw_read_ad10a
#define _hw_read_ad10a(c,n,i,a)		_hw_read_bits(c,n,i,a, adc)

#define hw_def_hw_trigger_ad10a		, _hw_trigger_ad10a
#define _hw_trigger_ad10a(c,n,i,a)	_hw_write_bits(c,n,i,a, sc, 1 )


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_ad10a_t ;

#endif
