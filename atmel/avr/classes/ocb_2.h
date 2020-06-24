
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @addtogroup atmelavr_ocb
 * @section atmelavr_ocbact Actions
 *
 * <br><br>hwa( configure, ... ):
 *
 * @code
 * hwa( configure, (counter1,compare0),
 *
 *    [ update,	    after_top, ]			// Default, no other choice
 *
 *  [	output
 *    | output_h,   disconnected			// Default
 *		  | toggle_after_match
 *		  | clear_after_match
 *		  | set_after_match
 *		  | set_at_bottom_clear_after_match
 *		  | clear_at_bottom_set_after_match, ]
 *
 *    [ output_l,   disconnected			// Default
 *		  | clear_at_bottom_set_after_match ]
 * );
 * @endcode
 */
#define hwa_configure__ocb		, _hwa_cfocb


/*  Optionnal argument `update`
 *
 *    Add a second void argument to the end of the list so that there are always
 *    at least 2 arguments following the last non-void argument.
 */
#define _hwa_cfocb(o,ct,oc,k,...)					\
  do {									\
    HW_B(_hwa_cfocb_kupdate_,_hw_is_update_##k)(ct,oc,k,__VA_ARGS__,)	\
      } while(0)

#define _hwa_cfocb_kupdate_1(ct,oc,kw,v,...)				\
  HW_G2(_hwa_cfocb_vupdate,HW_IS(after_top,v))(ct,oc,v,__VA_ARGS__)

#define _hwa_cfocb_vupdate_0(ct,oc,v,...)				\
  HW_E(HW_EM_VAL(v,update,(after_top)))

#define _hwa_cfocb_vupdate_1(ct,oc,v,...)		\
  _hwa_cfocb_kupdate_0(ct,oc,__VA_ARGS__)

#define _hwa_cfocb_kupdate_0(ct,oc,kw,...)					\
  HW_B(_hwa_cfocb_koutputh_,_hw_ocb_koutputh_##kw)(ct,oc,kw,__VA_ARGS__)


/*  Optionnal argument `output` (or `output_h`)
 */
#define _hw_ocb_koutputh_output					, 1
#define _hw_ocb_koutputh_output_h				, 1

/*									// COM	PWM
 */
#define _hw_ocb_voutputh_disconnected				, 0	// 0	0
#define _hw_ocb_voutputh_toggle_after_match			, 1	// 1	0
#define _hw_ocb_voutputh_clear_after_match			, 2	// 2	0
#define _hw_ocb_voutputh_set_after_match			, 3	// 3	0
#define _hw_ocb_voutputh_set_at_bottom_clear_after_match	, 4	// 1,2	1
#define _hw_ocb_voutputh_clear_at_bottom_set_after_match	, 5	// 3	1


#define _hwa_cfocb_koutputh_1(ct,oc,kw,v,...)				\
  HW_B(_hwa_cfocb_voutputh_,_hw_ocb_voutputh_##v)(ct,oc,v,__VA_ARGS__)

#define _hwa_cfocb_voutputh_0(ct,oc,v,...)					\
  HW_E(HW_EM_VAL(v,output,(disconnected,toggle_after_match,clear_after_match,set_after_match,set_at_bottom_clear_after_match,clear_at_bottom_set_after_match)))

#define _hwa_cfocb_voutputh_1(ct,oc,v,...)		\
  hwa->ct.compare##oc.config.outputh = HW_A1(_hw_ocb_voutputh_##v);	\
  _hwa_cfocb_koutputh_0(ct,oc,__VA_ARGS__)

#define _hwa_cfocb_koutputh_0(ct,oc,kw,...)				\
  HW_G2(_hwa_cfocb_koutputl,HW_IS(output_l,kw))(ct,oc,kw,__VA_ARGS__)


/*  Optionnal argument `output_l`
 */
/*									// COM	  PWM
 */
#define _hw_ocb_voutputl_disconnected				, 0	// 0,2,3  0,1
#define _hw_ocb_voutputl_clear_at_bottom_set_after_match	, 1	// 1	  1

#define _hwa_cfocb_koutputl_1(ct,oc,kw,v,...)				\
  HW_B(_hwa_cfocb_voutputl_,_hw_ocb_voutputl_##v)(ct,oc,v,__VA_ARGS__)

#define _hwa_cfocb_voutputl_0(ct,oc,v,...)				\
  HW_E(HW_EM_VAL( v,output_l,(disconnected,clear_at_bottom_set_after_match)))

#define _hwa_cfocb_voutputl_1(ct,oc,v,...)			\
  hwa->ct.compare##oc.config.outputl = HW_A1(_hw_ocb_voutputl_##v);	\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfocb_koutputl_0(ct,oc,...)		\
  HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ocb
 *
 * <br><br>hw( read, ... ): get the compare value
 *
 * @code
 * uint8_t ocr = hw( read, (counter0,compare0) );
 * @endcode
 *
 * <br><br>hw( write, ... ), hwa( write, ... ): set the compare value
 *
 * @code
 * hw( write, (counter0,compare0), value );
 * @endcode
 *
 * @code
 * hwa( write, (counter0,compare0), value );
 * @endcode
 */
#define hw_write__ocb			, _hw_write_ocb
#define _hw_write_ocb(o,ct,oc,v,...)	_hw_write(ct,ocr##oc,v) HW_EOL(__VA_ARGS__)

#define hwa_write__ocb			, _hwa_write_ocb
#define _hwa_write_ocb(o,ct,oc,v,...)	_hwa_write(ct,ocr##oc,v) HW_EOL(__VA_ARGS__)

#define hw_read__ocb			, _hw_read_ocb
#define _hw_read_ocb(o,ct,oc,...)	_hw_read(ct,ocr##oc) HW_EOL(__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_solve_ocb(counter,oc)					\
  if ( hwa->counter.compare##oc.config.outputh != 0xFF || hwa->counter.compare##oc.config.outputl != 0xFF ) { \
    if ( hwa->counter.compare##oc.config.outputl == HW_A1(_hw_ocb_voutputl_clear_at_bottom_set_after_match) ) { \
      if ( hwa->counter.compare##oc.config.outputh != HW_A1(_hw_ocb_voutputh_set_at_bottom_clear_after_match) ) \
	HWA_E(HW_EM_3((o,oc)));					\
      _hwa_write(counter,pwm##oc,1);					\
      _hwa_write(counter,com##oc,1);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_disconnected) ) { \
      _hwa_write(counter,pwm##oc,0);					\
      _hwa_write(counter,com##oc,0);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_toggle_after_match) ) { \
      _hwa_write(counter,pwm##oc,0);					\
      _hwa_write(counter,com##oc,1);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_clear_after_match) ) { \
      _hwa_write(counter,pwm##oc,0);					\
      _hwa_write(counter,com##oc,2);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_set_after_match) ) { \
      _hwa_write(counter,pwm##oc,0);					\
      _hwa_write(counter,com##oc,3);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_set_at_bottom_clear_after_match) ) { \
      _hwa_write(counter,pwm##oc,1);					\
      _hwa_write(counter,com##oc,2);					\
    }									\
    else if ( hwa->counter.compare##oc.config.outputh == HW_A1(_hw_ocb_voutputh_clear_at_bottom_set_after_match) ) { \
      _hwa_write(counter,pwm##oc,1);					\
      _hwa_write(counter,com##oc,3);					\
    }									\
    if ( hwa->counter.compare##oc.config.outputh != 0xFF && hwa->counter.compare##oc.config.outputh != 0 ) \
      _hwa( configure, (counter,compare##oc##_pin_h), mode, digital_output ); \
    if ( hwa->counter.compare##oc.config.outputl != 0xFF && hwa->counter.compare##oc.config.outputl != 0 ) \
      _hwa( configure, (counter,compare##oc##_pin_l), mode, digital_output ); \
  }


/**
 * @addtogroup atmelavr_ocb
 * @section atmelavr_ocbreg Registers
 *
 * Registers are hold by the parent counter.
 */
