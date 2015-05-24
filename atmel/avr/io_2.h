
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

HW_INLINE void __hwa_begin__io8a ( hwa_io8a_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _io8a, port );
  _hwa_begin_reg_p( p, a, _io8a, ddr  );
}


HW_INLINE void __hwa_init__io8a ( hwa_io8a_t *p )
{
  _hwa_set_r8( &p->port, 0x00 );
  _hwa_set_r8( &p->ddr,  0x00 );
}


HW_INLINE void __hwa_commit__io8a ( hwa_t *hwa, hwa_io8a_t *p )
{
  _hwa_commit_reg_p( p, _io8a, port );
  _hwa_commit_reg_p( p, _io8a, ddr  );
}


#define __hwa_begin__io6a		__hwa_begin__io8a
#define __hwa_init__io6a		__hwa_init__io8a
#define __hwa_commit__io6a		__hwa_commit__io8a


#define _hw_mthd_hw_config__pin1		, _hw_cfdio
#define _hw_mthd_hwa_config__pin1	, _hwa_cfdio
#define _hw_mthd_hw_read__pin1		, _hw_read_pin1
#define _hw_mthd_hw_write__pin1		, _hw_write_pin1
#define _hw_mthd_hwa_write__pin1		, _hwa_write_pin1
#define _hw_mthd_hw_toggle__pin1		, _hw_toggle_pin1


#define _hw_is_mode_mode		, 1
#define hw_cfdio_mode_digital		, 0
#define hw_cfdio_mode_analog		, 1

#define _hw_is_direction_direction	, 1
#define hw_cfdio_direction_input	, 0
#define hw_cfdio_direction_output	, 1

#define _hw_is_pullup_pullup		, 1


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_config Configuring i/o pins
 *
 * An i/o pin (or group of pins) is configured using the `hw_config(...)` or
 * `hwa_config(...)` instruction.
 *
 * @code
 * #define PIN		hw_pin_pa2
 *
 * hw_config( PIN,
 *
 *            [direction,   input,
 *                        | output,]
 *
 *            [pullup,      on,
 *                        | off] );
 * @endcode
 */
