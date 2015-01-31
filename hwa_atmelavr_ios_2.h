
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hw_def_hw_config_io		, _hw_cfio
#define hw_def_hwa_config_io		, _hwa_cfio
#define hw_def_hw_read_io		, _hw_read_io
#define hw_def_hw_write_io		, _hw_write_io
#define hw_def_hwa_write_io		, _hwa_write_io
#define hw_def_hw_toggle_io		, _hw_toggle_io


#define hw_is_direction_direction	, 1
#define hw_cfio_direction_input		, 0
#define hw_cfio_direction_output	, 1

#define hw_is_pullup_pullup		, 1


/*	Config io (synchronous)
 */
#define _hw_cfio( io,ion,ioi, c,n,i,a, bn, bp, ...)			\
  do {									\
    HW_G2(_hw_cfio_xdirection, HW_IS(direction,__VA_ARGS__))(ion,a,c,bn,bp,__VA_ARGS__) \
      } while(0)

#define _hw_cfio_xdirection_1(ion,a,c,bn,bp,kw,...)			\
  HW_G2(_hw_cfio_vdirection, HW_IS(,hw_cfio_direction_##__VA_ARGS__))(ion,a,c,bn,bp,__VA_ARGS__)

#define _hw_cfio_vdirection_1(ion,a,c,bn,bp,v,...)			\
  _hw_write(_hw_reg_cb1(c,,a,,ddr,bn,bp), (HW_A1(hw_cfio_direction_##v)?(1U<<bn)-1:0));	\
  HW_G2(_hw_cfio_xpullup, HW_IS(pullup,__VA_ARGS__))(ion,a,c,bn,bp,__VA_ARGS__)

#define _hw_cfio_vdirection_0(ion,a,c,bn,bp,v,...)			\
  HW_ERR("`direction` must be `input` or `output`, not `" HW_QUOTE(v) "`.")

#define _hw_cfio_xdirection_0(ion,a,c,bn,bp,...)			\
  HW_G2(_hw_cfio_xpullup, HW_IS(pullup,__VA_ARGS__))(ion,a,c,bn,bp,__VA_ARGS__)

#define _hw_cfio_xpullup_0(ion,a,c,bn,bp,...)\
  HW_TX(,__VA_ARGS__)

#define _hw_cfio_xpullup_1(ion,a,c,bn,bp,kw,...)			\
  HW_G2(_hw_cfio_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(ion,a,c,bn,bp,__VA_ARGS__)

#define _hw_cfio_vpullup_1(ion,a,c,bn,bp,v,...)			\
  _hw_write(_hw_reg_cb1(c,,a,,port,bn,bp), (HW_A1(hw_state_##v)?(1U<<bn)-1:0));	\
  HW_TX(,__VA_ARGS__)

#define _hw_cfio_vpullup_0(ion,a,c,bn,bp,v,...)			\
  HW_ERR("`pullup` must be `on` or `off`, not `" HW_QUOTE(v) "`.");

#define _hwa_cfio( io,ion,ioi, c,n,i,a, bn, bp, ...)			\
  do {									\
      HW_G2(_hwa_cfio_xdirection, HW_IS(direction,__VA_ARGS__))(n,bn,bp,__VA_ARGS__,) \
      } while(0)


/*	Config io (asynchronous)
 */
#define _hwa_cfio_xdirection_1(n,bn,bp,kw,...)			\
  HW_G2(_hwa_cfio_vdirection, HW_IS(,hw_cfio_direction_##__VA_ARGS__))(n,bn,bp,__VA_ARGS__)

#define _hwa_cfio_vdirection_1(n,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->n.ddr, 0xFF,0, bn,bp, (HW_A1(hw_cfio_direction_##v)?(1U<<bn)-1:0));	\
  HW_G2(_hwa_cfio_xpullup, HW_IS(pullup,__VA_ARGS__))(n,bn,bp,__VA_ARGS__)

#define _hwa_cfio_vdirection_0(n,bn,bp,v,...)			\
  HW_ERR("`direction` must be `input` or `output`, not `" HW_QUOTE(v) "`.")

#define _hwa_cfio_xdirection_0(n,bn,bp,...)			\
  HW_G2(_hwa_cfio_xpullup, HW_IS(pullup,__VA_ARGS__))(n,bn,bp,__VA_ARGS__)

#define _hwa_cfio_xpullup_0(n,bn,bp,...)	\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfio_xpullup_1(n,bn,bp,kw,...)			\
  HW_G2(_hwa_cfio_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(n,bn,bp,__VA_ARGS__)

#define _hwa_cfio_vpullup_1(n,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->n.port, 0xFF,0, bn,bp, (HW_A1(hw_state_##v)?(1U<<bn)-1:0) );\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfio_vpullup_0(n,bn,bp,v,...)			\
  HW_ERR("`pullup` must be `on` or `off`, not `" HW_QUOTE(v) "`.");


/*	Read io
 */
#define _hw_read_io(io,ion,ioid, c,n,i,a, bn,bp)	\
  _hw_read_io_2(n,a,hw_##c##_pin, bn,bp)
#define _hw_read_io_2(...)	_hw_read_io_3(__VA_ARGS__)
#define _hw_read_io_3(n,a, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_read_r8(a+ra,bn,bp)


/*	Write io
 */
#define _hw_write_io(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hw_write_io_2(cn,ca,hw_##cc##_port, bn,bp,v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp,v)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,v)

#define _hwa_write_io(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hwa_write_r8(&hwa->cn.port, 0xFF,0x00, bn,bp, v)


/*	Toggle io
 */
#define _hw_toggle_io(io,ion,ioid, cc,cn,ci,ca, bn,bp,...)	\
  HW_TX(_hw_toggle_io_2(cn,ca,hw_##cc##_pin, bn,bp),__VA_ARGS__)
#define _hw_toggle_io_2(...)	_hw_toggle_io_3(__VA_ARGS__)
#define _hw_toggle_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,(1U<<bn)-1)
