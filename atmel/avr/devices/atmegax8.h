
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
 * @section atmegax8_device Description
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE`		    |The device name passed to the compiler
 * `HW_DEVICE_ATMEGAX8`	    |Always defined (void)
 * `HW_DEVICE_ATMEGA48`<br>...<br>`HW_DEVICE_ATMEGA328P_AU` | Defined (void) depending on the HWA header included
 * `HW_DEVICE_PACKAGE_32Q`  |Defined (void) depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte (after registers and I/O regs)
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table)
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
 * `HW_DEVICE_RAM_START`       |0x0100	      |0x0100	     |0x0100	     |0x0100
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


/* 	Fuse bytes are defined in device-specific header	*/


/**
 * @page atmegax8
 * @subsection atmegax8_fuses_clocking Clocking
 *
 * HWA uses these settings to compute the system clock frequency `hw_syshz`.
 *
 * Symbol		 | Valid values | Comments
 * :---------------------|--------------|:-----------
 * `HW_DEVICE_CLK_SRC`	 | `external`<br>`rc_128kHz`<br><b>`rc_8MHz`</b><br>`low_freq_xosc`<br>`low_power_xosc`<br>`full_swing_xosc`|External source on pin CLKI<br>Internal RC oscillator (watchdog)<br>Internal RC calibrated oscillator<br>Crystal/resonator oscillator between pins XTAL1 and XTAL2<br> <br> <br>
 * `HW_DEVICE_CLK_SRC_HZ`| Positive integer |Clock frequency for `external` and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`	 | <b>`8`</b><br>`1`|Clock divided by 8<br>Clock not divided
 */
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_rc_128kHz_rc_128kHz			, 1
#define _hw_is_low_freq_xosc_low_freq_xosc		, 1
#define _hw_is_low_power_xosc_low_power_xosc		, 1
#define _hw_is_full_swing_xosc_full_swing_xosc		, 1

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
#  define hw_syshz					hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_FUSE_CKDIV8				1
#  define hw_syshz					hw_syshz_base
#else
#  HW_ERROR(`HW_DEVICE_CLK_PSC` can be `8`, or `1`, but not HW_DEVICE_CLK_PSC)
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

#define _hw_is_application_application			, 1
#define _hw_is_bootloader_bootloader			, 1

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
 * @note All the peripherals are not completely implemented yet.
 *
 * Object name		  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_core0`	 | @ref atmelavr_coreb "_coreb" | The core
 * `hw_int0`	 | @ref atmelavr_inta "_inta"   | External interrupt INT0
 * `hw_int1`	 | @ref atmelavr_inta "_inta"   | External interrupt INT1
 * `hw_portb`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port B (PORTB)
 * `hw_portc`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port C (PORTC)
 * `hw_portd`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port D (PORTD)
 * `hw_pcic0`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `hw_pcic1`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `hw_pcic2`	 | @ref atmelavr_pcica "_pcica" | Pin change interrupt controller
 * `hw_wdog0`	 | @ref atmelavr_wdogb "_wdogb" | Watchdog (WDG)
 * `hw_counter0` | @ref atmelavr_c8a "_c8a"	| 8-bit counter-timer (T0)
 * `hw_oc00`	 | @ref atmelavr_oc8a "_oc8a"	| Compare unit 0 of hw_counter0 (OC0A)
 * `hw_oc01`	 | @ref atmelavr_oc8a "_oc8a"	| Compare unit 1 of hw_counter0 (OC0B)
 * `hw_counter1` | @ref atmelavr_c16a "_c16a"	| 16-bit counter-timer (T1)
 * `hw_oc10`	 | @ref atmelavr_oc16a "_oc16a"	| Compare unit 0 of hw_counter1 (OC1A)
 * `hw_oc11`	 | @ref atmelavr_oc16a "_oc16a"	| Compare unit 1 of hw_counter1 (OC1B)
 * `hw_ic10`	 | @ref atmelavr_ic16a "_ic16a"	| Capture unit 0 of hw_counter1 (ICP1)
 * `hw_counter2` | @ref atmelavr_c8c "_c8c"	| 8-bit counter-timer (T2)
 * `hw_oc20`	 | @ref atmelavr_oc8a "_oc8a"	| Compare unit 0 of hw_counter2 (OC2A)
 * `hw_oc21`	 | @ref atmelavr_oc8a "_oc8a"	| Compare unit 1 of hw_counter2 (OC2B)
 * `hw_psc0`	 | @ref atmelavr_psca "_psca"	| hw_counter0/hw_counter1 prescaler (PSC0)
 * `hw_spi0`	 | @ref atmelavr_spia "_spia"   | Serial Peripheral Interface
 * `hw_uart0`	 | @ref atmelavr_uarta "_uarta" | Universal Asynchronous Receiver Transmitter
 * `hw_twi0`	 | @ref atmelavr_twia "_twia"   | 2-wire Serial Interface
 * `hw_acmp0`	 | @ref atmelavr_acmpa "acmpa"	| Analog Comparator
 * `hw_adc0`	 | @ref atmelavr_ad10b "ad10b"	| 10-bit Analog to Digital Converter
 * `hw_eeprom0`	 | @ref atmelavr_eeproma "eeproma" | Eeprom memory
 * `hw_flash0`	 | @ref atmelavr_flasha "flasha"   | Flash memory
 *
 * @subsection atmegax8_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name			  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_spimaster_swclk0`  | @ref atmelavr_usia_spimaster_swclk "usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `hw_swuart0`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 * `hw_swuart1`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 *
 * @subsection atmegax8_objrel Aliases and relations
 *
 * Some objects can be accessed from their relatives or can have more than one
 * name. There are the existing relations between the device's objects and their
 * different names:
 *
 * Name		 | Aliases		 | Relations
 * :-------------|-----------------------|:--------------------------------------
 * `hw_psc0`	 | `hw_counter0prescaler`  | `hw_rel(hw_counter0, prescaler)`
 * `hw_psc0`	 | `hw_counter0prescaler0` | `hw_rel(hw_counter0, prescaler0)`
 * `hw_psc0`	 | `hw_counter1prescaler`  | `hw_rel(hw_counter1, prescaler)`
 * `hw_psc0`	 | `hw_counter1prescaler0` | `hw_rel(hw_counter1, prescaler0)`
 * `hw_oc00`	 | `hw_counter0compare0`   | `hw_rel(hw_counter0, compare0)`
 * `hw_oc01`	 | `hw_counter0compare1`   | `hw_rel(hw_counter0, compare1)`
 * `hw_counter0` | `hw_oc00counter`	   | `hw_rel(hw_oc00, counter)`
 * `hw_counter0` | `hw_oc01counter`	   | `hw_rel(hw_oc01, counter)`
 * `hw_pin_oc00` | `hw_oc00pin`		   | `hw_rel(hw_oc00, pin)`
 * `hw_pin_oc01` | `hw_oc01pin`		   | `hw_rel(hw_oc01, pin)`
 * `hw_oc10`	 | `hw_counter1compare0`   | `hw_rel(hw_counter1, compare0)`
 * `hw_oc11`	 | `hw_counter1compare1`   | `hw_rel(hw_counter1, compare1)`
 * `hw_counter1` | `hw_oc10counter`	   | `hw_rel(hw_oc10, counter)`
 * `hw_counter1` | `hw_oc11counter`	   | `hw_rel(hw_oc11, counter)`
 * `hw_pin_oc10` | `hw_oc10pin`		   | `hw_rel(hw_oc10, pin)`
 * `hw_pin_oc11` | `hw_oc11pin`		   | `hw_rel(hw_oc11, pin)`
 * `hw_pin_ic10` | `hw_ic10pin`		   | `hw_rel(hw_ic10, pin)`
 * `hw_counter2` | `hw_oc20counter`	   | `hw_rel(hw_oc20, counter)`
 * `hw_counter2` | `hw_oc21counter`	   | `hw_rel(hw_oc21, counter)`
 * `hw_pin_oc20` | `hw_oc20pin`		   | `hw_rel(hw_oc20, pin)`
 * `hw_pin_oc21` | `hw_oc21pin`		   | `hw_rel(hw_oc21, pin)`
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
 * Interrupt definition                    | Atmel label  | Comments
 * :---------------------------------------|--------------|------------------------
 * `hw_int0`                               | INT0         | External Interrupt Request 0
 * `hw_int1`                               | INT1         | External Interrupt Request 1
 * `hw_pin_*,change`                       | PCINT0/1/2   | Pin Change Interrupt Request 0/1/2
 * `hw_wdog0`                              | WDT          | Watchdog Time-out Interrupt
 * `hw_oc20`<br>`hw_counter2,compare0`     | TIMER2 COMPA | Timer/Counter2 Compare Match A
 * `hw_oc21`<br>`hw_counter2,compare1`     | TIMER2 COMPB | Timer/Counter2 Compare Match B
 * `hw_counter2`<br>`hw_counter2,overflow` | TIMER2 OVF   | Timer/Counter2 Overflow
 * `hw_ic10`<br>`hw_counter1,capture0`     | TIMER1 CAPT  | Timer/Counter1 Capture Event
 * `hw_oc10`<br>`hw_counter1,compare0`     | TIMER1 COMPA | Timer/Counter1 Compare Match A
 * `hw_oc11`<br>`hw_counter1,compare1`     | TIMER1 COMPB | Timer/Coutner1 Compare Match B
 * `hw_counter1`<br>`hw_counter1,overflow` | TIMER1 OVF   | Timer/Counter1 Overflow
 * `hw_oc00`<br>`hw_counter0,compare0`     | TIMER0 COMPA | Timer/Counter0 Compare Match A
 * `hw_oc01`<br>`hw_counter0,compare1`     | TIMER0 COMPB | Timer/Counter0 Compare Match B
 * `hw_counter0`<br>`hw_counter0,overflow` | TIMER0 OVF   | Timer/Counter0 Overflow
 * `hw_spi0`                               | SPI,STC      | SPI Serial Transfer Complete
 * `hw_uart0,rxc`                          | USART,RXC    | USART Rx Complete
 * `hw_uart0,txqne`                        | USART,UDRE   | USART, Data Register Empty
 * `hw_uart0,txc`                          | USART,TXC    | USART, Tx Complete
 * `hw_adc0`                               | ADC          | ADC conversion complete
 * `hw_eeprom0`                            | EE READY     | EEPROM ready
 * `hw_eeprom0,ready`                      | EE READY     | EEPROM ready
 * `hw_acmp0`                              | ANALOG COMP  | Analog comparator
 * `hw_twi0`                               | TWI          | 2-wire Serial Interface
 * `hw_flash0`                             | SPM READY    | Store Program Memory Ready
 */
