
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny24/44/84
 */

#include "../hwa_1.h"

/**
 * @page attinyx4 ATtiny24/44/84
 * @section attinyx4_device Description
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE_ATTINYX4`	    |Always defined (void)
 * `HW_DEVICE_ATTINY84`<br>`HW_DEVICE_ATTINY84_20PU`<br>...|Defined (void) depending on the HWA header included
 * `HW_DEVICE_PACKAGE_8P3`  |Defined (void) depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte: `0x`
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table): `0x`
 *
 * Symbol		       | ATtiny24     | ATtiny44     | ATtiny84	     
 * :---------------------------|:------------:|:------------:|:-------------:
 * `HW_DEVICE`		       |	      |		     |attiny84
 * `HW_DEVICE_SIGNATURE`       |	      |		     |0x1E,0x93,0x0C
 * `HW_DEVICE_FLASH_SIZE`      |2048	      |4096	     |8192	    
 * `HW_DEVICE_FLASH_PAGE_SIZE` |32	      |32	     |64	    
 * `HW_DEVICE_EEPROM_SIZE`     |128	      |256	     |512
 * `HW_DEVICE_EEPROM_PAGE_SIZE`|4	      |4	     |4
 * `HW_DEVICE_RAM_SIZE`	       |128	      |256	     |512
 */
#define HW_DEVICE_ATTINYX4
#define HW_DEVICE_RAM_START		0x0060
#define HW_DEVICE_APP_START		0x0022

/**
 * @page attinyx4
 * @section attinyx4_fuses Fuses
 *
 * ATtinyX4 devices hold 3 fuse bytes describing their hardware configuration.
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
 * @page attinyx4
 *
 * Optionnaly, before including the device-specific header, fuses values can be
 * defined to describe the target more precisely. If these symbols are not
 * defined by the user, HWA will define them with the factory values.
 *
 */
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_rc_128kHz_rc_128kHz			, 1
#define _hw_is_low_freq_xosc_low_freq_xosc		, 1
#define _hw_is_xosc_xosc				, 1

/**
 * @page attinyx4
 * @subsection attinyx4_fuses_clocking Clocking
 *
 * Symbol		 |Valid values | Comments
 * :---------------------|-------------|:-----------
 * `HW_DEVICE_CLK_SRC`	 |`external`<br><b>`rc_8MHz`</b><br>`rc_128kHz`<br>`low_freq_xosc`<br>`xosc`|External source on pin CLKI<br>Internal RC oscillator<br>Internal RC oscillator (watchdog)<br>Crystal/resonator oscillator between pins XTAL1 and XTAL2<br> <br>
 * `HW_DEVICE_CLK_SRC_HZ`|Integer     |Clock frequency for `external`, `low_freq_xosc`, and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`	 |<b>`8`</b><br>`1`|Clock divided by 8<br>Clock not divided
 */
#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				rc_8Mhz
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
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define HW_DEVICE_CKSEL31				3
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#elif HW_IS(xosc, HW_DEVICE_CLK_SRC)
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_CKSEL31				4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_CKSEL31				5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_CKSEL31				6
#  else
#    define HW_DEVICE_CKSEL31				7
#  endif
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#else
#  error HW_DEVICE_CLK_SRC must be defined as one of `external`, `rc_8MHz`, `rc_128kHz`, `low_freq_xosc`, or `xosc`.
#endif

#if hw_syshz_base == 0
#  error HW_DEVICE_CLK_SRC_HZ must be defined when HW_DEVICE_CLK_SRC is `xosc` or `low_freq_xosc`.
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
HW_E_AVL('HW_DEVICE_CLK_PSC', HW_DEVICE_CLK_PSC, 1 | 8)
#endif

/**
 * @page attinyx4
 * @subsection attinyx4_fuses_sut Startup delays
 *
 * Symbol		| Valid values | Comments
 * :--------------------|--------------|:-----------
 * `HW_DEVICE_STARTUP_DELAYS` | `6CK_14CK`<br>`6CK_14CK_4ms`<br>`6CK_14CK_64ms`<br>`1KCK_4ms`<br>`1KCK_64ms`<br>`32KCK_64ms`<br>`258CK_14CK_4ms`<br>`258CK_14CK_64ms`<br>`1KCK_14CK`<br>`1KCK_14CK_4ms`<br>`1KCK_14CK_64ms`<br>`16KCK_14CK`<br>`16KCK_14CK_4ms`<br>`16KCK_14CK_64ms` | Valid values depend on the clocking configuration
*/
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


