
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
 * @page atmelavr_acmpa
 * @section atmelavr_acmpa_config Configuration
 *
 * __Note__: when the analog comparator shares the analog multiplexer output
 * with the ADC, the ADC must be turned off for the analog comparator to be able
 * to use the analog multiplexer output.
 *
 * @code
 * hwa_config( hw_acmp0,
 * 
 *           [ edge,             falling
 *                             | rising
 *                             | both,   ]
 *
 *           [ positive_input,   hw_pin_ain0
 *                             | bandgap,    ]
 *
 *           [ negative_input,   hw_pin_ain1
 *                             | hw_pin_adc0 .. hw_pin_adc7 ]
 *           );
 * @endcode
 */
/*
 *  NOTE: another solution could be the creation of an object `hw_admux0` for
 *  the analog multiplexer that's shared between the ADC and the ACMP but the
 *  ADC and ACMP can not use the analog multiplexer at the same time. Then, it
 *  seems acceptable to make the configuration instructions of the ADC or of the
 *  ACMP drive the analog multiplexer.
 */
#define _hw_mthd_hwa_config__acmpa		, _hwa_cfacmpa

/*  Optionnal parameter `edge`
 */
#define _hw_is_edge_edge			, 1
#define _hw_acmpa_edge_falling			, 2	/* ACIS */
#define _hw_acmpa_edge_rising			, 3
#define _hw_acmpa_edge_both			, 0

#define _hwa_cfacmpa(o,i,a,...)						\
  do {									\
    HW_G2(_hwa_cfacmpa_xedge, HW_IS(edge,__VA_ARGS__))(o,__VA_ARGS__,,); \
  } while(0)

#define _hwa_cfacmpa_xedge_1(o,k,v,...)				\
  HW_G2(_hwa_cfacmpa_vedge, HW_IS(,_hw_acmpa_edge_##v))(o,v,__VA_ARGS__)

#define _hwa_cfacmpa_vedge_0(o,v,...)					\
  HW_ERR("`edge` can be `falling`, `rising`, or `both`, but not `"#v".")

#define _hwa_cfacmpa_vedge_1(o,v,k,...)			\
  _hwa_write_reg(o,acis, HW_A1(_hw_acmpa_edge_##v));	\
  HW_G2(_hwa_cfacmpa_xposin, HW_IS(positive_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfacmpa_xedge_0(o,k,...)					\
  HW_G2(_hwa_cfacmpa_xposin, HW_IS(positive_input,k))(o,k,__VA_ARGS__)

/*  Optionnal parameter `positive_input`
 */
#define _hw_is_positive_input_positive_input	, 1
#define _hw_acmpa_posin_hw_pin_ain0		, 0	/* ACBG */
#define _hw_acmpa_posin_bandgap			, 1	/* ACBG */

#define _hwa_cfacmpa_xposin_1(o,k,v,...)				\
  HW_G2(_hwa_cfacmpa_vposin, HW_IS(,_hw_acmpa_posin_##v))(o,v,__VA_ARGS__)

#define _hwa_cfacmpa_vposin_0(o,v,...)					\
  HW_ERR("`positive_input` can be `hw_pin_ain0`, or `bandgap` but not `"#v"`.")

#define _hwa_cfacmpa_vposin_1(o,v,k,...)		\
  _hwa_write_reg(o,acbg, HW_A1(_hw_acmpa_posin_##v));	\
  HW_G2(_hwa_cfacmpa_xnegin, HW_IS(negative_input,k))(o,k,__VA_ARGS__)

#define _hwa_cfacmpa_xposin_0(o,k,...)					\
  HW_G2(_hwa_cfacmpa_xnegin, HW_IS(negative_input,k))(o,k,__VA_ARGS__)

/*  Optionnal parameter `negative_input`
 */
#define _hw_is_negative_input_negative_input	, 1

#define _hwa_cfacmpa_xnegin_0(o,...)		HW_EOL(__VA_ARGS__)

#define _hwa_cfacmpa_xnegin_1(o,k,v,...)				\
  if ( hw_id(v)==hw_id(hw_pin_ain1) ) {					\
    _hwa_write_reg(o,acme,0);						\
  } else {								\
    _hwa_write_reg(o,acme,1);						\
    _hwa_write_reg(o,aden,0);						\
    if ( hw_id(v) == hw_id( hw_pin_adc0 ) )				\
      _hwa_write_reg(o,admux, 0);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc1 ) )			\
      _hwa_write_reg(o,admux, 1);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc2 ) )			\
      _hwa_write_reg(o,admux, 2);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc3 ) )			\
      _hwa_write_reg(o,admux, 3);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc4 ) )			\
      _hwa_write_reg(o,admux, 4);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc5 ) )			\
      _hwa_write_reg(o,admux, 5);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc6 ) )			\
      _hwa_write_reg(o,admux, 6);					\
    else if ( hw_id(v) == hw_id( hw_pin_adc7 ) )			\
      _hwa_write_reg(o,admux, 7);					\
    else								\
      HWA_ERR("`negative_input` can be `hw_pin_ain1`, or any "		\
	      "analog input pin, but not`" #v "`.");			\
  }									\
  HW_EOL(__VA_ARGS__)


#if 0
/**
 * @page atmelavr_acmpa
 * @section atmelavr_acmpa_pm Power management
 * @code
 * hw_turn( hw_acmp0, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__acmpa			, _hw_turnacmpa

#define _hw_turnacmpa(o,i,a,...)		\
  HW_G2(_hw_turnacmpa_vstate,HW_IS(,__hw_state_##__VA_ARGS__))

#define _hw_turnacmpa_vstate_1(o,i,a,v,...)	\
  HW_TX( _hw_write_reg(o,acd,(HW_A1(__hw_state_##v)==0)), __VA_ARGS__ )

#define _hw_turnacmpa_vstate_0(o,i,a,v,...)	\
  HW_ERR("object `" #o "` of class `_acmpa` can be turned `on` or `off`, but not `" #v "`.")
#endif

#define _hw_mthd_hw_power__acmpa			, _hw_power
#define _hw_mthd_hwa_power__acmpa			, _hwa_power


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_create__acmpa(o,i,a)	_hwa_create_reg( o, csr  );

#define _hwa_init__acmpa(o,i,a)		_hwa_init_reg( o, csr, 0x00 );

#define _hwa_commit__acmpa(o,i,a)	_hwa_commit_reg( o, csr );


/**
 * @page atmelavr_acmpa
 * @section Internals
 *
 * Though it should not be necessary, the internal registers are accessible
 * through the @ref public_reg_instructions "register access intructions".
 *
 * Class `_acmpa` objects have the following hardware registers:
 *
 *  * `csr`: control/status register
 *
 * that hold the following logical registers:
 *
 *  * `acme`: analog comparator multiplexer enabled
 *  * `aden`: A/D converter enable
 *  * `admux`: analog multiplexer input select
 *  * `acd` : analog comparator disable (power management)
 *  * `acbg` : analog comparator bandgap select
 *  * `aco` : analog comparator output
 *  * `if` : analog comparator interrupt flag
 *  * `ie` : analog comparator interrupt enable
 *  * `acic` : analog comparator input capture enable
 *  * `acis` : analog comparator interrupt mode select
 */

/**
 * @page atmelavr_acmpa
 * <br>
 */
