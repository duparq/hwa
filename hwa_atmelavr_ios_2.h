
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hw_def_hw_config_io			, _hw_cfio


#define hw_is_direction_direction	, 1
#define hw_cfio_direction_input		, 0
#define hw_cfio_direction_output	, 1

#define hw_is_pullup_pullup		, 1

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


#define hw_def_hw_read_io			, _hw_read_io
#define _hw_read_io(io,ion,ioid, c,n,i,a, bn,bp)	\
  _hw_read_io_2(n,a,hw_##c##_pin, bn,bp)
#define _hw_read_io_2(...)	_hw_read_io_3(__VA_ARGS__)
#define _hw_read_io_3(n,a, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_read_r8(a+ra,bn,bp)


#define hw_def_hw_write_io			, _hw_write_io
#define _hw_write_io(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hw_write_io_2(cn,ca,hw_##cc##_port, bn,bp,v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp,v)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,v)


#define hw_def_hw_toggle_io			, _hw_toggle_io
#define _hw_toggle_io(io,ion,ioid, cc,cn,ci,ca, bn,bp,...)	\
  HW_TX(_hw_toggle_io_2(cn,ca,hw_##cc##_pin, bn,bp),__VA_ARGS__)
#define _hw_toggle_io_2(...)	_hw_toggle_io_3(__VA_ARGS__)
#define _hw_toggle_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,(1U<<bn)-1)




#define hw_def_hwa_config_io		, hwa_config_io
#define hwa_config_io(t,ion,ioid, cc,cn,cid,ca, bn, bp, mode)	\
  _hwa_config_io(&hwa->cn, bn, bp, hw_iomode_##mode)


/** \brief Configures one or more consecutive i/o pins
 *  \param p	pointer to i/o port instance in hwa struct
 *  \param bn	number of consecutive bits to configure
 *  \param bp   position of least significant bit to configure
 *  \param mode	pin(s) mode
 */
HW_INLINE void _hwa_config_io( hwa_io_t *p, uint8_t bn, uint8_t bp, uint8_t mode )
{
  if ( mode & 0x08 )	/* pull-up */
    _hwa_write_r8( &p->port, 0xFF,0, bn,bp, ((mode & 0x04)!=0)*((1U<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    _hwa_write_r8( &p->ddr, 0xFF,0, bn,bp, ((mode & 0x01)!=0)*((1U<<bn)-1) );
}


#define hw_def_hwa_write_io		, _hwa_write_io

#define _hwa_write_io(io,ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hwa_write_r8(&hwa->cn.port, 0xFF,0x00, bn,bp, v)
