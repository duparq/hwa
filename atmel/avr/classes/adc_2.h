
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _adc: 10-bit analog to digital converter
 */

/*	Base class
 */
#include "adx_2.h"

#define hw_prescaler_max__adc		, hw_adx_prescaler_max
#define hw_prescaler_min__adc		, hw_adx_prescaler_min

/**
 * @page atmelavr_adc
 * @section atmelavr_adc_act Actions
 *
 * <br>
 * `configure`:
 *
 * __Note__ The ADC is turned off by default. Configuring the ADC automatically
 * turns it on.
 *
 * @subsection atmelavr_adc_cf1 Single-end mode
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
 *		 | counter0_compare1		// TIMER0_COMPV interrupt request
 *		 | pcic0,			// PCINT0 interrupt request
 *						
 *	//  Voltage reference			
 *	//					
 *	vref,	   vcc				// Vcc
 *		 | pin_aref			// Voltage on AREF pin
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
 *	input,	   HW_PIN(adc0..3)
 *		 | gnd
 *		 | bandgap
 *		 | temperature );
 * @endcode
 *
 * @subsection atmelavr_adc_cf2 Differential mode
 *
 * The differential mode allows the use of the 20x gain stage.
 *
 * @code
 * hwa( configure, ADC,
 * 
 *	       clock, ... ,			// See above
 *	       trigger, ... ,
 *	       vref, ... ,
 *	     [ align, ... , ]
 * 
 *	       //  Type of conversion (default is `unipolar`)
 *	       //
 *	     [ polarity,	 unipolar
 *			       | bipolar, ]
 *
 *	       //  Amplification (default is 1)
 *	       //
 *	     [ gain,		 1
 *			       | 20, ]
 * 
 *	       //  HWA will trigger an error if you try to use a combination
 *	       //  of inputs that is not available
 *	       //
 *	       positive_input,	 HW_PIN(adc0..3)
 * 
 *	       negative_input,	 HW_PIN(adc0..3)
 *	     );
 * @endcode
 */
#define hwa_configure__adc		, _hwa_cfadc

/*  Mandatory parameter `clock`
 */
#define _hwa_cfadc(o,a,k,...)					\
  do {									\
    uint8_t gain __attribute__((unused)) = 1 ;				\
    _hwa_write( o, en, 1 ); /* turn the ADC on */			\
    HW_Y(_hwa_cfadc_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,);	\
  } while(0)

#define _hwa_cfadc_kclock_0(o,k,...)					\
  HW_E_VL(k,clock)
#define _hwa_cfadc_kclock_1(o,k,v,...)				\
  HW_Y(_hwa_cfadc_vclock_,_hw_adx_clock_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, (min, max, ioclk / 2**n with n in 1..7))
