
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hw_def_hw_config_io			, _hw_config_io

#define _hw_config_io( io,ion,ioi, c,n,i,a,bn,bp,mode )			\
  _hw_config_io_2(a,hw_##c##_ddr,hw_##c##_port,				\
		    bn,bp,hw_iomode_##mode)
#define _hw_config_io_2(...)	_hw_config_io_3(__VA_ARGS__)
#define _hw_config_io_3(a,reg1,rw1,ra1,rwm1,rfm1,		\
			reg2,rw2,ra2,rwm2,rfm2,			\
			bn,bp,mode)				\
  __hw_config_io(a+ra1,rwm1,a+ra2,rwm2,bn,bp,mode)


#define hw_def_hw_read_io			, _hw_read_io
#define _hw_read_io(t, ion,ioid, c,n,i,a, bn,bp)	\
  _hw_read_io_2(n,a,hw_##c##_pin, bn,bp)
#define _hw_read_io_2(...)	_hw_read_io_3(__VA_ARGS__)
#define _hw_read_io_3(n,a, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_read_r8(a+ra,bn,bp)


#define hw_def_hw_write_io			, _hw_write_io
#define _hw_write_io(t, ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hw_write_io_2(cn,ca,hw_##cc##_port, bn,bp,v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp,v)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,v)


#define hw_def_hw_toggle_io			, _hw_toggle_io
#define _hw_toggle_io(t, ion,ioid, cc,cn,ci,ca, bn,bp)	\
  _hw_toggle_io_2(cn,ca,hw_##cc##_pin, bn,bp)
#define _hw_toggle_io_2(...)	_hw_toggle_io_3(__VA_ARGS__)
#define _hw_toggle_io_3(cn,ca, reg,rw,ra,rwm,rfm, bn,bp)	\
  _hw_write_r8(ca+ra,rwm,rfm,bn,bp,(1U<<bn)-1)


/*
 * Available modes for IO pins:
 * - input
 * - input_pullup
 * - input_nopullup
 * - pullup
 * - nopullup
 * - output
 *
 *
 *	IO mode encoding:
 *	  bit 0: set/clear ddr
 *	  bit 1: ddr value
 *	  bit 2: set/clear port (pullup)
 *	  bit 3: port value
 */
#define hw_iomode_input				0x02	/* 00 0010 */
#define hw_iomode_output			0x03	/* 00 0011 */
#define hw_iomode_pullup			0x0C	/* 00 1100 */
#define hw_iomode_nopullup			0x08	/* 00 1000 */
#define hw_iomode_input_pullup			0x0E	/* 00 1110 */
#define hw_iomode_input_nopullup		0x0A	/* 00 1010 */


HW_INLINE void __hw_config_io( intptr_t ddr, uint8_t rwm1,
			       intptr_t port, uint8_t rwm2,
			       uint8_t bn, uint8_t bp, uint8_t mode )
{
  if ( mode & 0x08 )	/* pull-up */
    _hw_write_r8( port, rwm2,0, bn, bp, -1 * ((mode & 0x04)!=0) & ((1<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    _hw_write_r8( ddr, rwm1,0, bn, bp, -1 * ((mode & 0x01)!=0) & ((1<<bn)-1) );
}


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

#define _hwa_write_io(t, ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hwa_write_r8(&hwa->cn.port, 0xFF,0x00, bn,bp, v)