/**
 * @ingroup atmegax8_interrupts
 * @brief Definition of the interrupts
 */
#define _hw_irq_hw_int0			_irq,  1, hw_int0,     ie,  if
#define _hw_irq_hw_int1			_irq,  2, hw_int1,     ie,  if
#define _hw_irq_hw_pcic0		_irq,  3, hw_pcic0,    ie,  if
#define _hw_irq_hw_pcic1		_irq,  4, hw_pcic1,    ie,  if
#define _hw_irq_hw_pcic2		_irq,  5, hw_pcic2,    ie,  if
#define _hw_irq_hw_wdog0		_irq,  6, hw_wdog0,    ie,  if

#define _hw_irq_hw_counter2_compare0	_irq,  7, hw_oc20,     ie,  if
#define _hw_irq_hw_oc20			_irq,  7, hw_oc20,     ie,  if
#define _hw_irq_hw_counter2_compare1	_irq,  8, hw_oc21,     ie,  if
#define _hw_irq_hw_oc21			_irq,  8, hw_oc21,     ie,  if
#define _hw_irq_hw_counter2_overflow	_irq,  9, hw_counter2, ie,  if
#define _hw_irq_hw_counter2		_irq,  9, hw_counter2, ie,  if

#define _hw_irq_hw_counter1_capture0	_irq, 10, hw_ic10,     ie,  if
#define _hw_irq_hw_ic10			_irq, 10, hw_ic10,     ie,  if
#define _hw_irq_hw_counter1_compare0	_irq, 11, hw_oc10,     ie,  if
#define _hw_irq_hw_oc10			_irq, 11, hw_oc10,     ie,  if
#define _hw_irq_hw_counter1_compare1	_irq, 12, hw_oc11,     ie,  if
#define _hw_irq_hw_oc11			_irq, 12, hw_oc11,     ie,  if
#define _hw_irq_hw_counter1_overflow	_irq, 13, hw_counter1, ie,  if
#define _hw_irq_hw_counter1		_irq, 13, hw_counter1, ie,  if

#define _hw_irq_hw_counter0_compare0	_irq, 14, hw_oc00,     ie,  if
#define _hw_irq_hw_oc00			_irq, 14, hw_oc00,     ie,  if
#define _hw_irq_hw_counter0_compare1	_irq, 15, hw_oc01,     ie,  if
#define _hw_irq_hw_oc01			_irq, 15, hw_oc01,     ie,  if
#define _hw_irq_hw_counter0_overflow	_irq, 16, hw_counter0, ie,  if
#define _hw_irq_hw_counter0		_irq, 16, hw_counter0, ie,  if

#define _hw_irq_hw_spi0			_irq, 17, hw_spi0,     ie,  if
#define _hw_irq_hw_spi0_txc		_irq, 17, hw_spi0,     ie,  if

#define _hw_irq_hw_uart0_rxc		_irq, 18, hw_uart0,   ierxc,  ifrxc
#define _hw_irq_hw_uart0_txqnf		_irq, 19, hw_uart0,   ietxqe, iftxqnf
#define _hw_irq_hw_uart0_txc		_irq, 20, hw_uart0,   ietxc,  iftxc

#define _hw_irq_hw_adc0			_irq, 21, hw_adc0,     ie,    if

#define _hw_irq_hw_eeprom0		_irq, 22, hw_eeprom0,  ie, /* no irq flag */
#define _hw_irq_hw_eeprom0_ready	_irq, 22, hw_eeprom0,  ie,

#define _hw_irq_hw_acmp0		_irq, 23, hw_acmp0,    ie, if

#define _hw_irq_hw_twi0			_irq, 24, hw_twi0,     ie, if

#define _hw_irq_hw_flash0		_irq, 25, hw_flash0,   ie, if


