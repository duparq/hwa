
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief ATmegaX8 fuses & user definitions
 */

/**
 * @addtogroup atmegax8
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
 *  Computed value of the fuse extended byte. Default: 0xFF.
 */
/*  FIXME: there's a problem with avrdude reading/writing unprogrammed fuses of
 *  extended byte as 0 instead of 1.
 */
#define HW_DEVICE_FUSE_EB			\
  /* 0xF8 | */					\
  HW_DEVICE_FUSE_BODLEVEL


/**
 * @hideinitializer
 *
 * Computed value of the fuse high byte. Default: 0xD9.
 */
#define HW_DEVICE_FUSE_HB			\
  HW_DEVICE_FUSE_RSTDISBL<<7 |			\
  HW_DEVICE_FUSE_DWEN<<6 |			\
  HW_DEVICE_FUSE_SPIEN<<5 |			\
  HW_DEVICE_FUSE_WDTON<<4 |			\
  HW_DEVICE_FUSE_EESAVE<<3 |			\
  HW_DEVICE_FUSE_BOOTSZ<<1 |			\
  HW_DEVICE_FUSE_BOOTRST


/**
 * @hideinitializer
 *
 * Computed value of the fuse low byte. Default: 0x62.
 */
#define HW_DEVICE_FUSE_LB			\
  HW_DEVICE_FUSE_CKDIV8<<7 |			\
  HW_DEVICE_FUSE_CKOUT<<6 |			\
  HW_DEVICE_FUSE_SUT10<<4 |			\
  HW_DEVICE_FUSE_CKSEL31<<1 |			\
  HW_DEVICE_FUSE_CKSEL0


/**
 * @}
 *
 * @ingroup atmegax8
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
 *  Size of the boot section in bytes: 512, 1024, 2048, or 4096
 *
 */
#if !defined HW_DEVICE_BOOTSECTION_SIZE
#  define HW_DEVICE_BOOTSECTION_SIZE			4096
#endif

/**
 * @hideinitializer
 *
 *  How the device is clocked.
 * <dl>
 *  <dt>external</dt>		<dd>External source on pin CLKI</dd>
 *  <dt>rc_128kHz</dt>		<dd>Internal RC oscillator (watchdog)</dd>
 *  <dt>rc_8MHz</dt>		<dd>Internal RC oscillator</dd>
 *  <dt>low_freq_xosc</dt>	<dd>Crystal/resonator oscillator between pins XTAL1 and XTAL2</dd>
 *  <dt>low_power_xosc</dt>	<dd>Crystal/resonator oscillator between pins XTAL1 and XTAL2</dd>
 *  <dt>full_swing_xosc</dt>		<dd>Crystal/resonator oscillator between pins XTAL1 and XTAL2</dd>
 * </dl>
 */
#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC			rc_8MHz
#  define HW_DEVICE_CLK_SRC_HZ			8000000		/**<> */
#endif

/**
 * @hideinitializer
 *
 *  Startup delays
 *
 * Valid values depend on the clocking configuration.
 *
 * <dl>
 *  <dt>4CK</dt>		<dd></dd>
 *  <dt>4CK_4ms</dt>		<dd></dd>
 *  <dt>4CK_64ms</dt>		<dd></dd>
 *  <dt>6CK_14CK</dt>		<dd></dd>
 *  <dt>6CK_14CK_4ms</dt>	<dd></dd>
 *  <dt>6CK_14CK_64ms</dt>	<dd></dd>
 *  <dt>258CK_14CK_4ms</dt>	<dd></dd>
 *  <dt>258CK_14CK_64ms</dt>	<dd></dd>
 *  <dt>1KCK_4ms</dt>		<dd></dd>
 *  <dt>1KCK_64ms</dt>		<dd></dd>
 *  <dt>1KCK_14CK</dt>		<dd></dd>
 *  <dt>1KCK_14CK_4ms</dt>	<dd></dd>
 *  <dt>1KCK_14CK_64ms</dt>	<dd></dd>
 *  <dt>16KCK_14CK</dt>		<dd></dd>
 *  <dt>16KCK_14CK_4ms</dt>	<dd></dd>
 *  <dt>16KCK_14CK_64ms</dt>	<dd></dd>
 *  <dt>32KCK_64ms</dt>		<dd></dd>
 * </dl>
 */
#if defined DOXYGEN
#  define HW_DEVICE_STARTUP_DELAYS
#endif

/**
 * @hideinitializer
 *
 *  Whether the device outputs its clock
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
 *  Whether the device can be reset via its RESET pin
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
 *  Whether the Debug Wire is operationnal
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
 *  Whether the device can be programmed via the SPI
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
 *  Whether the watchdog is always running
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
 *  Whether the EEPROM memory is erased when a chip erase occurs
 *
 * <dl>
 *  <dt>enabled</dt>		<dd></dd>
 *  <dt>disabled</dt>		<dd></dd>
 * </dl>
 */
