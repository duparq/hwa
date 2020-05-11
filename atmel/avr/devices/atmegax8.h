
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega48A/PA/88A/PA/168A/PA/328/P devices
 * @page atmegax8 ATmega48A/PA/88A/PA/168A/PA/328/P
 */

#include "../hwa_1.h"

/**
 * @section atmegax8_object Objects
 *
 * __Note__ These objects are not all completely implemented yet.
 *
 * Object name		| Class				  | Comments
 * :--------------------|---------------------------------|:----------------------------------
 * `core0`		|@ref atmelavr_coreb "_coreb"	  |The core
 * `int0`		|@ref atmelavr_inta "_inta"	  |External interrupt INT0
 * `int1`		|@ref atmelavr_inta "_inta"	  |External interrupt INT1
 * `port0`		|@ref atmelavr_gpa "_gpa"	  |General purpose I/O port B (PORT0)
 * `port1`		|@ref atmelavr_gpa "_gpa"	  |General purpose I/O port C (PORT1)
 * `port2`		|@ref atmelavr_gpa "_gpa"	  |General purpose I/O port D (PORT2)
 * `pcic0`		|@ref atmelavr_pxa "_pxa"	  |Pin change interrupt controller
 * `pcic1`		|@ref atmelavr_pxa "_pxa"	  |Pin change interrupt controller
 * `pcic2`		|@ref atmelavr_pxa "_pxa"	  |Pin change interrupt controller
 * `watchdog0`		|@ref atmelavr_wdb "_wdb"	  |Watchdog (WDG)
 * `counter0`		|@ref atmelavr_cta "_cta"	  |8-bit counter-timer (T0)
 * `(counter0,compare0)`|@ref atmelavr_oca "_oca"	  |Compare unit 0 of counter0 (OC0A)
 * `(counter0,compare1)`|@ref atmelavr_oca "_oca"	  |Compare unit 1 of counter0 (OC0B)
 * `counter1`		|@ref atmelavr_ctd "_ctd"	  |16-bit counter-timer (T1)
 * `(counter1,compare0)`|@ref atmelavr_occ "_occ"	  |Compare unit 0 of counter1 (OC1A)
 * `(counter1,compare1)`|@ref atmelavr_occ "_occ"	  |Compare unit 1 of counter1 (OC1B)
 * `(counter1,capture0)`|@ref atmelavr_ica "_ica"	  |Capture unit 0 of counter1 (ICP1)
 * `counter2`		|@ref atmelavr_ctc "_ctc"	  |8-bit counter-timer (T2)
 * `(counter2,compare0)`|@ref atmelavr_oca "_oca"	  |Compare unit 0 of counter2 (OC2A)
 * `(counter2,compare1)`|@ref atmelavr_oca "_oca"	  |Compare unit 1 of counter2 (OC2B)
 * `prescaler0`		|@ref atmelavr_psa "_psa"	  |counter0/counter1 prescaler (PSC0)
 * `spi0`		|@ref atmelavr_spia "_spia"	  |Serial Peripheral Interface
 * `uart0`		|@ref atmelavr_uarta "_uarta"	  |Universal Asynchronous Receiver Transmitter
 * `twi0`		|@ref atmelavr_twia "_twia"	  |2-wire Serial Interface
 * `acmp0`		|@ref atmelavr_aca "_aca"	  |Analog Comparator
 * `adc0`		|@ref atmelavr_adb "_adb"	  |10-bit Analog to Digital Converter
 * `eeprom0`		|@ref atmelavr_eea "_eea" |Eeprom memory
 * `flash0`		|@ref atmelavr_fla "_fla"	  |Flash memory
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
 * @note This section needs to be rewritten.
 *
 * Some objects can be accessed from their relatives or can have more than one
 * name. There are the existing relations between the device's objects and their
 * different names:
 *
 * Name		 | Alias		| Path
 * :-------------|----------------------|:-----
 * `prescaler0`		 | `counter0prescaler`	    |`(counter0, prescaler)`
 * `prescaler0`		 | `counter0prescaler0`	    |`(counter0, prescaler0)`
 * `prescaler0`		 | `counter1prescaler`	    |`(counter1, prescaler)`
 * `prescaler0`		 | `counter1prescaler0`	    |`(counter1, prescaler0)`
 * `counter0compare0`	 | `counter0compare0`	    |`(counter0, compare0)`
 * `counter0compare1`	 | `counter0compare1`	    |`(counter0, compare1)`
 * `counter0`		 | `counter0compare0counter`|`(counter0compare0, counter)`
 * `counter0`		 | `counter0compare1counter`|`(counter0compare1, counter)`
 * `pin_counter0compare0`| `counter0compare0pin`    |`(counter0compare0, pin)`
 * `pin_counter0compare1`| `counter0compare1pin`    |`(counter0compare1, pin)`
 * `counter1compare0`	 | `counter1compare0`	    |`(counter1, compare0)`
 * `counter1compare1`	 | `counter1compare1`	    |`(counter1, compare1)`
 * `counter1`		 | `counter1compare0counter`|`(counter1compare0, counter)`
 * `counter1`		 | `counter1compare1counter`|`(counter1compare1, counter)`
 * `pin_counter1compare0`| `counter1compare0pin`    |`(counter1compare0, pin)`
 * `pin_counter1compare1`| `counter1compare1pin`    |`(counter1compare1, pin)`
 * `pin_counter1capture0`| `counter1capture0pin`    |`(counter1capture0, pin)`
 * `counter2`		 | `counter2compare0counter`|`(counter2compare0, counter)`
 * `counter2`		 | `counter2compare1counter`|`(counter2compare1, counter)`
 * `pin_counter2compare0`| `counter2compare0pin`    |`(counter2compare0, pin)`
 * `pin_counter2compare1`| `counter2compare1pin`    |`(counter2compare1, pin)`
 *
 */


