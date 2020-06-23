
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_icb
 * @section atmelavr_icb_act Actions
 *
 * <br>
 * `configure`:
 *
 * __Note__ Currently, only `edge` configuration is implemented for the synchronous
 * method.
 *
 * @code
 * hw( configure,   capture0,
 *
 *     input,       pin_icp,     // NOT IMPLEMENTED YET
 *
 *   [ edge,        falling
 *                | rising, ]
 *
 *   [ filter,      on           // NOT IMPLEMENTED YET
 *                | off ]
 *   );
 * @endcode
 */
#define hw_configure__icb		, _hw_cficb

#define hw_icb_input_pin_icp		, 1
#define hw_icb_input_acmp0		, 2

#define hw_icb_edge_falling		, 1
#define hw_icb_edge_rising		, 2

#define _hw_cficb_kw_edge		, _hw_cficb_edge
//#define _hw_cficb_kw_			, _hw_cficb_

#define _hw_cficb(o,a,k,...)					\
  HW_B(_hw_cficbkw1_,_hw_cficb_kw_##k)(o,k,__VA_ARGS__,)

#define _hw_cficbkw1_0(o,kw,...)					\
  HW_E_VL(k,input | edge | filter)

#define _hw_cficbkw1_1(o,kw,...)		\
  HW_A1(_hw_cficb_kw_##kw)(o,__VA_ARGS__)

#define _hw_cficb_edge(o,v,...)					\
  HW_B(_hw_cficb_vedge_,hw_icb_edge_##v)(o,v,__VA_ARGS__)
#define _hw_cficb_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)
#define _hw_cficb_vedge_1(o,v,...)			\
  _hw_write(o, ices, HW_A1(hw_icb_edge_##v)-1) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_icb
 *
 * @code
 * hwa( configure,   capture0,
 *
 *      input,       pin_icp,
 *
 *    [ edge,        falling
 *                 | rising, ]
 *
 *    [ filter,      on
 *                 | off ] );
 * @endcode
 */
#define hwa_configure__icb		, _hwa_cficb

#define _hwa_cficb(o,a,k,...)					\
  do { HW_B(_hwa_cficb_kinput_,_hw_is_input_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cficb_kinput_0(o,k,...)					\
  HW_E_VL(k,input)

#define _hwa_cficb_kinput_1(o,k,v,...)				\
  HW_B(_hwa_cficb_vinput_,hw_icb_input_##v)(o,v,__VA_ARGS__)

#define _hwa_cficb_vinput_0(o,v,...)					\
  HW_E_AVL(`input`, v, `pin_icp`)

#define _hwa_cficb_vinput_1(o,v,k,...)				\
  hwa->o.config.input = HW_A1(hw_icb_input_##v);			\
  HW_B(_hwa_cficb_kedge_,_hw_is_edge_##k)(o,k,__VA_ARGS__)

#define _hwa_cficb_kedge_0(o,k,...)					\
  HW_E_VL(k,edge)

#define _hwa_cficb_kedge_1(o,k,v,...)				\
  HW_B(_hwa_cficb_vedge_,hw_icb_edge_##v)(o,v,__VA_ARGS__)

#define _hwa_cficb_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)

#define _hwa_cficb_vedge_1(o,v,k,...)				\
  hwa->o.config.edge = HW_A1(hw_icb_edge_##v);				\
  HW_B(_hwa_cficb_kfilter_,_hw_is_filter_##k)(o,k,__VA_ARGS__)

#define _hwa_cficb_kfilter_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cficb_kfilter_1(o,k,v,...)				\
  HW_B(_hwa_cficb_vfilter_,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cficb_vfilter_0(o,v,...)					\
  HW_E_OAVL(filter, v, on | off)

#define _hwa_cficb_vfilter_1(o,v,...)		\
  hwa->o.config.filter = HW_A1(_hw_state_##v);		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_icb
 *
 * <br>
 * `read`:
 *
 * @code
 * uint16_t capture = hw( read, capture0 );
 * @endcode
 */
#define hw_read__icb			, _hw_read_ica


/**
 * @page atmelavr_icb
 *
 * <br>
 * `write`:
 *
 * @code
 * hw( write, capture0, value );
 * @endcode
 */
#define hw_write__icb		, _hw_write_ica

/**
 * @page atmelavr_icb
 *
 * @code
 * hwa( write, capture0, value );
 * @endcode
 */
#define hwa_write__icb		, _hwa_write_ica


/**
 * @page atmelavr_icb
 * @section atmelavr_icb_st Status
 *
 * The capture event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read,(counter0,capture0,irq) ) ) {	   // Read capture IRQ flag
 *   hw( clear,(counter0,capture0,irq) );		   // Clear capture IRQ flag
 *   hw( disable,(counter0,capture0,irq) );		   // Disable capture IRQs
 * }
 * @endcode
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__icb		_hwa_setup__ica
#define _hwa_init__icb		_hwa_init__ica
#define _hwa_commit__icb		_hwa_commit__ica
