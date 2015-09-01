
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega16U4/32U4
 */

#include "../hwa_1.h"

/**
 * @page atmegaxu4 ATmega16U4/32U4
 * @section attinyx8_device Device description symbols
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE`		    |The device name as passed to the compiler
 * `HW_DEVICE_ATMEGAXU4`    |Defined void
 * `HW_DEVICE_ATMEGA32U4_MU` | Defined void depending on the HWA header included
 * `HW_DEVICE_PACKAGE_44Q`  |Defined void depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte (after registers and I/O regs)
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table)
 *
 * Symbol		       | ATmega16U4 | ATmega32U4
 * :---------------------------|:------------:|:------------
 * `HW_DEVICE`		       |	      |atmega32u4
 * `HW_DEVICE_SIGNATURE`       |              |0x1E,0x95,0x87
 * `HW_DEVICE_FLASH_SIZE`      |     	      |32768
 * `HW_DEVICE_FLASH_PAGE_SIZE` |   	      |256
 * `HW_DEVICE_EEPROM_SIZE`     |    	      |1024
 * `HW_DEVICE_EEPROM_PAGE_SIZE`| 	      |8
 * `HW_DEVICE_RAM_SIZE`	       |   	      |2560
 * `HW_DEVICE_RAM_START`       |       	      |0x0100
 * `HW_DEVICE_APP_START`       |      	      |0x00AC
 */
#define HW_DEVICE_ATMEGAXU4


/**
 * @page atmegaxu4
 * @section atmegaxu4_fuses Configuration fuses
 *
 * ATmegaXU4 devices hold 3 fuse bytes describing their hardware configuration.
 * HWA computes the value of these fuse bytes from the fuse values (detailed in
 * the following subsections) that must be defined prior to including the HWA
 * header. Factory defaults (shown with a bold face) are used for values that
 * are undefined as the HWA header is included.
 *
 * Symbol		| Comments
 * :--------------------|:-----------
 * `HW_DEVICE_FUSE_EB`	| Fuse extended byte
 * `HW_DEVICE_FUSE_HB`	| Fuse high byte
 * `HW_DEVICE_FUSE_LB`	| Fuse low byte
 */

#if !defined HW_DEVICE_FUSE_EBX
#  define HW_DEVICE_FUSE_EBX		0xF
#endif

#define HW_DEVICE_FUSE_EB			\
  (HW_DEVICE_FUSE_EBX & 0x0F)<<4 |		\
  HW_DEVICE_FUSE_HWBE<<3 |			\
  HW_DEVICE_FUSE_BODLEVEL

#define HW_DEVICE_FUSE_HB			\
  HW_DEVICE_FUSE_OCDEN<<7 |			\
  HW_DEVICE_FUSE_JTAGEN<<6 |			\
  HW_DEVICE_FUSE_SPIEN<<5 |			\
  HW_DEVICE_FUSE_WDTON<<4 |			\
  HW_DEVICE_FUSE_EESAVE<<3 |			\
  HW_DEVICE_FUSE_BOOTSZ<<1 |			\
  HW_DEVICE_FUSE_BOOTRST

#define HW_DEVICE_FUSE_LB			\
  HW_DEVICE_FUSE_CKDIV8<<7 |			\
  HW_DEVICE_FUSE_CKOUT<<6 |			\
  HW_DEVICE_FUSE_SUT10<<4 |			\
  HW_DEVICE_FUSE_CKSEL31<<1 |			\
  HW_DEVICE_FUSE_CKSEL0

/**
 * @page atmegaxu4
 * @subsection atmegaxu4_fuses_clocking Clocking
 *
 * HWA uses these settings to compute the system clock frequency `hw_syshz`.
 *
 * Symbol		 | Valid values | Comments
 * :---------------------|--------------|:-----------
 * `HW_DEVICE_CLK_SRC`	 | `external`<br><b>`rc_8MHz`</b><br>`low_freq_xosc`<br>`low_power_xosc`|External source on pin CLKI<br>Internal RC calibrated oscillator<br>Crystal/resonator oscillator between pins XTAL1 and XTAL2<br>
 * `HW_DEVICE_CLK_SRC_HZ`| Positive integer |Clock frequency for `external` and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`	 | <b>`8`</b><br>`1`|Clock divided by 8<br>Clock not divided
 */
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_low_freq_xosc_low_freq_xosc		, 1
#define _hw_is_low_power_xosc_low_power_xosc		, 1


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
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_FUSE_CKSEL31			2
#
#elif HW_IS(HW_DEVICE_CLK_SRC, low_power_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#  endif
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
#else
#  error HW_DEVICE_CLK_SRC can be `rc_8MHz`, `low_freq_xosc`, `low_power_xosc`, or `external`.
#endif

