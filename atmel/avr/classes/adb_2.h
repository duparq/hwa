
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit A/D converter
 */

/*	Base class
 */
#include "adx_2.h"

/**
 * @addtogroup atmelavr_adb
 * @section atmelavr_adbact Actions
 *
 * <br><br> hwa( configure, ... ) configures the ADC.
 *
 * @code
 * hwa( configure, adc0,
 *
 *	//  Clock source: the resulting clock frequency should be in
 *	//  the 50..200 kHz range for maximum resolution, and in all
 *	//  case lower than 1 MHz.
 *	//
 *	clock,	   min				// Nearest 50 kHz
 *		 | max				// Nearest 200 kHz
 *		 | ioclk / 2**(1..7),		// IOCLK divided by 2,4,..,128
 *
 *	//  How a conversion is started
 *	//
 *	trigger,   manual			// Use hw(trigger,adc0)
 *		 | auto				// As soon as a conversion is completed
 *		 | (acmp0,irq)			// Other trigger sources
 *		 | (int0,irq)			//
 *		 | (counter0,compare0,irq)	//
 *		 | (counter0,overflow,irq)	//
 *		 | (counter1,compare1,irq)	//
 *		 | (counter1,overflow,irq)	//
 *		 | (counter1,capture,irq),	//
 *
 *	//  Voltage reference
 *	//
 *	vref,	   (pin,avcc)			// Voltage on AVCC pin
 *		 | (pin,aref)			// Voltage on AREF pin
 *		 | bandgap_1100mV,		// Internal 1.1V bandgap
 *
 *	//  Result alignment
 *	//
 *    [ align,	   left				//
 *		 | right, ]			// Default
 *
 *	//  Input
 *	//
 *	input,	   (pin,adc0..7)
 *		 | gnd
 *		 | bandgap_1100mV
 *		 | temperature
 * );
 * @endcode
 *
 * @note The ADC and the analog comparator share the same output of the analog
 * multiplexer. The ADC is disabled after reset. Configuring the ADC
 * automatically enables it. When the ADC is enabled, the analog comparator
 * `acmp0` can not use the analog multiplexer output. Use hw(disable,adc0) to
 * disable the ADC and let acmp0 use the analog multiplexer output.
 */
#define hwa_configure__adb		, _hwa_cfadb

#define _hwa_cfadb(o,a,k,...)				\
  do {							\
    _hwa_write(o,en,1); /* turn the ADC on */		\
    HW_BW(_hwa_cfadbck,clock,k)(o,k,__VA_ARGS__,,);	\
  } while(0)

/*	Mandatory parameter 'clock'
 */
#define _hwa_cfadbck0(o,k,...)		HW_E(HW_EM_AN(k,clock))
#define _hwa_cfadbck1(o,k,v,...)	HW_BV(_hwa_cfadbck1,adxclock_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbck10(v,o)		HW_E(HW_EM_VAL(v,clock,(min, max, ioclk/2**(1..7)))) HW_EAT // Pop
#define _hwa_cfadbck11(f,v,o)		_hwa_write(o,ps,f(v)); _hwa_cfadbtrg // Pop

/*	Mandatory parameter 'trigger'
 */
#define _hwa_cfadbtrg(o,v,k,...)	HW_BW(_hwa_cfadbtrg,trigger,k)(o,v,__VA_ARGS__)
#define _hwa_cfadbtrg0(o,k,...)		HW_E(HW_EM_AN(k,trigger))
#define _hwa_cfadbtrg1(o,k,v,...)	HW_B(_hwa_cfadbtrg2, _hw_par v)(o,v,__VA_ARGS__)

/*		"manual" or "auto"
 */
#define _hwa_cfadbtrg20(o,v,...)	HW_BV(_hwa_cfadbtrg20,adbtrg_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbtrg201(_ate,_ts,o)	_hwa_write(o,ate,_ate); _hwa_write(o,ts,_ts); _hwa_cfadbref
#define _hwa_cfadbtrg200(v,...)		HW_E(HW_EM_VAL(v,trigger,(manual, auto, (int0,irq), (acmp0,irq), \
								  (counter0,compare0,irq), (counter0,overflow,irq), \
								  (counter1,compare1,irq), (counter1,overflow,irq), \
								  (counter1,capture0,irq)))); HW_EAT // Pop
/*		IRQs
 */