/**
 * @page atmegax8
 * @subsection atmegax8_interrupts Interrupts
 * 
 * HWA interrupt name			   | Atmel name	  | Comments
 * :---------------------------------------|--------------|------------------------
 * `int0`				   | INT0	  | External Interrupt Request 0
 * `int1`				   | INT1	  | External Interrupt Request 1
 * `pcic0`				   | PCINT0	  | Pin Change Interrupt Request 0
 * `pcic1`				   | PCINT1	  | Pin Change Interrupt Request 1
 * `pcic2`				   | PCINT2	  | Pin Change Interrupt Request 2
 * `watchdog0`				   | WDT	  | Watchdog Time-out Interrupt
 * `counter2,compare0`			   | TIMER2 COMPA | Timer/Counter2 Compare Match A
 * `counter2,compare1`			   | TIMER2 COMPB | Timer/Counter2 Compare Match B
 * `counter2`<br>`counter2,overflow`	   | TIMER2 OVF	  | Timer/Counter2 Overflow
 * `counter1,capture0`			   | TIMER1 CAPT  | Timer/Counter1 Capture Event
 * `counter1,compare0`			   | TIMER1 COMPA | Timer/Counter1 Compare Match A
 * `counter1,compare1`			   | TIMER1 COMPB | Timer/Coutner1 Compare Match B
 * `counter1`<br>`counter1,overflow`	   | TIMER1 OVF	  | Timer/Counter1 Overflow
 * `counter0,compare0`			   | TIMER0 COMPA | Timer/Counter0 Compare Match A
 * `counter0,compare1`			   | TIMER0 COMPB | Timer/Counter0 Compare Match B
 * `counter0`<br>`counter0,overflow`	   | TIMER0 OVF	  | Timer/Counter0 Overflow
 * `spi0`				   | SPI,STC	  | SPI Serial Transfer Complete
 * `uart0,rxc`				   | USART,RXC	  | USART Rx Complete
 * `uart0,txqne`			   | USART,UDRE	  | USART, Data Register Empty
 * `uart0,txc`				   | USART,TXC	  | USART, Tx Complete
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
#define hw_int0_irq			_irq,  1, int0,	     ie,     if
#define hw_int1_irq			_irq,  2, int1,	     ie,     if
#define hw_pcic0_irq			_irq,  3, pcic0,     ie,     if
#define hw_pcic1_irq			_irq,  4, pcic1,     ie,     if
#define hw_pcic2_irq			_irq,  5, pcic2,     ie,     if
#define hw_watchdog0_irq		_irq,  6, watchdog0, ie,     if
#define hw_counter2_irq_compare0	_irq,  7, counter2,  ocie0,  ocif0
#define hw_counter2_compare0_irq	_irq,  7, counter2,  ocie0,  ocif0
#define hw_counter2_irq_compare1	_irq,  8, counter2,  ocie1,  ocif1
#define hw_counter2_compare1_irq	_irq,  8, counter2,  ocie1,  ocif1
#define hw_counter2_irq_overflow	_irq,  9, counter2,  ie,     if
#define hw_counter2_irq			_irq,  9, counter2,  ie,     if
#define hw_counter1_irq_capture0	_irq, 10, counter1,  icie0,  icif0
#define hw_counter1_capture0_irq	_irq, 10, counter1,  icie0,  icif0
#define hw_counter1_irq_compare0	_irq, 11, counter1,  ocie0,  ocif0
#define hw_counter1_compare0_irq	_irq, 11, counter1,  ocie0,  ocif0
#define hw_counter1_irq_compare1	_irq, 12, counter1,  ocie1,  ocif1
#define hw_counter1_compare1_irq	_irq, 12, counter1,  ocie1,  ocif1
#define hw_counter1_irq_overflow	_irq, 13, counter1,  ie,     if
#define hw_counter1_irq			_irq, 13, counter1,  ie,     if
#define hw_counter0_irq_compare0	_irq, 14, counter0,  ocie0,  ocif0
#define hw_counter0_compare0_irq	_irq, 14, counter0,  ocie0,  ocif0
#define hw_counter0_irq_compare1	_irq, 15, counter0,  ocie1,  ocif1
#define hw_counter0_compare1_irq	_irq, 15, counter0,  ocie1,  ocif1
#define hw_counter0_irq_overflow	_irq, 16, counter0,  ie,     if
#define hw_counter0_irq			_irq, 16, counter0,  ie,     if
#define hw_spi0_irq			_irq, 17, spi0,	     ie,     if
#define hw_spi0_irq_txc			_irq, 17, spi0,	     ie,     if
#define hw_uart0_irq			_irq,   , , , /* FIXME: should create a class for concatenation */
#define hw_uart0_irq_rxc		_irq, 18, uart0,     ierxc,  ifrxc
#define hw_uart0_irq_txqnf		_irq, 19, uart0,     ietxqe, iftxqnf
#define hw_uart0_irq_txc		_irq, 20, uart0,     ietxc,  iftxc
#define hw_adc0_irq			_irq, 21, adc0,	     ie,     if
#define hw_eeprom0_irq			_irq, 22, eeprom0,   ie,     /* no irq flag */
#define hw_eeprom0_irq_ready		_irq, 22, eeprom0,   ie,
#define hw_acmp0_irq			_irq, 23, acmp0,     ie,     if
#define hw_twi0_irq			_irq, 24, twi0,	     ie,     if
#define hw_flash0_irq			_irq, 25, flash0,    ie,     if


