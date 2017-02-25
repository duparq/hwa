
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @page atmelavr_corec
 * @section atmelavr_corec_config Configuration
 *
 * @code
 * hwa_config( OBJECT_NAME,
 *
 *             //  Whether the `hw_sleep()` instruction will put the core in
 *             //  sleep mode or not
 *             //
 *           [ sleep,        enabled,
 *                         | disabled, ]
 *
 *             //  Wanted sleep mode
 *             //
 *           [ sleep_mode,   idle
 *                         | adc_noise_reduction
 *                         | power_down
 *                         | power_save
 *                         | standby
 *                         | extended_standby     ]
 *             );
 * @endcode
 */
#define _hw_mthd_hwa_configure__corec		, _hwa_cfcorec

/*  TODO: use a list of wake-up sources instead (or in addition)?
 */

/*	Optionnal parameter `sleep`
 */
#define _hw_is_sleep_sleep			, 1

#define _hwa_cfcorec(o,i,a,...)					\
  do {									\
    HW_GX(_hwa_cfcorec_ksleep,_hw_is_sleep_##__VA_ARGS__)(o,__VA_ARGS__,,); \
  } while(0)

#define _hwa_cfcorec_ksleep_1(o,k,v,...)				\
  HW_GX(_hwa_cfcorec_vsleep,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcorec_vsleep_0(o,v,...)		HW_E_VL(v, enabled | disabled)
#define _hwa_cfcorec_vsleep_1(o,v,k,...)				\
  _hwa_write_reg( o, se, HW_A1(_hw_state_##v) );			\
  HW_G2(_hwa_cfcorec_ksleepmode,HW_IS(sleep_mode,k))(o,k,__VA_ARGS__)

#define _hwa_cfcorec_ksleep_0(o,k,...)					\
  HW_G2(_hwa_cfcorec_ksleepmode,HW_IS(sleep_mode,k))(o,k,__VA_ARGS__)

/*	Optionnal parameter `sleep_mode`
 */
#define _hw_is_sleep_mode_sleep_mode		, 1

#define _hwa_cfcorec_ksleepmode_0(o,...)	HW_EOL(__VA_ARGS__)

#define _hwa_cfcorec_ksleepmode_1(o,k,v,...)				\
  HW_GX(_hwa_cfcorec_vsleepmode,_hw_sleepmode_##v)(o,v,__VA_ARGS__)

#define _hw_sleepmode_idle			, 0
#define _hw_sleepmode_adc_noise_reduction	, 1
#define _hw_sleepmode_power_down		, 2
#define _hw_sleepmode_power_save		, 3
#define _hw_sleepmode_standby			, 6
#define _hw_sleepmode_extended_standby		, 7

#define _hwa_cfcorec_vsleepmode_0(o,v,...)				\
  HW_E_AVL(sleep_mode, v, idle | adc_noise_reduction | power_down | power_save | standby | extended_standby)

#define _hwa_cfcorec_vsleepmode_1(o,v,...)	\
  HW_TX(_hwa_write_reg( o, sm, HW_A1(_hw_sleepmode_##v)),__VA_ARGS__)


/**
 * @page atmelavr_corec
 * @section atmelavr_corec_sleep Sleep
 *
 * If enabled, the `hw_sleep()` instruction puts the core into sleeping mode:
 *
 * @code
 * hw_sleep();
 * @endcode
 */


/**
 * @page atmelavr_corec
 * @section atmelavr_corec_stat Status
 *
 * The `hw_stat()` instruction returns the status flags of the core in a
 * structure whose typename is given by the `hw_stat_t()` instruction. Available
 * flags are:
 *
 * * `porf`  or `reset_by_power_on`  : 1 if reset was caused by power-on
 * * `extrf` or `reset_by_reset_pin` : 1 if reset was caused by external pin RESET
 * * `borf`  or `reset_by_brown_out` : 1 if reset was caused by brown-out detection
 * * `wdrf`  or `reset_by_watchdog`  : 1 if reset was caused by watchdog
 * * `jtrf`  or `reset_by_jtag`      : 1 if reset was caused by JTAG
 * * `usbrf` or `reset_by_usb`       : 1 if reset was caused by USB
 *
 * @code
 * hw_stat_t( OBJECT_NAME ) st ;
 * st = hw_stat( OBJECT_NAME );
 * if ( st.wdrf ) {
 *   n_wdresets++ ;    // Increment watchdog resets count
 * }
 * @endcode
 */
#define _hw_mthd_hw_stat__corec		, _hw_stat_corec

typedef union {
  uint8_t         byte ;
  struct {
    unsigned int porf   : 1 ;
    unsigned int extrf  : 1 ;
    unsigned int borf   : 1 ;
    unsigned int wdrf   : 1 ;
    unsigned int jtrf   : 1 ;
    unsigned int usbrf  : 1 ;
    unsigned int __67   : 2 ;
  };
  struct {
    unsigned int reset_by_power_on  : 1 ;
    unsigned int reset_by_reset_pin : 1 ;
    unsigned int reset_by_brown_out : 1 ;
    unsigned int reset_by_watchdog  : 1 ;
    unsigned int reset_by_jtag      : 1 ;
    unsigned int reset_by_usb       : 1 ;
    unsigned int __67b              : 2 ;
  };
} _hw_corec_stat_t ;


#define _hw_mthd_hw_stat_t__corec	, _hw_corec_stat_t
#define _hw_stat_corec(o,i,a,...)	HW_TX(_hw_corec_stat(_hw_read_reg(o, mcusr)),__VA_ARGS__)


HW_INLINE _hw_corec_stat_t _hw_corec_stat( uint8_t byte )
{
  _hw_corec_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @page atmelavr_corec
 *
 * The `hw_clear()` instruction clears the status flags all at once:
 *
 * @code
 * hwa_clear( core0 );
 * @endcode
 */
#define _hw_mthd_hwa_clear__corec	, _hwa_clear__corec

#define _hwa_clear__corec(o,i,a,...)	_hwa_write_reg( o, allrf, 0 )


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_setup__corec(o,i,a)		\
  _hwa_setup_reg( o, mcucr  );			\
  _hwa_setup_reg( o, mcusr  );			\
  _hwa_setup_reg( o, smcr   );			\
  _hwa_setup_reg( o, osccal )

/*  mcusr is not initialized as its status is not known after RESET
 */
#define _hwa_init__corec(o,i,a)			\
  _hwa_init_reg( o, mcucr,  0x00 );		\
  _hwa_init_reg( o, smcr,   0x00 );		\
  _hwa_init_reg( o, osccal, 0x00 )


#define _hwa_commit__corec(o,i,a)		\
  _hwa_commit_reg( o, mcucr  );			\
  _hwa_commit_reg( o, mcusr  );			\
  _hwa_commit_reg( o, smcr   );			\
  _hwa_commit_reg( o, osccal )


/**
 * @page atmelavr_corec
 * <br>
 */
