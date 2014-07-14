
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA common declarations to all Atmel AVR counter-timers (level 2)
 */


/*	Parameters for counter units
 */
#define hw_counter_overflow_at_bottom		, 1
#define hw_counter_overflow_at_top		, 2
#define hw_counter_overflow_at_max		, 3

#define hw_counter_update_immediately		, 1
#define hw_counter_update_at_bottom		, 2
#define hw_counter_update_at_top		, 3


/*	Parameters for compare units
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
#define hw_is_disconnected_disconnected		, 1

#define hw_def_hw_config_ocu		, _hw_config_ocu
#define _hw_config_ocu(c,n,i, cn,chn,ion, mode)				\
  HW_G2(_hw_config_ocu, HW_IS(disconnected,mode))(n,mode,hw_##cn,chn)
#define _hw_config_ocu_0(n,mode,...)					\
  HW_ERR( "`disconnected` is the only acceptable mode for hw_config(ocu,...)." )
#define _hw_config_ocu_1(...)		_hw_config_ocu_3(__VA_ARGS__)
#define _hw_config_ocu_3(n,mode, cc,cn,ci,ca, chn)	\
  _hw_write_bits(cc,cn,ci,ca, com##chn, 0)


#define hw_def_hwa_config_ocu		, _hwa_config_ocu
#define _hwa_config_ocu(c,n,i, cn,ocn,ion, mode)			\
  HW_G2(_hwa_config_ocu, HW_IS(,hw_ocu_mode_##mode))(n,cn,ocn,mode)
#define _hwa_config_ocu_0(n,cn,mode)				\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #n "`." )
#define _hwa_config_ocu_1(n,cn,ocn,mode)	_hwa_config_ocu_2(hw_##cn,ocr##ocn##_mode, mode)
#define _hwa_config_ocu_2(...)			_hwa_config_ocu_3(__VA_ARGS__)
#define _hwa_config_ocu_3(cc,cn,ci,ca, r, mode)	\
  hwa->cn.r = HW_A1(hw_ocu_mode_##mode)


/*	Write the 'compare' register of a counter's compare unit
 */
#define hw_def_hw_write_ocu		, _hw_write_ocu
#define _hw_write_ocu(c,n,i,cn,ocn,ion,v)	_hw_write_bits(hw_##cn,ocr##ocn,v)

#define hw_def_hwa_write_ocu		, _hwa_write_ocu
#define _hwa_write_ocu(c,n,i,cn,ocn,ion,v)	_hwa_write_bits(hw_##cn,ocr##ocn,v)


/*	Definition of the io pin associated to an ocu
 */
#define hw_def_hw_io_ocu		, _hw_io_ocu
#define _hw_io_ocu(c,n,i,cn,ch,ion)		hw_##ion


/*	Trigger compare
 */
#define hw_def_hw_trigger_ocu		, _hw_trigger_ocu
#define _hw_trigger_ocu(c,n,i, cn,ch,ion)	_hw_write_bits(hw_##cn, foc##ch, 1 )

#define hw_def_hwa_trigger_ocu		, _hwa_trigger_ocu
#define _hwa_trigger_ocu(c,n,i, cn,ch,ion)	_hwa_write_bits(hw_##cn, foc##ch, 1 )


/*		Definition of the counter associated to an ocu
 */
/* #define hw_def_hw_ctr_ocu		, _hw_ctr_ocu */
/* #define _hw_ctr_ocu(t,ocn,...)			_hw_ctr_ocu_2(hw_##ocn##_##ext) */
/* #define _hw_ctr_ocu_2(...)			_hw_ctr_ocu_3(__VA_ARGS__) */
/* #define _hw_ctr_ocu_3(cc,cn,ci,ca, ocr, ion)	cc,cn,ci,ca */


/*	Parameters for capture units
 */
#define hw_icu_input_pin_icp		, 1
#define hw_icu_input_acmp0		, 2

#define hw_icu_edge_falling		, 1
#define hw_icu_edge_rising		, 2


/*	Change the configuration of a capture unit
 */
#define hw_def_hw_config_icu		, _hw_config_icu

