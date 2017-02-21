
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny25/45/85
 */

#include "../hwa_1.h"

/**
 * @page attinyx5 ATtiny25/45/85
 * @section attinyx5_device Description
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE_ATTINYX5`	    |Always defined (void)
 * `HW_DEVICE_ATTINY85`<br>`HW_DEVICE_ATTINY85_20PU` | Defined (void) depending on the HWA header included
 * `HW_DEVICE_PACKAGE_8P3`  |Defined (void) depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte: `0x0060`
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table): `0x001E`
 *
 * Symbol		       | ATtiny25     | ATtiny45     | ATtiny85	     
 * :---------------------------|:------------:|:------------:|:-------------:
 * `HW_DEVICE`		       |	      |		     |attiny85_20pu 
 * `HW_DEVICE_SIGNATURE`       |0x1E,0x91,0x08|0x1E,0x92,0x06|0x1E,0x93,0x0B
 * `HW_DEVICE_FLASH_SIZE`      |2048	      |4096	     |8192	    
 * `HW_DEVICE_FLASH_PAGE_SIZE` |32	      |32	     |64	    
 * `HW_DEVICE_EEPROM_SIZE`     |128	      |256	     |512
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4	      |4	     |4
 * `HW_DEVICE_RAM_SIZE`	       |128	      |256	     |512
 */
#define HW_DEVICE_ATTINYX5
#define HW_DEVICE_RAM_START		0x0060
#define HW_DEVICE_APP_START		0x001E


/**
 * @page attinyx5
 * @section attinyx5_fuses Fuses
 *
 * ATtinyX5 devices hold 3 fuse bytes describing their hardware configuration.
 * HWA computes the value of these fuse bytes from the fuse values (detailed in
 * the following subsections) that must be defined prior to including the HWA
 * header. Undefined fuse values are replaced by factory default values.
 *
 * Symbol		| Comments
 * :--------------------|:-----------
 * `HW_DEVICE_FUSE_EB`	| Fuse extended byte
 * `HW_DEVICE_FUSE_HB`	| Fuse high byte
 * `HW_DEVICE_FUSE_LB`	| Fuse low byte
 */
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


/**
 * @page attinyx5
 * @subsection attinyx5_fuses_clocking Clocking
 *
 * Symbol		 |Valid values | Comments
 * :---------------------|-------------|:-----------
 * `HW_DEVICE_CLK_SRC`	 |`external`<br>`rc_pll_16MHz`<br><b>`rc_8MHz`</b><br>`rc_1600kHz`<br>`rc_128kHz`<br>`low_freq_xosc`<br>`xosc`|External source on pin CLKI<br>Internal RC oscillator (PLL)<br>Internal RC oscillator<br>Internal RC oscillator<br>Internal RC oscillator (watchdog)<br>Crystal/resonator oscillator between pins XTAL1 and XTAL2<br> <br>
 * `HW_DEVICE_CLK_SRC_HZ`|Integer     |Clock frequency for `external`, `low_freq_xosc`, and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`	 |<b>`8`</b><br>`1`|Clock divided by 8<br>Clock not divided
 */
#define _hw_is_external_external		, 1
#define _hw_is_rc_pll_16MHz_rc_pll_16MHz	, 1
#define _hw_is_rc_8MHz_rc_8MHz			, 1
#define _hw_is_rc_1600kHz_rc_1600kHz		, 1
#define _hw_is_rc_128kHz_rc_128kHz		, 1
#define _hw_is_low_freq_xosc_low_freq_xosc	, 1
#define _hw_is_xosc_xosc			, 1

#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC			rc_8MHz
#endif

#if HW_IS(HW_DEVICE_CLK_SRC, external)
#  define HW_DEVICE_CKSEL31			0
#  define HW_DEVICE_CKSEL0			0
#elif HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define HW_DEVICE_CKSEL31			0
#  define HW_DEVICE_CKSEL0			1
#  define hw_syshz_base				16000000
#elif HW_IS(HW_DEVICE_CLK_SRC, rc_8MHz)
#  define HW_DEVICE_CKSEL31			1
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				8000000
#elif HW_IS(HW_DEVICE_CLK_SRC, rc_1600kHz)
#  define HW_DEVICE_CKSEL31			1
#  define HW_DEVICE_CKSEL0			1
#  define hw_syshz_base				1600000
#elif HW_IS(HW_DEVICE_CLK_SRC, rc_128kHz)
#  define HW_DEVICE_CKSEL31			2
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define HW_DEVICE_CKSEL31			3
#  define HW_DEVICE_CKSEL0			0
#  define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#elif HW_IS(HW_DEVICE_CLK_SRC, xosc)
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_CKSEL31			4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_CKSEL31			5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_CKSEL31			6
#  else
#    define HW_DEVICE_CKSEL31			7
#  endif
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined when HW_DEVICE_CLK_SRC is `xosc`.
#  endif
#  define hw_syshz_base			      HW_DEVICE_CLK_SRC_HZ
#else
#  error HW_DEVICE_CLK_SRC can be `external`, `rc_8MHz`, `rc_128kHz`, `low_freq_xosc`, or `xosc`.
#endif

#if !defined HW_DEVICE_CLK_PSC
#  define HW_DEVICE_CLK_PSC			8
#endif
#if HW_DEVICE_CLK_PSC == 8
#  define HW_DEVICE_CKDIV8			0
#  define hw_syshz				hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_CKDIV8			1
#  define hw_syshz				hw_syshz_base
#else
#  error HW_DEVICE_CLK_PSC can be `8`, or `1`.
#endif


/**
 * @page attinyx5
 * @subsection attinyx5_fuses_sut Startup delays
 *
 * Symbol		| Valid values | Comments
 * :--------------------|--------------|:-----------
 * `HW_DEVICE_STARTUP_DELAYS` | `6CK_14CK`<br>`6CK_14CK_4ms`<br>`6CK_14CK_64ms`<br>`1KCK_4ms`<br>`1KCK_64ms`<br>`32KCK_64ms`<br>`258CK_14CK_4ms`<br>`258CK_14CK_64ms`<br>`1KCK_14CK`<br>`1KCK_14CK_4ms`<br>`1KCK_14CK_64ms`<br>`16KCK_14CK`<br>`16KCK_14CK_4ms`<br>`16KCK_14CK_64ms` | Valid values depend on the clocking configuration
*/
#define HW_DEVICE_CKSEL				(2*HW_DEVICE_CKSEL31+HW_DEVICE_CKSEL0)

