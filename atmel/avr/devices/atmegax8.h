
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega48A/PA/88A/PA/168A/PA/328/P devices
 */

#include "../hwa_1.h"

/**
 * @page atmegax8 ATmega48A/PA/88A/PA/168A/PA/328/P
 * @section atmegax8_device Defined symbols
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE`		    |The device name passed to the compiler
 * `HW_DEVICE_ATMEGAX8`	    |Defined void.
 * `HW_DEVICE_ATMEGA48`<br>...<br>`HW_DEVICE_ATMEGA328P_AU` | Defined void depending on the HWA header included.
 * `HW_DEVICE_PACKAGE_32Q`  |Defined void depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte (after registers and I/O regs): `0x0100`.
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table). See below.
 *
 * Symbol		       | ATmega48(P)A | ATmega88(P)A | ATmega168(P)A | ATmega328(P)
 * :---------------------------|:------------:|:------------:|:-------------:|:------------:
 * `HW_DEVICE`		       |	      |		     |		     |atmega328p
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x92,0x05<br>(0x1E,0x92,0x0A)|0x1E,0x93,0x0A<br>(0x1E,0x93,0x0F)|0x1E,0x94,0x06<br>(0x1E,0x94,0x0B)|0x1E,0x95,0x14<br>(0x1E,0x95,0x0F)
 * `HW_DEVICE_FLASH_SIZE`      |4096	      |8192	     |16384	     |32768
 * `HW_DEVICE_FLASH_PAGE_SIZE` |64	      |64	     |128	     |128
 * `HW_DEVICE_EEPROM_SIZE`     |256	      |512	     |512	     |1024
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4	      |4	     |4		     |4
 * `HW_DEVICE_RAM_SIZE`	       |512	      |1024	     |1024	     |2048
 * `HW_DEVICE_APP_START`       |0x0034	      |0x0034	     |0x0068	     |0x0068
 */
#define HW_DEVICE_ATMEGAX8


/**
 * @page atmegax8
 * @section atmegax8_fuses Fuses
 *
 * ATmegaX8 devices hold 3 fuse bytes describing their hardware configuration.
 * HWA computes the value of these fuse bytes from the fuse values (detailed in
 * the following subsections) that must be defined prior to including the HWA
 * header. Factory default values (shown with a bold face) are used for
 * undefined fuse values.
 *
 * Symbol		| Comments
 * :--------------------|:-----------
 * `HW_DEVICE_FUSE_EB`	| Fuse extended byte
 * `HW_DEVICE_FUSE_HB`	| Fuse high byte
 * `HW_DEVICE_FUSE_LB`	| Fuse low byte
 */


/*	Fuse bytes are defined in device-specific header	*/


/**
 * @page atmegax8
 * @subsection atmegax8_fuses_clocking Clocking
 *
 * HWA uses these settings to compute the system clock frequency `syshz`.
 *
 * Symbol		 | Valid values | Comments
 * :---------------------|--------------|:-----------
 * `HW_DEVICE_CLK_SRC`	 | `external`<br>`rc_128kHz`<br><b>`rc_8MHz`</b><br>`low_freq_xosc`<br>`low_power_xosc`<br>`full_swing_xosc`|External source on pin CLKI<br>Internal RC oscillator (watchdog)<br>Internal RC calibrated oscillator<br>Crystal/resonator oscillator between pins XTAL1 and XTAL2<br> <br> <br>
 * `HW_DEVICE_CLK_SRC_HZ`| Positive integer |Clock frequency for `external` and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`	 | <b>`8`</b><br>`1`|Clock divided by 8<br>Clock not divided
 */
#define _hw_is_rc_8MHz_rc_8MHz			, 1
#define _hw_is_rc_128kHz_rc_128kHz		, 1
#define _hw_is_low_freq_xosc_low_freq_xosc	, 1
#define _hw_is_low_power_xosc_low_power_xosc	, 1
#define _hw_is_full_swing_xosc_full_swing_xosc	, 1

/*  Define default HW_DEVICE_CLK_SRC_HZ as void so that hw_syshz_base can be checked
 */
#ifndef HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_CLK_SRC_HZ
#endif

#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				rc_8MHz
#endif

#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31			0
#  define HW_DEVICE_FUSE_CKSEL0				0
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31			1
#  define HW_DEVICE_FUSE_CKSEL0				0
#  define hw_syshz_base					8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_FUSE_CKSEL31			1
#  define HW_DEVICE_FUSE_CKSEL0				1
#  define hw_syshz_base					128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_FUSE_CKSEL31			2
#
#elif HW_IS(HW_DEVICE_CLK_SRC, low_power_xosc)
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_FUSE_CKSEL31			4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_FUSE_CKSEL31			5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_FUSE_CKSEL31			6
#  else
#    define HW_DEVICE_FUSE_CKSEL31			7
#  endif
#elif HW_IS(HW_DEVICE_CLK_SRC, full_swing_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#    define HW_DEVICE_FUSE_CKSEL31				3
#  endif
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
HW_E_AVL('HW_DEVICE_CLK_PSC', HW_DEVICE_CLK_PSC, 1 | 8)
#endif


/**
 * @page atmegax8
 * @subsection atmegax8_fuses_sut Startup delays
 *
 * Symbol		| Valid values | Comments
 * :--------------------|--------------|:-----------
 * `HW_DEVICE_STARTUP_DELAYS`|`4CK`<br>`4CK_4ms`<br>`4CK_64ms`<br>`6CK_14CK`<br>`6CK_14CK_4ms`<br>`6CK_14CK_64ms`<br>`1KCK_4ms`<br>`1KCK_64ms`<br>`32KCK_64ms`<br>`258CK_14CK_4ms`<br>`258CK_14CK_64ms`<br>`1KCK_14CK`<br>`1KCK_14CK_4ms`<br>`1KCK_14CK_64ms`<br>`16KCK_14CK`<br>`16KCK_14CK_4ms`<br>`16KCK_14CK_64ms`| Valid values depend on the clocking configuration
*/
#define _hw_is_4CK_4CK					, 1
#define _hw_is_4CK_4ms_4CK_4ms				, 1
#define _hw_is_4CK_64ms_4CK_64ms			, 1
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

/*	SUT
 */
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
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif
#  elif HW_DEVICE_FUSE_CKSEL31 == 2
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK)
#      define HW_DEVICE_FUSE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_4ms)
#      define HW_DEVICE_FUSE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_64ms)
#      define HW_DEVICE_FUSE_SUT10				2
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `4CK`, `4CK_4ms`, or `4CK_64ms`.
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
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `258CK_14CK_4ms`, `258CK_14CK_64ms`, `1KCK_14CK`, `1KCK_14CK_4ms`, `1KCK_14CK_64ms`, `16KCK_14CK`, `16KCK_14CK_4ms`, or `16KCK_14CK_64ms`.
#    endif
#  endif
#else
#  define HW_DEVICE_FUSE_SUT10				2
#endif


/**
 * @page atmegax8
 * @subsection atmegax8_fuses_other Other fuses
 *
 * Symbol		  | Valid values | Comments
 * :----------------------|--------------|:-----------
 * `HW_DEVICE_EXTERNAL_RESET`	 |<b>`enabled`</b><br>`disabled`|Whether the device can be reset via its RESET pin
 * `HW_DEVICE_SELF_PROGRAMMING`	 |<b>`enabled`</b><br>`disabled`|Whether the device can write into its Flash program memory
 * `HW_DEVICE_SERIAL_PROGRAMMING`|<b>`enabled`</b><br>`disabled`|Whether the device can be programmed via the SPI
 * `HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE`|`enabled`<br><b>`disabled`</b>|Whether the EEPROM memory is erased when a chip erase occurs
 * `HW_DEVICE_DEBUG_WIRE`	 |`enabled`<br><b>`disabled`</b>|Whether the Debug Wire is operationnal
 * `HW_DEVICE_WATCHDOG_ALWAYS_ON`|`yes`<br><b>`no`</b>		|Whether the watchdog is always running
 * `HW_DEVICE_CLOCK_OUTPUT`	 |`enabled`<br><b>`disabled`</b>|Whether the device outputs its clock
 * `HW_DEVICE_BROWNOUT_DETECTION`|<b>`off`</b><br>`1700_2000mV`<br>`2500_2900mV`<br>`4100_4500mV`|Brown-out detection level
 * `HW_DEVICE_BOOT`|<b>`application`</b><br>`bootloader`|Whether the device starts the application or the bootloader after reset
 * `HW_DEVICE_BOOTSECTION_SIZE`|`512`<br>`1024`<br>`2048`<br><b>`4096`</b>|Size of the boot section
 */

