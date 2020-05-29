
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny25/45/85
 * @page attinyx5 ATtiny25/45/85
 */

#include "../hwa_1.h"

/**
 * @page attinyx5
 * @section attinyx5_objects Objects
 * 
 * Object name		|Class			     | Comments
 * :--------------------|----------------------------|:--------------------------------------
 * `acmp0`		|@ref atmelavr_acb "_acb"| Analog Comparator
 * `adc0`		|@ref atmelavr_adc "_adc"| 10-bit Analog to Digital Converter
 * `core0`		|@ref atmelavr_corea "_corea"| The core
 * `int0`		|@ref atmelavr_inta "_inta"  | External interrupt INT0
 * `prescaler0`		|@ref atmelavr_psa "_psa"  | Counter 0 prescaler
 * `counter0`		|@ref atmelavr_cta "_cta"    | 8-bit counter-timer (T0)
 * `(counter0,compare0)`|@ref atmelavr_oca "_oca"| Compare unit 0 of counter0 (OC0A)
 * `(counter0,compare1)`|@ref atmelavr_oca "_oca"| Compare unit 1 of counter0 (OC0B)
 * `prescaler1`		|@ref atmelavr_psb "_psb"  | Counter 1 prescaler
 * `counter1`		|@ref atmelavr_ctb "_ctb"    | 8-bit counter-timer (T1)
 * `(counter1,compare0)`|@ref atmelavr_ocb "_ocb"| Compare unit 0 of counter1 (OC1A)
 * `(counter1,compare1)`|@ref atmelavr_ocb "_ocb"| Compare unit 1 of counter1 (OC1B)
 * `dtg1`		|@ref atmelavr_dtga "_dtga"  | Dead time generator for `counter1` compare outputs
 * `eeprom0`		|@ref atmelavr_eea "_eea"| Eeprom memory
 * `flash0`		|@ref atmelavr_fla "_fla"	 | Flash memory
 * `pcic0`		|@ref atmelavr_pxa "_pxa"| Pin change interrupt controller
 * `port0`		|@ref atmelavr_gpa "_gpa"    | General purpose I/O port B (PORT0)
 * `usi0`		|@ref atmelavr_usia "_usia"  | Universal Serial Interface
 * `watchdog0`		|@ref atmelavr_wda "_wda"| Watchdog (WDG)
 *
 * @subsection attinyx5_swobj Software-emulated peripherals
 * 
 * HWA provides the following software-emulated peripherals:
 * 
 * Name		     | Class		     | Comments
 * :-----------------|-----------------------|:--------------------------------------
 * `spimaster_swclk0`| @ref atmelavr_usia_spimaster_swclk "_usia_spimaster_swclk" | Universal Serial Interface used as SPI master and clocked by software
 * `swuart0`	     | @ref atmelavr_swuarta "_swuarta" | Software UART
 * `swuart1`	     | @ref atmelavr_swuarta "_swuarta" | Software UART
 *
 * @subsection attinyx5_objrel Aliases and relations
 *
 * Some objects can be accessed from their relatives or can have more than one
 * name. There are the existing relations between the device's objects and their
 * different names:
 *
 * Name			 | Aliases		   | Relations
 * :---------------------|-------------------------|:--------------------------------------
 * `prescaler0`		 |`counter0prescaler`	   | `(counter0, prescaler)`
 * `prescaler0`		 |`counter0prescaler0`	   | `(counter0, prescaler0)`
 * `prescaler0`		 |`counter1prescaler`	   | `(counter1, prescaler)`
 * `prescaler0`		 |`counter1prescaler0`	   | `(counter1, prescaler0)`
 * `counter0compare0`	 |`counter0compare0`	   | `(counter0, compare0)`
 * `counter0compare1`	 |`counter0compare1`	   | `(counter0, compare1)`
 * `counter0`		 |`counter0compare0counter`| `(counter0compare0, counter)`
 * `counter0`		 |`counter0compare1counter`| `(counter0compare1, counter)`
 * `pin_counter0compare0`|`counter0compare0pin`	   | `(counter0compare0, pin)`
 * `pin_counter0compare1`|`counter0compare1pin`	   | `(counter0compare1, pin)`
 * `counter1compare0`	 |`counter1compare0`	   | `(counter1, compare0)`
 * `counter1compare1`	 |`counter1compare1`	   | `(counter1, compare1)`
 * `counter1`		 |`counter1compare0counter`| `(counter1compare0, counter)`
 * `counter1`		 |`counter1compare1counter`| `(counter1compare1, counter)`
 * `pin_counter1compare0`|`counter1compare0pin`	   | `(counter1compare0, pin)`
 * `pin_counter1compare1`|`counter1compare1pin`	   | `(counter1compare1, pin)`
 * `dtg1`		 |`counter1dtg0`	   | `(counter1, dtg)`<br>`(counter1, dtg0)`
 */