#if !defined HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE	no
#endif

/**
 * @hideinitializer
 *
 *  Brown-out detection level
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

/**
 * @hideinitializer
 *
 *  Whether the device starts the bootloader (in the boot Flash) or the application.
 */
#if !defined HW_DEVICE_BOOT
#  define HW_DEVICE_BOOT				application
#endif

/** @} */



#if HW_DEVICE_BOOTSECTION_SIZE == 512
#  define HW_DEVICE_FUSE_BOOTSZ			3
#elif HW_DEVICE_BOOTSECTION_SIZE == 1024
#  define HW_DEVICE_FUSE_BOOTSZ			2
#elif HW_DEVICE_BOOTSECTION_SIZE == 2048
#  define HW_DEVICE_FUSE_BOOTSZ			1
#elif HW_DEVICE_BOOTSECTION_SIZE == 4096
#  define HW_DEVICE_FUSE_BOOTSZ			0
#else
#  error HW_EM_VSL(HW_DEVICE_BOOTSECTION_SIZE, (512, 1024, 2048, 4096))
#endif


#ifndef HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_CLK_SRC_HZ
#endif

#define _hw_is_rc_8MHz_rc_8MHz			, 1
#define _hw_is_rc_128kHz_rc_128kHz		, 1
#define _hw_is_low_freq_xosc_low_freq_xosc	, 1
#define _hw_is_low_power_xosc_low_power_xosc	, 1
#define _hw_is_full_swing_xosc_full_swing_xosc	, 1

#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31		0
#  define HW_DEVICE_FUSE_CKSEL0			0
#  define HW_NC_PB6				1
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31		1
#  define HW_DEVICE_FUSE_CKSEL0			0
#  define hw_syshz_base				8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31		1
#  define HW_DEVICE_FUSE_CKSEL0			1
#  define hw_syshz_base				128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_FUSE_CKSEL31		2
#  define HW_NC_PB6				1
#  define HW_NC_PB7				1
#elif HW_IS(HW_DEVICE_CLK_SRC, low_power_xosc)
#  define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_FUSE_CKSEL31		4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_FUSE_CKSEL31		5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_FUSE_CKSEL31		6
#  else
#    define HW_DEVICE_FUSE_CKSEL31		7
#  endif
#  define HW_NC_PB6				1
#  define HW_NC_PB7				1
#elif HW_IS(HW_DEVICE_CLK_SRC, full_swing_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base			HW_DEVICE_CLK_SRC_HZ
#    define HW_DEVICE_FUSE_CKSEL31		3
#  endif
#  define HW_NC_PB6				1
#  define HW_NC_PB7				1
#else
#  error HW_DEVICE_CLK_SRC can be `rc_8MHz`, `rc_128kHz`, `low_freq_xosc`, `low_power_xosc`, `full_swing_xosc`, or `external`.
#endif

/*  Check that we have a valid hw_syshz_base
 */
#if HW_IS(,hw_syshz_base)
#  error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#endif

#if !defined HW_DEVICE_CLK_PSC
#  define HW_DEVICE_CLK_PSC				8
#endif

#if HW_DEVICE_CLK_PSC == 8
#  define HW_DEVICE_FUSE_CKDIV8				0
#  define HW_SYSHZ					hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_FUSE_CKDIV8				1
#  define HW_SYSHZ					hw_syshz_base
#else
#  error HW_EM_VAL(HW_DEVICE_CLK_PSC,HW_DEVICE_CLK_PSC,(1,8))
#endif



#define _hw_is_4CK_4CK					, 1
#define _hw_is_4CK_4ms_4CK_4ms				, 1
#define _hw_is_4CK_64ms_4CK_64ms			, 1
#define _hw_is_6CK_14CK_6CK_14CK			, 1
#define _hw_is_6CK_14CK_4ms_6CK_14CK_4ms		, 1
#define _hw_is_6CK_14CK_64ms_6CK_14CK_64ms		, 1
#define _hw_is_258CK_14CK_4ms_258CK_14CK_4ms		, 1
#define _hw_is_258CK_14CK_64ms_258CK_14CK_64ms		, 1
#define _hw_is_1KCK_4ms_1KCK_4ms			, 1
#define _hw_is_1KCK_64ms_1KCK_64ms			, 1
#define _hw_is_1KCK_14CK_1KCK_14CK			, 1
#define _hw_is_1KCK_14CK_4ms_1KCK_14CK_4ms		, 1
#define _hw_is_1KCK_14CK_64ms_1KCK_14CK_64ms		, 1
#define _hw_is_16KCK_14CK_16KCK_14CK			, 1
#define _hw_is_16KCK_14CK_4ms_16KCK_14CK_4ms		, 1
#define _hw_is_16KCK_14CK_64ms_16KCK_14CK_64ms		, 1
#define _hw_is_32KCK_64ms_32KCK_64ms			, 1