#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT			disabled
#endif
#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_FUSE_CKOUT				0
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_FUSE_CKOUT				1
#else
#  error HW_DEVICE_CLOCK_OUTPUT must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_EXTERNAL_RESET
#  define HW_DEVICE_EXTERNAL_RESET			enabled
#endif
#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_FUSE_RSTDISBL			1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_FUSE_RSTDISBL			0
#else
#  error HW_DEVICE_EXTERNAL_RESET must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_DEBUG_WIRE
#  define HW_DEVICE_DEBUG_WIRE				disabled
#endif
#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_FUSE_DWEN				0
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_FUSE_DWEN				1
#else
#  error HW_DEVICE_DEBUG_WIRE must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_SERIAL_PROGRAMMING
#  define HW_DEVICE_SERIAL_PROGRAMMING			enabled
#endif
#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_FUSE_SPIEN				0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_FUSE_SPIEN				1
#else
#  error HW_DEVICE_SERIAL_PROGRAMMING must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON			no
#endif
#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_FUSE_WDTON				0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_FUSE_WDTON				1
#else
#  error HW_DEVICE_WATCHDOG_ALWAYS_ON must be defined as `yes` or `no` (default).
#endif

#if !defined HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE	no
#endif
#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE, yes)
#  define HW_DEVICE_FUSE_EESAVE				0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE, no)
#  define HW_DEVICE_FUSE_EESAVE				1
#else
#  error HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE must be defined as `yes` or `no` (default).
#endif

#define _hw_is_1700_2000mV_1700_2000mV			, 1
#define _hw_is_2500_2900mV_2500_2900mV			, 1
#define _hw_is_4100_4500mV_4100_4500mV			, 1

#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION			off
#endif
#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_FUSE_BODLEVEL			7
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_FUSE_BODLEVEL			6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_FUSE_BODLEVEL			5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_FUSE_BODLEVEL			4
#else
#  error HW_DEVICE_BROWNOUT_DETECTION must be defined as `1700_2000mV`, `2500_2900mV`, `4100_4500mV` or `off` (default).
#endif

#define _hw_is_application_application	, 1
#define _hw_is_bootloader_bootloader	, 1

/**
 * @def HW_DEVICE_BOOT
 * @brief Whether the device starts the bootloader (in the boot Flash) or the application.
 * @hideinitializer
 */
#if !defined HW_DEVICE_BOOT
#  define HW_DEVICE_BOOT				application
#endif
#if HW_IS(HW_DEVICE_BOOT, application)
#  define HW_DEVICE_FUSE_BOOTRST			1
#elif HW_IS(HW_DEVICE_BOOT, bootloader)
#  define HW_DEVICE_FUSE_BOOTRST			0
#else
#  error HW_DEVICE_BOOT must be defined as `bootloader` or `application` (default).
#endif


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @section atmegax8_object Peripherals
 *
 * __Note__ All the peripherals are not completely implemented yet.
 *
 * Object name		  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `core0`	 | @ref atmelavr_coreb "_coreb" | The core
 * `int0`	 | @ref atmelavr_inta "_inta"	| External interrupt INT0
 * `int1`	 | @ref atmelavr_inta "_inta"	| External interrupt INT1
 * `port0`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port B (PORT0)
 * `port1`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port C (PORT1)
 * `port2`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port D (PORT2)
 * `pcic0`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `pcic1`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `pcic2`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `watchdog0`	 | @ref atmelavr_wdogb "_wdogb" | Watchdog (WDG)
 * `counter0` | @ref atmelavr_c8a "_c8a"	| 8-bit counter-timer (T0)
 * `counter0compare0`	 | @ref atmelavr_cmp8a "_cmp8a"	| Compare unit 0 of counter0 (OC0A)
 * `counter0compare1`	 | @ref atmelavr_cmp8a "_cmp8a"	| Compare unit 1 of counter0 (OC0B)
 * `counter1` | @ref atmelavr_c16a "_c16a"	| 16-bit counter-timer (T1)
 * `counter1compare0`	 | @ref atmelavr_cmp16a "_cmp16a"	| Compare unit 0 of counter1 (OC1A)
 * `counter1compare1`	 | @ref atmelavr_cmp16a "_cmp16a"	| Compare unit 1 of counter1 (OC1B)
 * `counter1capture0`	 | @ref atmelavr_cap16a "_cap16a"	| Capture unit 0 of counter1 (ICP1)
 * `counter2` | @ref atmelavr_c8c "_c8c"	| 8-bit counter-timer (T2)
 * `counter2compare0`	 | @ref atmelavr_cmp8a "_cmp8a"	| Compare unit 0 of counter2 (OC2A)
 * `counter2compare1`	 | @ref atmelavr_cmp8a "_cmp8a"	| Compare unit 1 of counter2 (OC2B)
 * `prescaler0`	 | @ref atmelavr_psca "_psca"	| counter0/counter1 prescaler (PSC0)
 * `spi0`	 | @ref atmelavr_spia "_spia"	| Serial Peripheral Interface
 * `uart0`	 | @ref atmelavr_uarta "_uarta" | Universal Asynchronous Receiver Transmitter
 * `twi0`	 | @ref atmelavr_twia "_twia"	| 2-wire Serial Interface
 * `acmp0`	 | @ref atmelavr_acmpa "_acmpa"	| Analog Comparator
 * `adc0`	 | @ref atmelavr_ad10b "_ad10b"	| 10-bit Analog to Digital Converter
 * `eeprom0`	 | @ref atmelavr_eeproma "_eeproma" | Eeprom memory
 * `flash0`	 | @ref atmelavr_flasha "_flasha"   | Flash memory
 *
 * @subsection atmegax8_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name			  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `spimaster_swclk0`  | @ref atmelavr_usia_spimaster_swclk "_usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `swuart0`		  | @ref atmelavr_swuarta "_swuarta" | Software UART
 * `swuart1`		  | @ref atmelavr_swuarta "_swuarta" | Software UART
 *
 * @subsection atmegax8_objrel Aliases and relations
 *
 * Some objects can be accessed from their relatives or can have more than one
 * name. There are the existing relations between the device's objects and their
 * different names:
 *
 * Name		 | Aliases		 | Relations
 * :-------------|-----------------------|:--------------------------------------
 * `prescaler0`	 | `counter0prescaler`	| `HW_RELATIVE(counter0, prescaler)`
 * `prescaler0`	 | `counter0prescaler0` | `HW_RELATIVE(counter0, prescaler0)`
 * `prescaler0`	 | `counter1prescaler`	| `HW_RELATIVE(counter1, prescaler)`
 * `prescaler0`	 | `counter1prescaler0` | `HW_RELATIVE(counter1, prescaler0)`
 * `counter0compare0`	 | `counter0compare0`	| `HW_RELATIVE(counter0, compare0)`
 * `counter0compare1`	 | `counter0compare1`	| `HW_RELATIVE(counter0, compare1)`
 * `counter0` | `counter0compare0counter`	   | `HW_RELATIVE(counter0compare0, counter)`
 * `counter0` | `counter0compare1counter`	   | `HW_RELATIVE(counter0compare1, counter)`
 * `pin_counter0compare0` | `counter0compare0pin`		   | `HW_RELATIVE(counter0compare0, pin)`
 * `pin_counter0compare1` | `counter0compare1pin`		   | `HW_RELATIVE(counter0compare1, pin)`
 * `counter1compare0`	 | `counter1compare0`	| `HW_RELATIVE(counter1, compare0)`
 * `counter1compare1`	 | `counter1compare1`	| `HW_RELATIVE(counter1, compare1)`
 * `counter1` | `counter1compare0counter`	   | `HW_RELATIVE(counter1compare0, counter)`
 * `counter1` | `counter1compare1counter`	   | `HW_RELATIVE(counter1compare1, counter)`
 * `pin_counter1compare0` | `counter1compare0pin`		   | `HW_RELATIVE(counter1compare0, pin)`
 * `pin_counter1compare1` | `counter1compare1pin`		   | `HW_RELATIVE(counter1compare1, pin)`
 * `pin_counter1capture0` | `counter1capture0pin`		   | `HW_RELATIVE(counter1capture0, pin)`
 * `counter2` | `counter2compare0counter`	   | `HW_RELATIVE(counter2compare0, counter)`
 * `counter2` | `counter2compare1counter`	   | `HW_RELATIVE(counter2compare1, counter)`
 * `pin_counter2compare0` | `counter2compare0pin`		   | `HW_RELATIVE(counter2compare0, pin)`
 * `pin_counter2compare1` | `counter2compare1pin`		   | `HW_RELATIVE(counter2compare1, pin)`
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

