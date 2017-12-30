
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief ESP8266 I/O
 */

/**
 * @page espressif_io1b
 * @section espressif_io1b_config Configuration
 *
 * `configure`:
 * @code
 * hw | hwa( configure, gpio16,
 *
 *         [ function,    gpio, ]
 *
 *         [ direction,   input
 *                      | output_when_awake
 *                      | output, ]
 *
 *         [ pulldown,    on
 *                      | when_awake
 *                      | off, ]
 *           );
 * @endcode
 */
#define _hw_mtd_hw_configure__io1b		, _hw_cfio1b
#define _hw_mtd_hwa_configure__io1b		, _hwa_cfio1b

#define _hw_cfio1b(o,i,p,bn,bp,...)		_hw_cfio1b2(o,__VA_ARGS__,,)
#define _hw_cfio1b2(...)			_hw_cfio1b3( __VA_ARGS__ )
#define _hw_cfio1b3(o,k,...)						\
  do{									\
    typedef struct {							\
      uint8_t		commit ;					\
      hwa_rtca_t	rtc ;						\
    } hwa_t ;								\
    hwa_t hwa_st ; hwa_t *hwa= &hwa_st ;				\
    _hwa_setup( rtc );							\
    HW_Y(_hwa_cfio1b_kfunction,_hw_is_function_##k)(o,k,__VA_ARGS__);	\
    hwa->commit = 1;							\
    _hwa_commit( rtc );							\
  }while(0)

#define _hwa_cfio1b(o,i,p,bn,bp,...)		_hwa_cfio1b2(o, __VA_ARGS__,,)
#define _hwa_cfio1b2(...)			_hwa_cfio1b3( __VA_ARGS__ )
#define _hwa_cfio1b3(o,k,...)						\
  HW_Y(_hwa_cfio1b_kfunction,_hw_is_function_##k)(o,k,__VA_ARGS__);

/*  Optionnal parameter `function`
 *    Assume 'gpio' if function is not specified.
 */
#define _hwa_cfio1b_kfunction_1(o,k,v,...)			\
  HW_Y(_hwa_cfio1b_vfunction,_hw_##o##_fn_##v)(o,v,__VA_ARGS__)
#define _hwa_cfio1b_vfunction_0(o,v,...)	HW_E_IOFN(o, function, v, _hw_##o##_fns)
#define _hwa_cfio1b_vfunction_1(o,v,k,...)			\
  _hwa_write(_hw_reg_##o##_fn,HW_A1(_hw_##o##_fn_##v) );	\
  _hwa_write(_hw_reg_##o##_cf,0);				\
  HW_Y(_hwa_cfio1b_gpio,_hw_is_gpio_##v)(o,v,k,__VA_ARGS__)
#define _hwa_cfio1b_gpio_0(o,v,k,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfio1b_gpio_1(o,v,k,...)					\
  HW_Y(_hwa_cfio1b_kdirection,_hw_is_direction_##k)(o,k,__VA_ARGS__)
#define _hwa_cfio1b_kfunction_0(o,k,...)				\
  HW_Y(_hwa_cfio1b_kdirection,_hw_is_direction_##k)(o,k,__VA_ARGS__)

/*  Optionnal parameter `direction`
 */
#define _hwa_cfio1b_kdirection_1(o,k,v,...)	HW_Y(_hwa_cfio1b_vdirection,_hw_cfio1b_direction_##v)(o,v,__VA_ARGS__)
#define _hwa_cfio1b_vdirection_0(o,v,...)	HW_E_AVL(direction,v,(input,output))
#define _hwa_cfio1b_vdirection_1(o,v,k,...)				\
  _hwa_write(_hw_reg_##o##_oe,HW_A1(_hw_cfio1b_direction_##v));		\
  HW_Y(_hwa_cfio1b_kpulldown,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)
#define _hwa_cfio1b_kdirection_0(o,k,...)				\
  HW_Y(_hwa_cfio1b_kpulldown,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)

#define _hw_cfio1b_direction_input		, 0	/* oe */
#define _hw_cfio1b_direction_output		, 1

/*  Optionnal parameter `pulldown`
 */
#define _hwa_cfio1a_kpulldown_1(o,cf,p,bn,bp,k,v,...)				\
    HW_Y(_hwa_cfio1a_vpulldown0,_hw_cfio1a_pulldown_##v)(o,cf,p,bn,bp,v,__VA_ARGS__)

#define _hwa_cfio1a_vpulldown_1(o,cf,p,bn,bp,v,...)	\
    _hwa_write_reg( cf, pux, HW_A1(_hw_cfio1a_pulldown_##v) );	\
    HW_EOL(__VA_ARGS__)

#define _hwa_cfio1b_vpulldown_0(o,v,...)	HW_AVL(pulldown,v,(on,off,when_awake))
#define _hwa_cfio1b_vpulldown0_0(o,v,...)	HW_AVL(pulldown,v,(on,off,when_awake))
#define _hwa_cfio1b_kpulldown_0(o,...)		HW_EOL(__VA_ARGS__)

/*  FIXME: fake values
 */
#define _hw_cfio1b_pulldown_off			, 0	/* pux */
#define _hw_cfio1b_pulldown_when_sleeping	, 1
#define _hw_cfio1b_pulldown_when_awake		, 2
#define _hw_cfio1b_pulldown_on			, 3


/**
 * @page espressif_io1b
 * @section espressif_io1b_read State
 *
 * The instruction `read` returns the state of the I/O object:
 *
 * @code
 * uint8_t value = hw( read, gpio0 );
 * @endcode
 */
#define _hw_mtd_hw_read__io1b		, _hw_read_io1b

#define _hw_read_io1b(o,i, p,bn,bp,...)				\
  HW_TX( ((_hw_read_reg(p, _gpioin) & (((1UL<<bn)-1)<<bp))>>bp), __VA_ARGS__)


/**
 * @page espressif_io1b
 *
 * The instruction `hw_write()` changes the state of the I/O object:
 *
 * @code
 * hw( write, gpio0, value );
 * @endcode
 */
#define _hw_mtd_hw_write__io1b		, _hw_wrio1b

#define _hw_wrio1b(o,i, p,bn,bp, v,...)			\
  HW_TX( _hw_write_reg_m(p, _gpioout, ((1UL<<bn)-1)<<bp, (v)<<bp), __VA_ARGS__ )


/**
 * @page espressif_io1b
 *
 * @code
 * hwa( write, gpio0, value );
 * @endcode
 */
#define _hw_mtd_hwa_write__io1b		, _hwa_wrio1b

#define _hwa_wrio1b(o,i, p,bn,bp, v, ...)				\
  HW_TX(_hwa_write_reg_m(&hwa->p._gpioout, ((1UL<<bn)-1)<<bp, (v)<<bp)), __VA_ARGS__)


/**
 * @page espressif_io1b
 * @code
 * hw( toggle, gpio0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
#define _hw_mtd_hw_toggle__io1b		, _hw_tgio1b

#define _hw_tgio1b(o,i,p,bn,bp,...)	HW_TX( _hw_tgio1b_2(_HW_A(_HW_R(p,_gpioout)),(((1UL<<bn)-1)<<bp)), __VA_ARGS__)
#define _hw_tgio1b_2(r,msk)		*(volatile uint32_t *)r = *(volatile uint32_t *)r ^ msk

/**
 * @page espressif_io1b
 * <br>
 */
