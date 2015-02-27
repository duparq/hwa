
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Common definitions for ATtiny{2,4,8}4 devices
 */


#define HW_DEVICE_ATTINYX4


/*	Clocking
 */
#define hw_is_external_external				, 1
#define hw_is_rc_8MHz_rc_8MHz				, 1
#define hw_is_rc_128kHz_rc_128kHz			, 1
#define hw_is_xosc_xosc					, 1

#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				internal_rc
#endif

#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				0
#  define HW_DEVICE_CKSEL0				0
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				2
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					128000
#elif HW_IS(xosc, HW_DEVICE_CLK_SRC)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#    if HW_DEVICE_CLK_SRC_HZ < 400000 /* Assume values other than 32768 are acceptable */
#      define HW_DEVICE_CKSEL31				3
#      define HW_DEVICE_CKSEL0				0
#    else
#      if HW_DEVICE_CLK_SRC_HZ < 900000
#        define HW_DEVICE_CKSEL31			4
#      elif HW_DEVICE_CLK_SRC_HZ < 3000000
#        define HW_DEVICE_CKSEL31			5
#      elif HW_DEVICE_CLK_SRC_HZ < 8000000
#        define HW_DEVICE_CKSEL31			6
#      else
#        define HW_DEVICE_CKSEL31			7
#      endif
#    endif
#  endif
#else
#  error HW_DEVICE_CLK_SRC must be defined as one of `external`, `rc_8MHz`, `rc_128kHz`, or `xosc`.
#endif

#define hw_is_6CK_14CK_6CK_14CK				, 1
#define hw_is_6CK_14CK_4ms_6CK_14CK_4ms			, 1
#define hw_is_6CK_14CK_64ms_6CK_14CK_64ms		, 1
#define hw_is_1KCK_4ms_1KCK_4ms				, 1
#define hw_is_1KCK_64ms_1KCK_64ms			, 1
#define hw_is_32KCK_64ms_32KCK_64ms			, 1
#define hw_is_258CK_14CK_4ms_258CK_14CK_4ms		, 1
#define hw_is_258CK_14CK_64ms_258CK_14CK_64ms		, 1
#define hw_is_1KCK_14CK_1KCK_14CK			, 1
#define hw_is_1KCK_14CK_4ms_1KCK_14CK_4ms		, 1
#define hw_is_1KCK_14CK_64ms_1KCK_14CK_64ms		, 1
#define hw_is_16KCK_14CK_16KCK_14CK			, 1
#define hw_is_16KCK_14CK_4ms_16KCK_14CK_4ms		, 1
#define hw_is_16KCK_14CK_64ms_16KCK_14CK_64ms		, 1

/*	SUT
 */
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
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif
#  elif HW_DEVICE_CKSEL31 == 3
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_4ms)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_64ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 32KCK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
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
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `258CK_14CK_4ms`, `258CK_14CK_64ms`, `1KCK_14CK`, `1KCK_14CK_4ms`, `1KCK_14CK_64ms`, `16KCK_14CK`, `16KCK_14CK_4ms`, or `16KCK_14CK_64ms`.
#    endif
#  endif
#else
#  define HW_DEVICE_SUT10				2
#endif


#if !defined HW_DEVICE_CLK_PSC
#  define HW_DEVICE_CLK_PSC				8
#endif
#if HW_DEVICE_CLK_PSC == 8
#  define HW_DEVICE_CKDIV8				0
#  define hw_syshz					hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_CKDIV8				1
#  define hw_syshz					hw_syshz_base
#else
#  error HW_DEVICE_CLK_PSC must be defined as one of `8` or `1`.
#endif

