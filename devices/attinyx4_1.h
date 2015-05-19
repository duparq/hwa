
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @page atmelavr_attinyx4 Atmel AVR ATtiny24 ATtiny44 ATtiny84
 * @par Device definition
 *
 * You must define `HW_DEVICE` according to the name of your target before
 * including `hwa.h`. Optionnaly, other symbols can also be defined to
 * describe the target more precisely.
 *
 * Symbol               | Valid values | Comments
 * ---------------------|--------------|:-----------
 * `HW_DEVICE`          | `attiny24`<br>`attiny44`<br>`attiny84` | Name of the device
 * `HW_DEVICE_PACKAGE`  | `14pdip`     | Packaging of the device. This gives the possibility to use pins named by their number.
 */
#define HW_DEVICE_ATTINYX4

#define HW_DEVICE_RAM_START		0x0060
#define HW_DEVICE_APP_START		0x0022


/**
 * @page atmelavr_attinyx4
 * @par Symbols
 *
 * HWA defines a few symbols:
 * 
 * Symbol               | Definition
 * ---------------------|-----------
 * `HW_DEVICE_ATTINYX4` | Void
 * `HW_DEVICE_ATMELAVR` | Void
 * `HW_FLASHSIZE`       | Size of the flash memory in bytes
 * `HW_EEPROMSIZE`      | Size of the eeprom memory in bytes
 * `HW_RAMSIZE`         | Size of the ram memory in bytes
 * 
 */

#include "atmel/avr/1.h"

#include "atmel/avr/corea_1.h"
#include "atmel/avr/io_1.h"
#include "atmel/avr/pcica_1.h"
#include "atmel/avr/wdoga_1.h"
#include "atmel/avr/c8a_1.h"
#include "atmel/avr/c16a_1.h"
#include "atmel/avr/ocua_1.h"
#include "atmel/avr/icua_1.h"
#include "atmel/avr/usia_1.h"
#include "atmel/avr/acmpa_1.h"
#include "atmel/avr/ad10a_1.h"

/**
 * @page atmelavr_attinyx4
 * @par Objects
 * 
 * Name                   | Class                 | Comments
 * -----------------------|-----------------------|:--------------------------------------
 * `hw_core0`             | @ref atmelavr_corea   | The core
 * `hw_porta`             | @ref atmelavr_io8a    | General purpose I/O port A (PORTA)
 * `hw_portb`             | @ref atmelavr_io8a    | General purpose I/O port B (PORTB)
 * `hw_wdog0`         | @ref atmelavr_wdoga   | Watchdog (WDG)
 * `hw_counter0`          | @ref atmelavr_c8a     | 8-bit counter-timer (T0)
 * `hw_counter0_compare0` | @ref atmelavr_ocua    | Compare unit 0 of hw_counter0 (OC0A)
 * `hw_counter0_compare1` | @ref atmelavr_ocua    | Compare unit 1 of hw_counter0 (OC0B)
 * `hw_counter1`          | @ref atmelavr_c16a    | 16-bit counter-timer (T1)
 * `hw_counter1_compare0` | @ref atmelavr_ocua    | Compare unit 0 of hw_counter0 (OC1A)
 * `hw_counter1_compare1` | @ref atmelavr_ocua    | Compare unit 1 of hw_counter0 (OC1B)
 * `hw_counter1_capture0` | @ref atmelavr_icua    | Capture unit 0 of hw_counter0 (ICP)
 * `hw_psc0`              | @ref atmelavr_psca    | hw_counter0/hw_counter1 prescaler (PSC0)
 * `hw_usi0`              | @ref atmelavr_usia    | Universal Serial Interface
 * `hw_acmp0`             | @ref atmelavr_acmpa   | Analog Comparator
 * `hw_adc0`              | @ref atmelavr_ad10a   | 10-bit Analog to Digital Converter
 * `hw_eeprom0`           | @ref atmelavr_eeproma | Eeprom memory
 * `hw_flash0`            | @ref atmelavr_flasha  | Flash memory
 * 
 * A few additionnal objects are defined for convenience.
 * 
 * Name                   | Class                 | Comments
 * -----------------------|-----------------------|:--------------------------------------
 * `hw_spimaster0_swclk`  | @ref atmelavr_usia_spimaster_swclk | Universal Serial Interface used as SPI master and clocked by software
 * `hw_swuart0`           | @ref atmelavr_swuarta | Software UART
 * `hw_swuart1`           | @ref atmelavr_swuarta | Software UART
 *
 * <br>
 */


