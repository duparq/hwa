
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Core
 */

/**
 * @addtogroup atmelavr_corea
 *
 * @act hwa( configure, ... )
 *
 * @code
 * hwa( configure, core0,
 *
 *      //  Whether the `hw( wait, irq )` instruction will put the core in
 *      //  sleep mode or not
 *      //
 *    [ sleep,        enabled,
 *                  | disabled, ]
 *
 *      //  Wanted sleep mode
 *      //
 *    [ sleep_mode,   idle
 *                  | adc_noise_reduction
 *                  | power_down
 *                  | standby             ]
 *      );
 * @endcode
 *
 * @par Argument `sleep_mode`:
 *
 * * `idle`: the SLEEP instruction makes the MCU enter Idle mode, stopping the
 *   CPU but allowing Analog Comparator, ADC, USI, Timer/Counter, Watchdog, and the
 *   interrupt system to continue oper- ating. This sleep mode basically halts clk
 *   CPU and clk FLASH , while allowing the other clocks to run.  Idle mode enables
 *   the MCU to wake up from external triggered interrupts as well as internal ones
 *   like the Timer Overflow. If wake-up from the Analog Comparator interrupt is not
 *   required, the Analog Comparator can be powered down by setting the ACD bit in
 *   “ACSR – Analog Comparator Control and Status Register” on page 120. This will
 *   reduce power consumption in Idle mode. If the ADC is enabled, a conversion
 *   starts automatically when this mode is entered.
 *
 * * `adc_noise_reduction`: the SLEEP instruction makes the MCU enter ADC Noise
 *   Reduction mode, stopping the CPU but allowing the ADC, the external interrupts,
 *   and the Watchdog to continue operating (if enabled). This sleep mode halts clk
 *   I/O , clk CPU , and clk FLASH , while allowing the other clocks to run.  This
 *   improves the noise environment for the ADC, enabling higher resolution
 *   measurements. If the ADC is enabled, a conversion starts automatically when this
 *   mode is entered. Apart form the ADC Conversion Complete interrupt, only an
 *   External Reset, a Watchdog Reset, a Brown-out Reset, an SPM/EEPROM ready
 *   interrupt, an external level interrupt on INT0 or a pin change interrupt can
 *   wake up the MCU from ADC Noise Reduction mode.
 *
 * * `power_down`: the oscillator is stopped, while the external interrupts, the
 *   USI start condition detection and the Watchdog continue operating (if
 *   enabled). Only an External Reset, a Watchdog Reset, a Brown-out Reset, USI
 *   start condition interupt, an external level interrupt on INT0 or a pin
 *   change interrupt can wake up the MCU. This sleep mode halts all generated
 *   clocks, allowing operation of asynchronous modules only.
 */
#define hwa_configure__corea		, _hwa_cfcorea

/*  TODO use a list of wake-up sources instead (or in addition)?
 */

/*	Optionnal parameter `sleep`
 */
#define _hwa_cfcorea(o,a,k,...)					\
  do {									\
    HW_B(_hwa_cfcorea_ksleep_,_hw_is_sleep_##k)(o,k,__VA_ARGS__,,);	\
  } while(0)

#define _hwa_cfcorea_ksleep_0(o,v,...)					\
  HW_G2(_hwa_cfcorea_ksleepmode,HW_IS(sleep_mode,v))(o,v,__VA_ARGS__)

#define _hwa_cfcorea_ksleep_1(o,k,v,...)				\
  HW_B(_hwa_cfcorea_vsleep_,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcorea_vsleep_0(o,v,...)					\
  HW_E(HW_EM_VOAST(v,sleep))

#define _hwa_cfcorea_vsleep_1(o,v,k,...)				\
  _hwa_write( o, se, HW_A1(_hw_state_##v) );			\
  HW_G2(_hwa_cfcorea_ksleepmode,HW_IS(sleep_mode,k))(o,k,__VA_ARGS__)

/*	Optionnal parameter `sleep_mode`
 */
#define hw_sleepmode_idle			, 0
#define hw_sleepmode_adc_noise_reduction	, 1
#define hw_sleepmode_power_down			, 2
#define hw_sleepmode_standby			, 3

#define _hwa_cfcorea_ksleepmode_0(o,...)	HW_EOL(__VA_ARGS__)

#define _hwa_cfcorea_ksleepmode_1(o,k,v,...)				\
  HW_B(_hwa_cfcorea_vsleepmode_,hw_sleepmode_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcorea_vsleepmode_0(o,v,...)				\
  HW_E(HW_EM_VAL(v,sleep_mode,(idle,adc_noise_reduction,power_down,standby)))

#define _hwa_cfcorea_vsleepmode_1(o,v,...)		\
  _hwa_write( o, sm, HW_A1(hw_sleepmode_##v) );	\
  HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_corea
 *
 * @act hw( wait, irq ) puts the core into sleeping mode
 *
 * @code
 * hw( wait, irq );
 * @endcode
 */


/**
 * @addtogroup atmelavr_corea
 *
 * <br>
 * `stat`: returns the status flags of the core in a
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
#define hw_stat__corea			, _hw_stat_corea

/*  FIXME intf0 should be there
 */
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
} _hw_corea_stat_t ;


#define _hw_stat_corea(o,a,...)	_hw_corea_stat(_hw_read(o, mcusr)) HW_EOL(__VA_ARGS__)

HW_INLINE _hw_corea_stat_t _hw_corea_stat( uint8_t byte )
{
  _hw_corea_stat_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @addtogroup atmelavr_corea
 *
 * <br>
 * `clear`:
 *
 * @code
 * hwa( clear, core0 );
 * @endcode
 */
#define hwa_clear__corea		, _hwa_clear_corea

#define _hwa_clear_corea(o,a,...)	_hwa_write(o,allrf,0)



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__corea(o,a)		\
  _hwa_setup_r( o, mcucr  );			\
  _hwa_setup_r( o, mcusr  );			\
  _hwa_setup_r( o, osccal )

/*  mcusr is not initialized as its status is not known after RESET
 */
#define _hwa_init__corea(o,a)			\
  _hwa_init_r( o, mcucr,  0x00 );		\
  _hwa_init_r( o, osccal, 0x00 )

#define _hwa_commit__corea(o,a)		\
  _hwa_commit_r( o, mcucr  );			\
  _hwa_commit_r( o, mcusr  );			\
  _hwa_commit_r( o, osccal )
