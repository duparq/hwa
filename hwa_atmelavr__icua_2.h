
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_icua
 * @par Configure the unit
 *
 * @code
 * hw_config( CAPTURE,
 *
 *           [input,    pin_icp
 *                    | hw_acmp0, ]
 *
 *           [edge,     falling
 *                    | rising, ]
 *
 *           [filter,   on
 *                    | off ]
 *           );
 * @endcode
 *
 * Note: currently, only `edge` configuration is implemented for the synchronous
 * method.
 *
 * @code
 * hwa_config( CAPTURE,
 *
 *             input,    pin_icp
 *                     | hw_acmp0,
 *
 *             edge,     falling
 *                     | rising,
 *
 *            [filter,   on
 *                     | off ]
 *           );
 * @endcode
 *
 */
#define _hw_mthd_hw_config__icua		, _hw_cficua

#define hw_icua_input_pin_icp			, 1
#define hw_icua_input_acmp0			, 2

#define hw_icua_edge_falling			, 1
#define hw_icua_edge_rising			, 2

#define _hw_cficua_kw_edge			, _hw_cficua_edge
#define _hw_cficua_kw_				, _hw_cficua_

#define _hw_cficua(p,i,cn,icn,ion,...)					\
  HW_G2(_hw_cficuakw1, HW_IS(,_hw_cficua_kw_##__VA_ARGS__))(cn,__VA_ARGS__)

#define _hw_cficuakw1_0(cn, ...)					\
  HW_ERR("expected `input`, `edge` or `filter` instead of `"HW_QUOTE(__VA_ARGS__)"`.")

#define _hw_cficuakw1_1(cn, kw, ...)		\
  HW_A1(_hw_cficua_kw_##kw)(cn,__VA_ARGS__)

#define _hw_cficua_edge(cn, ...)					\
  HW_G2(_hw_cficua_vedge,HW_IS(,hw_icua_edge_##__VA_ARGS__))(cn,__VA_ARGS__)
#define _hw_cficua_vedge_0(cn,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hw_cficua_vedge_1(cn,zedge,...)			\
  HW_TX(_hw_write_reg(cn, ices, HW_A1(hw_icua_edge_##zedge)-1),__VA_ARGS__);



#define _hw_mthd_hwa_config__icua		, _hwa_cficua

#define _hwa_cficua(p,i,cn,icn,ion,...)					\
  do {									\
    HW_G2(_hwa_cficua_xinput,HW_IS(input,__VA_ARGS__))(cn,icn,__VA_ARGS__,) \
      } while(0)

#define _hwa_cficua_xinput_0(cn,icn,...)				\
  HW_ERR("expected `input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_xinput_1(cn,icn,kw,...)				\
  HW_G2(_hwa_cficua_vinput,HW_IS(,hw_icua_input_##__VA_ARGS__))(cn,icn,__VA_ARGS__)

#define _hwa_cficua_vinput_0(cn,icn,...)				\
  HW_ERR( "`input` can be `pin_icp` or `hw_acmp0` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vinput_1(cn,icn,v,...)				\
  hwa->cn.config.icn.input = HW_A1(hw_icua_input_##v);			\
  HW_G2(_hwa_cficua_xedge,HW_IS(edge,__VA_ARGS__))(cn,icn,__VA_ARGS__)

#define _hwa_cficua_xedge_0(cn,icn,...)				\
  HW_ERR("expected `edge` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_xedge_1(cn,icn,kw,...)				\
  HW_G2(_hwa_cficua_vedge,HW_IS(,hw_icua_edge_##__VA_ARGS__))(cn,icn,__VA_ARGS__)

#define _hwa_cficua_vedge_0(cn,icn,...)				\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vedge_1(cn,icn,v,...)				\
  hwa->cn.config.icn.edge = HW_A1(hw_icua_edge_##v);				\
  HW_G2(_hwa_cficua_xfilter,HW_IS(filter,__VA_ARGS__))(cn,icn,__VA_ARGS__)

#define _hwa_cficua_xfilter_0(cn,icn,...)		\
  HW_TX(,__VA_ARGS__)

#define _hwa_cficua_xfilter_1(cn,icn,kw,...)				\
  HW_G2(_hwa_cficua_vfilter,HW_IS(,hw_state_##__VA_ARGS__))(cn,icn,__VA_ARGS__)

#define _hwa_cficua_vfilter_0(cn,icn,...)					\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cficua_vfilter_1(cn,icn,v,...)		\
  hwa->cn.config.icn.filter = HW_A1(hw_state_##v);		\
  HW_TX(,__VA_ARGS__)


/*	Read the capture register of an icu
 */
#define _hw_mthd_hw_read__icua			, _hw_read_icua
#define _hw_read_icua(p,i,cn,icn,ion,...)	HW_TX( _hw_read_reg(cn,icn), __VA_ARGS__ )
