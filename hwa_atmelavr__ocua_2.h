
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	Atmel AVR 8-bit timer-counter compare output unit version 'a'
 *
 *	Used in: ATtinyX4 OC0A	hw_counter0_output0
 */

#define hw_ocu_mode_disconnected				, 0	/* Non-PWM */
#define hw_ocu_mode_toggle_on_match				, 1	/* Non-PWM */
#define hw_ocu_mode_clear_on_match				, 2	/* Non-PWM */
#define hw_ocu_mode_set_on_match				, 3	/* Non-PWM */

#define hw_ocu_mode_set_at_bottom_clear_on_match		, 4	/* Fast PWM */
#define hw_ocu_mode_clear_at_bottom_set_on_match		, 5

#define hw_ocu_mode_clear_on_match_up_set_on_match_down		, 6	/* Phase correct PWM */
#define hw_ocu_mode_set_on_match_up_clear_on_match_down		, 7


/*	Configure an compare output unit
 *
 *		The only possible mode here is 'disconnected' since we do not
 *		know the counter unit configuration.
 */
#define hw_is_disconnected_disconnected		, 1

#define hw_def_hw_config__ocua		, _hw_cfocua
#define _hw_cfocua(c,n,i, cn,chn,ion, mode, ...)			\
  HW_TX(HW_G2(_hw_cfocua, HW_IS(disconnected,mode))(n,mode,hw_##cn,chn),__VA_ARGS__)
#define _hw_cfocua_0(n,mode,...)					\
  HW_ERR( "`disconnected` is the only acceptable mode for hw_config(ocu,...)." )
#define _hw_cfocua_1(...)		_hw_cfocua_3(__VA_ARGS__)
#define _hw_cfocua_3(n,mode, cc,cn,ci,ca, chn)	\
  _hw_write_reg(cc,cn,ci,ca, com##chn, 0)


#define hw_def_hwa_config__ocua		, _hwa_cfocua
/* #define _hwa_cfocua(c,n,i, cn,ocn,ion, mode, ...)			\ */
/*   HW_G2(_hwa_cfocua, HW_IS(,hw_ocu_mode_##mode))(n,cn,ocn,mode) */
#define _hwa_cfocua(c,n,i, cn,ocn,ion, mode, ...)			\
  HW_TX(HW_G2(_hwa_cfocua, HW_IS(,hw_ocu_mode_##mode))(n,cn,ocn,mode),__VA_ARGS__)
#define _hwa_cfocua_0(n,cn,ocn,mode)				\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #n "`." )
#define _hwa_cfocua_1(n,cn,ocn,mode)	_hwa_cfocua_2(hw_##cn,output##ocn##_mode, mode)
#define _hwa_cfocua_2(...)			_hwa_cfocua_3(__VA_ARGS__)
#define _hwa_cfocua_3(cc,cn,ci,ca, r, mode)	\
  hwa->cn.r = HW_A1(hw_ocu_mode_##mode)


/*	Write the OCR register of a counter's compare output unit
 */
#define hw_def_hw_write__ocua		, _hw_write_ocu
#define _hw_write_ocu(c,n,i, cn,ocn,ion,v)	_hw_write_reg(hw_##cn,output##ocn,v)

#define hw_def_hwa_write__ocua		, _hwa_write_ocu
#define _hwa_write_ocu(c,n,i, cn,ocn,ion,v)	_hwa_write_reg(hw_##cn,output##ocn,v)


/*	Definition of the io pin associated to an ocu
 */
#define hw_def_hw_io__ocua		, _hw_io_ocu
#define _hw_io_ocu(c,n,i,cn,ch,ion)		hw_##ion


/*	Trigger compare
 */
#define hw_def_hw_trigger__ocua		, _hw_trigger_ocu
#define _hw_trigger_ocu(c,n,i, cn,ch,ion)	_hw_write_reg(hw_##cn, foc##ch, 1 )

#define hw_def_hwa_trigger__ocua	, _hwa_trigger_ocu
#define _hwa_trigger_ocu(c,n,i, cn,ch,ion)	_hwa_write_reg(hw_##cn, foc##ch, 1 )
