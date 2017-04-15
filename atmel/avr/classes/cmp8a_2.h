
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_cmp8a
 * @section atmelavr_cmp8a_config Configuration
 * @subsection atmelavr_cmp8a_cf1 Synchronous
 *
 * The hw_config() instruction only permits to change the behavior of the output
 * pin and does not perform any verification against the counter configuration:
 *
 * @code
 * hw( configure, compare0,
 *
 *	      //  Behavior of the ouput pin
 *	      //
 *	      output,	disconnected
 *		      | toggle_on_match
 *		      | clear_on_match
 *		      | set_on_match
 *		      | set_at_bottom_clear_on_match
 *		      | clear_at_bottom_set_on_match
 *		      | clear_on_match_up_set_on_match_down
 *		      | set_on_match_up_clear_on_match_down
 *	     );
 * @endcode
 */
#define _hw_mthd_hw_configure__cmp8a	, _hw_cfcmp8a

/*  Mandatory parameter `output`
 */
#define _hw_is_output_output		, 1

#define _hw_cmp8a_output_disconnected	, 0, 0	/* code, COM */ /* Non-PWM */
#define _hw_cmp8a_output_toggle_on_match	, 1, 1			/* Non-PWM */
#define _hw_cmp8a_output_clear_on_match	, 2, 2			/* Non-PWM */
#define _hw_cmp8a_output_set_on_match	, 3, 3			/* Non-PWM */

#define _hw_cmp8a_output_set_at_bottom_clear_on_match	, 4, 2			/* Fast PWM */
#define _hw_cmp8a_output_clear_at_bottom_set_on_match	, 5, 3

#define _hw_cmp8a_output_clear_on_match_up_set_on_match_down	, 6, 2	/* Phase correct PWM */
#define _hw_cmp8a_output_set_on_match_up_clear_on_match_down	, 7, 3

//#define _hw_is_disconnected_disconnected	, 1