/**
 * @page atmegax8
 * @section atmegax8_pm Power Management
 *
 * The following peripherals can be powered on/off using the `hw_power()` or the
 * `hwa_power()` instruction:
 *
 *  * `hw_twi0`
 *  * `hw_counter0`
 *  * `hw_counter1`
 *  * `hw_counter2`
 *  * `hw_spi0`
 *  * `hw_uart0`
 *  * `hw_adc0`
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
#define _hw_shared			_shared, 0, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_shared_did1			_r8, 0x7F, 0x03, 0x00	/* DID for AIN0/AIN1 */
#define _hw_shared_did0			_r8, 0x7E, 0x3F, 0x00 	/* DID for PORTC */
#define _hw_shared_eicr			_r8, 0x69, 0x0F, 0x00
#define _hw_shared_pcicr		_r8, 0x68, 0x07, 0x00
#define _hw_shared_prr			_r8, 0x64, 0xEF, 0x00
#define _hw_shared_gpior2		_r8, 0x4B, 0xFF, 0x00
#define _hw_shared_gpior1		_r8, 0x4A, 0xFF, 0x00
#define _hw_shared_gtccr		_r8, 0x43, 0x81, 0x00
#define _hw_shared_gpior0		_r8, 0x3E, 0xFF, 0x00
#define _hw_shared_eimsk		_r8, 0x3D, 0x03, 0x00
#define _hw_shared_eifr			_r8, 0x3C, 0x03, 0x03
#define _hw_shared_pcifr		_r8, 0x3B, 0x07, 0x07

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
 * `hw_port_b`	|	      | @ref atmelavr_io1a "_io1a" | PORTB
 * `hw_pin_pb0` | `hw_pin_12` | @ref atmelavr_io1a "_io1a" | PB0
 * `hw_pin_pb1` | `hw_pin_13` | @ref atmelavr_io1a "_io1a" | PB1
 * `hw_pin_pb2` | `hw_pin_14` | @ref atmelavr_io1a "_io1a" | PB2
 * `hw_pin_pb3` | `hw_pin_15` | @ref atmelavr_io1a "_io1a" | PB3
 * `hw_pin_pb4` | `hw_pin_16` | @ref atmelavr_io1a "_io1a" | PB4
 * `hw_pin_pb5` | `hw_pin_17` | @ref atmelavr_io1a "_io1a" | PB5
 * `hw_pin_pb6` | `hw_pin_7`  | @ref atmelavr_io1a "_io1a" | PB6
 * `hw_pin_pb7` | `hw_pin_8`  | @ref atmelavr_io1a "_io1a" | PB7
 * `hw_port_c`	|	      | @ref atmelavr_io1a "_io1a" | PORTC
 * `hw_pin_pc0` | `hw_pin_23` | @ref atmelavr_io1a "_io1a" | PC0
 * `hw_pin_pc1` | `hw_pin_24` | @ref atmelavr_io1a "_io1a" | PC1
 * `hw_pin_pc2` | `hw_pin_25` | @ref atmelavr_io1a "_io1a" | PC2
 * `hw_pin_pc3` | `hw_pin_26` | @ref atmelavr_io1a "_io1a" | PC3
 * `hw_pin_pc4` | `hw_pin_27` | @ref atmelavr_io1a "_io1a" | PC4
 * `hw_pin_pc5` | `hw_pin_28` | @ref atmelavr_io1a "_io1a" | PC5
 * `hw_pin_pc6` | `hw_pin_29` | @ref atmelavr_io1a "_io1a" | PC6
 * `hw_port_d`	|	      | @ref atmelavr_io1a "_io1a" | PORTD
 * `hw_pin_pd0` | `hw_pin_30` | @ref atmelavr_io1a "_io1a" | PD0
 * `hw_pin_pd1` | `hw_pin_31` | @ref atmelavr_io1a "_io1a" | PD1
 * `hw_pin_pd2` | `hw_pin_32` | @ref atmelavr_io1a "_io1a" | PD2
 * `hw_pin_pd3` | `hw_pin_1`  | @ref atmelavr_io1a "_io1a" | PD3
 * `hw_pin_pd4` | `hw_pin_2`  | @ref atmelavr_io1a "_io1a" | PD4
 * `hw_pin_pd5` | `hw_pin_9`  | @ref atmelavr_io1a "_io1a" | PD5
 * `hw_pin_pd6` | `hw_pin_10` | @ref atmelavr_io1a "_io1a" | PD6
 * `hw_pin_pd7` | `hw_pin_11` | @ref atmelavr_io1a "_io1a" | PD7
 */

/*	Objects				class, id, address
 */
#include "../classes/p8a_1.h"
#include "../classes/io1a_1.h"

#define _hw_portb			_p8a, 300, 0x23
#define _hw_portc			_p8a, 310, 0x26
#define _hw_portd			_p8a, 320, 0x29

/*  Pins				class, id, port, bn, bp
 */
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)
#  define _hw_pin_pb0			_io1a, 301, hw_portb, 1, 0
#endif
#define _hw_pin_pb1			_io1a, 302, hw_portb, 1, 1
#define _hw_pin_pb2			_io1a, 303, hw_portb, 1, 2
#define _hw_pin_pb3			_io1a, 304, hw_portb, 1, 3
#define _hw_pin_pb4			_io1a, 305, hw_portb, 1, 4
#define _hw_pin_pb5			_io1a, 306, hw_portb, 1, 5

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb6			_io1a, 307, hw_portb, 1, 6
#endif
#if !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb7			_io1a, 308, hw_portb, 1, 7
#endif
#define _hw_port_b			_io1a, 309, hw_portb, 8, 0

#define _hw_pin_pc0			_io1a, 311, hw_portc, 1, 0
#define _hw_pin_pc1			_io1a, 312, hw_portc, 1, 1
#define _hw_pin_pc2			_io1a, 313, hw_portc, 1, 2
#define _hw_pin_pc3			_io1a, 314, hw_portc, 1, 3
#define _hw_pin_pc4			_io1a, 315, hw_portc, 1, 4
#define _hw_pin_pc5			_io1a, 316, hw_portc, 1, 5
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)
#  define _hw_pin_pc6			_io1a, 317, hw_portc, 1, 6
#endif
#define _hw_port_c			_io1a, 319, hw_portc, 7, 0

#define _hw_pin_pd0			_io1a, 321, hw_portd, 1, 0
#define _hw_pin_pd1			_io1a, 322, hw_portd, 1, 1
#define _hw_pin_pd2			_io1a, 323, hw_portd, 1, 2
#define _hw_pin_pd3			_io1a, 324, hw_portd, 1, 3
#define _hw_pin_pd4			_io1a, 325, hw_portd, 1, 4
#define _hw_pin_pd5			_io1a, 326, hw_portd, 1, 5
#define _hw_pin_pd6			_io1a, 327, hw_portd, 1, 6
#define _hw_pin_pd7			_io1a, 328, hw_portd, 1, 7
#define _hw_port_d			_io1a, 329, hw_portd, 8, 0

/*  Alternate pin functions
 */
#define hw_pin_sck			hw_pin_pb5
#define hw_pin_miso			hw_pin_pb4
#define hw_pin_mosi			hw_pin_pb3
#define hw_pin_ss			hw_pin_pb2

/*  Capture & compare outputs
 */
#define hw_pin_oc00			hw_pin_pd6
#define hw_pin_oc01			hw_pin_pd5
#define hw_pin_oc10			hw_pin_pb1
#define hw_pin_oc11			hw_pin_pb2
#define hw_pin_ic10			hw_pin_pb0
#define hw_pin_oc20			hw_pin_pb3
#define hw_pin_oc21			hw_pin_pd3