/**
 * @page attinyx5
 * @subsection attinyx5_irqs Interrupts
 * 
 * Interrupt name			| Atmel label | Comments
 * :------------------------------------|-------------|------------------------
 * `acmp0`				| ANA_COMP    | Analog comparator
 * `adc0`				| ADC	      | ADC conversion complete
 * `core0,int0`				| INT0	      | External interrupt INT0
 * `counter0`<br>`counter0,overflow`	| TIM0_OVF    | Counter 0 overflow
 * `counter0,compare0`<br>`counter0compare0`<br>`counter0compare0` | TIM0_COMPA	 | Compare-match A on counter 0
 * `counter0,compare1`<br>`counter0compare1`<br>`counter0compare1` | TIM0_COMPB	 | Compare-match B on counter 0
 * `counter1`<br>`counter1,overflow`	| TIM1_OVF    | Counter 1 overflow
 * `counter1,compare0`			| TIM1_COMPA  | Compare-match A on counter 1
 * `counter1,compare1`			| TIM1_COMPB  | Compare-match B on counter 1
 * `eeprom0`<br>`eeprom0,ready`		| EE_RDY      | EEPROM ready
 * `pcic0`<br>`hw_pin_*,change`		| PCINT0      | Pin-change interrupt
 * `usi0,overflow`<br>`usi0,txc`	| USI_OVF     | USI overflow
 * `usi0,start`				| USI_STR     | USI start
 * `watchdog0`				| WDT	      | Watchdog timeout
 */
#define hw_int0_irq			_irq,  1, core0,     ie,    if
#define hw_pcic0_irq			_irq,  2, pcic0,     ie,    if
#define hw_counter1_irq_compare0	_irq,  3, counter1,  ocie0, ocif0
#define hw_counter1_compare0_irq	_irq,  3, counter1,  ocie0, ocif0
#define hw_counter1_irq			_irq,  4, counter1,  ie,    if
#define hw_counter1_irq_overflow	_irq,  4, counter1,  ie,    if
#define hw_counter0_irq			_irq,  5, counter0,  ie,    if
#define hw_counter0_irq_overflow	_irq,  5, counter0,  ie,    if
#define hw_eeprom0_irq			_irq,  6, eeprom0,   ie, /* no irq flag */
#define hw_eeprom0_irq_ready		_irq,  6, eeprom0,   ie,
#define hw_acmp0_irq			_irq,  7, acmp0,     ie,    if
#define hw_adc0_irq			_irq,  8, adc0,	     ie,    if
#define hw_counter1_irq_compare1	_irq,  9, counter1,  ocie1, ocif1
#define hw_counter1_compare1_irq	_irq,  9, counter1,  ocie1, ocif1
#define hw_counter0_irq_compare0	_irq, 10, counter0,  ocie0, ocif0
#define hw_counter0_compare0_irq	_irq, 10, counter0,  ocie0, ocif0
#define hw_counter0_irq_compare1	_irq, 11, counter0,  ocie1, ocif1
#define hw_counter0_compare1_irq	_irq, 11, counter0,  ocie1, ocif1
#define hw_watchdog0_irq		_irq, 12, watchdog0, ie,    if
#define hw_usi0_irq			_irq, , , ,
#define hw_usi0_irq_start		_irq, 13, usi0,	     ies,   ifs
#define hw_usi0_irq_overflow		_irq, 14, usi0,	     ieov,  ifov
#define hw_usi0_irq_txc			_irq, 14, usi0,	     ieov,  ifov


