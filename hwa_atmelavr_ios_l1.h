
/* This file is ca+rt of the HWA project.
 * Copyright (c) Christophe Duca+rquet <duca+rq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * \file
 * \brief	IO functions common to all Atmel AVR chips
 *
 *	Device-specific io definitions used by generic definitions declared in
 *	hwa___ios_l1.h.
 *
 * Available modes for IO pins:
 * - input
 * - input_analog
 * - input_digital
 * - input_pullup
 * - input_0pullup
 * - input_digital_pullup
 * - input_digital_0pullup
 * - input_analog_0pullup
 * - pullup
 * - nopullup
 * - output
 */


/*	IO mode encoding:
 *	  bit 0: set/clear ddr
 *	  bit 1: ddr value
 *	  bit 2: set/clear port (pullup)
 *	  bit 3: port value
 *	  bit 4: set/clear didr
 *	  bit 5: didr value
 */
#define hw_iomode_input				0x02	/* 00 0010 */
#define hw_iomode_output			0x03	/* 00 0011 */
#define hw_iomode_pullup			0x0C	/* 00 1100 */
#define hw_iomode_0pullup			0x08	/* 00 1000 */
#define hw_iomode_input_pullup			0x0E	/* 00 1110 */
#define hw_iomode_input_0pullup		0x0A	/* 00 1010 */
#define hw_iomode_input_digital			0x22	/* 10 0010 */
#define hw_iomode_input_digital_pullup		0x2E	/* 10 1110 */
#define hw_iomode_input_digital_0pullup	0x2A	/* 10 1010 */
#define hw_iomode_input_analog			0x32	/* 11 0010 */
#define hw_iomode_input_analog_0pullup		0x3A	/* 11 1010 */


#define hw_fn_hw_ctr_io				, _hw_ctr_io
#define _hw_ctr_io(t,n,i, cc,cn,ci,ca, ...)	cc,cn,ci,ca

#define hw_fn_hw_bn_io				, _hw_bn_io
#define _hw_bn_io(t,n,i, cc,cn,ci,ca, bn,bp)	bn

#define hw_fn_hw_bp_io				, _hw_bp_io
#define _hw_bp_io(t,n,i, cc,cn,ci,ca, bn,bp)	bp

#define hw_fn_hw_io_io				, _hw_io_io
#define _hw_io_io(...)				__VA_ARGS__


#if !defined __ASSEMBLER__

HW_INLINE void _hw_config_io( intptr_t ddr, uint8_t rwm1,
			      intptr_t port, uint8_t rwm2,
			      intptr_t didr, uint8_t rwm3,
			      uint8_t bn, uint8_t bp, uint8_t mode )
{
  if ( mode & 0x20 ) {	/* didr */
    if ( didr == -1 )
      HWA_ERR("no disable digital filter for this io port");
    else
      _hw_write_r8( didr, rwm3, bn, bp, -1 * ((mode & 0x10)!=0) & ((1<<bn)-1) );
  }

  if ( mode & 0x08 )	/* pull-up */
    _hw_write_r8( port, rwm2, bn, bp, -1 * ((mode & 0x04)!=0) & ((1<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    _hw_write_r8( ddr, rwm1, bn, bp, -1 * ((mode & 0x01)!=0) & ((1<<bn)-1) );
}


#define hw_config_io_isfn
#define hw_config_io( cn1,ctr,cc,cn,ca,bn,bp,mode )			\
  _hw_config_io_2(ca,hw_##cc##_ddr,hw_##cc##_port,hw_##cc##_didr,	\
		  bn,bp,hw_iomode_##mode)
#define _hw_config_io_2(...)	_hw_config_io_3(__VA_ARGS__)
#define _hw_config_io_3(ca,reg1,rw1,ra1,riv1,rwm1,		\
			reg2,rw2,ra2,riv2,rwm2,			\
			reg3,rw3,ra3,riv3,rwm3,			\
			bn,bp,mode)				\
  _hw_config_io(ca+ra1,rwm1,ca+ra2,rwm2,ca+ra3,rwm3,bn,bp,mode)


#define hw_read_io_isfn
#define hw_read_io(ion, ctr,cc,cn,ca, bn,bp)	\
  _hw_read_io_2(cn,ca,hw_##cc##_pin, bn,bp)
#define _hw_read_io_2(...)	_hw_read_io_3(__VA_ARGS__)
#define _hw_read_io_3(cn,ca, mem,reg,rw,ra,riv,rwm, bn,bp)	\
  _hw_read_r8(ca+ra,bn,bp)


#define hw_fn_hw_write_io		, _hw_write_io

#define _hw_write_io(t, ion,ioid, cc,cn,ci,ca, bn,bp, v)	\
  _hw_write_io_2(cn,ca,hw_##cc##_port, bn,bp,v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(cn,ca, reg,rw,ra,rrv,rwm, bn,bp,v)	\
  _hw_write_r8(ca+ra,rwm,bn,bp,v)


#define hw_fn_hw_toggle_io		, _hw_toggle_io

#define _hw_toggle_io(t, ion,ioid, cc,cn,ci,ca, bn,bp)	\
  _hw_toggle_io_2(cn,ca,hw_##cc##_pin, bn,bp)
#define _hw_toggle_io_2(...)	_hw_toggle_io_3(__VA_ARGS__)
#define _hw_toggle_io_3(cn,ca, reg,rw,ra,rrv,rwm, bn,bp)	\
  _hw_write_r8(ca+ra,rwm,bn,bp,(1U<<bn)-1)

#endif /* !defined __ASSEMBLER__ */
