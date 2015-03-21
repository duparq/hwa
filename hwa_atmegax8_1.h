
/*	Atmel ATmega48 ATmega88 ATmega168 ATmega328
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_1.h"

#define HW_DEVICE_ATMEGAX8

#define HWA_DCL					\
  hwa_coreb_t	hw_core0 ;			\
  hwa_io8a_t	hw_portb ;			\
  hwa_io8a_t	hw_portc ;			\
  hwa_io8a_t	hw_portd ;			\
  hwa_wdogb_t	hw_watchdog0 ;			\
  hwa_c8a_t	hw_counter0 ;			\
  hwa_c16a_t	hw_counter1 ;			\
  hwa_acmpa_t	hw_acmp0 ;


/*******************************************************************************
 *									       *
 *	Fuses								       *
 *									       *
 *	HW_DEVICE_FUSE_... are defined in the the device-specific file	       *
 *	that includes this file						       *
 *									       *
 *******************************************************************************/

/*	Clocking
 */
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_rc_128kHz_rc_128kHz			, 1
#define _hw_is_low_power_xosc_low_power_xosc		, 1
#define _hw_is_full_swing_xosc_full_swing_xosc		, 1


#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				rc_8MHz
#endif
#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				0
#  define HW_DEVICE_CKSEL0				0
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				1
#  define hw_syshz_base					128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_power_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the \
  crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#    if HW_DEVICE_CLK_SRC_HZ < 400000 /* Assume values other than 32768 are acceptable */
#      define HW_DEVICE_CKSEL31				2
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
#elif HW_IS(HW_DEVICE_CLK_SRC, full_swing_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#    define HW_DEVICE_CKSEL31				3
#  endif
#else
#  error HW_DEVICE_CLK_SRC must be defined as one of `internal_rc`, `internal_watchdog`, `external_low_power_xo`, `external_full_swing_xo`, or `external`.
#endif

#define _hw_is_4CK_4CK					, 1
#define _hw_is_4CK_4ms_4CK_4ms				, 1
#define _hw_is_4CK_64ms_4CK_64ms				, 1
#define _hw_is_6CK_14CK_6CK_14CK				, 1
#define _hw_is_6CK_14CK_4ms_6CK_14CK_4ms			, 1
#define _hw_is_6CK_14CK_64ms_6CK_14CK_64ms		, 1
#define _hw_is_1KCK_4ms_1KCK_4ms				, 1
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

#define _hw_is_application_application			, 1
#define _hw_is_bootloader_bootloader			, 1

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


/*******************************************************************************
 *									       *
 *	Core definition							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__coreb_1.h"

/*	Instance	        	class, id, address
 */
#define _hw_core0			_coreb, 101, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw__coreb_osccal		_crg, 8, 0x66, 0xFF, 0x00
#define _hw__coreb_prr			_crg, 8, 0x64, 0xEF, 0x00
#define _hw__coreb_sreg			_crg, 8, 0x5F, 0xFF, 0x00
#define _hw__coreb_sph			_crg, 8, 0x5E, 0x03, 0x00
#define _hw__coreb_spl			_crg, 8, 0x5D, 0xFF, 0x00
#define _hw__coreb_mcucr		_crg, 8, 0x55, 0x73, 0x00
#define _hw__coreb_mcusr		_crg, 8, 0x54, 0x0F, 0x00
#define _hw__coreb_smcr			_crg, 8, 0x53, 0x0F, 0x00
#define _hw__coreb_gpior2		_crg, 8, 0x4B, 0xFF, 0x00
#define _hw__coreb_gpior1		_crg, 8, 0x4A, 0xFF, 0x00
#define _hw__coreb_gpior0		_crg, 8, 0x3E, 0xFF, 0x00
#define _hw__coreb_eimsk		_crg, 8, 0x3D, 0x03, 0x00
#define _hw__coreb_eifr			_crg, 8, 0x3C, 0x03, 0x03

#define _hw__coreb_bods			_cb1, mcucr, 1, 6
#define _hw__coreb_bodse		_cb1, mcucr, 1, 5
#define _hw__coreb_pud			_cb1, mcucr, 1, 4
#define _hw__coreb_ivsel		_cb1, mcucr, 1, 1
#define _hw__coreb_ivce			_cb1, mcucr, 1, 0

