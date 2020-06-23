
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief A/D converter
 */

/*	Base class
 */
#include "adx_2.h"

#define hw_prescaler_max__adb		, hw_adx_prescaler_max
#define hw_prescaler_min__adb		, hw_adx_prescaler_min

/**
 * @page atmelavr_adb
 * @section atmelavr_adb_act Actions
 *
 * <br>
 * `configure`:
 *
 * __Note__ The ADC is turned off by default. Configuring the ADC automatically
 * turns it on.
 *
 * @code
 * hwa( configure, adc0,
 * 
 *	//  Clock source: the resulting clock frequency should be in
 *	//  the 50..200 kHz range for maximum resolution, and in all
 *	//  case lower than 1 MHz.
 *	//
 *	clock,	   min				// choose the nearest 50 kHz
 *		 | max				// choose the nearest 200 kHz
 *		 | ioclk / 2**n,		// with n in 1..7
 *						
 *	//  How a conversation is started	
 *	//					
 *	trigger,   manual			// with the `trigger` instruction
 *		 | auto				// as soon as a consersion is completed
 *		 | acmp0			// ANA_COMP interrupt request
 *		 | int0				// INT0 interrupt request
 *		 | counter0_compare0		// TIMER0_COMPA interrupt request
 *		 | counter0_overflow		// TIMER0_OVF interrupt request
 *		 | counter1_compare1		// TIMER1_COMPB interrupt request
 *		 | counter1_overflow		// TIMER1_OVF interrupt request
 *		 | counter1_capture,		// TIMER1_CAPT interrupt request
 *						
 *	//  Voltage reference			
 *	//					
 *	vref,	   vcc				// Vcc
 *		 | pin_avcc			// Voltage on AVCC pin
 *		 | pin_aref			// Voltage on AREF pin
 *		 | bandgap_1100mV,		// Internal 1.1V bandgap
 * 
 *	//  Result alignment (default is `right`)
 *	//
 *    [ align,	   left
 *		 | right, ]
 *
 *	//  Input
 *	//
 *	input,	   (pin,adc0..7)
 *		 | agnd
 *		 | bandgap_1100mV
 *		 | temperature );
 * @endcode
 */
#define hwa_configure__adb		, _hwa_cfadb

/*	Mandatory parameter 'clock'
 */
#define _hwa_cfadb(o,a,k,...)					\
  do {									\
    uint8_t mux __attribute__((unused)) = 0xFF ;			\
    _hwa_write( o, en, 1 ); /* turn the ADC on */			\
    HW_B(_hwa_cfadb_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,);	\
    if ( mux != 0xFF ) _hwa_write(o,mux,mux);				\
  } while(0)

#define _hwa_cfadb_kclock_0(o,k,...)			\
  HW_E_VL(k,clock)
#define _hwa_cfadb_kclock_1(o,k,v,...)				\
  HW_B(_hwa_cfadb_vclock_,_hw_adx_clock_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadb_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, (min, max, ioclk / 2**n with n in 1..7))