#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT			disabled
#endif
#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_CKOUT				0
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_CKOUT				1
#else
#  error HW_DEVICE_CLOCK_OUTPUT must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_SELF_PROGRAMMING
#  define HW_DEVICE_SELF_PROGRAMMING			enabled
#endif
#if HW_IS(HW_DEVICE_SELF_PROGRAMMING, enabled)
#  define HW_DEVICE_SELFPRGEN				0
#elif HW_IS(HW_DEVICE_SELF_PROGRAMMING, disabled)
#  define HW_DEVICE_SELFPRGEN				1
#else
#  error HW_DEVICE_SELF_PROGRAMMING must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_EXTERNAL_RESET
#  define HW_DEVICE_EXTERNAL_RESET			enabled
#endif
#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_RSTDISBL				1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_RSTDISBL				0
#else
#  error HW_DEVICE_EXTERNAL_RESET must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_DEBUG_WIRE
#  define HW_DEVICE_DEBUG_WIRE				disabled
#endif
#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_DWEN				0
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_DWEN				1
#else
#  error HW_DEVICE_DEBUG_WIRE must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_SERIAL_PROGRAMMING
#  define HW_DEVICE_SERIAL_PROGRAMMING			enabled
#endif
#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_SPIEN				0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_SPIEN				1
#else
#  error HW_DEVICE_SERIAL_PROGRAMMING must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON			no
#endif
#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_WDTON				0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_WDTON				1
#else
#  error HW_DEVICE_WATCHDOG_ALWAYS_ON must be defined as `yes` or `no` (default).
#endif

#if !defined HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE	no
#endif
#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, yes)
#  define HW_DEVICE_EESAVE				0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, no)
#  define HW_DEVICE_EESAVE				1
#else
#  error HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE must be defined as `yes` or `no` (default).
#endif

#define hw_is_1700_2000mV_1700_2000mV			, 1
#define hw_is_2500_2900mV_2500_2900mV			, 1
#define hw_is_4100_4500mV_4100_4500mV			, 1

#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION			off
#endif
#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_BODLEVEL				6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_BODLEVEL				5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_BODLEVEL				4
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_BODLEVEL				7
#else
#  error HW_DEVICE_BROWNOUT_DETECTION must be defined as `1700_2000mV`, `2500_2900mV`, `4100_4500mV` or `off` (default).
#endif


#define HW_DEVICE_FUSE_EB			\
  0xFE | HW_DEVICE_SELFPRGEN

#define HW_DEVICE_FUSE_HB			\
  HW_DEVICE_RSTDISBL<<7 |			\
  HW_DEVICE_DWEN<<6 |				\
  HW_DEVICE_SPIEN<<5 |				\
  HW_DEVICE_WDTON<<4 |				\
  HW_DEVICE_EESAVE<<3 |				\
  HW_DEVICE_BODLEVEL

#define HW_DEVICE_FUSE_LB			\
  HW_DEVICE_CKDIV8<<7 |				\
  HW_DEVICE_CKOUT<<6 |				\
  HW_DEVICE_SUT10<<4 |				\
  HW_DEVICE_CKSEL31<<1 |			\
  HW_DEVICE_CKSEL0


/*	The include order and ids follows that of the datasheet
 */
#include "hwa_atmelavr_1.h"
#include "hwa_attinyx4_cores_1.h"		/* id: 100 */
//#include "hwa_attinyx4_pcints_1.h"		/* id: 200 */
#include "hwa_attinyx4_ios_1.h"			/* id: 300 */
#include "hwa_attinyx4_counters_1.h"		/* id: 400 */
/* #include "hwa_attinyx4_pscs_1.h"		/\* id: 500 *\/ */
/* #include "hwa_attinyx4_usis_1.h"		/\* id: 600 *\/ */
#include "hwa_attinyx4_acmps_1.h"		/* id: 700 */
/* #include "hwa_attinyx4_adcs_1.h"		/\* id: 800 *\/ */
#include "hwa_attinyx4_watchdogs_1.h"		/* id: 900 */
#include "hwa_attinyx4_eeproms_1.h"		/* id: 1000 */
#include "hwa_attinyx4_flashs_1.h"		/* id: 1100 */


#define HWA_DCL					\
  hwa_corea_t	core0 ;				\
  hwa_io8a_t	porta ;				\
  hwa_io8a_t	portb ;				\
  hwa_wdoga_t	watchdog0 ;			\
  hwa_c8a_t	counter0 ;			\
  hwa_c16a_t	counter1 ;			\
  hwa_acmpa_t	acmp0 ;				\