/**
 * @page atmegax8
 * @subsection atmegax8_pins Ports and pins
 *
 * Some of the pins may not be available depending on the fuses configuration.
 *
 * HWA name	| 32qfp/mlf   | Class			   | Atmel name
 * -------------|-------------|----------------------------|-----------
 * `portb`	|	      | @ref atmelavr_ioa "_ioa" | PORTB
 * `pb0` | `HW_PIN(12)` | @ref atmelavr_ioa "_ioa" | PB0
 * `pb1` | `HW_PIN(13)` | @ref atmelavr_ioa "_ioa" | PB1
 * `pb2` | `HW_PIN(14)` | @ref atmelavr_ioa "_ioa" | PB2
 * `pb3` | `HW_PIN(15)` | @ref atmelavr_ioa "_ioa" | PB3
 * `pb4` | `HW_PIN(16)` | @ref atmelavr_ioa "_ioa" | PB4
 * `pb5` | `HW_PIN(17)` | @ref atmelavr_ioa "_ioa" | PB5
 * `pb6` | `HW_PIN(7)`	| @ref atmelavr_ioa "_ioa" | PB6
 * `pb7` | `HW_PIN(8)`	| @ref atmelavr_ioa "_ioa" | PB7
 * `portc`	|	      | @ref atmelavr_ioa "_ioa" | PORTC
 * `pc0` | `HW_PIN(23)` | @ref atmelavr_ioa "_ioa" | PC0
 * `pc1` | `HW_PIN(24)` | @ref atmelavr_ioa "_ioa" | PC1
 * `pc2` | `HW_PIN(25)` | @ref atmelavr_ioa "_ioa" | PC2
 * `pc3` | `HW_PIN(26)` | @ref atmelavr_ioa "_ioa" | PC3
 * `pc4` | `HW_PIN(27)` | @ref atmelavr_ioa "_ioa" | PC4
 * `pc5` | `HW_PIN(28)` | @ref atmelavr_ioa "_ioa" | PC5
 * `pc6` | `HW_PIN(29)` | @ref atmelavr_ioa "_ioa" | PC6
 * `portd`	|	      | @ref atmelavr_ioa "_ioa" | PORTD
 * `pd0` | `HW_PIN(30)` | @ref atmelavr_ioa "_ioa" | PD0
 * `pd1` | `HW_PIN(31)` | @ref atmelavr_ioa "_ioa" | PD1
 * `pd2` | `HW_PIN(32)` | @ref atmelavr_ioa "_ioa" | PD2
 * `pd3` | `HW_PIN(1)`	| @ref atmelavr_ioa "_ioa" | PD3
 * `pd4` | `HW_PIN(2)`	| @ref atmelavr_ioa "_ioa" | PD4
 * `pd5` | `HW_PIN(9)`	| @ref atmelavr_ioa "_ioa" | PD5
 * `pd6` | `HW_PIN(10)` | @ref atmelavr_ioa "_ioa" | PD6
 * `pd7` | `HW_PIN(11)` | @ref atmelavr_ioa "_ioa" | PD7
 */


/**
 * @page atmegax8
 * @subsection atmegax8_pm Power Management
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

/**
 * @page atmegax8
 * @section atmegax8_device Symbols
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


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#define hw_class__shared
#define hw_shared			_shared, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_shared_did1			_r8, 0x7F, 0x03, 0x00	/* DID for AIN0/AIN1 */
#define hw_shared_did0			_r8, 0x7E, 0x3F, 0x00	/* DID for PORT1 */
#define hw_shared_eicr			_r8, 0x69, 0x0F, 0x00
#define hw_shared_pcicr			_r8, 0x68, 0x07, 0x00
#define hw_shared_prr			_r8, 0x64, 0xEF, 0x00
#define hw_shared_gpior2		_r8, 0x4B, 0xFF, 0x00
#define hw_shared_gpior1		_r8, 0x4A, 0xFF, 0x00
#define hw_shared_gtccr			_r8, 0x43, 0x83, 0x00
#define hw_shared_gpior0		_r8, 0x3E, 0xFF, 0x00
#define hw_shared_eimsk			_r8, 0x3D, 0x03, 0x00
#define hw_shared_eifr			_r8, 0x3C, 0x03, 0x03
#define hw_shared_pcifr			_r8, 0x3B, 0x07, 0x07

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

/*	Objects				class, address
 */
#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"

#define hw_port0			_gpa, 0x23
#define hw_port1			_gpa, 0x26
#define hw_port2			_gpa, 0x29

/*  Pins				class, port, bn, bp
 */
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)
#  define hw_pb0			_ioa, port0, 1, 0
#endif
#define hw_pb1				_ioa, port0, 1, 1
#define hw_pb2				_ioa, port0, 1, 2
#define hw_pb3				_ioa, port0, 1, 3
#define hw_pb4				_ioa, port0, 1, 4
#define hw_pb5				_ioa, port0, 1, 5

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pb6			_ioa, port0, 1, 6
#endif
#if !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pb7			_ioa, port0, 1, 7
#endif
#define hw_portb			_ioa, port0, 8, 0

#define hw_pc0				_ioa, port1, 1, 0
#define hw_pc1				_ioa, port1, 1, 1
#define hw_pc2				_ioa, port1, 1, 2
#define hw_pc3				_ioa, port1, 1, 3
#define hw_pc4				_ioa, port1, 1, 4
#define hw_pc5				_ioa, port1, 1, 5
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)
#  define hw_pc6			_ioa, port1, 1, 6
#endif
#define hw_portc			_ioa, port1, 7, 0