#define HWA_DCL					\
  hwa_corea_t	hw_core0 ;			\
  hwa_io8a_t	hw_porta ;			\
  hwa_io8a_t	hw_portb ;			\
  hwa_pcica_t	hw_pcic0 ;			\
  hwa_wdoga_t	hw_wdog0 ;			\
  hwa_c8a_t	hw_counter0 ;			\
  hwa_c16a_t	hw_counter1 ;			\
  hwa_usia_t	hw_usi0 ;			\
  hwa_acmpa_t	hw_acmp0 ;			\
  hwa_ad10a_t	hw_adc0 ;


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

#define _hw_irq_hw_core0_int0		_irq,  1, hw_core0,    int0,  intf0
#define _hw_irq_hw_pin_pa0_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa1_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa2_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa3_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa4_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa5_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa6_change	_irq,  2, hw_pcic0,    irqe0, irqf0
#define _hw_irq_hw_pin_pa7_change	_irq,  2, hw_pcic0,    irqe0, irqf0

#define _hw_irq_hw_pin_pb0_change	_irq,  3, hw_pcic0,    irqe1, irqf1
#define _hw_irq_hw_pin_pb1_change	_irq,  3, hw_pcic0,    irqe1, irqf1
#define _hw_irq_hw_pin_pb2_change	_irq,  3, hw_pcic0,    irqe1, irqf1
#define _hw_irq_hw_pin_pb3_change	_irq,  3, hw_pcic0,    irqe1, irqf1

#define _hw_irq_hw_wdog0		_irq,  4, hw_wdog0,    wdie,  wdif
#define _hw_irq_hw_counter1_capture0	_irq,  5, hw_counter1, icie,  icf
#define _hw_irq_hw_counter1_compare0	_irq,  6, hw_counter1, ociea, ocfa
#define _hw_irq_hw_counter1_compare1	_irq,  7, hw_counter1, ocieb, ocfb
#define _hw_irq_hw_counter1_overflow	_irq,  8, hw_counter1, oie,   ov
#define _hw_irq_hw_counter0_compare0	_irq,  9, hw_counter0, ociea, ocfa
#define _hw_irq_hw_counter0_compare1	_irq, 10, hw_counter0, ocieb, ocfb
#define _hw_irq_hw_counter0_overflow	_irq, 11, hw_counter0, oie,   ov
#define _hw_irq_hw_acmp0		_irq, 12, hw_acmp0,    ie,    if
#define _hw_irq_hw_adc0			_irq, 13, hw_adc0,     ie,    if
#define _hw_irq_hw_eeprom0		_irq, 14, hw_eeprom0,  sie, /* no irq flag */
#define _hw_irq_hw_eeprom0_ready	_irq, 14, hw_eeprom0,  sie,
#define _hw_irq_hw_usi0_start		_irq, 15, hw_usi0,     sie,   sif
#define _hw_irq_hw_usi0_overflow	_irq, 16, hw_usi0,     oie,   oif
#define _hw_irq_hw_usi0_txc		_irq, 16, hw_usi0,     oie,   oif


/*******************************************************************************
 *									       *
 *	Fuses								       *
 *									       *
 *******************************************************************************/
/**
 * @page atmelavr_attinyx4
 * @par Fuses
 *
 * Clocking
 *
 * Symbol                 | Valid values | Comments
 * -----------------------|--------------|:-----------
 * `HW_DEVICE_CLK_SRC`    | `external`<br>`rc_8MHz`<br>`rc_128kHz`<br>`xosc` | Source clock
 * `HW_DEVICE_CLK_SRC_HZ` | Integer     | Crystal frequency for `xosc` clock source
 * `HW_DEVICE_CLK_PSC`    | `8`<br>`1`  | Clock prescaler
*/
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_rc_128kHz_rc_128kHz			, 1
#define _hw_is_xosc_xosc				, 1

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


/**
 * @page atmelavr_attinyx4
 *
 * Startup delays
 *
 * Symbol               | Valid values | Comments
 * ---------------------|--------------|:-----------
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
 * @page atmelavr_attinyx4
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


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/


/*	Instance			class, id, address
 */
