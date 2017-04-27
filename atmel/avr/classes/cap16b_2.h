
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_cap16b
 * @section atmelavr_cap16b_config Configuration
 * @subsection atmelavr_cap16b_cf1 Synchronous
 *
 * __Note__ Currently, only `edge` configuration is implemented for the synchronous
 * method.
 *
 * @code
 * hw( configure, capture0,
 *
 *	      input,	pin_icp,     // NOT IMPLEMENTED YET
 *
 *	     [edge,	falling
 *		      | rising, ]
 *
 *	     [filter,	on	     // NOT IMPLEMENTED YET
 *		      | off ]
 *	     );
 * @endcode
 */
#define _hw_mtd_hw_configure__cap16b	, _hw_cfcap16b

#define hw_cap16b_input_pin_icp			, 1
#define hw_cap16b_input_acmp0			, 2

#define hw_cap16b_edge_falling			, 1
#define hw_cap16b_edge_rising			, 2

#define _hw_cfcap16b_kw_edge		, _hw_cfcap16b_edge
//#define _hw_cfcap16b_kw_		, _hw_cfcap16b_

#define _hw_cfcap16b(o,i,a,...)						\
  HW_X(_hw_cfcap16bkw1,_hw_cfcap16b_kw_##__VA_ARGS__)(o,__VA_ARGS__,)

#define _hw_cfcap16bkw1_0(o,kw,...)					\
  HW_E_VL(k,input | edge | filter)

#define _hw_cfcap16bkw1_1(o,kw,...)		\
  HW_A1(_hw_cfcap16b_kw_##kw)(o,__VA_ARGS__)

#define _hw_cfcap16b_edge(o,v,...)					\
  HW_X(_hw_cfcap16b_vedge,hw_cap16b_edge_##v)(o,v,__VA_ARGS__)
#define _hw_cfcap16b_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)
#define _hw_cfcap16b_vedge_1(o,v,...)			\
  HW_TX(_hw_write_reg(o, ices, HW_A1(hw_cap16b_edge_##v)-1),__VA_ARGS__)


/**
 * @page atmelavr_cap16b
 * @subsection atmelavr_cap16b_cf2 Asynchronous
 * @code
 * hwa( configure, capture0,
 *
 *	       input,	 pin_icp,
 *
 *	       edge,	 falling
 *		       | rising,
 *
 *	     [ filter,	 on
 *		       | off ]
 *	     );
 * @endcode
 */
#define _hw_mtd_hwa_configure__cap16b	, _hwa_cfcap16b

#define _hwa_cfcap16b(o,i,a,...)						\
  do {									\
    HW_X(_hwa_cfcap16b_kinput,_hw_is_input_##__VA_ARGS__)(o,__VA_ARGS__,,) \
      } while(0)

#define _hwa_cfcap16b_kinput_0(o,k,...)					\
  HW_E_VL(k,input)

#define _hwa_cfcap16b_kinput_1(o,k,v,...)				\
  HW_X(_hwa_cfcap16b_vinput,hw_cap16b_input_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcap16b_vinput_0(o,v,...)					\
  HW_E_AVL(`input`, v, `pin_icp`)

#define _hwa_cfcap16b_vinput_1(o,v,k,...)				\
  hwa->o.config.input = HW_A1(hw_cap16b_input_##v);			\
  HW_X(_hwa_cfcap16b_kedge,_hw_is_edge_##k)(o,k,__VA_ARGS__)

#define _hwa_cfcap16b_kedge_0(o,k,...)					\
  HW_E_VL(k,edge)

#define _hwa_cfcap16b_kedge_1(o,k,v,...)				\
  HW_X(_hwa_cfcap16b_vedge,hw_cap16b_edge_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcap16b_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)

#define _hwa_cfcap16b_vedge_1(o,v,k,...)				\
  hwa->o.config.edge = HW_A1(hw_cap16b_edge_##v);				\
  HW_X(_hwa_cfcap16b_kfilter,_hw_is_filter_##k)(o,k,__VA_ARGS__)

#define _hwa_cfcap16b_kfilter_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfcap16b_kfilter_1(o,k,v,...)				\
  HW_X(_hwa_cfcap16b_vfilter,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcap16b_vfilter_0(o,v,...)					\
  HW_E_OAVL(filter, v, on | off)

#define _hwa_cfcap16b_vfilter_1(o,v,...)		\
  hwa->o.config.filter = HW_A1(_hw_state_##v);		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cap16b
 * @section atmelavr_cap16b_read Capture value
 *
 * @code
 * uint16_t capture = hw( read, capture0 );
 * @endcode
 */
#define _hw_mtd_hw_read__cap16b	, _hw_read_cap16a


/**
 * @page atmelavr_cap16b
 *
 * @code
 * hw_write( capture0, value );
 * @endcode
 */
#define _hw_mtd_hw_write__cap16b	, _hw_write_cap16a

/**
 * @page atmelavr_cap16b
 *
 * @code
 * hwa_write( capture0, value );
 * @endcode
 */
#define _hw_mtd_hwa_write__cap16b	, _hwa_write_cap16a


/**
 * @page atmelavr_cap16b
 * @section atmelavr_cap16b_st Status
 *
 * The capture event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( capture0 ) ) ) {	// Read capture IRQ flag
 *   hw( clear, HW_IRQFLAG( capture0 ) );		// Clear capture IRQ flag
 *   hw( turn, HW_IRQ( capture0, off ) );		// Disable capture IRQs
 * }
 * @endcode
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__cap16b		_hwa_setup__cap16a
#define _hwa_init__cap16b		_hwa_init__cap16a
#define _hwa_commit__cap16b		_hwa_commit__cap16a


/**
 * @page atmelavr_cap16b
 * <br>
 */