#define _hw__coreb_wdrf			_cb1, mcusr, 1, 3
#define _hw__coreb_borf			_cb1, mcusr, 1, 2
#define _hw__coreb_extrf		_cb1, mcusr, 1, 1
#define _hw__coreb_porf			_cb1, mcusr, 1, 0
#define _hw__coreb_allrf		_cb1, mcusr, 4, 0	/* convenient */

#define _hw__coreb_sm			_cb1, smcr, 3, 1
#define _hw__coreb_se			_cb1, smcr, 1, 0

#define _hw__coreb_int1			_cb1, eimsk, 1, 1
#define _hw__coreb_int0			_cb1, eimsk, 1, 0

#define _hw__coreb_intf1		_cb1, eifr, 1, 1
#define _hw__coreb_intf0		_cb1, eifr, 1, 0

#define _hw__coreb_prtwi		_cb1, prr, 1, 7
#define _hw__coreb_prtim2		_cb1, prr, 1, 6
#define _hw__coreb_prtim0		_cb1, prr, 1, 5
#define _hw__coreb_prtim1		_cb1, prr, 1, 3
#define _hw__coreb_prspi		_cb1, prr, 1, 2
#define _hw__coreb_prusart		_cb1, prr, 1, 1
#define _hw__coreb_pradc		_cb1, prr, 1, 0


/*******************************************************************************
 *									       *
 *	i/o definitions							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__io_1.h"

/*	Instances			class, id, address
 */
#define _hw_portb			_io8a, 300, 0x23
#define _hw_portc			_io8a, 310, 0x26
#define _hw_portd			_io8a, 320, 0x29

/*	Pins				class, name, id, controller, bn, bp
 *
 *	FIXME: remove definition of pins used for alternate functions (XTAL, etc.)
 */
//#define _hw_port_b			_io_b,  309, hw_portb, 8, 0
#define _hw_pin_pb0			_dio, 301, hw_portb, 1, 0
#define _hw_pin_pb1			_dio, 302, hw_portb, 1, 1
#define _hw_pin_pb2			_dio, 303, hw_portb, 1, 2
#define _hw_pin_pb3			_dio, 304, hw_portb, 1, 3
#define _hw_pin_pb4			_dio, 305, hw_portb, 1, 4
#define _hw_pin_pb5			_dio, 306, hw_portb, 1, 5
#define _hw_pin_pb6			_dio, 307, hw_portb, 1, 6
#define _hw_pin_pb7			_dio, 308, hw_portb, 1, 7

//#define _hw_port_c			_dio, port_c,  319, hw_portc, 8, 0
#define _hw_pin_pc0			_dio, 311, hw_portc, 1, 0
#define _hw_pin_pc1			_dio, 312, hw_portc, 1, 1
#define _hw_pin_pc2			_dio, 313, hw_portc, 1, 2
#define _hw_pin_pc3			_dio, 314, hw_portc, 1, 3
#define _hw_pin_pc4			_dio, 315, hw_portc, 1, 4
#define _hw_pin_pc5			_dio, 316, hw_portc, 1, 5
#define _hw_pin_pc6			_dio, 317, hw_portc, 1, 6

//#define _hw_port_d			_dio, port_d,  329, hw_portd, 8, 0
#define _hw_pin_pd0			_dio, 321, hw_portd, 1, 0
#define _hw_pin_pd1			_dio, 322, hw_portd, 1, 1
#define _hw_pin_pd2			_dio, 323, hw_portd, 1, 2
#define _hw_pin_pd3			_dio, 324, hw_portd, 1, 3
#define _hw_pin_pd4			_dio, 325, hw_portd, 1, 4
#define _hw_pin_pd5			_dio, 326, hw_portd, 1, 5
#define _hw_pin_pd6			_dio, 327, hw_portd, 1, 6
#define _hw_pin_pd7			_dio, 328, hw_portd, 1, 7

#define _hw_pin_rxd			hw_pin_pd0
#define _hw_pin_txd			hw_pin_pd1

/*	Pins by numbers
 */
#define _hw_is_dil_dil			, 1
#define _hw_is_28pdip_28pdip		, 1
#define _hw_is_28mlf_28mlf		, 1
#define _hw_is_32mlf_32mlf		, 1