/*  Analog pins. ADC6/ADC7 are analog inputs only, no DID register.
 */
#define hw_pin_adc0			hw_pin_pc0
#define hw_pin_adc1			hw_pin_pc1
#define hw_pin_adc2			hw_pin_pc2
#define hw_pin_adc3			hw_pin_pc3
#define hw_pin_adc4			hw_pin_pc4
#define hw_pin_adc5			hw_pin_pc5

#define hw_pin_ain1			hw_pin_pd7
#define hw_pin_ain0			hw_pin_pd6

#define _hw_pin_adc6			_io1a, 336
#define _hw_pin_adc7			_io1a, 337

/*  Digital input disable bits for analog input pins
 */
#define _hw_pin_pc0_did			_xob1, hw_shared, did0, 1, 0	/* ADC0 */
#define _hw_pin_pc1_did			_xob1, hw_shared, did0, 1, 1	/* ADC1 */
#define _hw_pin_pc2_did			_xob1, hw_shared, did0, 1, 2	/* ADC2 */
#define _hw_pin_pc3_did			_xob1, hw_shared, did0, 1, 3	/* ADC3 */
#define _hw_pin_pc4_did			_xob1, hw_shared, did0, 1, 4	/* ADC4 */
#define _hw_pin_pc5_did			_xob1, hw_shared, did0, 1, 5	/* ADC5 */

/* #define _hw_pin_adc6_did		, */
/* #define _hw_pin_adc7_did		, */

#define _hw_pin_pd6_did			_xob1, hw_shared, did1, 1, 0	/* AIN0 */
#define _hw_pin_pd7_did			_xob1, hw_shared, did1, 1, 1	/* AIN1 */

/*  Communications
 */
#define hw_pin_scl			hw_pin_pc5
#define hw_pin_sda			hw_pin_pc4

#define hw_pin_txd			hw_pin_pd1
#define hw_pin_rxd			hw_pin_pd0

/*  Relative pin change controllers
 */
#define hw_pin_pb0pcic			hw_pcic0
#define hw_pin_pb1pcic			hw_pcic0
#define hw_pin_pb2pcic			hw_pcic0
#define hw_pin_pb3pcic			hw_pcic0
#define hw_pin_pb4pcic			hw_pcic0
#define hw_pin_pb5pcic			hw_pcic0
#define hw_pin_pb6pcic			hw_pcic0
#define hw_pin_pb7pcic			hw_pcic0

#define hw_pin_pc0pcic			hw_pcic1
#define hw_pin_pc1pcic			hw_pcic1
#define hw_pin_pc2pcic			hw_pcic1
#define hw_pin_pc3pcic			hw_pcic1
#define hw_pin_pc4pcic			hw_pcic1
#define hw_pin_pc5pcic			hw_pcic1
#define hw_pin_pc6pcic			hw_pcic1

#define hw_pin_pd0pcic			hw_pcic2
#define hw_pin_pd1pcic			hw_pcic2
#define hw_pin_pd2pcic			hw_pcic2
#define hw_pin_pd3pcic			hw_pcic2
#define hw_pin_pd4pcic			hw_pcic2
#define hw_pin_pd5pcic			hw_pcic2
#define hw_pin_pd6pcic			hw_pcic2
#define hw_pin_pd7pcic			hw_pcic2


/*  Pins by numbers
 */
#if defined HW_DEVICE_PACKAGE_28P
#
#  define hw_pin_1			hw_pin_pc6
#  define hw_pin_2			hw_pin_pd0
#  define hw_pin_3			hw_pin_pd1
#  define hw_pin_4			hw_pin_pd2
#  define hw_pin_5			hw_pin_pd3
#  define hw_pin_6			hw_pin_pd4
#  define hw_pin_9			hw_pin_pb6
#  define hw_pin_10			hw_pin_pb7
#  define hw_pin_11			hw_pin_pd5
#  define hw_pin_12			hw_pin_pd6
#  define hw_pin_13			hw_pin_pd7
#  define hw_pin_14			hw_pin_pb0
#  define hw_pin_15			hw_pin_pb1
#  define hw_pin_16			hw_pin_pb2
#  define hw_pin_17			hw_pin_pb3
#  define hw_pin_18			hw_pin_pb4
#  define hw_pin_19			hw_pin_pb5
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#
#elif defined HW_DEVICE_PACKAGE_28Q
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
/* #  define hw_pin_3			hw_pin_ */
/* #  define hw_pin_4			hw_pin_ */
#  define hw_pin_5			hw_pin_pb6
#  define hw_pin_6			hw_pin_pb7
#  define hw_pin_7			hw_pin_pd5
#  define hw_pin_8			hw_pin_pd6
#  define hw_pin_9			hw_pin_pd7
#  define hw_pin_10			hw_pin_pb0
#  define hw_pin_11			hw_pin_pb1
#  define hw_pin_12			hw_pin_pb2
#  define hw_pin_13			hw_pin_pb3
#  define hw_pin_14			hw_pin_pb4
#  define hw_pin_15			hw_pin_pb5
/* #  define hw_pin_16			hw_pin_ */
/* #  define hw_pin_17			hw_pin_ */
/* #  define hw_pin_18			hw_pin_ */
#  define hw_pin_19			hw_pin_pc0
#  define hw_pin_20			hw_pin_pc1
#  define hw_pin_21			hw_pin_pc2
#  define hw_pin_22			hw_pin_pc3
#  define hw_pin_23			hw_pin_pc4
#  define hw_pin_24			hw_pin_pc5
#  define hw_pin_25			hw_pin_pc6
#  define hw_pin_26			hw_pin_pd0
#  define hw_pin_27			hw_pin_pd1
#  define hw_pin_28			hw_pin_pd2
#
#elif defined HW_DEVICE_PACKAGE_32Q
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
#  define hw_pin_7			hw_pin_pb6
#  define hw_pin_8			hw_pin_pb7
#  define hw_pin_9			hw_pin_pd5
#  define hw_pin_10			hw_pin_pd6
#  define hw_pin_11			hw_pin_pd7
#  define hw_pin_12			hw_pin_pb0
#  define hw_pin_13			hw_pin_pb1
#  define hw_pin_14			hw_pin_pb2
#  define hw_pin_15			hw_pin_pb3
#  define hw_pin_16			hw_pin_pb4
#  define hw_pin_17			hw_pin_pb5
#  define hw_pin_19			hw_pin_adc6
#  define hw_pin_22			hw_pin_adc7
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#  define hw_pin_29			hw_pin_pc6
#  define hw_pin_30			hw_pin_pd0
#  define hw_pin_31			hw_pin_pd1
#  define hw_pin_32			hw_pin_pd2
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
#define _hw_core0			_coreb, 101, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_core0_osccal		_r8, 0x66, 0xFF, 0x00
#define _hw_core0_sreg			_r8, 0x5F, 0xFF, 0x00
#define _hw_core0_sph			_r8, 0x5E, 0x03, 0x00
#define _hw_core0_spl			_r8, 0x5D, 0xFF, 0x00
#define _hw_core0_mcucr			_r8, 0x55, 0x73, 0x00
#define _hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define _hw_core0_smcr			_r8, 0x53, 0x0F, 0x00

/*	Object logical registers
 */
#define _hw_core0_bods			_ob1, mcucr, 1, 6
#define _hw_core0_bodse			_ob1, mcucr, 1, 5
#define _hw_core0_pud			_ob1, mcucr, 1, 4
#define _hw_core0_ivsel			_ob1, mcucr, 1, 1
#define _hw_core0_ivce			_ob1, mcucr, 1, 0