/*  Fuse: startup delays
 */
#if !defined HW_DEVICE_STARTUP_DELAYS
#  define HW_DEVICE_SUT10			2
#else

#  if HW_DEVICE_CKSEL == 0 /* external */
#    define _hw_sut_6CK_14CK			, 0
#    define _hw_sut_6CK_14CK_4ms		, 1
#    define _hw_sut_6CK_14CK_64ms		, 2
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `external`, HW_DEVICE_STARTUP_DELAYS must be\
 `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL == 1 /* rc_pll_16MHz */
#    define _hw_sut_14CK_1KCK_4ms		, 0
#    define _hw_sut_14CK_16KCK_4ms		, 1
#    define _hw_sut_14CK_1KCK_64ms		, 2
#    define _hw_sut_14CK_16KCK_64ms		, 3
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `rc_pll_16MHz`, HW_DEVICE_STARTUP_DELAYS must be\
 `14CK_1KCK_4ms`, `14CK_16KCK_4ms`, `14CK_1KCK_64ms`, or `14CK_16KCK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL == 2 /* rc_8MHz */
#    define _hw_sut_6CK_14CK			, 0
#    define _hw_sut_6CK_14CK_4ms		, 1
#    define _hw_sut_6CK_14CK_64ms		, 2
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `rc_8MHz`, HW_DEVICE_STARTUP_DELAYS must be\
 `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL == 3 /* rc_1600kHz */
#    define _hw_sut_6CK_14CK_64ms		, 0
#    define _hw_sut_6CK_14CK_4ms		, 2
#    define _hw_sut_1CK_14CK			, 3
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `rc_1600kHz`, HW_DEVICE_STARTUP_DELAYS must be\
 `1CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL == 4 /* rc_128kHz */