/**
 * @page attinyx5
 * @subsection attinyx5_pins Ports and pins
 *
 * Some of the pins `pb0`..`pb3` may not be available depending on
 * the fuses configuration.
 *
 * HWA name| 8P3       | Class			    | Atmel name
 * --------|-----------|----------------------------|-----------
 * `portb` |	       | @ref atmelavr_gpa "p8a"    | PORTB
 * `pb0`   |`HW_PIN(5)`| @ref atmelavr_ioa "_ioa" | PB0
 * `pb1`   |`HW_PIN(6)`| @ref atmelavr_ioa "_ioa" | PB1
 * `pb2`   |`HW_PIN(7)`| @ref atmelavr_ioa "_ioa" | PB2
 * `pb3`   |`HW_PIN(2)`| @ref atmelavr_ioa "_ioa" | PB3
 * `pb4`   |`HW_PIN(3)`| @ref atmelavr_ioa "_ioa" | PB4
 * `pb5`   |`HW_PIN(1)`| @ref atmelavr_ioa "_ioa" | PB5
 */


/**
 * @page attinyx5
 * @section attinyx5_device Symbols
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Comments
 * :------------------------|:-----------
 * `HW_DEVICE_ATTINYX5`	    |Defined void.
 * `HW_DEVICE_ATTINY85`<br>`HW_DEVICE_ATTINY85_20PU` | Defined void depending on the HWA header included.
 * `HW_DEVICE_PACKAGE_8P3`  |Defined (void) depending on the packaging of the device.
 * `HW_DEVICE_RAM_START`    |Address of first RAM byte: `0x0060`.
 * `HW_DEVICE_APP_START`    |Address of first application byte (after IRQ vector table): `0x001E`.
 *
 * See also:
 *  * @subpage attiny25
 *  * @subpage attiny45
 *  * @subpage attiny85
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
#define _hw_is_rc_pll_16MHz_rc_pll_16MHz	, 1
#define _hw_is_rc_8MHz_rc_8MHz			, 1
#define _hw_is_rc_1600kHz_rc_1600kHz		, 1
#define _hw_is_rc_128kHz_rc_128kHz		, 1
#define _hw_is_low_freq_xosc_low_freq_xosc	, 1
#define _hw_is_xosc_xosc		, 1

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
#  define HW_SYSHZ				hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_CKDIV8			1
#  define HW_SYSHZ				hw_syshz_base
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
#  define HW_DEVICE_BROWNOUT_DETECTION		off
#endif

#define _hw_bod_1700_2000mV			, 6
#define _hw_bod_2500_2900mV			, 5
#define _hw_bod_4100_4500mV			, 4
#define _hw_bod_off			, 7

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
#  HW_E(`pll_64MHz` is not available with supply voltages below 2.7 V)
#endif


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by other objects						       *
 *									       *
 *******************************************************************************/

#define hw_class__shared

/*	Object				class, address
 */
#define hw_shared			_shared, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_shared_gimsk			_r8, 0x5B, 0x60, 0x00
#define hw_shared_gifr			_r8, 0x5A, 0x60, 0x60
#define hw_shared_timsk			_r8, 0x59, 0x7E, 0x00
#define hw_shared_tifr			_r8, 0x58, 0x7E, 0x7E
#define hw_shared_gtccr			_r8, 0x4C, 0xFF, 0x00
#define hw_shared_prr			_r8, 0x40, 0x0F, 0x00
#define hw_shared_gpior2		_r8, 0x33, 0xFF, 0x00
#define hw_shared_gpior1		_r8, 0x32, 0xFF, 0x00
#define hw_shared_gpior0		_r8, 0x31, 0xFF, 0x00
#define hw_shared_did			_r8, 0x34, 0x3F, 0x00


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

#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"

/*	Object				class, address
 */
#define hw_port0			_gpa, 0x36