#define _hw_cfcmp8a(o,i,a, ...)						\
  do {									\
    HW_X(_hw_cfcmp8a_koutput,_hw_is_output_##__VA_ARGS__)(o,__VA_ARGS__,,);	\
  }while(0)

#define _hw_cfcmp8a_koutput_0(o,k,...)		\
  HW_E_VL(k,output)
#define _hw_cfcmp8a_koutput_1(o,k,v,...)					\
  HW_X(_hw_cfcmp8a_voutput,_hw_cmp8a_output_##v)(o,v,__VA_ARGS__)
#define _hw_cfcmp8a_voutput_0(o,v,...)					\
  HW_E_AVL(mode of `o`, v, `disconnected | toggle_on_match | clear_on_match | set_on_match | set_at_bottom_clear_on_match | clear_at_bottom_set_on_match | clear_on_match_up_set_on_match_down | set_on_match_up_clear_on_match_down`)
#define _hw_cfcmp8a_voutput_1(o,v,...)					\
  HW_TX(_hw_write_reg(o, com, HW_A2(_hw_cmp8a_output_##v)),__VA_ARGS__)


/**
 * @page atmelavr_cmp8a
 * @subsection atmelavr_cmp8a_cf2 Asynchronous
 *
 * The `hwa(configure,...)` instruction allows the `update` parameter to be set. It
 * tells when the compare value is transferred from the latch register to the
 * compare register. This is used to complete and check the configuration of the
 * related counter when the hwa_commit() instruction is encountered:
 *
 * @code
 * hwa( configure, compare0,
 *
 *	       //  When the content of the compare register is latched
 *	       //
 *	     [ update,	 at_bottom
 *		       | at_top
 *		       | at_max,   ]
 *
 *	       //  Behavior of the ouput pin
 *	       //
 *	     [ output,	 disconnected
 *		       | toggle_on_match
 *		       | clear_on_match
 *		       | set_on_match
 *		       | set_at_bottom_clear_on_match
 *		       | clear_at_bottom_set_on_match
 *		       | clear_on_match_up_set_on_match_down
 *		       | set_on_match_up_clear_on_match_down ]
 *	      );
 * @endcode
 */
#define _hw_mthd_hwa_configure__cmp8a	, _hwa_cfcmp8a

/*  Optionnal parameter `update`
 */
#define _hw_is_update_update		, 1

#define _hw_cmp8a_update_immediately	, 0
#define _hw_cmp8a_update_at_bottom	, 1
#define _hw_cmp8a_update_at_top		, 2

#define _hwa_cfcmp8a(o,i,a,...)						\
  do {									\
    HW_X(_hwa_cfcmp8a_kupdate,_hw_is_update_##__VA_ARGS__)(o,__VA_ARGS__,); \
  }while(0)

#define _hwa_cfcmp8a_kupdate_0(o,k,...)				\
  HW_X(_hwa_cfcmp8a_koutput,_hw_is_output_##k)(o,k,__VA_ARGS__)

#define _hwa_cfcmp8a_kupdate_1(o,k,v,...)				\
  HW_X(_hwa_cfcmp8a_vupdate,_hw_cmp8a_update_##v)(o,v,__VA_ARGS__)
#define _hwa_cfcmp8a_vupdate_0(o,v,...)		\
  HW_E_AVL(update mode of `o`, v, `immediately | at_bottom | at_top`)

#define _hwa_cfcmp8a_vupdate_1(o,v,k,...)			\
  hwa->o.config.update = HW_A1(_hw_cmp8a_update_##v);		\
  HW_X(_hwa_cfcmp8a_koutput,_hw_is_output_##k)(o,k,__VA_ARGS__)

/*  Optionnal parameter `output`
 */
#define _hwa_cfcmp8a_koutput_0(o,...)		\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfcmp8a_koutput_1(o,k,v,...)					\
  HW_X(_hwa_cfcmp8a_voutput,_hw_cmp8a_output_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcmp8a_voutput_0(o,v,...)			\
  HW_E_AVL(mode of `o`, v, `disconnected | toggle_on_match | clear_on_match | set_on_match | set_at_bottom_clear_on_match | clear_at_bottom_set_on_match | clear_on_match_up_set_on_match_down | set_on_match_up_clear_on_match_down`)
#define _hwa_cfcmp8a_voutput_1(o,v,...)					\
  HW_TX(hwa->o.config.output = HW_A1(_hw_cmp8a_output_##v),__VA_ARGS__)


/**
 * @page atmelavr_cmp8a
 * @section atmelavr_cmp8a_ocr Compare value
 *
 * The compare value is set using the hw_write() or hwa_write() instruction:
 *
 * @code
 * hw_write( compare0, value );
 * @endcode
 */
#define _hw_mthd_hw_write__cmp8a	, _hw_write_cmp8a
#define _hw_write_cmp8a(o,i,a,v,...)		HW_TX(_hw_write_reg(o,reg,v),__VA_ARGS__)


/**
 * @page atmelavr_cmp8a
 *
 * @code
 * hwa_write( compare0, value );
 * @endcode
 */
#define _hw_mthd_hwa_write__cmp8a	, _hwa_write_cmp8a
#define _hwa_write_cmp8a(o,i,a,v,...)		HW_TX(_hwa_write_reg(o,reg,v),__VA_ARGS__)


/**
 * @page atmelavr_cmp8a
 *
 * The compare value is read using the`read`instruction:
 *
 * @code
 * uint16_t ocr = hw( read, compare0 );
 * @endcode
 */
#define _hw_mthd_hw_read__cmp8a		, _hw_read_cmp8a
#define _hw_read_cmp8a(o,i,a,...)		HW_TX(_hw_read_reg(o,reg),__VA_ARGS__)


/**
 * @page atmelavr_cmp8a
 * @section atmelavr_cmp8a_trigger Compare event
 *
 * The hw_trigger() or hwa_trigger() instructions trigger a compare event:
 *
 * @code
 * hw_trigger( compare0 );
 * @endcode
 */
#define _hw_mthd_hw_trigger__cmp8a	, _hw_trigger_cmp8a
#define _hw_trigger_cmp8a(o,i,a)			_hw_write_reg(o,force,1)

/**
 * @page atmelavr_cmp8a
 *
 * @code
 * hwa_trigger( compare0 );
 * @endcode
 */
#define _hw_mthd_hwa_trigger__cmp8a	, _hwa_trigger_cmp8a
#define _hwa_trigger_cmp8a(o,i,a)		_hwa_write_reg(o,force,1)


/**
 * @page atmelavr_cmp8a
 * @section atmelavr_cmp8a_st Status
 *
 * The compare event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( compare0 ) ) ) {	// Read compare IRQ flag
 *   hw( clear, HW_IRQFLAG( compare0 ) );		// Clear compare IRQ flag
 *   hw( turn, HW_IRQ( compare0, off ) );		// Disable compare IRQs
 * }
 * @endcode
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__cmp8a(o,i,a)			\
  _hwa_setup_reg( o, reg );			\
  hwa->o.config.update	= 0xFF ;		\
  hwa->o.config.output	= 0xFF ;

#define _hwa_init__cmp8a(o,i,a)			_hwa_init_reg( o, reg, 0x00 )

#define _hwa_commit__cmp8a(o,i,a)		_hwa_commit_reg( o, reg )


/**
 * @page atmelavr_cmp8a
 * <br>
 */