#define _hw_core0_wdrf			_ob1, mcusr, 1, 3
#define _hw_core0_borf			_ob1, mcusr, 1, 2
#define _hw_core0_extrf			_ob1, mcusr, 1, 1
#define _hw_core0_porf			_ob1, mcusr, 1, 0
#define _hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */

#define _hw_core0_sm			_ob1, smcr, 3, 1
#define _hw_core0_se			_ob1, smcr, 1, 0


/*******************************************************************************
 *									       *
 *	External interrupt controllers					       *
 *									       *
 *******************************************************************************/

#include "../classes/inta_1.h"

/*	Object				class, id, address
 */
#define _hw_int0			_inta, 110, 0

/*	Object logical registers
 */
#define _hw_int0_sc			_xob1, hw_shared, eicr,  2, 0
#define _hw_int0_ie			_xob1, hw_shared, eimsk, 1, 0
#define _hw_int0_if			_xob1, hw_shared, eifr,  1, 0

/*	Object				class, id, address
 */
#define _hw_int1			_inta, 111, 0

/*	Object logical registers
 */
#define _hw_int1_sc			_xob1, hw_shared, eicr,  2, 2
#define _hw_int1_ie			_xob1, hw_shared, eimsk, 1, 1
#define _hw_int1_if			_xob1, hw_shared, eifr,  1, 1


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

#include "../classes/pcica_1.h"

/*	Object				class, id, address
 */
#define _hw_pcic0			_pcica, 350, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic0_msk			_r8, 0x6B, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_pcic0_ie			_xob1, hw_shared, pcicr, 1, 0
#define _hw_pcic0_if			_xob1, hw_shared, pcifr, 1, 0

/*	Object				class, id, address
 */
#define _hw_pcic1			_pcica, 351, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic1_msk			_r8, 0x6C, 0x7F, 0x00

/*	Object logical registers
 */
#define _hw_pcic1_ie			_xob1, hw_shared, pcicr, 1, 1
#define _hw_pcic1_if			_xob1, hw_shared, pcifr, 1, 1

/*	Object				class, id, address
 */
#define _hw_pcic2			_pcica, 352, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic2_msk			_r8, 0x6D, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_pcic2_ie			_xob1, hw_shared, pcicr, 1, 2
#define _hw_pcic2_if			_xob1, hw_shared, pcifr, 1, 2


/*******************************************************************************
 *									       *
 *	hw_wdog0: watchdog						       *
 *									       *
 *******************************************************************************/

#include "../classes/wdogb_1.h"

/*	Object				class, id, address
 */
#define _hw_wdog0			_wdogb, 109, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__wdogb_csr			_r8, 0x60, 0xFF, 0x80

/*	Class logical registers
 */
#define _hw__wdogb_wdrf			_xob1, hw_core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0/1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psca_1.h"

/*	Object				class, id, address
 */
#define _hw_psc0			_psca, 401, 0

/*	Object logical registers
 */
#define _hw_psc0_tsm			_xob1, hw_shared, gtccr, 1, 7
#define _hw_psc0_psr			_xob1, hw_shared, gtccr, 1, 0

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define _hw_psc0_tsmpsr			_xob2, hw_shared, gtccr, 1, 7, 1, gtccr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	Counter 0 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c8a_1.h"

/*	Object				class, id, address
 */
#define _hw_counter0			_c8a, 400, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter0_ccra		_r8, 0x44, 0xF3, 0x00
#define _hw_counter0_ccrb		_r8, 0x45, 0xCF, 0x00
#define _hw_counter0_count		_r8, 0x46, 0xFF, 0x00
#define _hw_counter0_imsk		_r8, 0x6E, 0x07, 0x00
#define _hw_counter0_ifr		_r8, 0x35, 0x07, 0x07

/*	Object logical registers
 */
#define _hw_counter0_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_counter0_cs			_ob1, ccrb, 3, 0
#define _hw_counter0_ie			_ob1, imsk, 1, 0
#define _hw_counter0_if			_ob1, ifr, 1, 0
#define _hw_counter0_prr		_xob1, hw_shared, prr, 1, 5


/*	Relatives
 */
#define hw_counter0prescaler0		hw_psc0
#define hw_counter0prescaler		hw_psc0
#define hw_counter0compare0		hw_oc00
#define hw_counter0compare1		hw_oc01


/*******************************************************************************
 *									       *
 *	Counter 0 compare units hw_oc00, hw_oc01 (OCR0A, OCR0B)		       *
 *									       *
 *******************************************************************************/

#include "../classes/oc8a_1.h"

/*	Object				class, id, address
 */
#define _hw_oc00			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc00_reg			_r8, 0x47, 0xFF, 0x00	/* OCR0A */

/*	Object logical registers
 */
#define _hw_oc00_com			_xob1, hw_counter0, ccra, 2, 6
#define _hw_oc00_force			_xob1, hw_counter0, ccrb, 1, 7
#define _hw_oc00_ie			_xob1, hw_counter0, imsk, 1, 1
#define _hw_oc00_if			_xob1, hw_counter0, ifr,  1, 1

/*	Relatives
 */
#define hw_oc00pin			hw_pin_oc00
#define hw_oc00counter			hw_counter0

/*	Object				class, id, address
 */
#define _hw_oc01			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc01_reg			_r8, 0x48, 0xFF, 0x00	/* OCR0B */

/*	Object logical registers
 */
#define _hw_oc01_com			_xob1, hw_counter0, ccra, 2, 4
#define _hw_oc01_force			_xob1, hw_counter0, ccrb, 1, 6
#define _hw_oc01_ie			_xob1, hw_counter0, imsk, 1, 2
#define _hw_oc01_if			_xob1, hw_counter0, ifr,  1, 2

/*	Relatives
 */
#define hw_oc01pin			hw_pin_oc01
#define hw_oc01counter			hw_counter0


/*******************************************************************************
 *									       *
 *	hw_counter1: counter 1 counting unit				       *
 *									       *
 *******************************************************************************/

#include "../classes/c16a_1.h"

/*	Object				class, id, address
 */
#define _hw_counter1			_c16a, 410, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter1_ccra		_r8,  0x80, 0xF3,   0x00
#define _hw_counter1_ccrb		_r8,  0x81, 0xDF,   0x00
#define _hw_counter1_ccrc		_r8,  0x82, 0xC0,   0x00
#define _hw_counter1_count		_r16, 0x84, 0xFFFF, 0x0000
#define _hw_counter1_imsk		_r8,  0x6F, 0x27,   0x00
#define _hw_counter1_ifr		_r8,  0x36, 0x27,   0x27

/*	Object logical registers
 */
#define _hw_counter1_cs			_ob1, ccrb, 3, 0
#define _hw_counter1_wgm		_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define _hw_counter1_ie			_ob1, imsk, 1, 0
#define _hw_counter1_if			_ob1, ifr, 1, 0
#define _hw_counter1_prr		_xob1, hw_shared, prr, 1, 3

/*	Relatives
 */
#define hw_counter1prescaler0		hw_psc0
#define hw_counter1prescaler		hw_psc0
#define hw_counter1compare0		hw_oc10
#define hw_counter1compare1		hw_oc11
#define hw_counter1capture0		hw_ic10