#if defined HW_DEVICE_STARTUP_DELAYS
#  if HW_DEVICE_FUSE_CKSEL31 < 2
#    define HW_DEVICE_FUSE_CKSEL0				0
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK)
#      define HW_DEVICE_FUSE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_4ms)
#      define HW_DEVICE_FUSE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_64ms)
#      define HW_DEVICE_FUSE_SUT10				2
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (6CK_14CK, 6CK_14CK_4ms, 6CK_14CK_64ms))
#    endif
#  elif HW_DEVICE_FUSE_CKSEL31 == 2
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK)
#      define HW_DEVICE_FUSE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_4ms)
#      define HW_DEVICE_FUSE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_64ms)
#      define HW_DEVICE_FUSE_SUT10				2
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (4CK, 4CK_4ms, 4CK_64ms))
#    endif
#  else
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_4ms)
#      define HW_DEVICE_FUSE_CKSEL0				0
#      define HW_DEVICE_FUSE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_64ms)
#      define HW_DEVICE_FUSE_CKSEL0				0
#      define HW_DEVICE_FUSE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK)
#      define HW_DEVICE_FUSE_CKSEL0				0
#      define HW_DEVICE_FUSE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_4ms)
#      define HW_DEVICE_FUSE_CKSEL0				0
#      define HW_DEVICE_FUSE_SUT10				3
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_64ms)
#      define HW_DEVICE_FUSE_CKSEL0				1
#      define HW_DEVICE_FUSE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK)
#      define HW_DEVICE_FUSE_CKSEL0				1
#      define HW_DEVICE_FUSE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_4ms)
#      define HW_DEVICE_FUSE_CKSEL0				1
#      define HW_DEVICE_FUSE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_64ms)
#      define HW_DEVICE_FUSE_CKSEL0				1
#      define HW_DEVICE_FUSE_SUT10				3
#    else
#      error HW_EM_VSL(HW_DEVICE_STARTUP_DELAYS, (258CK_14CK_4ms, 258CK_14CK_64ms, 1KCK_14CK, \
						  1KCK_14CK_4ms, 1KCK_14CK_64ms, 16KCK_14CK, \
						  16KCK_14CK_4ms, 16KCK_14CK_64ms))
#    endif
#  endif
#else
#  define HW_DEVICE_FUSE_SUT10				2
#endif


#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_FUSE_CKOUT				0
#  define HW_NC_PB0					1
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_FUSE_CKOUT				1
#else
#  error HW_EM_VSL(HW_DEVICE_EXTERNAL_RESET, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_FUSE_RSTDISBL			1
#  define HW_NC_PC6					1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_FUSE_RSTDISBL			0
#else
#  error HW_EM_VSL(HW_DEVICE_EXTERNAL_RESET, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_FUSE_DWEN				0
#  define HW_NC_PC6					1
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_FUSE_DWEN				1
#else
#  error HW_EM_VSL(HW_DEVICE_DEBUG_WIRE, (enabled, disabled))
#endif


#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_FUSE_SPIEN				0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_FUSE_SPIEN				1
#else
#  error HW_EM_VSL(HW_DEVICE_SERIAL_PROGRAMMING, (enabled, disabled))
#endif


#define _hw_is_1700_2000mV_1700_2000mV			, 1
#define _hw_is_2500_2900mV_2500_2900mV			, 1
#define _hw_is_4100_4500mV_4100_4500mV			, 1

#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_FUSE_BODLEVEL			7
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_FUSE_BODLEVEL			6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_FUSE_BODLEVEL			5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_FUSE_BODLEVEL			4
#else
#  error HW_EM_VSL(HW_DEVICE_BROWNOUT_DETECTION, (1700_2000mV, 2500_2900mV, 4100_4500mV, off))
#endif

#define _hw_is_application_application	, 1
#define _hw_is_bootloader_bootloader	, 1


#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_FUSE_WDTON				0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_FUSE_WDTON				1
#else
#  error HW_EM_VSL(HW_DEVICE_WATCHDOG_ALWAYS_ON, (yes, no))
#endif


#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE, yes)
#  define HW_DEVICE_FUSE_EESAVE				0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE, no)
#  define HW_DEVICE_FUSE_EESAVE				1
#else
#  error HW_EM_VSL(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, (yes, no))
#endif


#if HW_IS(HW_DEVICE_BOOT, application)
#  define HW_DEVICE_FUSE_BOOTRST			1
#elif HW_IS(HW_DEVICE_BOOT, bootloader)
#  define HW_DEVICE_FUSE_BOOTRST			0
#else
#  error HW_EM_VSL(HW_DEVICE_BOOT, (application, bootloader))
#endif
  
/** @} */
