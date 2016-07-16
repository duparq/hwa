
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
#include "ad10__2.h"

/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_config1 Configuration
 *
 * @note The ADC is turned off by default. Configuring the ADC automatically
 * turns it on.
 *
 * @code
 * hwa_config( ADC_NAME,
 * 
 *             //  Clock source: the resulting clock frequency should be in
 *             //  the 50..200 kHz range for maximum resolution, and in all
 *             //  case lower than 1 MHz.
 *             //
 *             clock,     min                        // choose the nearest 50 kHz
 *                      | max                        // choose the nearest 200 kHz
 *                      | sysclk_div(    2
 *                                   |   4
 *                                   |   8
 *                                   |  16
 *                                   |  32
 *                                   |  64
 *                                   | 128 ),
 *
 *             //  How a conversation is started
 *             //
 *             trigger,   manual                     // with the `hw_trigger()` instruction
 *                      | auto                       // as soon as a consersion is completed
 *                      | hw_acmp0                   // ANA_COMP interrupt request
 *                      | hw_int0                    // INT0 interrupt request
 *                      | hw_counter0_compare0       // TIMER0_COMPA interrupt request
 *                      | hw_counter0_overflow       // TIMER0_OVF interrupt request
 *                      | hw_counter1_compare1       // TIMER1_COMPB interrupt request
 *                      | hw_counter1_overflow       // TIMER1_OVF interrupt request
 *                      | hw_counter1_capture,       // TIMER1_CAPT interrupt request
 *
 *             //  Voltage reference
 *             //
 *             vref,      vcc                        // Vcc
 *                      | hw_pin_avcc                // Voltage on AVCC pin
 *                      | hw_pin_aref                // Voltage on AREF pin
 *                      | bandgap,                   // Internal 1.1V bandgap
 * 
 *             //  Result alignment (default is `right`)
 *             //
 *           [ align,     left
 *                      | right, ]
 *
 *             //  Input
 *             //
 *             input,     hw_pin_adc0 .. hw_pin_adc7
 *                      | agnd
 *                      | bandgap
 *                      | temperature
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__ad10b		, _hwa_cfad10b

/*	Mandatory parameter 'clock'
 */
#define _hwa_cfad10b(o,i,a,...)						\
  do {									\
    _hwa_write_reg( o, en, 1 ); /* turn the ADC on */			\
    HW_G2(_hwa_cfad10b_kclock, HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__,,); \
  } while(0)

#define _hwa_cfad10b_kclock_0(o,k,...)			\
  HW_ERR("expected `clock` instead of `" #k "`.")
#define _hwa_cfad10b_kclock_1(o,k,v,...)				\
  HW_G2(_hwa_cfad10b_vclock, HW_IS(,_hw_ad10b_clock_##v))(o,v,__VA_ARGS__)
#define _hwa_cfad10b_vclock_0(o,v,...)					\
  HW_ERR("`clock` can be `min`, `max`, or `sysclk_div( 1 | 2 | 4 | 8 | 16 " \
	 "| 32 | 64 | 128 )`, but not `"#v".")
#define _hwa_cfad10b_vclock_1(o,v,k,...)				\
  if ( HW_A1(_hw_ad10b_clock_##v) == HW_A1(_hw_ad10b_clock_min) ) {	\
    if ( hw_syshz / 128 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_128));	\
    else if ( hw_syshz / 64 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_64));	\
    else if ( hw_syshz / 32 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_32));	\
    else if ( hw_syshz / 16 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_16));	\
    else if ( hw_syshz / 8 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_8));	\
    else if ( hw_syshz / 4 >= 50000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_4));	\
    else								\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_2));	\
  }									\
  else if ( HW_A1(_hw_ad10b_clock_##v) == HW_A1(_hw_ad10b_clock_max) ) { \
    if ( hw_syshz / 2 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_2));	\
    else if ( hw_syshz / 4 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_4));	\
    else if ( hw_syshz / 8 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_8));	\
    else if ( hw_syshz / 16 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_16));	\
    else if ( hw_syshz / 32 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_32));	\
    else if ( hw_syshz / 64 <= 200000 )					\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_64));	\
    else								\
      _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_sysclk_div_128));	\
  }									\
  else									\
    _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_##v));			\
  HW_G2(_hwa_cfad10b_ktrigger, HW_IS(trigger,k))(o,k,__VA_ARGS__)