/*******************************************************************************
 *									       *
 *	Counter 1 compare units hw_oc10, hw_oc11 (OCR1A, OCR1B)		       *
 *									       *
 *******************************************************************************/

#include "../classes/oc16a_1.h"

/*	Object				class, id, address
 */
#define _hw_oc10			_oc16a, 411, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc10_reg			_r16, 0x88, 0xFFFF, 0x0000	/* OCR1A */

/*	Object logical registers
 */
#define _hw_oc10_com			_xob1, hw_counter1, ccra, 2, 6
#define _hw_oc10_force			_xob1, hw_counter1, ccrc, 1, 7
#define _hw_oc10_ie			_xob1, hw_counter1, imsk, 1, 1
#define _hw_oc10_if			_xob1, hw_counter1, ifr,  1, 1

/*	Relatives
 */
#define hw_oc10pin			hw_pin_oc10
#define hw_oc10counter			hw_counter1

/*	Object				class, id, address
 */
#define _hw_oc11			_oc16a, 412, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc11_reg			_r16, 0x8A, 0xFFFF, 0x0000	/* OCR1B */

/*	Object logical registers
 */
#define _hw_oc11_com			_xob1, hw_counter1, ccra, 2, 4
#define _hw_oc11_force			_xob1, hw_counter1, ccrc, 1, 6
#define _hw_oc11_ie			_xob1, hw_counter1, imsk, 1, 2
#define _hw_oc11_if			_xob1, hw_counter1, ifr,  1, 2

/*	Relatives
 */
#define hw_oc11pin			hw_pin_oc11
#define hw_oc11counter			hw_counter1


/*******************************************************************************
 *									       *
 *	Counter 1 capture unit hw_ic10					       *
 *									       *
 *******************************************************************************/

#include "../classes/ic16a_1.h"

/*	Object				class, id, address
 */
#define _hw_ic10			_ic16a, 413, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_ic10_reg			_r16, 0x86, 0xFFFF, 0x0000	/* ICR1 */

/*	Object logical registers
 */
#define _hw_ic10_acic			_xob1, hw_acmp0, csr, 1, 2
#define _hw_ic10_icnc			_xob1, hw_counter1, ccrb, 1, 7
#define _hw_ic10_ices			_xob1, hw_counter1, ccrb, 1, 6
#define _hw_ic10_ie			_xob1, hw_counter1, imsk, 1, 5
#define _hw_ic10_if			_xob1, hw_counter1, ifr,  1, 5

/*	Relatives
 */
#define hw_ic10pin			hw_pin_ic11
#define hw_ic10counter			hw_counter1


/*******************************************************************************
 *									       *
 *	hw_psc2: hw_counter2 prescaler					       *
 *									       *
 *	hw_psc0 and hw_psc2 share the same tsm bit			       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#define _hw_psc2			_psca, 421, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define _hw_psc2_tsm			_xob1, hw_shared, gtccr, 1, 7
#define _hw_psc2_psr			_xob1, hw_shared, gtccr, 1, 1

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define _hw_psc2_tsmpsr			_xob2, hw_shared, gtccr, 1, 7, 1, gtccr, 1, 1, 0


/*******************************************************************************
 *									       *
 *	Counter 2 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c8c_1.h"	/* was c8b */

/*	Object				class, id, address
 */
#define _hw_counter2			_c8c, 420, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter2_ccra		_r8, 0xB0, 0xF3, 0x00
#define _hw_counter2_ccrb		_r8, 0xB1, 0xCF, 0x00
#define _hw_counter2_count		_r8, 0xB2, 0xFF, 0x00
#define _hw_counter2_imsk		_r8, 0x70, 0x07, 0x00
#define _hw_counter2_ifr		_r8, 0x37, 0x07, 0x07
#define _hw_counter2_assr		_r8, 0xB6, 0x60, 0x00

/*	Object logical registers
 */
#define _hw_counter2_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_counter2_cs			_ob1, ccrb, 3, 0
#define _hw_counter2_ie			_ob1, imsk, 1, 0
#define _hw_counter2_if			_ob1, ifr, 1, 0
#define _hw_counter2_prr		_xob1, hw_shared, prr, 1, 6

/*	Relatives
 */
#define hw_counter2prescaler0		hw_psc2
#define hw_counter2prescaler		hw_psc2
#define hw_counter2compare0		hw_oc20
#define hw_counter2compare1		hw_oc21


/*******************************************************************************
 *									       *
 *	Counter 2 compare units hw_oc20, hw_oc21 (OCR2A, OCR2B)		       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_oc20			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc20_reg			_r8, 0xB3, 0xFF, 0x00	/* OCR2A */

/*	Object logical registers
 */
#define _hw_oc20_com			_xob1, hw_counter2, ccra, 2, 6
#define _hw_oc20_force			_xob1, hw_counter2, ccrb, 1, 7
#define _hw_oc20_ie			_xob1, hw_counter2, imsk, 1, 1
#define _hw_oc20_if			_xob1, hw_counter2, ifr,  1, 1

/*	Relatives
 */
#define hw_oc20pin			hw_pin_oc20
#define hw_oc20counter			hw_counter2

/*	Object				class, id, address
 */
#define _hw_oc21			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc21_reg			_r8, 0xB4, 0xFF, 0x00	/* OCR2B */

/*	Object logical registers
 */
#define _hw_oc21_com			_xob1, hw_counter2, ccra, 2, 4
#define _hw_oc21_force			_xob1, hw_counter2, ccrb, 1, 6
#define _hw_oc21_ie			_xob1, hw_counter2, imsk, 1, 2
#define _hw_oc21_if			_xob1, hw_counter2, ifr,  1, 2

/*	Relatives
 */
#define hw_oc21pin			hw_pin_oc21
#define hw_oc21counter			hw_counter2


/*******************************************************************************
 *									       *
 *	Serial Peripheral Interface					       *
 *									       *
 *******************************************************************************/

#include "../classes/spia_1.h"

/*	Object				class, id, address
 */
#define _hw_spi0			_spia, 500, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_spi0_dr			_r8, 0x4E, 0xFF, 0x00
#define _hw_spi0_sr			_r8, 0x4D, 0xFF, 0x00
#define _hw_spi0_cr			_r8, 0x4C, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_spi0_ie			_ob1, cr, 1, 7
#define _hw_spi0_en			_ob1, cr, 1, 6
#define _hw_spi0_dord			_ob1, cr, 1, 5
#define _hw_spi0_mstr			_ob1, cr, 1, 4
#define _hw_spi0_cpol			_ob1, cr, 1, 3
#define _hw_spi0_cpha			_ob1, cr, 1, 2

#define _hw_spi0_if			_ob1, sr, 1, 7
#define _hw_spi0_wpol			_ob1, sr, 1, 6

#define _hw_spi0_xpr			_ob2, sr, 1, 0, 2, cr, 2, 0, 0

/*	Relatives
 */
#define hw_spi0pin_mosi			hw_pin_mosi
#define hw_spi0pin_miso			hw_pin_miso
#define hw_spi0pin_sck			hw_pin_sck
#define hw_spi0pin_ss			hw_pin_ss


/*******************************************************************************
 *									       *
 *	UART								       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Object
 */
