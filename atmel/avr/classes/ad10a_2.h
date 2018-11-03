
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
#include "ad10__2.h"

#define _hw_mtd_hw_prescaler_max__ad10a		, hw_ad10_prescaler_max
#define _hw_mtd_hw_prescaler_min__ad10a		, hw_ad10_prescaler_min

/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_cf Configuration
 *
 * __Note__ The ADC is turned off by default. Configuring the ADC automatically
 * turns it on.
 *
 * @subsection atmelavr_ad10a_cf1 Single-end mode
 *
 * @code
 * hwa( configure, adc0,
 * 
 *      //  Clock source: the resulting clock frequency should be in
 *      //  the 50..200 kHz range for maximum resolution, and in all
 *      //  case lower than 1 MHz.
 *      //
 *      clock,     min                       // choose the nearest 50 kHz
 *               | max                       // choose the nearest 200 kHz
 *               | ioclk / 2**n,             // with n in 1..7
 *
 *      //  How a conversation is started
 *      //
 *      trigger,   manual                    // with the `trigger` action
 *               | auto                      // as soon as a conversion is completed
 *               | acmp0                     // ANA_COMP interrupt request
 *               | int0                      // INT0 interrupt request
 *               | counter0_compare0         // TIMER0_COMPA interrupt request
 *               | counter0_overflow         // TIMER0_OVF interrupt request
 *               | counter1_compare1         // TIMER1_COMPB interrupt request
 *               | counter1_overflow         // TIMER1_OVF interrupt request
 *               | counter1_capture,         // TIMER1_CAPT interrupt request
 *
 *      //  Voltage reference
 *      //
 *      vref,      vcc                       // Vcc
 *               | pin_aref                  // Voltage on AREF pin
 *               | bandgap,                  // Internal 1.1V bandgap
 * 
 *      //  Result alignment (default is `right`)
 *      //
 *    [ align,     left
 *               | right, ]
 *
 *      //  Input
 *      //
 *      input,     HW_PIN(adc0..7)
 *               | agnd
 *               | bandgap
 *               | temperature );
 * @endcode
 *
 * @subsection atmelavr_ad10a_cf2 Differential mode
 *
 * The differential mode allows the use of the 20x gain stage.
 *
 * @code
 * hwa( configure, adc0,
 * 
 *	clock, ... ,				// See above
 *	trigger, ... ,
 *	vref, ... ,
 *    [ align, ... , ]
 *
 *	//  Type of conversion (default is `unipolar`)
 *	//
 *    [ polarity,	  unipolar
 *			| bipolar, ]
 *
 *	//  Amplification (default is 1)
 *	//
 *    [ gain,		  1
 *			| 20, ]
 *
 *	//  HWA will trigger an error if you try to use a combination
 *	//  of inputs that is not available
 *	//
 *	positive_input,	  HW_PIN(adc0..7),
 * 
 *	negative_input,	  HW_PIN(adc0..7) );
 * @endcode
 */

/* FIXME
 *
 * Use HW_IRQ(...) or irq() for trigger?
 */

#define _hw_mtd_hwa_configure__ad10a	, _hwa_cfad10a

/*  Mandatory parameter `clock`
 */
