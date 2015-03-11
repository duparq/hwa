
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 *	Atmel AVR input capture unit version 'a'
 *
 *	Used in: 
 */

#include "hwa_atmelavr__icu.h"


/*	Change the configuration of a capture unit
 */
#define hw_mthd_hw_config__icua		, _hw_cficua

#define _hw_cficua(c,n,i,cn,...)	_hw_cficua_2(cn,_hw_pop_icu(c,n,i,cn,__VA_ARGS__))
#define _hw_cficua_2(...)		_hw_cficua_3(__VA_ARGS__)
#define _hw_cficua_3(cn, ...)					\
  HW_G2(_hw_cficua, HW_IS(,_hw_cficua_kw_##__VA_ARGS__))(cn,__VA_ARGS__,)
#define _hw_cficua_0(cn, ...)					\
  HW_ERR("`"HW_QUOTE(__VA_ARGS__)"` is not a valid parameter for hw_config(icu,...).")
#define _hw_cficua_1(cn, kw, ...)		\
  HW_A1(_hw_cficua_kw_##kw)(cn,__VA_ARGS__)

#define _hw_cficua_kw_edge		, _hw_cficua_edge

#define _hw_cficua_edge(cn, ...)					\
  HW_G2(_hw_cficua_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(cn,__VA_ARGS__)
#define _hw_cficua_vedge_0(cn,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_cficua_vedge_1(cn,zedge,...)			\
  HW_TX(hw_write_reg(hw_##cn, ices, HW_A1(hw_icu_edge_##zedge)-1),__VA_ARGS__);


/*	Configure a capture unit
 */
#define hw_mthd_hwa_config__icua		, _hwa_cficua

#define _hwa_cficua(c,n,i,cn,chn, ...)	_hwa_cficua_2(cn,chn,_hw_pop_icu(c,n,i,cn,chn, __VA_ARGS__))
#define _hwa_cficua_2(...)		_hwa_cficua_3(__VA_ARGS__)
#define _hwa_cficua_3(cn,r, ...)					\
  do { HW_G2(_hwa_cficua_xinput,HW_IS(input,__VA_ARGS__))(cn,r,__VA_ARGS__,) } while(0)

#define _hwa_cficua_xinput_0(n,r,...)				\
  HW_ERR("expected `input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_xinput_1(n,r,_input_,...)			\
  HW_G2(_hwa_cficua_vinput,HW_IS(,hw_icu_input_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_cficua_vinput_0(n,r,...)				\
  HW_ERR( "`input` can be `pin_icp` or `acmp0` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vinput_1(n,r,zinput,...)			\
  hwa->n.r##_input = HW_A1(hw_icu_input_##zinput);			\
  HW_G2(_hwa_cficua_xedge,HW_IS(edge,__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_cficua_xedge_0(n,r,...)				\
  HW_ERR("expected `edge` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_xedge_1(n,r,_edge_,...)				\
  HW_G2(_hwa_cficua_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_cficua_vedge_0(n,r,...)				\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vedge_1(n,r,zedge,...)				\
  hwa->n.r##_edge = HW_A1(hw_icu_edge_##zedge);				\
  HW_G2(_hwa_cficua_xfilter,HW_IS(filter,__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_cficua_xfilter_0(n,r,...)	\
  HW_TX(,__VA_ARGS__)

#define _hwa_cficua_xfilter_1(n,r,_filter_,...)			\
  HW_G2(_hwa_cficua_vfilter,HW_IS(,hw_state_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define _hwa_cficua_vfilter_0(n,r,...)				\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vfilter_1(n,r,zfilter,...)	\
  hwa->n.r##_filter = HW_A1(hw_state_##zfilter);	\
  HW_TX(,__VA_ARGS__)


/*		Read the capture register of an icu
 */
#define hw_mthd_hw_read__icua			, _hw_read_icua
#define _hw_read_icua(c,n,i,cn,...)		_hw_read_icua_2(hw_##cn,icr)
#define _hw_read_icua_2(...)			_hw_read_reg(__VA_ARGS__)


/*		Definition of the io pin associated to an icu
 */
#define hw_mthd_hw_io__icua			, _hw_io_icua
#define _hw_io_icua(c,n,i,cn,icn,ion)		hw_##ion