/*  TODO: handle these special pins differently.
 */
#define hw_pc6a				_ioa, port1, 1, 8
#define hw_pc7a				_ioa, port1, 1, 9

#define hw_pd0				_ioa, port2, 1, 0
#define hw_pd1				_ioa, port2, 1, 1
#define hw_pd2				_ioa, port2, 1, 2
#define hw_pd3				_ioa, port2, 1, 3
#define hw_pd4				_ioa, port2, 1, 4
#define hw_pd5				_ioa, port2, 1, 5
#define hw_pd6				_ioa, port2, 1, 6
#define hw_pd7				_ioa, port2, 1, 7
#define hw_portd			_ioa, port2, 8, 0

/*  Digital input disable bits for analog input pins
 */
#define hw_pc0_did			_xob1, shared, did0, 1, 0	/* ADC0 */
#define hw_pc1_did			_xob1, shared, did0, 1, 1	/* ADC1 */
#define hw_pc2_did			_xob1, shared, did0, 1, 2	/* ADC2 */
#define hw_pc3_did			_xob1, shared, did0, 1, 3	/* ADC3 */
#define hw_pc4_did			_xob1, shared, did0, 1, 4	/* ADC4 */
#define hw_pc5_did			_xob1, shared, did0, 1, 5	/* ADC5 */

#define hw_pd6_did			_xob1, shared, did1, 1, 0	/* AIN0 */
#define hw_pd7_did			_xob1, shared, did1, 1, 1	/* AIN1 */

/*  Relative pin change controllers
 *
 *  FIXME: these declarations are necessary for _HW_REL() since it does not look
 *  for class method (i.e. _swarta).
 */
#define hw_pb0_pcic			pcic0
#define hw_pb1_pcic			pcic0
#define hw_pb2_pcic			pcic0
#define hw_pb3_pcic			pcic0
#define hw_pb4_pcic			pcic0
#define hw_pb5_pcic			pcic0
#define hw_pb6_pcic			pcic0
#define hw_pb7_pcic			pcic0

#define hw_pc0_pcic			pcic1
#define hw_pc1_pcic			pcic1
#define hw_pc2_pcic			pcic1
#define hw_pc3_pcic			pcic1
#define hw_pc4_pcic			pcic1
#define hw_pc5_pcic			pcic1
#define hw_pc6_pcic			pcic1

#define hw_pd0_pcic			pcic2
#define hw_pd1_pcic			pcic2
#define hw_pd2_pcic			pcic2
#define hw_pd3_pcic			pcic2
#define hw_pd4_pcic			pcic2
#define hw_pd5_pcic			pcic2
#define hw_pd6_pcic			pcic2
#define hw_pd7_pcic			pcic2

/* #define _hw_port0_pcic			pcic0 */
/* #define _hw_port1_pcic			pcic1 */
/* #define _hw_port2_pcic			pcic2 */


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
#define _hw_pin_adc6			, pc6a
#define _hw_pin_adc7			, pc7a

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
#  define _hw_pin_19			, pc6a
#  define _hw_pin_22			, pc7a
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

/*	Object				class, address
 */
#include "../classes/coreb_1.h"
#define hw_core0			_coreb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_core0_osccal			_r8, 0x66, 0xFF, 0x00
#define hw_core0_sreg			_r8, 0x5F, 0xFF, 0x00
#define hw_core0_sph			_r8, 0x5E, 0x03, 0x00
#define hw_core0_spl			_r8, 0x5D, 0xFF, 0x00
#define hw_core0_mcucr			_r8, 0x55, 0x73, 0x00
#define hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define hw_core0_smcr			_r8, 0x53, 0x0F, 0x00

/*	Object logical registers
 */
#define hw_core0_bods			_ob1, mcucr, 1, 6
#define hw_core0_bodse			_ob1, mcucr, 1, 5
#define hw_core0_pud			_ob1, mcucr, 1, 4
#define hw_core0_ivsel			_ob1, mcucr, 1, 1
#define hw_core0_ivce			_ob1, mcucr, 1, 0

#define hw_core0_wdrf			_ob1, mcusr, 1, 3
#define hw_core0_borf			_ob1, mcusr, 1, 2
#define hw_core0_extrf			_ob1, mcusr, 1, 1
#define hw_core0_porf			_ob1, mcusr, 1, 0
#define hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */

#define hw_core0_sm			_ob1, smcr, 3, 1
#define hw_core0_se			_ob1, smcr, 1, 0


/*******************************************************************************
 *									       *
 *	External interrupt controllers					       *
 *									       *
 *******************************************************************************/

#include "../classes/inta_1.h"

/*	Object				class, address
 */
#define hw_int0				_inta, 0

/*	Object logical registers
 */
#define hw_int0_sc			_xob1, shared, eicr,  2, 0
#define hw_int0_ie			_xob1, shared, eimsk, 1, 0
#define hw_int0_if			_xob1, shared, eifr,  1, 0

/*	Object				class, address
 */
#define hw_int1				_inta, 0

/*	Object logical registers
 */
#define hw_int1_sc			_xob1, shared, eicr,  2, 2
#define hw_int1_ie			_xob1, shared, eimsk, 1, 1
#define hw_int1_if			_xob1, shared, eifr,  1, 1


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

#include "../classes/pxa_1.h"

/*	Object				class, address
 */
#define hw_pcic0			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic0_msk			_r8, 0x6B, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_pcic0_ie			_xob1, shared, pcicr, 1, 0
#define hw_pcic0_if			_xob1, shared, pcifr, 1, 0