#define _hw_uart0			_uarta, 600, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__uarta_dr			_r8,  0xC6, 0xFF,   0x00
#define _hw__uarta_ubrr			_r16, 0xC4, 0x0FFF, 0x0000
#define _hw__uarta_csrc			_r8,  0xC2, 0xFF,   0x00
#define _hw__uarta_csrb			_r8,  0xC1, 0xFD,   0x00
#define _hw__uarta_csra			_r8,  0xC0, 0x43,   0x40

/*	Class logical registers
 */
#define _hw__uarta_brr			_cb1, ubrr, 12, 0

#define _hw__uarta_ifrxc		_cb1, csra, 1, 7
#define _hw__uarta_iftxc		_cb1, csra, 1, 6
#define _hw__uarta_iftxqnf		_cb1, csra, 1, 5
#define _hw__uarta_fe			_cb1, csra, 1, 4
#define _hw__uarta_dor			_cb1, csra, 1, 3
#define _hw__uarta_pe			_cb1, csra, 1, 2
#define _hw__uarta_2x			_cb1, csra, 1, 1
#define _hw__uarta_mpcm			_cb1, csra, 1, 0

#define _hw__uarta_ierxc		_cb1, csrb, 1, 7
#define _hw__uarta_ietxc		_cb1, csrb, 1, 6
#define _hw__uarta_ietxqnf		_cb1, csrb, 1, 5
#define _hw__uarta_rxen			_cb1, csrb, 1, 4
#define _hw__uarta_txen			_cb1, csrb, 1, 3
#define _hw__uarta_rxb8			_cb1, csrb, 1, 1
#define _hw__uarta_txb8			_cb1, csrb, 1, 0

#define _hw__uarta_msel			_cb1, csrc, 2, 6
#define _hw__uarta_pm			_cb1, csrc, 2, 4
#define _hw__uarta_sbs			_cb1, csrc, 1, 3
#define _hw__uarta_cpol			_cb1, csrc, 1, 0

#define _hw__uarta_csz			_cb2, csrb, 1, 2, 2, csrc, 2, 1, 0

/*	Object logical registers
 */
#define _hw_uart0_prr			_xob1, hw_shared, prr, 1, 1


/*******************************************************************************
 *									       *
 *	2-wire interface						       *
 *									       *
 *******************************************************************************/

#include "../classes/twia_1.h"

/*	Object
 */
#define _hw_twi0			_twia, 610, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__twia_br			_r8, 0xB8, 0xFF, 0x00
#define _hw__twia_cr			_r8, 0xBC, 0xF5, 0x80
#define _hw__twia_sr			_r8, 0xB9, 0x03, 0x00
#define _hw__twia_dr			_r8, 0xBB, 0xFF, 0x00
#define _hw__twia_ar			_r8, 0xBA, 0xFF, 0x00
#define _hw__twia_amr			_r8, 0xBD, 0xFE, 0x00

/*	Relatives
 */
#define hw_twi0pin_scl			hw_pin_scl
#define hw_twi0pin_sda			hw_pin_sda


/*******************************************************************************
 *									       *
 *	hw_acmp0: analog comparator					       *
 *									       *
 *******************************************************************************/

#include "../classes/acmpa_1.h"

/*	Object				class, id, address
 */					
#define _hw_acmp0			_acmpa, 710, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__acmpa_csr			_r8, 0x50, 0xDF, 0x10

/*	Object hardware registers
 *	  Required for _hw_ic10_acic
 */
#define _hw_acmp0_csr			_r8, 0x50, 0xDF, 0x10

/*	Object logical registers
 */
#define _hw_acmp0_acme			_xob1, hw_adc0, srb,   1, 6
#define _hw_acmp0_aden			_xob1, hw_adc0, sra,   1, 7
#define _hw_acmp0_admux			_xob1, hw_adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/ad10b_1.h"

/*	Object				class, id, address
 */					
#define _hw_adc0			_ad10b, 720, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__ad10b_admux		_r8,  0x7C,   0xEF,   0x00
#define _hw__ad10b_sra			_r8,  0x7A,   0xFF,   0x10
#define _hw__ad10b_adc			_r16, 0x78, 0x0000, 0x0000
#define _hw__ad10b_adch			_r8,  0x79,   0x00,   0x00
#define _hw__ad10b_adcl			_r8,  0x78,   0x00,   0x00
#define _hw__ad10b_srb			_r8,  0x7B,   0x47,   0x00

/*	Object hardware registers	class, address, write mask, flags mask
 *
 *	These are necessary for hw_acmp0, and analog input pin configuration
 *	that needs access to the did register of the ADC object.
 */					
#define _hw_adc0_admux			_r8,  0x7C,   0xEF,   0x00
#define _hw_adc0_sra			_r8,  0x7A,   0xFF,   0x10
#define _hw_adc0_srb			_r8,  0x7B,   0x47,   0x00

/*	Class logical registers
 */					
#define _hw__ad10b_refs			_cb1, admux, 2, 6
#define _hw__ad10b_lar			_cb1, admux, 1, 5
#define _hw__ad10b_mux			_cb1, admux, 4, 0

#define _hw__ad10b_en			_cb1, sra, 1, 7
#define _hw__ad10b_sc			_cb1, sra, 1, 6
#define _hw__ad10b_ate			_cb1, sra, 1, 5
#define _hw__ad10b_if			_cb1, sra, 1, 4
#define _hw__ad10b_ie			_cb1, sra, 1, 3
#define _hw__ad10b_ps			_cb1, sra, 3, 0

#define _hw__ad10b_me			_cb1, srb, 1, 6
#define _hw__ad10b_ts			_cb1, srb, 3, 0

/*	Object logical registers
 */
#define _hw_adc0_prr			_xob1, hw_shared, prr, 1, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__eeproma

/*	Object				class, id, address
 */					
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__eeproma_arh		_r8,  0x42,   0x03, 0x00
#define _hw__eeproma_arl		_r8,  0x41,   0xFF, 0x00
#define _hw__eeproma_ar			_r16, 0x41, 0x03FF, 0x00
#define _hw__eeproma_dr			_r8,  0x40,   0xFF, 0x00
#define _hw__eeproma_cr			_r8,  0x3F,   0x3F, 0x00

/*	Class logical registers
 */					
#define _hw__eeproma_pm			_cb1, cr, 2, 4
#define _hw__eeproma_rie		_cb1, cr, 1, 3
#define _hw__eeproma_mpe		_cb1, cr, 1, 2
#define _hw__eeproma_pe			_cb1, cr, 1, 1
#define _hw__eeproma_re			_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__flasha

/*	Object				class, id, address
 */					
#define _hw_flash0			_flasha, 1100, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__flasha_csr			_r8, 0x57, 0xBF, 0x00

/*	Class logical registers
 */					
#define _hw__flasha_spmie		_cb1, csr, 1, 7
#define _hw__flasha_rwwsb		_cb1, csr, 1, 6
#define _hw__flasha_sigrd		_cb1, csr, 1, 5
#define _hw__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw__flasha_blbset		_cb1, csr, 1, 3
#define _hw__flasha_pgwrt		_cb1, csr, 1, 2
#define _hw__flasha_pgers		_cb1, csr, 1, 1
#define _hw__flasha_spmen		_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	Software UART							       *
 *									       *
 *******************************************************************************/

#define _hw_class__swuarta

#if defined hw_swuart0_compare
/*
 *	Object hw_swuart0
 */