#define _hwa_cfadb_vclock_1(o,v,k,...)				\
  _hwa_write(o, ps, HW_A1(_hw_adx_clock_##v)(HW_A2(_hw_adx_clock_##v))); \
  HW_B(_hwa_cfadb_ktrigger_,_hw_is_trigger_##k)(o,k,__VA_ARGS__)

/*	Mandatory parameter 'trigger'
 */
#define _hwa_cfadb_ktrigger_0(o,k,...)		\
  HW_E_VL(k,trigger)
#define _hwa_cfadb_ktrigger_1(o,k,v,...)				\
  HW_B(_hwa_cfadb_vtrigger_,_hw_adb_trigger_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadb_vtrigger_0(o,v,...)				\
  HW_E_AVL(trigger, v, manual | auto | int0 | acmp0 | counter0_compare0 | counter0_overflow | counter1_compare1 | counter1_overflow | counter1_capture0)
#define _hwa_cfadb_vtrigger_1(o,v,k,...)				\
  _hwa_write(o,ate, HW_A1(_hw_adb_trigger_##v));			\
  _hwa_write(o,ts, HW_A2(_hw_adb_trigger_##v));			\
  HW_B(_hwa_cfadb_kvref_,_hw_is_vref_##k)(o,k,__VA_ARGS__)

#define _hw_adb_trigger_manual	, 0, 0	/* , ate, ts */
#define _hw_adb_trigger_auto		, 1, 0
#define _hw_adb_trigger_acmp0		, 1, 1
#define _hw_adb_trigger_int0		, 1, 2
#define _hw_adb_trigger_counter0_compare0	, 1, 3
#define _hw_adb_trigger_counter0_overflow	, 1, 4
#define _hw_adb_trigger_counter1_compare1	, 1, 5
#define _hw_adb_trigger_counter1_overflow	, 1, 6
#define _hw_adb_trigger_counter1_capture0	, 1, 7

/*	Mandatory parameter 'vref'
 */
#define _hwa_cfadb_kvref_0(o,k,...)		HW_E_VL(k,vref)
#define _hwa_cfadb_kvref_1(o,k,v,...)		HW_B(_hwa_cfadb_vvref_,_hw_adb_vref_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadb_vvref_0(o,v,...)		HW_E_AVL(vref, v, vcc | pin_avcc | pin_aref | bandgap_1100mV)
#define _hwa_cfadb_vvref_1(o,v,...)			\
  _hwa_write(o,refs, HW_A1(_hw_adb_vref_##v));	\
  _hwa_cfadb_align(o,__VA_ARGS__)

#define _hw_adb_vref_vcc		, 1	/* , refs */
#define _hw_adb_vref_pin_aref		, 0
#define _hw_adb_vref_bandgap_1100mV	, 3

/*	Optionnal parameter 'align'
 */
#define _hwa_cfadb_align(o,k,...)				\
  HW_B(_hwa_cfadb_kalign_,_hw_is_align_##k)(o,k,__VA_ARGS__)
#define _hwa_cfadb_kalign_0(o,...)		\
  _hwa_cfadb_in(o,__VA_ARGS__)
#define _hwa_cfadb_kalign_1(o,k,v,...)				\
  HW_B(_hwa_cfadb_valign_,_hw_adb_align_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadb_valign_0(o,v,...)				\
  HW_E_AVL(align, v, left | right)
#define _hwa_cfadb_valign_1(o,v,...)			\
  _hwa_write(o,lar, HW_A1(_hw_adb_align_##v));	\
  _hwa_cfadb_in(o,__VA_ARGS__)

#define _hw_adb_align_left		, 1	/* , lar */
#define _hw_adb_align_right		, 0

/*	Mandatory parameter 'input'
 */
#define _hwa_cfadb_kinput(o,k,...)					\
  HW_B(_hwa_cfadb_kinput_,_hw_is_input_##k)(o,k,__VA_ARGS__)
#define _hwa_cfadb_kinput_0(o,k,...)		\
  HW_E_VL(k,input)
#define _hwa_cfadb_kinput_1(o,k,v,...)				\
  if ( HW_IS(,HW_A0(_hw_adb_input_##v)) )				\
    _hwa_write(o,mux, HW_A1(_hw_adb_input_##v,0));			\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc0) ) )		\
    _hwa_write(o,mux, 0);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc1) ) )		\
    _hwa_write(o,mux, 1);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc2) ) )		\
    _hwa_write(o,mux, 2);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc3) ) )		\
    _hwa_write(o,mux, 3);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc4) ) )		\
    _hwa_write(o,mux, 4);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc5) ) )		\
    _hwa_write(o,mux, 5);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc6) ) )		\
    _hwa_write(o,mux, 6);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( (pin,adc7) ) )		\
    _hwa_write(o,mux, 7);						\
  else									\
    HWA_ERR("`input` can be '(pin,adc0..7)' (or synonyms), "		\
	    "`temperature`, `bandgap_1100mV`, or `ground`  but not `"#v"`."); \
  HW_EOL(__VA_ARGS__)



/*	Mandatory parameter `input`
 */
#define _hwa_cfadb_in(o,k,...)		HW_BW(_hwa_cfadb_in,input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadb_in1(o,k,v,...)	HW_BV(_hwa_cfadb_in1,_hw__adbinput_,v)(o,v,__VA_ARGS__)
#define _hwa_cfadb_in10(k)		HW_E(HW_EM_XNIL(k,((pin,adc0..7),temperature,bandgap,ground))) // _hwa_cfadb_in12
#define _hwa_cfadb_in11(v)		mux=v;	_hwa_cfadb_in12
#define _hwa_cfadb_in12(o,k,...)	HW_EOL(__VA_ARGS__)
#define _hwa_cfadb_in1b(o,v,...)					\
  uint32_t a = HW_ADDRESS(v);						\
  if ( a==HW_ADDRESS((pin,adc0)) )	mux=0;				\
  else if ( a==HW_ADDRESS((pin,adc1)) )	mux=1;				\
  else if ( a==HW_ADDRESS((pin,adc2)) )	mux=2;				\
  else if ( a==HW_ADDRESS((pin,adc3)) )	mux=3;				\
  else if ( a==HW_ADDRESS((pin,adc4)) )	mux=4;				\
  else if ( a==HW_ADDRESS((pin,adc5)) )	mux=5;				\
  else if ( a==HW_ADDRESS((pin,adc6)) )	mux=6;				\
  else if ( a==HW_ADDRESS((pin,adc7)) )	mux=7;				\
  else HWA_ERR(HW_Q(HW_Q(v) is not in ((pin,adc0..7),temperature,bandgap_1100mV,ground))); HW_EOL(__VA_ARGS__)

#define _hw__adbinput_temperature	, 8	/* , mux */
#define _hw__adbinput_bandgap_1100mV	, 14
#define _hw__adbinput_ground		, 15


/*  Power management
 */
#define hw_power__adb			, _hw_power
#define hwa_power__adb			, _hwa_power


/**
 * @page atmelavr_adb
 *
 * <br>
 * `turn`:
 *
 * The ADC must be turned off for the analog comparator to have access to the
 * analog multiplexer.
 *
 * __Note__ This is not related to power management. Assuming the target device
 * supports it, use the `power` action if you want to power the ADC on/off.
 *
 * @code
 * hw( turn, adc0, on | off );
 * @endcode
 */
#define hw_turn__adb			, _hw_turn_adx_


/**
 * @page atmelavr_adb
 *
 * @code
 * hwa( turn, adc0, on | off );
 * @endcode
 */
#define hwa_turn__adb			, _hwa_turn_adx_


/**
 * @page atmelavr_adb
 *
 * <br>
 * `trigger`:
 *
 * @code
 * hw( trigger, adc0 );
 * @endcode
 */
#define hw_trigger__adb		, _hw_trigger_adx_

/**
 * @page atmelavr_adb
 *
 * @code
 * hwa( trigger, adc0 );
 * @endcode
 */
#define hwa_trigger__adb		, _hwa_trigger_adx_


/**
 * @page atmelavr_adb
 *
 * <br>
 * `read`:
 *
 * @code
 * uint16_t adc = hw( read, adc0 );
 * @endcode
 */
#define hw_read__adb			, _hw_rdad10_

/**
 * @page atmelavr_adb
 *
 * <br>
 * `read`:
 *
 * @code
 * uint16_t adc = hw_atomic_read( adc0 );
 * @endcode
 */
#define hw_atomic_read__adb		, _hw_ardad10_


/**
 * @page atmelavr_adb
 * @section atmelavr_adb_stat Status
 *
 * You'll usually use the IRQ flag to test whether a conversion is completed:
 *
 * @code
 * hw( trigger, adc0 );
 * while ( !hw( read, (adc0,irq) ) ) {}
 * hw( clear, (adc0,irq) );
 * uint16_t result = hw( read, adc0 );
 * @endcode
 *
 * but you can also check the `busy` flag of the status of the converter to know
 * whether a conversion is in progress:
 *
 * @code
 * hw_stat_t(adc0)	st ;
 * st = hw(stat,adc0);
 * if ( !st.busy )
 *   hw( trigger, adc0 );
 * @endcode
 */
#define hw_stat__adb			, _hw_stat_adx_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__adb(o,a)	_hwa_setup__adx_(o)
#define _hwa_init__adb(o,a)		_hwa_init__adx_(o)
#define _hwa_commit__adb(o,a)	_hwa_commit__adx_(o)


/**
 * @page atmelavr_adb
 * @section atmelavr_adb_internals Internals
 *
 * Class `_adb` objects hold the following hardware registers:
 *
 *  * `admux`: analog multiplexer and voltage reference
 *  * `sra`: control/status register a
 *  * `srb`: control/status register b
 *  * `adc`: conversion result
 *
 * that hold the following logical registers:
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
 *  * `ie`: overflow IRQ mask
 *  * `if`: overflow IRQ flag
 */