#    define _hw_sut_6CK_14CK			, 0
#    define _hw_sut_6CK_14CK_4ms		, 1
#    define _hw_sut_6CK_14CK_64ms		, 2
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `rc_128kHz`, HW_DEVICE_STARTUP_DELAYS must be\
 `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL == 6 /* low_freq_xosc */
#    define _hw_sut_1KCK_4ms			, 0
#    define _hw_sut_1KCK_64ms			, 1
#    define _hw_sut_32KCK_64ms			, 2
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `low_freq_xosc`, HW_DEVICE_STARTUP_DELAYS must be\
 `1KCK_4ms`, `1KCK_64ms`, or `32KCK_64ms`.
#    endif

#  elif HW_DEVICE_CKSEL31 > 3 /* xosc */     /* , CKSEL0, SUT10 */
#    define _hw_sut_258CK_14CK_4ms		, 0, 0
#    define _hw_sut_258CK_14CK_64ms		, 0, 1
#    define _hw_sut_1KCK_14CK			, 0, 2
#    define _hw_sut_1KCK_14CK_4ms		, 0, 3
#    define _hw_sut_1KCK_14CK_64ms		, 1, 0
#    define _hw_sut_16KCK_14CK			, 1, 1
#    define _hw_sut_16KCK_14CK_4ms		, 1, 2
#    define _hw_sut_16KCK_14CK_64ms		, 1, 3
#    if HW_IS(,HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_CKSEL0	HW_A1(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#      define HW_DEVICE_SUT10	HW_A2(HW_G2(_hw_sut,HW_DEVICE_STARTUP_DELAYS))
#    else
#      error When CLK_SRC is `xosc`, HW_DEVICE_STARTUP_DELAYS must be\
 `258CK_14CK_4ms`, `258CK_14CK_64ms`, `1KCK_14CK`, `1KCK_14CK_4ms`,\
 `1KCK_14CK_64ms`, `16KCK_14CK`, `16KCK_14CK_4ms`, or `16KCK_14CK_64ms`.
#    endif
#  else
#    error
#  endif
#endif


/**
 * @page attinyx5
 * @subsection attinyx5_fuses_other Other fuses
 *
 * Symbol		  | Valid values | Comments
 * :----------------------|--------------|:-----------
 * `HW_DEVICE_SELF_PROGRAMMING`	 |<b>`enabled`</b><br>`disabled`|Whether the device can write into its Flash program memory
 * `HW_DEVICE_EXTERNAL_RESET`	 |<b>`enabled`</b><br>`disabled`|Whether the device can be reset via its RESET pin
 * `HW_DEVICE_DEBUG_WIRE`	 |`enabled`<br><b>`disabled`</b>|Whether the Debug Wire is operationnal
 * `HW_DEVICE_SERIAL_PROGRAMMING`|<b>`enabled`</b><br>`disabled`|Whether the device can be programmed via the SPI
 * `HW_DEVICE_WATCHDOG_ALWAYS_ON`|`yes`<br><b>`no`</b>		|Whether the watchdog is always running
 * `HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE`|`enabled`<br><b>`disabled`</b>|Whether the EEPROM memory is erased when a chip erase occurs
 * `HW_DEVICE_BROWNOUT_DETECTION`|<b>`off`</b><br>`1700_2000mV`<br>`2500_2900mV`<br>`4100_4500mV`|Brown-out detection level
 * `HW_DEVICE_CLOCK_OUTPUT`	 |<b>`disabled`</b><br>`enabled`|Whether the device outputs its clock
 */
#if !defined HW_DEVICE_SELF_PROGRAMMING
#  define HW_DEVICE_SELF_PROGRAMMING		enabled
#endif
#if HW_IS(HW_DEVICE_SELF_PROGRAMMING, enabled)
#  define HW_DEVICE_SELFPRGEN			0
#elif HW_IS(HW_DEVICE_SELF_PROGRAMMING, disabled)
#  define HW_DEVICE_SELFPRGEN			1
#else
#  error HW_DEVICE_SELF_PROGRAMMING can be `enabled` or `disabled` (default).
#endif


#if !defined HW_DEVICE_EXTERNAL_RESET
#  define HW_DEVICE_EXTERNAL_RESET		enabled
#endif
#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_RSTDISBL			1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_RSTDISBL			0
#else
#  error HW_DEVICE_EXTERNAL_RESET can be `enabled` (default) or `disabled`.
#endif


#if !defined HW_DEVICE_DEBUG_WIRE
#  define HW_DEVICE_DEBUG_WIRE			disabled
#endif
#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_DWEN			0
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_DWEN			1
#else
#  error HW_DEVICE_DEBUG_WIRE can be `enabled` or `disabled` (default).
#endif


#if !defined HW_DEVICE_SERIAL_PROGRAMMING
#  define HW_DEVICE_SERIAL_PROGRAMMING		enabled
#endif
#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_SPIEN			0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_SPIEN			1
#else
#  error HW_DEVICE_SERIAL_PROGRAMMING can be `enabled` (default) or `disabled`.
#endif


#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON		no
#endif
#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_WDTON			0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_WDTON			1
#else
#  error HW_DEVICE_WATCHDOG_ALWAYS_ON can be `yes` or `no` (default).
#endif


#if !defined HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE		no
#endif
#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, yes)
#  define HW_DEVICE_EESAVE					0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, no)
#  define HW_DEVICE_EESAVE					1
#else
#  error HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE can be `yes` or `no` (default).
#endif


#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION			off
#endif

#define _hw_bod_1700_2000mV				, 6
#define _hw_bod_2500_2900mV				, 5
#define _hw_bod_4100_4500mV				, 4
#define _hw_bod_off					, 7

#if HW_IS(,HW_G2(_hw_bod,HW_DEVICE_BROWNOUT_DETECTION))
#  define HW_DEVICE_BODLEVEL	HW_A1(HW_G2(_hw_bod,HW_DEVICE_BROWNOUT_DETECTION))
#else
#  error HW_DEVICE_BROWNOUT_DETECTION can be `1700_2000mV`, `2500_2900mV`,\
  `4100_4500mV`, or `off` (default).
#endif


#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT		disabled
#endif
#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_CKOUT			0
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_CKOUT			1
#else
#  error HW_DEVICE_CLOCK_OUTPUT can be `enabled` or `disabled` (default).
#endif

#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz) && HW_DEVICE_BODLEVEL==6
#  HW_ERROR(`pll_64MHz` is not available with supply voltages below 2.7 V)
#endif


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx5
 * @section attinyx5_objects Peripherals
 * 
 * Object name			     |Class			  | Comments
 * :---------------------------------|----------------------------|:--------------------------------------
 * `hw_acmp0`	|@ref atmelavr_acmpb "_acmpb"| Analog Comparator
 * `hw_adc0`	|@ref atmelavr_ad10c "_ad10c"| 10-bit Analog to Digital Converter
 * `hw_core0`	|@ref atmelavr_corea "_corea"| The core
 * `hw_int0`	|@ref atmelavr_inta "_inta"  | External interrupt INT0
 * `hw_psc0`	|@ref atmelavr_psca "_psca"  | Counter 0 prescaler
 * `hw_counter0`|@ref atmelavr_c8a "_c8a"    | 8-bit counter-timer (T0)
 * `hw_oc00`	|@ref atmelavr_oc8a "_oc8a"    | Compare unit 0 of hw_counter0 (OC0A)
 * `hw_oc01`	|@ref atmelavr_oc8a "_oc8a"    | Compare unit 1 of hw_counter0 (OC0B)
 * `hw_psc1`	|@ref atmelavr_pscb "_pscb"  | Counter 1 prescaler
 * `hw_counter1`|@ref atmelavr_c8b "_c8b"    | 8-bit counter-timer (T1)
 * `hw_oc10`	|@ref atmelavr_oc8b "_oc8b"  | Compare unit 0 of hw_counter1 (OC1A)
 * `hw_oc11`	|@ref atmelavr_oc8b "_oc8b"  | Compare unit 1 of hw_counter1 (OC1B)
 * `hw_dtg1`	|@ref atmelavr_dtga "_dtga"  | Dead time generator for `hw_counter1` compare outputs
 * `hw_eeprom0` |@ref atmelavr_eeproma "_eeproma"| Eeprom memory
 * `hw_flash0`	|@ref atmelavr_flasha "_flasha"	 | Flash memory
 * `hw_pcic0`	|@ref atmelavr_pcica "_pcica"| Pin change interrupt controller
 * `hw_portb`	|@ref atmelavr_p8a "_p8a"  | General purpose I/O port B (PORTB)
 * `hw_usi0`	|@ref atmelavr_usia "_usia"  | Universal Serial Interface
 * `hw_wdog0`	|@ref atmelavr_wdoga "_wdoga"| Watchdog (WDG)
 *
 * @subsection attinyx5_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name			  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_spimaster_swclk0`  | @ref atmelavr_usia_spimaster_swclk "usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `hw_swuart0`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 * `hw_swuart1`		  | @ref atmelavr_swuarta "swuarta" | Software UART
 *
 * @subsection attinyx5_objrel Aliases and relations
 *
 * Some objects can be accessed from their @ref using_relatives "relatives" or
 * can have more than one name. There are the existing relations between the
 * device's objects and their different names:
 *
 * Name		 | Aliases		 | Relations
 * :-------------|-----------------------|:--------------------------------------
 * `hw_psc0`	 | `hw_counter0prescaler`  | `HW_REL(hw_counter0, prescaler)`
 * `hw_psc0`	 | `hw_counter0prescaler0` | `HW_REL(hw_counter0, prescaler0)`
 * `hw_psc0`	 | `hw_counter1prescaler`  | `HW_REL(hw_counter1, prescaler)`
 * `hw_psc0`	 | `hw_counter1prescaler0` | `HW_REL(hw_counter1, prescaler0)`
 * `hw_oc00`	 | `hw_counter0compare0`   | `HW_REL(hw_counter0, compare0)`
 * `hw_oc01`	 | `hw_counter0compare1`   | `HW_REL(hw_counter0, compare1)`
 * `hw_counter0` | `hw_oc00counter`	   | `HW_REL(hw_oc00, counter)`
 * `hw_counter0` | `hw_oc01counter`	   | `HW_REL(hw_oc01, counter)`
 * `hw_pin_oc00` | `hw_oc00pin`		   | `HW_REL(hw_oc00, pin)`
 * `hw_pin_oc01` | `hw_oc01pin`		   | `HW_REL(hw_oc01, pin)`
 * `hw_oc10`	 | `hw_counter1compare0`   | `HW_REL(hw_counter1, compare0)`
 * `hw_oc11`	 | `hw_counter1compare1`   | `HW_REL(hw_counter1, compare1)`
 * `hw_counter1` | `hw_oc10counter`	   | `HW_REL(hw_oc10, counter)`
 * `hw_counter1` | `hw_oc11counter`	   | `HW_REL(hw_oc11, counter)`
 * `hw_pin_oc10` | `hw_oc10pin`		   | `HW_REL(hw_oc10, pin)`
 * `hw_pin_oc11` | `hw_oc11pin`		   | `HW_REL(hw_oc11, pin)`
 * `hw_dtg1`	 | `hw_counter1dtg0`	   | `HW_REL(hw_counter1, dtg)`<br>`HW_REL(hw_counter1, dtg0)`
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx5
 * @section attinyx5_irqs Interrupts
 * 
 * Interrupt name						| Atmel label | Comments
 * :------------------------------------------------------------|-------------|------------------------
 * `hw_acmp0`							| ANA_COMP    | Analog comparator
 * `hw_adc0`							| ADC	      | ADC conversion complete
 * `hw_core0,int0`						| INT0	      | External interrupt INT0
 * `hw_counter0`<br>`hw_counter0,overflow`			| TIM0_OVF    | Counter 0 overflow
 * `hw_counter0,compare0`<br>`hw_counter0compare0`<br>`hw_oc00` | TIM0_COMPA  | Compare-match A on counter 0
 * `hw_counter0,compare1`<br>`hw_counter0compare1`<br>`hw_oc01` | TIM0_COMPB  | Compare-match B on counter 0
 * `hw_counter1`<br>`hw_counter1,overflow`			| TIM1_OVF    | Counter 1 overflow
 * `hw_counter1,compare0`					| TIM1_COMPA  | Compare-match A on counter 1
 * `hw_counter1,compare1`					| TIM1_COMPB  | Compare-match B on counter 1
 * `hw_eeprom0`<br>`hw_eeprom0,ready`				| EE_RDY      | EEPROM ready
 * `hw_pcic0`<br>`hw_pin_*,change`				| PCINT0      | Pin-change interrupt
 * `hw_usi0,overflow`<br>`hw_usi0,txc`				| USI_OVF     | USI overflow
 * `hw_usi0,start`						| USI_STR     | USI start
 * `hw_wdog0`							| WDT	      | Watchdog timeout
 */