#define hw_pb0				_ioa, port0, 1, 0
#define hw_pb1				_ioa, port0, 1, 1
#define hw_pb2				_ioa, port0, 1, 2
#define hw_pb3				_ioa, port0, 1, 3
#define hw_pb4				_ioa, port0, 1, 4
#if HW_DEVICE_RSTDISBL == 0
#  define hw_pb5			_ioa, port0, 1, 5
#endif
#define hw_portb			_ioa, port0, 6, 0

/*  Digital input disable bits for analog input pins
 */
#define hw_pb5_did			_xob1, shared, did, 1, 5	/* ADC0 */
#define hw_pb2_did			_xob1, shared, did, 1, 4	/* ADC1 */
#define hw_pb4_did			_xob1, shared, did, 1, 3	/* ADC2 */
#define hw_pb3_did			_xob1, shared, did, 1, 2	/* ADC3 */
#define hw_pb1_did			_xob1, shared, did, 1, 1	/* AIN1 */
#define hw_pb0_did			_xob1, shared, did, 1, 0	/* AIN0 */

/*  Relative pin change controllers
 */
#define hw_pb0_pcic			pcic0
#define hw_pb1_pcic			pcic0
#define hw_pb2_pcic			pcic0
#define hw_pb3_pcic			pcic0
#define hw_pb4_pcic			pcic0
#define hw_pb5_pcic			pcic0

/*  Canonical pin names
 */
#define _hw_pin_compare0a		, pb0
#define _hw_pin_compare0b		, pb1

#define _hw_pin_compare1a		, pb1
#define _hw_pin_compare1an		, pb0
#define _hw_pin_compare1b		, pb4
#define _hw_pin_compare1bn		, pb3

#define _hw_pin_usck			, pb2
#define _hw_pin_do			, pb1
#define _hw_pin_di			, pb0
#define _hw_pin_usi0_ck			, pb2
#define _hw_pin_usi0_do			, pb1
#define _hw_pin_usi0_di			, pb0

#define _hw_pin_adc0			, pb5
#define _hw_pin_adc1			, pb2
#define _hw_pin_adc2			, pb4
#define _hw_pin_adc3			, pb3
#define _hw_pin_ain1			, pb1
#define _hw_pin_ain0			, pb0

#if defined HW_DEVICE_PACKAGE_8P3
#  define _hw_pin_1			, pb5
#  define _hw_pin_2			, pb3
#  define _hw_pin_3			, pb4
#  define _hw_pin_5			, pb0
#  define _hw_pin_6			, pb1
#  define _hw_pin_7			, pb2
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/corea_1.h"
#define hw_core0			_corea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__corea_sreg			_r8, 0x5F, 0xFF, 0x00
#define hw__corea_sph			_r8, 0x5E, 0x03, 0x00
#define hw__corea_spl			_r8, 0x5D, 0xFF, 0x00

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_core0_mcucr			_r8, 0x55, 0xFF, 0x00
#define hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define hw_core0_osccal			_r8, 0x51, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_core0_bods			_ob1, mcucr, 1, 7
#define hw_core0_pud			_ob1, mcucr, 1, 6
#define hw_core0_se			_ob1, mcucr, 1, 5
#define hw_core0_sm			_ob1, mcucr, 2, 3
#define hw_core0_bodse			_ob1, mcucr, 1, 2
#define hw_core0_isc0			_ob1, mcucr, 2, 0

#define hw_core0_wdrf			_ob1, mcusr, 1, 3
#define hw_core0_borf			_ob1, mcusr, 1, 2
#define hw_core0_extrf			_ob1, mcusr, 1, 1
#define hw_core0_porf			_ob1, mcusr, 1, 0
#define hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */


/*******************************************************************************
 *									       *
 *	External interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/inta_1.h"
#define hw_int0				_inta, 0

#define hw_int0_sc			_xob1, core0,  mcucr, 2, 0
#define hw_int0_ie			_xob1, shared, gimsk, 1, 6
#define hw_int0_if			_xob1, shared, gifr,  1, 6


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/pxa_1.h"
#define hw_pcic0			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic0_msk			_r8, 0x35, 0x3F, 0x00

/*	Object logical registers
 */