#define _hw_core0			_corea, 101, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw__corea_sreg			_crg, 8, 0x5F, 0xFF, 0x00
#define _hw__corea_sph			_crg, 8, 0x5E, 0x03, 0x00
#define _hw__corea_spl			_crg, 8, 0x5D, 0xFF, 0x00
#define _hw__corea_gimsk		_crg, 8, 0x5B, 0x70, 0x00
#define _hw__corea_gifr			_crg, 8, 0x5A, 0x70, 0x70
#define _hw__corea_mcucr		_crg, 8, 0x55, 0xFF, 0x00
#define _hw__corea_mcusr		_crg, 8, 0x54, 0x0F, 0x00
#define _hw__corea_osccal		_crg, 8, 0x51, 0xFF, 0x00
#define _hw__corea_gpior2		_crg, 8, 0x35, 0xFF, 0x00
#define _hw__corea_gpior1		_crg, 8, 0x34, 0xFF, 0x00
#define _hw__corea_gpior0		_crg, 8, 0x33, 0xFF, 0x00
#define _hw__corea_prr			_crg, 8, 0x20, 0x0F, 0x00


/*******************************************************************************
 *									       *
 *	Ports & pins							       *
 *									       *
 *******************************************************************************/

/*	Instances			class, id, address
 */
#define _hw_porta			_io8a, 300, 0x39
#define _hw_portb			_io8a, 310, 0x36


/**
 * @page atmelavr_attinyx4
 * @par Ports and pins
 *
 * Atmel name | HWA name   | 14pdid #  | Class
 * -----------|:-----------|:----------|:----------
 * Port A     | hw_port_a  |           | @ref atmelavr_io8a
 * PA0	      | hw_pin_pa0 | hw_pin_13 | @ref atmelavr_pin1
 * PA1	      | hw_pin_pa1 | hw_pin_12 | @ref atmelavr_pin1
 * PA2	      | hw_pin_pa2 | hw_pin_11 | @ref atmelavr_pin1
 * PA3	      | hw_pin_pa3 | hw_pin_10 | @ref atmelavr_pin1
 * PA4	      | hw_pin_pa4 | hw_pin_9  | @ref atmelavr_pin1
 * PA5	      | hw_pin_pa5 | hw_pin_8  | @ref atmelavr_pin1
 * PA6	      | hw_pin_pa6 | hw_pin_7  | @ref atmelavr_pin1
 * PA7	      | hw_pin_pa7 | hw_pin_6  | @ref atmelavr_pin1
 * Port B     | hw_port_b  |           | @ref atmelavr_io8a
 * PB0	      | hw_pin_pb0 | hw_pin_2  | @ref atmelavr_pin1
 * PB1	      | hw_pin_pb1 | hw_pin_3  | @ref atmelavr_pin1
 * PB2	      | hw_pin_pb2 | hw_pin_5  | @ref atmelavr_pin1
 * PB3	      | hw_pin_pb3 | hw_pin_4  | @ref atmelavr_pin1
 * 
 * Pin numbers `hw_pin_2` to `hw_pin_13` can be used if `HW_DEVICE_PACKAGE` is
 * defined as '14pdip'.
 * 
 */

/*  Pins				class, id, controller, bn, bp
 */
#define _hw_pin_pa0			_pin1, 301, hw_porta, 1, 0
#define _hw_pin_pa1			_pin1, 302, hw_porta, 1, 1
#define _hw_pin_pa2			_pin1, 303, hw_porta, 1, 2
#define _hw_pin_pa3			_pin1, 304, hw_porta, 1, 3
#define _hw_pin_pa4			_pin1, 305, hw_porta, 1, 4
#define _hw_pin_pa5			_pin1, 306, hw_porta, 1, 5
#define _hw_pin_pa6			_pin1, 307, hw_porta, 1, 6
#define _hw_pin_pa7			_pin1, 308, hw_porta, 1, 7

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb0			_pin1, 311, hw_portb, 1, 0
#endif
#define _hw_pin_pb1			_pin1, 312, hw_portb, 1, 1
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define _hw_pin_pb2			_pin1, 313, hw_portb, 1, 2
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET) && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define _hw_pin_pb3			_pin1, 314, hw_portb, 1, 3
#endif