#define _hw_irq_hw_int0_		_irq, hw_core0,     1, ie,    if
#define _hw_irq_hw_pcic0_		_irq, hw_pcic0,     2, ie,    if
#define _hw_irq_hw_counter1_compare0	_irq, hw_oc10,      3, ie,    if
#define _hw_irq_hw_oc10_		_irq, hw_oc10,      3, ie,    if
#define _hw_irq_hw_counter1_		_irq, hw_counter1,  4, ie,    if
#define _hw_irq_hw_counter1_overflow	_irq, hw_counter1,  4, ie,    if
#define _hw_irq_hw_counter0_		_irq, hw_counter0,  5, ie,    if
#define _hw_irq_hw_counter0_overflow	_irq, hw_counter0,  5, ie,    if
#define _hw_irq_hw_eeprom0_		_irq, hw_eeprom0,   6, ie, /* no irq flag */
#define _hw_irq_hw_eeprom0_ready	_irq, hw_eeprom0,   6, ie,
#define _hw_irq_hw_acmp0_		_irq, hw_acmp0,     7, ie,    if
#define _hw_irq_hw_adc0_		_irq, hw_adc0,      8, ie,    if
#define _hw_irq_hw_counter1_compare1	_irq, hw_oc11,      9, ie,    if
#define _hw_irq_hw_counter0_compare0	_irq, hw_oc00,     10, ie,    if
#define _hw_irq_hw_oc00_		_irq, hw_oc00,     10, ie,    if
#define _hw_irq_hw_counter0_compare1	_irq, hw_oc01,     11, ie,    if
#define _hw_irq_hw_oc01_		_irq, hw_oc01,     11, ie,    if
#define _hw_irq_hw_wdog0_		_irq, hw_wdog0,    12, ie,    if
#define _hw_irq_hw_usi0_start		_irq, hw_usi0,     13, ies,   ifs
#define _hw_irq_hw_usi0_overflow	_irq, hw_usi0,     14, ieov,  ifov
#define _hw_irq_hw_usi0_txc		_irq, hw_usi0,     14, ieov,  ifov


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by other objects						       *
 *									       *
 *******************************************************************************/

#define _hw_class__shared
#define _hw_obj_hw_shared		_shared, 0, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_shared_gimsk		_r8, 0x5B, 0x60, 0x00
#define _hw_shared_gifr			_r8, 0x5A, 0x60, 0x60
#define _hw_shared_timsk		_r8, 0x59, 0x7E, 0x00
#define _hw_shared_tifr			_r8, 0x58, 0x7E, 0x7E
#define _hw_shared_gtccr		_r8, 0x4C, 0xFF, 0x00
#define _hw_shared_prr			_r8, 0x40, 0x0F, 0x00
#define _hw_shared_gpior2		_r8, 0x33, 0xFF, 0x00
#define _hw_shared_gpior1		_r8, 0x32, 0xFF, 0x00
#define _hw_shared_gpior0		_r8, 0x31, 0xFF, 0x00
#define _hw_shared_did			_r8, 0x34, 0x3F, 0x00


#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	gimsk ;
  hwa_r8_t	gifr ;
  hwa_r8_t	timsk ;
  hwa_r8_t	tifr ;
  hwa_r8_t	gtccr ;
  hwa_r8_t	prr ;
  hwa_r8_t	did ;
} hwa_shared_t ;