#define hw_pcic0_ie			_xob1, shared, gimsk, 1, 5
#define hw_pcic0_if			_xob1, shared, gifr,  1, 5


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/wda_1.h"
#define hw_watchdog0			_wda, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__wda_csr			_r8, 0x41, 0xFF, 0x80

/*	Class logical registers
 */
#define hw__wda_if			_cb1, csr, 1, 7
#define hw__wda_ie			_cb1, csr, 1, 6
#define hw__wda_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw__wda_wdce			_cb1, csr, 1, 4
#define hw__wda_wde			_cb1, csr, 1, 3

#define hw__wda_eie			_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define hw__wda_ifie			_cb1, csr, 2, 6 /* convenient for clearing irq */

#define hw__wda_wdrf			_xob1, core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0							       *
 *									       *
 *******************************************************************************/

#include "../classes/oca_1.h"
#include "../classes/cta_1.h"

/*	Object				class, address
 */
#define hw_counter0			_cta, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_counter0_ccra		_r8, 0x4A, 0xF3, 0x00
#define hw_counter0_ocr0		_r8, 0x49, 0xFF, 0x00	/* OCR0A */
#define hw_counter0_ocr1		_r8, 0x48, 0xFF, 0x00	/* OCR0B */
#define hw_counter0_ccrb		_r8, 0x53, 0xCF, 0x00
#define hw_counter0_count		_r8, 0x52, 0xFF, 0x00
#define hw_counter0_imsk		_r8, -1, 0, 0	/* For compatibility */
#define hw_counter0_ifr			_r8, -1, 0, 0

/*	Object logical registers
 */
#define hw_counter0_com0		_ob1, ccra, 2, 6
#define hw_counter0_com1		_ob1, ccra, 2, 4
#define hw_counter0_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define hw_counter0_foc0		_ob1, ccrb, 1, 7
#define hw_counter0_foc1		_ob1, ccrb, 1, 6
#define hw_counter0_cs			_ob1, ccrb, 3, 0

#define hw_counter0_ie			_xob1, shared, timsk, 1, 1
#define hw_counter0_if			_xob1, shared, tifr,  1, 1

#define hw_counter0_ocie0		_xob1, shared, timsk, 1, 4
#define hw_counter0_ocif0		_xob1, shared, tifr,  1, 4

#define hw_counter0_ocie1		_xob1, shared, imsk,  1, 3
#define hw_counter0_ocif1		_xob1, shared, ifr,   1, 3

/*	Relatives
 */
#define hw_counter0_prescaler0		prescaler0
#define hw_counter0_prescaler		prescaler0

#define hw_counter0_compare0		_oca, counter0, 0
#define hw_counter0_compare0_pin	pb0
#define hw_counter0_compare0_counter	counter0

#define hw_counter0_compare1		_oca, counter0, 1
#define hw_counter0_compare1_pin	pb1
#define hw_counter0_compare1_counter	counter0


/*******************************************************************************
 *									       *
 *	Counter 0 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psa_1.h"

/*	Object				class, address
 */
#define hw_prescaler0			_psa, 0

/*	Object logical registers
 */
#define hw_prescaler0_tsm		_xob1, shared, gtccr, 1, 7
#define hw_prescaler0_psr		_xob1, shared, gtccr, 1, 0

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define hw_prescaler0_tsmpsr		_xob2, shared, gtccr, 1, 7, 1, gtccr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	Counter 1							       *
 *									       *
 *******************************************************************************/

#include "../classes/ocb_1.h"
#include "../classes/dtga_1.h"
#include "../classes/ctb_1.h"

/*	Object				class, address
 */
