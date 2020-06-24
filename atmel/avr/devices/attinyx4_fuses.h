
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @addtogroup attinyx4
 * @{
 *
 * @name Fuse bytes
 *
 * These definitions are computed by HWA from the target device name and the
 * definitions provided by the user.
 *
 * @{
 */

/**
 * @hideinitializer
 *
 *  Computed value of the fuse extended byte.
 */
#define HW_DEVICE_FUSE_EB			\
  (0xFE | HW_DEVICE_SELFPRGEN)

/**
 * @hideinitializer
 *
 *  Computed value of the fuse high byte.
 */
#define HW_DEVICE_FUSE_HB			\
  HW_DEVICE_RSTDISBL<<7 |			\
  HW_DEVICE_DWEN<<6 |				\
  HW_DEVICE_SPIEN<<5 |				\
  HW_DEVICE_WDTON<<4 |				\
  HW_DEVICE_EESAVE<<3 |				\
  HW_DEVICE_BODLEVEL

/**
 * @hideinitializer
 *
 *  Computed value of the fuse low byte.
 */
#define HW_DEVICE_FUSE_LB			\
  HW_DEVICE_CKDIV8<<7 |				\
  HW_DEVICE_CKOUT<<6 |				\
  HW_DEVICE_SUT10<<4 |				\
  HW_DEVICE_CKSEL31<<1 |			\
  HW_DEVICE_CKSEL0

/**
 * @}
 *
 * @ingroup attinyx4
 * @name User-defineable symbols
 *
 * Before including the device-specific header, the user can define these
 * symbols to describe the configuration of the target device. HWA defines
 * undefined symbols with factory values.
 *
 * @{
 */

/**
 * @hideinitializer
 *
 * How the device is clocked.
 * <dl>
 *  <dt>external</dt>		<dd>External source on pin CLKI</dd>
 *  <dt>rc_8MHz</dt>		<dd>Internal RC oscillator</dd>
 *  <dt>rc_128kHz</dt>		<dd>Internal RC oscillator (watchdog)</dd>
 *  <dt>low_freq_xosc</dt>	<dd>Crystal/resonator oscillator between pins XTAL1 and XTAL2</dd>
 *  <dt>xosc</dt>		<dd>Crystal/resonator oscillator between pins XTAL1 and XTAL2</dd>
 * </dl>
 */
#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC			rc_8MHz
#endif
/**
 * @hideinitializer
 *
 * Clock prescaler
 * <dl>
 *  <dt>1</dt>		<dd>Clock not prescaled</dd>
 *  <dt>8</dt>		<dd>Clock divided by 8</dd>
 * </dl>
 */
#if !defined HW_DEVICE_CLK_PSC
#  define HW_DEVICE_CLK_PSC				8
#endif

/**
 * @hideinitializer
 *
 * Startup delays
 *
 * Valid values depend on the clocking configuration.
 *
 * <dl>
 *  <dt>6CK_14CK</dt>		<dd></dd>
 *  <dt>6CK_14CK_4ms</dt>	<dd></dd>
 *  <dt>6CK_14CK_64ms</dt>	<dd></dd>
 *  <dt>1KCK_4ms</dt>		<dd></dd>
 *  <dt>1KCK_64ms</dt>		<dd></dd>
 *  <dt>32KCK_64ms</dt>		<dd></dd>
 *  <dt>258CK_14CK_4ms</dt>	<dd></dd>
 *  <dt>258CK_14CK_64ms</dt>	<dd></dd>
 *  <dt>1KCK_14CK</dt>		<dd></dd>
 *  <dt>1KCK_14CK_4ms</dt>	<dd></dd>
 *  <dt>1KCK_14CK_64ms</dt>	<dd></dd>
 *  <dt>16KCK_14CK</dt>		<dd></dd>
 *  <dt>16KCK_14CK_4ms</dt>	<dd></dd>
 *  <dt>16KCK_14CK_64ms</dt>	<dd></dd>
 * </dl>
 */
#if defined DOXYGEN
#  define HW_DEVICE_STARTUP_DELAYS
#endif

/**
 * @hideinitializer
 *
 * Whether the device outputs its clock
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT			disabled
#endif

/**
 * @hideinitializer
 *
 * Whether the device can write into its Flash program memory
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_SELF_PROGRAMMING
#  define HW_DEVICE_SELF_PROGRAMMING			enabled
#endif

/**
 * @hideinitializer
 *
 * Whether the device can be reset via its RESET pin
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_EXTERNAL_RESET
#  define HW_DEVICE_EXTERNAL_RESET			enabled
#endif

/**
 * @hideinitializer
 *
 * Whether the Debug Wire is operationnal
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_DEBUG_WIRE
#  define HW_DEVICE_DEBUG_WIRE				disabled
#endif

/**
 * @hideinitializer
 *
 * Whether the device can be programmed via the SPI
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_SERIAL_PROGRAMMING
#  define HW_DEVICE_SERIAL_PROGRAMMING			enabled
#endif

/**
 * @hideinitializer
 *
 * Whether the watchdog is always running
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON			no
#endif

/**
 * @hideinitializer
 *
 * Whether the EEPROM memory is erased when a chip erase occurs
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE	no
#endif

/**
 * @hideinitializer
 *
 * Brown-out detection level
 *
 * <dl>
 *  <dt>off</dt>		<dd></dd>
 *  <dt>1700_2000mV</dt>	<dd></dd>
 *  <dt>2500_2900mV</dt>	<dd></dd>
 *  <dt>4100_4500mV</dt>	<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION			off
#endif

/** @} */


#define _hw_is_rc_8MHz_rc_8MHz			, 1
#define _hw_is_rc_128kHz_rc_128kHz		, 1
#define _hw_is_low_freq_xosc_low_freq_xosc	, 1
#define _hw_is_xosc_xosc			, 1

#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31			0
#  define HW_DEVICE_CKSEL0			0
#  define HW_NC_PB0				1
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31			1
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31			2
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define HW_DEVICE_CKSEL31			3
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#  define HW_NC_PB0				1
#  define HW_NC_PB1				1
#elif HW_IS(xosc, HW_DEVICE_CLK_SRC)
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_CKSEL31			4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_CKSEL31			5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_CKSEL31			6
#  else
#    define HW_DEVICE_CKSEL31			7
#  endif
#  define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#  define HW_NC_PB0				1
#  define HW_NC_PB1				1
#else
#  error HW_EM_VSL(HW_DEVICE_CLK_SRC, (external, rc_8MHz, rc_128kHz, low_freq_xosc, xosc))
#endif

#if hw_syshz_base == 0
#  error HW_EM_SD(HW_DEVICE_CLK_SRC_HZ)
#endif


#if HW_DEVICE_CLK_PSC == 8
#  define HW_DEVICE_CKDIV8				0
#  define HW_SYSHZ					hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_CKDIV8				1
#  define HW_SYSHZ					hw_syshz_base
#else
#  error HW_EM_VSL(HW_DEVICE_CLK_PSC, (1,8))
#endif


#define _hw_is_6CK_14CK_6CK_14CK			, 1
#define _hw_is_6CK_14CK_4ms_6CK_14CK_4ms		, 1
#define _hw_is_6CK_14CK_64ms_6CK_14CK_64ms		, 1
#define _hw_is_1KCK_4ms_1KCK_4ms			, 1
#define _hw_is_1KCK_64ms_1KCK_64ms			, 1
#define _hw_is_32KCK_64ms_32KCK_64ms			, 1
#define _hw_is_258CK_14CK_4ms_258CK_14CK_4ms		, 1
#define _hw_is_258CK_14CK_64ms_258CK_14CK_64ms		, 1
#define _hw_is_1KCK_14CK_1KCK_14CK			, 1
#define _hw_is_1KCK_14CK_4ms_1KCK_14CK_4ms		, 1
#define _hw_is_1KCK_14CK_64ms_1KCK_14CK_64ms		, 1
#define _hw_is_16KCK_14CK_16KCK_14CK			, 1
#define _hw_is_16KCK_14CK_4ms_16KCK_14CK_4ms		, 1
#define _hw_is_16KCK_14CK_64ms_16KCK_14CK_64ms		, 1

#if defined HW_DEVICE_STARTUP_DELAYS
#  if HW_DEVICE_CKSEL31 < 3
#    define HW_DEVICE_CKSEL0				0
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_4ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (6CK_14CK, 6CK_14CK_4ms, 6CK_14CK_64ms))
#    endif
#  elif HW_DEVICE_CKSEL31 == 3
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_4ms)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_64ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 32KCK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (6CK_14CK, 6CK_14CK_4ms, 6CK_14CK_64ms))
#    endif
#  else
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				3
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				3
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (258CK_14CK_4ms, 258CK_14CK_64ms, 1KCK_14CK, \
						  1KCK_14CK_4ms, 1KCK_14CK_64ms, 16KCK_14CK, \
						  16KCK_14CK_4ms, 16KCK_14CK_64ms))
