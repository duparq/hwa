
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit counter with two compare units and one dead-time generator
 */

/**
 * @addtogroup atmelavr_ctb
 * @section atmelavr_ctbact Actions
 *
 * <br><br>hwa( configure, ... ): configure the counting unit
 *
 * @code
 * hwa( configure, counter0,
 *
 *	//  How the counter is clocked
 *	//
 *	clock,	     none			// No clock, counter stopped
 *		   | ioclk [/ 2**(0..14)]	// IOCLK divided by 1,2,4,..16384
 *
 *    [ direction,   up_loop, ]			// Default, no other choice
 *    [ bottom,	     0,	      ]			// Default, no other choice
 *
 *	//  The maximum value the counter reaches
 *	//
 *    [ top,	     0xFF | 0x00FF | 255 | max	// Hardware fixed value 0xFF (default)
 *		   | compare2, ]		// Value stored in compare2
 *
 *	//  When the overflow flag is set
 *	//
 *    [ overflow,    after_bottom ]		// When the counter restarts from 0
 * );
 * @endcode
 *
 * @note If a compare unit is used, its configuration must be done inside the
 * same context as the counter so that HWA has all the necessary informations to
 * choose the correct register settings.
 */
#define hwa_configure__ctb		, _hwa_cfctb

/*  Mandatory argument `clock`
 *
 *    Add 2 void arguments to the end of the list so that there are always
 *    3 arguments following the last non-void argument.
 */