/**
 * @page attinyx4
 * @subsection attinyx4_fuses_other Other fuses
 *
 * Symbol		  | Valid values | Comments
 * :----------------------|--------------|:-----------
 * `HW_DEVICE_EXTERNAL_RESET`	 |`enabled`<br>`disabled`|Whether the device can be reset via its RESET pin
 * `HW_DEVICE_SELF_PROGRAMMING`	 |`enabled`<br>`disabled`|Whether the device can write into its Flash program memory
 * `HW_DEVICE_SERIAL_PROGRAMMING`|`enabled`<br>`disabled`|Whether the device can be programmed via the SPI
 * `HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE`|`enabled`<br>`disabled`|Whether the EEPROM memory is erased when a chip erase occurs
 * `HW_DEVICE_DEBUG_WIRE`	 |`disabled`<br>`enabled`|Whether the Debug Wire is operationnal
 * `HW_DEVICE_WATCHDOG_ALWAYS_ON`|`no`<br>`yes`		 |Whether the watchdog is always running
 * `HW_DEVICE_CLOCK_OUTPUT`	 |`disabled`<br>`enabled`|Whether the device outputs its clock
 * `HW_DEVICE_BROWNOUT_DETECTION`|`2500_2900mV`<br>`1700_2000mV`<br>`4100_4500mV`|Brown-out detection level
 *
 */
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

#define _hw_is_1700_2000mV_1700_2000mV			, 1
#define _hw_is_2500_2900mV_2500_2900mV			, 1
#define _hw_is_4100_4500mV_4100_4500mV			, 1

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



