
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

/* #define hw_prescaler_max__ada		, hw_adx_prescaler_max */
/* #define hw_prescaler_min__ada		, hw_adx_prescaler_min */

/**
 * @addtogroup atmelavr_ada
 * @section atmelavr_adaac Actions
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
 *		 | (counter1,compare1,irq)	//
 *		 | (counter1,overflow,irq)	//
 *		 | (counter1,capture,irq),	//
 *
 *	//  Voltage reference
 *	//
 *	vref,	   vcc				// Vcc
 *		 | (pin,aref)			// Voltage on AREF pin
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
 *		 | gnd
 *		 | bandgap
 *		 | temperature );
 * @endcode
 *
 * The differential mode allows the use of the 20x gain stage:
 *
 * @code
 * hwa( configure, adc0,
 * 
 *	clock,           ... ,			// See above
 *	trigger,         ... ,			//
 *	vref,            ... ,			//
 *    [ align,           ... , ]		//
 *
 *    [ polarity,	 unipolar		// Default
 *    		       | bipolar, ]
 *
 *    [ gain,		 1			// Default
 *    		       | 20, ]
 * 
 *      positive_input,	 (pin,adc0..7)		// HWA will trigger an error if you
 * 						// try to use a combination of inputs
 *      negative_input,	 (pin,adc0..7)		// that is not available
 * );
 * @endcode
 *
 * @note The ADC and the analog comparator share the same output of the analog
 * multiplexer. The ADC is disabled after reset. Configuring the ADC
 * automatically enables it. When the ADC is enabled, the analog comparator
 * `acmp0` can not use the analog multiplexer output. Use hw(disable,adc0) to
 * disable the ADC and let acmp0 use the analog multiplexer output.
 */
#define hwa_configure__ada		, _hwa_cfada

/*  Mandatory parameter `clock`
 */
#define _hwa_cfada(o,a,k,...)				\
  do {							\
    uint8_t gain __attribute__((unused)) =  1 ;		\
    _hwa_write(o,en,1); /* enable the ADC */		\
    HW_BW(_hwa_cfadack,clock,k)(o,k,__VA_ARGS__,,);	\
  } while(0)


/*	Mandatory parameter 'clock'
 */
#define _hwa_cfadack0(o,k,...)		HW_E(HW_EM_AN(k,clock))
#define _hwa_cfadack1(o,k,v,...)	HW_BV(_hwa_cfadack1,adxclock_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadack10(v,o)		HW_E(HW_EM_VAL(v,clock,(min, max, ioclk/2**(1..7)))) HW_EAT // Pop
#define _hwa_cfadack11(f,v,o)		_hwa_write(o,ps,f(v)); _hwa_cfadatrg // Pop

/*	Mandatory parameter 'trigger'
 */
#define _hwa_cfadatrg(o,v,k,...)	HW_BW(_hwa_cfadatrg,trigger,k)(o,v,__VA_ARGS__)
#define _hwa_cfadatrg0(o,k,...)		HW_E(HW_EM_AN(k,trigger))
#define _hwa_cfadatrg1(o,k,v,...)	HW_B(_hwa_cfadatrg2, _hw_par v)(o,v,__VA_ARGS__)

/*		"manual" or "auto"
 */
#define _hwa_cfadatrg20(o,v,...)	HW_BV(_hwa_cfadatrg20,adatrg_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadatrg201(_ate,_ts,o)	_hwa_write(o,ate,_ate); _hwa_write(o,ts,_ts); _hwa_cfadaref
#define _hwa_cfadatrg200(v,...)		HW_E(HW_EM_VAL(v,trigger,(manual, auto, (int0,irq), (acmp0,irq), \
								  (counter0,compare0,irq), (counter0,overflow,irq), \
								  (counter1,compare1,irq), (counter1,overflow,irq), \
								  (counter1,capture0,irq)))); HW_EAT // Pop
/*		IRQs
 */
