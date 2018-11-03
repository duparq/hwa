
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @page atmelavr_coreb
 * @section atmelavr_coreb_config Configuration
 *
 * @code
 * hwa( configure, core0,
 *
 *	       //  Whether the `hw_sleep_until_irq()` instruction will put the core in
 *	       //  sleep mode or not
 *	       //
 *	     [ sleep,	     enabled,
 *			   | disabled, ]
 *
 *	       //  Wanted sleep mode
 *	       //
 *	     [ sleep_mode,   idle
 *			   | adc_noise_reduction
 *			   | power_down
 *			   | power_save
 *			   | standby
 *			   | extended_standby	  ]
 *	       );
 * @endcode
 */
#define _hw_mtd_hwa_configure__coreb	, _hwa_cfcoreb

/*  TODO use a list of wake-up sources instead (or in addition)?
 */
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

/*	Optionnal parameter `sleep`
 */
#define _hwa_cfcoreb(o,i,a,k,...)					\
  do {									\
    HW_Y(_hwa_cfcoreb_ksleep,_hw_is_sleep_##k)(o,k,__VA_ARGS__,,);	\
  } while(0)

#define _hwa_cfcoreb_ksleep_1(o,k,v,...)				\
  HW_Y(_hwa_cfcoreb_vsleep,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcoreb_vsleep_0(o,v,...)		HW_E_VL(v, enabled | disabled)
#define _hwa_cfcoreb_vsleep_1(o,v,k,...)				\
  _hwa_write_or( o, se, HW_A1(_hw_state_##v) );			\
  HW_G2(_hwa_cfcoreb_ksleepmode,HW_IS(sleep_mode,k))(o,k,__VA_ARGS__)

#define _hwa_cfcoreb_ksleep_0(o,k,...)					\
  HW_G2(_hwa_cfcoreb_ksleepmode,HW_IS(sleep_mode,k))(o,k,__VA_ARGS__)

/*	Optionnal parameter `sleep_mode`
 */
#define _hwa_cfcoreb_ksleepmode_0(o,...)	HW_EOL(__VA_ARGS__)

#define _hwa_cfcoreb_ksleepmode_1(o,k,v,...)				\
  HW_Y(_hwa_cfcoreb_vsleepmode,_hw_sleepmode_##v)(o,v,__VA_ARGS__)

#define _hw_sleepmode_idle		, 0
#define _hw_sleepmode_adc_noise_reduction	, 1
#define _hw_sleepmode_power_down	, 2
#define _hw_sleepmode_power_save	, 3
#define _hw_sleepmode_standby		, 6
#define _hw_sleepmode_extended_standby	, 7

#define _hwa_cfcoreb_vsleepmode_0(o,v,...)				\
  HW_E_AVL(sleep_mode, v, idle | adc_noise_reduction | power_down | power_save | standby | extended_standby)

#define _hwa_cfcoreb_vsleepmode_1(o,v,...)	\
  _hwa_write_or( o, sm, HW_A1(_hw_sleepmode_##v)) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_coreb
 * @section atmelavr_coreb_sleep Sleep
 *
 * If enabled, the `hw_sleep_until_irq()` instruction puts the core into sleeping mode
 *
 * @code
 * hw_sleep_until_irq();
 * @endcode
 */


/**
 * @page atmelavr_coreb
 * @section atmelavr_coreb_stat Status
 *
 * The `hw(stat,)` instruction returns the status flags of the core in a
 * structure whose typename is given by the `hw_stat_t()` instruction. Available
 * flags are
 *
 * * `porf`  or `reset_by_power_on`   1 if reset was caused by power-on
 * * `extrf` or `reset_by_reset_pin`  1 if reset was caused by external pin RESET
 * * `borf`  or `reset_by_brown_out`  1 if reset was caused by brown-out detection
 * * `wdrf`  or `reset_by_watchdog`   1 if reset was caused by watchdog
 *
 * @code
 * hw_stat_t( core0 ) st ;
 * st = hw( stat, core0 );
 * if ( st.wdrf ) {
 *   n_wdresets++ ;    // Increment watchdog resets count
 * }
 * @endcode
 */
#define _hw_mtd_hw_stat__coreb		, _hw_stat_coreb

typedef union {
  uint8_t	  byte ;
  struct {
    unsigned int porf:	 1 ;
    unsigned int extrf:	 1 ;
    unsigned int borf:	 1 ;
    unsigned int wdrf:	 1 ;
    unsigned int __4to7: 4 ;
  };
  struct {
    unsigned int reset_by_power_on:  1 ;
    unsigned int reset_by_reset_pin: 1 ;
    unsigned int reset_by_brown_out: 1 ;
    unsigned int reset_by_watchdog:  1 ;
    unsigned int __4to7_2:	     4 ;
  };
} _hw_coreb_stat_t ;


#define _hw_mtd_hw_stat_t__coreb	, _hw_coreb_stat_t
#define _hw_stat_coreb(o,i,a,...)	_hw_coreb_stat(_hw_read_or(o, mcusr)) HW_EOL(__VA_ARGS__)


HW_INLINE _hw_coreb_stat_t _hw_coreb_stat( uint8_t byte )
{
  _hw_coreb_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @page atmelavr_coreb
 *
 * The ``clear`` instruction clears the status flags all at once
 *
 * @code
 * hwa( clear, core0 );
 * @endcode
 */
#define _hw_mtd_hwa_clear__coreb	, _hwa_clear__coreb

#define _hwa_clear__coreb(o,i,a,...)	_hwa_write_or(o,allrf,0)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__coreb(o,i,a)		\
  _hwa_setup_or( o, mcucr  );			\
  _hwa_setup_or( o, mcusr  );			\
  _hwa_setup_or( o, smcr   );			\
  _hwa_setup_or( o, osccal )

/*  mcusr is not initialized as its status is not known after RESET
 */
#define _hwa_init__coreb(o,i,a)			\
  _hwa_init_or( o, mcucr,  0x00 );		\
  _hwa_init_or( o, smcr,   0x00 );		\
  _hwa_init_or( o, osccal, 0x00 )


#define _hwa_commit__coreb(o,i,a)		\
  _hwa_commit_or( o, mcucr  );			\
  _hwa_commit_or( o, mcusr  );			\
  _hwa_commit_or( o, smcr   );			\
  _hwa_commit_or( o, osccal )


/**
 * @page atmelavr_coreb
 * <br>
 */