/*  Analog input pins (with Digital Input Disable bits, stored in register `did`
 *  in hw_adc0)
 */
#define _hw_pin_pa0_did			, hw_adc0, did_0
#define _hw_pin_pa1_did			, hw_adc0, did_1
#define _hw_pin_pa2_did			, hw_adc0, did_2
#define _hw_pin_pa3_did			, hw_adc0, did_3
#define _hw_pin_pa4_did			, hw_adc0, did_4
#define _hw_pin_pa5_did			, hw_adc0, did_5
#define _hw_pin_pa6_did			, hw_adc0, did_6
#define _hw_pin_pa7_did			, hw_adc0, did_7

/*  Analog input pin names
 */
#define hw_pin_adc0			hw_pin_pa0
#define hw_pin_adc1			hw_pin_pa1
#define hw_pin_adc2			hw_pin_pa2
#define hw_pin_adc3			hw_pin_pa3
#define hw_pin_adc4			hw_pin_pa4
#define hw_pin_adc5			hw_pin_pa5
#define hw_pin_adc6			hw_pin_pa6
#define hw_pin_adc7			hw_pin_pa7

#define hw_pin_ain0			hw_pin_pa1
#define hw_pin_ain1			hw_pin_pa2


/*	Pins by numbers
 */
#define _hw_is_14pdip_14pdip		, 1

#if HW_IS(14pdip,HW_DEVICE_PACKAGE)
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
#elif !HW_IS(,HW_DEVICE_PACKAGE)
#  error Package can be `14pdip` but not `HW_DEVICE_PACKAGE`
#endif


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_pcic0			_pcica, 350, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__pcica_msk1			_crg, 8, 0x40, 0x0F, 0x00
#define _hw__pcica_msk0			_crg, 8, 0x32, 0xFF, 0x00

#define _hw__pcica_irqe0		_ext, hw_core0, pcie0
#define _hw__pcica_irqf0		_ext, hw_core0, pcif0

#define _hw__pcica_irqe1		_ext, hw_core0, pcie1
#define _hw__pcica_irqf1		_ext, hw_core0, pcif1

#define _hw__pcica_hw_pin_pa0		_cb1, msk0, 1, 0
#define _hw__pcica_hw_pin_pa1		_cb1, msk0, 1, 1
#define _hw__pcica_hw_pin_pa2		_cb1, msk0, 1, 2
#define _hw__pcica_hw_pin_pa3		_cb1, msk0, 1, 3
#define _hw__pcica_hw_pin_pa4		_cb1, msk0, 1, 4
#define _hw__pcica_hw_pin_pa5		_cb1, msk0, 1, 5
#define _hw__pcica_hw_pin_pa6		_cb1, msk0, 1, 6
#define _hw__pcica_hw_pin_pa7		_cb1, msk0, 1, 7

#define _hw__pcica_hw_pin_pb0		_cb1, msk1, 1, 0
#define _hw__pcica_hw_pin_pb1		_cb1, msk1, 1, 1
#define _hw__pcica_hw_pin_pb2		_cb1, msk1, 1, 2
#define _hw__pcica_hw_pin_pb3		_cb1, msk1, 1, 3


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_wdog0			_wdoga, 901, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__wdoga_csr			_crg, 8, 0x41, 0xFF, 0x80

#define _hw__wdoga_wdif			_cb1, csr, 1, 7
#define _hw__wdoga_wdie			_cb1, csr, 1, 6
#define _hw__wdoga_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw__wdoga_wdce			_cb1, csr, 1, 4
#define _hw__wdoga_wde			_cb1, csr, 1, 3

#define _hw__wdoga_wdeie		_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw__wdoga_wdifie		_cb1, csr, 2, 6 /* convenient for clearing irq */
#define _hw__wdoga_wdall		_cb1, csr, 7, 0 /* convenient for turning wd off */

#define _hw__wdoga_wdrf			_ext, hw_core0, wdrf /* convenient */