#define _hwa_cfadatrg21(o,v,...)	_hwa_cfadatrg22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadatrg22(...)		_hwa_cfadatrg23(__VA_ARGS__)
#define _hwa_cfadatrg23(d,...)		HW_BW(_hwa_cfadatrg3,_irq,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadatrg30(d,o,v,...)	_hwa_cfadatrg200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadatrg31(d,o,v,...)	HW_BV(_hwa_cfadatrg20,adatrg_,HW_A1 d,)(o,v,__VA_ARGS__) // Push

#define _hw_adatrg_manual			, 0, 0	/* , ate, ts */
#define _hw_adatrg_auto				, 1, 0
#define _hw_adatrg_acmp0_irq			, 1, 1
#define _hw_adatrg_int0_irq			, 1, 2
#define _hw_adatrg_counter0_compare0_irq	, 1, 3
#define _hw_adatrg_counter0_overflow_irq	, 1, 4
#define _hw_adatrg_counter1_compare1_irq	, 1, 5
#define _hw_adatrg_counter1_overflow_irq	, 1, 6
#define _hw_adatrg_counter1_capture0_irq	, 1, 7

/*	Mandatory parameter 'vref'
 */
#define _hwa_cfadaref(o,v,k,...)	HW_BW(_hwa_cfadaref,vref,k)(o,k,__VA_ARGS__)
#define _hwa_cfadaref0(o,k,...)		HW_E(HW_EM_AN(k,vref))
#define _hwa_cfadaref1(o,k,v,...)	HW_B(_hwa_cfadaref2, _hw_par v)(o,v,__VA_ARGS__)

/*		"bandgap_1100mV"
 */
#define _hwa_cfadaref20(o,v,...)	HW_BV(_hwa_cfadaref20,adaref_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadaref201(v,o)		_hwa_write(o,refs,v); _hwa_cfadaal // Pop
#define _hwa_cfadaref200(v,...)		HW_E(HW_EM_VAL(v,vref,(vcc, (pin,aref), bandgap_1100mV))) HW_EAT // Pop

/*		vcc, (pin,aref)
 */
#define _hwa_cfadaref21(o,v,...)	_hwa_cfadaref22((HW_X(v)),o,v,__VA_ARGS__)
#define _hwa_cfadaref22(...)		_hwa_cfadaref23(__VA_ARGS__)
#define _hwa_cfadaref23(d,...)		HW_BW(_hwa_cfadaref3,_pin,HW_RP d)(d,__VA_ARGS__)
#define _hwa_cfadaref30(d,o,v,...)	_hwa_cfadaref200(v,)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadaref31(d,o,v,...)	HW_BV(_hwa_cfadaref20,adaref_,HW_A1 d,o)(o,v,__VA_ARGS__) // Push

#define _hw_adaref_vcc			, 0	/* , refs */
#define _hw_adaref_pin_aref		, 1
#define _hw_adaref_bandgap_1100mV	, 2

/*  Optionnal parameter 'align'
 */
#define _hwa_cfadaal(o,v,k,...)		HW_BW(_hwa_cfadaal,align,k)(o,k,__VA_ARGS__)
#define _hwa_cfadaal0			_hwa_cfadapo
#define _hwa_cfadaal1(o,k,v,...)	HW_BV(_hwa_cfadaal1,adaal_,v,o)(o,v,__VA_ARGS__) // Push
#define _hwa_cfadaal10(v,o)		HW_E(HW_EM_VOAL(v,align,(left,right))) HW_EAT // Pop
#define _hwa_cfadaal11(v,o)		_hwa_write(o,lar,v); _hwa_cfadaal12 // Pop
#define _hwa_cfadaal12(o,v,k,...)	_hwa_cfadapo(o,k,__VA_ARGS__)

#define _hw_adaal_left			, 1	/* , lar */
#define _hw_adaal_right			, 0

/*  Optionnal parameter `polarity`
 */
#define _hwa_cfadapo(o,k,...)		HW_BW(_hwa_cfadapo,polarity,k)(o,k,__VA_ARGS__)
#define _hwa_cfadapo0			_hwa_cfadagn
#define _hwa_cfadapo1(o,k,v,...)	HW_BV(_hwa_cfadapo1,adapo_,v,o)(o,v,__VA_ARGS__) // PUSH
#define _hwa_cfadapo10(v,o)		HW_E(HW_EM_VOAL(v,polarity,(unipolar,bipolar))) HW_EAT // POP
#define _hwa_cfadapo11(v,o)		_hwa_write(o,bin,v); _hwa_cfadagn  // POP