/*	Object				class, address
 */
#define hw_pcic1			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic1_msk			_r8, 0x6C, 0x7F, 0x00

/*	Object logical registers
 */
#define hw_pcic1_ie			_xob1, shared, pcicr, 1, 1
#define hw_pcic1_if			_xob1, shared, pcifr, 1, 1

/*	Object				class, address
 */
#define hw_pcic2			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic2_msk			_r8, 0x6D, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_pcic2_ie			_xob1, shared, pcicr, 1, 2
#define hw_pcic2_if			_xob1, shared, pcifr, 1, 2


/*******************************************************************************
 *									       *
 *	hw_watchdog0: watchdog						       *
 *									       *
 *******************************************************************************/

#include "../classes/wdb_1.h"

/*	Object				class, address
 */
#define hw_watchdog0			_wdb, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__wdb_csr			_r8, 0x60, 0xFF, 0x80

/*	Class logical registers
 */
#define hw__wdb_wdrf			_xob1, core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0/1 prescaler						       *
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
 *	Counter 0							       *
 *									       *
 *******************************************************************************/

#include "../classes/oca_1.h"
#include "../classes/cta_1.h"

/*	Object				class, address
 */
#define hw_counter0			_cta, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter0_imsk		_r8, 0x6E, 0x07, 0x00
#define hw_counter0_ocr1		_r8, 0x48, 0xFF, 0x00	/* OCR0B */
#define hw_counter0_ocr0		_r8, 0x47, 0xFF, 0x00	/* OCR0A */
#define hw_counter0_ccra		_r8, 0x44, 0xF3, 0x00
#define hw_counter0_ccrb		_r8, 0x45, 0xCF, 0x00
#define hw_counter0_count		_r8, 0x46, 0xFF, 0x00
#define hw_counter0_ifr			_r8, 0x35, 0x07, 0x07

/*	Logical registers
 */
#define hw_counter0_com0		_ob1, ccra, 2, 6
#define hw_counter0_com1		_ob1, ccra, 2, 4
#define hw_counter0_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_counter0_foc0		_ob1, ccrb, 1, 7
#define hw_counter0_foc1		_ob1, ccrb, 1, 6
#define hw_counter0_cs			_ob1, ccrb, 3, 0

#define hw_counter0_ocie1		_ob1, imsk, 1, 2
#define hw_counter0_ocie0		_ob1, imsk, 1, 1
#define hw_counter0_ie			_ob1, imsk, 1, 0

#define hw_counter0_ocif1		_ob1, ifr,  1, 2
#define hw_counter0_ocif0		_ob1, ifr,  1, 1
#define hw_counter0_if			_ob1, ifr,  1, 0

#define hw_counter0_prr			_xob1, shared, prr, 1, 5

/*	Relatives
 */
#define hw_counter0_prescaler0		prescaler0
#define hw_counter0_prescaler		prescaler0

#define hw_counter0_compare0		_oca, counter0, 0
#define hw_counter0_compare0_pin	pd6
#define hw_counter0_compare0_counter	counter0

#define hw_counter0_compare1		_oca, counter0, 1
#define hw_counter0_compare1_pin	pd5
#define hw_counter0_compare1_counter	counter0


/*******************************************************************************
 *									       *
 *	Counter 1							       *
 *									       *
 *******************************************************************************/

#include "../classes/occ_1.h"
#include "../classes/ica_1.h"
#include "../classes/ctd_1.h"

/*	Object				class, address
 */
#define hw_counter1			_ctd, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter1_ocr1		_r16, 0x8A, 0xFFFF, 0x0000	/* OCR1B */
#define hw_counter1_ocr0		_r16, 0x88, 0xFFFF, 0x0000	/* OCR1A */
#define hw_counter1_icr0		_r16, 0x86, 0xFFFF, 0x0000	/* ICR1 */
#define hw_counter1_count		_r16, 0x84, 0xFFFF, 0x0000
#define hw_counter1_ccrc		_r8,  0x82, 0xC0,   0x00
#define hw_counter1_ccrb		_r8,  0x81, 0xDF,   0x00
#define hw_counter1_ccra		_r8,  0x80, 0xF3,   0x00
#define hw_counter1_imsk		_r8,  0x6F, 0x27,   0x00
#define hw_counter1_ifr			_r8,  0x36, 0x27,   0x27

/*	Logical registers
 */
#define hw_counter1_foc0		_ob1, ccrc, 1, 7
#define hw_counter1_foc1		_ob1, ccrc, 1, 6

#define hw_counter1_icnc		_ob1, ccrb, 1, 7
#define hw_counter1_ices		_ob1, ccrb, 1, 6
#define hw_counter1_cs			_ob1, ccrb, 3, 0
#define hw_counter1_wgm			_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define hw_counter1_com0		_ob1, ccra, 2, 6
#define hw_counter1_com1		_ob1, ccra, 2, 4

#define hw_counter1_icie0		_ob1, imsk, 1, 5
#define hw_counter1_ocie1		_ob1, imsk, 1, 2
#define hw_counter1_ocie0		_ob1, imsk, 1, 1
#define hw_counter1_ie			_ob1, imsk, 1, 0

#define hw_counter1_icif0		_ob1, ifr,  1, 5
#define hw_counter1_ocif1		_ob1, ifr,  1, 2
#define hw_counter1_ocif0		_ob1, ifr,  1, 1
#define hw_counter1_if			_ob1, ifr,  1, 0

#define hw_counter1_prr			_xob1, shared, prr, 1, 3

#define hw_counter1_acic		_xob1, acmp0,  csr, 1, 2

/*	Relatives
 */