#define hw_counter1			_ctb, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter1_ccr			_r8, 0x50, 0xFF, 0x00	/* TCCR1 */
#define hw_counter1_count		_r8, 0x4F, 0xFF, 0x00	/* TCNT1 */
#define hw_counter1_ocr0		_r8, 0x4E, 0xFF, 0x00	/* OCR1A */
#define hw_counter1_ocr2		_r8, 0x4D, 0xFF, 0x00	/* OCR1C */
#define hw_counter1_ocr1		_r8, 0x4B, 0xFF, 0x00	/* OCR1B */
#define hw_counter1_dta			_r8, 0x45, 0xFF, 0x00	/* DT1A */
#define hw_counter1_dtb			_r8, 0x44, 0xFF, 0x00	/* DT1B */
#define hw_counter1_dtps		_r8, 0x43, 0x03, 0x00	/* DTPS1 */

/*	Logical registers
 */
#define hw_counter1_ctc			_ob1, ccr, 1, 7
#define hw_counter1_pwm0		_ob1, ccr, 1, 6
#define hw_counter1_com0		_ob1, ccr, 2, 4
#define hw_counter1_cs			_ob1, ccr, 4, 0

#define hw_counter1_dtgps		_ob1, dtps, 2, 0
#define hw_counter1_dtg0h		_ob1, dta,  4, 4
#define hw_counter1_dtg0l		_ob1, dta,  4, 0
#define hw_counter1_dtg1h		_ob1, dtb,  4, 4
#define hw_counter1_dtg1l		_ob1, dtb,  4, 0

#define hw_counter1_ocie0		_xob1, shared, timsk, 1, 6
#define hw_counter1_ocie1		_xob1, shared, timsk, 1, 5
#define hw_counter1_ie			_xob1, shared, timsk, 1, 2

#define hw_counter1_ocif0		_xob1, shared, tifr,  1, 6
#define hw_counter1_ocif1		_xob1, shared, tifr,  1, 5
#define hw_counter1_if			_xob1, shared, tifr,  1, 2

#define hw_counter1_pwm1		_xob1, shared, gtccr, 1, 6
#define hw_counter1_com1		_xob1, shared, gtccr, 2, 4
#define hw_counter1_foc1		_xob1, shared, gtccr, 1, 3
#define hw_counter1_foc0		_xob1, shared, gtccr, 1, 2

/*	Relatives
 */
#define hw_counter1_prescaler		prescaler1
#define hw_counter1_prescaler0		prescaler1

#define hw_counter1_compare0		_ocb, counter1, 0
#define hw_counter1_compare0_pin	pb1
#define hw_counter1_compare0_pin_h	pb1
#define hw_counter1_compare0_pin_l	pb0
#define hw_counter1_compare0_counter	counter1
#define hw_counter1_compare0_dtg	_dtga, counter1, 0

#define hw_counter1_compare1		_ocb, counter1, 1
#define hw_counter1_compare1_pin	pb4
#define hw_counter1_compare1_pin_h	pb4
#define hw_counter1_compare1_pin_l	pb3
#define hw_counter1_compare1_counter	counter1
#define hw_counter1_compare1_dtg	_dtga, counter1, 1

#define hw_counter1_compare2		_xob1, counter1, ocr2, 8, 0


/*******************************************************************************
 *									       *
 *	Counter 1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psb_1.h"

/*	Object				class, address
 */
#define hw_prescaler1			_psb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_prescaler1_pllcsr		_r8, 0x47, 0x86, 0x00	/* PLLCSR */

/*	Object logical registers
 */
#define hw_prescaler1_psr		_xob1, shared, gtccr, 1, 1

#define hw_prescaler1_lsm		_ob1, pllcsr, 1, 7
#define hw_prescaler1_pcke		_ob1, pllcsr, 1, 2
#define hw_prescaler1_plle		_ob1, pllcsr, 1, 1
#define hw_prescaler1_plock		_ob1, pllcsr, 1, 0


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#include "../classes/usia_1.h"
#define hw_usi0				_usia, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_usi0_dr			_r8, 0x2F, 0xFF, 0x00
#define hw_usi0_br			_r8, 0x30, 0xFF, 0x00
#define hw_usi0_sr			_r8, 0x2E, 0xFF, 0xE0
#define hw_usi0_cr			_r8, 0x2D, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_usi0_ies			_ob1, cr, 1, 7
#define hw_usi0_ieov			_ob1, cr, 1, 6
#define hw_usi0_iep			_ob1, cr, 1, 5
#define hw_usi0_wm			_ob1, cr, 2, 4
#define hw_usi0_cs			_ob1, cr, 2, 2
#define hw_usi0_clk			_ob1, cr, 1, 1
#define hw_usi0_tc			_ob1, cr, 1, 0