/**
 * @page atmegax8
 * @section atmegax8_interrupts Interrupts
 * 
 * Interrupt definition			   | Atmel label  | Comments
 * :---------------------------------------|--------------|------------------------
 * `int0`				   | INT0	  | External Interrupt Request 0
 * `int1`				   | INT1	  | External Interrupt Request 1
 * `pcic0`				   | PCINT0	  | Pin Change Interrupt Request 0
 * `pcic1`				   | PCINT1	  | Pin Change Interrupt Request 1
 * `pcic2`				   | PCINT2	  | Pin Change Interrupt Request 2
 * `watchdog0`				   | WDT	  | Watchdog Time-out Interrupt
 * `counter2compare0`<br>`counter2,compare0`	   | TIMER2 COMPA | Timer/Counter2 Compare Match A
 * `counter2compare1`<br>`counter2,compare1`	   | TIMER2 COMPB | Timer/Counter2 Compare Match B
 * `counter2`<br>`counter2,overflow` | TIMER2 OVF	  | Timer/Counter2 Overflow
 * `counter1capture0`<br>`counter1,capture0`	   | TIMER1 CAPT  | Timer/Counter1 Capture Event
 * `counter1compare0`<br>`counter1,compare0`	   | TIMER1 COMPA | Timer/Counter1 Compare Match A
 * `counter1compare1`<br>`counter1,compare1`	   | TIMER1 COMPB | Timer/Coutner1 Compare Match B
 * `counter1`<br>`counter1,overflow` | TIMER1 OVF	  | Timer/Counter1 Overflow
 * `counter0compare0`<br>`counter0,compare0`	   | TIMER0 COMPA | Timer/Counter0 Compare Match A
 * `counter0compare1`<br>`counter0,compare1`	   | TIMER0 COMPB | Timer/Counter0 Compare Match B
 * `counter0`<br>`counter0,overflow` | TIMER0 OVF	  | Timer/Counter0 Overflow
 * `spi0`				   | SPI,STC	  | SPI Serial Transfer Complete
 * `uart0,rxc`			   | USART,RXC	  | USART Rx Complete
 * `uart0,txqne`			   | USART,UDRE	  | USART, Data Register Empty
 * `uart0,txc`			   | USART,TXC	  | USART, Tx Complete
 * `adc0`				   | ADC	  | ADC conversion complete
 * `eeprom0`				   | EE READY	  | EEPROM ready
 * `eeprom0,ready`			   | EE READY	  | EEPROM ready
 * `acmp0`				   | ANALOG COMP  | Analog comparator
 * `twi0`				   | TWI	  | 2-wire Serial Interface
 * `flash0`				   | SPM READY	  | Store Program Memory Ready
 */
/**
 * @ingroup atmegax8_interrupts
 * @brief Definition of the interrupts
 */
#define _hw_irq_int0_			_irq, int0,	 1, ie,	 if
#define _hw_irq_int1_			_irq, int1,	 2, ie,	 if
#define _hw_irq_pcic0_			_irq, pcic0,	 3, ie,	 if
#define _hw_irq_pcic1_			_irq, pcic1,	 4, ie,	 if
#define _hw_irq_pcic2_			_irq, pcic2,	 5, ie,	 if
#define _hw_irq_watchdog0_		_irq, watchdog0,	 6, ie,	 if
							   
#define _hw_irq_counter2_compare0	_irq, counter2compare0,	 7, ie,	 if
#define _hw_irq_counter2compare0_	_irq, counter2compare0,	 7, ie,	 if
#define _hw_irq_counter2_compare1	_irq, counter2compare1,	 8, ie,	 if
#define _hw_irq_counter2compare1_	_irq, counter2compare1,	 8, ie,	 if
#define _hw_irq_counter2_overflow	_irq, counter2,	 9, ie,	 if
#define _hw_irq_counter2		_irq, counter2,	 9, ie,	 if
							   
#define _hw_irq_counter1_capture0	_irq, counter1capture0,	10, ie,	 if
#define _hw_irq_counter1capture0_	_irq, counter1capture0,	10, ie,	 if
#define _hw_irq_counter1_compare0	_irq, counter1compare0,	11, ie,	 if
#define _hw_irq_counter1compare0_	_irq, counter1compare0,	11, ie,	 if
#define _hw_irq_counter1_compare1	_irq, counter1compare1,	12, ie,	 if
#define _hw_irq_counter1compare1_	_irq, counter1compare1,	12, ie,	 if
#define _hw_irq_counter1_overflow	_irq, counter1, 13, ie,	 if
#define _hw_irq_counter1_		_irq, counter1, 13, ie,	 if
							   
#define _hw_irq_counter0_compare0	_irq, counter0compare0,	14, ie,	 if
#define _hw_irq_counter0compare0_	_irq, counter0compare0,	14, ie,	 if
#define _hw_irq_counter0_compare1	_irq, counter0compare1,	15, ie,	 if
#define _hw_irq_counter0compare1_	_irq, counter0compare1,	15, ie,	 if
#define _hw_irq_counter0_overflow	_irq, counter0, 16, ie,	 if
#define _hw_irq_counter0_		_irq, counter0, 16, ie,	 if
							   
#define _hw_irq_spi0_			_irq, spi0,	17, ie,	 if
#define _hw_irq_spi0_txc		_irq, spi0,	17, ie,	 if
							   
#define _hw_irq_uart0_rxc		_irq, uart0,	18, ierxc,  ifrxc
#define _hw_irq_uart0_txqnf		_irq, uart0,	19, ietxqe, iftxqnf
#define _hw_irq_uart0_txc		_irq, uart0,	20, ietxc,  iftxc
							   
#define _hw_irq_adc0_			_irq, adc0,	21, ie,	   if
							   
#define _hw_irq_eeprom0			_irq, eeprom0,	22, ie, /* no irq flag */
#define _hw_irq_eeprom0_ready		_irq, eeprom0,	22, ie,
							   
#define _hw_irq_acmp0_			_irq, acmp0,	23, ie, if
							   
#define _hw_irq_twi0_			_irq, twi0,	24, ie, if
							   
#define _hw_irq_flash0_			_irq, flash0,	25, ie, if


/**
 * @page atmegax8
 * @section atmegax8_pm Power Management
 *
 * The following peripherals can be powered on/off using the `power`
 * instruction:
 *
 *  * `twi0`
 *  * `counter0`
 *  * `counter1`
 *  * `counter2`
 *  * `spi0`
 *  * `uart0`
 *  * `adc0`
 *
 * @code
 * hw( power, counter0, on );
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_class__shared
#define _hw_def_shared			_shared, 101, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_shared_did1		_r8, 0x7F, 0x03, 0x00	/* DID for AIN0/AIN1 */
#define _hw_reg_shared_did0		_r8, 0x7E, 0x3F, 0x00	/* DID for PORT1 */
#define _hw_reg_shared_eicr		_r8, 0x69, 0x0F, 0x00
#define _hw_reg_shared_pcicr		_r8, 0x68, 0x07, 0x00
#define _hw_reg_shared_prr		_r8, 0x64, 0xEF, 0x00
#define _hw_reg_shared_gpior2		_r8, 0x4B, 0xFF, 0x00
#define _hw_reg_shared_gpior1		_r8, 0x4A, 0xFF, 0x00
#define _hw_reg_shared_gtccr		_r8, 0x43, 0x83, 0x00
#define _hw_reg_shared_gpior0		_r8, 0x3E, 0xFF, 0x00
#define _hw_reg_shared_eimsk		_r8, 0x3D, 0x03, 0x00
#define _hw_reg_shared_eifr		_r8, 0x3C, 0x03, 0x03
#define _hw_reg_shared_pcifr		_r8, 0x3B, 0x07, 0x07

#if !defined __ASSEMBLER__
/*
 *  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	eimsk ;
  hwa_r8_t	eicr ;
  hwa_r8_t	eifr ;
  hwa_r8_t	gtccr ;
  hwa_r8_t	prr ;
  hwa_r8_t	did1 ;
  hwa_r8_t	did0 ;
  hwa_r8_t	pcicr ;
  hwa_r8_t	pcifr ;
} hwa_shared_t ;
#endif


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page atmegax8
 * @section atmegax8_pins Ports and pins
 *
 * Some of the pins may not be available depending on the fuses configuration.
 *
 * HWA name	| 32qfp/mlf   | Class			   | Atmel name
 * -------------|-------------|----------------------------|-----------
 * `portb`	|	      | @ref atmelavr_io1a "_io1a" | PORTB
 * `pb0` | `HW_PIN(12)` | @ref atmelavr_io1a "_io1a" | PB0
 * `pb1` | `HW_PIN(13)` | @ref atmelavr_io1a "_io1a" | PB1
 * `pb2` | `HW_PIN(14)` | @ref atmelavr_io1a "_io1a" | PB2
 * `pb3` | `HW_PIN(15)` | @ref atmelavr_io1a "_io1a" | PB3
 * `pb4` | `HW_PIN(16)` | @ref atmelavr_io1a "_io1a" | PB4
 * `pb5` | `HW_PIN(17)` | @ref atmelavr_io1a "_io1a" | PB5
 * `pb6` | `HW_PIN(7)`	| @ref atmelavr_io1a "_io1a" | PB6
 * `pb7` | `HW_PIN(8)`	| @ref atmelavr_io1a "_io1a" | PB7
 * `portc`	|	      | @ref atmelavr_io1a "_io1a" | PORTC
 * `pc0` | `HW_PIN(23)` | @ref atmelavr_io1a "_io1a" | PC0
 * `pc1` | `HW_PIN(24)` | @ref atmelavr_io1a "_io1a" | PC1
 * `pc2` | `HW_PIN(25)` | @ref atmelavr_io1a "_io1a" | PC2
 * `pc3` | `HW_PIN(26)` | @ref atmelavr_io1a "_io1a" | PC3
 * `pc4` | `HW_PIN(27)` | @ref atmelavr_io1a "_io1a" | PC4
 * `pc5` | `HW_PIN(28)` | @ref atmelavr_io1a "_io1a" | PC5
 * `pc6` | `HW_PIN(29)` | @ref atmelavr_io1a "_io1a" | PC6
 * `portd`	|	      | @ref atmelavr_io1a "_io1a" | PORTD
 * `pd0` | `HW_PIN(30)` | @ref atmelavr_io1a "_io1a" | PD0
 * `pd1` | `HW_PIN(31)` | @ref atmelavr_io1a "_io1a" | PD1
 * `pd2` | `HW_PIN(32)` | @ref atmelavr_io1a "_io1a" | PD2
 * `pd3` | `HW_PIN(1)`	| @ref atmelavr_io1a "_io1a" | PD3
 * `pd4` | `HW_PIN(2)`	| @ref atmelavr_io1a "_io1a" | PD4
 * `pd5` | `HW_PIN(9)`	| @ref atmelavr_io1a "_io1a" | PD5
 * `pd6` | `HW_PIN(10)` | @ref atmelavr_io1a "_io1a" | PD6
 * `pd7` | `HW_PIN(11)` | @ref atmelavr_io1a "_io1a" | PD7
 */

