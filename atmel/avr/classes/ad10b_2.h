
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief A/D converter
 */

/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_config1 Configuration
 *
 * __Note__: the ADC is turned off by default. Configuring the ADC will
 * automatically turn it on.
 *
 * @code
 * hwa_config( ADC_NAME,
 * 
 *             //  Clock source: the resulting clock frequency should be in
 *             //  the 50..200 kHz range for maximum resolution, and in all
 *             //  case lower than 1 MHz.
 *             //
 *             clock,        sysclk_div(    2
 *                                      |   4
 *                                      |   8
 *                                      |  16
 *                                      |  32
 *                                      |  64
 *                                      | 128 ),
 *
 *             //  How a conversation is started
 *             //
 *             trigger,      manual                     // with the `hw_trigger()` instruction
 *                         | auto                       // as soon as a consersion is completed
 *                         | hw_acmp0                   // ANA_COMP interrupt request
 *                         | hw_int0                    // INT0 interrupt request
 *                         | hw_counter0_compare0       // TIMER0_COMPA interrupt request
 *                         | hw_counter0_overflow       // TIMER0_OVF interrupt request
 *                         | hw_counter1_compare1       // TIMER1_COMPB interrupt request
 *                         | hw_counter1_overflow       // TIMER1_OVF interrupt request
 *                         | hw_counter1_capture,       // TIMER1_CAPT interrupt request
 *
 *             //  Voltage reference
 *             //
 *             vref,         vcc                        // Vcc
 *                         | hw_pin_avcc                // Voltage on AVCC pin
 *                         | hw_pin_aref                // Voltage on AREF pin
 *                         | bandgap,                   // Internal 1.1V bandgap
 * 
 *             //  Result alignment (default is `right`)
 *             //
 *           [ align,        left
 *                         | right, ]
 *
 *             //  Input
 *             //
 *             input,        hw_pin_adc0 .. hw_pin_adc7
 *                         | agnd
 *                         | bandgap
 *                         | temperature
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__ad10b		, _hwa_cfad10b

/*	Mandatory parameter 'clock'
 */
#define _hw_is_clock_clock			, 1
#define _hw_ad10b_clock_sysclk_div_2		, 0	/* , ps */
#define _hw_ad10b_clock_sysclk_div_4		, 2
#define _hw_ad10b_clock_sysclk_div_8		, 3
#define _hw_ad10b_clock_sysclk_div_16		, 4
#define _hw_ad10b_clock_sysclk_div_32		, 5
#define _hw_ad10b_clock_sysclk_div_64		, 6
#define _hw_ad10b_clock_sysclk_div_128		, 7
#define _hw_ad10b_clock_sysclk_div(x)		HW_G2(_hw_ad10b_clock_sysclk_div,x)

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
  HW_ERR("`clock` can be `sysclk_div( 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 )`, not `"#v".")
#define _hwa_cfad10b_vclock_1(o,v,k,...)				\
  _hwa_write_reg(o,ps, HW_A1(_hw_ad10b_clock_##v));			\
  HW_G2(_hwa_cfad10b_ktrigger, HW_IS(trigger,k))(o,k,__VA_ARGS__)

/*	Mandatory parameter 'trigger'
 */
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

/*	Mandatory parameter 'vref'
 */
#define _hw_is_vref_vref			, 1
#define _hw_ad10b_vref_vcc			, 1	/* , refs */
#define _hw_ad10b_vref_pin_aref			, 0
#define _hw_ad10b_vref_bandgap			, 3

#define _hwa_cfad10b_kvref_0(o,...)					\
  HW_ERR("expected `vref` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10b_kvref_1(o,k,...)					\
  HW_G2(_hwa_cfad10b_vvref, HW_IS(,_hw_ad10b_vref_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_vvref_0(o,v,...)					\
  HW_ERR("`vref` can be `vcc`, `hw_pin_avcc`, `hw_pin_aref`, or `bandgap` but not `" #v "`.")
#define _hwa_cfad10b_vvref_1(o,v,...)			\
  _hwa_write_reg(o,refs, HW_A1(_hw_ad10b_vref_##v));	\
  _hwa_cfad10b_align(o,__VA_ARGS__)

/*	Optionnal parameter 'align'
 */
#define _hw_is_align_align			, 1
#define _hw_ad10b_align_left			, 1	/* , lar */
#define _hw_ad10b_align_right			, 0

#define _hwa_cfad10b_align(o,...)					\
  HW_G2(_hwa_cfad10b_kalign, HW_IS(align,__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_kalign_0(o,...)		\
  _hwa_cfad10b_kinput(o,__VA_ARGS__)
#define _hwa_cfad10b_kalign_1(o,k,...)					\
  HW_G2(_hwa_cfad10b_valign, HW_IS(,_hw_ad10b_align_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_valign_0(o,v,...)				\
  HW_ERR("`align` can be `left`, or `right` but not `" #v "`.")
#define _hwa_cfad10b_valign_1(o,v,...)				\
  _hwa_write_reg(o,lar, HW_A1(_hw_ad10b_align_##v));	\
  _hwa_cfad10b_kinput(o,__VA_ARGS__)

/*	Mandatory parameter 'input'
 */
#define _hw_is_input_input			, 1
#define _hw_ad10b_input_temperature		, 8	/* , mux */
#define _hw_ad10b_input_bandgap			, 14
#define _hw_ad10b_input_ground			, 15

#define _hwa_cfad10b_kinput(o,...)					\
    HW_G2(_hwa_cfad10b_kinput, HW_IS(input,__VA_ARGS__))(o,__VA_ARGS__)
#define _hwa_cfad10b_kinput_0(o,k,...)					\
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
 * __Note__: this is not related to power management. Assuming the target device
 * supports it, use `hw_power()` or `hwa_power()` if you want power the ADC
 * on/off.
 *
 * @code
 * hw_turn( ADC_NAME, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__ad10b		, _hw_turn_ad10b

#define _hw_turn_ad10b(o,i,a, ...)					\
  HW_G2(_hw_turn_ad10b, HW_IS(,_hw_state_##__VA_ARGS__))(o,__VA_ARGS__)
#define _hw_turn_ad10b_0(o,v, ...)			\
  HW_ERR("expected `on` or `off`, not `" #v "`.")
#define _hw_turn_ad10b_1(o,v, ...)				\
  HW_TX(_hw_write_reg(o, en, HW_A1(_hw_state_##v)),__VA_ARGS__)


/**
 * @page atmelavr_ad10b
 *
 * @code
 * hwa_turn( ADC_NAME, on | off );
 * @endcode
 */
#define _hw_mthd_hwa_turn__ad10b	, _hwa_turn_ad10b

#define _hwa_turn_ad10b(o,i,a, ...)					\
  HW_G2(_hwa_turn_ad10b, HW_IS(,_hw_state_##__VA_ARGS__))(o,__VA_ARGS__,)
#define _hwa_turn_ad10b_0(o,v, ...)			\
  HW_ERR("expected `on` or `off`, got `" #v "` instead.")
#define _hwa_turn_ad10b_1(o,v, ...)			\
  HW_TX(_hwa_write_reg(o, en, HW_A1(_hw_state_##v)),__VA_ARGS__)


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_trigger Starting a conversion
 *
 * @code
 * hw_trigger( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_trigger__ad10b	, _hw_trigger_ad10b
#define _hw_trigger_ad10b(o,i,a,...)	HW_TX(_hw_write_reg(o, sc, 1),__VA_ARGS__)

/**
 * @page atmelavr_ad10b
 *
 * @code
 * hwa_trigger( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hwa_trigger__ad10b	, _hwa_trigger_ad10b
#define _hwa_trigger_ad10b(o,i,a,...)	HW_TX(_hwa_write_reg(o, sc, 1),__VA_ARGS__)


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_read Result of the conversion
 *
 * @code
 * uint16_t adc = hw_read( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__ad10b		, _hw_read_ad10b
#define _hw_read_ad10b(o,i,a,...)	HW_TX(_hw_read_reg(o, adc),__VA_ARGS__)

#if 0
/*  FIXME: usefull?
 */
/**
 * @page atmelavr_ad10b
 *
 * @code
 * uint16_t adc = hw_atomic_read( ADC_NAME );
 * @endcode
 */
#define _hw_mthd_hw_atomic_read__ad10b	, _hw_atoread_ad10b
#define _hw_atoread_ad10b(o,i,a,...)	HW_TX(_hw_atomic_read_reg(o, adc),__VA_ARGS__)
#endif


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
typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  __0_5 : 6 ;
    unsigned int  busy  : 1 ;
    unsigned int  __7   : 1 ;
  };
} _hw_ad10b_status_t ;

#define _hw_mthd_hw_stat__ad10b		, _hw_stat_ad10b
#define _hw_stat_ad10b(o,i,a,...)	HW_TX(_hw_ad10b_status(_hw_read_reg(o,sra)), \
					      __VA_ARGS__)

HW_INLINE _hw_ad10b_status_t _hw_ad10b_status( uint8_t byte )
{
  _hw_ad10b_status_t	st ;
  st.byte = byte ;
  return st ;
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_create__ad10b(o,i,a)		\
  _hwa_create_reg( o, admux );			\
  _hwa_create_reg( o, sra   );			\
  _hwa_create_reg( o, srb   )

#define _hwa_init__ad10b(o,i,a)			\
  _hwa_init_reg( o, admux, 0x00 );		\
  _hwa_init_reg( o, sra,   0x00 );		\
  _hwa_init_reg( o, srb,   0x00 )

#define _hwa_commit__ad10b(o,i,a)		\
  _hwa_commit_reg( o, admux );			\
  _hwa_commit_reg( o, sra   );			\
  _hwa_commit_reg( o, srb   )


/* /\* HW_INLINE void _hwa_begin_p__ad10b ( hwa_ad10b_t *p, intptr_t a ) */
/* { */
/*   _hwa_create_reg_p( p, a, _ad10b, admux ); */
/*   _hwa_create_reg_p( p, a, _ad10b, sra   ); */
/*   _hwa_create_reg_p( p, a, _ad10b, srb   ); */
/*   _hwa_create_reg_p( p, a, _ad10b, did   ); */
/* } */


/* HW_INLINE void _hwa_init_p__ad10b ( hwa_ad10b_t *p ) */
/* { */
/*   _hwa_set__r8( &p->admux, 0x00 ); */
/*   _hwa_set__r8( &p->sra,   0x00 ); */
/*   _hwa_set__r8( &p->srb,   0x00 ); */
/*   _hwa_set__r8( &p->did,   0x00 ); */
/* } */


/* HW_INLINE void _hwa_commit_p__ad10b ( hwa_t *hwa, hwa_ad10b_t *p ) */
/* { */
/*   _hwa_commit_reg_p( p, _ad10b, admux ); */
/*   _hwa_commit_reg_p( p, _ad10b, sra   ); */
/*   _hwa_commit_reg_p( p, _ad10b, srb   ); */
/*   _hwa_commit_reg_p( p, _ad10b, did   ); */
/* } */



/**
 * @page atmelavr_ad10b
 * @section Internals
 *
 * Though it should not be necessary, the internal registers are accessible
 * through the @ref public_reg_instructions "register access intructions".
 *
 * Class `_ad10b` objects have the following hardware registers:
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

/**
 * @page atmelavr_ad10b
 * <br>
 */
