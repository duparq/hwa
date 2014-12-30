
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define HW_DEVICE_ATMEGAX8


/*  Fuses for clocking
 */
#define hw_is_internal_rc_internal_rc				, 1
#define hw_is_internal_watchdog_internal_watchdog		, 1
#define hw_is_external_low_power_xo_external_low_power_xo	, 1
#define hw_is_external_full_swing_xo_external_full_swing_xo	, 1
#define hw_is_external_external					, 1

#define hw_is_4CK_4CK					, 1
#define hw_is_4CK_4ms_4CK_4ms				, 1
#define hw_is_4CK_64ms_4CK_64ms				, 1
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


#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				internal_rc
#endif
#if HW_IS(HW_DEVICE_CLK_SRC, external)
#  define HW_DEVICE_CKSEL31				0
#  define HW_DEVICE_CKSEL0				0
#elif HW_IS(HW_DEVICE_CLK_SRC, internal_rc)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					8000000
#elif HW_IS(HW_DEVICE_CLK_SRC, internal_watchdog)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				1
#  define hw_syshz_base					128000
#elif HW_IS(HW_DEVICE_CLK_SRC, external_low_power_xo)
#  ifndef HW_DEVICE_CLK_HZ
#    error HW_DEVICE_CLK_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_HZ
#    if HW_DEVICE_CLK_HZ < 400000 /* Assume values other than 32768 are acceptable */
#      define HW_DEVICE_CKSEL31				2
#      define HW_DEVICE_CKSEL0				0
#    else
#      if HW_DEVICE_CLK_HZ < 900000
#        define HW_DEVICE_CKSEL31			4
#      elif HW_DEVICE_CLK_HZ < 3000000
#        define HW_DEVICE_CKSEL31			5
#      elif HW_DEVICE_CLK_HZ < 8000000
#        define HW_DEVICE_CKSEL31			6
#      else
#        define HW_DEVICE_CKSEL31			7
#      endif
#    endif
#  endif
#elif HW_IS(HW_DEVICE_CLK_SRC, external_full_swing_xo)
#  ifndef HW_DEVICE_CLK_HZ
#    error HW_DEVICE_CLK_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_HZ
#    define HW_DEVICE_CKSEL31				3
#  endif
#else
#  error HW_DEVICE_CLK_SRC must be defined as one of `internal_rc`, `internal_watchdog`, `external_low_power_xo`, `external_full_swing_xo`, or `external`.
#endif

/*	SUT
 */
#if defined HW_DEVICE_STARTUP_DELAYS
#  if HW_DEVICE_CKSEL31 < 2
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
#  elif HW_DEVICE_CKSEL31 == 2
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_4ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `4CK`, `4CK_4ms`, or `4CK_64ms`.
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

/* #if !defined HW_DEVICE_SELF_PROGRAMMING */
/* #  define HW_DEVICE_SELF_PROGRAMMING			enabled */
/* #endif */
/* #if HW_IS(HW_DEVICE_SELF_PROGRAMMING, enabled) */
/* #  define HW_DEVICE_SELFPRGEN				0 */
/* #elif HW_IS(HW_DEVICE_SELF_PROGRAMMING, disabled) */
/* #  define HW_DEVICE_SELFPRGEN				1 */
/* #else */
/* #  error HW_DEVICE_SELF_PROGRAMMING must be defined as `enabled` or `disabled` (default). */
/* #endif */

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
#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_BODLEVEL				7
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_BODLEVEL				6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_BODLEVEL				5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_BODLEVEL				4
#else
#  error HW_DEVICE_BROWNOUT_DETECTION must be defined as `1700_2000mV`, `2500_2900mV`, `4100_4500mV` or `off` (default).
#endif

#define hw_is_application_application			, 1
#define hw_is_bootloader_bootloader			, 1

#if !defined HW_DEVICE_BOOT
#  define HW_DEVICE_BOOT				application
#endif
#if HW_IS(HW_DEVICE_BOOT, application)
#  define HW_DEVICE_BOOTRST				1
#elif HW_IS(HW_DEVICE_BOOT, bootloader)
#  define HW_DEVICE_BOOTRST				0
#else
#  error HW_DEVICE_RESET_VECTOR must be defined as `bootloader` or `application` (default).
#endif


/*	The include order and ids follows that of the datasheet
 */
#include "hwa_atmelavr_1.h"
#include "hwa_atmegax8_cores_1.h"		/* id: 100 */
/* #include "hwa_atmegax8_pcints_1.h"		/\* id: 200 *\/ */
#include "hwa_atmegax8_watchdogs_1.h"		/* id: 110 */
#include "hwa_atmegax8_ios_1.h"			/* id: 300 */
/* #include "hwa_atmegax8_counters_1.h"		/\* id: 400 *\/ */
/* #include "hwa_atmegax8_pscs_1.h"		/\* id: 500 *\/ */
/* #include "hwa_atmegax8_usis_1.h"		/\* id: 600 *\/ */
/* #include "hwa_atmegax8_acmps_1.h"		/\* id: 700 *\/ */
/* #include "hwa_atmegax8_adcs_1.h"		/\* id: 800 *\/ */
#include "hwa_atmegax8_eeproms_1.h"		/* id: 1000 */
#include "hwa_atmegax8_flashs_1.h"		/* id: 1100 */

#if !defined __ASSEMBLER__ 

#define HWA_DCL					\
  HWA_DCL_CORES ;				\
  HWA_DCL_IOS ;					\

  /* HWA_DCL_PCINTS ;				\ */
  /* HWA_DCL_COUNTERS ;				\ */
  /* HWA_DCL_USIS ;				\ */
  /* HWA_DCL_ACMPS ;				\ */
  /* HWA_DCL_ADCS ;				\ */
  /* HWA_DCL_WATCHDOGS ; */


#endif /* !defined __ASSEMBLER__ */