#define _hw_cfdio( p,i, pn,bn,bp, ...)				\
  do {									\
    HW_G2(_hw_cfdio_xdirection, HW_IS(direction,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__) \
      } while(0)

#define _hw_cfdio_xdirection_1(pn,bn,bp,kw,...)			\
  HW_G2(_hw_cfdio_vdirection, HW_IS(,hw_cfdio_direction_##__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

//  do { _hw_cfdio_vdirection_1(porta,1,6,output,) } while(0);
#define _hw_cfdio_vdirection_1(pn,bn,bp,v,...)			\
  _hw_write_bits(_hw_reg(pn,ddr),bn,bp, (HW_A1(hw_cfdio_direction_##v)?(1U<<bn)-1:0)); \

#define _hw_cfdio_vdirection_0(pn,bn,bp,v,...)			\
  HW_ERR("`direction` must be `input` or `output`, not `" HW_QUOTE(v) "`.")

#define _hw_cfdio_xdirection_0(pn,bn,bp,...)			\
  HW_G2(_hw_cfdio_xpullup, HW_IS(pullup,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hw_cfdio_xpullup_0(pn,bn,bp,...)\
  HW_TX(,__VA_ARGS__)

#define _hw_cfdio_xpullup_1(pn,bn,bp,kw,...)			\
  HW_G2(_hw_cfdio_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hw_cfdio_vpullup_1(pn,bn,bp,v,...)			\
  _hw_write(_hw_reg_cb1b(pn,port,bn,bp), (HW_A1(hw_state_##v)?(1U<<bn)-1:0)); \
  HW_TX(,__VA_ARGS__)

#define _hw_cfdio_vpullup_0(pn,bn,bp,v,...)			\
  HW_ERR("`pullup` must be `on` or `off`, not `" HW_QUOTE(v) "`.");


/**
 * @page atmelavr_pin1
 * @code
 * #define PIN		hw_pin_pa2
 *
 * hwa_config( PIN,
 *
 *            [mode,        analog,
 *                        | digital,]
 *
 *            [direction,   input,
 *                        | output,]
 *
 *            [pullup,      on,
 *                        | off] );
 * @endcode
 */

#define _hwa_cfdio( p,i, pn,bn,bp, ...)					\
  do {									\
    HW_G2(_hwa_cfdio_xmode, HW_IS(mode,__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__); \
  } while(0)

#define _hwa_cfdio_xmode_1(p,pn,bn,bp,kw,...)				\
  HW_G2(_hwa_cfdio_vmode, HW_IS(,hw_cfdio_mode_##__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vmode_0(p,pn,bn,bp,v,...)				\
  HW_ERR("`mode` must be `analog` or `digital`, not `" HW_QUOTE(v) "`.")

#define _hwa_cfdio_vmode_1(p,pn,bn,bp,v,...)				\
  HW_G2(_hwa_cfdio_vmode, v)(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vmode_analog(p,pn,bn,bp,...)				\
  HW_G2(_hwa_cfdio_vmode_analog, HW_IS(,_##p##_##did))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vmode_analog_0(p,pn,bn,bp,...)	\
  HW_ERR("pin `"#p"` does not support analog mode.")

#define _hwa_cfdio_vmode_analog_1(p,pn,bn,bp,...)	\
  _hwa_cfdio_analog2(p,pn,bn,bp,_##p##_##did,__VA_ARGS__)

#define _hwa_cfdio_analog2(...)		_hwa_cfdio_analog3(__VA_ARGS__)

#define _hwa_cfdio_analog3(p,pn,bn,bp,_,cn,m,...)	\
  _hwa_write_reg( cn, m, 1);			\
  _hwa_cfdio_xmode_0(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vmode_digital	_hwa_cfdio_xmode_0

#define _hwa_cfdio_xmode_0(p,pn,bn,bp,...)				\
  HW_G2(_hwa_cfdio_xdirection, HW_IS(direction,__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__) \

#define _hwa_cfdio_xdirection_1(p,pn,bn,bp,kw,...)				\
  HW_G2(_hwa_cfdio_vdirection, HW_IS(,hw_cfdio_direction_##__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vdirection_1(p,pn,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->pn.ddr, 0xFF,0, bn,bp, (HW_A1(hw_cfdio_direction_##v)?(1U<<bn)-1:0));	\
  HW_G2(_hwa_cfdio_xpullup, HW_IS(pullup,__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vdirection_0(p,pn,bn,bp,v,...)			\
  HW_ERR("`direction` must be `input` or `output`, not `" HW_QUOTE(v) "`.")

#define _hwa_cfdio_xdirection_0(p,pn,bn,bp,...)			\
  HW_G2(_hwa_cfdio_xpullup, HW_IS(pullup,__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_xpullup_0(p,pn,bn,bp,...)	\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfdio_xpullup_1(p,pn,bn,bp,kw,...)			\
  HW_G2(_hwa_cfdio_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(p,pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vpullup_1(p,pn,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->pn.port, 0xFF,0, bn,bp, (HW_A1(hw_state_##v)?(1U<<bn)-1:0) );\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfdio_vpullup_0(p,pn,bn,bp,v,...)				\
  HW_ERR("`pullup` must be `on` or `off`, not `" HW_QUOTE(v) "`.")


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_read Reading a digital i/o pin
 *
 * @code
 * uint8_t p = hw_read( PIN );
 * @endcode
 */
#define _hw_read_pin1(p,i, pn,bn,bp)	_hw_rddio_2(_##pn,bn,bp)
#define _hw_rddio_2(...)		_hw_rddio_3(__VA_ARGS__)
#define _hw_rddio_3(c,i,a,bn,bp)	_hw_rddio_4(a,bn,bp,_hw_##c##_##port)
#define _hw_rddio_4(...)		_hw_rddio_5(__VA_ARGS__)
#define _hw_rddio_5(a,bn,bp, rt,rw,ra,rwm,rfm)	\
  _hw_read_r8(a+ra,rwm,rfm,bn,bp)


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_write Writing a digital i/o pin
 *
 * @code
 * hw/hwa_write( PIN, 1 );
 * @endcode
 */
#define _hw_write_pin1(p,i, pn,bn,bp, v,...)	HW_TX(_hw_wrdio_2(_##pn,bn,bp,v),__VA_ARGS__)
#define _hw_wrdio_2(...)		_hw_wrdio_3(__VA_ARGS__)
#define _hw_wrdio_3(c,i,a,bn,bp,v)	_hw_wrdio_4(a,bn,bp,v,_hw_##c##_##port)
#define _hw_wrdio_4(...)		_hw_wrdio_5(__VA_ARGS__)
#define _hw_wrdio_5(a,bn,bp,v, rt,rw,ra,rwm,rfm)	\
  _hw_write_r8(a+ra,rwm,rfm,bn,bp,v)

#define _hwa_write_pin1(p,i, pn,bn,bp, v, ...)		\
  HW_TX(_hwa_write_r8(&hwa->pn.port, 0xFF,0x00, bn,bp, v),__VA_ARGS__)


/**
 * @page atmelavr_pin1
 * @section atmelavr_pin1_toggle Toggling a digital i/o pin
 *
 * @code
 * hw_toggle( PIN );
 * @endcode
 */
#define _hw_toggle_pin1(p,i, port,...)			\
  _hw_toggle_pin1_2(_hw_reg(port,pin),__VA_ARGS__)
#define _hw_toggle_pin1_2(...)	_hw_toggle_pin1_3(__VA_ARGS__)
#define _hw_toggle_pin1_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hw_write(_m1,p,a,r,rw,ra,rwm,rfm,bn,bp, 1),__VA_ARGS__)