/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx4
 * @section attinyx4_object Peripherals
 * 
 * Object name   |Class                           | Comments
 * :-------------|--------------------------------|:--------------------------------------
 * `hw_core0`    |@ref atmelavr_corea "_corea"    | The core
 * `hw_int0`	 |@ref atmelavr_inta "_inta"      | External interrupt INT0
 * `hw_porta`    |@ref atmelavr_p8a "_p8a"        | General purpose I/O port A (PORTA)
 * `hw_portb`    |@ref atmelavr_p8a "_p8a"        | General purpose I/O port B (PORTB)
 * `hw_pcic0`    |@ref atmelavr_pcica "_pcica"    | Pin change interrupt controller
 * `hw_pcic1`    |@ref atmelavr_pcica "_pcica"    | Pin change interrupt controller
 * `hw_wdog0`    |@ref atmelavr_wdoga "_wdoga"    | Watchdog (WDG)
 * `hw_counter0` |@ref atmelavr_c8a "_c8a"        | 8-bit counter-timer (T0)
 * `hw_psc0`     |@ref atmelavr_psca "_psca"      | hw_counter0/hw_counter1 prescaler (PSC0)
 * `hw_oc00`     |@ref atmelavr_oc8a "_oc8a"      | Compare unit 0 of hw_counter0 (OC0A)
 * `hw_oc01`     |@ref atmelavr_oc8a "_oc8a"      | Compare unit 1 of hw_counter0 (OC0B)
 * `hw_counter1` |@ref atmelavr_c16a "_c16a"      | 16-bit counter-timer (T1)
 * `hw_oc10`     |@ref atmelavr_oc16a "_oc16a"    | Compare unit 0 of hw_counter1 (OC1A)
 * `hw_oc11`     |@ref atmelavr_oc16a "_oc16a"    | Compare unit 1 of hw_counter1 (OC1B)
 * `hw_ic10`     |@ref atmelavr_ic16a "_ic16a"    | Capture unit 0 of hw_counter1 (ICP)
 * `hw_usi0`     |@ref atmelavr_usia "_usia"      | Universal Serial Interface
 * `hw_acmp0`    |@ref atmelavr_acmpa "_acmpa"    | Analog Comparator
 * `hw_adc0`     |@ref atmelavr_ad10a "_ad10a"    | 10-bit Analog to Digital Converter
 * `hw_eeprom0`  |@ref atmelavr_eeproma "_eeproma"| Eeprom memory
 * `hw_flash0`   |@ref atmelavr_flasha "_flasha"  | Flash memory
 *
 * @subsection attinyx4_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name                   | Class                 | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_spimaster_swclk0`  | @ref atmelavr_usia_spimaster_swclk "usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `hw_swuart0`           | @ref atmelavr_swuarta "swuarta" | Software UART
 * `hw_swuart1`           | @ref atmelavr_swuarta "swuarta" | Software UART
 *
 * @subsection attinyx4_objrel Aliases and relations
 *
 * Some objects can be accessed from their @ref using_relatives "relatives" or
 * can have more than one name. There are the existing relations between the
 * device's objects and their different names:
 *
 * Name          | Aliases               | Relations
 * :-------------|-----------------------|:--------------------------------------
 * `hw_psc0`     | `hw_counter0prescaler`  | `HW_REL(hw_counter0, prescaler)`
 * `hw_psc0`     | `hw_counter0prescaler0` | `HW_REL(hw_counter0, prescaler0)`
 * `hw_psc0`     | `hw_counter1prescaler`  | `HW_REL(hw_counter1, prescaler)`
 * `hw_psc0`     | `hw_counter1prescaler0` | `HW_REL(hw_counter1, prescaler0)`
 * `hw_oc00`     | `hw_counter0compare0`   | `HW_REL(hw_counter0, compare0)`
 * `hw_oc01`     | `hw_counter0compare1`   | `HW_REL(hw_counter0, compare1)`
 * `hw_counter0` | `hw_oc00counter`        | `HW_REL(hw_oc00, counter)`
 * `hw_counter0` | `hw_oc01counter`        | `HW_REL(hw_oc01, counter)`
 * `hw_pin_oc00` | `hw_oc00pin`            | `HW_REL(hw_oc00, pin)`
 * `hw_pin_oc01` | `hw_oc01pin`            | `HW_REL(hw_oc01, pin)`
 * `hw_oc10`     | `hw_counter1compare0`   | `HW_REL(hw_counter1, compare0)`
 * `hw_oc11`     | `hw_counter1compare1`   | `HW_REL(hw_counter1, compare1)`
 * `hw_counter1` | `hw_oc10counter`        | `HW_REL(hw_oc10, counter)`
 * `hw_counter1` | `hw_oc11counter`        | `HW_REL(hw_oc11, counter)`
 * `hw_pin_oc10` | `hw_oc10pin`            | `HW_REL(hw_oc10, pin)`
 * `hw_pin_oc11` | `hw_oc11pin`            | `HW_REL(hw_oc11, pin)`
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx4
 * @section attinyx4_interrupts Interrupts
 * 
 * Interrupt name	  | Atmel label | Comments
 * :----------------------|-------------|------------------------
 * `hw_int0`	  	  | INT0	| External interrupt INT0
 * `hw_pcic0`	          | PCINT0	| Pin-change interrupt
 * `hw_pcic1`	          | PCINT1	| Pin-change interrupt
 * `hw_wdog0`		  | WDT		| Watchdog timeout
 * `hw_counter1,capture0` | TIM1_CAPT	| Capture event on counter 1
 * `hw_counter1,compare0` | TIM1_COMPA	| Compare-match A on counter 1
 * `hw_counter1,compare1` | TIM1_COMPB	| Compare-match B on counter 1
 * `hw_counter1,overflow` | TIM1_OVF	| Counter 1 overflow
 * `hw_counter0,compare0` | TIM0_COMPA	| Compare-match A on counter 0
 * `hw_counter0,compare1` | TIM0_COMPB	| Compare-match B on counter 0
 * `hw_counter0,overflow` | TIM0_OVF	| Counter 0 overflow
 * `hw_acmp0`		  | ANA_COMP	| Analog comparator
 * `hw_adc0`		  | ADC		| ADC conversion complete
 * `hw_eeprom0`		  | EE_RDY	| EEPROM ready
 * `hw_eeprom0,ready`	  | EE_RDY	| EEPROM ready
 * `hw_usi0,start`	  | USI_STR	| USI start
 * `hw_usi0,overflow`	  | USI_OVF	| USI overflow
 * `hw_usi0,txc`	  | USI_OVF	| USI overflow (transmit completed)
 */
#define _hw_irq_hw_int0_		_irq, hw_core0,     1, ie,  if
#define _hw_irq_hw_pcic0_		_irq, hw_pcic0,     2, ie,  if
#define _hw_irq_hw_pcic1_		_irq, hw_pcic1,     3, ie,  if
#define _hw_irq_hw_wdog0_		_irq, hw_wdog0,     4, ie,  if
#define _hw_irq_hw_counter1_capture0	_irq, hw_ic10,      5, ie,  if
#define _hw_irq_hw_ic10_		_irq, hw_ic10,      5, ie,  if
#define _hw_irq_hw_counter1_compare0	_irq, hw_oc10,      6, ie,  if
#define _hw_irq_hw_oc10_		_irq, hw_oc10,      6, ie,  if
#define _hw_irq_hw_counter1_compare1	_irq, hw_oc11,      7, ie,  if
#define _hw_irq_hw_oc11_		_irq, hw_oc11,      7, ie,  if
#define _hw_irq_hw_counter1_overflow	_irq, hw_counter1,  8, ie,  if
#define _hw_irq_hw_counter1		_irq, hw_counter1,  8, ie,  if
#define _hw_irq_hw_counter0_compare0	_irq, hw_oc00,      9, ie,  if
#define _hw_irq_hw_oc00_		_irq, hw_oc00,      9, ie,  if
#define _hw_irq_hw_counter0_compare1	_irq, hw_oc01,     10, ie,  if
#define _hw_irq_hw_oc01_		_irq, hw_oc01,     10, ie,  if
#define _hw_irq_hw_counter0_overflow	_irq, hw_counter0, 11, ie,  if
#define _hw_irq_hw_counter0_		_irq, hw_counter0, 11, ie,  if
#define _hw_irq_hw_acmp0_		_irq, hw_acmp0,    12, ie,  if
#define _hw_irq_hw_adc0_		_irq, hw_adc0,     13, ie,  if
#define _hw_irq_hw_eeprom0_		_irq, hw_eeprom0,  14, sie, /* no irq flag */
#define _hw_irq_hw_eeprom0_ready	_irq, hw_eeprom0,  14, sie,
#define _hw_irq_hw_usi0_start		_irq, hw_usi0,     15, ies,  ifs
#define _hw_irq_hw_usi0_overflow	_irq, hw_usi0,     16, ieov, ifov
#define _hw_irq_hw_usi0_txc		_irq, hw_usi0,     16, ieov, ifov


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by other objects						       *
 *									       *
 *******************************************************************************/

#define _hw_class__shared
#define _hw_shared			_shared, 0, 0

#define _hw_shared_gimsk		_r8, 0x5B, 0x70, 0x00
#define _hw_shared_gifr			_r8, 0x5A, 0x70, 0x70
#define _hw_shared_timsk		_r8, 0x59, 0x7E, 0x00
#define _hw_shared_tifr			_r8, 0x58, 0x7E, 0x7E
#define _hw_shared_gtccr		_r8, 0x43, 0x81, 0x00
#define _hw_shared_prr			_r8, 0x40, 0x0F, 0x00
#define _hw_shared_gpior2		_r8, 0x35, 0xFF, 0x00
#define _hw_shared_gpior1		_r8, 0x34, 0xFF, 0x00
#define _hw_shared_gpior0		_r8, 0x33, 0xFF, 0x00
#define _hw_shared_did			_r8, 0x21, 0xFF, 0x00

#if !defined __ASSEMBLER__
/*
 *  HWA context
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
 * @page attinyx4
 * @section attinyx4_pins Ports and pins
 *
 * Some of the pins `hw_pin_pb0`..`hw_pin_pb3` may not be available depending on
 * the fuses configuration.
 *
 * HWA name	| 14pdip      | Class			  | Atmel name
 * -------------|-------------|---------------------------|-----------
 * `hw_port_a`	|	      | @ref atmelavr_p8a "_p8a"   | -
 * `hw_pin_pa0` | `hw_pin_13` | @ref atmelavr_io1a "_io1a" | PA0
 * `hw_pin_pa1` | `hw_pin_12` | @ref atmelavr_io1a "_io1a" | PA1
 * `hw_pin_pa2` | `hw_pin_11` | @ref atmelavr_io1a "_io1a" | PA2
 * `hw_pin_pa3` | `hw_pin_10` | @ref atmelavr_io1a "_io1a" | PA3
 * `hw_pin_pa4` | `hw_pin_9`  | @ref atmelavr_io1a "_io1a" | PA4
 * `hw_pin_pa5` | `hw_pin_8`  | @ref atmelavr_io1a "_io1a" | PA5
 * `hw_pin_pa6` | `hw_pin_7`  | @ref atmelavr_io1a "_io1a" | PA6
 * `hw_pin_pa7` | `hw_pin_6`  | @ref atmelavr_io1a "_io1a" | PA7
 * `hw_port_b`	|	      | @ref atmelavr_p8a "_p8a"   | -
 * `hw_pin_pb0` | `hw_pin_2`  | @ref atmelavr_io1a "_io1a" | PB0
 * `hw_pin_pb1` | `hw_pin_3`  | @ref atmelavr_io1a "_io1a" | PB1
 * `hw_pin_pb2` | `hw_pin_5`  | @ref atmelavr_io1a "_io1a" | PB2
 * `hw_pin_pb3` | `hw_pin_4`  | @ref atmelavr_io1a "_io1a" | PB3
 */

#include "../classes/p8a_1.h"
#include "../classes/io1a_1.h"

/*	Objects				class, id, address
 */
#define _hw_porta			_p8a, 300, 0x39
#define _hw_portb			_p8a, 310, 0x36

/*  Pins				class, id, peripheral, bn, bp
 */
#define _hw_pin_pa0			_io1a, 301, hw_porta, 1, 0
#define _hw_pin_pa1			_io1a, 302, hw_porta, 1, 1
#define _hw_pin_pa2			_io1a, 303, hw_porta, 1, 2
#define _hw_pin_pa3			_io1a, 304, hw_porta, 1, 3
#define _hw_pin_pa4			_io1a, 305, hw_porta, 1, 4
#define _hw_pin_pa5			_io1a, 306, hw_porta, 1, 5
#define _hw_pin_pa6			_io1a, 307, hw_porta, 1, 6
#define _hw_pin_pa7			_io1a, 308, hw_porta, 1, 7
#define _hw_port_a			_io1a, 309, hw_porta, 8, 0

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb0			_io1a, 311, hw_portb, 1, 0
#endif
#define _hw_pin_pb1			_io1a, 312, hw_portb, 1, 1
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb2			_io1a, 313, hw_portb, 1, 2
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET) && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define _hw_pin_pb3			_io1a, 314, hw_portb, 1, 3
#endif

/*  Alternate pin functions
 */
#define hw_pin_ain0			hw_pin_pa1
#define hw_pin_ain1			hw_pin_pa2

#define hw_pin_usck			hw_pin_pa4
#define hw_pin_do			hw_pin_pa5
#define hw_pin_di			hw_pin_pa6

#define hw_pin_adc0			hw_pin_pa0
#define hw_pin_adc1			hw_pin_pa1
#define hw_pin_adc2			hw_pin_pa2
#define hw_pin_adc3			hw_pin_pa3
#define hw_pin_adc4			hw_pin_pa4
#define hw_pin_adc5			hw_pin_pa5
#define hw_pin_adc6			hw_pin_pa6
#define hw_pin_adc7			hw_pin_pa7

/*  Digital input disable bits for analog input pins
 */
#define _hw_pin_pa0_did			_xob1, hw_shared, did, 1, 0
#define _hw_pin_pa1_did			_xob1, hw_shared, did, 1, 1
#define _hw_pin_pa2_did			_xob1, hw_shared, did, 1, 2
#define _hw_pin_pa3_did			_xob1, hw_shared, did, 1, 3
#define _hw_pin_pa4_did			_xob1, hw_shared, did, 1, 4
#define _hw_pin_pa5_did			_xob1, hw_shared, did, 1, 5
#define _hw_pin_pa6_did			_xob1, hw_shared, did, 1, 6
#define _hw_pin_pa7_did			_xob1, hw_shared, did, 1, 7

/*  Relative pin change controllers
 */
#define hw_pin_pa0pcic			hw_pcic0
#define hw_pin_pa1pcic			hw_pcic0
#define hw_pin_pa2pcic			hw_pcic0
#define hw_pin_pa3pcic			hw_pcic0
#define hw_pin_pa4pcic			hw_pcic0
#define hw_pin_pa5pcic			hw_pcic0
#define hw_pin_pa6pcic			hw_pcic0
#define hw_pin_pa7pcic			hw_pcic0

#define hw_pin_pb0pcic			hw_pcic1
#define hw_pin_pb1pcic			hw_pcic1
#define hw_pin_pb2pcic			hw_pcic1
#define hw_pin_pb3pcic			hw_pcic1

/*	Pins by numbers
 */
#if defined HW_DEVICE_PACKAGE_14P3
#
#  define hw_pin_2			hw_pin_pb0
#  define hw_pin_3			hw_pin_pb1
#  define hw_pin_4			hw_pin_pb3
#  define hw_pin_5			hw_pin_pb2
#  define hw_pin_6			hw_pin_pa7
#  define hw_pin_7			hw_pin_pa6
#  define hw_pin_8			hw_pin_pa5
#  define hw_pin_9			hw_pin_pa4
#  define hw_pin_10			hw_pin_pa3
#  define hw_pin_11			hw_pin_pa2
#  define hw_pin_12			hw_pin_pa1
#  define hw_pin_13			hw_pin_pa0
#
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

#include "../classes/corea_1.h"

/*	Object				class, id, address
 */
#define _hw_core0			_corea, 101, 0

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
#define _hw_int0			_inta, 110, 0

#define _hw_int0_sc			_xob1, hw_core0,  mcucr, 2, 0
#define _hw_int0_ie			_xob1, hw_shared, gimsk, 1, 6
#define _hw_int0_if			_xob1, hw_shared, gifr,	 1, 6


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controllers				       *
 *									       *
 *******************************************************************************/

#include "../classes/pcica_1.h"

/*	Object				class, id, address
 */
#define _hw_pcic0			_pcica, 350, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic0_msk			_r8, 0x32, 0xFF, 0x00

/*	Object logical registers
 */
#define _hw_pcic0_ie			_xob1, hw_shared, gimsk, 1, 4
#define _hw_pcic0_if			_xob1, hw_shared, gifr,	 1, 4

/*	Object				class, id, address
 */
#define _hw_pcic1			_pcica, 351, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic1_msk			_r8, 0x40, 0x0F, 0x00

/*	Object logical registers
 */
#define _hw_pcic1_ie			_xob1, hw_shared, gimsk, 1, 5
#define _hw_pcic1_if			_xob1, hw_shared, gifr,	 1, 5


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#include "../classes/wdoga_1.h"
#define _hw_wdog0			_wdoga, 901, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define _hw__wdoga_csr			_r8, 0x41, 0xFF, 0x80

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

/*	Object				class, id, address
 */
#include "../classes/c8a_1.h"
#define _hw_counter0			_c8a, 400, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter0_imsk		_r8, 0x59, 0x07, 0x00
#define _hw_counter0_ifr		_r8, 0x58, 0x07, 0x07
#define _hw_counter0_ccrb		_r8, 0x53, 0xCF, 0x00
#define _hw_counter0_count		_r8, 0x52, 0xFF, 0x00
#define _hw_counter0_ccra		_r8, 0x50, 0xF3, 0x00

/*	Object logical registers
 */
#define _hw_counter0_wgm		_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define _hw_counter0_cs			_ob1, ccrb, 3, 0
#define _hw_counter0_ie			_ob1, imsk, 1, 0
#define _hw_counter0_if			_ob1, ifr,  1, 0

/*	Relatives
 */
#define hw_counter0prescaler0		hw_psc0
#define hw_counter0prescaler		hw_psc0
#define hw_counter0compare0		hw_oc00
#define hw_counter0compare1		hw_oc01


/*******************************************************************************
 *									       *
 *	Counter 0 compare units (OCR0A, OCR0B)				       *
 *									       *
 *******************************************************************************/

#include "../classes/oc8a_1.h"

/*	Object				class, id, address
 */
#define _hw_oc00			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc00_reg			_r8, 0x56, 0xFF, 0x00	/* OCR0A */

/*	Object logical registers
 */
#define _hw_oc00_com			_xob1, hw_counter0, ccra, 2, 6
#define _hw_oc00_force			_xob1, hw_counter0, ccrb, 1, 7
#define _hw_oc00_ie			_xob1, hw_counter0, imsk, 1, 1
#define _hw_oc00_if			_xob1, hw_counter0, ifr,  1, 1

/*	Relatives
 */
#define hw_oc00pin			hw_pin_pb2
#define hw_oc00counter			hw_counter0

/*	Object				class, id, address
 */
#define _hw_oc01			_oc8a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc01_reg			_r8, 0x5C, 0xFF, 0x00	/* OCR0B */

/*	Object logical registers
 */
#define _hw_oc01_com			_xob1, hw_counter0, ccra, 2, 4
#define _hw_oc01_force			_xob1, hw_counter0, ccrb, 1, 6
#define _hw_oc01_ie			_xob1, hw_counter0, imsk, 1, 2
#define _hw_oc01_if			_xob1, hw_counter0, ifr,  1, 2

/*	Relatives
 */
#define hw_oc01pin			hw_pin_pa7
#define hw_oc01counter			hw_counter0


/*******************************************************************************
 *									       *
 *	Counter 1 counting unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/c16a_1.h"

/*	Object				class, id, address
 */
#define _hw_counter1			_c16a, 410, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_counter1_ccra		_r8,  0x4F,   0xF3,   0x00
#define _hw_counter1_ccrb		_r8,  0x4E,   0xDF,   0x00
#define _hw_counter1_ccrc		_r8,  0x42,   0xC0,   0x00
#define _hw_counter1_count		_r16, 0x4C, 0xFFFF, 0x0000
#define _hw_counter1_imsk		_r8,  0x2C,   0x27,   0x00
#define _hw_counter1_ifr		_r8,  0x2B,   0x27,   0x27

/*	Object logical registers
 */
#define _hw_counter1_cs			_ob1, ccrb, 3, 0
#define _hw_counter1_wgm		_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define _hw_counter1_ie			_ob1, imsk, 1, 0
#define _hw_counter1_if			_ob1, ifr, 1, 0

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
#define _hw_oc10			_oc16a, 402, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc10_reg			_r16, 0x4A, 0xFFFF, 0x0000	/* OCR1A */

/*	Object logical registers
 */
#define _hw_oc10_com			_xob1, hw_counter1, ccra, 2, 6
#define _hw_oc10_force			_xob1, hw_counter1, ccrc, 1, 7
#define _hw_oc10_ie			_xob1, hw_counter1, imsk, 1, 1
#define _hw_oc10_if			_xob1, hw_counter1, ifr,  1, 1

/*	Relatives
 */
#define hw_oc10pin			hw_pin_pa6
#define hw_oc10counter			hw_counter1

/*	Object				class, id, address
 */
#define _hw_oc11			_oc16a, 403, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_oc11_reg			_r16, 0x48, 0xFFFF, 0x0000	/* OCR1B */

/*	Object logical registers
 */
#define _hw_oc11_com			_xob1, hw_counter1, ccra, 2, 4
#define _hw_oc11_force			_xob1, hw_counter1, ccrc, 1, 6
#define _hw_oc11_ie			_xob1, hw_counter1, imsk, 1, 2
#define _hw_oc11_if			_xob1, hw_counter1, ifr,  1, 2

/*	Relatives
 */
#define hw_oc11pin			hw_pin_pa5
#define hw_oc11counter			hw_counter1


/*******************************************************************************
 *									       *
 *	Counter 1 capture unit						       *
 *									       *
 *******************************************************************************/

#include "../classes/ic16a_1.h"

/*	Object				class, id, address
 */
#define _hw_ic10			_ic16a, 404, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_ic10_reg			_r16, 0x44, 0xFFFF, 0x0000	/* ICR1 */

/*	Object logical registers
 */
#define _hw_ic10_acic			_xob1, hw_acmp0, csr, 1, 2
#define _hw_ic10_icnc			_xob1, hw_counter1, ccrb, 1, 7
#define _hw_ic10_ices			_xob1, hw_counter1, ccrb, 1, 6
#define _hw_ic10_ie			_xob1, hw_counter1, imsk, 1, 5
#define _hw_ic10_if			_xob1, hw_counter1, ifr,  1, 5

/*	Relatives
 */
#define hw_ic10pin			hw_pin_pa7
#define hw_ic10counter			hw_counter1


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#include "../classes/usia_1.h"
#define _hw_usi0			_usia, 600, 0

/*	Class registers			class, address, write mask, flags mask
 */					
#define _hw__usia_cr			_r8, 0x2D, 0xFF, 0x00
#define _hw__usia_sr			_r8, 0x2E, 0xFF, 0xE0
#define _hw__usia_dr			_r8, 0x2F, 0xFF, 0x00
#define _hw__usia_br			_r8, 0x30, 0xFF, 0x00

#define _hw__usia_ies			_cb1, cr, 1, 7
#define _hw__usia_ieov			_cb1, cr, 1, 6
#define _hw__usia_wm			_cb1, cr, 2, 4
#define _hw__usia_cs			_cb1, cr, 2, 2
#define _hw__usia_clk			_cb1, cr, 1, 1
#define _hw__usia_tc			_cb1, cr, 1, 0

#define _hw__usia_ifs			_cb1, sr, 1, 7
#define _hw__usia_ifov			_cb1, sr, 1, 6
#define _hw__usia_pf			_cb1, sr, 1, 5
#define _hw__usia_dc			_cb1, sr, 1, 4
#define _hw__usia_cnt			_cb1, sr, 4, 0


/*	USI used as SPI master with software clock
 */
#define _hw_spimaster_swclk0		_usia_spimaster_swclk, 602, hw_usi0

/*	USI used as SPI master with counter0 overflow clock
 */
#define _hw_spimaster_c0clk0		_usia_spimaster_c0clk, 603, hw_usi0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */					
#include "../classes/acmpa_1.h"
#define _hw_acmp0			_acmpa, 700, 0

/*	Class registers			class, address, write mask, flags mask
 */					
#define _hw__acmpa_csr			_r8, 0x28, 0xDF, 0x10

/*	Object registers		class, address, write mask, flags mask
 *
*	Required for _hw_ic10_acic
 */
#define _hw_acmp0_csr			_r8, 0x28, 0xDF, 0x10

#define _hw_acmp0_acme			_xob1, hw_adc0, srb,   1, 6
#define _hw_acmp0_aden			_xob1, hw_adc0, sra,   1, 7
#define _hw_acmp0_admux			_xob1, hw_adc0, admux, 6, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/ad10a_1.h"
#define _hw_adc0			_ad10a, 800, 0

#define _hw__ad10a_admux		_r8,  0x27,   0xFF,   0x00
#define _hw__ad10a_sra			_r8,  0x26,   0xFF,   0x10
#define _hw__ad10a_adc			_r16, 0x24, 0x0000, 0x0000
#define _hw__ad10a_adch			_r8,  0x25,   0x00,   0x00
#define _hw__ad10a_adcl			_r8,  0x24,   0x00,   0x00
#define _hw__ad10a_srb			_r8,  0x23,   0xD7,   0x00
//#define _hw_adc0_did			_r8,  0x21,   0xFF,   0x00 /* port A */

#define _hw_adc0_admux			_r8,  0x27,   0xFF,   0x00
#define _hw_adc0_sra			_r8,  0x26,   0xFF,   0x10
#define _hw_adc0_srb			_r8,  0x23,   0xD7,   0x00

#define _hw__ad10a_refs			_cb1, admux, 2, 6
#define _hw__ad10a_mux			_cb1, admux, 6, 0

#define _hw__ad10a_en			_cb1, sra, 1, 7
#define _hw__ad10a_sc			_cb1, sra, 1, 6
#define _hw__ad10a_ate			_cb1, sra, 1, 5
#define _hw__ad10a_if			_cb1, sra, 1, 4
#define _hw__ad10a_ie			_cb1, sra, 1, 3
#define _hw__ad10a_ps			_cb1, sra, 3, 0

#define _hw__ad10a_bin			_cb1, srb, 1, 7
#define _hw__ad10a_lar			_cb1, srb, 1, 4
#define _hw__ad10a_ts			_cb1, srb, 3, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#define _hw_class__eeproma

/*	Object				class, id, address
 */
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define _hw__eeproma_arh		_r8,  0x3F,   0x01, 0x00
#define _hw__eeproma_arl		_r8,  0x3E,   0xFF, 0x00
#define _hw__eeproma_ar			_r16, 0x3E, 0x01FF, 0x00
#define _hw__eeproma_dr			_r8,  0x3D,   0xFF, 0x00
#define _hw__eeproma_cr			_r8,  0x3C,   0x3F, 0x00

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
#define _hw_class__flasha

/*	Object				class, id, address
 */
#define _hw_flash0			_flasha, 1100, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define _hw__flasha_csr			_r8,  0x57, 0x3F, 0x00

#define _hw__flasha_sigrd		_cb1, csr, 1, 5
#define _hw__flasha_rsig		_cb1, csr, 1, 5	/* old definition */
#define _hw__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw__flasha_ctpb		_cb1, csr, 1, 4	/* old definition */
#define _hw__flasha_blbset		_cb1, csr, 1, 3
#define _hw__flasha_rflb		_cb1, csr, 1, 3	/* old definition */
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
#define _hw_swuart0		_swuarta, 1200, 0
#define _hw_swuart0_dtn		_hw_rc(HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_swuart0_dt0		_hw_rc(HW_REL(hw_swuart0_compare,counter),count), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_swuart0__st		_hw_ra(hw_shared, gpior0)
#define _hw_swuart0_sr		_hw_shared_gpior0
#define _hw_swuart0_synced	_ob1, sr, 1, 0
#endif

#if defined hw_swuart1_compare
/*
 *	Object hw_swuart1
 */
#define _hw_swuart1		_swuarta, 1210, 0
#define _hw_swuart1_dtn		_hw_rc(HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_swuart1_dt0		_hw_rc(HW_REL(hw_swuart1_compare,counter),count), (intptr_t)&__hw_swuart1_dt0, -1, 0x00
#define _hw_swuart1__st		_hw_ra(hw_shared, gpior1)
#define _hw_swuart1_sr		_hw_shared_gpior1
#define _hw_swuart1_synced	_ob1, sr, 1, 0
#endif


/**
 * @page attinyx4
 *
 * @section attinyx4_pwr Power Management
 *
 * The following peripherals can be turned on/off with the `hw_power()` and `hwa_power()`
 * instructions to manage power consumption of the device:
 *
 * * `hw_counter0`
 * * `hw_counter1`
 * * `hw_usi0`
 * * `hw_adc0`
 * * `hw_acmp0`
 *
 * @code
 * hw_power( hw_counter0, off );
 * @endcode
 */

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

  hwa_corea_t	hw_core0 ;
  hwa_p8a_t	hw_porta ;
  hwa_p8a_t	hw_portb ;
  hwa_pcica_t	hw_pcic0 ;
  hwa_pcica_t	hw_pcic1 ;
  hwa_wdoga_t	hw_wdog0 ;

  hwa_oc8a_t	hw_oc00 ;
  hwa_oc8a_t	hw_oc01 ;
  hwa_c8a_t	hw_counter0 ;

  hwa_oc16a_t	hw_oc10 ;
  hwa_oc16a_t	hw_oc11 ;
  hwa_ic16a_t	hw_ic10 ;
  hwa_c16a_t	hw_counter1 ;

  hwa_usia_t	hw_usi0 ;
  hwa_acmpa_t	hw_acmp0 ;
  hwa_ad10a_t	hw_adc0 ;
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
#include "../classes/oc16a_2.h"
#include "../classes/ic16a_2.h"
#include "../classes/c16a_2.h"
#include "../classes/usia_2.h"
#include "../classes/acmpa_2.h"
#include "../classes/ad10a_2.h"
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
  _hwa_setup( hw_porta );
  _hwa_setup( hw_portb );
  _hwa_setup( hw_pcic0 );
  _hwa_setup( hw_pcic1 );
  _hwa_setup( hw_wdog0 );

  _hwa_setup( hw_oc00 );
  _hwa_setup( hw_oc01 );
  _hwa_setup( hw_counter0 );

  _hwa_setup( hw_oc10 );
  _hwa_setup( hw_oc11 );
  _hwa_setup( hw_ic10 );
  _hwa_setup( hw_counter1 );

  _hwa_setup( hw_usi0 );
  _hwa_setup( hw_adc0 );

  _hwa_setup( hw_acmp0 );
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

  _hwa_init( hw_porta );
  _hwa_init( hw_portb );
  _hwa_init( hw_pcic0 );
  _hwa_init( hw_pcic1 );
  _hwa_init( hw_wdog0 );

  _hwa_init( hw_oc00 );
  _hwa_init( hw_oc01 );
  _hwa_init( hw_counter0 );

  _hwa_init( hw_oc10 );
  _hwa_init( hw_oc11 );
  _hwa_init( hw_ic10 );
  _hwa_init( hw_counter1 );

  _hwa_init( hw_usi0 );
  _hwa_init( hw_adc0 );
  _hwa_init( hw_acmp0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  /*  Solve the configuration of the counters
   *
   *  The configuration values are written here since the solve function only
   *  has the address of the counter and does not know its name.
   *
   *  _reg_p(...) could be used as well though it can not access registers of
   *  another object.
   */
  _hwa_solve( hw_counter0 );
  _hwa_solve( hw_counter1 );

  _hwa_commit_reg( hw_shared, gimsk );
  _hwa_commit_reg( hw_shared, gifr  );
  _hwa_commit( hw_core0 );
  _hwa_commit_reg( hw_shared, prr   );

  _hwa_commit( hw_wdog0 );
  _hwa_commit( hw_porta );
  _hwa_commit( hw_portb );

  _hwa_commit( hw_pcic0 );
  _hwa_commit( hw_pcic1 );

  _hwa_commit_reg( hw_shared, gtccr );
  _hwa_commit( hw_counter0 );
  _hwa_commit( hw_oc00 );
  _hwa_commit( hw_oc01 );

  _hwa_commit( hw_counter1 );
  _hwa_commit( hw_oc10 );
  _hwa_commit( hw_oc11 );
  _hwa_commit( hw_ic10 );

  _hwa_commit( hw_usi0 );
  _hwa_commit( hw_adc0 );
  _hwa_commit_reg( hw_shared, did );
  _hwa_commit( hw_acmp0 );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page attinyx4
 * <br>
 */
