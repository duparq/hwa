
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief I/O
 */

#define _hw_mthd_hw_read__io1a		, _hw_read_io1a
#define _hw_mthd_hw_write__io1a		, _hw_write_io1a
//#define _hw_mthd_hwa_write__io1a	, _hwa_write_io1a
//#define _hw_mthd_hw_toggle__io1a	, _hw_toggle_io1a


/**
 * @page espressif_io1a
 * @section espressif_io1a_config Configuration
 *
 * @note `direction` and `pullup` should only be used when FUNCTION is
 * `gpio`. HWA does not check anything here.
 *
 * @note Currently, there is no asynchronous method.
 *
 * @code
 * hw_config( PIN_NAME,
 *
 *          [ function,       FUNCTION, ]
 *
 *          [ direction,      input
 *			    | output_when_awake
 *                          | output,           ]
 *
 *          [ pullup,         on
 *			    | when_awake
 *                          | off,       ]
 *            );
 * @endcode
 */
#define _hw_mthd_hw_config__io1a	, _hw_cfio1a


/*  Optionnal parameter `function`
 */
#define _hw_is_function_function		, 1

#define _hw_cfio1a( o,i, p,bn,bp, ...)					\
  do{									\
    uint32_t mux_mask = 0 ;						\
    uint32_t mux_value = 0 ;						\
    HW_G2(_hw_cfio1a_kfunction, HW_IS(function,__VA_ARGS__))(o,p,bn,bp,__VA_ARGS__,,); \
    if ( mux_mask )							\
      _hw_write__r32_m( _hw_ra(hw_iomux0, o), 0x01FF, 0, mux_mask, mux_value ); \
  }while(0)