#define _hwa_cfadc_vclock_1(o,v,k,...)				\
  _hwa_write(o, ps, HW_A1(_hw_adx_clock_##v)(HW_A2(_hw_adx_clock_##v))); \
  HW_Y(_hwa_cfadc_ktrigger_,_hw_is_trigger_##k)(o,k,__VA_ARGS__)


/*  Mandatory parameter `trigger`
 */
#define _hwa_cfadc_ktrigger_0(o,k,...)		\
  HW_E_VL(k,trigger)
#define _hwa_cfadc_ktrigger_1(o,k,v,...)				\
  HW_Y(_hwa_cfadc_vtrigger_,_hw_adc_trigger_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vtrigger_0(o,v,...)				\
  HW_E_AVL(trigger, v, manual | auto | acmp0 | int0 | counter0_compare0 | counter0_overflow | counter0_compare1 | pcic0)
#define _hwa_cfadc_vtrigger_1(o,v,k,...)				\
  _hwa_write(o,ate, HW_A1(_hw_adc_trigger_##v));		\
  _hwa_write(o,ts, HW_A2(_hw_adc_trigger_##v));		\
  HW_Y(_hwa_cfadc_kvref_,_hw_is_vref_##k)(o,k,__VA_ARGS__)

#define _hw_adc_trigger_manual	, 0, 0	/* , ate, ts */
#define _hw_adc_trigger_auto		, 1, 0
#define _hw_adc_trigger_acmp0		, 1, 1
#define _hw_adc_trigger_int0		, 1, 2
#define _hw_adc_trigger_counter0_compare0	, 1, 3
#define _hw_adc_trigger_counter0_overflow	, 1, 4
#define _hw_adc_trigger_counter0_compare1	, 1, 5
#define _hw_adc_trigger_pcic0		, 1, 6

/*  Mandatory parameter `vref`
 */
#define _hwa_cfadc_kvref_0(o,k,...)					\
  HW_E_VL(k,vref)
#define _hwa_cfadc_kvref_1(o,k,v,...)					\
  HW_Y(_hwa_cfadc_vvref_,_hw_adc_vref_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vvref_0(o,v,...)				\
  HW_E_AVL(vref, v, vcc | pin_aref | bandgap_1100mV | handgap_2560mV | handgap_2560mV_aref)
#define _hwa_cfadc_vvref_1(o,v,k,...)			\
  _hwa_write(o,refs, HW_A1(_hw_adc_vref_##v));	\
  HW_Y(_hwa_cfadc_kalign_,_hw_is_align_##k)(o,k,__VA_ARGS__)

#define _hw_adc_vref_vcc		, 0	/* , refs */
#define _hw_adc_vref_pin_aref		, 1
#define _hw_adc_vref_bandgap_1100mV		, 2
#define _hw_adc_vref_bandgap_2560mV		, 6
#define _hw_adc_vref_bandgap_2560mV_aref	, 7

/*  Optionnal parameter `align`
 */
#define _hwa_cfadc_kalign_1(o,k,v,...)				\
  HW_Y(_hwa_cfadc_valign_,_hw_adc_align_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_valign_0(o,v,...)				\
  HW_E_OAVL(align, v, left | right)
#define _hwa_cfadc_valign_1(o,v,k,...)				\
  _hwa_write(o,lar, HW_A1(_hw_adc_align_##v));			\
  HW_Y(_hwa_cfadc_kpolarity_,_hw_is_polarity_##k)(o,k,__VA_ARGS__)
#define _hwa_cfadc_kalign_0(o,k,...)					\
  HW_Y(_hwa_cfadc_kpolarity_,_hw_is_polarity_##k)(o,k,__VA_ARGS__)

#define _hw_adc_align_left		, 1	/* , lar */
#define _hw_adc_align_right		, 0

/*  Optionnal parameter `polarity`
 */
#define _hwa_cfadc_kpolarity_1(o,k,v,...)				\
  HW_Y(_hwa_cfadc_vpolarity_,_hw_adc_polarity_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vpolarity_0(o,v,...)				\
    HW_E_OAVL(polarity, v, unipolar | bipolar)
#define _hwa_cfadc_vpolarity_1(o,v,k,...)				\
    _hwa_write(o,bin, HW_A1(_hw_adc_polarity_##vpolarity));	\
    HW_Y(_hwa_cfadc_kgain_,_hw_is_gain_##k)(o,k,__VA_ARGS__)
#define _hwa_cfadc_kpolarity_0(o,k,...)			\
  HW_Y(_hwa_cfadc_kgain_,_hw_is_gain_##k)(o,k,__VA_ARGS__)

#define _hw_adc_polarity_unipolar	, 0	/* , bin */
#define _hw_adc_polarity_bipolar	, 1

/*  Optionnal parameter `gain`
 */
#define _hwa_cfadc_kgain_1(o,k,v,...)					\
  gain = (uint8_t)(v) ;							\
  if ( gain != 1 && gain != 20 )					\
    HWA_ERR("optionnal parameter `gain` must be 1 or 20.");		\
  HW_G2(_hwa_cfadc_kpositive_input,HW_IS(positive_input,__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfadc_kgain_0(o,k,...)				\
  HW_Y(_hwa_cfadc_kinput_,_hw_is_input_##k)(o,k,__VA_ARGS__)


/*  Optionnal parameter `input`
 */
#define _hwa_cfadc_kinput_1(o,k,v,...)				\
  if ( HW_IS(,HW_A0(_hw_adc_input_##v)) )				\
    _hwa_write(o,mux, HW_A1(_hw_adc_input_##v,0));			\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( HW_PIN(adc0) ) ) \
    _hwa_write(o,mux, 0);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( HW_PIN(adc1) ) ) \
    _hwa_write(o,mux, 1);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( HW_PIN(adc2) ) ) \
    _hwa_write(o,mux, 2);						\
  else if ( HW_ADDRESS(v)==HW_ADDRESS( HW_PIN(adc3) ) ) \
    _hwa_write(o,mux, 3);						\
  else									\
    HWA_ERR("`input` can be 'HW_PIN(adc0..3)' (or synonyms), "		\
	    "`temperature`, `bandgap`, or `ground`  but not `"#v"`.");	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfadc_kinput(o,k,...)					\
  HW_Y(_hwa_cfadc_kinput_,_hw_is_input_##k)(o,k,__VA_ARGS__)

#define _hw_adc_input_bandgap		, 12	/* , mux */
#define _hw_adc_input_ground		, 13
#define _hw_adc_input_temperature	, 15


/*	Process 'positive_input' & 'negative_input' in differential mode
 */
#define _hwa_cfadc_kpositive_input_0(o,k,...)	\
  HW_E_VL(k,input | positive_input)
#define _hwa_cfadc_kpositive_input_1(o,k,v,...)			\
  HW_Y(_hwa_cfadc_vpositive_input_,_hw_adc_input_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vpositive_input_0(o,v,...)			\
  HW_E_AVL(`positive_input`, v, 'HW_PIN(adc0..3)' or synonyms)
#define _hwa_cfadc_vpositive_input_1(o,v,k,...)			\
  uint8_t positive_input = HW_A1(_hw_adc_input_##v);			\
  HW_G2(_hwa_cfadc_knegative_input,HW_IS(negative_input,k))(o,k,__VA_ARGS__)
#define _hwa_cfadc_knegative_input_0(o,k,...)	\
  HW_E_VL(k,negative_input)
#define _hwa_cfadc_knegative_input_1(o,k,v,...)			\
  HW_Y(_hwa_cfadc_vnegative_input_,_hw_adc_input_##v)(o,v,__VA_ARGS__)
#define _hwa_cfadc_vnegative_input_0(o,v,...)			\
  HW_E_AVL(`negative_input`, v, 'HW_PIN(adc0..3)' or synonyms)
#define _hwa_cfadc_vnegative_input_1(o,v,...)				\
  uint8_t negative_input = HW_A1(_hw_adc_input_##v);			\
  _hwa_write(o,mux,_hwa_adc_compute_mux(positive_input,negative_input,gain)); \
  HW_EOL(__VA_ARGS__)


/*	Check the combination of differential inputs & gain,
 *	return a combination of `ipr` and `mux` values.
 */
HW_INLINE uint8_t _hwa_adc_compute_mux ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( pos==0 ) {
    if ( neg==0 )
      return 0x08 + (gain==20);
    else if ( neg==1 )
      return 0x0A + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0` or `pin_adc1` or synonyms.");
  }
  else if ( pos==1 ) {
    if ( neg==0 )
      return 0x1A + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0` or synonym.");
  }
  else if ( pos==2 ) {
    if ( neg==2 )
      return 0x04 + (gain==20);
    else if ( neg==3 )
      return 0x06 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc2` or `pin_adc3` or synonyms.");
  }
  else if ( pos==3 ) {
    if ( neg==2 )
      return 0x16 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc2` or synonym.");
  }
  HWA_ERR("parsing error.");
  return 0;
}


/**
 * @page atmelavr_adc
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
#define hw_turn__adc			, _hw_turn_adx_

/**
 * @page atmelavr_adc
 * @code
 * hwa( turn, adc0, on | off );
 * @endcode
 */
#define hwa_turn__adc			, _hwa_turn_adx_


/**
 * @page atmelavr_adc
 *
 * <br>
 * `trigger`:
 *
 * @code
 * hw( trigger, adc0 );
 * @endcode
 */
#define hw_trigger__adc		, _hw_trigger_adx_

/**
 * @page atmelavr_adc
 * @code
 * hwa( trigger, adc0 );
 * @endcode
 */
#define hwa_trigger__adc		, _hwa_trigger_adx_


/**
 * @page atmelavr_adc
 *
 * <br>
 * `read`:
 *
 * @code
 * uint16_t adc = hw( read, adc0 );
 * @endcode
 *
 * Optionnally, read a single byte:
 * @code
 * uint8_t adc = hw( read, adc0, lo8 | hi8 );
 * @endcode
 */
#define hw_read__adc			, _hw_rdad10_


/**
 * @page atmelavr_adc
 *
 * <br>
 * `read_atomic`: read the ADC result with interrupts disabled and restore state as soon as
 * possible:
 *
 * @code
 * uint16_t adc = hw_atomic_read( adc0 );
 * @endcode
 */
#define hw_atomic_read__adc		, _hw_ardad10_


/**
 * @page atmelavr_adc
 * @section atmelavr_adc_stat Status
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
#define hw_stat__adc			, _hw_stat_adx_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__adc(o,a)		_hwa_setup__adx_(o)
#define _hwa_init__adc(o,a)			_hwa_init__adx_(o)
#define _hwa_commit__adc(o,a)		_hwa_commit__adx_(o)


/**
 * @page atmelavr_adc
 * @section atmelavr_adc_internals Internals
 *
 * Class `_adc` objects hold the following hardware registers:
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
