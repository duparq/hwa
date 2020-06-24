
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
 * @addtogroup atmelavr_adc
 * @section atmelavr_adcac Actions
 *
 * <br><br> hwa( configure, ... ) configures the ADC.
 *
 * Single-end mode:
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
 *		 | ioclk / 2**(1..7),		// IOCLK divided by 2,4,..,128
 *						
 *	//  How a conversation is started	
 *	//					
 *	trigger,   manual			// Use hw(trigger,adc0)
 *		 | auto				// as soon as a conversion is completed
 *		 | (acmp0,irq)			// Other trigger sources
 *		 | (int0,irq)			//
 *		 | (counter0,compare0,irq)	//
 *		 | (counter0,overflow,irq)	//
 *		 | (counter0,compare1,irq)	//
 *		 | pcic0,			//
 *						
 *	//  Voltage reference			
 *	//					
 *	vref,	   vcc				// Vcc
 *		 | (pin,aref)			// Voltage on AREF pin
 *		 | bandgap_1100mV		// Internal 1.1V bandgap
 *		 | bandgap_2560mV		// Internal 2.56V bandgap
 *		 | bandgap_2560mV_aref,		//   + output on AREF pin for decoupling
 * 
 *	//  Result alignment (default is `right`)
 *	//
 *    [ align,	   left
 *		 | right, ]
 *
 *	//  Input
 *	//
 *	input,	   (pin,adc0..3)
 *		 | gnd
 *		 | bandgap
 *		 | temperature
 * );
 * @endcode
 *
 * The differential mode allows the use of the 20x gain stage:
 *
 * @code
 * hwa( configure, ADC,
 * 
 *	clock,            ... ,			// See above
 *	trigger,          ... ,			//
 *	vref,             ... ,			//
 *    [ align,            ... , ]		//
 * 
 *    [ polarity,	  unipolar		// Default
 *    		        | bipolar, ]
 *
 *    [ gain,	 	  1			// Default
 *    		        | 20, ]
 * 
 *      positive_input,	  (pin,adc0)		// HWA will trigger an error
 *                      | (pin,adc2),		// if you try to use
 * 						// a combination of inputs
 *      negative_input,	  (pin,adc0..3)		// that is not available
 * );
 * @endcode
 *
 * @note The ADC and the analog comparator share the same output of the analog
 * multiplexer. The ADC is disabled after reset. Configuring the ADC
 * automatically enables it. When the ADC is enabled, the analog comparator
 * `acmp0` can not use the analog multiplexer output. Use hw(disable,adc0) to
 * disable the ADC and let acmp0 use the analog multiplexer output.
 */
#define hwa_configure__adc		, _hwa_cfadc

/*  Mandatory parameter `clock`
 */
#define _hwa_cfadc(o,a,k,...)				\
  do {							\
    uint8_t gain __attribute__((unused)) =  1 ;		\
    _hwa_write(o,en,1); /* enable the ADC */		\
    HW_BW(_hwa_cfadcck,clock,k)(o,k,__VA_ARGS__,,);	\
  } while(0)


/*	Mandatory parameter 'clock'
 */
#define _hwa_cfadcck0(o,k,...)		HW_E(HW_EM_AN(k,clock))
#define _hwa_cfadcck1(o,k,v,...)	HW_BV(_hwa_cfadcck1,adxclock_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadcck10(v,o)		HW_E(HW_EM_VAL(v,clock,(min, max, ioclk/2**(1..7)))) HW_EAT // Pop
#define _hwa_cfadcck11(f,v,o)		_hwa_write(o,ps,f(v)); _hwa_cfadctrg // Pop

/*	Mandatory parameter 'trigger'
 */
#define _hwa_cfadctrg(o,v,k,...)	HW_BW(_hwa_cfadctrg,trigger,k)(o,v,__VA_ARGS__)
#define _hwa_cfadctrg0(o,k,...)		HW_E(HW_EM_AN(k,trigger))
#define _hwa_cfadctrg1(o,k,v,...)	HW_B(_hwa_cfadctrg2, _hw_par v)(o,v,__VA_ARGS__)

/*		"manual" or "auto"
 */
#define _hwa_cfadctrg20(o,v,...)	HW_BV(_hwa_cfadctrg20,adctrg_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadctrg201(_ate,_ts,o)	_hwa_write(o,ate,_ate); _hwa_write(o,ts,_ts); _hwa_cfadcref
#define _hwa_cfadctrg200(v,...)		HW_E(HW_EM_VAL(v,trigger,(manual, auto, (int0,irq), (acmp0,irq), \
								  (counter0,compare0,irq), (counter0,overflow,irq), \
								  (counter1,compare1,irq), (counter1,overflow,irq), \
								  (counter1,capture0,irq)))); HW_EAT // Pop
/*		IRQs
 */