/*	Objects				class, id, address
 */
#include "../classes/p8a_1.h"
#include "../classes/io1a_1.h"

#define _hw_def_port0			_p8a, 102, 0x23
#define _hw_def_port1			_p8a, 103, 0x26
#define _hw_def_port2			_p8a, 104, 0x29

/*  Pins				class, id, port, bn, bp
 */
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)
#  define _hw_def_pb0		_io1a, 105, port0, 1, 0
#endif
#define _hw_def_pb1			_io1a, 105, port0, 1, 1
#define _hw_def_pb2			_io1a, 106, port0, 1, 2
#define _hw_def_pb3			_io1a, 107, port0, 1, 3
#define _hw_def_pb4			_io1a, 108, port0, 1, 4
#define _hw_def_pb5			_io1a, 109, port0, 1, 5

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_def_pb6		_io1a, 111, port0, 1, 6
#endif
#if !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_def_pb7		_io1a, 112, port0, 1, 7
#endif
#define _hw_def_portb			_io1a, 110, port0, 8, 0

#define _hw_def_pc0			_io1a, 111, port1, 1, 0
#define _hw_def_pc1			_io1a, 112, port1, 1, 1
#define _hw_def_pc2			_io1a, 113, port1, 1, 2
#define _hw_def_pc3			_io1a, 114, port1, 1, 3
#define _hw_def_pc4			_io1a, 115, port1, 1, 4
#define _hw_def_pc5			_io1a, 116, port1, 1, 5
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)
#  define _hw_def_pc6		_io1a, 120, port1, 1, 6
#endif
#define _hw_def_portc			_io1a, 117, port1, 7, 0

#define _hw_def_pd0			_io1a, 118, port2, 1, 0
#define _hw_def_pd1			_io1a, 119, port2, 1, 1
#define _hw_def_pd2			_io1a, 120, port2, 1, 2
#define _hw_def_pd3			_io1a, 121, port2, 1, 3
#define _hw_def_pd4			_io1a, 122, port2, 1, 4
#define _hw_def_pd5			_io1a, 123, port2, 1, 5
#define _hw_def_pd6			_io1a, 124, port2, 1, 6
#define _hw_def_pd7			_io1a, 125, port2, 1, 7
#define _hw_def_portd			_io1a, 126, port2, 8, 0

#define _hw_def_pin_adc6		_io1a, 336
#define _hw_def_pin_adc7		_io1a, 337

/*  Digital input disable bits for analog input pins
 */
#define _hw_reg_pc0_did		_xob1, shared, did0, 1, 0	/* ADC0 */
#define _hw_reg_pc1_did		_xob1, shared, did0, 1, 1	/* ADC1 */
#define _hw_reg_pc2_did		_xob1, shared, did0, 1, 2	/* ADC2 */
#define _hw_reg_pc3_did		_xob1, shared, did0, 1, 3	/* ADC3 */
#define _hw_reg_pc4_did		_xob1, shared, did0, 1, 4	/* ADC4 */
#define _hw_reg_pc5_did		_xob1, shared, did0, 1, 5	/* ADC5 */

#define _hw_reg_pd6_did		_xob1, shared, did1, 1, 0	/* AIN0 */
#define _hw_reg_pd7_did		_xob1, shared, did1, 1, 1	/* AIN1 */

/*  Relative pin change controllers
 */
#define _hw_rel_pb0_pcic		pcic0
#define _hw_rel_pb1_pcic		pcic0
#define _hw_rel_pb2_pcic		pcic0
#define _hw_rel_pb3_pcic		pcic0
#define _hw_rel_pb4_pcic		pcic0
#define _hw_rel_pb5_pcic		pcic0
#define _hw_rel_pb6_pcic		pcic0
#define _hw_rel_pb7_pcic		pcic0

#define _hw_rel_pc0_pcic		pcic1
#define _hw_rel_pc1_pcic		pcic1
#define _hw_rel_pc2_pcic		pcic1
#define _hw_rel_pc3_pcic		pcic1
#define _hw_rel_pc4_pcic		pcic1
#define _hw_rel_pc5_pcic		pcic1
#define _hw_rel_pc6_pcic		pcic1

#define _hw_rel_pd0_pcic		pcic2
#define _hw_rel_pd1_pcic		pcic2
#define _hw_rel_pd2_pcic		pcic2
#define _hw_rel_pd3_pcic		pcic2
#define _hw_rel_pd4_pcic		pcic2
#define _hw_rel_pd5_pcic		pcic2
#define _hw_rel_pd6_pcic		pcic2
#define _hw_rel_pd7_pcic		pcic2

/*  Canonical pin names
 */
#define _hw_pin_sck			, pb5
#define _hw_pin_miso			, pb4
#define _hw_pin_mosi			, pb3
#define _hw_pin_ss			, pb2

#define _hw_pin_counter0compare0	, pd6
#define _hw_pin_counter0compare1	, pd5
#define _hw_pin_counter1compare0	, pb1
#define _hw_pin_counter1compare1	, pb2
#define _hw_pin_counter1capture0	, pb0
#define _hw_pin_counter2compare0	, pb3
#define _hw_pin_counter2compare1	, pd3

#define _hw_pin_adc0			, pc0
#define _hw_pin_adc1			, pc1
#define _hw_pin_adc2			, pc2
#define _hw_pin_adc3			, pc3
#define _hw_pin_adc4			, pc4
#define _hw_pin_adc5			, pc5
#define _hw_pin_adc6			, pin_adc6
#define _hw_pin_adc7			, pin_adc7

#define _hw_pin_ain1			, pd7
#define _hw_pin_ain0			, pd6

#define _hw_pin_scl			, pc5
#define _hw_pin_sda			, pc4

#define _hw_pin_txd			, pd1
#define _hw_pin_rxd			, pd0

