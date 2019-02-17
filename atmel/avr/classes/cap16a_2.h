
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_cap16a
 * @section atmelavr_cap16a_config Configuration
 *
 * @code
 * hw( configure, counter0capture0,
 *
 *   [ input,     pin_icp      // NOT IMPLEMENTED YET
 *              | acmp0, ]
 *
 *   [ edge,      falling
 *              | rising, ]
 *
 *   [ filter,    on           // NOT IMPLEMENTED YET
 *              | off ] );
 * @endcode
 */
/*  TODO: complete this.
 */
#define hw_configure__cap16a	, _hw_cfcap16a

#define hw_cap16a_input_pin_icp			, 1
#define hw_cap16a_input_acmp0			, 2

#define hw_cap16a_edge_falling			, 1
#define hw_cap16a_edge_rising			, 2

#define _hw_cfcap16a_kw_edge		, _hw_cfcap16a_edge
//#define _hw_cfcap16a_kw_		, _hw_cfcap16a_

#define _hw_cfcap16a(o,i,a,k,...)					\
  HW_Y(_hw_cfcap16akw1_,_hw_cfcap16a_kw_##k)(o,k,__VA_ARGS__,)

#define _hw_cfcap16akw1_0(o,kw,...)					\
  HW_E_VL(k,input | edge | filter)

#define _hw_cfcap16akw1_1(o,kw,...)		\
  HW_A1(_hw_cfcap16a_kw_##kw)(o,__VA_ARGS__)

#define _hw_cfcap16a_edge(o,v,...)					\
  HW_Y(_hw_cfcap16a_vedge_,hw_cap16a_edge_##v)(o,v,__VA_ARGS__)
#define _hw_cfcap16a_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)
#define _hw_cfcap16a_vedge_1(o,v,...)			\
  _hw_write(o, ices, HW_A1(hw_cap16a_edge_##v)-1) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cap16a
 * @code
 * hwa( configure, counter0capture0,
 *
 *    [ input,     pin_icp
 *               | acmp0, ]
 *
 *    [ edge,      falling
 *               | rising, ]
 *
 *    [ filter,    on
 *               | off ] );
 * @endcode
 */
#define hwa_configure__cap16a		, _hwa_cfcap16a

#define _hwa_cfcap16a(o,i,a,k,...) \
  do { HW_Y(_hwa_cfcap16a_kinput_,_hw_is_input_##k)(o,k,__VA_ARGS__) } while(0)

#define _hwa_cfcap16a_kinput_0(o,k,...)		\
  HW_Y(_hwa_cfcap16a_kedge_,_hw_is_edge_##k)(o,k,__VA_ARGS__) //HW_E_VL(k,input)
#define _hwa_cfcap16a_kinput_1(o,k,v,...)	HW_Y(_hwa_cfcap16a_vinput_,hw_cap16a_input_##v)(o,v,__VA_ARGS__)
#define _hwa_cfcap16a_vinput_0(o,v,...)		HW_E_AVL(input, v, pin_icp | acmp0)
#define _hwa_cfcap16a_vinput_1(o,v,k,...)				\
  hwa->o.config.input = HW_A1(hw_cap16a_input_##v);			\
  HW_Y(_hwa_cfcap16a_kedge_,_hw_is_edge_##k)(o,k,__VA_ARGS__)

#define _hwa_cfcap16a_kedge_0(o,k,...)					\
  HW_Y(_hwa_cfcap16a_kfilter_,_hw_is_filter_##k)(o,k,__VA_ARGS__) //  HW_E_VL(k,edge)

#define _hwa_cfcap16a_kedge_1(o,k,v,...)				\
  HW_Y(_hwa_cfcap16a_vedge_,hw_cap16a_edge_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcap16a_vedge_0(o,v,...)					\
  HW_E_AVL(edge, v, falling | rising)

#define _hwa_cfcap16a_vedge_1(o,v,k,...)				\
  hwa->o.config.edge = HW_A1(hw_cap16a_edge_##v);				\
  HW_Y(_hwa_cfcap16a_kfilter_,_hw_is_filter_##k)(o,k,__VA_ARGS__)

#define _hwa_cfcap16a_kfilter_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfcap16a_kfilter_1(o,k,v,...)				\
  HW_Y(_hwa_cfcap16a_vfilter_,_hw_state_##v)(o,v,__VA_ARGS__)

#define _hwa_cfcap16a_vfilter_0(o,v,...)					\
  HW_E_OAVL(filter, v, on | off)

#define _hwa_cfcap16a_vfilter_1(o,v,...)		\
  hwa->o.config.filter = HW_A1(_hw_state_##v);		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cap16a
 * @section atmelavr_cap16a_read Capture value
 *
 * @code
 * uint16_t capture = hw( read, capture0 );
 * @endcode
 */
#define hw_read__cap16a	, _hw_read_cap16a
#define _hw_read_cap16a(o,i,a,...)	 _hw_read(o,reg) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cap16a
 *
 * @code
 * hw( write, capture0, value );
 * @endcode
 */
#define hw_write__cap16a	, _hw_write_cap16a
#define _hw_write_cap16a(o,i,a,v,...)		 _hw_write(o,reg,v) HW_EOL(__VA_ARGS__)

/**
 * @page atmelavr_cap16a
 *
 * @code
 * hwa( write, capture0, value );
 * @endcode
 */
#define hwa_write__cap16a	, _hwa_write_cap16a
#define _hwa_write_cap16a(o,i,a,v,...)		 _hwa_write(o,reg,v) HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_cap16a
 * @section atmelavr_cap16a_st Status
 *
 * The capture event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, irqflag((counter0,capture0)) ) ) {       // Read capture IRQ flag
 *   hw( clear, irqflag((counter0,capture0)) );            // Clear capture IRQ flag
 *   hw( turn, irq((counter0,capture0)), off );            // Disable capture IRQs
 * }
 * @endcode
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__cap16a(o,i,a)		\
  _hwa_setup_r( o, reg      );		\
  hwa->o.config.input  = 0xFF ;			\
  hwa->o.config.edge   = 0xFF ;			\
  hwa->o.config.filter = 0xFF

#define _hwa_init__cap16a(o,i,a)		_hwa_init_r(o,reg,0)

#define _hwa_commit__cap16a(o,i,a)		_hwa_commit_r(o,reg)


/**
 * @page atmelavr_cap16a
 * <br>
 */