/*  Check that we have a valid hw_syshz_base
 */
/* #if HW_IS(,hw_syshz_base) */
/* #  error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking */
/* #endif */

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
 * @page atmegaxu4
 * @subsection atmegaxu4_fuses_sut Startup delays
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
#  if HW_DEVICE_CKSEL31 < 2
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
#  elif HW_DEVICE_CKSEL31 == 2
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
#  define HW_DEVICE_FUSE_SUT10					2
#  define HW_DEVICE_FUSE_CKSEL0					1
#endif


/**
 * @page atmegaxu4
 * @subsection atmegaxu4_fuses_other Other fuses
 *
 * Symbol		  | Valid values | Comments
 * :----------------------|--------------|:-----------
 * `HW_DEVICE_PIN_HWB`|<b>`enabled`</b><br>`disabled`|Whether the HWB pin allows to execute the bootloader section after reset when tied to ground during external reset pulse.
 * `HW_DEVICE_BROWNOUT_DETECTION`|<b>`off`</b><br>`1800_2200mV`<br>`2000_2400mV`<br>`2200_2600mV`<br>`2400_2800mV`<br>`3200_3600mV`<br>`3300_3700mV`<br>`4000_4500mV`|Brown-out detection level
 * `HW_DEVICE_ON_CHIP_DEBUG`|`enabled`<br><b>`disabled`</b>|Whether on-chip debugging is enabled
 * `HW_DEVICE_JTAG`|`enabled`<br><b>`disabled`</b>|Whether the JTAG interface is enabled
 * `HW_DEVICE_SERIAL_PROGRAMMING`|<b>`enabled`</b><br>`disabled`|Whether the device can be programmed via the SPI
 * `HW_DEVICE_WATCHDOG_ALWAYS_ON`|`yes`<br><b>`no`</b>		|Whether the watchdog is always running
 * `HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE`|`enabled`<br><b>`disabled`</b>|Whether the EEPROM memory is erased when a chip erase occurs
 * `HW_DEVICE_BOOT`|<b>`application`</b><br>`bootloader`|Whether the device starts the application or the bootloader after reset
 * `HW_DEVICE_BOOTSECTION_SIZE`|`512`<br>`1024`<br>`2048`<br><b>`4096`</b>|Size of the boot section
 * `HW_DEVICE_CLOCK_OUTPUT`|`enabled`<br><b>`disabled`</b>|Whether the device outputs its clock
 */

#if !defined HW_DEVICE_PIN_HWB
#  define HW_DEVICE_PIN_HWB			enabled
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_PIN_HWB))
#  define HW_DEVICE_FUSE_HWBE			\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_PIN_HWB))
#else
#  error HW_DEVICE_PIN_HWB must be defined as `enabled` (default) or `disabled`.
#endif


#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION		off
#endif

#define _hw_bodlevel_off			, 7
#define _hw_bodlevel_1800_2200mV		, 6
#define _hw_bodlevel_2000_2400mV		, 5
#define _hw_bodlevel_2200_2600mV		, 4
#define _hw_bodlevel_2400_2800mV		, 3
#define _hw_bodlevel_3200_3600mV		, 2
#define _hw_bodlevel_3300_3700mV		, 1
#define _hw_bodlevel_4000_4500mV		, 0

#if HW_IS(,HW_G2(_hw_bodlevel,HW_DEVICE_BROWNOUT_DETECTION))
#  define HW_DEVICE_FUSE_BODLEVEL	HW_A1(HW_G2(_hw_bodlevel,HW_DEVICE_BROWNOUT_DETECTION))
#else
#  error HW_DEVICE_BROWNOUT_DETECTION must be defined as `off` (default), `1800_2200mV`, `2000_2400mV`, `2200_2600mV`, `2400_2800mV`, `3200_3600mV`, `3300_3700mV`, or `4000_4500mV`
#endif
/*
 *	Fuse high byte
 */
#if !defined HW_DEVICE_ON_CHIP_DEBUG
#  define HW_DEVICE_ON_CHIP_DEBUG		disabled
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_ON_CHIP_DEBUG))
#  define HW_DEVICE_FUSE_OCDEN				\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_ON_CHIP_DEBUG))
#else
#  error HW_DEVICE_ON_CHIP_DEBUG must be defined as `enabled` or `disabled` (default).
#endif


