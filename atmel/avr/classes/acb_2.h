
/*
 * This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Analog Comparator
 */

/**
 * @addtogroup atmelavr_acb
 * @section atmelavr_acb_act Actions
 *
 * <br>
 * `configure`:
 *
 * __Note__ When the analog comparator shares the analog multiplexer output
 * with the ADC, the ADC must be turned off for the analog comparator to be able
 * to use the analog multiplexer output.
 *
 * @code
 * hwa( configure, acmp0,
 * 
 *    [ edge,		 falling
 *		       | rising
 *		       | both, ]
 *
 *    [ positive_input,	 (pin,ain0)
 *		       | bandgap,    ]
 *
 *    [ negative_input,	 (pin,ain1)
 *		       | (pin,adc0..3) ] );
 * @endcode
 */
/*
 *  NOTE: another solution could be the creation of an object `admux0` for
 *  the analog multiplexer that's shared between the ADC and the ACMP but the
 *  ADC and ACMP can not use the analog multiplexer at the same time. Then, it
 *  seems acceptable to make the configuration instructions of the ADC or the
 *  ACMP drive the analog multiplexer transparently.
 */
#define hwa_configure__acb		, _hwa_cfacb

/*  Optionnal parameter `edge`
 */
#define _hw_acb_edge_falling		, 2	/* ACIS */
#define _hw_acb_edge_rising		, 3
#define _hw_acb_edge_both		, 0

#define _hwa_cfacb(o,a,k,...)					\
  do {								\
    HW_B(_hwa_cfacb_xedge_,_hw_is_edge_##k)(o,k,__VA_ARGS__,,);	\
  } while(0)

#define _hwa_cfacb_xedge_1(o,k,v,...)				\
  HW_B(_hwa_cfacb_vedge_,_hw_acb_edge_##v)(o,v,__VA_ARGS__)

#define _hwa_cfacb_vedge_0(o,v,...)			\
  HW_E(HW_EM_VAL( v,edge,(falling,rising,both)))

#define _hwa_cfacb_vedge_1(o,v,k,...)					\
  _hwa_write(o,acis, HW_A1(_hw_acb_edge_##v));				\
  HW_G2(_hwa_cfacb_xposin,HW_IS(positive_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfacb_xedge_0(o,k,...)					\
  HW_G2(_hwa_cfacb_xposin,HW_IS(positive_input,k))(o,k,__VA_ARGS__)

/*  Optionnal parameter `positive_input`
 */
#define _hwa_cfacb_xposin_1(o,k,v,...)					\
  HW_B(_hwa_cfacb_vposin_bandgap_,_hw_is_bandgap_##v)(o,v,__VA_ARGS__)

#define _hwa_cfacb_vposin_bandgap_1(o,v,k,...)				\
  _hwa_write(o,acbg,1);							\
  HW_G2(_hwa_cfacb_xnegin,HW_IS(negative_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfacb_vposin_bandgap_0(o,v,k,...)				\
  if ( HW_ADDRESS(v)==HW_ADDRESS(pin_ain0) )				\
    _hwa_write(o,acbg,0);						\
  else									\
    HWA_E(HW_EM_VAL(v,positive_input,((pin,ain0),bandgap)));		\
  HW_G2(_hwa_cfacb_xnegin,HW_IS(negative_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfacb_xposin_0(o,k,...)					\
  HW_G2(_hwa_cfacb_xnegin,HW_IS(negative_input,k))(o,k,__VA_ARGS__)

/*  Optionnal parameter `negative_input`
 */
#define _hwa_cfacb_xnegin_0(o,...)		HW_EOL(__VA_ARGS__)

#define _hwa_cfacb_xnegin_1(o,k,v,...)					\
  uint32_t a = HW_ADDRESS(v);						\
  if ( a==HW_ADDRESS(pin_ain1) ) {		_hwa_write(o,acme,0);	\
  } else {								\
    _hwa_write(o,acme,1);						\
    _hwa_write(o,aden,0);						\
    if      ( a == HW_ADDRESS(pin_adc0) )	_hwa_write(o,admux, 0);	\
    else if ( a == HW_ADDRESS(pin_adc1) )	_hwa_write(o,admux, 1);	\
    else if ( a == HW_ADDRESS(pin_adc2) )	_hwa_write(o,admux, 2);	\
    else if ( a == HW_ADDRESS(pin_adc3) )	_hwa_write(o,admux, 3);	\
    else HWA_E(HW_EM_VAL(v,negative_input,((pin,ain1),(pin,adc0..3)))); \
  }									\
  HW_EOL(__VA_ARGS__)


#define hw_power__acb			, _hw_power
#define hwa_power__acb			, _hwa_power


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__acb(o,a)		_hwa_setup_r( o, csr )
#define _hwa_init__acb(o,a)		_hwa_init_r( o, csr, 0x00 )
#define _hwa_commit__acb(o,a)		_hwa_commit_r( o, csr )

/**
 * @addtogroup atmelavr_acb
 * @section atmelavr_acbregs Registers
 *
 * Hardware registers:
 *
 *  * `csr`: control/status register
 *
 * Logical registers:
 *
 *  * `acd`: analog comparator disable (power management)
 *  * `acbg`: analog comparator bandgap select
 *  * `aco`: analog comparator output
 *  * `if`: analog comparator interrupt flag
 *  * `ie`: analog comparator interrupt enable
 *  * `acic`: analog comparator input capture enable
 *  * `acis`: analog comparator interrupt mode select
 */
