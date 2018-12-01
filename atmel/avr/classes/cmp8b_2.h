
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_cmp8b
 * @section atmelavr_cmp8b_acfg Configuration
 *
 * @code
 * hwa( configure, compare0,
 *
 *	   [   update,	   at_top, ]
 *
 *	   [   output
 *	     | output_h,   disconnected
 *			 | toggle_on_match
 *			 | clear_on_match
 *			 | set_on_match
 *			 | set_at_bottom_clear_on_match
 *			 | clear_at_bottom_set_on_match, ]
 *
 *	   [   output_l,   disconnected
 *			 | clear_at_bottom_set_on_match	 ]
 *	     );
 * @endcode
 */

#define hwa_configure__cmp8b	, _hwa_cfcmp8b


/*  Optionnal argument `update`
 *
 *    Add a second void argument to the end of the list so that there are always
 *    at least 2 arguments following the last non-void argument.
 */
#define _hwa_cfcmp8b(o,i,a,k,...)					\
  do {									\
    HW_Y(_hwa_cfcmp8b_kupdate_,_hw_is_update_##k)(o,k,__VA_ARGS__,)	\
      } while(0)

#define _hwa_cfcmp8b_kupdate_1(o,kw,v,...)				\
  HW_G2(_hwa_cfcmp8b_vupdate,HW_IS(at_top,v))(o,v,__VA_ARGS__)

#define _hwa_cfcmp8b_vupdate_0(o,v,...)				\
  HW_E_AVL(`update`, v, `at_top`)

#define _hwa_cfcmp8b_vupdate_1(o,v,...)		\
  _hwa_cfcmp8b_kupdate_0(o,__VA_ARGS__)

#define _hwa_cfcmp8b_kupdate_0(o,kw,...)					\
  HW_Y(_hwa_cfcmp8b_koutputh_,_hw_cmp8b_koutputh_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `output` (or `output_h`)
 */
#define _hw_cmp8b_koutputh_output	, 1
#define _hw_cmp8b_koutputh_output_h	, 1

/*								// COM	PWM
 */
#define _hw_cmp8b_voutputh_disconnected	, 0	// 0	0
#define _hw_cmp8b_voutputh_toggle_on_match	, 1	// 1	0
#define _hw_cmp8b_voutputh_clear_on_match	, 2	// 2	0
#define _hw_cmp8b_voutputh_set_on_match	, 3	// 3	0
#define _hw_cmp8b_voutputh_set_at_bottom_clear_on_match	, 4	// 1,2	1
#define _hw_cmp8b_voutputh_clear_at_bottom_set_on_match	, 5	// 3	1


#define _hwa_cfcmp8b_koutputh_1(o,kw,v,...)				\
  HW_Y(_hwa_cfcmp8b_voutputh_,_hw_cmp8b_voutputh_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcmp8b_voutputh_0(o,v,...)					\
  HW_E_AVL(`output_h` (or `output`), v, `disconnected | toggle_on_match | clear_on_match | set_on_match | set_at_bottom_clear_on_match | clear_at_bottom_set_on_match`)

#define _hwa_cfcmp8b_voutputh_1(o,v,...)		\
  hwa->o.config.outputh = HW_A1(_hw_cmp8b_voutputh_##v);	\
  _hwa_cfcmp8b_koutputh_0(o,__VA_ARGS__)

#define _hwa_cfcmp8b_koutputh_0(o,kw,...)				\
  HW_G2(_hwa_cfcmp8b_koutputl,HW_IS(output_l,kw))(o,kw,__VA_ARGS__)


/*  Optionnal argument `output_l`
 */
/*								// COM	  PWM
 */
#define _hw_cmp8b_voutputl_disconnected	, 0	// 0,2,3  0,1
#define _hw_cmp8b_voutputl_clear_at_bottom_set_on_match	, 1	// 1	  1

#define _hwa_cfcmp8b_koutputl_1(o,kw,v,...)				\
  HW_Y(_hwa_cfcmp8b_voutputl_,_hw_cmp8b_voutputl_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcmp8b_voutputl_0(o,v,...)				\
  HW_E_AVL(output_l, v, disconnected | clear_at_bottom_set_on_match)

#define _hwa_cfcmp8b_voutputl_1(o,v,...)			\
  hwa->o.config.outputl = HW_A1(_hw_cmp8b_voutputl_##v);	\
  _hwa_cfcmp8b_koutputl_0(o,__VA_ARGS__)

#define _hwa_cfcmp8b_koutputl_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cmp8b
 * @section atmelavr_cmp8b_cr Compare value
 *
 * The compare value is set using the hw_write() or hwa_write() instruction:
 *
 * @code
 * hw_write( compare0, value );
 * @endcode
 */
#define hw_write__cmp8b	, _hw_wrcmp8b
#define _hw_wrcmp8b(o,i,a,v,...)		_hw_write(o,reg,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_cmp8b
 *
 * @code
 * hwa_write( compare0, value );
 * @endcode
 */
#define hwa_write__cmp8b	, _hwa_wrcmp8b
#define _hwa_wrcmp8b(o,i,a,v,...)	_hwa_write(o,reg,v) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cmp8b
 *
 * The compare value is read using the`read`instruction:
 *
 * @code
 * uint16_t ocr = hw( read, compare0 );
 * @endcode
 */
#define hw_read__cmp8b		, _hw_read_cmp8b
#define _hw_read_cmp8b(o,i,a,...)	_hw_read(o,reg) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cmp8b
 * @section atmelavr_cmp8b_st Status
 *
 * The compare event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, irqflag( compare0 ) ) ) {	// Read compare IRQ flag
 *   hw( clear, irqflag( compare0 ) );		// Clear compare IRQ flag
 *   hw( turn, irq( compare0, off ) );		// Disable compare IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__cmp8b(o,i,a)			\
  _hwa_setup_r( o, reg );			\
  hwa->o.config.outputh = 0xFF ;			\
  hwa->o.config.outputl = 0xFF ;


#define _hwa_init__cmp8b(o,i,a)			_hwa_init_r( o, reg, 0x00 );

#define _hwa_solve_cmp8b(o)						\
  if ( hwa->o.config.outputh != 0xFF || hwa->o.config.outputl != 0xFF ) {	\
  if ( hwa->o.config.outputl == HW_A1(_hw_cmp8b_voutputl_clear_at_bottom_set_on_match) ) { \
    if ( hwa->o.config.outputh != HW_A1(_hw_cmp8b_voutputh_set_at_bottom_clear_on_match) ) \
      HWA_ERR("`output_h` must be `set_at_bottom_clear_on_match` "	\
	      "when `output_l` is `clear_at_bottom_set_on_match`.");	\
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,1);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_disconnected) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,0);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_toggle_on_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,1);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_clear_on_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,2);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_set_on_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,3);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_set_at_bottom_clear_on_match) ) { \
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,2);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_cmp8b_voutputh_clear_at_bottom_set_on_match) ) { \
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,3);						\
  }									\
  if ( hwa->o.config.outputh != 0xFF && hwa->o.config.outputh != 0 )	\
    _hwa( configure, (o,pin_h), mode, digital_output );	\
  if ( hwa->o.config.outputl != 0xFF && hwa->o.config.outputl != 0 )	\
    _hwa( configure, (o,pin_l), mode, digital_output );	\
  }


#define _hwa_commit__cmp8b(o,i,a)		_hwa_commit_r(o,reg);


/**
 * @page atmelavr_cmp8b
 * <br>
 */