#endif


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx5
 * @section attinyx5_pins Ports and pins
 *
 * Some of the pins `hw_pin_pb0`..`hw_pin_pb3` may not be available depending on
 * the fuses configuration.
 *
 * HWA name    | 8P3	  | Class		      | Atmel name
 * ------------|----------|---------------------------|-----------
 * `hw_port_b` |	  | @ref atmelavr_p8a "p8a"    | -
 * `hw_pin_pb0`|`hw_pin_5`| @ref atmelavr_io1a "_io1a" | PB0
 * `hw_pin_pb1`|`hw_pin_6`| @ref atmelavr_io1a "_io1a" | PB1
 * `hw_pin_pb2`|`hw_pin_7`| @ref atmelavr_io1a "_io1a" | PB2
 * `hw_pin_pb3`|`hw_pin_2`| @ref atmelavr_io1a "_io1a" | PB3
 * `hw_pin_pb4`|`hw_pin_3`| @ref atmelavr_io1a "_io1a" | PB4
 * `hw_pin_pb5`|`hw_pin_1`| @ref atmelavr_io1a "_io1a" | PB5
 */
#include "../classes/p8a_1.h"
#include "../classes/io1a_1.h"

#define _hw_obj_hw_portb		_p8a, 300, 0x36

#define _hw_obj_hw_port_b		_io1a, 309, hw_portb, 6, 0
#define _hw_obj_hw_pin_pb0		_io1a, 301, hw_portb, 1, 0
#define _hw_obj_hw_pin_pb1		_io1a, 302, hw_portb, 1, 1
#define _hw_obj_hw_pin_pb2		_io1a, 303, hw_portb, 1, 2
#define _hw_obj_hw_pin_pb3		_io1a, 304, hw_portb, 1, 3
#define _hw_obj_hw_pin_pb4		_io1a, 305, hw_portb, 1, 4
#if HW_DEVICE_RSTDISBL == 0
#  define _hw_obj_hw_pin_pb5		_io1a, 306, hw_portb, 1, 5
#endif

/*  Alternate pin functions
 */
#define hw_pin_oc0a			hw_pin_pb0
#define hw_pin_oc0b			hw_pin_pb1

#define hw_pin_oc1a			hw_pin_pb1
#define hw_pin_oc1an			hw_pin_pb0
#define hw_pin_oc1b			hw_pin_pb4
#define hw_pin_oc1bn			hw_pin_pb3

#define hw_pin_usck			hw_pin_pb2
#define hw_pin_do			hw_pin_pb1
#define hw_pin_di			hw_pin_pb0

#define hw_pin_adc0			hw_pin_pb5
#define hw_pin_adc1			hw_pin_pb2
#define hw_pin_adc2			hw_pin_pb4
#define hw_pin_adc3			hw_pin_pb3
#define hw_pin_ain1			hw_pin_pb1
#define hw_pin_ain0			hw_pin_pb0

/*  Digital input disable bits for analog input pins
 */
#define _hw_reg_hw_pin_pb5_did		_xob1, hw_shared, did, 1, 5	/* ADC0 */
#define _hw_reg_hw_pin_pb2_did		_xob1, hw_shared, did, 1, 4	/* ADC1 */
#define _hw_reg_hw_pin_pb4_did		_xob1, hw_shared, did, 1, 3	/* ADC2 */
#define _hw_reg_hw_pin_pb3_did		_xob1, hw_shared, did, 1, 2	/* ADC3 */
#define _hw_reg_hw_pin_pb1_did		_xob1, hw_shared, did, 1, 1	/* AIN1 */
#define _hw_reg_hw_pin_pb0_did		_xob1, hw_shared, did, 1, 0	/* AIN0 */

/*  Relative pin change controllers
 */
#define hw_pin_pb0pcic			hw_pcic0
#define hw_pin_pb1pcic			hw_pcic0
#define hw_pin_pb2pcic			hw_pcic0
#define hw_pin_pb3pcic			hw_pcic0
#define hw_pin_pb4pcic			hw_pcic0
#define hw_pin_pb5pcic			hw_pcic0

/*  Pin numbers
 */
#if defined HW_DEVICE_PACKAGE_8P3
#  define hw_pin_1			hw_pin_pb5
#  define hw_pin_2			hw_pin_pb3
#  define hw_pin_3			hw_pin_pb4
#  define hw_pin_5			hw_pin_pb0
#  define hw_pin_6			hw_pin_pb1
#  define hw_pin_7			hw_pin_pb2
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/corea_1.h"
#define _hw_obj_hw_core0		 _corea, 101, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__corea_sreg			_r8, 0x5F, 0xFF, 0x00
#define _hw__corea_sph			_r8, 0x5E, 0x03, 0x00
#define _hw__corea_spl			_r8, 0x5D, 0xFF, 0x00

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_core0_mcucr			_r8, 0x55, 0xFF, 0x00
#define _hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define _hw_core0_osccal		_r8, 0x51, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_core0_bods			_ob1, mcucr, 1, 7
#define _hw_core0_pud			_ob1, mcucr, 1, 6
#define _hw_core0_se			_ob1, mcucr, 1, 5
#define _hw_core0_sm			_ob1, mcucr, 2, 3
#define _hw_core0_bodse			_ob1, mcucr, 1, 2
#define _hw_core0_isc0			_ob1, mcucr, 2, 0

#define _hw_core0_wdrf			_ob1, mcusr, 1, 3
#define _hw_core0_borf			_ob1, mcusr, 1, 2
#define _hw_core0_extrf			_ob1, mcusr, 1, 1
#define _hw_core0_porf			_ob1, mcusr, 1, 0
#define _hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */


/*******************************************************************************
 *									       *
 *	External interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/inta_1.h"
#define _hw_obj_hw_int0			_inta, 110, 0

#define _hw_int0_sc			_xob1, hw_core0,  mcucr, 2, 0
#define _hw_int0_ie			_xob1, hw_shared, gimsk, 1, 6
#define _hw_int0_if			_xob1, hw_shared, gifr,	 1, 6


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/pcica_1.h"
#define _hw_obj_hw_pcic0		_pcica, 350, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic0_msk			_r8, 0x35, 0x3F, 0x00

/*	Object logical registers
 */
#define _hw_pcic0_ie			_xob1, hw_shared, gimsk, 1, 5
#define _hw_pcic0_if			_xob1, hw_shared, gifr,	 1, 5


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/wdoga_1.h"
#define _hw_obj_hw_wdog0		_wdoga, 901, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__wdoga_csr			_r8, 0x41, 0xFF, 0x80

/*	Class logical registers
 */