#define _hwa_cfctb(o,a,k,...)						\
  do { HW_B(_hwa_cfctb_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfctb_kclock_0(o,k,...)		HW_E(HW_EM_AN(k,clock))
#define _hwa_cfctb_kclock_1(o,k,v,...)		HW_B(_hwa_cfctb_vclock_,_hw_ctb_clock_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctb_vclock_0(o,v,...)					\
  HW_E(HW_EM_VAL(v,clock,(none,ioclk [/ 2**n] with n in {0..14})))

#define _hwa_cfctb_vclock_1(o,v,k,...)					\
  _hwa_write(o, cs, HW_VF(_hw_ctb_clock_##v));				\
  HW_B(_hwa_cfctb_kdirection_,_hw_is_direction_##k)(o,k,__VA_ARGS__)

#define _hw_ctb_clock_none		, _hw_ctbck_none, 0
#define _hw_ctb_clock_ioclk		, _hw_ctbck_ioclk, 16384.0

HW_INLINE uint8_t _hw_ctbck_none( float v )
{
  if ( v != 0 )
    HWA_E(HW_EM_VL(clock,(none, ioclk/2**(0..14), external_falling, external_rising)));

  return 0 ;
}

HW_INLINE uint8_t _hw_ctbck_ioclk( float v )
{
  if ( v == 16384 ) return 1 ;
  if ( v ==  8192 ) return 2 ;
  if ( v ==  4096 ) return 3 ;
  if ( v ==  2048 ) return 4 ;
  if ( v ==  1024 ) return 5 ;
  if ( v ==   512 ) return 6 ;
  if ( v ==   256 ) return 7 ;
  if ( v ==   128 ) return 8 ;
  if ( v ==    64 ) return 9 ;
  if ( v ==    32 ) return 10 ;
  if ( v ==    16 ) return 11 ;
  if ( v ==     8 ) return 12 ;
  if ( v ==     4 ) return 13 ;
  if ( v ==     2 ) return 14 ;
  if ( v ==     1 ) return 15 ;

  HWA_E(HW_EM_VL(clock,(none, ioclk/2**(0..14), external_falling, external_rising)));

  return 0 ;
}

/*  Optionnal argument `direction`
 */
#define _hwa_cfctb_kdirection_1(o,k,v,...)				\
  HW_G2(_hwa_cfctb_vdirection,HW_IS(up_loop,v))(o,v,__VA_ARGS__)

#define _hwa_cfctb_vdirection_0(o,v,...)	\
  HW_E(HW_EM_VAL(v,direction,(up_loop)))

#define _hwa_cfctb_vdirection_1(o,v,...)	\
  _hwa_cfctb_kdirection_0(o,__VA_ARGS__)

#define _hwa_cfctb_kdirection_0(o,k,...)			\
  HW_B(_hwa_cfctb_kbottom_,_hw_is_bottom_##k)(o,k,__VA_ARGS__)

/*  Optionnal argument `bottom`
 */
#define _hwa_cfctb_kbottom_1(o,k,v,...)			\
  HW_G2(_hwa_cfctb_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfctb_vbottom_0(o,v,...)		\
  HW_E(HW_EM_VAL(v,bottom,(0)))

#define _hwa_cfctb_vbottom_1(o,v,...)		\
  _hwa_cfctb_kbottom_0(o,__VA_ARGS__)

#define _hwa_cfctb_kbottom_0(o,k,...)				\
  HW_B(_hwa_cfctb_ktop_,_hw_is_top_##k)(o,k,__VA_ARGS__)


/*  Optionnal argument `top`
 */
#define _hw_ctb_top_0xFF		, 0
#define _hw_ctb_top_0x00FF		, 0
#define _hw_ctb_top_255			, 0
#define _hw_ctb_top_max			, 0
#define _hw_ctb_top_compare2		, 1

#define _hwa_cfctb_ktop_1(o,k,v,...)				\
  HW_B(_hwa_cfctb_vtop_,_hw_ctb_top_##v)(o,v,__VA_ARGS__)

#define _hwa_cfctb_vtop_0(o,v,...)				\
  HW_E(HW_EM_VAL(v,top,(0xFF,0x00FF,255,max,compare2)))

#define _hwa_cfctb_vtop_1(o,v,...)		\
  _hwa_write(o, ctc, HW_A1(_hw_ctb_top_##v));	\
  _hwa_cfctb_ktop_0(v,__VA_ARGS__)

#define _hwa_cfctb_ktop_0(o,k,...)					\
  HW_B(_hwa_cfctb_koverflow_,_hw_is_overflow_##k)(o,k,__VA_ARGS__)


/*  Optionnal argument `overflow`
 */
#define _hwa_cfctb_koverflow_1(o,k,v,...)				\
  HW_G2(_hwa_cfctb_voverflow,HW_IS(after_bottom,v))(o,v,__VA_ARGS__)

#define _hwa_cfctb_voverflow_0(o,v,...)		\
  HW_E(HW_EM_VAL(v,overflow,(after_bottom)))

#define _hwa_cfctb_voverflow_1(o,v,...)		\
  _hwa_cfctb_koverflow_0(o,__VA_ARGS__)

#define _hwa_cfctb_koverflow_0(o,...)		HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ctb
 *
 * <br><br>hw( read, ... ): get the count
 *
 * @code
 * uint8_t n = hw( read, counter0 );
 * @endcode
 *
 * <br><br>hw( write, ... ), hwa( write, ... ): set the count
 *
 * @code
 * hw( write, counter0, value );
 * @endcode
 *
 * @code
 * hwa( write, counter0, value );
 * @endcode
 */
#define hw_read__ctb			, _hw_ctbrd
#define _hw_ctbrd(o,a,...)		 _hw_read(o,count) HW_EOL(__VA_ARGS__)

#define hw_write__ctb			, _hw_ctbwr
#define _hw_ctbwr(o,a,v,...)		 _hw_write(o,count,v) HW_EOL(__VA_ARGS__)

#define hwa_write__ctb			, _hwa_ctbwr
#define _hwa_ctbwr(o,a,v,...)		 _hwa_write(o,count,v) HW_EOL(__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

/* Solve the configuration of the counter and its related peripherals.
 *
 *  This kind of counter does not trigger overflow IRQs on compare match with
 *  OCRC if no compare output is in pwm mode:
 *
 *  "In the normal mode an overflow interrupt (TOV1) is generated when
 *  Timer/Counter1 counts from $FF to $00, while in the PWM mode the overflow
 *  interrupt is generated when Timer/Counter1 counts either from $FF to $00 or
 *  from OCR1C to $00. The inverted PWM outputs OC1A and OC1B are not connected
 *  in normal mode."
 *
 * -> If one compare output has been put in PWM mode, the other must have been
 *    too if it is used.
 */
#define _hwa_solve__ctb(o,a)						\
  _hwa_solve_ocb(o,0);							\
  _hwa_solve_ocb(o,1);							\
  if ( _hwa_mmask(o,pwm0) && _hwa_mmask(o,pwm1)				\
       && _hwa_mvalue(o,pwm0) != _hwa_mvalue(o,pwm1) )			\
    /* "used compare outputs must be in the same NORMAL or PWM mode." */ \
    HWA_E(HW_EM_CMOO((o,compare0),(o,compare1)));			\
  else if ( _hwa_mmask(o,ctc) && _hwa_mvalue(o,ctc)==0			\
	    && (   (_hwa_mmask(o,pwm0) && _hwa_mvalue(o,pwm1))		\
		   || (_hwa_mmask(o,pwm1) && _hwa_mvalue(o,pwm1))) )	\
    /* "`top` must be `compare2` for `" #o "` when using the PWM mode." */ \
    HWA_E(HW_EM_AOVM(top,o,compare2));				\
  if ( _hwa_mvalue(o,ie)==1						\
       && _hwa_mvalue(o,ctc)==1						\
       && _hwa_mvalue(o,pwm0) == 0					\
       && _hwa_mvalue(o,pwm1) == 0 ) {					\
    if ( _hwa_mmask(o,pwm0)==1 || _hwa_mmask(o,pwm1)== 1 )		\
      /* "`" #o "` does not trigger overflow IRQs when not using PWM mode for outputs." */ \
      HWA_E(HW_EM_1(o));						\
    else								\
      if ( _hwa_mmask(o,pwm0)==0 )					\
	_hwa_write(o,pwm0,1);						\
      else								\
	_hwa_write(o,pwm0,1);						\
    }


#define _hwa_setup__ctb(o,a)			\
  _hwa_setup_r( o, ccr	    );			\
  _hwa_setup_r( o, count    );			\
  _hwa_setup_r( o, ocr0 );			\
  _hwa_setup_r( o, ocr1 );			\
  _hwa_setup_r( o, ocr2 );			\
  _hwa_setup_r( o, dtps );			\
  _hwa_setup_r( o, dta );			\
  _hwa_setup_r( o, dtb );			\
  hwa->o.compare0.config.outputh = 0xFF ;	\
  hwa->o.compare0.config.outputl = 0xFF ;	\
  hwa->o.compare1.config.outputh = 0xFF ;	\
  hwa->o.compare1.config.outputl = 0xFF ;	\

#define _hwa_init__ctb(o,a)			\
  _hwa_init_r( o, ccr, 0	);		\
  _hwa_init_r( o, count, 0	);		\
  _hwa_init_r( o, ocr0, 0 );			\
  _hwa_init_r( o, ocr1, 0 );			\
  _hwa_init_r( o, ocr2, 0 );			\
  _hwa_init_r( o, dtps, 0 );			\
  _hwa_init_r( o, dta, 0 );			\
  _hwa_init_r( o, dtb, 0 )

#define _hwa_commit__ctb(o,a)			\
  _hwa_commit_r( o, ccr	  );			\
  _hwa_commit_r( o, count );			\
  _hwa_commit_r( o, ocr0  );			\
  _hwa_commit_r( o, ocr1  );			\
  _hwa_commit_r( o, ocr2  );			\
  _hwa_commit_r( o, dtps  );			\
  _hwa_commit_r( o, dta   );			\
  _hwa_commit_r( o, dtb   )


/**
 * @addtogroup atmelavr_ctb
 * @section atmelavr_ctb_internals Internals
 *
 * Hardware registers:
 *
 *  * `ccr`: control register
 *  * `count`: count register
 *  * `ocr0`: output-compare A register
 *  * `ocr1`: output-compare B register
 *  * `ocr2`:        compare C register
 *  * `dtps`: dead-time prescaler register
 *  * `dta`: dead-time A register
 *  * `dtb`: dead-time B register
 *
 * Logical registers:
 *
 *  * `com0`
 *  * `com1`
 *  * `cs`
 *  * `ctc`
 *  * `dtg0h`
 *  * `dtg0l`
 *  * `dtg1h`
 *  * `dtg1l`
 *  * `dtgs`
 *  * `foc0`
 *  * `foc1`
 *  * `ie`
 *  * `if`
 *  * `ocie0`
 *  * `ocie1`
 *  * `ocif0`
 *  * `ocif1`
 *  * `pwm0`
 *  * `pwm1`
 */