#define _hw_is_clock_clock			, 1
#define _hw_ad10b_clock_sysclk_div_2		, 0	/* , ps */
#define _hw_ad10b_clock_sysclk_div_4		, 2
#define _hw_ad10b_clock_sysclk_div_8		, 3
#define _hw_ad10b_clock_sysclk_div_16		, 4
#define _hw_ad10b_clock_sysclk_div_32		, 5
#define _hw_ad10b_clock_sysclk_div_64		, 6
#define _hw_ad10b_clock_sysclk_div_128		, 7
#define _hw_ad10b_clock_min			, 8
#define _hw_ad10b_clock_max			, 9
#define _hw_ad10b_clock_sysclk_div(x)		HW_G2(_hw_ad10b_clock_sysclk_div,x)

/*	Mandatory parameter 'trigger'
 */
#define _hwa_cfad10b_ktrigger_0(o,k,...)		\
  HW_ERR("expected `trigger` instead of `" #k "`.")
#define _hwa_cfad10b_ktrigger_1(o,k,...)				\
  HW_G2(_hwa_cfad10b_vtrigger, HW_IS(,_hw_ad10b_trigger_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_vtrigger_0(o,v,...)				\
  HW_ERR("`trigger` can be `manual`, `auto`, `int0`, `hw_acmp0`, "	\
	 "`hw_counter0_compare0`, `hw_counter0_overflow`, `hw_counter1_compare1`, " \
	 "`hw_counter1_overflow`, `hw_counter1_capture0`, but not `" #v "`.")
#define _hwa_cfad10b_vtrigger_1(o,v,...)				\
  _hwa_write_reg(o,ate, HW_A1(_hw_ad10b_trigger_##v));			\
  _hwa_write_reg(o,ts, HW_A2(_hw_ad10b_trigger_##v));			\
  HW_G2(_hwa_cfad10b_kvref, HW_IS(vref,__VA_ARGS__))(o,__VA_ARGS__)

#define _hw_is_trigger_trigger			, 1
#define _hw_ad10b_trigger_manual		, 0, 0	/* , ate, ts */
#define _hw_ad10b_trigger_auto			, 1, 0
#define _hw_ad10b_trigger_hw_acmp0		, 1, 1
#define _hw_ad10b_trigger_int0			, 1, 2
#define _hw_ad10b_trigger_hw_counter0_compare0	, 1, 3
#define _hw_ad10b_trigger_hw_counter0_overflow	, 1, 4
#define _hw_ad10b_trigger_hw_counter1_compare1	, 1, 5
#define _hw_ad10b_trigger_hw_counter1_overflow	, 1, 6
#define _hw_ad10b_trigger_hw_counter1_capture0	, 1, 7

/*	Mandatory parameter 'vref'
 */
#define _hwa_cfad10b_kvref_0(o,...)					\
  HW_ERR("expected `vref` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10b_kvref_1(o,k,...)					\
  HW_G2(_hwa_cfad10b_vvref, HW_IS(,_hw_ad10b_vref_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_vvref_0(o,v,...)					\
  HW_ERR("`vref` can be `vcc`, `hw_pin_avcc`, `hw_pin_aref`, or `bandgap` but not `" #v "`.")
#define _hwa_cfad10b_vvref_1(o,v,...)			\
  _hwa_write_reg(o,refs, HW_A1(_hw_ad10b_vref_##v));	\
  _hwa_cfad10b_align(o,__VA_ARGS__)

#define _hw_is_vref_vref			, 1
#define _hw_ad10b_vref_vcc			, 1	/* , refs */
#define _hw_ad10b_vref_pin_aref			, 0
#define _hw_ad10b_vref_bandgap			, 3

/*	Optionnal parameter 'align'
 */
#define _hwa_cfad10b_align(o,...)					\
  HW_G2(_hwa_cfad10b_kalign, HW_IS(align,__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_kalign_0(o,...)		\
  _hwa_cfad10b_kinput(o,__VA_ARGS__)
#define _hwa_cfad10b_kalign_1(o,k,...)					\
  HW_G2(_hwa_cfad10b_valign, HW_IS(,_hw_ad10b_align_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_valign_0(o,v,...)				\
  HW_ERR("`align` can be `left`, or `right` but not `" #v "`.")
#define _hwa_cfad10b_valign_1(o,v,...)			\
  _hwa_write_reg(o,lar, HW_A1(_hw_ad10b_align_##v));	\
  _hwa_cfad10b_kinput(o,__VA_ARGS__)

#define _hw_is_align_align			, 1
#define _hw_ad10b_align_left			, 1	/* , lar */
#define _hw_ad10b_align_right			, 0

/*	Mandatory parameter 'input'
 */
#define _hwa_cfad10b_kinput(o,...)					\
  HW_G2(_hwa_cfad10b_kinput, HW_IS(input,__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_kinput_0(o,k,...)			\
  HW_ERR("expected `input` instead of `" #k "`.")
#define _hwa_cfad10b_kinput_1(o,k,v,...)				\
  if ( HW_IS(,HW_A0(_hw_ad10b_input_##v)) )				\
    _hwa_write_reg(o,mux, HW_A1(_hw_ad10b_input_##v,0));		\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc0 ) )		\
    _hwa_write_reg(o,mux, 0);						\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc1 ) )		\
    _hwa_write_reg(o,mux, 1);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc2 ) )		\
    _hwa_write_reg(o,mux, 2);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc3 ) )		\
    _hwa_write_reg(o,mux, 3);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc4 ) )		\
    _hwa_write_reg(o,mux, 4);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc5 ) )		\
    _hwa_write_reg(o,mux, 5);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc6 ) )		\
    _hwa_write_reg(o,mux, 6);	     					\
  else if ( hw_id(v)!=0 && hw_id(v)==hw_id( hw_pin_adc7 ) )		\
    _hwa_write_reg(o,mux, 7);						\
  else									\
    HWA_ERR("`input` can be `hw_pin_adc0..7` (or synonyms), "		\
	    "`temperature`, `bandgap`, or `ground`  but not `"#v"`.");	\
  HW_TX(__VA_ARGS__)

#define _hw_is_input_input			, 1
#define _hw_ad10b_input_temperature		, 8	/* , mux */
#define _hw_ad10b_input_bandgap			, 14
#define _hw_ad10b_input_ground			, 15


/*  Power management
 */
#define _hw_mthd_hw_power__ad10b	, _hw_power
#define _hw_mthd_hwa_power__ad10b	, _hwa_power


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_turn Turning on / off
 *
 * The ADC must be turned off for the analog comparator to have access to the
 * analog multiplexer.
 *
 * @note This is not related to power management. Assuming the target device
 * supports it, use `hw_power()` or `hwa_power()` if you want power the ADC
 * on/off.
 *
 * @code
 * hw_turn( ADC_NAME, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__ad10b		, _hw_turn_ad10_


/**
 * @page atmelavr_ad10b
 *
 * @code
 * hwa_turn( ADC_NAME, on | off );
 * @endcode
 */
#define _hw_mthd_hwa_turn__ad10b	, _hwa_turn_ad10_


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_trigger Starting a conversion
 *
 * @code
 * hw_trigger( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_trigger__ad10b	, _hw_trigger_ad10_

/**
 * @page atmelavr_ad10b
 *
 * @code
 * hwa_trigger( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hwa_trigger__ad10b	, _hwa_trigger_ad10_


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_read Result of the conversion
 *
 * @code
 * uint16_t adc = hw_read( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__ad10b		, _hw_rdad10_

/**
 * @page atmelavr_ad10b
 *
 * @code
 * uint16_t adc = hw_atomic_read( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_atomic_read__ad10b	, _hw_ardad10_


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_stat Status
 *
 * You'll usually use the IRQ flag to test whether a conversion is completed:
 *
 * @code
 * hw_trigger( ADC_NAME );
 * while ( !hw_stat_irqf( ADC_NAME ) ) {}
 * hw_clear_irqf( ADC_NAME );
 * uint16_t result = hw_read( ADC_NAME );
 * @endcode
 *
 * but you can also check the `busy` flag of the status of the converter to know
 * whether a conversion is in progress:
 *
 * @code
 * hw_stat_t(ADC_NAME)	st ;
 * st = hw_stat(ADC_NAME);
 * if ( !st.busy )
 *   hw_trigger( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_stat__ad10b		, _hw_stat_ad10_


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ad10b(o,i,a)	_hwa_setup__ad10_(o)
#define _hwa_init__ad10b(o,i,a)		_hwa_init__ad10_(o)
#define _hwa_commit__ad10b(o,i,a)	_hwa_commit__ad10_(o)


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_internals Internals
 *
 * Class `_ad10b` objects hold the following hardware registers:
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
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_ad10b
 * <br>
 */
