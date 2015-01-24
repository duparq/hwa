
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Class methods
 */
#define hw_def_hw_config_core		, _hw_config_core
#define hw_def_hwa_config_core		, _hwa_config_core
#define hw_def_hw_stat_core		, _hw_stat_core


/*	Configure the MCU sleep mode
 */
#define hw_is_sleep_mode_sleep_mode	, 1


/* #define _hwa_config_core(c,n,i,a,...)					\ */
/*   HW_G2(_hwa_cfcore_xsleepmode, HW_IS(sleep_mode,__VA_ARGS__))(__VA_ARGS__,) */

/* #define _hwa_cfcore_xsleepmode_0(...)					\ */
/*   HW_ERR("expected `sleep_mode`, got `" HW_QUOTE(__VA_ARGS__) "` instead.") */

/* #define _hwa_cfcore_xsleepmode_1(kw,...)				\ */
/*   HW_G2(_hwa_cfcore_vsleepmode, HW_IS(,hw_core_sm_##__VA_ARGS__))(__VA_ARGS__) */

/* #define _hwa_cfcore_vsleepmode_0(...)					\ */
/*   HW_ERR("`sleep_mode` can be `idle`, `adc_noise_reduction`, `power_down`, or "	\ */
/* 	 "`standby`, but not `" HW_QUOTE(__VA_ARGS__) "`.") */

/* #define _hwa_cfcore_vsleepmode_1(vsleepmode,...)		\ */
/*   HW_TX(_hwa_write_reg(hw_core0, sm, HW_A1(hw_core_sm_##vsleepmode)),__VA_ARGS__) */





/*	Core status
 *
 *	hw_stat_t(...) declares the structure that holds the status
 *	hw_stat(...) reads and returns the status
 *
 *	The only flag that is available is the irq flag.
 */
typedef union {
  uint8_t         byte ;
  struct {
    unsigned int porf   : 1 ;
    unsigned int extrf  : 1 ;
    unsigned int borf   : 1 ;
    unsigned int wdrf   : 1 ;
    unsigned int __4to7 : 4 ;
  };
  struct {
    unsigned int reset_by_power_on  : 1 ;
    unsigned int reset_by_reset_pin : 1 ;
    unsigned int reset_by_brown_out : 1 ;
    unsigned int reset_by_watchdog  : 1 ;
    unsigned int __4to7_2           : 4 ;
  };
} _hw_core_stat_t ;


#define hw_def_hw_stat_t_core		, _hw_core_stat_t
#define _hw_core_stat_t(c,n,i,a,...)	HW_TX(_hw_core_stat_t, __VA_ARGS__)


#define _hw_stat_core(c,n,i,a)		_hw_core_stat(_hw_read_reg(c,n,i,a, mcusr))

HW_INLINE _hw_core_stat_t _hw_core_stat( uint8_t byte )
{
  _hw_core_stat_t	st ;
  st.byte = byte ;
  return st ;
}