#if !defined HW_DEVICE_JTAG
#  define HW_DEVICE_JTAG			enabled
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_JTAG))
#  define HW_DEVICE_FUSE_JTAGEN			\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_JTAG))
#else
#  error HW_DEVICE_JTAG must be defined as `enabled` (default) or `disabled`.
#endif


#if !defined HW_DEVICE_SPI
#  define HW_DEVICE_SPI				enabled
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_SPI))
#  define HW_DEVICE_FUSE_SPIEN			\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_SPI))
#else
#  error HW_DEVICE_SPI must be defined as `enabled` (default) or `disabled`.
#endif


#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON		no
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_WATCHDOG_ALWAYS_ON))
#  define HW_DEVICE_FUSE_WDTON				\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_WATCHDOG_ALWAYS_ON))
#else
#  error HW_DEVICE_WATCHDOG_ALWAYS_ON must be defined as `yes` or `no` (default).
#endif


#if !defined HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE	no
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE))
#  define HW_DEVICE_FUSE_EESAVE						\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE))
#else
#  error HW_DEVICE_PRESERVE_EEPROM_THROUGH_CHIP_ERASE must be defined as `yes` or `no` (default).
#endif


#if !defined HW_DEVICE_BOOTSECTION_SIZE
#  define HW_DEVICE_BOOTSECTION_SIZE		4096
#endif

#if HW_DEVICE_BOOTSECTION_SIZE == 512
#  define HW_DEVICE_FUSE_BOOTSZ			3
#elif HW_DEVICE_BOOTSECTION_SIZE == 1024
#  define HW_DEVICE_FUSE_BOOTSZ			2
#elif HW_DEVICE_BOOTSECTION_SIZE == 2048
#  define HW_DEVICE_FUSE_BOOTSZ			1
#elif HW_DEVICE_BOOTSECTION_SIZE == 4096
#  define HW_DEVICE_FUSE_BOOTSZ			0
#else
#  error HW_DEVICE_BOOTSECTION_SIZE must be `512`, `1024`, `2048`, or `4096` (default).
#endif


#if !defined HW_DEVICE_BOOT
#  define HW_DEVICE_BOOT				application
#endif

#define _hw_is_application_application			, 1
#define _hw_is_bootloader_bootloader			, 1

#if HW_IS(HW_DEVICE_BOOT, application)
#  define HW_DEVICE_FUSE_BOOTRST			1
#elif HW_IS(HW_DEVICE_BOOT, bootloader)
#  define HW_DEVICE_FUSE_BOOTRST			0
#else
#  error HW_DEVICE_BOOT must be defined as `bootloader` or `application` (default).
#endif


#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT			disabled
#endif

#if HW_IS(,HW_G2(_hw_state,HW_DEVICE_CLOCK_OUTPUT))
#  define HW_DEVICE_FUSE_CKOUT				\
  HW_A2(HW_G2(_hw_state,HW_DEVICE_CLOCK_OUTPUT))
#else
#  error HW_DEVICE_CLOCK_OUTPUT must be defined as `enabled` or `disabled` (default).
#endif


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page atmegaxu4
 * @section atmegaxu4_object Peripherals
 *
 * @note A missing class name means that the peripheral is not implemented yet.
 *
 * Object name		  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_core0`	 | @ref atmelavr_corec "_corec" | The core
 * `hw_portb`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port B (PORTB)
 * `hw_portc`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port C (PORTC)
 * `hw_portd`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port D (PORTD)
 * `hw_porte`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port D (PORTE)
 * `hw_portf`	 | @ref atmelavr_p8a "_p8a"	| General purpose I/O port D (PORTF)
 */

/* `hw_int0`	 | @ref atmelavr_inta "_inta"   | External interrupt INT0
 * `hw_int1`	 | @ref atmelavr_inta "_inta"   | External interrupt INT1
 * `hw_int0`	 | @ref atmelavr_inta "_inta"   | External interrupt INT0
 * `hw_int1`	 | @ref atmelavr_inta "_inta"   | External interrupt INT1
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
 */

/*
 * @page atmegaxu4
 * @subsection atmegaxu4_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name			  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_spimaster_swclk0`  | @ref atmelavr_usia_spimaster_swclk "usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `hw_swuart0`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 * `hw_swuart1`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 */