#define _hw_cfio1a_kfunction_1(o,p,bn,bp,k,v,...)				\
  HW_G2(_hw_cfio1a_vfunction, HW_IS(,_##o##_fn_##v))(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vfunction_0(o,p,bn,bp,v,...)				\
  HW_ERR("function for `" #o "` can be " _##o##_fn " but not `" #v "`.")

/*  Store the function code in bits b8,b5,b4 of the pin's MUX register
 */
#define _hw_cfio1a_vfunction_1(o,p,bn,bp,v,k,...)			\
  mux_mask |= 0x0130 ;							\
  mux_value |= (HW_A1(_##o##_fn_##v) & 0x04)<<6 ;			\
  mux_value |= (HW_A1(_##o##_fn_##v) & 0x03)<<4 ;			\
  HW_G2(_hw_cfio1a_kdirection, HW_IS(direction,k))(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_kfunction_0(o,p,bn,bp,k,...)				\
  HW_G2(_hw_cfio1a_kdirection, HW_IS(direction,k))(o,p,bn,bp,k,__VA_ARGS__)

/*  Optionnal parameter `direction`
 */
#define _hw_is_direction_direction		, 1
#define _hw_cfio1a_direction_input		, 0	/* */
#define _hw_cfio1a_direction_output		, 1	/* */
#define _hw_cfio1a_direction_output_when_awake	, 3	/* */

#define _hw_cfio1a_kdirection_1(o,p,bn,bp,k,v,...)				\
  HW_G2(_hw_cfio1a_vdirection, HW_IS(,_hw_cfio1a_direction_##v))(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vdirection_0(o,p,bn,bp,v,...)				\
  HW_ERR("`direction` can be `input`, `output` or `output_when_awake`, but not `" #v "`.")

#define _hw_cfio1a_vdirection_1(o,p,bn,bp,v,k,...)			\
  mux_mask |= 0x0003 ;							\
  mux_value |= HW_A1(_hw_cfio1a_direction_##v) ;			\
  if ( HW_A1(_hw_cfio1a_direction_##v) != 0 )				\
    _hw_write__r32_m( _hw_ra(p, _enbw1ts), 0xFFFFFFFF, 0, 0xFFFFFFFF, 1UL<<bp ); \
  HW_G2(_hw_cfio1a_kpullup, HW_IS(pullup,k))(o,p,bn,bp,k,__VA_ARGS__)

#define _hw_cfio1a_kdirection_0(o,p,bn,bp,k,...)				\
  HW_G2(_hw_cfio1a_kpullup, HW_IS(pullup,k))(o,p,bn,bp,k,__VA_ARGS__)


/*  Optionnal parameter `pullup`
 */
#define _hw_is_pullup_pullup			, 1
#define _hw_cfio1a_pullup_when_awake		, 0x80	/* */

#define _hw_cfio1a_kpullup_1(o,p,bn,bp,k,v,...)				\
  HW_G2(_hw_cfio1a_vpullup, HW_IS(,_hw_state_##v))(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vpullup_1(o,p,bn,bp,v,...)	\
  mux_mask |= 0x0088 ;				\
  if ( HW_A1(_hw_state_##v) )			\
    mux_value |= 0x88 ;				\
  HW_EOL(__VA_ARGS__)

#define _hw_cfio1a_vpullup_0(o,p,bn,bp,v,...)				\
    HW_G2(_hw_cfio1a_vpullup0, HW_IS(,_hw_cfio1a_pullup_##v))(o,p,bn,bp,v,__VA_ARGS__)

#define _hw_cfio1a_vpullup0_0(o,p,bn,bp,v,...)			\
    HW_ERR("`pullup` can be `on` or `off`, but not `" #v "`.");

#define _hw_cfio1a_vpullup0_1(o,p,bn,bp,v,...)			\
  mux_mask |= 0x0088 ;				\
  mux_value |= 0x80 ;				\
  HW_EOL(__VA_ARGS__)

#define _hw_cfio1a_kpullup_0(o,p,bn,bp,...)	\
    HW_EOL(__VA_ARGS__)


/**
 * @page espressif_io1a
 * @section espressif_io1a_read State
 *
 * The instruction `hw_read()` returns the state of the I/O object:
 *
 * @code
 * uint8_t value = hw_read( IO_NAME );
 * @endcode
 */
#define _hw_read_io1a(o,i, p,bn,bp,...)		HW_TX(_hw_rdio1a_2(_##p,bn,bp),__VA_ARGS__)
#define _hw_rdio1a_2(...)			_hw_rdio1a_3(__VA_ARGS__)
#define _hw_rdio1a_3(c,i,a,bn,bp)		_hw_rdio1a_4(a,bn,bp,_hw_##c##_##hin)
#define _hw_rdio1a_4(...)			_hw_rdio1a_5(__VA_ARGS__)
#define _hw_rdio1a_5(a,bn,bp, rt,ra,rwm,rfm)	_hw_read_##rt(a+ra,bn,bp)


/**
 * @page espressif_io1a
 *
 * The instruction `hw_write()` changes the state of the I/O object:
 *
 * @code
 * hw_write( IO_NAME, value );
 * @endcode
 */
#define _hw_write_io1a(o,i, p,bn,bp, v,...)	HW_TX(_hw_wrio1a_2(_##p,bn,bp,v),__VA_ARGS__)
#define _hw_wrio1a_2(...)			_hw_wrio1a_3(__VA_ARGS__)
#define _hw_wrio1a_3(c,i,a,bn,bp,v)		_hw_wrio1a_4(a,bn,bp,v,_hw_##c##_##hout)
#define _hw_wrio1a_4(...)			_hw_wrio1a_5(__VA_ARGS__)
#define _hw_wrio1a_5(a,bn,bp,v, rt,ra,rwm,rfm)	\
  _hw_write__r32_m(a+ra,rwm,rfm,((1U<<bn)-1)<<bp,(v)<<bp)


/**
 * @page espressif_io1a
 * @code
 * hwa_write( IO_NAME, value );
 * @endcode
 */
/* #define _hwa_write_io1a(o,i, p,bn,bp, v, ...)		\ */
/*   HW_TX(_hwa_write__r8(&hwa->p.port, 0xFF,0x00, bn,bp, v),__VA_ARGS__) */


/**
 * @page espressif_io1a
 * @code
 * hw_toggle( IO_NAME );	//  Toggle one or several consecutive pins at once
 * @endcode
 */
/* #define _hw_toggle_io1a(o,i, p,...)		_hw_toggle_io1a_2(_hw_reg(p,pin),__VA_ARGS__) */
/* #define _hw_toggle_io1a_2(...)			_hw_toggle_io1a_3(__VA_ARGS__) */
/* #define _hw_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\ */
/*   HW_TX(_hw_write(_m1,p,a,r,rw,ra,rwm,rfm,bn,bp, 1),__VA_ARGS__) */


/**
 * @page espressif_io1a
 * @code
 * // All the pins of the same I/O port toggled in the same transaction will be
 * // toggled at once by the `hwa_commit()` instruction.
 * //
 * hwa_toggle( IO_NAME );
 * @endcode
 */
/* #define _hwa_toggle_io1a(o,i, p,...)		_hwa_toggle_io1a_2(_hw_reg(p,pin),__VA_ARGS__) */
/* #define _hwa_toggle_io1a_2(...)			_hwa_toggle_io1a_3(__VA_ARGS__) */
/* #define _hwa_toggle_io1a_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\ */
/*   HW_TX(_hwa_write(_m1,p,a,r,rw,ra,rwm,rfm,bn,bp, 1),__VA_ARGS__) */


/**
 * @page espressif_io1a
 * @section espressif_io1a_def Creating a I/O definition
 *
 * Creating an I/O definition allows giving a name to a set of consecutive pins
 * and benefit of the generic read/write instructions.
 *
 * A class `_io1a` I/O definition named `mypins` is created with:
 *
 *     #define _hw_pin_mypins		 _io1a, id, port, bn, bp
 *
 * where:
 *
 * * `id` is a unique number identifying the object. If you're not going to use
 *        the `hw_id()` instruction, any value (or even none) is OK.
 *
 * * `port` is the name of the I/O port object holding the pin, e.g.: `hw_port0`.
 *
 * * `bn` is the number of consecutive bits the I/O definition contains.
 *
 * * `bp` is the position of the least significant bit in the port.
 */

/**
 * @page espressif_io1a
 * <br>
 */
