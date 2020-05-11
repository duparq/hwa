
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_ocb
 * @section atmelavr_oca_act Actions
 *
 * <br>
 * `configure`:
 *
 * @code
 * hwa( configure, (counter0,compare0),
 *
 *    [ update,	    after_top, ]
 *
 *  [	output
 *    | output_h,   disconnected
 *		  | toggle_after_match
 *		  | clear_after_match
 *		  | set_after_match
 *		  | set_at_bottom_clear_after_match
 *		  | clear_at_bottom_set_after_match, ]
 *
 *    [ output_l,   disconnected
 *		  | clear_at_bottom_set_after_match ] );
 * @endcode
 */

#define hwa_configure__ocb		, _hwa_cfocb


/*  Optionnal argument `update`
 *
 *    Add a second void argument to the end of the list so that there are always
 *    at least 2 arguments following the last non-void argument.
 */
#define _hwa_cfocb(o,a,k,...)					\
  do {									\
    HW_Y(_hwa_cfocb_kupdate_,_hw_is_update_##k)(o,k,__VA_ARGS__,)	\
      } while(0)

#define _hwa_cfocb_kupdate_1(o,kw,v,...)				\
  HW_G2(_hwa_cfocb_vupdate,HW_IS(after_top,v))(o,v,__VA_ARGS__)

#define _hwa_cfocb_vupdate_0(o,v,...)				\
  HW_E_AVL(`update`, v, `after_top`)

#define _hwa_cfocb_vupdate_1(o,v,...)		\
  _hwa_cfocb_kupdate_0(o,__VA_ARGS__)

#define _hwa_cfocb_kupdate_0(o,kw,...)					\
  HW_Y(_hwa_cfocb_koutputh_,_hw_ocb_koutputh_##kw)(o,kw,__VA_ARGS__)


/*  Optionnal argument `output` (or `output_h`)
 */
#define _hw_ocb_koutputh_output	, 1
#define _hw_ocb_koutputh_output_h	, 1

/*								// COM	PWM
 */
#define _hw_ocb_voutputh_disconnected	, 0	// 0	0
#define _hw_ocb_voutputh_toggle_after_match	, 1	// 1	0
#define _hw_ocb_voutputh_clear_after_match	, 2	// 2	0
#define _hw_ocb_voutputh_set_after_match	, 3	// 3	0
#define _hw_ocb_voutputh_set_at_bottom_clear_after_match	, 4	// 1,2	1
#define _hw_ocb_voutputh_clear_at_bottom_set_after_match	, 5	// 3	1


#define _hwa_cfocb_koutputh_1(o,kw,v,...)				\
  HW_Y(_hwa_cfocb_voutputh_,_hw_ocb_voutputh_##v)(o,v,__VA_ARGS__)

#define _hwa_cfocb_voutputh_0(o,v,...)					\
  HW_E_AVL(`output_h` (or `output`), v, `disconnected | toggle_after_match | clear_after_match | set_after_match | set_at_bottom_clear_after_match | clear_at_bottom_set_after_match`)

#define _hwa_cfocb_voutputh_1(o,v,...)		\
  hwa->o.config.outputh = HW_A1(_hw_ocb_voutputh_##v);	\
  _hwa_cfocb_koutputh_0(o,__VA_ARGS__)

#define _hwa_cfocb_koutputh_0(o,kw,...)				\
  HW_G2(_hwa_cfocb_koutputl,HW_IS(output_l,kw))(o,kw,__VA_ARGS__)


/*  Optionnal argument `output_l`
 */
/*								// COM	  PWM
 */
#define _hw_ocb_voutputl_disconnected	, 0	// 0,2,3  0,1
#define _hw_ocb_voutputl_clear_at_bottom_set_after_match	, 1	// 1	  1

#define _hwa_cfocb_koutputl_1(o,kw,v,...)				\
  HW_Y(_hwa_cfocb_voutputl_,_hw_ocb_voutputl_##v)(o,v,__VA_ARGS__)

#define _hwa_cfocb_voutputl_0(o,v,...)				\
  HW_E_AVL(output_l, v, disconnected | clear_at_bottom_set_after_match)

#define _hwa_cfocb_voutputl_1(o,v,...)			\
  hwa->o.config.outputl = HW_A1(_hw_ocb_voutputl_##v);	\
  _hwa_cfocb_koutputl_0(o,__VA_ARGS__)

#define _hwa_cfocb_koutputl_0(o,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ocb
 *
 * <br>
 * `write`:
 *
 * @code
 * hw( write, (counter0,compare0), value );
 * @endcode
 *
 * @code
 * hwa( write, (counter0,compare0), value );
 * @endcode
 *
 *
 * <br>
 * `read`:
 *
 * @code
 * uint8_t ocr = hw( read, (counter0,compare0) );
 * @endcode
 */
#define hw_write__ocb			, _hw_wrocb
#define _hw_wrocb(o,a,v,...)	_hw_write(o,reg,v) HW_EOL(__VA_ARGS__)

#define hwa_write__ocb		, _hwa_wrocb
#define _hwa_wrocb(o,a,v,...)	_hwa_write(o,reg,v) HW_EOL(__VA_ARGS__)

#define hw_read__ocb			, _hw_read_ocb
#define _hw_read_ocb(o,a,...)	_hw_read(o,reg) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ocb
 * @section atmelavr_ocb_st Status
 *
 * The compare event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, irqflag((counter0,compare0)) ) ) {	// Read compare IRQ flag
 *   hw( clear, irqflag((counter0,compare0)) );		// Clear compare IRQ flag
 *   hw( turn, irq((counter0,compare0)), off );		// Disable compare IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ocb(o,a)			\
  _hwa_setup_r( o, reg );			\
  hwa->o.config.outputh = 0xFF ;			\
  hwa->o.config.outputl = 0xFF ;


#define _hwa_init__ocb(o,a)			_hwa_init_r( o, reg, 0x00 );

#define _hwa_solve_ocb(o)						\
  if ( hwa->o.config.outputh != 0xFF || hwa->o.config.outputl != 0xFF ) {	\
  if ( hwa->o.config.outputl == HW_A1(_hw_ocb_voutputl_clear_at_bottom_set_after_match) ) { \
    if ( hwa->o.config.outputh != HW_A1(_hw_ocb_voutputh_set_at_bottom_clear_after_match) ) \
      HWA_ERR("`output_h` must be `set_at_bottom_clear_after_match` "	\
	      "when `output_l` is `clear_at_bottom_set_after_match`.");	\
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,1);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_disconnected) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,0);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_toggle_after_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,1);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_clear_after_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,2);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_set_after_match) ) { \
    _hwa_write(o,pwm,0);					\
    _hwa_write(o,mode,3);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_set_at_bottom_clear_after_match) ) { \
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,2);						\
  }									\
  else if ( hwa->o.config.outputh == HW_A1(_hw_ocb_voutputh_clear_at_bottom_set_after_match) ) { \
    _hwa_write(o,pwm,1);						\
    _hwa_write(o,mode,3);						\
  }									\
  if ( hwa->o.config.outputh != 0xFF && hwa->o.config.outputh != 0 )	\
    _hwa( configure, (o,pin_h), mode, digital_output );	\
  if ( hwa->o.config.outputl != 0xFF && hwa->o.config.outputl != 0 )	\
    _hwa( configure, (o,pin_l), mode, digital_output );	\
  }


#define _hwa_commit__ocb(o,a)		_hwa_commit_r(o,reg);


/**
 * @page atmelavr_ocb
 * <br>
 */