/*******************************************************************************
 *									       *
 *	Counter 0							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_counter0			_c8a, 400, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
//#define _hw__c8a_ocrb			_crg, 8, 0x5C, 0xFF, 0x00
#define _hw__c8a_compare1		_crg, 8, 0x5C, 0xFF, 0x00	/* OCRB */
#define _hw__c8a_imsk			_crg, 8, 0x59, 0x07, 0x00
#define _hw__c8a_ifr			_crg, 8, 0x58, 0x07, 0x07
//#define _hw__c8a_ocra			_crg, 8, 0x56, 0xFF, 0x00
#define _hw__c8a_compare0		_crg, 8, 0x56, 0xFF, 0x00	/* OCRA */
#define _hw__c8a_ccrb			_crg, 8, 0x53, 0xCF, 0x00
#define _hw__c8a_count			_crg, 8, 0x52, 0xFF, 0x00
#define _hw__c8a_ccra			_crg, 8, 0x50, 0xF3, 0x00

//#define _hw__c8a_coma			_cb1, ccra, 2, 6
//#define _hw__c8a_com0			_cb1, ccra, 2, 6 /* convenient */
#define _hw__c8a_compare0_mode		_cb1, ccra, 2, 6 /* COMA */
//#define _hw__c8a_comb			_cb1, ccra, 2, 4
//#define _hw__c8a_com1			_cb1, ccra, 2, 4 /* convenient */
#define _hw__c8a_compare1_mode		_cb1, ccra, 2, 6 /* COMB */
#define _hw__c8a_wgm			_cb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define _hw__c8a_foca			_cb1, ccrb, 1, 7
#define _hw__c8a_focb			_cb1, ccrb, 1, 6
#define _hw__c8a_cs			_cb1, ccrb, 3, 0

#define _hw__c8a_ocieb			_cb1, imsk, 1, 2
#define _hw__c8a_ociea			_cb1, imsk, 1, 1
#define _hw__c8a_oie			_cb1, imsk, 1, 0

#define _hw__c8a_ocfb			_cb1, ifr, 1, 2
#define _hw__c8a_ocfa			_cb1, ifr, 1, 1
#define _hw__c8a_ov			_cb1, ifr, 1, 0


/*	Counter0 compare output units
 *
 *	Instance			class, id, counter, ocn, ion
 */
#define _hw_counter0_compare0		_ocua, 401, hw_counter0, compare0, pin_pb2
#define _hw_counter0_compare1		_ocua, 402, hw_counter0, compare1, pin_pa7


/*******************************************************************************
 *									       *
 *	Counter 1							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_counter1			_c16a, 410, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__c16a_ccra			_crg,  8, 0x4F,   0xF3,   0x00
#define _hw__c16a_ccrb			_crg,  8, 0x4E,   0xDF,   0x00
#define _hw__c16a_ccrc			_crg,  8, 0x42,   0xC0,   0x00
#define _hw__c16a_count			_crg, 16, 0x4C, 0xFFFF, 0x0000
/* #define _hw__c16a_countl		_crg,  8, 0x4C,   0xFF,   0x00 */
/* #define _hw__c16a_counth		_crg,  8, 0x4D,   0xFF,   0x00 */
#define _hw__c16a_compare0		_crg, 16, 0x4A, 0xFFFF, 0x0000	/* OCRA */
/* #define _hw__c16a_ocral			_crg,  8, 0x4A,   0xFF,   0x00 */
/* #define _hw__c16a_ocrah			_crg,  8, 0x4B,   0xFF,   0x00 */
#define _hw__c16a_compare1		_crg, 16, 0x48, 0xFFFF, 0x0000	/* OCRB */
/* #define _hw__c16a_ocrbl			_crg,  8, 0x48,   0xFF,   0x00 */
/* #define _hw__c16a_ocrbh			_crg,  8, 0x49,   0xFF,   0x00 */
#define _hw__c16a_capture0		_crg, 16, 0x44, 0xFFFF, 0x0000	/* ICR */
/* #define _hw__c16a_icrl			_crg,  8, 0x44,   0xFF,   0x00 */
/* #define _hw__c16a_icrh			_crg,  8, 0x45,   0xFF,   0x00 */
#define _hw__c16a_imsk			_crg,  8, 0x2C,   0x27,   0x00
#define _hw__c16a_ifr			_crg,  8, 0x2B,   0x27,   0x27

#define _hw__c16a_acic			_ext, hw_acmp0, acic

/*	Counter1 compare output units	class, id, counter, channel, io
 */
