
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
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


#define hw_mthd_hw_config__dio		, _hw_cfdio
#define hw_mthd_hwa_config__dio		, _hwa_cfdio
#define hw_mthd__hwa_config__dio		, __hwa_cfdio
#define hw_mthd_hw_read__dio		, _hw_read_dio
#define hw_mthd_hw_write__dio		, _hw_write_dio
#define hw_mthd_hwa_write__dio		, _hwa_write_dio
#define hw_mthd_hw_toggle__dio		, _hw_toggle_dio


#define _hw_is_direction_direction	, 1
#define hw_cfdio_direction_input	, 0
#define hw_cfdio_direction_output	, 1

#define _hw_is_pullup_pullup		, 1


/*	Config io (synchronous)
 */
//  _hw_cfdio(pin_7,307, porta, 1, 6,direction, output,);
#define _hw_cfdio( p,i, pn,bn,bp, ...)					\
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



/*	Config io (asynchronous)
 */
#define __hwa_cfdio(t, ...)		_hwa_cfdio(__VA_ARGS__,)

// _hwa_cfdio(_dio,pin_pa5,306, porta, 1, 5,direction, output,);
#define _hwa_cfdio( ion,ioid, pn,bn,bp, ...)			\
  do {									\
    HW_G2(_hwa_cfdio_xdirection, HW_IS(direction,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__) \
      } while(0)

#define _hwa_cfdio_xdirection_1(pn,bn,bp,kw,...)				\
  HW_G2(_hwa_cfdio_vdirection, HW_IS(,hw_cfdio_direction_##__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vdirection_1(pn,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->pn.ddr, 0xFF,0, bn,bp, (HW_A1(hw_cfdio_direction_##v)?(1U<<bn)-1:0));	\
  HW_G2(_hwa_cfdio_xpullup, HW_IS(pullup,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vdirection_0(pn,bn,bp,v,...)			\
  HW_ERR("`direction` must be `input` or `output`, not `" HW_QUOTE(v) "`.")

#define _hwa_cfdio_xdirection_0(pn,bn,bp,...)			\
  HW_G2(_hwa_cfdio_xpullup, HW_IS(pullup,__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_xpullup_0(pn,bn,bp,...)	\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfdio_xpullup_1(pn,bn,bp,kw,...)			\
  HW_G2(_hwa_cfdio_vpullup, HW_IS(,hw_state_##__VA_ARGS__))(pn,bn,bp,__VA_ARGS__)

#define _hwa_cfdio_vpullup_1(pn,bn,bp,v,...)			\
  _hwa_write_r8( &hwa->pn.port, 0xFF,0, bn,bp, (HW_A1(hw_state_##v)?(1U<<bn)-1:0) );\
  HW_TX(,__VA_ARGS__)

#define _hwa_cfdio_vpullup_0(pn,bn,bp,v,...)			\
  HW_ERR("`pullup` must be `on` or `off`, not `" HW_QUOTE(v) "`.");


/*	Read _dio
 */
#define _hw_read_dio(io,ion,ioid, c,n,i,a, bn,bp)	\
  _hw_read_dio_2(n,a,_hw_##c##_pin, bn,bp)
#define _hw_read_dio_2(...)	_hw_read_dio_3(__VA_ARGS__)
#define _hw_read_dio_3(n,a, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_read_r8(a+ra,bn,bp)


/*	Write _dio
 */
#define _hw_write_dio(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hw_write_dio_2(cn,ca,hw_##cc##_port, bn,bp,v)
#define _hw_write_dio_2(...)	_hw_write_dio_3(__VA_ARGS__)
#define _hw_write_dio_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp,v)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,v)

#define _hwa_write_dio(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hwa_write_r8(&hwa->cn.port, 0xFF,0x00, bn,bp, v)


/*	Toggle _dio
 */
#define _hw_toggle_dio(p,i, port,...)			\
  _hw_toggle_dio_2(_hw_reg(port,pin),__VA_ARGS__)
#define _hw_toggle_dio_2(...)	_hw_toggle_dio_3(__VA_ARGS__)
#define _hw_toggle_dio_3(_m1,p,a,r,rw,ra,rwm,rfm,_bn,_bp,bn,bp,...)	\
  HW_TX(_hw_write(_m1,p,a,r,rw,ra,rwm,rfm,bn,bp, 1),__VA_ARGS__)
