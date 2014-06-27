
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
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
 * - input_nopullup
 * - input_digital_pullup
 * - input_digital_nopullup
 * - input_analog_nopullup
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
#define hw_iomode_nopullup			0x08	/* 00 1000 */
#define hw_iomode_input_pullup			0x0E	/* 00 1110 */
#define hw_iomode_input_nopullup		0x0A	/* 00 1010 */
#define hw_iomode_input_digital			0x22	/* 10 0010 */
#define hw_iomode_input_digital_pullup		0x2E	/* 10 1110 */
#define hw_iomode_input_digital_nopullup	0x2A	/* 10 1010 */
#define hw_iomode_input_analog			0x32	/* 11 0010 */
#define hw_iomode_input_analog_nopullup		0x3A	/* 11 1010 */


#if !defined __ASSEMBLER__

HW_INLINE void _hw_config_io( intptr_t ddr, uint8_t rwm1,
			      intptr_t port, uint8_t rwm2,
			      intptr_t didr, uint8_t rwm3,
			      uint8_t bn, uint8_t bp, uint8_t mode )
{
  if ( mode & 0x20 ) {	/* didr */
    if ( didr == -1 )
      HW_RTERROR("no disable digital filter for this io port");
    else
      hw_write_8( didr, rwm3, bn, bp, -1 * ((mode & 0x10)!=0) & ((1<<bn)-1) );
  }

  if ( mode & 0x08 )	/* pull-up */
    hw_write_8( port, rwm2, bn, bp, -1 * ((mode & 0x04)!=0) & ((1<<bn)-1) );

  if ( mode & 0x02 )	/* ddr */
    hw_write_8( ddr, rwm1, bn, bp, -1 * ((mode & 0x01)!=0) & ((1<<bn)-1) );
}


#define hw_config_io_isfn
#define hw_config_io( pn1,per,pn,pc,pa,bn,bp,mode )			\
  _hw_config_io_2(pa,HW_G3(hw,pc,ddr),HW_G3(hw,pc,port),HW_G3(hw,pc,didr), \
		  bn,bp,HW_G2(hw_iomode,mode))
#define _hw_config_io_2(...)	_hw_config_io_3(__VA_ARGS__)
#define _hw_config_io_3(pa,reg1,rn1,rw1,ra1,riv1,rwm1,		\
			reg2,rn2,rw2,ra2,riv2,rwm2,		\
			reg3,rn3,rw3,ra3,riv3,rwm3,		\
			bn,bp,mode)				\
  _hw_config_io(pa+ra1,rwm1,pa+ra2,rwm2,pa+ra3,rwm3,bn,bp,mode)


#define hw_read_io_isfn
#define hw_read_io( pn1,per,pn,pc,pa, bn, bp )	\
  _hw_read_io_2(pn,pa,HW_G3(hw,pc,port), bn, bp)
#define _hw_read_io_2(...)	_hw_read_io_3(__VA_ARGS__)
#define _hw_read_io_3(pn,pa,reg,rn,rw,ra,riv,rwm,bn,bp)	\
  hw_read_8(pa+ra,bn,bp)


#define hw_write_io( pn1,per,pn,pc,pa, bn, bp, v )	\
  _hw_write_io_2(pn,pa,HW_G3(hw,pc,port), bn, bp, v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(pn,pa,reg,rn,rw,ra,riv,rwm,rbn,rbp,v)	\
  hw_write_8(pa+ra,rwm,rbn,rbp,v)


#define hw_write_io_isfn
#define hw_write_io( pn1,per,pn,pc,pa, bn, bp, v )	\
  _hw_write_io_2(pn,pa,HW_G3(hw,pc,port), bn, bp, v)
#define _hw_write_io_2(...)	_hw_write_io_3(__VA_ARGS__)
#define _hw_write_io_3(pn,pa,reg,rn,rw,ra,riv,rwm,rbn,rbp,v)	\
  hw_write_8(pa+ra,rwm,rbn,rbp,v)


#define hw_toggle_io_isfn
#define hw_toggle_io( pn1,per,pn,pc,pa, bn,bp)	\
  _hw_toggle_io_2(pn,pa,HW_G3(hw,pc,pin), bn,bp)
#define _hw_toggle_io_2(...)	_hw_toggle_io_3(__VA_ARGS__)
#define _hw_toggle_io_3(pn,pa,reg,rn,rw,ra,riv,rwm, bn,bp)	\
  hw_write_8(pa+ra,rwm,bn,bp,(1U<<bn)-1)


/**
 * \brief	Sets to 1 \c bn bits from position \c bp in register \c reg.
 *
 *	If only one bit has to be set, use sbi to set the bit. Otherwise, use
 *	ldi/out and clear other bits.
 */
/* HW_INLINE void hw_write_ones_r8( uint8_t *reg, uint8_t bn, uint8_t bp ) */
/* { */
/*   uint8_t mask = ((1<<bn)-1)<<bp ; */

/*   if ( bn == 1 ) */
/*     hw_write_r8( reg, -1, mask, 0, mask ); */
/*   else */
/*     hw_write_r8( reg, -1, -1, 0, mask ); */
/* } */

#endif /* !defined __ASSEMBLER__ */