#define _hw_counter1_compare0		_ocua, 411, hw_counter1, compare0, pin_pa6 /* dil#7 */
#define _hw_counter1_compare1		_ocua, 412, hw_counter1, compare1, pin_pa5 /* dil#8 */

/*	Counter1 input capture unit	class, id, counter, reg, io
 */
#define _hw_counter1_capture0		_icua, 413, hw_counter1, capture0, pin_pa7 /* dil#6 */


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

#define _hw_pin_usck			_pin1, 305, hw_porta, 1, 4	/* hw_pin_pa4 */
#define _hw_pin_do			_pin1, 306, hw_porta, 1, 5	/* hw_pin_pa5 */
#define _hw_pin_di			_pin1, 307, hw_porta, 1, 6	/* hw_pin_pa6 */

/*	Instance			class, id, address
 */				        
#define _hw_usi0			_usia, 600, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define _hw__usia_cr			_crg, 8, 0x2D, 0xFF, 0x00
#define _hw__usia_sr			_crg, 8, 0x2E, 0xFF, 0xE0
#define _hw__usia_dr			_crg, 8, 0x2F, 0xFF, 0x00
#define _hw__usia_br			_crg, 8, 0x30, 0xFF, 0x00

#define _hw__usia_sie			_cb1, cr, 1, 7
#define _hw__usia_oie			_cb1, cr, 1, 6
#define _hw__usia_wm			_cb1, cr, 2, 4
#define _hw__usia_cs			_cb1, cr, 2, 2
#define _hw__usia_clk			_cb1, cr, 1, 1
#define _hw__usia_tc			_cb1, cr, 1, 0

#define _hw__usia_sif			_cb1, sr, 1, 7
#define _hw__usia_oif			_cb1, sr, 1, 6
#define _hw__usia_pf			_cb1, sr, 1, 5
#define _hw__usia_dc			_cb1, sr, 1, 4
#define _hw__usia_cnt			_cb1, sr, 4, 0


/*	USI used as SPI master with software clock
 */
#define _hw_spimaster0_swclk		_usia_spimaster_swclk, 602, hw_usi0

/*	USI used as SPI master with counter0 overflow clock
 */
#define _hw_spimaster0_c0clk		_usia_spimaster_c0clk, 603, hw_usi0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */				        
#define _hw_acmp0			_acmpa, 700, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define _hw__acmpa_csr			_crg, 8, 0x28, 0xDF, 0x10

#define _hw__acmpa_if			_cb1, csr, 1, 4
#define _hw__acmpa_ie			_cb1, csr, 1, 3

#define _hw_acmp0_acme			_ext, hw_adc0, me
#define _hw_acmp0_aden			_ext, hw_adc0, en
#define _hw_acmp0_admux			_ext, hw_adc0, mux


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#define _hw_adc0			_ad10a, 800, 0

#define _hw__ad10a_admux		_crg,  8, 0x27,   0xFF,   0x00
#define _hw__ad10a_sra			_crg,  8, 0x26,   0xFF,   0x10
#define _hw__ad10a_adc			_crg, 16, 0x24, 0x0000, 0x0000
#define _hw__ad10a_adch			_crg,  8, 0x25,   0x00,   0x00
#define _hw__ad10a_adcl			_crg,  8, 0x24,   0x00,   0x00
#define _hw__ad10a_srb			_crg,  8, 0x23,   0xD7,   0x00
#define _hw__ad10a_did			_crg,  8, 0x21,   0xFF,   0x00 /* port A */

#define _hw__ad10a_refs			_cb1, admux, 2, 6
#define _hw__ad10a_mux			_cb1, admux, 6, 0

#define _hw__ad10a_en			_cb1, sra, 1, 7
#define _hw__ad10a_sc			_cb1, sra, 1, 6
#define _hw__ad10a_ate			_cb1, sra, 1, 5
#define _hw__ad10a_if			_cb1, sra, 1, 4
#define _hw__ad10a_ie			_cb1, sra, 1, 3
#define _hw__ad10a_ps			_cb1, sra, 3, 0

#define _hw__ad10a_bin			_cb1, srb, 1, 7
#define _hw__ad10a_me			_cb1, srb, 1, 6
#define _hw__ad10a_lar			_cb1, srb, 1, 4
#define _hw__ad10a_ts			_cb1, srb, 3, 0