#define hw_usi0_ifs			_ob1, sr, 1, 7
#define hw_usi0_ifov			_ob1, sr, 1, 6
#define hw_usi0_ifp			_ob1, sr, 1, 5
#define hw_usi0_dc			_ob1, sr, 1, 4
#define hw_usi0_cnt			_ob1, sr, 4, 0

/*	USI used as SPI master with software clock
 */
#define hw_spimaster_swclk0		_usia_spimaster_swclk, usi0

/*	USI used as SPI master with counter0 overflow clock
 */
#define hw_spimaster_c0clk0		_usia_spimaster_c0clk, usi0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#include "../classes/acb_1.h"
#define hw_acmp0			_acb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */					
#define hw_acmp0_csr			_r8, 0x28, 0xDF, 0x10

/*	Object logical registers
 */					
#define hw_acmp0_acd			_ob1, csr, 1, 7
#define hw_acmp0_acbg			_ob1, csr, 1, 6
#define hw_acmp0_aco			_ob1, csr, 1, 5
#define hw_acmp0_if			_ob1, csr, 1, 4
#define hw_acmp0_ie			_ob1, csr, 1, 3
#define hw_acmp0_acis			_ob1, csr, 2, 0

#define hw_acmp0_acme			_xob1, adc0, srb,   1, 6
#define hw_acmp0_aden			_xob1, adc0, sra,   1, 7
#define hw_acmp0_admux			_xob1, adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/adc_1.h"
#define hw_adc0				_adc, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_adc0_admux			_r8,  0x27,   0xFF,   0x00
#define hw_adc0_sra			_r8,  0x26,   0xFF,   0x10
#define hw_adc0_adc			_r16, 0x24, 0x0000, 0x0000
#define hw_adc0_adch			_r8,  0x25,   0x00,   0x00
#define hw_adc0_srb			_r8,  0x23,   0xE7,   0x00

/*	Object logical registers
 */
#define hw_adc0_refs			_ob2, admux, 2, 6, 0, admux, 1, 4, 2
#define hw_adc0_lar			_ob1, admux, 1, 5
#define hw_adc0_mux			_ob1, admux, 4, 0

#define hw_adc0_en			_ob1, sra, 1, 7
#define hw_adc0_sc			_ob1, sra, 1, 6
#define hw_adc0_ate			_ob1, sra, 1, 5
#define hw_adc0_if			_ob1, sra, 1, 4
#define hw_adc0_ie			_ob1, sra, 1, 3
#define hw_adc0_ps			_ob1, sra, 3, 0

#define hw_adc0_bin			_ob1, srb, 1, 7
#define hw_adc0_ipr			_ob1, srb, 1, 5
#define hw_adc0_ts			_ob1, srb, 3, 0


/*******************************************************************************
 *									       *
 *	EEPROM								       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#include "../classes/eea_1.h"

/*	Object				class, address
 */
#define hw_eeprom0			_eea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__eea_ar			_r16, 0x3E, 0x01FF, 0x00
#define hw__eea_dr			_r8,  0x3D,   0xFF, 0x00
#define hw__eea_cr			_r8,  0x3C,   0x3F, 0x00

/*	Class logical registers
 */
#define hw__eea_pm			_cb1, cr, 2, 4
#define hw__eea_rie			_cb1, cr, 1, 3
#define hw__eea_mpe			_cb1, cr, 1, 2
#define hw__eea_pe			_cb1, cr, 1, 1
#define hw__eea_re			_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#include "../classes/fla_1.h"

/*	Object				class, address
 */
#define hw_flash0			_fla, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__fla_csr			_r8,  0x57, 0x3F, 0x00

/*	Class logical registers
 */