#if defined HW_DEVICE_PACKAGE_28P
#
#  define _hw_pin_1			, pc6
#  define _hw_pin_2			, pd0
#  define _hw_pin_3			, pd1
#  define _hw_pin_4			, pd2
#  define _hw_pin_5			, pd3
#  define _hw_pin_6			, pd4
#  define _hw_pin_9			, pb6
#  define _hw_pin_10			, pb7
#  define _hw_pin_11			, pd5
#  define _hw_pin_12			, pd6
#  define _hw_pin_13			, pd7
#  define _hw_pin_14			, pb0
#  define _hw_pin_15			, pb1
#  define _hw_pin_16			, pb2
#  define _hw_pin_17			, pb3
#  define _hw_pin_18			, pb4
#  define _hw_pin_19			, pb5
#  define _hw_pin_23			, pc0
#  define _hw_pin_24			, pc1
#  define _hw_pin_25			, pc2
#  define _hw_pin_26			, pc3
#  define _hw_pin_27			, pc4
#  define _hw_pin_28			, pc5
#
#elif defined HW_DEVICE_PACKAGE_28Q
#
#  define _hw_pin_1			, pd3
#  define _hw_pin_2			, pd4
/* #  define _hw_pin_3			, pin_ */
/* #  define _hw_pin_4			, pin_ */
#  define _hw_pin_5			, pb6
#  define _hw_pin_6			, pb7
#  define _hw_pin_7			, pd5
#  define _hw_pin_8			, pd6
#  define _hw_pin_9			, pd7
#  define _hw_pin_10			, pb0
#  define _hw_pin_11			, pb1
#  define _hw_pin_12			, pb2
#  define _hw_pin_13			, pb3
#  define _hw_pin_14			, pb4
#  define _hw_pin_15			, pb5
/* #  define _hw_pin_16			, pin_ */
/* #  define _hw_pin_17			, pin_ */
/* #  define _hw_pin_18			, pin_ */
#  define _hw_pin_19			, pc0
#  define _hw_pin_20			, pc1
#  define _hw_pin_21			, pc2
#  define _hw_pin_22			, pc3
#  define _hw_pin_23			, pc4
#  define _hw_pin_24			, pc5
#  define _hw_pin_25			, pc6
#  define _hw_pin_26			, pd0
#  define _hw_pin_27			, pd1
#  define _hw_pin_28			, pd2
#
#elif defined HW_DEVICE_PACKAGE_32Q
#
#  define _hw_pin_1			, pd3
#  define _hw_pin_2			, pd4
#  define _hw_pin_7			, pb6
#  define _hw_pin_8			, pb7
#  define _hw_pin_9			, pd5
#  define _hw_pin_10			, pd6
#  define _hw_pin_11			, pd7
#  define _hw_pin_12			, pb0
#  define _hw_pin_13			, pb1
#  define _hw_pin_14			, pb2
#  define _hw_pin_15			, pb3
#  define _hw_pin_16			, pb4
#  define _hw_pin_17			, pb5
#  define _hw_pin_19			, pin_adc6
#  define _hw_pin_22			, pin_adc7
#  define _hw_pin_23			, pc0
#  define _hw_pin_24			, pc1
#  define _hw_pin_25			, pc2
#  define _hw_pin_26			, pc3
#  define _hw_pin_27			, pc4
#  define _hw_pin_28			, pc5
#  define _hw_pin_29			, pc6
#  define _hw_pin_30			, pd0
#  define _hw_pin_31			, pd1
#  define _hw_pin_32			, pd2
#
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/coreb_1.h"
#define _hw_def_core0			_coreb, 127, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_core0_osccal		_r8, 0x66, 0xFF, 0x00
#define _hw_reg_core0_sreg		_r8, 0x5F, 0xFF, 0x00
#define _hw_reg_core0_sph		_r8, 0x5E, 0x03, 0x00
#define _hw_reg_core0_spl		_r8, 0x5D, 0xFF, 0x00
#define _hw_reg_core0_mcucr		_r8, 0x55, 0x73, 0x00
#define _hw_reg_core0_mcusr		_r8, 0x54, 0x0F, 0x00
#define _hw_reg_core0_smcr		_r8, 0x53, 0x0F, 0x00

/*	Object logical registers
 */
#define _hw_reg_core0_bods		_ob1, mcucr, 1, 6
#define _hw_reg_core0_bodse		_ob1, mcucr, 1, 5
#define _hw_reg_core0_pud		_ob1, mcucr, 1, 4
#define _hw_reg_core0_ivsel		_ob1, mcucr, 1, 1
#define _hw_reg_core0_ivce		_ob1, mcucr, 1, 0

#define _hw_reg_core0_wdrf		_ob1, mcusr, 1, 3
#define _hw_reg_core0_borf		_ob1, mcusr, 1, 2
#define _hw_reg_core0_extrf		_ob1, mcusr, 1, 1
#define _hw_reg_core0_porf		_ob1, mcusr, 1, 0
#define _hw_reg_core0_allrf		_ob1, mcusr, 4, 0	/* convenient */

#define _hw_reg_core0_sm		_ob1, smcr, 3, 1
#define _hw_reg_core0_se		_ob1, smcr, 1, 0


/*******************************************************************************
 *									       *
 *	External interrupt controllers					       *
 *									       *
 *******************************************************************************/

#include "../classes/inta_1.h"

/*	Object				class, id, address
 */
#define _hw_def_int0			_inta, 128, 0

/*	Object logical registers
 */
#define _hw_reg_int0_sc			_xob1, shared, eicr,  2, 0
#define _hw_reg_int0_ie			_xob1, shared, eimsk, 1, 0
#define _hw_reg_int0_if			_xob1, shared, eifr,  1, 0

/*	Object				class, id, address
 */
#define _hw_def_int1			_inta, 129, 0

/*	Object logical registers
 */
#define _hw_reg_int1_sc			_xob1, shared, eicr,  2, 2
#define _hw_reg_int1_ie			_xob1, shared, eimsk, 1, 1
#define _hw_reg_int1_if			_xob1, shared, eifr,  1, 1


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

#include "../classes/pcica_1.h"

/*	Object				class, id, address
 */
#define _hw_def_pcic0			_pcica, 130, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_pcic0_msk		_r8, 0x6B, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_reg_pcic0_ie		_xob1, shared, pcicr, 1, 0
#define _hw_reg_pcic0_if		_xob1, shared, pcifr, 1, 0

/*	Object				class, id, address
 */
#define _hw_def_pcic1			_pcica, 131, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_pcic1_msk		_r8, 0x6C, 0x7F, 0x00

/*	Object logical registers
 */
#define _hw_reg_pcic1_ie		_xob1, shared, pcicr, 1, 1
#define _hw_reg_pcic1_if		_xob1, shared, pcifr, 1, 1

/*	Object				class, id, address
 */
#define _hw_def_pcic2			_pcica, 132, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_pcic2_msk		_r8, 0x6D, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_reg_pcic2_ie		_xob1, shared, pcicr, 1, 2
#define _hw_reg_pcic2_if		_xob1, shared, pcifr, 1, 2


/*******************************************************************************
 *									       *
 *	hw_watchdog0: watchdog						       *
 *									       *
 *******************************************************************************/

#include "../classes/wdogb_1.h"

/*	Object				class, id, address
 */
#define _hw_def_watchdog0		_wdogb, 133, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg__wdogb_csr		_r8, 0x60, 0xFF, 0x80

/*	Class logical registers
 */
#define _hw_reg__wdogb_wdrf		_xob1, core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0/1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psca_1.h"

/*	Object				class, id, address
 */
#define _hw_def_prescaler0		_psca, 134, 0

/*	Object logical registers
 */
#define _hw_reg_prescaler0_tsm		_xob1, shared, gtccr, 1, 7
#define _hw_reg_prescaler0_psr		_xob1, shared, gtccr, 1, 0

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define _hw_reg_prescaler0_tsmpsr	_xob2, shared, gtccr, 1, 7, 1, gtccr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	Counter 0 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c8a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_counter0		_c8a, 135, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter0_ccra		_r8, 0x44, 0xF3, 0x00
#define _hw_reg_counter0_ccrb		_r8, 0x45, 0xCF, 0x00
#define _hw_reg_counter0_count		_r8, 0x46, 0xFF, 0x00
#define _hw_reg_counter0_imsk		_r8, 0x6E, 0x07, 0x00
#define _hw_reg_counter0_ifr		_r8, 0x35, 0x07, 0x07

/*	Object logical registers
 */
#define _hw_reg_counter0_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_reg_counter0_cs		_ob1, ccrb, 3, 0
#define _hw_reg_counter0_ie		_ob1, imsk, 1, 0
#define _hw_reg_counter0_if		_ob1, ifr, 1, 0
#define _hw_reg_counter0_prr		_xob1, shared, prr, 1, 5


/*	Relatives
 */
#define _hw_rel_counter0_prescaler0	prescaler0
#define _hw_rel_counter0_prescaler	prescaler0
#define _hw_rel_counter0_compare0	counter0compare0
#define _hw_rel_counter0_compare1	counter0compare1


/*******************************************************************************
 *									       *
 *	Counter 0 compare units counter0compare0, counter0compare1 (OCR0A, OCR0B)		       *
 *									       *
 *******************************************************************************/

#include "../classes/cmp8a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_counter0compare0	_cmp8a, 136, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter0compare0_reg	_r8, 0x47, 0xFF, 0x00	/* OCR0A */

/*	Object logical registers
 */
#define _hw_reg_counter0compare0_com	_xob1, counter0, ccra, 2, 6
#define _hw_reg_counter0compare0_force	_xob1, counter0, ccrb, 1, 7
#define _hw_reg_counter0compare0_ie	_xob1, counter0, imsk, 1, 1
#define _hw_reg_counter0compare0_if	_xob1, counter0, ifr,  1, 1

/*	Relatives
 */
#define _hw_rel_counter0compare0_pin	pd6
#define _hw_rel_counter0compare0_counter	counter0


/*	Object				class, id, address
 */
#define _hw_def_counter0compare1	_cmp8a, 137, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter0compare1_reg	_r8, 0x48, 0xFF, 0x00	/* OCR0B */

/*	Object logical registers
 */
#define _hw_reg_counter0compare1_com	_xob1, counter0, ccra, 2, 4
#define _hw_reg_counter0compare1_force	_xob1, counter0, ccrb, 1, 6
#define _hw_reg_counter0compare1_ie	_xob1, counter0, imsk, 1, 2
#define _hw_reg_counter0compare1_if	_xob1, counter0, ifr,  1, 2

/*	Relatives
 */
#define _hw_rel_counter0compare1_pin	pd5
#define _hw_rel_counter0compare1_counter	counter0


/*******************************************************************************
 *									       *
 *	counter1: counter 1 counting unit				       *
 *									       *
 *******************************************************************************/

