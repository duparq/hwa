
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit capture unit
 */

/**
 * @addtogroup atmelavr_ica
 * @section atmelavr_ica_act Actions
 *
 * <br>
 * `configure`:
 *
 * @code
 * hw( configure, (counter0,capture0),
 *
 *   [ input,	  pin_icp      // NOT IMPLEMENTED YET
 *		| acmp0, ]
 *
 *   [ edge,	  falling
 *		| rising, ]
 *
 *   [ filter,	  on	       // NOT IMPLEMENTED YET
 *		| off ] );
 * @endcode
 */
/*  TODO: complete this.
 */
#define hw_configure__ica		, _hw_cfica

#define hw_ica_input_pin_icp		, 1
#define hw_ica_input_acmp0		, 2

#define hw_ica_edge_falling		, 1
#define hw_ica_edge_rising		, 2

#define _hw_cfica_kw_edge		, _hw_cfica_edge
//#define _hw_cfica_kw_			, _hw_cfica_

//_hw_cfica(counter1_capture0,counter1, 0,edge, falling,,);
#define _hw_cfica(o,ct,ic,k,...)				\
  HW_B(_hw_cficakw1_,_hw_cfica_kw_##k)(ct,k,__VA_ARGS__,)

#define _hw_cficakw1_0(ct,kw,...)	HW_E(HW_EM_AL(k,(input,edge,filter)))

#define _hw_cficakw1_1(ct,kw,...)	HW_A1(_hw_cfica_kw_##kw)(ct,__VA_ARGS__)

#define _hw_cfica_edge(ct,v,...)	HW_B(_hw_cfica_vedge_,hw_ica_edge_##v)(ct,v,__VA_ARGS__)
#define _hw_cfica_vedge_0(ct,v,...)		\
  HW_E(HW_EM_VAL(v,edge,(falling,rising)))
#define _hw_cfica_vedge_1(ct,v,...)					\
  _hw_write(ct, ices, HW_A1(hw_ica_edge_##v)-1 ) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ica
 * @code
 * hwa( configure, counter0capture0,
 *
 *    [ input,	   pin_icp	// FIXME: (pin,icp)
 *		 | acmp0, ]
 *
 *    [ edge,	   falling
 *		 | rising, ]
 *
 *    [ filter,	   on
 *		 | off ] );
 * @endcode
 */
#define hwa_configure__ica		, _hwa_cfica

#define _hwa_cfica(o,ct,ic,k,...)					\
  do { HW_BW(_hwa_cfica_kinput_,input,k)(ct,k,__VA_ARGS__) } while(0)

#define _hwa_cfica_kinput_0(ct,k,...)					\
  HW_BW(_hwa_cfica_kedge_,edge,k)(ct,k,__VA_ARGS__) //HW_E(HW_EM_AN(k,input))
#define _hwa_cfica_kinput_1(ct,k,v,...)		HW_B(_hwa_cfica_vinput_,hw_ica_input_##v)(ct,v,__VA_ARGS__)
#define _hwa_cfica_vinput_0(ct,v,...)		HW_E(HW_EM_VAL(v,input,(pin_icp,acmp0)))
#define _hwa_cfica_vinput_1(ct,v,k,...)				\
  hwa->ct.capture0.config.input = HW_A1(hw_ica_input_##v);		\
  HW_BW(_hwa_cfica_kedge_,edge,k)(ct,k,__VA_ARGS__)

#define _hwa_cfica_kedge_0(ct,k,...)					\
  HW_BW(_hwa_cfica_kfilter_,filter,k)(ct,k,__VA_ARGS__) //  HW_E(HW_EM_AN(k,edge))

#define _hwa_cfica_kedge_1(ct,k,v,...)				\
  HW_B(_hwa_cfica_vedge_,hw_ica_edge_##v)(ct,v,__VA_ARGS__)

#define _hwa_cfica_vedge_0(ct,v,...)		HW_E(HW_EM_VAL(v,edge,(falling,rising)))

#define _hwa_cfica_vedge_1(ct,v,k,...)				\
  hwa->ct.capture0.config.edge = HW_A1(hw_ica_edge_##v);			\
  HW_BW(_hwa_cfica_kfilter_,filter,k)(ct,k,__VA_ARGS__)

#define _hwa_cfica_kfilter_0(ct,...)		\
  HW_EOL(__VA_ARGS__)

#define _hwa_cfica_kfilter_1(ct,k,v,...)				\
  HW_B(_hwa_cfica_vfilter_,_hw_state_##v)(ct,v,__VA_ARGS__)

#define _hwa_cfica_vfilter_0(ct,v,...)		\
  HW_E(HW_EM_VOAL(v,filter,(on,off)))

#define _hwa_cfica_vfilter_1(ct,v,...)		\
  hwa->ct.capture0.config.filter = HW_A1(_hw_state_##v);	\
  HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ica
 *
 * <br>
 * `read`:
 *
 * @code
 * uint16_t capture = hw( read, capture0 );
 * @endcode
 */
#define hw_read__ica			, _hw_read_ica
#define _hw_read_ica(o,ct,ic,...)	_hw_read(ct,icr##ic) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ica
 *
 * <br>
 * `write`:
 *
 * @code
 * hw( write, capture0, value );
 * @endcode
 */
#define hw_write__ica			, _hw_write_ica
#define _hw_write_ica(o,ct,ic,v,...)	_hw_write(ct,icr##ic,v) HW_EOL(__VA_ARGS__)

/**
 * @addtogroup atmelavr_ica
 *
 * @code
 * hwa( write, capture0, value );
 * @endcode
 */
#define hwa_write__ica		, 	_hwa_write_ica
#define _hwa_write_ica(o,ct,ic,v,...)	_hwa_write(ct,icr##ic,v) HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_ica
 * @section atmelavr_ica_st Status
 *
 * The capture event flag can be accessed through interrupt-related
 * instructions:
 *
 * @code
 * if ( hw( read, (counter0,irq,capture0) ) ) {	// Read capture IRQ flag
 *   hw( clear, (counter0,irq,capture0) );	// Clear capture IRQ flag
 *   hw( disable, (counter0,irq,capture0) );	// Disable capture IRQs
 * }
 * @endcode
 */