#define hw_counter1_prescaler0		prescaler0
#define hw_counter1_prescaler		prescaler0

#define hw_counter1_compare0		_occ, counter1, 0
#define hw_counter1_compare0_pin	pb1
#define hw_counter1_compare0_counter	counter1

#define hw_counter1_compare1		_occ, counter1, 1
#define hw_counter1_compare1_pin	pb2
#define hw_counter1_compare1_counter	counter1

#define hw_counter1_capture0		_ica, counter1, 0
#define hw_counter1_capture0_pin	pb0
#define hw_counter1_capture0_counter	counter1


/*******************************************************************************
 *									       *
 *	prescaler2: counter2 prescaler					       *
 *									       *
 *	prescaler0 and prescaler2 share the same tsm bit		       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#define hw_prescaler2			_psa, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define hw_prescaler2_tsm		_xob1, shared, gtccr, 1, 7
#define hw_prescaler2_psr		_xob1, shared, gtccr, 1, 1

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define hw_prescaler2_tsmpsr		_xob2, shared, gtccr, 1, 7, 1, gtccr, 1, 1, 0


/*******************************************************************************
 *									       *
 *	Counter 2							       *
 *									       *
 *******************************************************************************/

#include "../classes/ctc_1.h"	/* was ctb */

/*	Object				class, address
 */
#define hw_counter2			_ctc, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter2_assr		_r8, 0xB6, 0x60, 0x00
#define hw_counter2_ocr1		_r8, 0xB4, 0xFF, 0x00	/* OCR2B */
#define hw_counter2_ocr0		_r8, 0xB3, 0xFF, 0x00	/* OCR2A */
#define hw_counter2_count		_r8, 0xB2, 0xFF, 0x00
#define hw_counter2_ccrb		_r8, 0xB1, 0xCF, 0x00
#define hw_counter2_ccra		_r8, 0xB0, 0xF3, 0x00
#define hw_counter2_imsk		_r8, 0x70, 0x07, 0x00
#define hw_counter2_ifr			_r8, 0x37, 0x07, 0x07

/*	Logical registers
 */
#define hw_counter2_com0		_ob1, ccra, 2, 6
#define hw_counter2_com1		_ob1, ccra, 2, 4
#define hw_counter2_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_counter2_foc0		_ob1, ccrb, 1, 7
#define hw_counter2_foc1		_ob1, ccrb, 1, 6
#define hw_counter2_cs			_ob1, ccrb, 3, 0

#define hw_counter2_ocie1		_ob1, imsk, 1, 2
#define hw_counter2_ocie0		_ob1, imsk, 1, 1
#define hw_counter2_ie			_ob1, imsk, 1, 0

#define hw_counter2_ocif1		_ob1, ifr,  1, 2
#define hw_counter2_ocif0		_ob1, ifr,  1, 1
#define hw_counter2_if			_ob1, ifr,  1, 0

#define hw_counter2_prr			_xob1, shared, prr, 1, 6

/*	Relatives
 */
#define hw_counter2_prescaler0		prescaler2
#define hw_counter2_prescaler		prescaler2

#define hw_counter2_compare0		_oca, counter2, 0
#define hw_counter2_compare0_pin	pb3
#define hw_counter2_compare0_counter	counter2

#define hw_counter2_compare1		_oca, counter2, 1
#define hw_counter2_compare1_pin	pd3
#define hw_counter2_compare1_counter	counter2


/*******************************************************************************
 *									       *
 *	Serial Peripheral Interface					       *
 *									       *
 *******************************************************************************/

#include "../classes/spia_1.h"

/*	Object				class, address
 */
#define hw_spi0				_spia, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_spi0_dr			_r8, 0x4E, 0xFF, 0x00
#define hw_spi0_sr			_r8, 0x4D, 0xFF, 0x00
#define hw_spi0_cr			_r8, 0x4C, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_spi0_ie			_ob1, cr, 1, 7
#define hw_spi0_en			_ob1, cr, 1, 6
#define hw_spi0_dord			_ob1, cr, 1, 5
#define hw_spi0_mstr			_ob1, cr, 1, 4
#define hw_spi0_cpol			_ob1, cr, 1, 3
#define hw_spi0_cpha			_ob1, cr, 1, 2
#define hw_spi0_mode			_ob1, cr, 2, 2	/* convenient */

#define hw_spi0_if			_ob1, sr, 1, 7
#define hw_spi0_wpol			_ob1, sr, 1, 6

#define hw_spi0_xpr			_ob2, sr, 1, 0, 2, cr, 2, 0, 0

/*	Relatives
 */
#define hw_spi0_pin_mosi		pb3
#define hw_spi0_pin_miso		pb4
#define hw_spi0_pin_sck			pb5
#define hw_spi0_pin_ss			pb2


/*******************************************************************************
 *									       *
 *	UART								       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Object
 */
#define hw_uart0			_uarta, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__uarta_dr			_r8,  0xC6, 0xFF,   0x00
#define hw__uarta_ubrr			_r16, 0xC4, 0x0FFF, 0x0000
#define hw__uarta_csrc			_r8,  0xC2, 0xFF,   0x00
#define hw__uarta_csrb			_r8,  0xC1, 0xFD,   0x00
#define hw__uarta_csra			_r8,  0xC0, 0x43,   0x40

/*	Class logical registers
 */
#define hw__uarta_brr			_cb1, ubrr, 12, 0

