
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

HW_INLINE uint8_t _hw_c8bck_none( float v )
{
  if ( v != 0 )
    HWA_E(value of `clock` must be in (`none`, `ioclk/2**n` with n in [1..14], `external_falling`, `external_rising`));

  return 0 ;
}

HW_INLINE uint8_t _hw_c8bck_ioclk( float v )
{
  if ( v == 16384 )
    return 1 ;
  if ( v == 8192 )
    return 2 ;
  if ( v == 4096 )
    return 3 ;
  if ( v == 2048 )
    return 4 ;
  if ( v == 1024 )
    return 5 ;
  if ( v == 512 )
    return 6 ;
  if ( v == 256 )
    return 7 ;
  if ( v == 128 )
    return 8 ;
  if ( v == 64 )
    return 9 ;
  if ( v == 32 )
    return 10 ;
  if ( v == 16 )
    return 11 ;
  if ( v == 8 )
    return 12 ;
  if ( v == 4 )
    return 13 ;
  if ( v == 2 )
    return 14 ;
  if ( v == 1 )
    return 15 ;

  HWA_E(value of `clock` must be in (`none`, `ioclk/2**n` with n in [1..14], `external_falling`, `external_rising`));

  return 0 ;
}

/**
 * @page atmelavr_c8b
 * @section atmelavr_c8b_acfg Configuration
 *
 * __Note__ If the a compare unit is used, its configuration must be done inside
 * the same context as its counter so that HWA has all the necessary
 * informations to choose the correct register settings.
 *
 * @code
 * hwa( configure, counter0,
 *
 *	//  Clock source
 *	//
 *	clock,	     none			 // No clock, counter stopped
 *		   | ioclk [/ 2**{n}]		 // I/O clock [divided], n in [ 0..14 ]
 *
 *	//  Class _c8b counters all loop from 0 to top
 *	//
 *    [ direction,   up_loop, ]
 *    [ bottom,	     0,	      ]
 *
 *	//  The maximum value the counter reaches (the default is `max`)
 *	//
 *    [ top,	     0xFF | 0x00FF | 255	  // Hardware fixed value 0xFF
 *		   | max			  // Hardware fixed value 0xFF
 *		   | compare2, ]		  // Value stored in the compare unit 2
 *
 *	//  When the overflow flag is set
 *	//
 *    [ overflow,    after_bottom ]		  // When the counter restarts from 0
 *     );
 * @endcode
 */