#include "../classes/c16a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_counter1		_c16a, 138, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter1_ccra		_r8,  0x80, 0xF3,   0x00
#define _hw_reg_counter1_ccrb		_r8,  0x81, 0xDF,   0x00
#define _hw_reg_counter1_ccrc		_r8,  0x82, 0xC0,   0x00
#define _hw_reg_counter1_count		_r16, 0x84, 0xFFFF, 0x0000
#define _hw_reg_counter1_imsk		_r8,  0x6F, 0x27,   0x00
#define _hw_reg_counter1_ifr		_r8,  0x36, 0x27,   0x27

/*	Object logical registers
 */
#define _hw_reg_counter1_cs		_ob1, ccrb, 3, 0
#define _hw_reg_counter1_wgm		_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define _hw_reg_counter1_ie		_ob1, imsk, 1, 0
#define _hw_reg_counter1_if		_ob1, ifr, 1, 0
#define _hw_reg_counter1_prr		_xob1, shared, prr, 1, 3

/*	Relatives
 */
#define _hw_rel_counter1_prescaler0	prescaler0
#define _hw_rel_counter1_prescaler	prescaler0
#define _hw_rel_counter1_compare0	counter1compare0
#define _hw_rel_counter1_compare1	counter1compare1
#define _hw_rel_counter1_capture0	counter1capture0


/*******************************************************************************
 *									       *
 *	Counter 1 compare units counter1compare0, counter1compare1 (OCR1A, OCR1B)		       *
 *									       *
 *******************************************************************************/

#include "../classes/cmp16a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_counter1compare0	_cmp16a, 139, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter1compare0_reg	_r16, 0x88, 0xFFFF, 0x0000	/* OCR1A */

/*	Object logical registers
 */
#define _hw_reg_counter1compare0_com	_xob1, counter1, ccra, 2, 6
#define _hw_reg_counter1compare0_force	_xob1, counter1, ccrc, 1, 7
#define _hw_reg_counter1compare0_ie	_xob1, counter1, imsk, 1, 1
#define _hw_reg_counter1compare0_if	_xob1, counter1, ifr,  1, 1

/*	Relatives
 */
#define _hw_rel_counter1compare0_pin	pb1
#define _hw_rel_counter1compare0_counter	counter1


/*	Object				class, id, address
 */
#define _hw_def_counter1compare1	_cmp16a, 140, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter1compare1_reg	_r16, 0x8A, 0xFFFF, 0x0000	/* OCR1B */

/*	Object logical registers
 */
#define _hw_reg_counter1compare1_com	_xob1, counter1, ccra, 2, 4
#define _hw_reg_counter1compare1_force	_xob1, counter1, ccrc, 1, 6
#define _hw_reg_counter1compare1_ie	_xob1, counter1, imsk, 1, 2
#define _hw_reg_counter1compare1_if	_xob1, counter1, ifr,  1, 2

/*	Relatives
 */
#define _hw_rel_counter1compare1_pin	pb2
#define _hw_rel_counter1compare1_counter	counter1


/*******************************************************************************
 *									       *
 *	Counter 1 capture unit counter1capture0					       *
 *									       *
 *******************************************************************************/

#include "../classes/cap16a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_counter1capture0	_cap16a, 141, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter1capture0_reg	_r16, 0x86, 0xFFFF, 0x0000	/* ICR1 */

/*	Object logical registers
 */
#define _hw_reg_counter1capture0_acic	_xob1, acmp0, csr, 1, 2
#define _hw_reg_counter1capture0_icnc	_xob1, counter1, ccrb, 1, 7
#define _hw_reg_counter1capture0_ices	_xob1, counter1, ccrb, 1, 6
#define _hw_reg_counter1capture0_ie	_xob1, counter1, imsk, 1, 5
#define _hw_reg_counter1capture0_if	_xob1, counter1, ifr,  1, 5

/*	Relatives
 */
#define _hw_rel_counter1capture0_pin	pb0
#define _hw_rel_counter1capture0_counter	counter1


/*******************************************************************************
 *									       *
 *	prescaler2: counter2 prescaler					       *
 *									       *
 *	prescaler0 and prescaler2 share the same tsm bit		       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#define _hw_def_prescaler2		_psca, 142, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define _hw_reg_prescaler2_tsm		_xob1, shared, gtccr, 1, 7
#define _hw_reg_prescaler2_psr		_xob1, shared, gtccr, 1, 1

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define _hw_reg_prescaler2_tsmpsr	_xob2, shared, gtccr, 1, 7, 1, gtccr, 1, 1, 0


/*******************************************************************************
 *									       *
 *	Counter 2 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c8c_1.h"	/* was c8b */

/*	Object				class, id, address
 */
#define _hw_def_counter2		_c8c, 143, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter2_ccra		_r8, 0xB0, 0xF3, 0x00
#define _hw_reg_counter2_ccrb		_r8, 0xB1, 0xCF, 0x00
#define _hw_reg_counter2_count		_r8, 0xB2, 0xFF, 0x00
#define _hw_reg_counter2_imsk		_r8, 0x70, 0x07, 0x00
#define _hw_reg_counter2_ifr		_r8, 0x37, 0x07, 0x07
#define _hw_reg_counter2_assr		_r8, 0xB6, 0x60, 0x00

/*	Object logical registers
 */
#define _hw_reg_counter2_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_reg_counter2_cs		_ob1, ccrb, 3, 0
#define _hw_reg_counter2_ie		_ob1, imsk, 1, 0
#define _hw_reg_counter2_if		_ob1, ifr, 1, 0
#define _hw_reg_counter2_prr		_xob1, shared, prr, 1, 6

/*	Relatives
 */
#define _hw_rel_counter2_prescaler0	prescaler2
#define _hw_rel_counter2_prescaler	prescaler2
#define _hw_rel_counter2_compare0	counter2compare0
#define _hw_rel_counter2_compare1	counter2compare1


/*******************************************************************************
 *									       *
 *	Counter 2 compare units counter2compare0, counter2compare1 (OCR2A, OCR2B)		       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_def_counter2compare0	_cmp8a, 144, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter2compare0_reg	_r8, 0xB3, 0xFF, 0x00	/* OCR2A */

/*	Object logical registers
 */
#define _hw_reg_counter2compare0_com	_xob1, counter2, ccra, 2, 6
#define _hw_reg_counter2compare0_force	_xob1, counter2, ccrb, 1, 7
#define _hw_reg_counter2compare0_ie	_xob1, counter2, imsk, 1, 1
#define _hw_reg_counter2compare0_if	_xob1, counter2, ifr,  1, 1

/*	Relatives
 */
#define _hw_rel_counter2compare0_pin	pb3
#define _hw_rel_counter2compare0_counter	counter2


/*	Object				class, id, address
 */
#define _hw_def_counter2compare1	_cmp8a, 145, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_counter2compare1_reg	_r8, 0xB4, 0xFF, 0x00	/* OCR2B */

/*	Object logical registers
 */
#define _hw_reg_counter2compare1_com	_xob1, counter2, ccra, 2, 4
#define _hw_reg_counter2compare1_force	_xob1, counter2, ccrb, 1, 6
#define _hw_reg_counter2compare1_ie	_xob1, counter2, imsk, 1, 2
#define _hw_reg_counter2compare1_if	_xob1, counter2, ifr,  1, 2

/*	Relatives
 */
#define _hw_rel_counter2compare1_pin	pd3
#define _hw_rel_counter2compare1_counter	counter2


/*******************************************************************************
 *									       *
 *	Serial Peripheral Interface					       *
 *									       *
 *******************************************************************************/

#include "../classes/spia_1.h"

/*	Object				class, id, address
 */
#define _hw_def_spi0			_spia, 146, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg_spi0_dr			_r8, 0x4E, 0xFF, 0x00
#define _hw_reg_spi0_sr			_r8, 0x4D, 0xFF, 0x00
#define _hw_reg_spi0_cr			_r8, 0x4C, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_reg_spi0_ie			_ob1, cr, 1, 7
#define _hw_reg_spi0_en			_ob1, cr, 1, 6
#define _hw_reg_spi0_dord		_ob1, cr, 1, 5
#define _hw_reg_spi0_mstr		_ob1, cr, 1, 4
#define _hw_reg_spi0_cpol		_ob1, cr, 1, 3
#define _hw_reg_spi0_cpha		_ob1, cr, 1, 2
#define _hw_reg_spi0_mode		_ob1, cr, 2, 2	/* convenient */

#define _hw_reg_spi0_if			_ob1, sr, 1, 7
#define _hw_reg_spi0_wpol		_ob1, sr, 1, 6

#define _hw_reg_spi0_xpr		_ob2, sr, 1, 0, 2, cr, 2, 0, 0

/*	Relatives
 */
#define _hw_rel_spi0_pin_mosi		pb3
#define _hw_rel_spi0_pin_miso		pb4
#define _hw_rel_spi0_pin_sck		pb5
#define _hw_rel_spi0_pin_ss		pb2