#if HW_IS(dil,HW_DEVICE_PACKAGE) || HW_IS(28pdip,HW_DEVICE_PACKAGE)
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
#elif HW_IS(28mlf,HW_DEVICE_PACKAGE)
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
#  define hw_pin_3			hw_pin_
#  define hw_pin_4			hw_pin_
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
#  define hw_pin_16			hw_pin_
#  define hw_pin_17			hw_pin_
#  define hw_pin_18			hw_pin_
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
#elif HW_IS(32mlf,HW_DEVICE_PACKAGE)
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
#elif !HW_IS(,HW_DEVICE_PACKAGE)
#  error Package type must be one of `dil`, `28pdip`, `28mlf`, or `32mlf`
#endif


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__wdogb_1.h"

/*	Instance			class, id, address
 */
#define _hw_watchdog0			_wdogb, 109, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__wdogb_csr			_crg, 8, 0x60, 0xFF, 0x80

#define _hw__wdogb_wdif			_cb1, csr, 1, 7
#define _hw__wdogb_wdie			_cb1, csr, 1, 6
#define _hw__wdogb_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw__wdogb_wdce			_cb1, csr, 1, 4
#define _hw__wdogb_wde			_cb1, csr, 1, 3

#define _hw__wdogb_wdeie		_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw__wdogb_wdifie		_cb1, csr, 2, 6 /* convenient for clearing irq */
#define _hw__wdogb_wdall		_cb1, csr, 7, 0 /* convenient for turning wd off */

#define _hw__wdogb_wdrf			_irg, hw_core0, wdrf /* convenient */


/*******************************************************************************
 *									       *
 *	Timer Counter 0							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__c8a_1.h"
//#include "hwa_atmelavr__ocua_1.h"


/*	Instance			class, id, address
 */
#define _hw_counter0			_c8a, 400, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__c8a_ccra			_crg, 8, 0x44, 0xF3, 0x00
#define _hw__c8a_ccrb			_crg, 8, 0x45, 0xCF, 0x00
#define _hw__c8a_count			_crg, 8, 0x46, 0xFF, 0x00
#define _hw__c8a_ocra			_crg, 8, 0x47, 0xFF, 0x00
#define _hw__c8a_compare0		_crg, 8, 0x47, 0xFF, 0x00
#define _hw__c8a_ocrb			_crg, 8, 0x48, 0xFF, 0x00
#define _hw__c8a_compare1		_crg, 8, 0x48, 0xFF, 0x00
#define _hw__c8a_imsk			_crg, 8, 0x6E, 0x07, 0x00
#define _hw__c8a_ifr			_crg, 8, 0x35, 0x07, 0x07


/*	Counter0 compare output units
 *
 *	Instance			class, name, id, counter, ocn, ion
 */
//#define _hw_counter0_compare0		_ocua, counter0_compare0, 401, counter0, 0, pin_pd6
//#define _hw_counter0_compare1		_ocua, counter0_compare1, 402, counter0, 1, pin_pd5


/*******************************************************************************
 *									       *
 *	Timer Counter 1							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__c16a_1.h"

/*	Instance			class, name, id, address
 */
#define _hw_counter1			_c16a, 410, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__c16a_ccra			_crg,  8, 0x80, 0xF3,   0x00
#define _hw__c16a_ccrb			_crg,  8, 0x81, 0xDF,   0x00
#define _hw__c16a_ccrc			_crg,  8, 0x82, 0xC0,   0x00
#define _hw__c16a_count			_crg, 16, 0x84, 0xFFFF, 0x0000
#define _hw__c16a_countl		_crg,  8, 0x84, 0xFF,   0x00
#define _hw__c16a_counth		_crg,  8, 0x85, 0xFF,   0x00
#define _hw__c16a_ocra			_crg, 16, 0x88, 0xFFFF, 0x0000
#define _hw__c16a_compare0		_crg, 16, 0x88, 0xFFFF, 0x0000
#define _hw__c16a_ocral			_crg,  8, 0x88, 0xFF,   0x00
#define _hw__c16a_ocrah			_crg,  8, 0x89, 0xFF,   0x00
#define _hw__c16a_ocrb			_crg, 16, 0x8A, 0xFFFF, 0x0000
#define _hw__c16a_compare1		_crg, 16, 0x8A, 0xFFFF, 0x0000
#define _hw__c16a_ocrbl			_crg,  8, 0x8A, 0xFF,   0x00
#define _hw__c16a_ocrbh			_crg,  8, 0x8B, 0xFF,   0x00
#define _hw__c16a_icr			_crg, 16, 0x86, 0xFFFF, 0x0000
#define _hw__c16a_capture0		_crg, 16, 0x86, 0xFFFF, 0x0000
#define _hw__c16a_icrl			_crg,  8, 0x86, 0xFF,   0x00
#define _hw__c16a_icrh			_crg,  8, 0x87, 0xFF,   0x00
#define _hw__c16a_imsk			_crg,  8, 0x6F, 0x27,   0x00
#define _hw__c16a_ifr			_crg,  8, 0x36, 0x27,   0x27