/* @subsection atmegaxu4_objrel Aliases and relations
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
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/corec_1.h"
#define _hw_core0			_corec, 101, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_core0_osccal		_r8, 0x66, 0xFF, 0x00
#define _hw_core0_sreg			_r8, 0x5F, 0xFF, 0x00
#define _hw_core0_sph			_r8, 0x5E, 0xFF, 0x00
#define _hw_core0_spl			_r8, 0x5D, 0xFF, 0x00
#define _hw_core0_mcucr			_r8, 0x55, 0x53, 0x00
#define _hw_core0_mcusr			_r8, 0x54, 0x1F, 0x00
#define _hw_core0_smcr			_r8, 0x53, 0x0F, 0x00

/*	Object logical registers
 */
#define _hw_core0_pud			_ob1, mcucr, 1, 4
#define _hw_core0_ivsel			_ob1, mcucr, 1, 1
#define _hw_core0_ivce			_ob1, mcucr, 1, 0

#define _hw_core0_usbrf			_ob1, mcusr, 1, 5
#define _hw_core0_jtrf			_ob1, mcusr, 1, 4
#define _hw_core0_wdrf			_ob1, mcusr, 1, 3
#define _hw_core0_borf			_ob1, mcusr, 1, 2
#define _hw_core0_extrf			_ob1, mcusr, 1, 1
#define _hw_core0_porf			_ob1, mcusr, 1, 0
#define _hw_core0_allrf			_ob1, mcusr, 6, 0	/* convenient */

#define _hw_core0_sm			_ob1, smcr, 3, 1
#define _hw_core0_se			_ob1, smcr, 1, 0


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page atmegaxu4
 * @section atmegaxu4_pins I/O ports and pins
 *
 * Some of the pins may not be available depending on the fuses configuration.
 *
 * HWA name	| 44Q         | Class			   | Atmel name
 * -------------|-------------|----------------------------|-----------
 * `hw_port_b`	|	      | @ref atmelavr_io1a "_io1a" | PORTB
 * `hw_pin_pb0` | `hw_pin_8`  | @ref atmelavr_io1a "_io1a" | PB0
 * `hw_pin_pb1` | `hw_pin_9`  | @ref atmelavr_io1a "_io1a" | PB1
 * `hw_pin_pb2` | `hw_pin_10` | @ref atmelavr_io1a "_io1a" | PB2
 * `hw_pin_pb3` | `hw_pin_11` | @ref atmelavr_io1a "_io1a" | PB3
 * `hw_pin_pb4` | `hw_pin_28` | @ref atmelavr_io1a "_io1a" | PB4
 * `hw_pin_pb5` | `hw_pin_29` | @ref atmelavr_io1a "_io1a" | PB5
 * `hw_pin_pb6` | `hw_pin_30` | @ref atmelavr_io1a "_io1a" | PB6
 * `hw_pin_pb7` | `hw_pin_12` | @ref atmelavr_io1a "_io1a" | PB7
 * `hw_port_c`	|	      | @ref atmelavr_io1a "_io1a" | PORTC
 * `hw_pin_pc6` | `hw_pin_31` | @ref atmelavr_io1a "_io1a" | PC6
 * `hw_pin_pc7` | `hw_pin_32` | @ref atmelavr_io1a "_io1a" | PC7
 * `hw_port_d`	|	      | @ref atmelavr_io1a "_io1a" | PORTD
 * `hw_pin_pd0` | `hw_pin_18` | @ref atmelavr_io1a "_io1a" | PD0
 * `hw_pin_pd1` | `hw_pin_19` | @ref atmelavr_io1a "_io1a" | PD1
 * `hw_pin_pd2` | `hw_pin_20` | @ref atmelavr_io1a "_io1a" | PD2
 * `hw_pin_pd3` | `hw_pin_21` | @ref atmelavr_io1a "_io1a" | PD3
 * `hw_pin_pd4` | `hw_pin_25` | @ref atmelavr_io1a "_io1a" | PD4
 * `hw_pin_pd5` | `hw_pin_22` | @ref atmelavr_io1a "_io1a" | PD5
 * `hw_pin_pd6` | `hw_pin_26` | @ref atmelavr_io1a "_io1a" | PD6
 * `hw_pin_pd7` | `hw_pin_27` | @ref atmelavr_io1a "_io1a" | PD7
 * `hw_port_e`	|	      | @ref atmelavr_io1a "_io1a" | PORTE
 * `hw_pin_pe2` | `hw_pin_33` | @ref atmelavr_io1a "_io1a" | PE2
 * `hw_pin_pe6` | `hw_pin_1`  | @ref atmelavr_io1a "_io1a" | PE6
 * `hw_port_f`	|	      | @ref atmelavr_io1a "_io1a" | PORTF
 * `hw_pin_pf0` | `hw_pin_41` | @ref atmelavr_io1a "_io1a" | PF0
 * `hw_pin_pf1` | `hw_pin_40` | @ref atmelavr_io1a "_io1a" | PF1
 * `hw_pin_pf4` | `hw_pin_39` | @ref atmelavr_io1a "_io1a" | PF4
 * `hw_pin_pf5` | `hw_pin_38` | @ref atmelavr_io1a "_io1a" | PF5
 * `hw_pin_pf6` | `hw_pin_37` | @ref atmelavr_io1a "_io1a" | PF6
 * `hw_pin_pf7` | `hw_pin_36` | @ref atmelavr_io1a "_io1a" | PF7
 */

