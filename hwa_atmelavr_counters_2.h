
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA common declarations to all Atmel AVR counter-timers (layer 2)
 */


/*	Configure an compare output unit
 */
#define hw_def_hwa_config_ocu		, _hwa_config_ocu

#define _hwa_config_ocu(c,n,i,a, mode)	\
  HW_G2(_hwa_config_ocu, HW_IS(,hw_ocu_mode_##mode))(n,mode)
#define _hwa_config_ocu_0(n,mode)					\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #n "`." )
#define _hwa_config_ocu_1(n,mode)	_hwa_config_ocu_2(hw_##n##_ext, mode)
#define _hwa_config_ocu_2(...)		_hwa_config_ocu_3(__VA_ARGS__)
#define _hwa_config_ocu_3(c,n,i,a, r,io, mode)		\
  hwa->n.r##_mode = HW_A1(hw_ocu_mode_##mode)


/*	Write the compare register of a counter compare unit
 */
#define hw_def_hwa_write_ocu		, _hwa_write_ocu
#define _hwa_write_ocu(c,n,i,a, v)		_hwa_write_ocu_2(hw_##n##_ext, v)
#define _hwa_write_ocu_2(...)			_hwa_write_ocu_3(__VA_ARGS__)
#define _hwa_write_ocu_3(c,n,i,a, r,io, v)	_hwa_write_bits(c,n,i,a,r,v)


/*	Configure an capture unit
 */
#define hw_def_hwa_config_icu		, _hwa_config_icu

#define _hwa_config_icu(c,n,i,a, ...)	_hwa_config_icu_2(hw_##n##_ext, __VA_ARGS__)
#define _hwa_config_icu_2(...)		_hwa_config_icu_3(__VA_ARGS__)
#define _hwa_config_icu_3(c,n,i,a, r,io, ...)				\
  do { HW_G2(hwa_config_icu_xinput,HW_IS(input,__VA_ARGS__))(n,r,__VA_ARGS__,) } while(0)

#define hwa_config_icu_xinput_0(n,r,...)					\
  HW_ERR("expected `input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_xinput_1(n,r,_input_,...)				\
  HW_G2(hwa_config_icu_vinput,HW_IS(,hw_icu_input_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_vinput_0(n,r,...)					\
  HW_ERR( "`input` can be `pin_icp` or `acmp0` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_vinput_1(n,r,zinput,...)				\
  hwa->n.r##_input = HW_A1(hw_icu_input_##zinput);				\
  HW_G2(hwa_config_icu_xedge,HW_IS(edge,__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_xedge_0(n,r,...)					\
  HW_ERR("expected `edge` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_xedge_1(n,r,_edge_,...)				\
  HW_G2(hwa_config_icu_vedge,HW_IS(,hw_icu_edge_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_vedge_0(n,r,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_vedge_1(n,r,zedge,...)				\
  hwa->n.r##_edge = HW_A1(hw_icu_edge_##zedge);				\
  HW_G2(hwa_config_icu_xfilter,HW_IS(filter,__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_xfilter_0(n,r,...)					\
  HW_G2(hwa_config_icu,HW_IS(,__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_xfilter_1(n,r,_filter_,...)			\
  HW_G2(hwa_config_icu_vfilter,HW_IS(,hw_state_##__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_vfilter_0(n,r,...)					\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_vfilter_1(n,r,zfilter,...)				\
  hwa->n.r##_filter = HW_A1(hw_state_##zfilter);				\
  HW_G2(hwa_config_icu,HW_IS(,__VA_ARGS__))(n,r,__VA_ARGS__)

#define hwa_config_icu_0(n,r,...)				\
  HW_ERR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_icu_1(...)