#define _hwa_cfadctrg21(o,v,...)	_hwa_cfadctrg22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadctrg22(...)		_hwa_cfadctrg23(__VA_ARGS__)
#define _hwa_cfadctrg23(d,...)		HW_BW(_hwa_cfadctrg3,_irq,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadctrg30(d,o,v,...)	_hwa_cfadctrg200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadctrg31(d,o,v,...)	HW_BV(_hwa_cfadctrg20,adctrg_,HW_A1 d,)(o,v,__VA_ARGS__) // Push

#define _hw_adctrg_manual			, 0, 0	/* , ate, ts */
#define _hw_adctrg_auto				, 1, 0
#define _hw_adctrg_acmp0_irq			, 1, 1
#define _hw_adctrg_int0_irq			, 1, 2
#define _hw_adctrg_counter0_compare0_irq	, 1, 3
#define _hw_adctrg_counter0_overflow_irq	, 1, 4
#define _hw_adctrg_counter0_compare1_irq	, 1, 5
#define _hw_adctrg_pcic0			, 1, 6

/*	Mandatory parameter 'vref'
 */
#define _hwa_cfadcref(o,v,k,...)	HW_BW(_hwa_cfadcref,vref,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcref0(o,k,...)		HW_E(HW_EM_AN(k,vref))
#define _hwa_cfadcref1(o,k,v,...)	HW_B(_hwa_cfadcref2, _hw_par v)(o,v,__VA_ARGS__)

/*		"bandgap_1100mV"
 */
#define _hwa_cfadcref20(o,v,...)	HW_BV(_hwa_cfadcref20,adcref_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadcref201(v,o)		_hwa_write(o,refs,v); _hwa_cfadcal // Pop
#define _hwa_cfadcref200(v,...)		HW_E(HW_EM_VAL(v,vref,(vcc, (pin,aref), bandgap_1100mV, \
							       bandgap_2560mV, bandgap_2560mV_aref))) HW_EAT // Pop

/*		vcc, (pin,aref)
 */
#define _hwa_cfadcref21(o,v,...)	_hwa_cfadcref22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadcref22(...)		_hwa_cfadcref23(__VA_ARGS__)
#define _hwa_cfadcref23(d,...)		HW_BW(_hwa_cfadcref3,_pin,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadcref30(d,o,v,...)	_hwa_cfadcref200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadcref31(d,o,v,...)	HW_BV(_hwa_cfadcref20,adcref_,HW_A1 d,o)(o,v,__VA_ARGS__) // Push

#define _hw_adcref_vcc			, 0	/* , refs */
#define _hw_adcref_pin_aref		, 1
#define _hw_adcref_bandgap_1100mV	, 2
#define _hw_adcref_bandgap_2560mV	, 6
#define _hw_adcref_bandgap_2560mV_aref	, 7

/*  Optionnal parameter 'align'
 */
#define _hwa_cfadcal(o,v,k,...)		HW_BW(_hwa_cfadcal,align,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcal0			_hwa_cfadcpo
#define _hwa_cfadcal1(o,k,v,...)	HW_BV(_hwa_cfadcal1,adcal_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadcal10(v,o)		HW_E(HW_EM_VOAL(v,align,(left,right))) HW_EAT // Pop
#define _hwa_cfadcal11(v,o)		_hwa_write(o,lar,v); _hwa_cfadcal12 // Pop
#define _hwa_cfadcal12(o,v,k,...)	_hwa_cfadcpo(o,k,__VA_ARGS__)

#define _hw_adcal_left			, 1	/* , lar */
#define _hw_adcal_right			, 0

/*  Optionnal parameter `polarity`
 */
#define _hwa_cfadcpo(o,k,...)		HW_BW(_hwa_cfadcpo,polarity,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcpo0			_hwa_cfadcgn
#define _hwa_cfadcpo1(o,k,v,...)	HW_BV(_hwa_cfadcpo1,adcpo_,v,o)(o,v,__VA_ARGS__) // PUSH
#define _hwa_cfadcpo10(v,o)		HW_E(HW_EM_VOAL(v,polarity,(unipolar,bipolar))) HW_EAT // POP
#define _hwa_cfadcpo11(v,o)		_hwa_write(o,bin,v); _hwa_cfadcgn  // POP

#define _hw_adcpo_unipolar		, 0	/* , bin */
#define _hw_adcpo_bipolar		, 1

/*  Optionnal parameter `gain`
 */
#define _hwa_cfadcgn(o,k,...)		HW_BW(_hwa_cfadcgn,gain,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcgn0			_hwa_cfadcin // -> 'input'
#define _hwa_cfadcgn1(o,k0,v,k,...)	gain = (uint8_t)(v); _hwa_cfadcpi(o,k,__VA_ARGS__) // -> 'positive_input'

/*  Optionnal parameter `input`
 */