#define hwa_configure__c8b		, _hwa_cfc8b

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hwa_cfc8b(o,a,k,...)						\
  do { HW_Y(_hwa_cfc8b_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfc8b_kclock_0(o,k,...)		HW_E_VL(k,clock)
#define _hwa_cfc8b_kclock_1(o,k,v,...)		HW_Y(_hwa_cfc8b_vclock_,_hw_c8b_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vclock_0(o,v,...)					\
  HW_E_AVL(clock, v, `none` | `ioclk [/ 2**n]` with n in {0..14})

#define _hwa_cfc8b_vclock_1(o,v,k,...)					\
  _hwa_write(o, cs, HW_VF(_hw_c8b_clock_##v));				\
  HW_Y(_hwa_cfc8b_kdirection_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

#define _hw_c8b_clock_none		, _hw_c8bck_none, 0
#define _hw_c8b_clock_ioclk		, _hw_c8bck_ioclk, 16384.0

/*  Optionnal argument `direction`
 */
#define _hwa_cfc8b_kdirection_1(o,k,v,...)				\
  HW_G2(_hwa_cfc8b_vdirection,HW_IS(up_loop,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vdirection_0(o,v,...)	\
  HW_E_AVL(`direction`, v, `up_loop`)

#define _hwa_cfc8b_vdirection_1(o,v,...)	\
  _hwa_cfc8b_kdirection_0(o,__VA_ARGS__)

#define _hwa_cfc8b_kdirection_0(o,k,...)			\
  HW_Y(_hwa_cfc8b_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfc8b_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfc8b_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vbottom_0(o,v,...)		\
  HW_E_AVL(`bottom`, v, `0`)

#define _hwa_cfc8b_vbottom_1(o,v,...)		\
  _hwa_cfc8b_kbottom_0(o,__VA_ARGS__)

#define _hwa_cfc8b_kbottom_0(o,k,...)				\
  HW_Y(_hwa_cfc8b_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)


/*  Optionnal argument `top`
 */
#define _hw_c8b_top_0xFF		, 0
#define _hw_c8b_top_0x00FF		, 0
#define _hw_c8b_top_255			, 0
#define _hw_c8b_top_max			, 0
#define _hw_c8b_top_compare2		, 1

#define _hwa_cfc8b_ktop_1(o,k,v,...)				\
  HW_Y(_hwa_cfc8b_vtop_,_hw_c8b_top_##v)(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vtop_0(o,v,...)				\
  HW_E_AVL(top, v, 0xFF | 0x00FF | 255 | max | compare2)

#define _hwa_cfc8b_vtop_1(o,v,...)		\
  _hwa_write(o, ctc, HW_A1(_hw_c8b_top_##v));	\
  _hwa_cfc8b_ktop_0(v,__VA_ARGS__)

#define _hwa_cfc8b_ktop_0(o,k,...)					\
  HW_Y(_hwa_cfc8b_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)


/*  Optionnal argument `overflow`
 */
#define _hwa_cfc8b_koverflow_1(o,k,v,...)				\
  HW_G2(_hwa_cfc8b_voverflow,HW_IS(after_bottom,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_voverflow_0(o,v,...)		\
  HW_E_AVL(`overflow`, v, `after_bottom`)

#define _hwa_cfc8b_voverflow_1(o,v,...)		\
  _hwa_cfc8b_koverflow_0(o,__VA_ARGS__)

#define _hwa_cfc8b_koverflow_0(o,...)		HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_c8b
 * @section atmelavr_c8b_cnt Count value
 *
 * The count value is accessible for reading and writing through the following
 * instructions:
 */

/**
 * @page atmelavr_c8b
 * @code
 * hw( read, counter0 );
 * @endcode
 */
#define hw_read__c8b			, _hw_c8brd
#define _hw_c8brd(o,a,...)		 _hw_read(o,count) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_c8b
 * @code
 * hw( write, counter0, value );
 * @endcode
 */
#define hw_write__c8b			, _hw_c8bwr
#define _hw_c8bwr(o,a,v,...)		 _hw_write(o,count,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_c8b
 * @code
 * hwa( write, counter0, value );
 * @endcode
 */
#define hwa_write__c8b			, _hwa_c8bwr
#define _hwa_c8bwr(o,a,v,...)		 _hwa_write(o,count,v) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_c8b
 * @section atmelavr_c8b_st Status
 *
 * The overflow flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, irqflag( counter0 ) ) ) {	// Read overflow IRQ flag
 *   hw( clear, irqflag( counter0 ) );		// Clear overflow IRQ flag
 *   hw( turn, irq(counter0), off );		// Disable overflow IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

/**
 * @brief Solve the configuration of the counter and its related peripherals.
 */
/*  This kind of counter does not trigger overflow IRQs on compare match with
 *  OCRC if no compare output is in pwm mode:
 *
 *  "In the normal mode an overflow interrupt (TOV1) is generated when
 *  Timer/Counter1 counts from $FF to $00, while in the PWM mode the overflow
 *  interrupt is generated when Timer/Counter1 counts either from $FF to $00 or
 *  from OCR1C to $00. The inverted PWM outputs OC1A and OC1B are not connected
 *  in normal mode."
 *
 * -> If one compare output has been put in PWM mode, the other must have been
 *    too if it us used.
 * -> If 
 */
#define _hwa_solve__c8b( o,a )				\
  _hwa_solve__c8b_2( o, hw_##o##_compare0, hw_##o##_compare1 )

#define _hwa_solve__c8b_2(...)	_hwa_solve_c8b(__VA_ARGS__)

#define _hwa_solve_c8b(counter, compare0, compare1)			\
  _hwa_solve_cmp8b( compare0 );						\
  _hwa_solve_cmp8b( compare1 );						\
  if ( _hwa_mmask(compare0, pwm) && _hwa_mmask(compare1, pwm)		\
       && _hwa_mvalue(compare0, pwm) != _hwa_mvalue(compare1, pwm) )	\
    HWA_ERR("used compare outputs must be in the same NORMAL or PWM mode."); \
  else if ( _hwa_mmask(counter, ctc) && _hwa_mvalue(counter, ctc)==0	\
	    && (   (_hwa_mmask(compare0, pwm) && _hwa_mvalue(compare1, pwm)) \
		   || (_hwa_mmask(compare1, pwm) && _hwa_mvalue(compare1, pwm))) ) \
    HWA_ERR("`top` must be `compare2` for `" #counter "` when using the PWM mode."); \
  if ( _hwa_mvalue(counter, ie)==1					\
       && _hwa_mvalue(counter, ctc)==1					\
       && _hwa_mvalue(compare0, pwm) == 0				\
       && _hwa_mvalue(compare1, pwm) == 0 ) {				\
    if ( _hwa_mmask(compare0, pwm)==1 || _hwa_mmask(compare1, pwm)== 1 ) \
      HWA_ERR("`" #counter "` does not trigger overflow IRQs when not using PWM mode for outputs."); \
    else								\
      if ( _hwa_mmask(compare0, pwm)==0 )				\
	_hwa_write(compare0,pwm,1);					\
      else								\
	_hwa_write(compare1,pwm,1);					\
  }

#define _hwa_setup__c8b(o,a)			\
  _hwa_setup_r( o, ccr	    );			\
  _hwa_setup_r( o, count    );			\
  _hwa_setup_r( o, compare2 );

#define _hwa_init__c8b(o,a)			\
  _hwa_init_r( o, ccr, 0	);		\
  _hwa_init_r( o, count, 0	);		\
  _hwa_init_r( o, compare2, 0 );

#define _hwa_commit__c8b(o,a)			\
  _hwa_commit_r( o, ccr	     );			\
  _hwa_commit_r( o, count    );			\
  _hwa_commit_r( o, compare2 );


/**
 * @page atmelavr_c8b
 * @section atmelavr_c8b_internals Internals
 *
 * Class `_c8b` objects hold the following hardware registers:
 *
 *  * `ccr`: control register
 *  * `count`: count register
 *  * `compare2`: compare register c, storing the top value
 *
 * and 1 external register, that hold the following logical registers:
 *
 *  * `ctc`: clear on compare
 *  * `cs`: clock selection
 *  * `ie`: overflow interrupt mask
 *  * `if`: overflow interrupt flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */
