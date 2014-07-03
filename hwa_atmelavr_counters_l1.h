
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1, common declarations for Atmel AVR counter-timers
 */

/*	Classes & methods
 */
#define hw_class_ocu

/*		Write compare value of an ocu
 */
#define hw_fn_hw_write_ocu	, _hw_write_ocu
#define _hw_write_ocu(t,n,i,a, value)	_hw_write_ocu_2(hw_##n##_ext, value)
#define _hw_write_ocu_2(...)		_hw_write_ocu_3(__VA_ARGS__)
#define _hw_write_ocu_3(t,n,i,a, rn,ion, v)	_hw_write_ocu_4(_hw_bits(t,n,i,a, rn), v)
#define _hw_write_ocu_4(...)		_hw_write_ocu_5(__VA_ARGS__)
#define _hw_write_ocu_5(t,...)		_hw_write_##t(t,__VA_ARGS__)

/*		Definition of the io pin associated to an ocu
 */
#define hw_fn_hw_io_ocu		, _hw_io_ocu
#define _hw_io_ocu(t,n,...)		_hw_io_ocu_2(hw_##n##_##ext)
#define _hw_io_ocu_2(...)		_hw_io_ocu_3(__VA_ARGS__)
#define _hw_io_ocu_3(t,n,i,a, oc, ion)	hw_##ion

/*		Definition of the counter associated to an ocu
 */
#define hw_fn_hw_ctr_ocu	, _hw_ctr_ocu
#define _hw_ctr_ocu(t,ocn,...)			_hw_ctr_ocu_2(hw_##ocn##_##ext)
#define _hw_ctr_ocu_2(...)			_hw_ctr_ocu_3(__VA_ARGS__)
#define _hw_ctr_ocu_3(cc,cn,ci,ca, ocr, ion)	cc,cn,ci,ca


/*	Modes for output-compare units
 */
#define hw_ocu_mode_disconnected				ok, 1
#define hw_ocu_mode_toggled_on_match				ok, 2
#define hw_ocu_mode_cleared_on_match				ok, 3
#define hw_ocu_mode_set_on_match				ok, 4
#define hw_ocu_mode_set_at_bottom_cleared_on_match		ok, 5
#define hw_ocu_mode_cleared_at_bottom_set_on_match		ok, 6
#define hw_ocu_mode_cleared_on_match_up_set_on_match_down	ok, 7
#define hw_ocu_mode_clearup_setdown				ok, 7
#define hw_ocu_mode_set_on_match_up_cleared_on_match_down	ok, 8
#define hw_ocu_mode_setup_cleardown				ok, 8


#if !defined __ASSEMBLER__

/*	Soft registers for output-compare units
 */
typedef struct {
  uint8_t 	config, mode ;
} hwa_ocu_t ;

#endif
