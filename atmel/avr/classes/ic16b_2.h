
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_ic16b
 * @section atmelavr_ic16b_config Configuration
 * @subsection atmelavr_ic16b_cf1 Synchronous
 *
 * @note: Currently, only `edge` configuration is implemented for the synchronous
 * method.
 *
 * @code
 * hw_config( CAPTURE_NAME,
 *
 *            input,    pin_icp,     // NOT IMPLEMENTED YET
 *
 *           [edge,     falling
 *                    | rising, ]
 *
 *           [filter,   on           // NOT IMPLEMENTED YET
 *                    | off ]
 *           );
 * @endcode
 */
#define _hw_mthd_hw_config__ic16b		, _hw_cfic16b

#define hw_ic16b_input_pin_icp			, 1
#define hw_ic16b_input_acmp0			, 2

#define hw_ic16b_edge_falling			, 1
#define hw_ic16b_edge_rising			, 2

#define _hw_cfic16b_kw_edge			, _hw_cfic16b_edge
//#define _hw_cfic16b_kw_				, _hw_cfic16b_

#define _hw_cfic16b(o,i,a,...)						\
  HW_G2(_hw_cfic16bkw1, HW_IS(,_hw_cfic16b_kw_##__VA_ARGS__))(o,__VA_ARGS__,)

#define _hw_cfic16bkw1_0(o,kw,...)					\
  HW_ERR("expected `input`, `edge` or `filter` instead of `" #kw "`.")

#define _hw_cfic16bkw1_1(o,kw,...)		\
  HW_A1(_hw_cfic16b_kw_##kw)(o,__VA_ARGS__)

#define _hw_cfic16b_edge(o,v,...)					\
  HW_G2(_hw_cfic16b_vedge,HW_IS(,hw_ic16b_edge_##v))(o,v,__VA_ARGS__)
#define _hw_cfic16b_vedge_0(o,v,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" #v "`.")
#define _hw_cfic16b_vedge_1(o,v,...)			\
  HW_TX(_hw_write_reg(o, ices, HW_A1(hw_ic16b_edge_##v)-1),__VA_ARGS__)


/**
 * @page atmelavr_ic16b
 * @subsection atmelavr_ic16b_cf2 Asynchronous
 * @code
 * hwa_config( CAPTURE_NAME,
 *
 *             input,    pin_icp,
 *
 *             edge,     falling
 *                     | rising,
 *
 *           [ filter,   on
 *                     | off ]
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__ic16b		, _hwa_cfic16b

#define _hwa_cfic16b(o,i,a,...)						\
  do {									\
    HW_G2(_hwa_cfic16b_kinput,HW_IS(input,__VA_ARGS__))(o,__VA_ARGS__,,) \
      } while(0)

#define _hwa_cfic16b_kinput_0(o,k,...)					\
  HW_ERR("expected `input` instead of `" #k "`.")

#define _hwa_cfic16b_kinput_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16b_vinput,HW_IS(,hw_ic16b_input_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16b_vinput_0(o,v,...)					\
  HW_ERR( "`input` can only be `pin_icp`, not `" #v "`.")

#define _hwa_cfic16b_vinput_1(o,v,k,...)				\
  hwa->o.config.input = HW_A1(hw_ic16b_input_##v);			\
  HW_G2(_hwa_cfic16b_kedge,HW_IS(edge,k))(o,k,__VA_ARGS__)

#define _hwa_cfic16b_kedge_0(o,k,...)					\
  HW_ERR("expected `edge` instead of `" #k "`.")

#define _hwa_cfic16b_kedge_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16b_vedge,HW_IS(,hw_ic16b_edge_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16b_vedge_0(o,v,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" #v "`.")

#define _hwa_cfic16b_vedge_1(o,v,k,...)				\
  hwa->o.config.edge = HW_A1(hw_ic16b_edge_##v);				\
  HW_G2(_hwa_cfic16b_kfilter,HW_IS(filter,k))(o,k,__VA_ARGS__)

#define _hwa_cfic16b_kfilter_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfic16b_kfilter_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16b_vfilter,HW_IS(,_hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16b_vfilter_0(o,v,...)					\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" #v "`.")

#define _hwa_cfic16b_vfilter_1(o,v,...)		\
  hwa->o.config.filter = HW_A1(_hw_state_##v);		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ic16b
 * @section atmelavr_ic16b_read Capture value
 *
 * @code
 * uint16_t capture = hw_read( CAPTURE_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__ic16b			, _hw_read_ic16a


/**
 * @page atmelavr_ic16b
 *
 * @code
 * hw_write( CAPTURE_NAME, value );
 * @endcode
 */
#define _hw_mthd_hw_write__ic16b		, _hw_write_ic16a

/**
 * @page atmelavr_ic16b
 *
 * @code
 * hwa_write( CAPTURE_NAME, value );
 * @endcode
 */
#define _hw_mthd_hwa_write__ic16b		, _hwa_write_ic16a


/**
 * @page atmelavr_ic16b
 * @section atmelavr_ic16b_st Status
 *
 * The capture event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw_stat_irqf( CAPTURE_NAME ) ) {        // Read capture IRQ flag
 *   hw_clear_irqf( CAPTURE_NAME );             // Clear capture IRQ flag
 *   hw_turn_irq( CAPTURE_NAME, off );          // Disable capture IRQs
 * }
 * @endcode
 */



/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_setup__ic16b	_hwa_setup__ic16a
#define _hwa_init__ic16b	_hwa_init__ic16a
#define _hwa_commit__ic16b	_hwa_commit__ic16a


/**
 * @page atmelavr_ic16b
 * <br>
 */