#define hw__uarta_ifrxc			_cb1, csra, 1, 7
#define hw__uarta_iftxc			_cb1, csra, 1, 6
#define hw__uarta_iftxqnf		_cb1, csra, 1, 5
#define hw__uarta_fe			_cb1, csra, 1, 4
#define hw__uarta_dor			_cb1, csra, 1, 3
#define hw__uarta_pe			_cb1, csra, 1, 2
#define hw__uarta_2x			_cb1, csra, 1, 1
#define hw__uarta_mpcm			_cb1, csra, 1, 0

#define hw__uarta_ierxc			_cb1, csrb, 1, 7
#define hw__uarta_ietxc			_cb1, csrb, 1, 6
#define hw__uarta_ietxqnf		_cb1, csrb, 1, 5
#define hw__uarta_rxen			_cb1, csrb, 1, 4
#define hw__uarta_txen			_cb1, csrb, 1, 3
#define hw__uarta_rxb8			_cb1, csrb, 1, 1
#define hw__uarta_txb8			_cb1, csrb, 1, 0

#define hw__uarta_msel			_cb1, csrc, 2, 6
#define hw__uarta_pm			_cb1, csrc, 2, 4
#define hw__uarta_sbs			_cb1, csrc, 1, 3
#define hw__uarta_cpol			_cb1, csrc, 1, 0

#define hw__uarta_csz			_cb2, csrb, 1, 2, 2, csrc, 2, 1, 0

/*	Object logical registers
 */
#define hw_uart0_prr			_xob1, shared, prr, 1, 1


/*******************************************************************************
 *									       *
 *	2-wire interface						       *
 *									       *
 *******************************************************************************/

#include "../classes/twia_1.h"

/*	Object
 */
#define hw_twi0				_twia, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__twia_br			_r8, 0xB8, 0xFF, 0x00
#define hw__twia_cr			_r8, 0xBC, 0xF5, 0x80
#define hw__twia_sr			_r8, 0xB9, 0x03, 0x00
#define hw__twia_dr			_r8, 0xBB, 0xFF, 0x00
#define hw__twia_ar			_r8, 0xBA, 0xFF, 0x00
#define hw__twia_amr			_r8, 0xBD, 0xFE, 0x00

/*	Relatives
 */
#define hw_twi0_pin_scl			pc5
#define hw_twi0_pin_sda			pc4


/*******************************************************************************
 *									       *
 *	acmp0: analog comparator					       *
 *									       *
 *******************************************************************************/

#include "../classes/aca_1.h"

/*	Object				class, address
 */					
#define hw_acmp0			_aca, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__aca_csr			_r8, 0x50, 0xDF, 0x10

/*	Object hardware registers
 *	  Required for _hw_counter1capture0_acic
 */
#define hw_acmp0_csr			_r8, 0x50, 0xDF, 0x10

/*	Object logical registers
 */
#define hw_acmp0_acme			_xob1, adc0, srb,   1, 6
#define hw_acmp0_aden			_xob1, adc0, sra,   1, 7
#define hw_acmp0_admux			_xob1, adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/adb_1.h"

/*	Object				class, address
 */					
#define hw_adc0				_adb, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__adb_admux			_r8,  0x7C,   0xEF,   0x00
#define hw__adb_sra			_r8,  0x7A,   0xFF,   0x10
#define hw__adb_adc			_r16, 0x78, 0x0000, 0x0000
#define hw__adb_adch			_r8,  0x79,   0x00,   0x00
#define hw__adb_adcl			_r8,  0x78,   0x00,   0x00
#define hw__adb_srb			_r8,  0x7B,   0x47,   0x00

/*	Object hardware registers	class, address, write mask, flags mask
 *
 *	These are necessary for acmp0, and analog input pin configuration
 *	that needs access to the did register of the ADC object.
 */					
#define hw_adc0_admux			_r8,  0x7C,   0xEF,   0x00
#define hw_adc0_sra			_r8,  0x7A,   0xFF,   0x10
#define hw_adc0_srb			_r8,  0x7B,   0x47,   0x00

/*	Class logical registers
 */					
#define hw__adb_refs			_cb1, admux, 2, 6
#define hw__adb_lar			_cb1, admux, 1, 5
#define hw__adb_mux			_cb1, admux, 4, 0

#define hw__adb_en			_cb1, sra, 1, 7
#define hw__adb_sc			_cb1, sra, 1, 6
#define hw__adb_ate			_cb1, sra, 1, 5
#define hw__adb_if			_cb1, sra, 1, 4
#define hw__adb_ie			_cb1, sra, 1, 3
#define hw__adb_ps			_cb1, sra, 3, 0

#define hw__adb_me			_cb1, srb, 1, 6
#define hw__adb_ts			_cb1, srb, 3, 0

/*	Object logical registers
 */
#define hw_adc0_prr			_xob1, shared, prr, 1, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define hw_class__eea

/*	Object				class, address
 */					
#define hw_eeprom0			_eea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__eea_arh			_r8,  0x42,   0x03, 0x00
#define hw__eea_arl			_r8,  0x41,   0xFF, 0x00
#define hw__eea_ar			_r16, 0x41, 0x03FF, 0x00
#define hw__eea_dr			_r8,  0x40,   0xFF, 0x00
#define hw__eea_cr			_r8,  0x3F,   0x3F, 0x00

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

#define hw_class__fla

/*	Object				class, address
 */					
#define hw_flash0			_fla, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__fla_csr			_r8, 0x57, 0xBF, 0x00

/*	Class logical registers
 */					