#define _hw__wdoga_if			_cb1, csr, 1, 7
#define _hw__wdoga_ie			_cb1, csr, 1, 6
#define _hw__wdoga_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw__wdoga_wdce			_cb1, csr, 1, 4
#define _hw__wdoga_wde			_cb1, csr, 1, 3

#define _hw__wdoga_eie			_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw__wdoga_ifie			_cb1, csr, 2, 6 /* convenient for clearing irq */

#define _hw__wdoga_wdrf			_xob1, hw_core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c8a_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_counter0		_c8a, 400, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter0_ccra		_r8, 0x4A, 0xF3, 0x00
#define _hw_counter0_ccrb		_r8, 0x53, 0xCF, 0x00
#define _hw_counter0_count		_r8, 0x52, 0xFF, 0x00
#define _hw_counter0_imsk		_r8, -1, 0, 0	/* For compatibility */
#define _hw_counter0_ifr		_r8, -1, 0, 0

/*	Object logical registers
 */
#define _hw_counter0_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_counter0_cs			_ob1, ccrb, 3, 0
#define _hw_counter0_ie			_xob1, hw_shared, timsk, 1, 1
#define _hw_counter0_if			_xob1, hw_shared, tifr,	 1, 1

/*	Relatives
 */
#define hw_counter0prescaler0		hw_psc0
#define hw_counter0prescaler		hw_psc0
#define hw_counter0compare0		hw_oc00
#define hw_counter0compare1		hw_oc01



/*******************************************************************************
 *									       *
 *	Counter 0 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psca_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_psc0		_psca, 401, 0

/*	Object logical registers
 */
#define _hw_psc0_tsm			_xob1, hw_shared, gtccr, 1, 7
#define _hw_psc0_psr			_xob1, hw_shared, gtccr, 1, 0

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define _hw_psc0_tsmpsr			_xob2, hw_shared, gtccr, 1, 7, 1, gtccr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	Counter 0 compare units OCR0A and OCR0B				       *
 *									       *
 *******************************************************************************/

#include "../classes/oc8a_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_oc00			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc00_reg			_r8, 0x49, 0xFF, 0x00	/* OCR0A */

/*	Object logical registers
 */
#define _hw_oc00_com			_xob1, hw_counter0, ccra, 2, 6
#define _hw_oc00_force			_xob1, hw_counter0, ccrb, 1, 7
#define _hw_oc00_ie			_xob1, hw_shared, timsk, 1, 4
#define _hw_oc00_if			_xob1, hw_shared, tifr,	 1, 4

/*	Relatives
 */
#define hw_oc00pin			hw_pin_oc0a
#define hw_oc00counter			hw_counter0


/*	Object				class, id, address
 */
#define _hw_obj_hw_oc01			_oc8a, 403, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc01_reg			_r8, 0x48, 0xFF, 0x00	/* OCR0B */

/*	Object logical registers
 */
#define _hw_oc01_com			_xob1, hw_counter0, ccra, 2, 4
#define _hw_oc01_force			_xob1, hw_counter0, ccrb, 1, 6
#define _hw_oc01_ie			_xob1, hw_shared, imsk, 1, 3
#define _hw_oc01_if			_xob1, hw_shared, ifr,	1, 3

/*	Relatives
 */
#define hw_oc01pin			hw_pin_oc0b
#define hw_oc01counter			hw_counter0


/*******************************************************************************
 *									       *
 *	Timer/Counter 1 counting unit					       *
 *									       *
 *******************************************************************************/

#include "../classes/c8b_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_counter1		_c8b, 500, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter1_ccr		_r8, 0x50, 0xFF, 0x00	/* TCCR1 */
#define _hw_counter1_count		_r8, 0x4F, 0xFF, 0x00	/* TCNT1 */
#define _hw_counter1_compare2		_r8, 0x4D, 0xFF, 0x00	/* OCR1C */

/*	Object logical registers
 */
#define _hw_counter1_ctc		_ob1, ccr, 1, 7
#define _hw_counter1_cs			_ob1, ccr, 4, 0

#define _hw_counter1_ie			_xob1, hw_shared, timsk, 1, 2
#define _hw_counter1_if			_xob1, hw_shared, tifr, 1, 2

/*	Relatives
 */
#define hw_counter1prescaler		hw_psc1
#define hw_counter1prescaler0		hw_psc1
#define hw_counter1compare0		hw_oc10
#define hw_counter1compare1		hw_oc11
#define hw_counter1compare2		hw_oc12
#define hw_counter1dtg			hw_dtg1
#define hw_counter1dtg0			hw_dtg1


/*******************************************************************************
 *									       *
 *	Counter 1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/pscb_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_psc1			_pscb, 501, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_psc1_pllcsr			_r8, 0x47, 0x86, 0x00	/* PLLCSR */

/*	Object logical registers
 */
#define _hw_psc1_psr			_xob1, hw_shared, gtccr, 1, 1

#define _hw_psc1_lsm			_ob1, pllcsr, 1, 7
#define _hw_psc1_pcke			_ob1, pllcsr, 1, 2
#define _hw_psc1_plle			_ob1, pllcsr, 1, 1
#define _hw_psc1_plock			_ob1, pllcsr, 1, 0


/*******************************************************************************
 *									       *
 *	Counter 1 compare units OCR1A OCR1B				       *
 *									       *
 *******************************************************************************/

#include "../classes/oc8b_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_oc10			_oc8b, 502, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc10_reg			_r8, 0x4E, 0xFF, 0x00	/* OCR1A */

/*	Object logical registers
 */
#define _hw_oc10_pwm			_xob1, hw_counter1, ccr,  1, 6
#define _hw_oc10_mode			_xob1, hw_counter1, ccr,  2, 4
#define _hw_oc10_force			_xob1, hw_counter1, ccr,  1, 2
#define _hw_oc10_ie			_xob1, hw_shared, timsk, 1, 6
#define _hw_oc10_if			_xob1, hw_shared, tifr,	 1, 6

/*	Relatives
 */
#define hw_oc10pin			hw_pin_oc1a
#define hw_oc10pin_h			hw_pin_oc1a
#define hw_oc10pin_l			hw_pin_oc1an
#define hw_oc10counter			hw_counter1

/*	Object				class, id, address
 */
