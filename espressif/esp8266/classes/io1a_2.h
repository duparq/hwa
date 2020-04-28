
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief ESP8266 I/O
 */

/**
 * @page espressif_io1a
 * @section espressif_io1a_config Configuration
 *
 * __Actions__
 *
 * `configure`:
 *
 * @code
 * hw | hwa( configure,	  gpio0,
 *
 *	   [ function,	  gpio, ]					// Default
 *
 *	   [ mode,	  digital_input | digital_input_floating	// Default
 *			| digital_input_pullup
 *			| digital_input_pullup_when_awake
 *			| digital_input_pullup_when_sleeping
 *			| digital_output | digital_output_pushpull
 *			| digital_output_when_awake | digital_output_pushpull_when_awake
 *			| digital_output_when_sleeping | digital_output_pushpull_when_sleeping
 *			| analog_input,
 *
 *	   [ pullup,	  off
 *			| when_awake
 *			| when_sleeping
 *			| on, ] );
 * @endcode
 * <br>
 * @code
 * // ALTERNATE_FUNCTION is a signal name, such as 'int0' or '(uart0,tx)'.
 * //
 * hw | hwa( configure,	  pa0,
 *
 *	     function,	  ALTERNATE_FUNCTION );
 * @endcode
 * <br>
 */
#define hw_configure__io1a		, _hw_cfio1a
#define hwa_configure__io1a		, _hwa_cfio1a

#define _hw_cfio1a(o, p,bn,bp, ...)		_hwx_cfio1a1( _hw, o, o##_cf, p,bn,bp, __VA_ARGS__)
#define _hwa_cfio1a(o, p,bn,bp, ...)		_hwx_cfio1a1( _hwa, o, o##_cf, p,bn,bp, __VA_ARGS__)

#define _hwx_cfio1a1(...)			_hwx_cfio1a2(__VA_ARGS__)
#define _hwx_cfio1a2(x,...)			x##_cfio1a1(__VA_ARGS__)

/*  Create a local minimal context, apply the asynchronous action on it, and
 *  commit.
 */
#define _hw_cfio1a1(o,cf,p,...)					\
  do {								\
    struct {							\
      uint8_t		commit ;				\
      hwa_shared_t	shared ;				\
      hwa_p16a_t	p ;					\
      hwa_pcfa_t	cf ;					\
    } st ;							\
    hwa_t *hwa = (hwa_t*)&st ;					\
    _hwa_setup_o( shared ); _hwa_setup_o( p ); _hwa_setup_o( cf );	\
    _hwa_cfio1a1(o,cf,p,__VA_ARGS__);				\
    st.commit = 1 ;						\
    _hwa_commit_o( shared ); _hwa_commit_o( p ); _hwa_commit_o( cf );	\
  }while(0)

/*  Key 'function'
 */