#define hw__fla_sigrd		_cb1, csr, 1, 5
#define hw__fla_rsig			_cb1, csr, 1, 5 /* old name */
#define hw__fla_rwwsre		_cb1, csr, 1, 4
#define hw__fla_ctpb			_cb1, csr, 1, 4 /* old name */
#define hw__fla_blbset		_cb1, csr, 1, 3
#define hw__fla_rflb			_cb1, csr, 1, 3 /* old name */
#define hw__fla_pgwrt		_cb1, csr, 1, 2
#define hw__fla_pgers		_cb1, csr, 1, 1
#define hw__fla_spmen		_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *			C O N T E X T					       *
 *									       *
 *******************************************************************************/


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;

  hwa_shared_t	shared ;

  hwa_corea_t	core0 ;
  hwa_gpa_t	port0 ;
  hwa_pxa_t	pcic0 ;
  hwa_wda_t	watchdog0 ;
  hwa_cta_t	counter0 ;
  hwa_psb_t	prescaler1 ;
  hwa_ctb_t	counter1 ;
  hwa_usia_t	usi0 ;
  hwa_acb_t	acmp0 ;
  hwa_adc_t	adc0 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/corea_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/pxa_2.h"
#include "../classes/wda_2.h"
#include "../classes/psa_2.h"
#include "../classes/oca_2.h"
#include "../classes/cta_2.h"
#include "../classes/ctb_2.h"
#include "../classes/ocb_2.h"
#include "../classes/psb_2.h"
#include "../classes/dtga_2.h"
#include "../classes/usia_2.h"
#include "../classes/adc_2.h"
#include "../classes/acb_2.h"
#include "../classes/eea_2.h"
#include "../classes/fla_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_r( shared, gimsk );
  _hwa_setup_r( shared, gifr	);
  _hwa_setup_r( shared, prr	);
  _hwa_setup_r( shared, gtccr );
  _hwa_setup_r( shared, timsk );
  _hwa_setup_r( shared, tifr	);
  _hwa_setup_r( shared, did	);

  _hwa_setup_o( core0 );

  _hwa_setup_o( port0 );
  _hwa_setup_o( pcic0 );
  _hwa_setup_o( watchdog0 );
  _hwa_setup_o( counter0 );
  _hwa_setup_o( prescaler1 );
  _hwa_setup_o( counter1 );

  _hwa_setup_o( usi0 );
  _hwa_setup_o( acmp0 );
  _hwa_setup_o( adc0 );
}

HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_r( shared, gimsk, 0 );
  _hwa_init_r( shared, gifr,	0 );
  _hwa_init_r( shared, prr,	0 );
  _hwa_init_r( shared, gtccr, 0 );
  _hwa_init_r( shared, timsk, 0 );
  _hwa_init_r( shared, tifr,	0 );
  _hwa_init_r( shared, did,	0 );

  _hwa_init_o( core0 );
  _hwa_init_o( port0 );
  _hwa_init_o( pcic0 );
  _hwa_init_o( watchdog0 );
  _hwa_init_o( counter0 );
  _hwa_init_o( prescaler1 );
  _hwa_init_o( counter1 );
  _hwa_init_o( usi0 );
  _hwa_init_o( acmp0 );
  _hwa_init_o( adc0 );
}

HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve_o( counter0 );
  _hwa_solve_o( counter1 );

  _hwa_commit_r( shared, gimsk );
  _hwa_commit_r( shared, gifr	 );
  _hwa_commit_o( core0 );
  _hwa_commit_r( shared, prr	 );

  _hwa_commit_o( watchdog0 );
  _hwa_commit_o( pcic0 );
  _hwa_commit_o( port0 );

  _hwa_commit_r( shared, gtccr );
  _hwa_commit_o( counter0 );
  _hwa_commit_r( shared, timsk );
  _hwa_commit_r( shared, tifr );

  _hwa_commit_o( prescaler1 );
  _hwa_commit_o( counter1 );
  _hwa_commit_o( usi0 );
  _hwa_commit_o( acmp0 );
  _hwa_commit_o( adc0 );
  _hwa_commit_r( shared, did );
}

#endif /* !defined __ASSEMBLER__ */