#define _hwa_cfad10a(o,i,a,k,...)					\
  do {									\
    uint8_t gain __attribute__((unused)) = 1 ;				\
    uint8_t input1 __attribute__((unused)) = 0xFF ;			\
    uint8_t input2 __attribute__((unused)) = 0xFF ;			\
    _hwa_write_or( o, en, 1 ); /* turn the ADC on */			\
    HW_Y(_hwa_cfad10a_kclock,_hw_is_clock_##k)(o,k,__VA_ARGS__,,);	\
  } while(0)

#define _hwa_cfad10a_kclock_0(o,k,...)					\
  HW_E_VL(k,clock)

#define _hwa_cfad10a_kclock_1(o,k,v,...)				\
  HW_Y(_hwa_cfad10a_vclock,_hw_ad10_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, (min, max, ioclk / 2**n with n in 1..7))

#define _hwa_cfad10a_vclock_1(o,v,k,...)				\
  _hwa_write_or(o, ps, HW_A1(_hw_ad10_clock_##v)(HW_A2(_hw_ad10_clock_##v))); \
  HW_Y(_hwa_cfad10a_ktrigger,_hw_is_trigger_##k)(o,k,__VA_ARGS__)


/*  Mandatory parameter `trigger`
 */
#define _hwa_cfad10a_ktrigger_0(o,k,...)		\
  HW_E_VL(k,trigger)

#define _hwa_cfad10a_ktrigger_1(o,k,v,...)				\
  HW_Y(_hwa_cfad10a_vtrigger,_hw_ad10a_trigger_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vtrigger_0(o,v,...)				\
  HW_E_AVL(trigger, v, manual | auto | acmp0 | int0 | counter0_compare0 | counter0_overflow | counter1_compare1 | counter1_overflow | counter1_capture0)

#define _hwa_cfad10a_vtrigger_1(o,v,k,...)			\
  _hwa_write_or(o,ate, HW_A1(_hw_ad10a_trigger_##v));		\
  _hwa_write_or(o,ts, HW_A2(_hw_ad10a_trigger_##v));		\
  HW_Y(_hwa_cfad10a_kvref,_hw_is_vref_##k)(o,k,__VA_ARGS__)

#define _hw_ad10a_trigger_manual	, 0, 0	/* , ate, ts */
#define _hw_ad10a_trigger_auto		, 1, 0
#define _hw_ad10a_trigger_acmp0		, 1, 1
#define _hw_ad10a_trigger_int0		, 1, 2
#define _hw_ad10a_trigger_counter0_compare0	, 1, 3
#define _hw_ad10a_trigger_counter0_overflow	, 1, 4
#define _hw_ad10a_trigger_counter1_compare1	, 1, 5
#define _hw_ad10a_trigger_counter1_overflow	, 1, 6
#define _hw_ad10a_trigger_counter1_capture0	, 1, 7

/*  Mandatory parameter `vref`
 */
#define _hwa_cfad10a_kvref_0(o,k,...)					\
  HW_E_VL(k,vref)

#define _hwa_cfad10a_kvref_1(o,k,v,...)					\
  HW_Y(_hwa_cfad10a_vvref,_hw_ad10a_vref_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vvref_0(o,v,...)				\
  HW_E_AVL(vref, v, vcc | pin_aref | bandgap)

#define _hwa_cfad10a_vvref_1(o,v,k,...)			\
  _hwa_write_or(o,refs, HW_A1(_hw_ad10a_vref_##v));	\
  HW_Y(_hwa_cfad10a_kalign,_hw_is_align_##k)(o,k,__VA_ARGS__)

#define _hw_ad10a_vref_vcc		, 0	/* , refs */
#define _hw_ad10a_vref_pin_aref		, 1
#define _hw_ad10a_vref_bandgap		, 2

/*  Optionnal parameter `align`
 */
#define _hwa_cfad10a_kalign_1(o,k,v,...)				\
  HW_Y(_hwa_cfad10a_valign,_hw_ad10a_align_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_valign_0(o,v,...)				\
  HW_E_OAVL(align, v, left | right)
#define _hwa_cfad10a_valign_1(o,v,k,...)				\
  _hwa_write_or(o,lar, HW_A1(_hw_ad10a_align_##v));			\
  HW_Y(_hwa_cfad10a_kpolarity,_hw_is_polarity_##k)(o,k,__VA_ARGS__)

#define _hwa_cfad10a_kalign_0(o,k,...)					\
  HW_Y(_hwa_cfad10a_kpolarity,_hw_is_polarity_##k)(o,k,__VA_ARGS__)

#define _hw_ad10a_align_left		, 1	/* , lar */
#define _hw_ad10a_align_right		, 0

/*  Optionnal parameter `polarity`
 */
#define _hwa_cfad10a_kpolarity_1(o,k,v,...)				\
  HW_Y(_hwa_cfad10a_vpolarity,_hw_ad10a_polarity_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vpolarity_0(o,v,...)				\
  HW_E_OAVL(polarity, v, unipolar | bipolar)

#define _hwa_cfad10a_vpolarity_1(o,v,k,...)			\
  _hwa_write_or(o,bin, HW_A1(_hw_ad10a_polarity_##vpolarity));	\
  HW_Y(_hwa_cfad10a_kgain,_hw_is_gain_##k)(o,k,__VA_ARGS__)

#define _hwa_cfad10a_kpolarity_0(o,k,...)			\
  HW_Y(_hwa_cfad10a_kgain,_hw_is_gain_##k)(o,k,__VA_ARGS__)

#define _hw_ad10a_polarity_unipolar	, 0	/* , bin */
#define _hw_ad10a_polarity_bipolar	, 1

/*  Optionnal parameter `gain`
 */
#define _hwa_cfad10a_kgain_1(o,k,v,...)					\
  gain = (uint8_t)(v) ;							\
  if ( gain != 1 && gain != 20 )					\
    HWA_ERR("optionnal parameter `gain` must be 1 or 20.");		\
  HW_G2(_hwa_cfad10a_kpositive_input,HW_IS(positive_input,__VA_ARGS__))(o,__VA_ARGS__)

#define _hwa_cfad10a_kgain_0(o,k,...)				\
  HW_Y(_hwa_cfad10a_kinput,_hw_is_input_##k)(o,k,__VA_ARGS__)

/*  Optionnal parameter `input` -> single-end mode, end of list
 */
#define _hwa_cfad10a_kinput_1(o,k,v,...)				\
  if ( HW_IS(,HW_A0(_hw_ad10a_input_##v)) )				\
    _hwa_write_or(o,mux, HW_A1(_hw_ad10a_input_##v,0));		\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc0) ) )		\
    _hwa_write_or(o,mux, 0);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc1) ) )		\
    _hwa_write_or(o,mux, 1);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc2) ) )		\
    _hwa_write_or(o,mux, 2);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc3) ) )		\
    _hwa_write_or(o,mux, 3);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc4) ) )		\
    _hwa_write_or(o,mux, 4);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc5) ) )		\
    _hwa_write_or(o,mux, 5);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc6) ) )		\
    _hwa_write_or(o,mux, 6);						\
  else if ( HW_ID(v)!=0 && HW_ID(v)==HW_ID( HW_PIN(adc7) ) )		\
    _hwa_write_or(o,mux, 7);						\
  else									\
    HWA_ERR("`input` can be `HW_PIN(adc0..7)` (or synonyms), "		\
	    "`temperature`, `bandgap`, or `ground`  but not `"#v"`.");	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfad10a_kinput_0(o,k,...)					\
  HW_G2(_hwa_cfad10a_kpositive_input,HW_IS(positive_input,k))(o,k,__VA_ARGS__)

#define _hw_ad10a_input_bandgap		, 0x21	/* , mux */
#define _hw_ad10a_input_ground		, 0x20
#define _hw_ad10a_input_temperature	, 0x22


/*  'positive_input' & 'negative_input' for differential mode
 */
#define _hwa_cfad10a_kpositive_input_0(o,k,...)				\
  HW_E_VL(k,input | positive_input)

#define _hwa_cfad10a_kpositive_input_1(o,k,v,...)			\
  HW_Y(_hwa_cfad10a_vpositive_input,_hw_ad10a_input_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vpositive_input_0(o,v,...)				\
  HW_E_AVL(`positive_input`, v, 'HW_PIN(adc0..7)' or synonyms)
#define _hwa_cfad10a_vpositive_input_1(o,v,k,...)			\
  uint8_t positive_input = HW_A1(_hw_ad10a_input_##v);		\
  HW_G2(_hwa_cfad10a_knegative_input,HW_IS(negative_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfad10a_knegative_input_0(o,k,...)				\
  HW_E_VL(k,negative_input)

#define _hwa_cfad10a_knegative_input_1(o,k,v,...)			\
  HW_Y(_hwa_cfad10a_vnegative_input,_hw_ad10a_input_##v)(o,v,__VA_ARGS__)

#define _hwa_cfad10a_vnegative_input_0(o,v,...)		\
  HW_E_AVL(`negative_input`, v, 'HW_PIN(adc0..7)' or synonyms)

#define _hwa_cfad10a_vnegative_input_1(o,v,...)				\
  uint8_t negative_input = HW_A1(_hw_ad10a_input_##v);			\
  _hwa_write_or(o,mux,_hwa_ad10a_compute_mux( positive_input, negative_input, gain )); \
  HW_EOL(__VA_ARGS__)


/*	Check the combination of differential inputs & gain, return the MUX
 *	value.
 */
HW_INLINE uint8_t _hwa_ad10a_compute_mux ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( pos==0 ) {
    if ( neg==0 ) {
      if ( gain != 20 )
	HWA_ERR("parameter `gain` must be 20 when pin_adc0 is used for both inputs.");
      else
	return 0x23 ;
    }
    else if ( neg==1 )
      return 0x08 + (gain==20);
    else if ( neg==3 )
      return 0x0A + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0`, `pin_adc1`, or `pin_adc3`.");
  }
  else if ( pos==1 ) {
    if ( neg==0 )
      return 0x28 + (gain==20);
    else if ( neg==2 )
      return 0x0C + (gain==20);
    else if ( neg==3 )
      return 0x0E + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0`, `pin_adc2`, or `pin_adc3`.");
  }
  else if ( pos==2 ) {
    if ( neg==1 )
      return 0x2C + (gain==20);
    else if ( neg==3 )
      return 0x10 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc1` or `pin_adc3`.");
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
    HWA_ERR("`negative_input` must be `pin_adc3` or `pin_adc5`.");
  }
  else if ( pos==5 ) {
    if ( neg==3 )
      return 0x34 + (gain==20);
    else if ( neg==4 )
      return 0x3A + (gain==20);
    else if ( neg==6 )
      return 0x1C + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc4`, or `pin_adc6`.");
  }
  else if ( pos==6 ) {
    if ( neg==3 )
      return 0x36 + (gain==20);
    else if ( neg==5 )
      return 0x3C + (gain==20);
    else if ( neg==7 )
      return 0x1E + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc5`, or `pin_adc7`.");
  }
  else if ( pos==7 ) {
    if ( neg==3 )
      return 0x38 + (gain==20);
    else if ( neg==6 )
      return 0x3E + (gain==20);
    else if ( neg==7 )
      return 0x16 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc6`, or `pin_adc7`.");
  }
  else
    HWA_ERR("`positive_input` must be between 0 and 7.");
  return 0;
}


/*  Power management
 */
#define _hw_mtd_hw_power__ad10a		, _hw_power
#define _hw_mtd_hwa_power__ad10a	, _hwa_power


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_turn Turning on / off
 *
 * The ADC must be turned off for the analog comparator to have access to the
 * analog multiplexer.
 *
 * __Note__ This is not related to power management. Assuming the target device
 * supports it, use the `power` instruction if you want power the ADC on/off.
 *
 * @code
 * hw( turn, adc0, on | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__ad10a		, _hw_turn_ad10_

/**
 * @page atmelavr_ad10a
 * @code
 * hwa( turn, adc0, on | off );
 * @endcode
 */
#define _hw_mtd_hwa_turn__ad10a	, _hwa_turn_ad10_


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_trigger Starting a conversion
 *
 * @code
 * hw( trigger, adc0 );
 * @endcode
 */
#define _hw_mtd_hw_trigger__ad10a	, _hw_trigger_ad10_

/**
 * @page atmelavr_ad10a
 *
 * @code
 * hwa( trigger, adc0 );
 * @endcode
 */
#define _hw_mtd_hwa_trigger__ad10a	, _hwa_trigger_ad10_


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_read Result of the conversion
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
#define _hw_mtd_hw_read__ad10a		, _hw_rdad10_


/**
 * @page atmelavr_ad10a
 *
 * Read the ADC result with interrupts disabled and restore state as soon as
 * possible:
 *
 * @code
 * uint16_t adc = hw_atomic_read( adc0 );
 * @endcode
 */
#define _hw_mtd_hw_atomic_read__ad10a	, _hw_ardad10_


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_stat Status
 *
 * You'll usually use the IRQ flag to test whether a conversion is completed:
 *
 * @code
 * hw( trigger, adc0 );
 * while ( !hw( read, HW_IRQFLAG(adc0) ) ) {}
 * hw( clear, HW_IRQFLAG(adc0) );
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
 *   hw_trigger( adc0 );
 * @endcode
 */
#define _hw_mtd_hw_stat__ad10a		, _hw_stat_ad10_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ad10a(o,i,a)	_hwa_setup__ad10_(o)
#define _hwa_init__ad10a(o,i,a)		_hwa_init__ad10_(o)
#define _hwa_commit__ad10a(o,i,a)	_hwa_commit__ad10_(o)


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_internals Internals
 *
 * Class `_ad10a` objects hold the following hardware registers:
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
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/**
 * @page atmelavr_ad10a
 * <br>
 */
