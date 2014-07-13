
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1, common declarations for Atmel AVR counter-timers
 */


/*	Parameters for counter units
 */
#define hw_counter_overflow_at_bottom		, 1
#define hw_counter_overflow_at_top		, 2
#define hw_counter_overflow_at_max		, 3

#define hw_counter_update_immediately		, 1
#define hw_counter_update_at_bottom		, 2
#define hw_counter_update_at_top		, 3


/*	Compare units
 */
#define hw_class_ocu

/*		Parameters for compare units
 */
#define hw_ocu_mode_disconnected				, 1	/* Non-PWM */
#define hw_ocu_mode_toggle_on_match				, 2	/* Non-PWM */
#define hw_ocu_mode_clear_on_match				, 3	/* Non-PWM */
#define hw_ocu_mode_set_on_match				, 4	/* Non-PWM */

#define hw_ocu_mode_set_at_bottom_clear_on_match		, 5	/* Fast PWM */
#define hw_ocu_mode_clear_at_bottom_set_on_match		, 6

#define hw_ocu_mode_clear_on_match_up_set_on_match_down		, 7
#define hw_ocu_mode_set_on_match_up_clear_on_match_down		, 8

/*	Configure an compare output unit
 *
 *		The only possible mode here is 'disconnected' since we do not
 *		know the counter unit configuration.
 */
#define hw_def_hw_config_ocu		, _hw_config_ocu

#define hw_is_disconnected_disconnected		, 1

#define _hw_config_ocu(c,n,i,a, mode)	\
  HW_G2(_hw_config_ocu, HW_IS(disconnected,mode))(n,mode)
#define _hw_config_ocu_0(n,mode)					\
  HW_ERR( "`disconnected` is the only acceptable mode for hw_config(ocu,...)." )
#define _hw_config_ocu_1(n,mode)	_hw_config_ocu_2(hw_##n##_ext)
#define _hw_config_ocu_2(...)		_hw_config_ocu_3(__VA_ARGS__)
#define _hw_config_ocu_3(c,n,i,a, r,io)		\
  _hw_write_bits(c,n,i,a, com##r, 0);

/*		Write the compare register of a counter compare unit
 */
#define hw_def_hw_write_ocu		, _hw_write_ocu
#define _hw_write_ocu(c,n,i,a, v)		_hw_write_ocu_2(hw_##n##_ext, v)
#define _hw_write_ocu_2(...)			_hw_write_ocu_3(__VA_ARGS__)
#define _hw_write_ocu_3(c,n,i,a, r,io, v)	_hw_write_bits(c,n,i,a,r,v)

/*		Definition of the io pin associated to an ocu
 */
#define hw_def_hw_io_ocu		, _hw_io_ocu
#define _hw_io_ocu(t,n,...)			_hw_io_ocu_2(hw_##n##_##ext)
#define _hw_io_ocu_2(...)			_hw_io_ocu_3(__VA_ARGS__)
#define _hw_io_ocu_3(t,n,i,a, oc, ion)		hw_##ion

/*		Definition of the counter associated to an ocu
 */
#define hw_def_hw_ctr_ocu		, _hw_ctr_ocu
#define _hw_ctr_ocu(t,ocn,...)			_hw_ctr_ocu_2(hw_##ocn##_##ext)
#define _hw_ctr_ocu_2(...)			_hw_ctr_ocu_3(__VA_ARGS__)
#define _hw_ctr_ocu_3(cc,cn,ci,ca, ocr, ion)	cc,cn,ci,ca


/*	Capture units
 */
#define hw_class_icu

/*		Parameters for capture units
 */
#define hw_icu_input_pin_icp		, 1
#define hw_icu_input_acmp0		, 2

#define hw_icu_edge_falling		, 1
#define hw_icu_edge_rising		, 2

/*		Read the capture register of an icu
 */
#define hw_def_hw_read_icu		, _hw_read_icu
#define _hw_read_icu(c,n,i,a)			_hw_read_icu_2(hw_##n##_ext)
#define _hw_read_icu_2(...)			_hw_read_icu_3(__VA_ARGS__)
#define _hw_read_icu_3(c,n,i,a, r,ion)		_hw_read_bits(c,n,i,a,r)

/*		Definition of the io pin associated to an icu
 */
#define hw_def_hw_io_icu		, _hw_io_icu
#define _hw_io_icu(c,n,...)			_hw_io_icu_2(hw_##n##_##ext)
#define _hw_io_icu_2(...)			_hw_io_icu_3(__VA_ARGS__)
#define _hw_io_icu_3(c,n,i,a, r, ion)		hw_##ion

/*		Definition of the counter associated to an icu
 */
#define hw_def_hw_ctr_icu		, _hw_ctr_icu
#define _hw_ctr_icu(c,n,...)			_hw_ctr_icu_2(hw_##n##_##ext)
#define _hw_ctr_icu_2(...)			_hw_ctr_icu_3(__VA_ARGS__)
#define _hw_ctr_icu_3(c,n,i,a, r, ion)		c,n,i,a

/*		Change the configuration of an icu
 */
#define hw_def_hw_config_icu		, _hw_config_icu

#define _hw_config_icu(c,n,i,a, ...)	\
  HW_G2(_hw_config_icu, HW_IS(,_hw_config_icu_kw_##__VA_ARGS__))(n,__VA_ARGS__,)
#define _hw_config_icu_0(n, ...)	\
  HW_ERR("`"HW_QUOTE(__VA_ARGS__)"` is not a valid parameter for hw_config(icu,...).")
#define _hw_config_icu_1(n, kw, ...)	\
  HW_A1(_hw_config_icu_kw_##kw)(n,__VA_ARGS__)

#define _hw_config_icu_kw_edge		, _hw_config_icu_edge

#define _hw_config_icu_edge(n, ...)	\
  HW_G2(_hw_config_icu_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hw_config_icu_vedge_0(n,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_config_icu_vedge_1(n,zedge,...)				\
  hw_write_bits(_hw_ctr_icu(icu,n,,), ices, HW_A1(hw_icu_edge_##zedge)-1) \
  HW_EOP(__VA_ARGS__)