#define _hw_adapo_unipolar		, 0	/* , bin */
#define _hw_adapo_bipolar		, 1

/*  Optionnal parameter `gain`
 */
#define _hwa_cfadagn(o,k,...)		HW_BW(_hwa_cfadagn,gain,k)(o,k,__VA_ARGS__)
#define _hwa_cfadagn0			_hwa_cfadain // -> 'input'
#define _hwa_cfadagn1(o,k0,v,k,...)	gain = (uint8_t)(v); _hwa_cfadapi(o,k,__VA_ARGS__) // -> 'positive_input'

/*  Optionnal parameter `input`
 */
#define _hwa_cfadain(o,k,...)		HW_BW(_hwa_cfadain,input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadain0			_hwa_cfadapi
#define _hwa_cfadain1(o,k,v,...)	HW_BV(_hwa_cfadain1,adain_,v,o)(o,v,__VA_ARGS__) // PUSH
#define _hwa_cfadain10(v,o)		HW_E(HW_EM_VAL(v,input,((pin,ada0..3),temperature,bandgap,gnd))) HW_EAT // POP
#define _hwa_cfadain11(v,o)		_hwa_write(o,mux,v); _hwa_cfadain12 // Pop
#define _hwa_cfadain12(o,v,...)		if ( gain != 1 ) HWA_E(HW_EM_AVM(gain,1)); HW_EOL(__VA_ARGS__)

#define _hwa_cfadain1_(o,v,...)		_hwa_write(o,mux,_hw_adamuxse(HW_ADDRESS(v))); HW_EOL(__VA_ARGS__)

#define _hw_adain_gnd			, 0x20	/* , mux */
#define _hw_adain_bandgap		, 0x21
#define _hw_adain_temperature		, 0x22

/*  Compute the mux register value from input pin address
 */
HW_INLINE uint8_t _hw_adamuxse( uint32_t a )
{
  if ( a==HW_ADDRESS(pin_adc0) ) return 0;
  if ( a==HW_ADDRESS(pin_adc1) ) return 1;
  if ( a==HW_ADDRESS(pin_adc2) ) return 2;
  if ( a==HW_ADDRESS(pin_adc3) ) return 3;
  if ( a==HW_ADDRESS(pin_adc4) ) return 4;
  if ( a==HW_ADDRESS(pin_adc5) ) return 5;
  if ( a==HW_ADDRESS(pin_adc6) ) return 6;
  if ( a==HW_ADDRESS(pin_adc7) ) return 7;
  HWA_E(HW_EM_AVL(input,((pin,adc0..7),temperature,bandgap,gnd)));
  return 0 ;  
}

/*	Process 'positive_input' & 'negative_input' for differential mode
 */
#define _hwa_cfadapi(o,k,...)		HW_BW(_hwa_cfadapi,positive_input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadapi0(o,k,...)		HW_E(HW_EM_AN(k,positive_input))
#define _hwa_cfadapi1(o,k0,v,k,...)	\
  uint8_t pi __attribute__((unused)) = _hw_adain(HW_ADDRESS(v));	\
  HW_BW(_hwa_cfadani,negative_input,k)(o,k,__VA_ARGS__)
#define _hwa_cfadani0(o,k,...)		HW_E(HW_EM_AN(k,negative_input))
#define _hwa_cfadani1(o,k,v,...)	\
  uint8_t ni __attribute__((unused)) = _hw_adain(HW_ADDRESS(v));	\
  _hwa_write(o,mux,_hw_adamuxdi(pi,ni,gain)); HW_EOL(__VA_ARGS__)

/*  Compute the mux register value from inputs and gain
 */
