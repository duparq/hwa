
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
 *         [ function,    gpio, ]                                       // Default
 *
 *         [ mode,        digital_input | digital_input_floating        // Default
 *                      | digital_input_pulldown
 *                      | digital_input_pulldown_when_awake
 *                      | digital_output | digital_output_pushpull
 *
 *         [ pulldown     off
 *                      | when_awake
 *                      | on, ] );
 * @endcode
 */
#define hw_configure__io1b		, _hw_cfio1b
#define hwa_configure__io1b		, _hwa_cfio1b

#define _hw_cfio1b(o,i, p,bn,bp, ...)		_hw_cfio1b2(o,__VA_ARGS__)
#define _hwa_cfio1b(o,i, p,bn,bp, ...)		_hwa_cfio1b2(o,__VA_ARGS__)

/*  Create a local minimal context, apply the asynchronous action on it, and
 *  commit.
 */
#define _hw_cfio1b2(o,k,...)						\
  do{									\
    struct {								\
      uint8_t		commit ;					\
      hwa_rtca_t	rtc ;						\
    } st ;								\
    hwa_t *hwa= (hwa_t*)&st ;						\
    _hwa_setup_o( rtc );							\
    HW_Y(_hwa_cfio1b_kfn_,_hw_is_function_##k)(o,k,__VA_ARGS__);		\
    st.commit = 1;							\
    _hwa_commit_o( rtc );							\
  }while(0)

#define _hwa_cfio1b2(o,k,...)	HW_Y(_hwa_cfio1b_kfn_,_hw_is_function_##k)(o,k,__VA_ARGS__)

/*  Key 'function'
 */
#define _hwa_cfio1b_kfn_0(o,k,...)		HW_Y(_hwa_cfio1b_kmd_,_hw_is_mode_##k)(o,k,__VA_ARGS__)
#define _hwa_cfio1b_kfn_1(o,k,v,...)		HW_Y(_hwa_cfio1b_vfn_,_hw_##o##_fn_##v)(o,v,__VA_ARGS__)
#define _hwa_cfio1b_vfn_0(o,v,...)		HW_E_IOFN(o, function, v, _hw_##o##_fns)
#define _hwa_cfio1b_vfn_1(o,v,k,...)				\
  _hwa_write(hw_reg_##o##_fn,HW_A1(_hw_##o##_fn_##v) );	\
  _hwa_write(hw_reg_##o##_cf,0);				\
  HW_Y(_hwa_cfio1b_gpio_,_hw_is_gpio_##v)(o,v,k,__VA_ARGS__)
#define _hwa_cfio1b_gpio_0(o,v,k,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfio1b_gpio_1(o,v,k,...)		HW_Y(_hwa_cfio1b_kmd_,_hw_is_mode_##k)(o,k,__VA_ARGS__)

/*  Key `mode`
 */
#define _hw_cfio1b_md_digital_input				, di
#define _hw_cfio1b_md_digital_input_floating			, dif
#define _hw_cfio1b_md_digital_input_pulldown			, dipd
#define _hw_cfio1b_md_digital_input_pulldown_when_awake		, dipdwa
#define _hw_cfio1b_md_digital_output				, dopp
#define _hw_cfio1b_md_digital_output_pushpull			, dopp

#define _hwa_cfio1b_kmd_0(o,k,...)	HW_E_NIL(k, (mode) )
#define _hwa_cfio1b_kmd_1(o,k,v,...)	HW_Y(_hwa_cfio1b_vmd_,_hw_cfio1b_md_##v)(o,v,__VA_ARGS__)
#define _hwa_cfio1b_vmd_0(o,v,...)	HW_E_NIL(v, (digital_input,digital_input_floating, \
						     digital_input_pulldown, digital_input_pulldown_when_awake, \
						     digital_output, digital_output_pushpull) )
#define _hwa_cfio1b_vmd_1(o,v,...)	HW_G2(_hwa_cfio1b,HW_A1(_hw_cfio1b_md_##v))(o,__VA_ARGS__)

#define _hwa_cfio1b_di(o,k,...)				\
  _hwa_write(hw_reg_##o##_oe, 0 /* input */ );				\
  HW_Y(_hwa_cfio1b_kpd_,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)

#define _hwa_cfio1b_dif(o,k,...)				\
  _hwa_write(hw_reg_##o##_oe, 0 /* input */ );				\
  _hwa_write( cf, pux, 0 /* pulldown off - FIXME: FAKE VALUE */ );	\
  HW_Y(_hwa_cfio1b_kpd_,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)

#define _hwa_cfio1b_dipd(o,k,...)				\
  _hwa_write(hw_reg_##o##_oe, 0 /* input */ );				\
  _hwa_write( cf, pux, 3 /* pulldown on - FIXME: FAKE VALUE */ );	\
  HW_Y(_hwa_cfio1b_kpd_,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)

#define _hwa_cfio1b_dipdwa(o,k,...)				\
  _hwa_write(hw_reg_##o##_oe, 0 /* input */ );				\
  _hwa_write( cf, pux, 2 /* pulldown when awake - FIXME: FAKE VALUE */ ); \
  HW_Y(_hwa_cfio1b_kpd_,_hw_is_pulldown_##k)(o,k,__VA_ARGS__)

#define _hwa_cfio1b_dopp(o,k,...)	_hwa_write(hw_reg_##o##_oe, 1 /* output */ ); HW_EOL(__VA_ARGS__)

/*  Key `pulldown`
 */
#define _hwa_cfio1b_kpd_0(o,...)		HW_EOL(__VA_ARGS__)
#define _hwa_cfio1b_kpd_1(o,k,v,...)	HW_Y(_hwa_cfio1b_vpd_,_hw_cfio1b_pulldown_##v)(o,v,__VA_ARGS__)
#define _hwa_cfio1b_vpd_0(o,v,...)		HW_AVL(pulldown,v,(on,off,when_awake))
#define _hwa_cfio1b_vpd_1(o,v,...)	_hwa_write( cf, pux, HW_A1(_hw_cfio1b_pulldown_##v) ); HW_EOL(__VA_ARGS__)

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
#define hw_read__io1b		, _hw_read_io1b

#define _hw_read_io1b(o,i, p,bn,bp,...)				\
   ((_hw_read(p, _gpioin) & (((1UL<<bn)-1)<<bp))>>bp) HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1b
 *
 * The instruction `hw_write()` changes the state of the I/O object:
 *
 * @code
 * hw( write, gpio0, value );
 * @endcode
 */
#define hw_write__io1b		, _hw_wrio1b

#define _hw_wrio1b(o,i, p,bn,bp, v,...)			\
   _hw_write_m(p, _gpioout, ((1UL<<bn)-1)<<bp, (v)<<bp) HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1b
 *
 * @code
 * hwa( write, gpio0, value );
 * @endcode
 */
#define hwa_write__io1b		, _hwa_wrio1b

#define _hwa_wrio1b(o,i, p,bn,bp, v, ...)				\
  _hwa_write_m(&hwa->p._gpioout, ((1UL<<bn)-1)<<bp, (v)<<bp)) HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1b
 * @code
 * hw( toggle, gpio0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
#define hw_toggle__io1b		, _hw_tgio1b

#define _hw_tgio1b(o,i,p,bn,bp,...)	 _hw_tgio1b_2(HW_ADDRESS((p,_gpioout)),(((1UL<<bn)-1)<<bp)) HW_EOL(__VA_ARGS__)
#define _hw_tgio1b_2(r,msk)		*(volatile uint32_t *)r = *(volatile uint32_t *)r ^ msk

/**
 * @page espressif_io1b
 * <br>
 */
