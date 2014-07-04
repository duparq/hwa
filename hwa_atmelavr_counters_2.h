
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA common declarations to all Atmel AVR counter-timers (layer 2)
 */


/*	Configure an output-compare unit
 */
#define hw_fn_hwa_config_ocu		, _hwa_config_ocu

/* #define _hwa_config_ocu(c,n,i,a, mode)				\ */
/*   HW_G2(_hwa_config_ocu, HW_IS(,hw_ocu_mode_##mode))(n,mode) */
/* #define _hwa_config_ocu_0(n,mode)					\ */
/*   HW_ERR( "`" #mode "` is not a valid mode for `hw_" #n "`." ) */
/* #define _hwa_config_ocu_1(n,zmode)	\ */
/*   do { hwa->n.config = 1 ; hwa->n.mode = HW_A1(hw_ocu_mode_##zmode) ; } while(0) */

#define _hwa_config_ocu(c,n,i,a, mode)	\
  HW_G2(_hwa_config_ocu, HW_IS(,hw_ocu_mode_##mode))(n,mode)
#define _hwa_config_ocu_0(n,mode)					\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #n "`." )
#define _hwa_config_ocu_1(n,mode)	_hwa_config_ocu_2(n, hw_##n##_ext, mode)
#define _hwa_config_ocu_2(...)		_hwa_config_ocu_3(__VA_ARGS__)
#define _hwa_config_ocu_3(n, cc,cn,ci,ca, r,io, mode)	\
  do { hwa->cn.r##_config = 1 ; hwa->cn.r##_mode = HW_A1(hw_ocu_mode_##mode) ; } while(0)


/*	Write the compare register of a counter compare unit
 */
#define hw_fn_hwa_write_ocu		, _hwa_write_ocu
#define _hwa_write_ocu(c,n,i,a, v)		_hwa_write_ocu_2(hw_##n##_ext, v)
#define _hwa_write_ocu_2(...)			_hwa_write_ocu_3(__VA_ARGS__)
#define _hwa_write_ocu_3(c,n,i,a, r,io, v)	_hwa_write_bits(c,n,i,a,r,v)