#define _hwa_cfadcin(o,k,...)		HW_BW(_hwa_cfadcin,input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcin0			_hwa_cfadcpi
#define _hwa_cfadcin1(o,k,v,...)	HW_BV(_hwa_cfadcin1,adcin_,v,o)(o,v,__VA_ARGS__) // PUSH
#define _hwa_cfadcin10(v,o)		HW_E(HW_EM_VAL(v,input,((pin,adc0..3),temperature,bandgap,gnd))) HW_EAT // POP
#define _hwa_cfadcin11(v,o)		_hwa_write(o,mux,v); _hwa_cfadcin12 // Pop
#define _hwa_cfadcin12(o,v,...)		if ( gain != 1 ) HWA_E(HW_EM_AVM(gain,1)); HW_EOL(__VA_ARGS__)

#define _hwa_cfadcin1_(o,v,...)		_hwa_write(o,mux,_hw_adcmuxse(HW_ADDRESS(v))); HW_EOL(__VA_ARGS__)

#define _hw_adcin_bandgap		, 12	/* , mux */
#define _hw_adcin_gnd			, 13
#define _hw_adcin_temperature		, 15

/*  Compute the mux register value from input pin address
 */
HW_INLINE uint8_t _hw_adcmuxse( uint32_t a )
{
  if ( a==HW_ADDRESS(pin_adc0) ) return 0;
  if ( a==HW_ADDRESS(pin_adc1) ) return 1;
  if ( a==HW_ADDRESS(pin_adc2) ) return 2;
  if ( a==HW_ADDRESS(pin_adc3) ) return 3;
  HWA_E(HW_EM_AVL(input,((pin,adc0..3),temperature,bandgap,gnd)));
  return 0 ;  
}

/*	Process 'positive_input' & 'negative_input' for differential mode
 */
#define _hwa_cfadcpi(o,k,...)		HW_BW(_hwa_cfadcpi,positive_input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcpi0(o,k,...)		HW_E(HW_EM_AN(k,positive_input))
#define _hwa_cfadcpi1(o,k0,v,k,...)	\
  uint8_t pi __attribute__((unused)) = _hw_adcin(HW_ADDRESS(v));	\
  HW_BW(_hwa_cfadcni,negative_input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadcni0(o,k,...)		HW_E(HW_EM_AN(k,negative_input))
#define _hwa_cfadcni1(o,k,v,...)	\
  uint8_t ni __attribute__((unused)) = _hw_adcin(HW_ADDRESS(v));	\
  _hwa_write(o,mux,_hw_adcmuxdi(pi,ni,gain)); HW_EOL(__VA_ARGS__)

/*  Compute the mux register value from inputs and gain
 */
HW_INLINE uint8_t _hw_adcmuxdi ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( gain != 1 && gain != 20 ) {
    HWA_E(HW_EM_AVL(gain,(1, 20)));
    return 0;
  }

  if ( pos==0 ) {
    if ( neg==0 )
      return 0x08 + (gain==20);
    else if ( neg==1 )
      return 0x0A + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc0), (pin,adc1))));
  }
  else if ( pos==2 ) {
    if ( neg==2 )
      return 0x04 + (gain==20);
    else if ( neg==3 )
      return 0x06 + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc2), (pin,adc3))));
  }
  else
    HWA_E(HW_EM_AVL(positive_input,((pin,adc0), (pin,adc2))));
  return 0;
}


/*  Power management
 */
#define hw_power__adc			, _hw_power
#define hwa_power__adc			, _hwa_power


/**
 * @addtogroup atmelavr_adc
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
#define hw_enable__adc			, _hw_enable_adx_
#define hwa_enable__adc			, _hwa_enable_adx_


/**
 * @addtogroup atmelavr_adc
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
#define hw_disable__adc			, _hw_disable_adx_
#define hwa_disable__adc		, _hwa_disable_adx_


/**
 * @addtogroup atmelavr_adc
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
#define hw_trigger__adc			, _hw_trigger_adx_
#define hwa_trigger__adc		, _hwa_trigger_adx_


/**
 * @addtogroup atmelavr_adc
 *
 * <br><br> hw( read, ... ) returns the result of the conversion.
 *
 * @code
 * uint16_t adc = hw( read, adc0 );
 * @endcode
 */
#define hw_read__adc			, _hw_rdadx_

/**
 * @addtogroup atmelavr_adc
 *
 * <br><br> hw( read_atomic, ... ) returns the result of the conversion after having
 * cleared the I bit of the status register and set it again as soon as possible.
 *
 * @code
 * uint16_t adc = hw( read_atomic, adc0 );
 * @endcode
 */
#define hw_read_atomic__adc		, _hw_ardadx_


/**
 * @addtogroup atmelavr_adc
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
#define hw_stat__adc			, _hw_stat_adx_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__adc(o,a)		_hwa_setup__adx_(o)
#define _hwa_init__adc(o,a)		_hwa_init__adx_(o)
#define _hwa_commit__adc(o,a)		_hwa_commit__adx_(o)


/**
 * @addtogroup atmelavr_adc
 * @section atmelavr_adcregs Registers
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
