
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @page atmelavr_ic16a
 * @section atmelavr_ic16a_config Configuration
 * @subsection atmelavr_ic16a_cf1 Synchronous
 *
 * @note: Currently, only `edge` configuration is implemented for the synchronous
 * method.
 *
 * @code
 * hw_config( CAPTURE_NAME,
 *
 *           [input,    pin_icp      // NOT IMPLEMENTED YET
 *                    | hw_acmp0, ]
 *
 *           [edge,     falling
 *                    | rising, ]
 *
 *           [filter,   on           // NOT IMPLEMENTED YET
 *                    | off ]
 *           );
 * @endcode
 */
#define _hw_mthd_hw_configure__ic16a		, _hw_cfic16a

#define hw_ic16a_input_pin_icp			, 1
#define hw_ic16a_input_acmp0			, 2

#define hw_ic16a_edge_falling			, 1
#define hw_ic16a_edge_rising			, 2

#define _hw_cfic16a_kw_edge			, _hw_cfic16a_edge
//#define _hw_cfic16a_kw_				, _hw_cfic16a_

#define _hw_cfic16a(o,i,a,...)						\
  HW_G2(_hw_cfic16akw1, HW_IS(,_hw_cfic16a_kw_##__VA_ARGS__))(o,__VA_ARGS__,)

#define _hw_cfic16akw1_0(o,kw,...)					\
  HW_ERR("expected `input`, `edge` or `filter` instead of `" #kw "`.")

#define _hw_cfic16akw1_1(o,kw,...)		\
  HW_A1(_hw_cfic16a_kw_##kw)(o,__VA_ARGS__)

#define _hw_cfic16a_edge(o,v,...)					\
  HW_G2(_hw_cfic16a_vedge,HW_IS(,hw_ic16a_edge_##v))(o,v,__VA_ARGS__)
#define _hw_cfic16a_vedge_0(o,v,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" #v "`.")
#define _hw_cfic16a_vedge_1(o,v,...)			\
  HW_TX(_hw_write_reg(o, ices, HW_A1(hw_ic16a_edge_##v)-1),__VA_ARGS__)


/**
 * @page atmelavr_ic16a
 * @subsection atmelavr_ic16a_cf2 Asynchronous
 * @code
 * hwa_config( CAPTURE_NAME,
 *
 *             input,    pin_icp
 *                     | hw_acmp0,
 *
 *             edge,     falling
 *                     | rising,
 *
 *           [ filter,   on
 *                     | off ]
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_configure__ic16a		, _hwa_cfic16a

#define _hwa_cfic16a(o,i,a,...)						\
  do {									\
    HW_G2(_hwa_cfic16a_kinput,HW_IS(input,__VA_ARGS__))(o,__VA_ARGS__,,) \
      } while(0)

#define _hwa_cfic16a_kinput_0(o,k,...)					\
  HW_ERR("expected `input` instead of `" #k "`.")

#define _hwa_cfic16a_kinput_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16a_vinput,HW_IS(,hw_ic16a_input_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16a_vinput_0(o,v,...)					\
  HW_ERR( "`input` can be `pin_icp` or `hw_acmp0` but not `" #v "`.")

#define _hwa_cfic16a_vinput_1(o,v,k,...)				\
  hwa->o.config.input = HW_A1(hw_ic16a_input_##v);			\
  HW_G2(_hwa_cfic16a_kedge,HW_IS(edge,k))(o,k,__VA_ARGS__)

#define _hwa_cfic16a_kedge_0(o,k,...)					\
  HW_ERR("expected `edge` instead of `" #k "`.")

#define _hwa_cfic16a_kedge_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16a_vedge,HW_IS(,hw_ic16a_edge_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16a_vedge_0(o,v,...)					\
  HW_ERR( "`edge` can be `falling` or `rising` but not `" #v "`.")

#define _hwa_cfic16a_vedge_1(o,v,k,...)				\
  hwa->o.config.edge = HW_A1(hw_ic16a_edge_##v);				\
  HW_G2(_hwa_cfic16a_kfilter,HW_IS(filter,k))(o,k,__VA_ARGS__)

#define _hwa_cfic16a_kfilter_0(o,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfic16a_kfilter_1(o,k,v,...)				\
  HW_G2(_hwa_cfic16a_vfilter,HW_IS(,_hw_state_##v))(o,v,__VA_ARGS__)

#define _hwa_cfic16a_vfilter_0(o,v,...)					\
  HW_ERR( "optionnal parameter `filter` can be `on` or `off` but not `" #v "`.")

#define _hwa_cfic16a_vfilter_1(o,v,...)		\
  hwa->o.config.filter = HW_A1(_hw_state_##v);		\
  HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ic16a
 * @section atmelavr_ic16a_read Capture value
 *
 * @code
 * uint16_t capture = hw_read( CAPTURE_NAME );
 * @endcode
 */
#define _hw_mthd_hw_read__ic16a			, _hw_read_ic16a
#define _hw_read_ic16a(o,i,a,...)		HW_TX( _hw_read_reg(o,reg), __VA_ARGS__ )


/**
 * @page atmelavr_ic16a
 *
 * @code
 * hw_write( CAPTURE_NAME, value );
 * @endcode
 */
#define _hw_mthd_hw_write__ic16a		, _hw_write_ic16a
#define _hw_write_ic16a(o,i,a,v,...)		HW_TX( _hw_write_reg(o,reg,v), __VA_ARGS__ )

/**
 * @page atmelavr_ic16a
 *
 * @code
 * hwa_write( CAPTURE_NAME, value );
 * @endcode
 */
#define _hw_mthd_hwa_write__ic16a		, _hwa_write_ic16a
#define _hwa_write_ic16a(o,i,a,v,...)		HW_TX( _hwa_write_reg(o,reg,v), __VA_ARGS__ )


/**
 * @page atmelavr_ic16a
 * @section atmelavr_ic16a_st Status
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

#define _hwa_setup__ic16a(o,i,a)		\
  _hwa_setup_reg( o, reg      );		\
  hwa->o.config.input  = 0xFF ;			\
  hwa->o.config.edge   = 0xFF ;			\
  hwa->o.config.filter = 0xFF

#define _hwa_init__ic16a(o,i,a)			_hwa_init_reg(o,reg,0)

#define _hwa_commit__ic16a(o,i,a)		_hwa_commit_reg(o,reg)


/**
 * @page atmelavr_ic16a
 * <br>
 */