#define _hw_config_icu(c,n,i,cn,...)	_hw_config_icu_2(cn,HW_POP_icu(c,n,i,cn,__VA_ARGS__))
#define _hw_config_icu_2(...)		_hw_config_icu_3(__VA_ARGS__)
#define _hw_config_icu_3(cn, ...)					\
  HW_G2(_hw_config_icu, HW_IS(,_hw_config_icu_kw_##__VA_ARGS__))(cn,__VA_ARGS__,)
#define _hw_config_icu_0(cn, ...)					\
  HW_ERR("`"HW_QUOTE(__VA_ARGS__)"` is not a valid parameter for hw_config(icu,...).")
#define _hw_config_icu_1(cn, kw, ...)		\
  HW_A1(_hw_config_icu_kw_##kw)(cn,__VA_ARGS__)

#define _hw_config_icu_kw_edge		, _hw_config_icu_edge

#define _hw_config_icu_edge(cn, ...)					\
  HW_G2(_hw_config_icu_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(cn,__VA_ARGS__)
#define _hw_config_icu_vedge_0(cn,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_config_icu_vedge_1(cn,zedge,...)			\
  hw_write_bits(hw_##cn, ices, HW_A1(hw_icu_edge_##zedge)-1);	\
  HW_EOP(__VA_ARGS__)


/*	Configure a capture unit
 */
#define hw_def_hwa_config_icu		, _hwa_config_icu

#define _hwa_config_icu(c,n,i,cn,chn, ...)	_hwa_config_icu_2(cn,chn,HW_POP_icu(c,n,i,cn,chn, __VA_ARGS__))
#define _hwa_config_icu_2(...)		_hwa_config_icu_3(__VA_ARGS__)
#define _hwa_config_icu_3(cn,r, ...)					\
  do { HW_G2(_hwa_config_icu_xinput,HW_IS(input,__VA_ARGS__))(cn,r,__VA_ARGS__,) } while(0)

#define _hwa_config_icu_xinput_0(n,r,...)				\
  HW_ERR("expected `input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_icu_xinput_1(n,r,_input_,...)			\
  HW_G2(_hwa_config_icu_vinput,HW_IS(,hw_icu_input_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_config_icu_vinput_0(n,r,...)				\
  HW_ERR( "`input` can be `pin_icp` or `acmp0` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_icu_vinput_1(n,r,zinput,...)			\
  hwa->n.r##_input = HW_A1(hw_icu_input_##zinput);			\
  HW_G2(_hwa_config_icu_xedge,HW_IS(edge,__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_config_icu_xedge_0(n,r,...)				\
  HW_ERR("expected `edge` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_icu_xedge_1(n,r,_edge_,...)				\
  HW_G2(_hwa_config_icu_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_config_icu_vedge_0(n,r,...)				\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_icu_vedge_1(n,r,zedge,...)				\
  hwa->n.r##_edge = HW_A1(hw_icu_edge_##zedge);				\
  HW_G2(_hwa_config_icu_xfilter,HW_IS(filter,__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_config_icu_xfilter_0(n,r,...)	\
  HW_EOP(__VA_ARGS__)

#define _hwa_config_icu_xfilter_1(n,r,_filter_,...)			\
  HW_G2(_hwa_config_icu_vfilter,HW_IS(,hw_state_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_config_icu_vfilter_0(n,r,...)				\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_config_icu_vfilter_1(n,r,zfilter,...)	\
  hwa->n.r##_filter = HW_A1(hw_state_##zfilter);	\
  HW_EOP(__VA_ARGS__)


/*		Read the capture register of an icu
 */
#define hw_def_hw_read_icu		, _hw_read_icu
#define _hw_read_icu(c,n,i,cn,...)		_hw_read_icu_2(hw_##cn,icr)
#define _hw_read_icu_2(...)			_hw_read_bits(__VA_ARGS__)


/*		Definition of the io pin associated to an icu
 */
#define hw_def_hw_io_icu		, _hw_io_icu
#define _hw_io_icu(c,n,i,cn,icn,ion)		hw_##ion

/*		Definition of the counter associated to an icu
 */
/* #define hw_def_hw_ctr_icu		, _hw_ctr_icu */
/* #define _hw_ctr_icu(c,n,...)			_hw_ctr_icu_2(hw_##n##_##ext) */
/* #define _hw_ctr_icu_2(...)			_hw_ctr_icu_3(__VA_ARGS__) */
/* #define _hw_ctr_icu_3(c,n,i,a, r, ion)		c,n,i,a */
