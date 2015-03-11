
/*	Atmel ATtiny24 ATtiny44 ATtiny84
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_1.h"

#define HWA_DCL					\
  hwa_corea_t	core0 ;				\
  hwa_io8a_t	porta ;				\
  hwa_io8a_t	portb ;				\
  hwa_wdoga_t	watchdog0 ;			\
  hwa_c8a_t	counter0 ;			\
  hwa_c16a_t	counter1 ;			\
  hwa_acmpa_t	acmp0 ;


/*******************************************************************************
 *									       *
 *	DEVICE definition						       *
 *									       *
 *******************************************************************************/

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


/*******************************************************************************
 *									       *
 *	Core definition							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__corea_1.h"


/*	Instance	    	    class, id, address
 */
#define hw_core0			_corea, 101, 0
//#define hw_hw_core0		_corea, 101, 0


/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw__corea_sreg			_crg, 8, 0x5F, 0xFF, 0x00
#define hw__corea_sph			_crg, 8, 0x5E, 0x03, 0x00
#define hw__corea_spl			_crg, 8, 0x5D, 0xFF, 0x00
#define hw__corea_gimsk			_crg, 8, 0x5B, 0x70, 0x00
#define hw__corea_gifr			_crg, 8, 0x5A, 0x70, 0x70
#define hw__corea_mcucr			_crg, 8, 0x55, 0xFF, 0x00
#define hw__corea_mcusr			_crg, 8, 0x54, 0x0F, 0x00
#define hw__corea_osccal		_crg, 8, 0x51, 0xFF, 0x00
#define hw__corea_gpior2		_crg, 8, 0x35, 0xFF, 0x00
#define hw__corea_gpior1		_crg, 8, 0x34, 0xFF, 0x00
#define hw__corea_gpior0		_crg, 8, 0x33, 0xFF, 0x00
#define hw__corea_prr			_crg, 8, 0x20, 0x0F, 0x00


/*	INT0 class
 */
#define hw_class_int0

/*	INT0 instance	        	class, name, id, address
 */
#define hw_pin_int0			int0, pin_int0, 102, core0, pin_pb2


/*******************************************************************************
 *									       *
 *	i/o definitions							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__io_1.h"

#define HWA_DCL_IOS			hwa_io8a_t porta, portb


/*	Instances			class, id, address
 */
#define hw_porta			_io8a, 300, 0x39
#define hw_portb			_io8a, 310, 0x36


/*  Pins				class, id, controller, bn, bp
 */
#define hw_pin_pa0			_dio, 301, porta, 1, 0
#define hw_pin_pa1			_dio, 302, porta, 1, 1
#define hw_pin_pa2			_dio, 303, porta, 1, 2
#define hw_pin_pa3			_dio, 304, porta, 1, 3
#define hw_pin_pa4			_dio, 305, porta, 1, 4
#define hw_pin_pa5			_dio, 306, porta, 1, 5
#define hw_pin_pa6			_dio, 307, porta, 1, 6
#define hw_pin_pa7			_dio, 308, porta, 1, 7

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb0			_dio, 11, portb, 1, 0
#endif
#define hw_pin_pb1			_dio, 12, portb, 1, 1
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#  define hw_pin_pb2			_dio, 13, portb, 1, 2
#endif
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET) && !HW_IS(enabled,HW_DEVICE_DEBUG_WIRE)
#  define hw_pin_pb3			_dio, 14, portb, 1, 3
#endif


/*	Pins by numbers
 */
#define hw_is_14pdip_14pdip		, 1

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
#  error Package type not recognized
#endif


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__wdoga_1.h"


/*	Instance			class, id, address
 */
#define hw_watchdog0			_wdoga, 901, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__wdoga_csr			_crg, 8, 0x41, 0xFF, 0x80

#define hw__wdoga_wdif			_cb1, csr, 1, 7
#define hw__wdoga_wdie			_cb1, csr, 1, 6
#define hw__wdoga_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw__wdoga_wdce			_cb1, csr, 1, 4
#define hw__wdoga_wde			_cb1, csr, 1, 3

#define hw__wdoga_wdeie			_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define hw__wdoga_wdifie		_cb1, csr, 2, 6 /* convenient for clearing irq */
#define hw__wdoga_wdall			_cb1, csr, 7, 0 /* convenient for turning wd off */

#define hw__wdoga_wdrf			_irg, core0, wdrf /* convenient */


/*******************************************************************************
 *									       *
 *	Timer Counter 0							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__c8a_1.h"

/*	Instance			class, id, address
 */
#define hw_counter0			_c8a, 400, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__c8a_ocrb			_crg, 8, 0x5C, 0xFF, 0x00
#define hw__c8a_compare1		_crg, 8, 0x5C, 0xFF, 0x00
#define hw__c8a_imsk			_crg, 8, 0x59, 0x07, 0x00
#define hw__c8a_ifr			_crg, 8, 0x58, 0x07, 0x07
#define hw__c8a_ocra			_crg, 8, 0x56, 0xFF, 0x00
#define hw__c8a_compare0		_crg, 8, 0x56, 0xFF, 0x00
#define hw__c8a_ccrb			_crg, 8, 0x53, 0xCF, 0x00
#define hw__c8a_count			_crg, 8, 0x52, 0xFF, 0x00
#define hw__c8a_ccra			_crg, 8, 0x50, 0xF3, 0x00


/*	Counter0 compare output units
 *
 *	Instance			class, id, counter, ocn, ion
 */
#define hw_counter0_compare0		_ocua, 401, counter0, 0, pin_pb2
#define hw_counter0_compare1		_ocua, 402, counter0, 1, pin_pa7