#define _hwa_cfadbtrg21(o,v,...)	_hwa_cfadbtrg22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadbtrg22(...)		_hwa_cfadbtrg23(__VA_ARGS__)
#define _hwa_cfadbtrg23(d,...)		HW_BW(_hwa_cfadbtrg3,_irq,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadbtrg30(d,o,v,...)	_hwa_cfadbtrg200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbtrg31(d,o,v,...)	HW_BV(_hwa_cfadbtrg20,adbtrg_,HW_A1 d,)(o,v,__VA_ARGS__) // Push

#define _hw_adbtrg_manual			, 0, 0	/* , ate, ts */
#define _hw_adbtrg_auto				, 1, 0
#define _hw_adbtrg_acmp0_irq			, 1, 1
#define _hw_adbtrg_int0_irq			, 1, 2
#define _hw_adbtrg_counter0_irq_compare0	, 1, 3
#define _hw_adbtrg_counter0_compare0_irq	, 1, 3
#define _hw_adbtrg_counter0_irq			, 1, 4
#define _hw_adbtrg_counter0_irq_overflow	, 1, 4
#define _hw_adbtrg_counter1_irq_compare1	, 1, 5
#define _hw_adbtrg_counter1_compare1_irq	, 1, 5
#define _hw_adbtrg_counter1_irq			, 1, 6
#define _hw_adbtrg_counter1_overflow_irq	, 1, 6
#define _hw_adbtrg_counter1_irq_capture0	, 1, 7
#define _hw_adbtrg_counter1_capture0_irq	, 1, 7

/*	Mandatory parameter 'vref'
 */
#define _hwa_cfadbref(o,v,k,...)	HW_BW(_hwa_cfadbref,vref,k)(o,k,__VA_ARGS__)
#define _hwa_cfadbref0(o,k,...)		HW_E(HW_EM_AN(k,vref))
#define _hwa_cfadbref1(o,k,v,...)	HW_B(_hwa_cfadbref2, _hw_par v)(o,v,__VA_ARGS__)

/*		"bandgap_1100mV"
 */
#define _hwa_cfadbref20(o,v,...)	HW_BV(_hwa_cfadbref20,adbref_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbref201(v,o)		_hwa_write(o,refs,v); _hwa_cfadbal // Pop
#define _hwa_cfadbref200(v,...)		HW_E(HW_EM_VAL(v,vref,((pin,avcc), (pin,aref), bandgap_1100mV))) HW_EAT // Pop

/*		(pin,aref) or (pin,avcc)
 */
#define _hwa_cfadbref21(o,v,...)	_hwa_cfadbref22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadbref22(...)		_hwa_cfadbref23(__VA_ARGS__)
#define _hwa_cfadbref23(d,...)		HW_BW(_hwa_cfadbref3,_pin,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadbref30(d,o,v,...)	_hwa_cfadbref200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbref31(d,o,v,...)	HW_BV(_hwa_cfadbref20,adbref_,HW_A1 d,o)(o,v,__VA_ARGS__) // Push

#define _hw_adbref_pin_aref		, 0	/* , refs */
#define _hw_adbref_pin_avcc		, 1
#define _hw_adbref_bandgap_1100mV	, 3

/*	Optionnal parameter 'align'
 */
#define _hwa_cfadbal(o,v,k,...)		HW_BW(_hwa_cfadbal,align,k)(o,k,__VA_ARGS__)
#define _hwa_cfadbal0			_hwa_cfadbin
#define _hwa_cfadbal1(o,k,v,...)	HW_BV(_hwa_cfadbal1,adbal_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbal10(v,o)		HW_E(HW_EM_VOAL(v,align,(left,right))) HW_EAT // Pop
#define _hwa_cfadbal11(v,o)		_hwa_write(o,lar,v); _hwa_cfadbin // Pop

#define _hw_adbal_left			, 1	/* , lar */
#define _hw_adbal_right			, 0

/*	Mandatory parameter `input`
 */
#define _hwa_cfadbin(o,v,k,...)		HW_BW(_hwa_cfadbin,input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadbin0(k)		HW_E(HW_EM_AN(k,input))
#define _hwa_cfadbin1(o,k,v,...)	HW_BV(_hwa_cfadbin1,adbin_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadbin10(v,o)		HW_E(HW_EM_VAL(v,input,((pin,adc0..7),temperature,bandgap,gnd))) HW_EAT // Pop
#define _hwa_cfadbin11(v,o)		_hwa_write(o,mux,v); _hwa_cfadbin12 // Pop
#define _hwa_cfadbin12(o,v,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfadbin1_(o,v,...)		_hwa_write(o,mux,_hw_adbin(HW_ADDRESS(v))); HW_EOL(__VA_ARGS__)