#define _hw_obj_hw_oc11			_oc8b, 503, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc11_reg			_r8, 0x4B, 0xFF, 0x00	/* OCR1B */

/*	Object logical registers
 */
#define _hw_oc11_pwm			_xob1, hw_shared, gtccr, 1, 6
#define _hw_oc11_mode			_xob1, hw_shared, gtccr, 2, 4
#define _hw_oc11_force			_xob1, hw_shared, gtccr, 1, 3
#define _hw_oc11_ie			_xob1, hw_shared, timsk,  1, 5
#define _hw_oc11_if			_xob1, hw_shared, tifr,	  1, 5

/*	Relatives
 */
#define hw_oc11pin			hw_pin_oc1b
#define hw_oc11pin_h			hw_pin_oc1b
#define hw_oc11pin_l			hw_pin_oc1bn
#define hw_oc11counter			hw_counter1

/*	Object				class, id, address
 */
/*  The `_oreg` class allows writing operations on the register `compare2`
 *  through a virtual object that we declare as a relative of `hw_counter1`.
 */
#define _hw_obj_hw_oc12			_oreg, hw_counter1, compare2


/*******************************************************************************
 *									       *
 *	Counter 1 dead time generator					       *
 *									       *
 *******************************************************************************/

#include "../classes/dtga_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_dtg1			_dtga, 504, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_dtg1_dtps			_r8, 0x43, 0x03, 0x00	/* DTPS1 */
#define _hw_dtg1_dta			_r8, 0x45, 0xFF, 0x00	/* DT1A */
#define _hw_dtg1_dtb			_r8, 0x44, 0xFF, 0x00	/* DT1B */

/*	Object logical registers
 */
#define _hw_dtg1_psc			_ob1, dtps, 2, 0

#define _hw_dtg1_compare0_h		_ob1, dta, 4, 4
#define _hw_dtg1_compare0_l		_ob1, dta, 4, 0

#define _hw_dtg1_compare1_h		_ob1, dtb, 4, 4
#define _hw_dtg1_compare1_l		_ob1, dtb, 4, 0


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#include "../classes/usia_1.h"
#define _hw_obj_hw_usi0			_usia, 600, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_usi0_dr			_r8, 0x2F, 0xFF, 0x00
#define _hw_usi0_br			_r8, 0x30, 0xFF, 0x00
#define _hw_usi0_sr			_r8, 0x2E, 0xFF, 0xE0
#define _hw_usi0_cr			_r8, 0x2D, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_usi0_ies			_ob1, cr, 1, 7
#define _hw_usi0_ieov			_ob1, cr, 1, 6
#define _hw_usi0_iep			_ob1, cr, 1, 5
#define _hw_usi0_wm			_ob1, cr, 2, 4
#define _hw_usi0_cs			_ob1, cr, 2, 2
#define _hw_usi0_clk			_ob1, cr, 1, 1
#define _hw_usi0_tc			_ob1, cr, 1, 0

#define _hw_usi0_ifs			_ob1, sr, 1, 7
#define _hw_usi0_ifov			_ob1, sr, 1, 6
#define _hw_usi0_ifp			_ob1, sr, 1, 5
#define _hw_usi0_dc			_ob1, sr, 1, 4
#define _hw_usi0_cnt			_ob1, sr, 4, 0

/*	USI used as SPI master with software clock
 */
#define _hw_obj_hw_spimaster_swclk0	_usia_spimaster_swclk, 602, hw_usi0

/*	USI used as SPI master with counter0 overflow clock
 */
#define _hw_obj_hw_spimaster_c0clk0	_usia_spimaster_c0clk, 603, hw_usi0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#include "../classes/acmpb_1.h"
#define _hw_obj_hw_acmp0		_acmpb, 700, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */					
#define _hw_acmp0_csr			_r8, 0x28, 0xDF, 0x10

/*	Object logical registers
 */					
#define _hw_acmp0_acd			_ob1, csr, 1, 7
#define _hw_acmp0_acbg			_ob1, csr, 1, 6
#define _hw_acmp0_aco			_ob1, csr, 1, 5
#define _hw_acmp0_if			_ob1, csr, 1, 4
#define _hw_acmp0_ie			_ob1, csr, 1, 3
#define _hw_acmp0_acis			_ob1, csr, 2, 0

#define _hw_acmp0_acme			_xob1, hw_adc0, srb,   1, 6
#define _hw_acmp0_aden			_xob1, hw_adc0, sra,   1, 7
#define _hw_acmp0_admux			_xob1, hw_adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/ad10c_1.h"
#define _hw_obj_hw_adc0			_ad10c, 800, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_adc0_admux			_r8,  0x27,   0xFF,   0x00
#define _hw_adc0_sra			_r8,  0x26,   0xFF,   0x10
#define _hw_adc0_adc			_r16, 0x24, 0x0000, 0x0000
#define _hw_adc0_adch			_r8,  0x25,   0x00,   0x00
#define _hw_adc0_srb			_r8,  0x23,   0xE7,   0x00

/*	Object logical registers
 */
#define _hw_adc0_refs			_ob2, admux, 2, 6, 0, admux, 1, 4, 2
#define _hw_adc0_lar			_ob1, admux, 1, 5
#define _hw_adc0_mux			_ob1, admux, 4, 0

#define _hw_adc0_en			_ob1, sra, 1, 7
#define _hw_adc0_sc			_ob1, sra, 1, 6
#define _hw_adc0_ate			_ob1, sra, 1, 5
#define _hw_adc0_if			_ob1, sra, 1, 4
#define _hw_adc0_ie			_ob1, sra, 1, 3
#define _hw_adc0_ps			_ob1, sra, 3, 0

#define _hw_adc0_bin			_ob1, srb, 1, 7
#define _hw_adc0_ipr			_ob1, srb, 1, 5
#define _hw_adc0_ts			_ob1, srb, 3, 0


/*******************************************************************************
 *									       *
 *	EEPROM								       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#include "../classes/eeproma_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_eeprom0		_eeproma, 1000, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__eeproma_ar			_r16, 0x3E, 0x01FF, 0x00
#define _hw__eeproma_dr			_r8,  0x3D,   0xFF, 0x00
#define _hw__eeproma_cr			_r8,  0x3C,   0x3F, 0x00

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

/*	Class
 */