#define _hw__c16a_acic			_irg, hw_acmp0, acic


/*	Counter1 compare output units	class, name, id, counter, channel, io
 */
//#define _hw_counter1_compare0		_ocua, counter1_compare0, 411, counter1, 0, pin_pb1
//#define _hw_counter1_compare1		_ocua, counter1_compare1, 412, counter1, 1, pin_pb2


/*	Counter1 input capture unit	class, name, id, counter, reg, io
 */
//#define _hw_counter1_capture0		_icua, counter1_capture0, 413, counter1, icr, pin_pb0
//#define _hw_counter1_input		_icua, counter1_input,  413, counter1, icr, pin_pb0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__acmpa_1.h"

/*	Instance			class, id, address
 */				        
#define _hw_acmp0			_acmpa, 700, 0

/*	Class registers			class, rw, ra, rwm, rfm
 */				        
#define _hw__acmpa_csr			_crg, 8, 0x28, 0xDF, 0x10


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#include "hwa_atmelavr__eeproma_1.h"

/*	Instance	        	class, id, address
 */
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw__eeproma_arh		_crg,  8, 0x42,   0x03, 0x00
#define _hw__eeproma_arl		_crg,  8, 0x41,   0xFF, 0x00
#define _hw__eeproma_ar			_crg, 16, 0x41, 0x03FF, 0x00
#define _hw__eeproma_dr			_crg,  8, 0x40,   0xFF, 0x00
#define _hw__eeproma_cr			_crg,  8, 0x3F,   0x3F, 0x00

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

#include "hwa_atmelavr__flasha_1.h"

/*	Instance	        	class, id, address
 */
#define _hw_flash0			_flasha, 1100, 0


/*	Class regs			class, rw, ra, rwm, rfm
 */
#define _hw_flasha_csr			_crg, 8, 0x57, 0xBF, 0x00

#define _hw_flasha_spmie		_cb1, csr, 1, 7
#define _hw_flasha_rwwsb		_cb1, csr, 1, 6
#define _hw_flasha_sigrd		_cb1, csr, 1, 5
#define _hw_flasha_rwwsre		_cb1, csr, 1, 4
#define _hw_flasha_blbset		_cb1, csr, 1, 3
#define _hw_flasha_pgwrt		_cb1, csr, 1, 2
#define _hw_flasha_pgers		_cb1, csr, 1, 1
#define _hw_flasha_spmen		_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/


/*					class, vector, controller, enable bit, flag bit
 */
#define _hw_irq_watchdog0		irq,  6, hw_watchdog0, wdie,  wdif
#define _hw_irq_counter1_capture0	irq, 10, hw_counter1,  icie,  icf
#define _hw_irq_counter1_compare0	irq, 11, hw_counter1,  ociea, ocfa
#define _hw_irq_counter1_compare1	irq, 12, hw_counter1,  ocieb, ocfb
#define _hw_irq_counter1_overflow	irq, 13, hw_counter1,  oie,   ov
#define _hw_irq_counter0_compare0	irq, 14, hw_counter0,  ociea, ocfa
#define _hw_irq_counter0_compare1	irq, 15, hw_counter0,  ocieb, ocfb
#define _hw_irq_counter0_overflow	irq, 16, hw_counter0,  oie,   ov