#define _hwa_cfio1a1(o,cf,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kfn_,_hw_is_function_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_kfn_0(o,cf,p,bn,bp,k,...)	HW_Y(_hwa_cfio1a_kmd_,_hw_is_mode_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_kfn_1(o,cf,p,bn,bp,k,v,...)	_hwa_cfio1a_kfn_2(o,cf,p,bn,bp,v,_HW_UBKT(v),__VA_ARGS__)
#define _hwa_cfio1a_kfn_2(...)			_hwa_cfio1a_kfn_3(__VA_ARGS__)
#define _hwa_cfio1a_kfn_3(o,cf,p,bn,bp,v,x,...)	HW_Y(_hwa_cfio1a_vfn_,_hw_pf_##o##_##x)(o,cf,p,bn,bp,v,x,__VA_ARGS__)
#define _hwa_cfio1a_vfn_0(o,cf,p,bn,bp,v,x,...)	HW_E_NIL(v, _hw_pf_##o)
#define _hwa_cfio1a_vfn_1(o,cf,p,bn,bp,v,x,k,...)			\
  _hwa_write( cf, fn, HW_A1(_hw_pf_##o##_##x) );			\
  HW_A2(_hw_pf_##o##_##x) /* Optionnal supplement of actions, e.g. swap	 */ \
  HW_Y(_hwa_cfio1a_vfn1_,_hw_is_gpio_##x)(o,cf,p,bn,bp,v,x,k,__VA_ARGS__)

#define _hwa_cfio1a_vfn1_1(o,cf,p,bn,bp,v,x,k,...)	HW_Y(_hwa_cfio1a_kmd_,_hw_is_mode_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)
#define _hwa_cfio1a_vfn1_0(o,cf,p,bn,bp,v,x,...)	HW_EOL(__VA_ARGS__)

/*  Key 'mode'
 */
#define _hw_cfio1a_md_digital_input	, di
#define _hw_cfio1a_md_digital_input_floating	, dif
#define _hw_cfio1a_md_digital_input_pullup	, dipu
#define _hw_cfio1a_md_digital_input_pullup_when_awake	, dipuwa
#define _hw_cfio1a_md_digital_input_pullup_when_sleeping	, dipuws
#define _hw_cfio1a_md_digital_output	, dopp
#define _hw_cfio1a_md_digital_output_pushpull	, dopp
#define _hw_cfio1a_md_digital_output_when_awake	, doppwa
#define _hw_cfio1a_md_digital_output_pushpull_when_awake	, doppwa
#define _hw_cfio1a_md_digital_output_when_sleeping	, doppws
#define _hw_cfio1a_md_digital_output_pushpull_when_sleeping	, doppws
#define _hw_cfio1a_md_analog_input	, ai

#define _hwa_cfio1a_kmd_0(o,cf,p,bn,bp,k,...)	HW_E_NIL(k, (mode) )
#define _hwa_cfio1a_kmd_1(o,cf,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vmd_,_hw_cfio1a_md_##v)(o,cf,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vmd_0(o,cf,p,bn,bp,v,...)	HW_E_NIL(v, (digital_input,digital_input_floating, digital_input_pullup, \
							     digital_input_pullup_when_awake, \
							     digital_output, digital_output_pushpull, \
							     digital_output_when_awake, digital_output_pushpull_when_awake, \
							     digital_output_when_sleeping, digital_output_pushpull_when_sleeping,\
							     analog_input) )
#define _hwa_cfio1a_vmd_1(o,cf,p,bn,bp,v,...)	HW_G2(_hwa_cfio1a,HW_A1(_hw_cfio1a_md_##v))(o,cf,p,bn,bp,__VA_ARGS__)

#define _hwa_cfio1a_di(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 0 );						\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_dif(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 0 );						\
  _hwa_write( cf, pux, 0 /* pull-up off */ );			\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_dipu(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 0 /* input */ );				\
  _hwa_write( cf, pux, 3 /* pull-up on */ );			\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_dipuwa(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 0 /* input */ );				\
  _hwa_write( cf, pux, 2 /* pull-up when awake */ );		\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_dipuws(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 0 /* input */ );				\
  _hwa_write( cf, pux, 1 /* pull-up when sleeping */ );		\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_dopp(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 3 /* output */ );				\
  _hwa_write_m( p, _enb, 1UL<<bp, 1UL<<bp );			\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_doppwa(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 1 /* output when awake */ );			\
  _hwa_write_m( p, _enb, 1UL<<bp, 1UL<<bp );			\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)

#define _hwa_cfio1a_doppws(o,cf,p,bn,bp,k,...)				\
  _hwa_write( cf, oex, 2 /* output when sleeping */ );		\
  _hwa_write_m( p, _enb, 1UL<<bp, 1UL<<bp );			\
  HW_Y(_hwa_cfio1a_kpu_,_hw_is_pullup_##k)(o,cf,p,bn,bp,k,__VA_ARGS__)


/*  Key `pullup`
 */
#define _hw_cfio1a_pu_off		, 0	/* pux */
#define _hw_cfio1a_pu_when_sleeping	, 1
#define _hw_cfio1a_pu_when_awake	, 2
#define _hw_cfio1a_pu_on		, 3

#define _hwa_cfio1a_kpu_0(o,cf,p,bn,bp,...)	HW_EOL(__VA_ARGS__)
#define _hwa_cfio1a_kpu_1(o,cf,p,bn,bp,k,v,...)	HW_Y(_hwa_cfio1a_vpu_,_hw_cfio1a_pu_##v)(o,cf,p,bn,bp,v,__VA_ARGS__)
#define _hwa_cfio1a_vpu_1(o,cf,p,bn,bp,v,...)	_hwa_write( cf, pux, HW_A1(_hw_cfio1a_pu_##v) ); HW_EOL(__VA_ARGS__)
#define _hwa_cfio1a_vpu_0(o,cf,p,bn,bp,v,...)	HW_AVL(pullup, v, (on,off,when_awake,when_sleeping))


/**
 * @page espressif_io1a
 * @section espressif_io1a_read State
 *
 * The instruction `read` returns the state of the I/O object:
 *
 * @code
 * uint8_t value = hw( read, gpio0 );
 * @endcode
 */
#define hw_read__io1a			, _hw_read_io1a

#define _hw_read_io1a(o, p,bn,bp,...)			\
  ((_hw_read(p, _in) & (((1UL<<bn)-1)<<bp))>>bp)	\
  HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1a
 *
 * `write`:
 *
 * @code
 * hw( write, gpio0, value );
 * @endcode
 * <br>
 * @code
 * hwa( write, gpio0, value );
 * @endcode
 * <br>
 */
#define hw_write__io1a			, _hw_wrio1a

#define _hw_wrio1a(o, p,bn,bp, v,...)		 _hw_write_m(p, _out, ((1UL<<bn)-1)<<bp, (v)<<bp) HW_EOL(__VA_ARGS__)

#define hwa_write__io1a			, _hwa_wrio1a

#define _hwa_wrio1a(o, p,bn,bp, v, ...)	 _hwa_write__r32(&hwa->p._out,0xFFFFFFFF,bn,bp,v) HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1a
 *
 * `toggle`:
 *
 * @code
 * hw( toggle, gpio0 );	//  Toggle one or several consecutive pins at once
 * @endcode
 * <br>
 */
#define hw_toggle__io1a			, _hw_tgio1a

#define _hw_tgio1a(o,p,bn,bp,...)	 _hw_tgio1a_2(HW_ADDRESS((p,_out)),(((1UL<<bn)-1)<<bp)) HW_EOL(__VA_ARGS__)
#define _hw_tgio1a_2(r,msk)		*(volatile uint32_t *)r = *(volatile uint32_t *)r ^ msk

/*
 * @page espressif_io1a
 * @code
 * // All the pins of the same I/O port toggled in the same transaction will be
 * // toggled at once by the `hwa_commit()` instruction.
 * //
 * hwa( toggle, pa0 );
 * @endcode
 */

/* #define _hwa_toggle_io1a(o, p,...)		_hwa_toggle_io1a_2(_hw_(p,pin),__VA_ARGS__) */
/* #define _hwa_toggle_io1a_2(...)			_hwa_toggle_io1a_3(__VA_ARGS__) */
/* #define _hwa_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\ */
/*   _hwa_write(_m1,p,a,r,rw,ra,rwm,rfm,bn,bp, 1) HW_EOL(__VA_ARGS__) */

/**
 * @page espressif_io1a
 * <br>
 */