#include "../classes/flasha_1.h"

/*	Object				class, id, address
 */
#define _hw_obj_hw_flash0		_flasha, 1100, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__flasha_csr			_r8,  0x57, 0x3F, 0x00

/*	Class logical registers
 */
#define _hw__flasha_sigrd		_cb1, csr, 1, 5
#define _hw__flasha_rsig		_cb1, csr, 1, 5 /* old name */
#define _hw__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw__flasha_ctpb		_cb1, csr, 1, 4 /* old name */
#define _hw__flasha_blbset		_cb1, csr, 1, 3
#define _hw__flasha_rflb		_cb1, csr, 1, 3 /* old name */
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
#define _hw_obj_hw_swuart0		_swuarta, 1200, 0
#define _hw_swuart0_dtn			_hw_rc(HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_swuart0_dt0			_hw_rc(HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_swuart0_sr			_hw_shared_gpior0
#endif

#if defined hw_swuart1_compare
/*
 *	Object hw_swuart1
 */
#define _hw_obj_hw_swuart1		_swuarta, 1210, 0
#define _hw_swuart1_dtn			_hw_rc(HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_swuart1_dt0			_hw_rc(HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dt0, -1, 0x00
#define _hw_swuart1_sr			_hw_shared_gpior1
#endif


/*******************************************************************************
 *									       *
 *			C O N T E X T					       *
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
  uint8_t	commit ;

  hwa_shared_t	hw_shared ;

  hwa_corea_t	hw_core0 ;
  hwa_p8a_t	hw_portb ;
  hwa_pcica_t	hw_pcic0 ;
  hwa_wdoga_t	hw_wdog0 ;

  hwa_oc8a_t	hw_oc00 ;
  hwa_oc8a_t	hw_oc01 ;
  hwa_c8a_t	hw_counter0 ;

  hwa_pscb_t	hw_psc1 ;
  hwa_dtga_t	hw_dtg1 ;
  hwa_oc8b_t	hw_oc10 ;
  hwa_oc8b_t	hw_oc11 ;
  hwa_c8b_t	hw_counter1 ;

  hwa_usia_t	hw_usi0 ;
  hwa_acmpb_t	hw_acmp0 ;
  hwa_ad10c_t	hw_adc0 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/corea_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p8a_2.h"
#include "../classes/pcica_2.h"
#include "../classes/wdoga_2.h"
#include "../classes/psca_2.h"
#include "../classes/oc8a_2.h"
#include "../classes/c8a_2.h"
#include "../classes/c8b_2.h"
#include "../classes/oc8b_2.h"
#include "../classes/pscb_2.h"
#include "../classes/dtga_2.h"
#include "../classes/usia_2.h"
#include "../classes/ad10c_2.h"
#include "../classes/acmpb_2.h"
#include "../classes/eeproma_2.h"
#include "../classes/flasha_2.h"
#include "../classes/swuarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_reg( hw_shared, gimsk );
  _hwa_setup_reg( hw_shared, gifr  );
  _hwa_setup_reg( hw_shared, prr   );
  _hwa_setup_reg( hw_shared, gtccr );
  _hwa_setup_reg( hw_shared, timsk );
  _hwa_setup_reg( hw_shared, tifr  );
  _hwa_setup_reg( hw_shared, did   );

  _hwa_setup( hw_core0 );

  _hwa_setup( hw_portb );
  _hwa_setup( hw_pcic0 );
  _hwa_setup( hw_wdog0 );

  _hwa_setup( hw_oc00 );
  _hwa_setup( hw_oc01 );
  _hwa_setup( hw_counter0 );

  _hwa_setup( hw_psc1 );
  _hwa_setup( hw_dtg1 );
  _hwa_setup( hw_oc10 );
  _hwa_setup( hw_oc11 );
  _hwa_setup( hw_counter1 );

  _hwa_setup( hw_usi0 );
  _hwa_setup( hw_acmp0 );
  _hwa_setup( hw_adc0 );
}

HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_reg( hw_shared, gimsk, 0 );
  _hwa_init_reg( hw_shared, gifr,  0 );
  _hwa_init_reg( hw_shared, prr,   0 );
  _hwa_init_reg( hw_shared, gtccr, 0 );
  _hwa_init_reg( hw_shared, timsk, 0 );
  _hwa_init_reg( hw_shared, tifr,  0 );
  _hwa_init_reg( hw_shared, did,   0 );

  _hwa_init( hw_core0 );
  _hwa_init( hw_portb );
  _hwa_init( hw_pcic0 );
  _hwa_init( hw_wdog0 );

  _hwa_init( hw_oc00 );
  _hwa_init( hw_oc01 );
  _hwa_init( hw_counter0 );

  _hwa_init( hw_psc1 );
  _hwa_init( hw_dtg1 );
  _hwa_init( hw_oc10 );
  _hwa_init( hw_oc11 );
  _hwa_init( hw_counter1 );

  _hwa_init( hw_usi0 );
  _hwa_init( hw_acmp0 );
  _hwa_init( hw_adc0 );
}

HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve( hw_counter0 );
  _hwa_solve( hw_counter1 );

  _hwa_commit_reg( hw_shared, gimsk );
  _hwa_commit_reg( hw_shared, gifr  );
  _hwa_commit( hw_core0 );
  _hwa_commit_reg( hw_shared, prr   );

  _hwa_commit( hw_wdog0 );
  _hwa_commit( hw_pcic0 );
  _hwa_commit( hw_portb );

  _hwa_commit( hw_oc00 );
  _hwa_commit( hw_oc01 );
  _hwa_commit_reg( hw_shared, gtccr );
  _hwa_commit( hw_counter0 );
  _hwa_commit_reg( hw_shared, timsk );
  _hwa_commit_reg( hw_shared, tifr );

  _hwa_commit( hw_psc1 );
  _hwa_commit( hw_dtg1 );
  _hwa_commit( hw_oc10 );
  _hwa_commit( hw_oc11 );
  _hwa_commit( hw_counter1 );

  _hwa_commit( hw_usi0 );
  _hwa_commit( hw_acmp0 );
  _hwa_commit( hw_adc0 );
  _hwa_commit_reg( hw_shared, did );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page attinyx5
 * <br>
 */