#define _hw_adbin_temperature		, 8	/* , mux */
#define _hw_adbin_bandgap_1100mV	, 14
#define _hw_adbin_gnd			, 15

HW_INLINE uint8_t _hw_adbin( uint32_t a )
{
  if ( a==HW_ADDRESS(pin_adc0) ) return 0;
  if ( a==HW_ADDRESS(pin_adc1) ) return 1;
  if ( a==HW_ADDRESS(pin_adc2) ) return 2;
  if ( a==HW_ADDRESS(pin_adc3) ) return 3;
  if ( a==HW_ADDRESS(pin_adc4) ) return 4;
  if ( a==HW_ADDRESS(pin_adc5) ) return 5;
  if ( a==HW_ADDRESS(pin_adc6) ) return 6;
  if ( a==HW_ADDRESS(pin_adc7) ) return 7;
  HWA_E(HW_EM_AVL(input,((pin,adc0..7), temperature, bandgap_1100mV, gnd)));
  return 0 ;  
}


/*  Power management
 */
#define hw_power__adb			, _hw_power
#define hwa_power__adb			, _hwa_power


/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( enable, ... ) / hwa( enable, ... ) enables the ADC.
 *
 * @code
 * hw( enable, adc0 );
 * @endcode
 *
 * @code
 * hwa( enable, adc0 );
 * @endcode
 */
#define hw_enable__adb			, _hw_enable_adx_
#define hwa_enable__adb			, _hwa_enable_adx_


/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( disable, ... ) / hwa( disable, ... ) disables the ADC.
 *
 * @code
 * hw( disable, adc0 );
 * @endcode
 *
 * @code
 * hwa( disable, adc0 );
 * @endcode
 */
#define hw_disable__adb			, _hw_disable_adx_
#define hwa_disable__adb		, _hwa_disable_adx_


/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( trigger, ... ) / hwa( trigger, ... ) starts a conversion.
 *
 * @code
 * hw( trigger, adc0 );
 * @endcode
 *
 * @code
 * hwa( trigger, adc0 );
 * @endcode
 */
#define hw_trigger__adb			, _hw_trigger_adx_
#define hwa_trigger__adb		, _hwa_trigger_adx_


/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( read, ... ) returns the result of the conversion.
 *
 * @code
 * uint16_t adc = hw( read, adc0 );
 * @endcode
 */
#define hw_read__adb			, _hw_rdadx_

/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( read_atomic, ... ) returns the result of the conversion after having
 * cleared the I bit of the status register and set it again as soon as possible.
 *
 * @code
 * uint16_t adc = hw( read_atomic, adc0 );
 * @endcode
 */
#define hw_read_atomic__adb		, _hw_ardadx_


/**
 * @addtogroup atmelavr_adb
 *
 * <br><br> hw( stat, ... ) returns the status of the ADC, that contains a
 * single 'busy' bit.
 *
 * @code
 * hw_stat_t(adc0)	st ;
 * st = hw(stat,adc0);
 * if ( !st.busy )		// No conversion pending?
 *   hw( trigger, adc0 );	//   Trigger one
 * @endcode
 *
 * You'll use the IRQ flag to test whether a conversion is completed:
 *
 * @code
 * hw( trigger, adc0 );
 * while ( !hw( read, (adc0,irq) ) ) {}
 * hw( clear, (adc0,irq) );
 * uint16_t result = hw( read, adc0 );
 * @endcode
 */
#define hw_stat__adb			, _hw_stat_adx_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__adb(o,a)		_hwa_setup__adx_(o)
#define _hwa_init__adb(o,a)		_hwa_init__adx_(o)
#define _hwa_commit__adb(o,a)		_hwa_commit__adx_(o)


/**
 * @addtogroup atmelavr_adb
 * @section atmelavr_adbregs Registers
 *
 * Hardware registers:
 *
 *  * `admux`: analog multiplexer and voltage reference
 *  * `sra`: control/status register a
 *  * `srb`: control/status register b
 *  * `adc`: conversion result
 *
 * Logical registers:
 *
 *  * `refs`: voltage reference
 *  * `mux`: analog multiplexer
 *  * `en`: enable
 *  * `sc`: start conversion
 *  * `ate`: auto trigger enable
 *  * `ps`: clock prescaler
 *  * `bin`: bipolar input mode
 *  * `lar`: left-aligned result
 *  * `ts`: trigger source
 *  * `ie`: conversion done IRQ mask
 *  * `if`: conversion done IRQ flag
 */
