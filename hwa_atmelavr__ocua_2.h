
/*	Atmel AVR 8-bit timer-counter compare unit version 'a'
 *
 *	Used in: ATtinyX4 OC0A	hw_counter0_compare0
 *		 	  OC0B	hw_counter0_compare1
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


#define hw_is_update_update			, 1
#define hw_is_output_output			, 1

#define hw_ocu_update_immediately		, 0
#define hw_ocu_update_at_bottom			, 1
#define hw_ocu_update_at_top			, 2

/*                                                           , code, COM value
 */
#define hw_ocu_output_disconnected				, 0, 0	/* Non-PWM */
#define hw_ocu_output_toggle_on_match				, 1, 1	/* Non-PWM */
#define hw_ocu_output_clear_on_match				, 2, 2	/* Non-PWM */
#define hw_ocu_output_set_on_match				, 3, 3	/* Non-PWM */

#define hw_ocu_output_set_at_bottom_clear_on_match		, 4, 2	/* Fast PWM */
#define hw_ocu_output_clear_at_bottom_set_on_match		, 5, 3

#define hw_ocu_output_clear_on_match_up_set_on_match_down	, 6, 2	/* Phase correct PWM */
#define hw_ocu_output_set_on_match_up_clear_on_match_down	, 7, 3


/*	hw_config( COMPARE_UNIT,
 *
 *	           output,   disconnected,
 *	                   | toggle_on_match,
 *	                   | clear_on_match,
 *	                   | set_on_match,
 *	                   | set_at_bottom_clear_on_match,
 *	                   | clear_at_bottom_set_on_match,
 *	                   | clear_on_match_up_set_on_match_down,
 *	                   | set_on_match_up_clear_on_match_down  );
 *
 *	Note: there is no checking against the counter configuration.
 */
#define hw_is_disconnected_disconnected		, 1

#define hw_def_hw_config__ocua		, _hw_cfocua

#define _hw_cfocua(c,n,i, cn,ocn,ion, ...)				\
  do {									\
    HW_G2(_hw_cfocua_xoutput, HW_IS(output,__VA_ARGS__))(n,cn,ocn,__VA_ARGS__); \
  }while(0)

#define _hw_cfocua_xoutput_0(n,cn,ocn,...)				\
  HW_ERR("expected `output` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_cfocua_xoutput_1(n,cn,ocn,kw,...	)			\
  HW_G2(_hw_cfocua_voutput, HW_IS(,hw_ocu_output_##__VA_ARGS__))(n,cn,ocn,__VA_ARGS__)
#define _hw_cfocua_voutput_0(n,cn,ocn,...)				\
  HW_ERR("output mode of `" #n "` can be `disconnected`, `toggle_on_match`, " \
	 "`clear_on_match`, `set_on_match`, `set_at_bottom_clear_on_match`, " \
	 "`clear_at_bottom_set_on_match`, "				\
	 "`clear_on_match_up_set_on_match_down`, or "			\
	 "`set_on_match_up_clear_on_match_down`, "			\
	 "but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_cfocua_voutput_1(n,cn,ocn,v,...)				\
  HW_TX(_hw_write_reg(hw_##cn,com##ocn, HW_A2(hw_ocu_output_##v)),__VA_ARGS__)


/*	hwa_config( COMPARE_UNIT,
 *
 *	           [update,   at_bottom,
 *	                    | at_top,
 *	                    | at_max,]
 *
 *	           [output,   disconnected,
 *	                    | toggle_on_match,
 *	                    | clear_on_match,
 *	                    | set_on_match,
 *	                    | set_at_bottom_clear_on_match,
 *	                    | clear_at_bottom_set_on_match,
 *	                    | clear_on_match_up_set_on_match_down,
 *	                    | set_on_match_up_clear_on_match_down,] );
 */
#define hw_def_hwa_config__ocua		, _hwa_cfocua

#define _hwa_cfocua(c,n,i, cn,ocn,ion, kw, ...)				\
  do {									\
    HW_G2(_hwa_cfocua_xupdate, HW_IS(update,kw))(n,cn,ocn,kw,__VA_ARGS__); \
  }while(0)

#define _hwa_cfocua_xupdate_0(n,cn,ocn,kw,...)			\
  HW_G2(_hwa_cfocua_xoutput, HW_IS(output,kw))(n,cn,ocn,kw,__VA_ARGS__)

#define _hwa_cfocua_xupdate_1(n,cn,ocn,kw,...)				\
  HW_G2(_hwa_cfocua_vupdate, HW_IS(,hw_ocu_update_##__VA_ARGS__))(n,cn,ocn,__VA_ARGS__)
#define _hwa_cfocua_vupdate_0(n,cn,ocn,...)		\
  HW_ERR("update mode of `" #n "` can be "		\
	 "`immediately`, "				\
	 "`at_bottom`, or "				\
	 "`at_top`,"					\
	 "but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfocua_vupdate_1(n,cn,ocn,v,...)	\
  hwa->cn.compare##ocn##_##update = HW_A1(hw_ocu_update_##v);\
  HW_G2(_hwa_cfocua_xoutput, HW_IS(output,__VA_ARGS__))(n,cn,ocn,__VA_ARGS__)

#define _hwa_cfocua_xoutput_0(n,cn,ocn,...)	\
  HW_TX(,__VA_ARGS__)
#define _hwa_cfocua_xoutput_1(n,cn,ocn,kw,...	)			\
  HW_G2(_hwa_cfocua_voutput, HW_IS(,hw_ocu_output_##__VA_ARGS__))(n,cn,ocn,__VA_ARGS__)
#define _hwa_cfocua_voutput_0(n,cn,ocn,...)				\
  HW_ERR("output mode of `" #n "` can be `disconnected`, `toggle_on_match`, " \
	 "`clear_on_match`, `set_on_match`, `set_at_bottom_clear_on_match`, " \
	 "`clear_at_bottom_set_on_match`, "				\
	 "`clear_on_match_up_set_on_match_down`, or "			\
	 "`set_on_match_up_clear_on_match_down`, "			\
	 "but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfocua_voutput_1(n,cn,ocn,v,...)	\
  HW_TX(hwa->cn.compare##ocn##_##output = HW_A1(hw_ocu_output_##v),__VA_ARGS__)


/*	Write the OCR register of a counter's compare output unit
 */
#define hw_def_hw_write__ocua			, _hw_write_ocu
#define _hw_write_ocu(c,n,i, cn,ocn,ion,v)	_hw_write_reg(hw_##cn,compare##ocn,v)

#define hw_def_hwa_write__ocua			, _hwa_write_ocu
#define _hwa_write_ocu(c,n,i, cn,ocn,ion,v)	_hwa_write_reg(hw_##cn,compare##ocn,v)

/*	Definition of the io pin associated to an ocu
 */
#define hw_def_hw_io__ocua			, _hw_io_ocu
#define _hw_io_ocu(c,n,i,cn,ch,ion)		hw_##ion


/*	Trigger compare
 */
#define hw_def_hw_trigger__ocua			, _hw_trigger_ocu
#define _hw_trigger_ocu(c,n,i, cn,ch,ion)	_hw_write_reg(hw_##cn, foc##ch, 1 )

#define hw_def_hwa_trigger__ocua		, _hwa_trigger_ocu
#define _hwa_trigger_ocu(c,n,i, cn,ch,ion)	_hwa_write_reg(hw_##cn, foc##ch, 1 )


#define hw_def_hw_sup__ocua			, _hw_sup_ocua
#define _hw_sup_ocua(c,n,i,cn,ch,ion)		hw_##cn
