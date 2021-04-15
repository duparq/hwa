
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit compare unit with waveform generator
 */

/**
 * @addtogroup atmelavr_oca
 * @section atmelavr_ocaact Actions
 *
 * <br><br>hw( configure, ... ) only permits to change the behavior of the output
 * pin and does not perform any verification against the counter configuration:
 *
 * @code
 * hw( configure, (counter0,compare0),
 *
 *     //  Behavior of the ouput pin
 *     //
 *     output,	  disconnected
 *		| toggle_after_match
 *		| clear_after_match
 *		| set_after_match
 *		| set_at_bottom_clear_after_match
 *		| clear_at_bottom_set_after_match
 *		| clear_after_match_up_set_after_match_down
 *		| set_after_match_up_clear_after_match_down
 * );
 * @endcode
 */
#define hw_configure__oca		, _hw_cfoca

/*  Mandatory parameter `output`
 */
#define _hw_oca_output_disconnected					, 0, 0	/* code, COM */ /* Non-PWM */
#define _hw_oca_output_toggle_after_match				, 1, 1			/* Non-PWM */
#define _hw_oca_output_clear_after_match				, 2, 2			/* Non-PWM */
#define _hw_oca_output_set_after_match					, 3, 3			/* Non-PWM */

#define _hw_oca_output_set_at_bottom_clear_after_match			, 4, 2			/* Fast PWM */
#define _hw_oca_output_clear_at_bottom_set_after_match			, 5, 3

#define _hw_oca_output_clear_after_match_up_set_after_match_down	, 6, 2	/* Phase correct PWM */
#define _hw_oca_output_set_after_match_up_clear_after_match_down	, 7, 3

#define _hw_cfoca(o,ct,oc,k,...)					\
  do {									\
    HW_B(_hw_cfoca_koutput_,_hw_is_output_##k)(ct,oc,k,__VA_ARGS__,,);	\
  }while(0)

#define _hw_cfoca_koutput_0(ct,oc,k,...)		\
  HW_E(HW_EM_AN(k,output))
#define _hw_cfoca_koutput_1(ct,oc,k,v,...)					\
  HW_B(_hw_cfoca_voutput_,_hw_oca_output_##v)(ct,oc,v,__VA_ARGS__)
#define _hw_cfoca_voutput_0(ct,oc,v,...)					\
  HW_E(HW_EM_VAL(v,output,(disconnected,toggle_after_match,clear_after_match,set_after_match,set_at_bottom_clear_after_match,clear_at_bottom_set_after_match,clear_after_match_up_set_after_match_down,set_after_match_up_clear_after_match_down)))
#define _hw_cfoca_voutput_1(ct,oc,v,...)					\
  _hw_write(ct, com##oc, HW_A2(_hw_oca_output_##v)) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_oca
 *
 * <br><br>hwa( configure, ... ) allows the `update` parameter to be set. It
 * tells when the compare value is transferred from the latch register to the
 * compare register. This is used to complete and check the configuration of the
 * related counter when the hwa(commit) instruction is encountered:
 *
 * @code
 * hwa( configure, (counter0,compare0),
 *
 *	//  When the content of the compare register is latched
 *	//
 *    [ update,	   after_bottom
 *		 | after_top
 *		 | after_max,	]
 *
 *	//  Behavior of the ouput pin
 *	//
 *    [ output,	   disconnected
 *		 | toggle_after_match
 *		 | clear_after_match
 *		 | set_after_match
 *		 | set_at_bottom_clear_after_match
 *		 | clear_at_bottom_set_after_match
 *		 | clear_after_match_up_set_after_match_down
 *		 | set_after_match_up_clear_after_match_down ]
 * );
 * @endcode
 */
#define hwa_configure__oca		, _hwa_cfoca

/*  Optionnal parameter `update`
 */
#define _hw_oca_update_immediately	, 0
#define _hw_oca_update_after_bottom	, 1
#define _hw_oca_update_after_top	, 2

#define _hwa_cfoca(o,ct,oc,k,...)						\
  do {									\
    HW_B(_hwa_cfoca_kupdate_,_hw_is_update_##k)(ct,oc,k,__VA_ARGS__,);	\
  }while(0)

#define _hwa_cfoca_kupdate_0(ct,oc,k,...)				\
  HW_B(_hwa_cfoca_koutput_,_hw_is_output_##k)(ct,oc,k,__VA_ARGS__)

#define _hwa_cfoca_kupdate_1(ct,oc,k,v,...)				\
  HW_B(_hwa_cfoca_vupdate_,_hw_oca_update_##v)(ct,oc,v,__VA_ARGS__)
#define _hwa_cfoca_vupdate_0(ct,oc,v,...)		\
  HW_E(HW_EM_VAL(v,update,(immediately,after_bottom,after_top)))

#define _hwa_cfoca_vupdate_1(ct,oc,v,k,...)			\
  hwa->ct.compare##oc.config.update = HW_A1(_hw_oca_update_##v);	\
  HW_B(_hwa_cfoca_koutput_,_hw_is_output_##k)(ct,oc,k,__VA_ARGS__)

/*  Optionnal parameter `output`
 */
#define _hwa_cfoca_koutput_0(ct,oc,...)		\
   HW_EOL(__VA_ARGS__)

#define _hwa_cfoca_koutput_1(ct,oc,k,v,...)					\
  HW_B(_hwa_cfoca_voutput_,_hw_oca_output_##v)(ct,oc,v,__VA_ARGS__)

#define _hwa_cfoca_voutput_0(ct,oc,v,...)			\
  HW_E(HW_EM_VAL(v,output,(disconnected,toggle_after_match,clear_after_match,set_after_match,set_at_bottom_clear_after_match,clear_at_bottom_set_after_match,clear_after_match_up_set_after_match_down,set_after_match_up_clear_after_match_down)))
#define _hwa_cfoca_voutput_1(ct,oc,v,...)					\
  hwa->ct.compare##oc.config.output = HW_A1(_hw_oca_output_##v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_oca
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
#define hw_read__oca			, _hw_read_oca
#define _hw_read_oca(o,ct,oc,...)	_hw_read(ct,ocr##oc) HW_EOL(__VA_ARGS__)

#define hw_write__oca			, _hw_write_oca
#define _hw_write_oca(o,ct,oc,v,...)	_hw_write(ct,ocr##oc,v) HW_EOL(__VA_ARGS__)

#define hwa_write__oca			, _hwa_write_oca
#define _hwa_write_oca(o,ct,oc,v,...)	_hwa_write(ct,ocr##oc,v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_oca
 *
 * <br><br>hw( trigger, ... ), hwa( trigger, ... ): force a compare-match
 *
 * @code
 * hw( trigger, (counter0,compare0) );
 * @endcode
 *
 * @code
 * hwa( trigger, (counter0,compare0) );
 * @endcode
 */
#define hw_trigger__oca			, _hw_trigger_oca
#define _hw_trigger_oca(o,ct,oc)	_hw_write(ct,foc##oc,1)

#define hwa_trigger__oca		, _hwa_trigger_oca
#define _hwa_trigger_oca(o,ct,oc)	_hwa_write(ct,foc##oc,1)


/**
 * @addtogroup atmelavr_oca
 * @section atmelavr_ocareg Registers
 *
 * Registers are hold by the parent counter.
 */