/*******************************************************************************
 *									       *
 *	UART								       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Object
 */
#define _hw_def_uart0			_uarta, 147, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg__uarta_dr		_r8,  0xC6, 0xFF,   0x00
#define _hw_reg__uarta_ubrr		_r16, 0xC4, 0x0FFF, 0x0000
#define _hw_reg__uarta_csrc		_r8,  0xC2, 0xFF,   0x00
#define _hw_reg__uarta_csrb		_r8,  0xC1, 0xFD,   0x00
#define _hw_reg__uarta_csra		_r8,  0xC0, 0x43,   0x40

/*	Class logical registers
 */
#define _hw_reg__uarta_brr		_cb1, ubrr, 12, 0

#define _hw_reg__uarta_ifrxc		_cb1, csra, 1, 7
#define _hw_reg__uarta_iftxc		_cb1, csra, 1, 6
#define _hw_reg__uarta_iftxqnf		_cb1, csra, 1, 5
#define _hw_reg__uarta_fe		_cb1, csra, 1, 4
#define _hw_reg__uarta_dor		_cb1, csra, 1, 3
#define _hw_reg__uarta_pe		_cb1, csra, 1, 2
#define _hw_reg__uarta_2x		_cb1, csra, 1, 1
#define _hw_reg__uarta_mpcm		_cb1, csra, 1, 0

#define _hw_reg__uarta_ierxc		_cb1, csrb, 1, 7
#define _hw_reg__uarta_ietxc		_cb1, csrb, 1, 6
#define _hw_reg__uarta_ietxqnf		_cb1, csrb, 1, 5
#define _hw_reg__uarta_rxen		_cb1, csrb, 1, 4
#define _hw_reg__uarta_txen		_cb1, csrb, 1, 3
#define _hw_reg__uarta_rxb8		_cb1, csrb, 1, 1
#define _hw_reg__uarta_txb8		_cb1, csrb, 1, 0

#define _hw_reg__uarta_msel		_cb1, csrc, 2, 6
#define _hw_reg__uarta_pm		_cb1, csrc, 2, 4
#define _hw_reg__uarta_sbs		_cb1, csrc, 1, 3
#define _hw_reg__uarta_cpol		_cb1, csrc, 1, 0

#define _hw_reg__uarta_csz		_cb2, csrb, 1, 2, 2, csrc, 2, 1, 0

/*	Object logical registers
 */
#define _hw_reg_uart0_prr		_xob1, shared, prr, 1, 1


/*******************************************************************************
 *									       *
 *	2-wire interface						       *
 *									       *
 *******************************************************************************/

#include "../classes/twia_1.h"

/*	Object
 */
#define _hw_def_twi0			_twia, 148, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg__twia_br		_r8, 0xB8, 0xFF, 0x00
#define _hw_reg__twia_cr		_r8, 0xBC, 0xF5, 0x80
#define _hw_reg__twia_sr		_r8, 0xB9, 0x03, 0x00
#define _hw_reg__twia_dr		_r8, 0xBB, 0xFF, 0x00
#define _hw_reg__twia_ar		_r8, 0xBA, 0xFF, 0x00
#define _hw_reg__twia_amr		_r8, 0xBD, 0xFE, 0x00

/*	Relatives
 */
#define _hw_rel_twi0_pin_scl		pc5
#define _hw_rel_twi0_pin_sda		pc4


/*******************************************************************************
 *									       *
 *	acmp0: analog comparator					       *
 *									       *
 *******************************************************************************/

#include "../classes/acmpa_1.h"

/*	Object				class, id, address
 */					
#define _hw_def_acmp0			_acmpa, 149, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw_reg__acmpa_csr		_r8, 0x50, 0xDF, 0x10

/*	Object hardware registers
 *	  Required for _hw_counter1capture0_acic
 */
#define _hw_reg_acmp0_csr		_r8, 0x50, 0xDF, 0x10

/*	Object logical registers
 */
#define _hw_reg_acmp0_acme		_xob1, adc0, srb,   1, 6
#define _hw_reg_acmp0_aden		_xob1, adc0, sra,   1, 7
#define _hw_reg_acmp0_admux		_xob1, adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/ad10b_1.h"

/*	Object				class, id, address
 */					
#define _hw_def_adc0			_ad10b, 150, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw_reg__ad10b_admux		_r8,  0x7C,   0xEF,   0x00
#define _hw_reg__ad10b_sra		_r8,  0x7A,   0xFF,   0x10
#define _hw_reg__ad10b_adc		_r16, 0x78, 0x0000, 0x0000
#define _hw_reg__ad10b_adch		_r8,  0x79,   0x00,   0x00
#define _hw_reg__ad10b_adcl		_r8,  0x78,   0x00,   0x00
#define _hw_reg__ad10b_srb		_r8,  0x7B,   0x47,   0x00

/*	Object hardware registers	class, address, write mask, flags mask
 *
 *	These are necessary for acmp0, and analog input pin configuration
 *	that needs access to the did register of the ADC object.
 */					
#define _hw_reg_adc0_admux		_r8,  0x7C,   0xEF,   0x00
#define _hw_reg_adc0_sra		_r8,  0x7A,   0xFF,   0x10
#define _hw_reg_adc0_srb		_r8,  0x7B,   0x47,   0x00

/*	Class logical registers
 */					
#define _hw_reg__ad10b_refs		_cb1, admux, 2, 6
#define _hw_reg__ad10b_lar		_cb1, admux, 1, 5
#define _hw_reg__ad10b_mux		_cb1, admux, 4, 0

#define _hw_reg__ad10b_en		_cb1, sra, 1, 7
#define _hw_reg__ad10b_sc		_cb1, sra, 1, 6
#define _hw_reg__ad10b_ate		_cb1, sra, 1, 5
#define _hw_reg__ad10b_if		_cb1, sra, 1, 4
#define _hw_reg__ad10b_ie		_cb1, sra, 1, 3
#define _hw_reg__ad10b_ps		_cb1, sra, 3, 0

#define _hw_reg__ad10b_me		_cb1, srb, 1, 6
#define _hw_reg__ad10b_ts		_cb1, srb, 3, 0

/*	Object logical registers
 */
#define _hw_reg_adc0_prr		_xob1, shared, prr, 1, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__eeproma

/*	Object				class, id, address
 */					
#define _hw_def_eeprom0			_eeproma, 151, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw_reg__eeproma_arh		_r8,  0x42,   0x03, 0x00
#define _hw_reg__eeproma_arl		_r8,  0x41,   0xFF, 0x00
#define _hw_reg__eeproma_ar		_r16, 0x41, 0x03FF, 0x00
#define _hw_reg__eeproma_dr		_r8,  0x40,   0xFF, 0x00
#define _hw_reg__eeproma_cr		_r8,  0x3F,   0x3F, 0x00

/*	Class logical registers
 */					
#define _hw_reg__eeproma_pm		_cb1, cr, 2, 4
#define _hw_reg__eeproma_rie		_cb1, cr, 1, 3
#define _hw_reg__eeproma_mpe		_cb1, cr, 1, 2
#define _hw_reg__eeproma_pe		_cb1, cr, 1, 1
#define _hw_reg__eeproma_re		_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__flasha

/*	Object				class, id, address
 */					
#define _hw_def_flash0			_flasha, 152, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw_reg__flasha_csr		_r8, 0x57, 0xBF, 0x00

/*	Class logical registers
 */					
#define _hw_reg__flasha_spmie		_cb1, csr, 1, 7
#define _hw_reg__flasha_rwwsb		_cb1, csr, 1, 6
#define _hw_reg__flasha_sigrd		_cb1, csr, 1, 5
#define _hw_reg__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw_reg__flasha_blbset		_cb1, csr, 1, 3
#define _hw_reg__flasha_pgwrt		_cb1, csr, 1, 2
#define _hw_reg__flasha_pgers		_cb1, csr, 1, 1
#define _hw_reg__flasha_spmen		_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	Software UART							       *
 *									       *
 *******************************************************************************/

#define _hw_class__swuarta

#  define _hw_class__swuarta

/*	Object hw_swuart0
 */
#if defined hw_swuart0_compare || defined hw_swuart0_clk_div || defined hw_swuart0_pin_txd || defined hw_swuart0_pin_rxd || defined hw_swuart0_starter || defined hw_swuart0_check_tx
#  if !defined hw_swuart0_compare
#    error hw_swuart0_compare is not defined
#  elif HW_ID(hw_swuart0_compare) == 0
#    error HWA: hw_swuart0_compare: invalid definition
#    undef hw_swuart0_compare
#  endif
#  if !defined hw_swuart0_clk_div
#    error hw_swuart0_clk_div is not defined
#    undef hw_swuart0_compare
#  endif
#  if defined hw_swuart0_pin_txd && HW_ID(hw_swuart0_pin_txd)==0
#    error invalid definition of hw_swuart0_pin_txd
#    undef hw_swuart0_compare
#  endif
#  if defined hw_swuart0_pin_rxd && HW_ID(hw_swuart0_pin_rxd)==0
#    error invalid definition of hw_swuart0_pin_rxd
#    undef hw_swuart0_compare
#  endif
#  if defined hw_swuart0_pin_rxd && !defined hw_swuart0_starter
#    warning hw_swuart0_starter is not defined, using default 'pcic'
#    undef hw_swuart0_compare
#  endif
#endif