#    endif
#  endif
#else
#  define HW_DEVICE_SUT10				2
#endif


#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_CKOUT				0
#  define HW_NC_PB2					1
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_CKOUT				1
#else
#  error HW_EM_VSL(HW_DEVICE_CLOCK_OUTPUT, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_SELF_PROGRAMMING, enabled)
#  define HW_DEVICE_SELFPRGEN				0
#elif HW_IS(HW_DEVICE_SELF_PROGRAMMING, disabled)
#  define HW_DEVICE_SELFPRGEN				1
#else
#  error HW_EM_VSL(HW_DEVICE_SELF_PROGRAMMING, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_RSTDISBL				1
#  define HW_NC_PB3					1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_RSTDISBL				0
#else
#  error HW_EM_VSL(HW_DEVICE_EXTERNAL_RESET, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_DWEN				0
#  define HW_NC_PB3					1
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_DWEN				1
#else
#  error HW_EM_VSL(HW_DEVICE_DEBUG_WIRE, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_SPIEN				0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_SPIEN				1
#else
#  error HW_EM_VSL(HW_DEVICE_SERIAL_PROGRAMMING, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_WDTON				0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_WDTON				1
#else
#  error HW_EM_VSL(HW_DEVICE_WATCHDOG_ALWAYS_ON, (yes, no))
#endif


#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, yes)
#  define HW_DEVICE_EESAVE				0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, no)
#  define HW_DEVICE_EESAVE				1
#else
#  error HW_EM_VSL(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, (yes, no))
#endif


#define _hw_is_1700_2000mV_1700_2000mV			, 1
#define _hw_is_2500_2900mV_2500_2900mV			, 1
#define _hw_is_4100_4500mV_4100_4500mV			, 1

#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_BODLEVEL				6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_BODLEVEL				5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_BODLEVEL				4
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_BODLEVEL				7
#else
#  error HW_EM_VSL(HW_DEVICE_BROWNOUT_DETECTION, (1700_2000mV, 2500_2900mV, 4100_4500mV, off))
#endif

/** @} */