#define _hw__ad10a_did_0		_cb1, did, 1, 0
#define _hw__ad10a_did_1		_cb1, did, 1, 1
#define _hw__ad10a_did_2		_cb1, did, 1, 2
#define _hw__ad10a_did_3		_cb1, did, 1, 3
#define _hw__ad10a_did_4		_cb1, did, 1, 4
#define _hw__ad10a_did_5		_cb1, did, 1, 5
#define _hw__ad10a_did_6		_cb1, did, 1, 6
#define _hw__ad10a_did_7		_cb1, did, 1, 7


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__eeproma

/*	Instance	        	class, id, address
 */
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw__eeproma_arh		_crg,  8, 0x3F,   0x01, 0x00
#define _hw__eeproma_arl		_crg,  8, 0x3E,   0xFF, 0x00
#define _hw__eeproma_ar			_crg, 16, 0x3E, 0x01FF, 0x00
#define _hw__eeproma_dr			_crg,  8, 0x3D,   0xFF, 0x00
#define _hw__eeproma_cr			_crg,  8, 0x3C,   0x3F, 0x00

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

/*	Instance	                class, id, address
 */
#define _hw_flash0			_flasha, 1100, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw__flasha_csr			_crg,  8, 0x57, 0x3F, 0x00

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

#if defined HW_SWUART0_PIN_RX || defined HW_SWUART0_PIN_TX
#define _hw_class__swuarta

/*	Instance	                class, id, address
 */
#define _hw_swuart0			_swuarta, 1200, 0
#define _hw_swuart1			_swuarta, 1210, 0


/* #if hw_bn(HW_SWUART0_COUNTER) == 8 */
/* #  define _hw_swuart0_dtn		_crg,  8, (intptr_t)&__hw_swuart0_dtn, 0xFF, 0x00 */
/* #  define _hw_swuart0_dt0		_crg,  8, (intptr_t)&__hw_swuart0_dt0, 0xFF, 0x00 */
/* #  define _hw_swuart1_dtn		_crg,  8, (intptr_t)&__hw_swuart1_dtn, 0xFF, 0x00 */
/* #  define _hw_swuart1_dt0		_crg,  8, (intptr_t)&__hw_swuart1_dt0, 0xFF, 0x00 */
/* #endif */
/* #if hw_bn(HW_SWUART0_COUNTER) == 16 */
/* #  define _hw_swuart0_dtn		_crg, 16, (intptr_t)&__hw_swuart0_dtn, 0xFFFF, 0x0000 */
/* #  define _hw_swuart0_dt0		_crg, 16, (intptr_t)&__hw_swuart0_dt0, 0xFFFF, 0x0000 */
/* #  define _hw_swuart1_dtn		_crg, 16, (intptr_t)&__hw_swuart1_dtn, 0xFFFF, 0x0000 */
/* #  define _hw_swuart1_dt0		_crg, 16, (intptr_t)&__hw_swuart1_dt0, 0xFFFF, 0x0000 */
/* #endif */

#define _hw_swuart0_dtn _crg, hw_bn(HW_SWUART0_COUNTER), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_swuart0_dt0	_crg, hw_bn(HW_SWUART0_COUNTER), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_swuart0__st			_hw_ra(hw_core0, gpior0)

#define _hw_swuart0_sr			_crg, 8, _hw_ra(hw_core0, gpior0), 0xFF, 0x00
#define _hw_swuart0_synced		_ob1, sr, 1, 0


#define _hw_swuart1_dtn	_crg, hw_bn(HW_SWUART1_COUNTER), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_swuart1_dt0	_crg, hw_bn(HW_SWUART1_COUNTER), (intptr_t)&__hw_swuart1_dt0, -1, 0x00

#define _hw_swuart1__st			_hw_ra(hw_core0, gpior1)

#define _hw_swuart1_sr			_crg, 8, _hw_ra(hw_core0, gpior1), 0xFF, 0x00
#define _hw_swuart1_synced		_ob1, sr, 1, 0


/*	Class regs			class, rw, ra, rwm, rfm
 */