#define _hw_swuart0			_swuarta, 1200, 0
#define _hw_swuart0_dtn							\
  _hw_rc(hw_rel(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_swuart0_dt0							\
  _hw_rc(hw_rel(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_swuart0__st			_hw_ra(hw_shared, gpior0)
#define _hw_swuart0_sr			_hw_shared_gpior0
#define _hw_swuart0_synced		_ob1, sr, 1, 0
#endif

#if defined hw_swuart1_compare
/*
 *	Object hw_swuart1
 */
#define _hw_swuart1			_swuarta, 1210, 0
#define _hw_swuart1_dtn							\
  _hw_rc(hw_rel(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_swuart1_dt0							\
  _hw_rc(hw_rel(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dt0, -1, 0x00
#define _hw_swuart1__st			_hw_ra(hw_shared, gpior1)
#define _hw_swuart1_sr			_hw_shared_gpior1
#define _hw_swuart1_synced		_ob1, sr, 1, 0
#endif


#if !defined __ASSEMBLER__

/**
 * @brief The HWA context
 *
 * This structure is instanciated by hwa_begin() or hwa_begin_from_reset() and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	hw_shared ;

  hwa_coreb_t	hw_core0 ;
  hwa_p8a_t	hw_portb ;
  hwa_p8a_t	hw_portc ;
  hwa_p8a_t	hw_portd ;
  hwa_pcica_t	hw_pcic0 ;
  hwa_pcica_t	hw_pcic1 ;
  hwa_pcica_t	hw_pcic2 ;
  hwa_wdogb_t	hw_wdog0 ;

  hwa_c8a_t	hw_counter0 ;
  hwa_oc8a_t	hw_oc00 ;
  hwa_oc8a_t	hw_oc01 ;

  hwa_c16a_t	hw_counter1 ;
  hwa_oc16a_t	hw_oc10 ;
  hwa_oc16a_t	hw_oc11 ;
  hwa_ic16a_t	hw_ic10 ;

  hwa_c8c_t	hw_counter2 ;
  hwa_oc8a_t	hw_oc20 ;
  hwa_oc8a_t	hw_oc21 ;

  hwa_spia_t	hw_spi0 ;
  hwa_uarta_t	hw_uart0 ;
  hwa_twia_t	hw_twi0 ;
  hwa_acmpa_t	hw_acmp0 ;
  hwa_ad10b_t	hw_adc0 ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p8a_2.h"
#include "../classes/coreb_2.h"
#include "../classes/inta_2.h"
#include "../classes/pcica_2.h"
#include "../classes/wdogb_2.h"
#include "../classes/oc8a_2.h"
#include "../classes/c8a_2.h"
#include "../classes/c8c_2.h"
#include "../classes/ic16a_2.h"
#include "../classes/oc16a_2.h"
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


HW_INLINE void _hwa_create_context( hwa_t *hwa )
{
  _hwa_create_reg( hw_shared, eimsk );
  _hwa_create_reg( hw_shared, eifr  );
  _hwa_create_reg( hw_shared, eicr  );
  _hwa_create_reg( hw_shared, gtccr );
  _hwa_create_reg( hw_shared, prr   );
  _hwa_create_reg( hw_shared, did1  );
  _hwa_create_reg( hw_shared, did0  );
  _hwa_create_reg( hw_shared, pcicr  );
  _hwa_create_reg( hw_shared, pcifr  );

  _hwa_create( hw_core0 );
  _hwa_create( hw_portb );
  _hwa_create( hw_portc );
  _hwa_create( hw_portd );
  _hwa_create( hw_pcic0 );
  _hwa_create( hw_pcic1 );
  _hwa_create( hw_pcic2 );
  _hwa_create( hw_wdog0 );

  _hwa_create( hw_oc00 );
  _hwa_create( hw_oc01 );
  _hwa_create( hw_counter0 );

  _hwa_create( hw_oc10 );
  _hwa_create( hw_oc11 );
  _hwa_create( hw_ic10 );
  _hwa_create( hw_counter1 );

  _hwa_create( hw_oc20 );
  _hwa_create( hw_oc21 );
  _hwa_create( hw_counter2 );

  _hwa_create( hw_spi0 );
  _hwa_create( hw_uart0 );
  _hwa_create( hw_twi0 );
  _hwa_create( hw_acmp0 );
  _hwa_create( hw_adc0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_reg( hw_shared, eimsk, 0 );
  _hwa_init_reg( hw_shared, eifr,  0 );
  _hwa_init_reg( hw_shared, eicr,  0 );
  _hwa_init_reg( hw_shared, gtccr, 0 );
  _hwa_init_reg( hw_shared, prr,   0 );
  _hwa_init_reg( hw_shared, did1,  0 );
  _hwa_init_reg( hw_shared, did0,  0 );
  _hwa_init_reg( hw_shared, pcicr, 0 );
  _hwa_init_reg( hw_shared, pcifr, 0 );

  _hwa_init( hw_core0 );
  _hwa_init( hw_portb );
  _hwa_init( hw_portc );
  _hwa_init( hw_portd );
  _hwa_init( hw_pcic0 );
  _hwa_init( hw_pcic1 );
  _hwa_init( hw_pcic2 );
  _hwa_init( hw_wdog0 );

  _hwa_init( hw_oc00 );
  _hwa_init( hw_oc01 );
  _hwa_init( hw_counter0 );

  _hwa_init( hw_oc10 );
  _hwa_init( hw_oc11 );
  _hwa_init( hw_ic10 );
  _hwa_init( hw_counter1 );

  _hwa_init( hw_oc20 );
  _hwa_init( hw_oc21 );
  _hwa_init( hw_counter2 );

  _hwa_init( hw_spi0 );
  _hwa_init( hw_uart0 );
  _hwa_init( hw_twi0 );
  _hwa_init( hw_acmp0 );
  _hwa_init( hw_adc0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve( hw_counter0 );
  _hwa_solve( hw_counter1 );
  _hwa_solve( hw_counter2 );

  _hwa_commit_reg( hw_shared, eimsk );
  _hwa_commit_reg( hw_shared, eifr  );
  _hwa_commit_reg( hw_shared, eicr  );
  _hwa_commit( hw_core0 );
  _hwa_commit_reg( hw_shared, prr   );
  _hwa_commit( hw_wdog0 );
  _hwa_commit( hw_portb );
  _hwa_commit( hw_portc );
  _hwa_commit( hw_portd );
  _hwa_commit_reg( hw_shared, pcifr );
  _hwa_commit_reg( hw_shared, pcicr );
  _hwa_commit( hw_pcic0 );
  _hwa_commit( hw_pcic1 );
  _hwa_commit( hw_pcic2 );

  _hwa_commit_reg( hw_shared, gtccr );
  _hwa_commit( hw_counter0 );
  _hwa_commit( hw_oc00 );
  _hwa_commit( hw_oc01 );

  _hwa_commit( hw_counter1 );
  _hwa_commit( hw_oc10 );
  _hwa_commit( hw_oc11 );
  _hwa_commit( hw_ic10 );

  _hwa_commit( hw_counter2 );
  _hwa_commit( hw_oc20 );
  _hwa_commit( hw_oc21 );

  _hwa_commit( hw_spi0  );
  _hwa_commit( hw_uart0 );
  _hwa_commit( hw_twi0  );
  _hwa_commit( hw_acmp0 );
  _hwa_commit_reg( hw_shared, did1  );
  _hwa_commit( hw_adc0 );
  _hwa_commit_reg( hw_shared, did0  );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page atmegax8
 * <br>
 */
