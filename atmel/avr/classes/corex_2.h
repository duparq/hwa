
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */


#define _hw_is_sleep_sleep			, 1
#define _hw_is_sleep_mode_sleep_mode		, 1
#define hw_sleepmode_idle			, 0
#define hw_sleepmode_adc_noise_reduction	, 1
#define hw_sleepmode_power_down			, 2
#define hw_sleepmode_standby			, 3

/* #define _hw_is_awaker_awaker		, 1 */
/* #define hw_awaker_io			, 0 */
/* #define hw_awaker_int0_edge		, 0 */
/* #define hw_awaker_adc			, 1 */
/* #define hw_awaker_flash			, 1 */
/* #define hw_awaker_eeprom		, 1 */
/* #define hw_awaker_int0_level		, 2 */
/* #define hw_awaker_pinchange		, 2 */
/* #define hw_awaker_usi_start_condition	, 2 */
/* #define hw_awaker_watchdog		, 2 */


/*  TODO: use a list of wake-up sources instead (or in addition)?
 */
#define _hwa_config_core(p,i,a,...)					\
  do {									\
    HW_G2(_hwa_cfcore_xsleep, HW_IS(sleep,__VA_ARGS__))(p,__VA_ARGS__);	\
  } while(0)

#define _hwa_cfcore_xsleep_0(p,...)					\
  HW_G2(_hwa_cfcore_xsleepmode, HW_IS(sleep_mode,__VA_ARGS__))(p,__VA_ARGS__)

#define _hwa_cfcore_xsleep_1(p,kw,...)					\
  HW_G2(_hwa_cfcore_vsleep, HW_IS(,_hw_state_##__VA_ARGS__))(p,__VA_ARGS__)

#define _hwa_cfcore_vsleep_0(p,...)					\
  HW_ERR("expected `enabled` or `disabled`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")

#define _hwa_cfcore_vsleep_1(p,v,...)					\
  _hwa_write_reg( p, se, HW_A1(_hw_state_##v) );			\
  HW_G2(_hwa_cfcore_xsleepmode, HW_IS(sleep_mode,__VA_ARGS__))(p,__VA_ARGS__)

#define _hwa_cfcore_xsleepmode_0(p,...)	_hwa_cfcore_end(__VA_ARGS__)

#define _hwa_cfcore_xsleepmode_1(p,kw,...)				\
  HW_G2(_hwa_cfcore_vsleepmode, HW_IS(,hw_sleepmode_##__VA_ARGS__))(p,__VA_ARGS__)

#define _hwa_cfcore_vsleepmode_0(p,...)					\
  HW_ERR("`sleep_mode` can be `idle`, `adc_noise_reduction`, or "	\
	 "`power_down`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfcore_vsleepmode_1(p,v,...)	\
  _hwa_write_reg( p, sm, HW_A1(hw_sleepmode_##v) );	\
  _hwa_cfcore_end(__VA_ARGS__)

/*   HW_G2(_hwa_cfcore_xawaker1, HW_IS(awaker,__VA_ARGS__))(__VA_ARGS__) */

/* #define _hwa_cfcore_xawaker1_0(...)	_hwa_cfcore_end(__VA_ARGS__) */

/* #define _hwa_cfcore_xawaker1_1(kw,...)					\ */
/*   HW_G2(_hwa_cfcore_vawaker1, HW_IS(,hw_awaker_##__VA_ARGS__))(__VA_ARGS__) */

/* #define _hwa_cfcore_vawaker1_0(v,...)				\ */
/*   HW_ERR("`awaker` can be `int0`, `pinchange`, `adc`, or "	\ */
/* 	 "`watchdog`, but not `" HW_QUOTE(v) "`.") */

/* #define _hwa_cfcore_vawaker1_1(v,...)		\ */
/*   level = HW_A1(hw_awaker_##v);			\ */
/*   if ( level < awaker_level )			\ */
/*     awaker_level = level ;			\ */
/*   _hwa_cfcore_end(__VA_ARGS__) */

#define _hwa_cfcore_end(...)			\
  HW_TX(,__VA_ARGS__)


/**
 * @page atmelavr_corea
 * @section atmelavr_corea_stat Getting the status of the core
 *
 * Available flags are (alternate names between brackets):
 * * porf  (reset_by_power_on)  : set if reset was caused by power-on
 * * extrf (reset_by_reset_pin) : set if reset was caused by external pin RESET
 * * borf  (reset_by_brown_out) : set if reset was caused by brown-out detection
 * * wdrf  (reset_by_watchdog)  : set if reset was caused by watchdog
 *
 * @code
 * hw_stat_t(CORE) st ;
 * st = hw_stat( CORE );
 * if ( st.wdrf ) {
 *   n_overflows++ ;
 * }
 * @endcode
 */
/*  FIXME: intf0 should be there
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


#define _hw_mthd_hw_stat_t__core	, _hw_core_stat_t
#define _hw_stat_core(p,i,a,...)	HW_TX(_hw_core_stat(_hw_read_reg(p, mcusr)),__VA_ARGS__)


HW_INLINE _hw_core_stat_t _hw_core_stat( uint8_t byte )
{
  _hw_core_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @page atmelavr_corea
 * @section atmelavr_corea_clear Clearing the status of the core
 *
 * @code
 * hwa_clear( hw_core0 );
 * @endcode
 */
#define _hwa_clear_core(p,i,a,...)\
  _hwa_write_reg( p, allrf, 0 )