/*	Objects				class, id, address
 */
#include "../classes/p8a_1.h"
#include "../classes/io1a_1.h"

#define _hw_portb			_p8a, 300, 0x23
#define _hw_portc			_p8a, 310, 0x26
#define _hw_portd			_p8a, 320, 0x29
#define _hw_porte			_p8a, 330, 0x2C
#define _hw_portf			_p8a, 340, 0x2F

/*  Pins				class, id, port, bn, bp
 */
#define _hw_pin_pb0			_io1a, 301, hw_portb, 1, 0
#define _hw_pin_pb1			_io1a, 302, hw_portb, 1, 1
#define _hw_pin_pb2			_io1a, 303, hw_portb, 1, 2
#define _hw_pin_pb3			_io1a, 304, hw_portb, 1, 3
#define _hw_pin_pb4			_io1a, 305, hw_portb, 1, 4
#define _hw_pin_pb5			_io1a, 306, hw_portb, 1, 5
#define _hw_pin_pb6			_io1a, 307, hw_portb, 1, 6
#define _hw_pin_pb7			_io1a, 308, hw_portb, 1, 7

#define _hw_pin_pd0			_io1a, 321, hw_portd, 1, 0
#define _hw_pin_pd1			_io1a, 322, hw_portd, 1, 1
#define _hw_pin_pd2			_io1a, 323, hw_portd, 1, 2
#define _hw_pin_pd3			_io1a, 324, hw_portd, 1, 3
#define _hw_pin_pd4			_io1a, 325, hw_portd, 1, 4
#define _hw_pin_pd5			_io1a, 326, hw_portd, 1, 5
#define _hw_pin_pd6			_io1a, 327, hw_portd, 1, 6
#define _hw_pin_pd7			_io1a, 328, hw_portd, 1, 7

/*  Communications
 */
#define hw_pin_scl			hw_pin_pd0
#define hw_pin_sda			hw_pin_pd1

#define hw_pin_txd			hw_pin_pd3
#define hw_pin_rxd			hw_pin_pd2

#if 0
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
#endif

/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#include "../classes/eeproma_1.h"

/*	Object				class, id, address
 */					
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__eeproma_ar			_r16, 0x41, 0x03FF, 0x00
#define _hw__eeproma_dr			_r8,  0x40,   0xFF, 0x00
#define _hw__eeproma_cr			_r8,  0x3F,   0x3F, 0x00


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

#include "../classes/flasha_1.h"

/*	Object				class, id, address
 */					
#define _hw_flash0			_flasha, 1100, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define _hw__flasha_csr			_r8, 0x57, 0xBF, 0x00


/*******************************************************************************
 *									       *
 *	H W A    C O N T E X T						       *
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

  hwa_corec_t	hw_core0 ;
  hwa_p8a_t	hw_portb ;
  hwa_p8a_t	hw_portc ;
  hwa_p8a_t	hw_portd ;
  hwa_p8a_t	hw_porte ;
  hwa_p8a_t	hw_portf ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/corec_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p8a_2.h"


HW_INLINE void _hwa_create_context( hwa_t *hwa )
{
  _hwa_create( hw_core0 );
  _hwa_create( hw_portb );
  _hwa_create( hw_portc );
  _hwa_create( hw_portd );
  _hwa_create( hw_porte );
  _hwa_create( hw_portf );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init( hw_core0 );
  _hwa_init( hw_portb );
  _hwa_init( hw_portc );
  _hwa_init( hw_portd );
  _hwa_init( hw_porte );
  _hwa_init( hw_portf );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit( hw_core0 );
  _hwa_commit( hw_portb );
  _hwa_commit( hw_portc );
  _hwa_commit( hw_portd );
  _hwa_commit( hw_porte );
  _hwa_commit( hw_portf );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page atmegaxu4
 * <br>
 */