HW_INLINE uint8_t _hw_adamuxdi ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( gain != 1 && gain != 20 ) {
    HWA_E(HW_EM_AVL(gain,(1, 20)));
    return 0;
  }

  if ( pos==0 ) {
    if ( neg==0 ) {
      if ( gain != 20 )
	HWA_E(HW_EM_AVM(gain,20));
      else
	return 0x23 ;
    }
    else if ( neg==1 )
      return 0x08 + (gain==20);
    else if ( neg==3 )
      return 0x0A + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc0), (pin,adc1), (pin,adc3))));
  }
  else if ( pos==1 ) {
    if ( neg==0 )
      return 0x28 + (gain==20);
    else if ( neg==2 )
      return 0x0C + (gain==20);
    else if ( neg==3 )
      return 0x0E + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc0), (pin,adc2), (pin,adc3))));
  }
  else if ( pos==2 ) {
    if ( neg==1 )
      return 0x2C + (gain==20);
    else if ( neg==3 )
      return 0x10 + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc1), (pin,adc3))));
  }
  else if ( pos==3 ) {
    const uint8_t v[8] = { 0x2A, 0x2E, 0x30, 0x24, 0x12, 0x14, 0x16, 0x18 };
    return v[neg] + (gain==20);
  }
  else if ( pos==4 ) {
    if ( neg==3 )
      return 0x32 + (gain==20);
    else if ( neg==5 )
      return 0x1A + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc3), (pin,adc5))));
  }
  else if ( pos==5 ) {
    if ( neg==3 )
      return 0x34 + (gain==20);
    else if ( neg==4 )
      return 0x3A + (gain==20);
    else if ( neg==6 )
      return 0x1C + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc3), (pin,adc4), (pin,adc6))));
  }
  else if ( pos==6 ) {
    if ( neg==3 )
      return 0x36 + (gain==20);
    else if ( neg==5 )
      return 0x3C + (gain==20);
    else if ( neg==7 )
      return 0x1E + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc3), (pin,adc5), (pin,adc7))));
  }
  else if ( pos==7 ) {
    if ( neg==3 )
      return 0x38 + (gain==20);
    else if ( neg==6 )
      return 0x3E + (gain==20);
    else if ( neg==7 )
      return 0x16 + (gain==20);
    HWA_E(HW_EM_AVL(negative_input,((pin,adc3), (pin,adc6), (pin,adc7))));
  }
  else
    HWA_E(HW_EM_AVL(positive_input,((pin,adc0..7))));
  return 0;
}


/*  Power management
 */
#define hw_power__ada			, _hw_power
#define hwa_power__ada			, _hwa_power


/**
 * @addtogroup atmelavr_ada
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
#define hw_enable__ada			, _hw_enable_adx_
#define hwa_enable__ada			, _hwa_enable_adx_


/**
 * @addtogroup atmelavr_ada
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
#define hw_disable__ada			, _hw_disable_adx_
#define hwa_disable__ada		, _hwa_disable_adx_


/**
 * @addtogroup atmelavr_ada
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
#define hw_trigger__ada			, _hw_trigger_adx_
#define hwa_trigger__ada		, _hwa_trigger_adx_


/**
 * @addtogroup atmelavr_ada
 *
 * <br><br> hw( read, ... ) returns the result of the conversion.
 *
 * @code
 * uint16_t adc = hw( read, adc0 );
 * @endcode
 */
#define hw_read__ada			, _hw_rdadx_

/**
 * @addtogroup atmelavr_ada
 *
 * <br><br> hw( read_atomic, ... ) returns the result of the conversion after having
 * cleared the I bit of the status register and set it again as soon as possible.
 *
 * @code
 * uint16_t adc = hw( read_atomic, adc0 );
 * @endcode
 */
#define hw_read_atomic__ada		, _hw_ardadx_


/**
 * @addtogroup atmelavr_ada
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
#define hw_stat__ada			, _hw_stat_adx_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ada(o,a)		_hwa_setup__adx_(o)
#define _hwa_init__ada(o,a)		_hwa_init__adx_(o)
#define _hwa_commit__ada(o,a)		_hwa_commit__adx_(o)


/**
 * @addtogroup atmelavr_ada
 * @section atmelavr_adaregs Registers
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