#define hw__fla_spmie			_cb1, csr, 1, 7
#define hw__fla_rwwsb			_cb1, csr, 1, 6
#define hw__fla_sigrd			_cb1, csr, 1, 5
#define hw__fla_rwwsre			_cb1, csr, 1, 4
#define hw__fla_blbset			_cb1, csr, 1, 3
#define hw__fla_pgwrt			_cb1, csr, 1, 2
#define hw__fla_pgers			_cb1, csr, 1, 1
#define hw__fla_spmen			_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;

  hwa_coreb_t	core0 ;
  hwa_gpa_t	port0 ;
  hwa_gpa_t	port1 ;
  hwa_gpa_t	port2 ;
  hwa_pxa_t	pcic0 ;
  hwa_pxa_t	pcic1 ;
  hwa_pxa_t	pcic2 ;
  hwa_wdb_t	watchdog0 ;

  hwa_cta_t	counter0 ;
  /* hwa_oca_t	counter0compare0 ; */
  /* hwa_oca_t	counter0compare1 ; */

  hwa_ctd_t	counter1 ;
  /* hwa_occ_t	counter1compare0 ; */
  /* hwa_occ_t	counter1compare1 ; */
  /* hwa_ica_t	counter1capture0 ; */

  hwa_ctc_t	counter2 ;
  /* hwa_oca_t	counter2compare0 ; */
  /* hwa_oca_t	counter2compare1 ; */

  hwa_spia_t	spi0 ;
  hwa_uarta_t	uart0 ;
  hwa_twia_t	twi0 ;
  hwa_aca_t	acmp0 ;
  hwa_adb_t	adc0 ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/coreb_2.h"
#include "../classes/inta_2.h"
#include "../classes/pxa_2.h"
#include "../classes/wdb_2.h"
#include "../classes/oca_2.h"
#include "../classes/cta_2.h"
#include "../classes/ctc_2.h"
#include "../classes/ica_2.h"
#include "../classes/occ_2.h"
#include "../classes/ctd_2.h"
#include "../classes/psa_2.h"
#include "../classes/spia_2.h"
#include "../classes/uarta_2.h"
#include "../classes/twia_2.h"
#include "../classes/aca_2.h"
#include "../classes/adb_2.h"
#include "../classes/eea_2.h"
#include "../classes/fla_2.h"
#include "../classes/swuarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_r( shared, eimsk );
  _hwa_setup_r( shared, eifr	);
  _hwa_setup_r( shared, eicr	);
  _hwa_setup_r( shared, gtccr );
  _hwa_setup_r( shared, prr	);
  _hwa_setup_r( shared, did1	);
  _hwa_setup_r( shared, did0	);
  _hwa_setup_r( shared, pcicr	 );
  _hwa_setup_r( shared, pcifr	 );

  _hwa_setup_o( core0 );
  _hwa_setup_o( port0 );
  _hwa_setup_o( port1 );
  _hwa_setup_o( port2 );
  _hwa_setup_o( pcic0 );
  _hwa_setup_o( pcic1 );
  _hwa_setup_o( pcic2 );
  _hwa_setup_o( watchdog0 );
  _hwa_setup_o( counter0 );
  _hwa_setup_o( counter1 );
  _hwa_setup_o( counter2 );

  _hwa_setup_o( spi0 );
  _hwa_setup_o( uart0 );
  _hwa_setup_o( twi0 );
  _hwa_setup_o( acmp0 );
  _hwa_setup_o( adc0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_r( shared, eimsk, 0 );
  _hwa_init_r( shared, eifr,	0 );
  _hwa_init_r( shared, eicr,	0 );
  _hwa_init_r( shared, gtccr, 0 );
  _hwa_init_r( shared, prr,	0 );
  _hwa_init_r( shared, did1,	0 );
  _hwa_init_r( shared, did0,	0 );
  _hwa_init_r( shared, pcicr, 0 );
  _hwa_init_r( shared, pcifr, 0 );

  _hwa_init_o( core0 );
  _hwa_init_o( port0 );
  _hwa_init_o( port1 );
  _hwa_init_o( port2 );
  _hwa_init_o( pcic0 );
  _hwa_init_o( pcic1 );
  _hwa_init_o( pcic2 );
  _hwa_init_o( watchdog0 );
  _hwa_init_o( counter0 );
  _hwa_init_o( counter1 );
  _hwa_init_o( counter2 );
  _hwa_init_o( spi0 );
  _hwa_init_o( uart0 );
  _hwa_init_o( twi0 );
  _hwa_init_o( acmp0 );
  _hwa_init_o( adc0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve_o( counter0 );
  _hwa_solve_o( counter1 );
  _hwa_solve_o( counter2 );

  _hwa_commit_r( shared, eimsk );
  _hwa_commit_r( shared, eifr	 );
  _hwa_commit_r( shared, eicr	 );
  _hwa_commit_o( core0 );
  _hwa_commit_r( shared, prr	 );
  _hwa_commit_o( watchdog0 );
  _hwa_commit_o( port0 );
  _hwa_commit_o( port1 );
  _hwa_commit_o( port2 );
  _hwa_commit_r( shared, pcifr );
  _hwa_commit_r( shared, pcicr );
  _hwa_commit_o( pcic0 );
  _hwa_commit_o( pcic1 );
  _hwa_commit_o( pcic2 );

  _hwa_commit_r( shared, gtccr );
  _hwa_commit_o( counter0 );
  _hwa_commit_o( counter1 );
  _hwa_commit_o( counter2 );

  _hwa_commit_o( spi0  );
  _hwa_commit_o( uart0 );
  _hwa_commit_o( twi0  );
  _hwa_commit_o( acmp0 );
  _hwa_commit_r( shared, did1	 );
  _hwa_commit_o( adc0 );
  _hwa_commit_r( shared, did0	 );
}

#endif /* !defined __ASSEMBLER__ */