#if defined hw_swuart0_compare
/*
 *	Object swuart0
 */
#define _hw_def_swuart0			_swuarta, 153, 0
#define _hw_reg_swuart0_dtn		_HW_RC(_HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_reg_swuart0_dt0		_HW_RC(_HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_reg_swuart0__st		_HW_A(_HW_M(shared, gpior0))
#define _hw_reg_swuart0_sr		_hw_reg_shared_gpior0
#define _hw_reg_swuart0_synced		_ob1, sr, 1, 0
#endif

#if defined hw_swuart1_compare || defined hw_swuart1_clk_div || defined hw_swuart1_pin_txd || defined hw_swuart1_pin_rxd || defined hw_swuart1_starter || defined hw_swuart1_check_tx
#  if !defined hw_swuart1_compare
#    error hw_swuart1_compare is not defined
#  elif HW_ID(hw_swuart1_compare) == 0
#    error HWA: hw_swuart1_compare: invalid definition
#    undef hw_swuart1_compare
#  endif
#  if !defined hw_swuart1_clk_div
#    error hw_swuart1_clk_div is not defined
#    undef hw_swuart1_compare
#  endif
#  if defined hw_swuart1_pin_txd && HW_ID(hw_swuart1_pin_txd)==0
#    error invalid definition of hw_swuart1_pin_txd
#    undef hw_swuart1_compare
#  endif
#  if defined hw_swuart1_pin_rxd && HW_ID(hw_swuart1_pin_rxd)==0
#    error invalid definition of hw_swuart1_pin_rxd
#    undef hw_swuart1_compare
#  endif
#  if defined hw_swuart1_pin_rxd && !defined hw_swuart1_starter
#    warning hw_swuart1_starter is not defined, using default 'pcic'
#    undef hw_swuart1_compare
#  endif
#endif

#if defined hw_swuart1_compare
/*
 *	Object swuart1
 */
#define _hw_def_swuart1			_swuarta, 154, 0
#define _hw_reg_swuart1_dtn		_HW_RC(_HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_reg_swuart1_dt0		_HW_RC(_HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dt0, -1, 0x00
#define _hw_reg_swuart1__st		_HW_A(_HW_M(shared, gpior1))
#define _hw_reg_swuart1_sr		_hw_reg_shared_gpior1
#define _hw_reg_swuart1_synced		_ob1, sr, 1, 0
#endif


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/


#if !defined __ASSEMBLER__

/**
 * @brief The HWA context
 *
 * This structure is instanciated by hwa_begin() or hwa_begin_from_reset() and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;

  hwa_coreb_t	core0 ;
  hwa_p8a_t	port0 ;
  hwa_p8a_t	port1 ;
  hwa_p8a_t	port2 ;
  hwa_pcica_t	pcic0 ;
  hwa_pcica_t	pcic1 ;
  hwa_pcica_t	pcic2 ;
  hwa_wdogb_t	watchdog0 ;

  hwa_c8a_t	counter0 ;
  hwa_cmp8a_t	counter0compare0 ;
  hwa_cmp8a_t	counter0compare1 ;

  hwa_c16a_t	counter1 ;
  hwa_cmp16a_t	counter1compare0 ;
  hwa_cmp16a_t	counter1compare1 ;
  hwa_cap16a_t	counter1capture0 ;

  hwa_c8c_t	counter2 ;
  hwa_cmp8a_t	counter2compare0 ;
  hwa_cmp8a_t	counter2compare1 ;

  hwa_spia_t	spi0 ;
  hwa_uarta_t	uart0 ;
  hwa_twia_t	twi0 ;
  hwa_acmpa_t	acmp0 ;
  hwa_ad10b_t	adc0 ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p8a_2.h"
#include "../classes/coreb_2.h"
#include "../classes/inta_2.h"
#include "../classes/pcica_2.h"
#include "../classes/wdogb_2.h"
#include "../classes/cmp8a_2.h"
#include "../classes/c8a_2.h"
#include "../classes/c8c_2.h"
#include "../classes/cap16a_2.h"
#include "../classes/cmp16a_2.h"
#include "../classes/c16a_2.h"
#include "../classes/psca_2.h"
#include "../classes/spia_2.h"
#include "../classes/uarta_2.h"
#include "../classes/twia_2.h"
#include "../classes/acmpa_2.h"
#include "../classes/ad10b_2.h"
#include "../classes/eeproma_2.h"
#include "../classes/flasha_2.h"
#include "../classes/swuarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_reg( shared, eimsk );
  _hwa_setup_reg( shared, eifr	);
  _hwa_setup_reg( shared, eicr	);
  _hwa_setup_reg( shared, gtccr );
  _hwa_setup_reg( shared, prr	);
  _hwa_setup_reg( shared, did1	);
  _hwa_setup_reg( shared, did0	);
  _hwa_setup_reg( shared, pcicr	 );
  _hwa_setup_reg( shared, pcifr	 );

  _hwa_setup( core0 );
  _hwa_setup( port0 );
  _hwa_setup( port1 );
  _hwa_setup( port2 );
  _hwa_setup( pcic0 );
  _hwa_setup( pcic1 );
  _hwa_setup( pcic2 );
  _hwa_setup( watchdog0 );

  _hwa_setup( counter0compare0 );
  _hwa_setup( counter0compare1 );
  _hwa_setup( counter0 );

  _hwa_setup( counter1compare0 );
  _hwa_setup( counter1compare1 );
  _hwa_setup( counter1capture0 );
  _hwa_setup( counter1 );

  _hwa_setup( counter2compare0 );
  _hwa_setup( counter2compare1 );
  _hwa_setup( counter2 );

  _hwa_setup( spi0 );
  _hwa_setup( uart0 );
  _hwa_setup( twi0 );
  _hwa_setup( acmp0 );
  _hwa_setup( adc0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_reg( shared, eimsk, 0 );
  _hwa_init_reg( shared, eifr,	0 );
  _hwa_init_reg( shared, eicr,	0 );
  _hwa_init_reg( shared, gtccr, 0 );
  _hwa_init_reg( shared, prr,	0 );
  _hwa_init_reg( shared, did1,	0 );
  _hwa_init_reg( shared, did0,	0 );
  _hwa_init_reg( shared, pcicr, 0 );
  _hwa_init_reg( shared, pcifr, 0 );

  _hwa_init( core0 );
  _hwa_init( port0 );
  _hwa_init( port1 );
  _hwa_init( port2 );
  _hwa_init( pcic0 );
  _hwa_init( pcic1 );
  _hwa_init( pcic2 );
  _hwa_init( watchdog0 );

  _hwa_init( counter0compare0 );
  _hwa_init( counter0compare1 );
  _hwa_init( counter0 );

  _hwa_init( counter1compare0 );
  _hwa_init( counter1compare1 );
  _hwa_init( counter1capture0 );
  _hwa_init( counter1 );

  _hwa_init( counter2compare0 );
  _hwa_init( counter2compare1 );
  _hwa_init( counter2 );

  _hwa_init( spi0 );
  _hwa_init( uart0 );
  _hwa_init( twi0 );
  _hwa_init( acmp0 );
  _hwa_init( adc0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve( counter0 );
  _hwa_solve( counter1 );
  _hwa_solve( counter2 );

  _hwa_commit_reg( shared, eimsk );
  _hwa_commit_reg( shared, eifr	 );
  _hwa_commit_reg( shared, eicr	 );
  _hwa_commit( core0 );
  _hwa_commit_reg( shared, prr	 );
  _hwa_commit( watchdog0 );
  _hwa_commit( port0 );
  _hwa_commit( port1 );
  _hwa_commit( port2 );
  _hwa_commit_reg( shared, pcifr );
  _hwa_commit_reg( shared, pcicr );
  _hwa_commit( pcic0 );
  _hwa_commit( pcic1 );
  _hwa_commit( pcic2 );

  _hwa_commit_reg( shared, gtccr );
  _hwa_commit( counter0 );
  _hwa_commit( counter0compare0 );
  _hwa_commit( counter0compare1 );

  _hwa_commit( counter1 );
  _hwa_commit( counter1compare0 );
  _hwa_commit( counter1compare1 );
  _hwa_commit( counter1capture0 );

  _hwa_commit( counter2 );
  _hwa_commit( counter2compare0 );
  _hwa_commit( counter2compare1 );

  _hwa_commit( spi0  );
  _hwa_commit( uart0 );
  _hwa_commit( twi0  );
  _hwa_commit( acmp0 );
  _hwa_commit_reg( shared, did1	 );
  _hwa_commit( adc0 );
  _hwa_commit_reg( shared, did0	 );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page atmegax8
 * <br>
 */