/*******************************************************************************
 *									       *
 *	Timer Counter 1							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__c16a_1.h"
#include "hwa_atmelavr__icua_1.h"

/*	Instance			class, id, address
 */
#define hw_counter1			_c16a, 410, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__c16a_ccra			_crg,  8, 0x4F, 0xF3,   0x00
#define hw__c16a_ccrb			_crg,  8, 0x4E, 0xDF,   0x00
#define hw__c16a_ccrc			_crg,  8, 0x42, 0xC0,   0x00
#define hw__c16a_count			_crg, 16, 0x4C, 0xFFFF, 0x0000
#define hw__c16a_countl			_crg,  8, 0x4C, 0xFF,   0x00
#define hw__c16a_counth			_crg,  8, 0x4D, 0xFF,   0x00
#define hw__c16a_ocra			_crg, 16, 0x4A, 0xFFFF, 0x0000
#define hw__c16a_compare0		_crg, 16, 0x4A, 0xFFFF, 0x0000
#define hw__c16a_ocral			_crg,  8, 0x4A, 0xFF,   0x00
#define hw__c16a_ocrah			_crg,  8, 0x4B, 0xFF,   0x00
#define hw__c16a_ocrb			_crg, 16, 0x48, 0xFFFF, 0x0000
#define hw__c16a_compare1		_crg, 16, 0x48, 0xFFFF, 0x0000
#define hw__c16a_ocrbl			_crg,  8, 0x48, 0xFF,   0x00
#define hw__c16a_ocrbh			_crg,  8, 0x49, 0xFF,   0x00
#define hw__c16a_icr			_crg, 16, 0x44, 0xFFFF, 0x0000
#define hw__c16a_capture0		_crg, 16, 0x44, 0xFFFF, 0x0000
#define hw__c16a_icrl			_crg,  8, 0x44, 0xFF,   0x00
#define hw__c16a_icrh			_crg,  8, 0x45, 0xFF,   0x00
#define hw__c16a_imsk			_crg,  8, 0x2C, 0x27,   0x00
#define hw__c16a_ifr			_crg,  8, 0x2B, 0x27,   0x27

#define hw__c16a_acic			_irg, acmp0, acic

/*	Counter1 compare output units	class, id, counter, channel, io
 */
#define hw_counter1_compare0		_ocua, 411, counter1, 0, pin_pa6 /* dil#7 */
#define hw_counter1_compare1		_ocua, 412, counter1, 1, pin_pa5 /* dil#8 */

/*	Counter1 input capture unit	class, id, counter, reg, io
 */
#define hw_counter1_capture0		_icua, 413, counter1, icr, pin_pa7 /* dil#6 */


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__acmpa_1.h"

/*	Instance			class, id, address
 */				        
#define hw_acmp0			_acmpa, 700, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define hw__acmpa_csr			_crg, 8, 0x28, 0xDF, 0x10


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

/*	Class & methods
 */
#define hw_class_eeprom
#define _hw_pop_eeprom(c,n,i,a,...)	__VA_ARGS__


/*	Instance	        	class, name, id, address
 */
#define hw_eeprom0			eeprom, 1000, 0


/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw_eeprom_arh			_crg,  8, 0x3F,   0x01, 0x00
#define hw_eeprom_arl			_crg,  8, 0x3E,   0xFF, 0x00
#define hw_eeprom_ar			_crg, 16, 0x3E, 0x01FF, 0x00
#define hw_eeprom_dr			_crg,  8, 0x3D,   0xFF, 0x00
#define hw_eeprom_cr			_crg,  8, 0x3C,   0x3F, 0x00

#define hw_eeprom_pm			_cb1, cr, 2, 4
#define hw_eeprom_rie			_cb1, cr, 1, 3
#define hw_eeprom_mpe			_cb1, cr, 1, 2
#define hw_eeprom_pe			_cb1, cr, 1, 1
#define hw_eeprom_re			_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

/*	Class & methods
 */
#define hw_class_flash
#define _hw_pop_flash(c,n,i,a,...)	__VA_ARGS__


/*	Instance	                class, name, id, address
 */
#define hw_flash0			flash, 1100, 0


/*	Class regs			class, rw, ra, rwm, rfm
 */
#define hw_flash_csr			_crg,  8, 0x57, 0x3F, 0x00

#define hw_flash_sigrd			_cb1, csr, 1, 5
#define hw_flash_rsig			_cb1, csr, 1, 5	/* old definition */
#define hw_flash_rwwsre			_cb1, csr, 1, 4
#define hw_flash_ctpb			_cb1, csr, 1, 4	/* old definition */
#define hw_flash_blbset			_cb1, csr, 1, 3
#define hw_flash_rflb			_cb1, csr, 1, 3	/* old definition */
#define hw_flash_pgwrt			_cb1, csr, 1, 2
#define hw_flash_pgers			_cb1, csr, 1, 1
#define hw_flash_spmen			_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

#define hw_irq_watchdog0		_irq,  4, watchdog0, wdie,  wdif
#define hw_irq_counter1_capture0	_irq,  5, counter1,  icie,  icf
#define hw_irq_counter1_compare0	_irq,  6, counter1,  ociea, ocfa
#define hw_irq_counter1_compare1	_irq,  7, counter1,  ocieb, ocfb
#define hw_irq_counter1_overflow	_irq,  8, counter1,  oie,   ov
#define hw_irq_counter0_compare0	_irq,  9, counter0,  ociea, ocfa
#define hw_irq_counter0_compare1	_irq, 10, counter0,  ocieb, ocfb
#define hw_irq_counter0_overflow	_irq, 11, counter0,  oie,   ov