#if 1
#if hw_bn(HW_SWUART0_COUNTER) == 8
//#define _hw__swuarta_dtn		_crg,  8, (intptr_t)&_hw_swuart0_dtn,   0xFF, 0x00
//#define _hw__swuarta_dt0		_crg,  8, (intptr_t)&_hw_swuart0_dt0,   0xFF, 0x00
#endif
#if hw_bn(HW_SWUART0_COUNTER) == 16
//#define _hw__swuarta_dtn		_crg, 16, (intptr_t)&_hw_swuart0_dtn,   0xFFFF, 0x0000
//#define _hw__swuarta_dt0		_crg, 16, (intptr_t)&_hw_swuart0_dt0,   0xFFFF, 0x0000
#endif

/* #define _hw__swuarta_st			_crg,  8, swuart_st,      0xFF,   0x00 */

/* #ifndef swuart_st */
/* #  define swuart_st			_hw_ra(hw_core0, gpior0) */
/* #endif */

#else

#define _hw__swuarta_dtn		_ird
#define _hw__swuarta_dt0		_ird
#define _hw__swuarta_match		_ird
#define _hw__swuarta_shift		_ird
#define _hw__swuarta_nbit		_ird
#define _hw__swuarta_data		_ird
#define _hw__swuarta_st			_ird

#define _hw__swuarta_st_stop		_cb1, st, 1, 0
#define _hw__swuarta_st_idle		_cb1, st, 1, 1
#define _hw__swuarta_st_rxc		_cb1, st, 1, 2
#define _hw__swuarta_st_txc		_cb1, st, 1, 3
#define _hw__swuarta_st_rxtx		_cb1, st, 1, 4
#define _hw__swuarta_st_wbtx		_cb1, st, 1, 5
#define _hw__swuarta_st_synced		_cb1, st, 1, 6

#if !defined __ASSEMBLER__
#  define HW_IPTR(x)	(intptr_t)&x
#else
#  define HW_IPTR(x)	x
#endif

#define _hw_swuart0_dtn			_crg, 16, HW_IPTR(swuart_dtn),   0xFFFF, 0x0000
#define _hw_swuart0_dt0			_crg, 16, HW_IPTR(swuart_dt0),   0xFFFF, 0x0000
#define _hw_swuart0_match		_crg, 16, HW_IPTR(swuart_match), 0xFFFF, 0x0000
#define _hw_swuart0_shift		_crg,  8, HW_IPTR(swuart_shift),   0xFF,   0x00
#define _hw_swuart0_nbit		_crg,  8, HW_IPTR(swuart_nbit),    0xFF,   0x00
#define _hw_swuart0_data		_crg,  8, HW_IPTR(swuart_data),    0xFF,   0x00
#define _hw_swuart0_st			_crg,  8, HW_IPTR(swuart_st),      0xFF,   0x00
//#define _hw_swuart0_st			_crg,  8, __hw_swuart0_st,             0xFF,   0x00
//#define _hw_swuart0_st			_xia, hw_core0, gpior0

#define _hw_swuart0_dtn			_crg, 16, HW_IPTR(swuart_dtn),   0xFFFF, 0x0000
#define _hw_swuart0_dt0			_crg, 16, HW_IPTR(swuart_dt0),   0xFFFF, 0x0000
#define _hw_swuart0_match		_crg, 16, HW_IPTR(swuart_match), 0xFFFF, 0x0000
#define _hw_swuart0_shift		_crg,  8, HW_IPTR(swuart_shift),   0xFF,   0x00
#define _hw_swuart0_nbit		_crg,  8, HW_IPTR(swuart_nbit),    0xFF,   0x00
#define _hw_swuart0_data		_crg,  8, HW_IPTR(swuart_data),    0xFF,   0x00
#define _hw_swuart0_st			_crg,  8, HW_IPTR(swuart_st),      0xFF,   0x00


/* #ifndef __hw_swuart0_st */
/* #  define __hw_swuart0_st		_hw_ra(hw_core0, gpior0) */
/* #endif */
#endif
#endif


/**
 * @page atmelavr_attinyx4
 *
 * @par Power Management
 *
 * The following controllers can be turned on/off with the `hw/hwa_turn(...)`
 * instruction to manage power consumption of the device:
 *
 * * `hw_counter0`
 * * `hw_counter1`
 * * `hw_usi0`
 * * `hw_adc0`
 *
 * @code
 * hw/hwa_turn( OBJECT, on | off );
 * @endcode
 */

/**
 * @page atmelavr_attinyx4
 * <br>
 */
