
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */

/**
 * @page stm32_p16a Class _p16a: 16-bit GPIO port
 *
 * A class `_p16a` object is a 16-bit GPIO port.
 */
#define hw_class__p16a

/*	Class registers			class, address, rwm, rfm
 */
#define hw__p16a_crl			_r32, 0x00, 0xffffffff, 0
#define hw__p16a_crh			_r32, 0x04, 0xffffffff, 0
#define hw__p16a_idr			_r32, 0x08, 0x00000000, 0
#define hw__p16a_odr			_r32, 0x0C, 0x0000ffff, 0
#define hw__p16a_bsrr			_r32, 0x10, 0xffffffff, 0xffffffff
#define hw__p16a_brr			_r32, 0x14, 0xffffffff, 0xffffffff
#define hw__p16a_lckr			_r32, 0x18, 0x0001ffff, 0

#define hw__p16a_cnf_15			_cb1, crh, 2, 30
#define hw__p16a_mode_15		_cb1, crh, 2, 28
#define hw__p16a_cnf_14			_cb1, crh, 2, 26
#define hw__p16a_mode_14		_cb1, crh, 2, 24
#define hw__p16a_cnf_13			_cb1, crh, 2, 22
#define hw__p16a_mode_13		_cb1, crh, 2, 20
#define hw__p16a_cnf_12			_cb1, crh, 2, 18
#define hw__p16a_mode_12		_cb1, crh, 2, 16
#define hw__p16a_cnf_11			_cb1, crh, 2, 14
#define hw__p16a_mode_11		_cb1, crh, 2, 12
#define hw__p16a_cnf_10			_cb1, crh, 2, 10
#define hw__p16a_mode_10		_cb1, crh, 2,  8
#define hw__p16a_cnf_9			_cb1, crh, 2,  6
#define hw__p16a_mode_9			_cb1, crh, 2,  4
#define hw__p16a_cnf_8			_cb1, crh, 2,  2
#define hw__p16a_mode_8			_cb1, crh, 2,  0

#define hw__p16a_cnf_7			_cb1, crl, 2, 30
#define hw__p16a_mode_7			_cb1, crl, 2, 28
#define hw__p16a_cnf_6			_cb1, crl, 2, 26
#define hw__p16a_mode_6			_cb1, crl, 2, 24
#define hw__p16a_cnf_5			_cb1, crl, 2, 22
#define hw__p16a_mode_5			_cb1, crl, 2, 20
#define hw__p16a_cnf_4			_cb1, crl, 2, 18
#define hw__p16a_mode_4			_cb1, crl, 2, 16
#define hw__p16a_cnf_3			_cb1, crl, 2, 14
#define hw__p16a_mode_3			_cb1, crl, 2, 12
#define hw__p16a_cnf_2			_cb1, crl, 2, 10
#define hw__p16a_mode_2			_cb1, crl, 2,  8
#define hw__p16a_cnf_1			_cb1, crl, 2,  6
#define hw__p16a_mode_1			_cb1, crl, 2,  4
#define hw__p16a_cnf_0			_cb1, crl, 2,  2
#define hw__p16a_mode_0			_cb1, crl, 2,  0

/*  Access 'mode' bits in crl/crh from a pin. [_HW_OX26]
 */
#define hw__io1a_mode			, _hw_io1a_mode

#define _hw_io1a_mode(...)		_hw_io1a_mode10(__VA_ARGS__)
#define _hw_io1a_mode10(o,p,bn,bp)	HW_Y(_hw_io1a_mode10_,_hw_is_1_##bn)(o,p,bn,bp)
#define _hw_io1a_mode10_0(o,p,bn,bp)	,o,"is not a single pin"
#define _hw_io1a_mode10_1(o,p,bn,bp)	_hw_io1a_mode20(o,p,bp,hw__p16a_mode_##bp,hw_##p)
#define _hw_io1a_mode20(...)		_hw_io1a_mode21(__VA_ARGS__)
#define _hw_io1a_mode21(pin,o,bp,cr,r,rbn,rbp,c,d)	c,o,(d),x, cr,r,rbn,rbp

/*  Access 'cnf' bits in crl/crh from a pin. [_HW_OX26]
 */
#define hw__io1a_cnf			, _hw_io1a_cnf

#define _hw_io1a_cnf(...)		_hw_io1a_cnf10(__VA_ARGS__)
#define _hw_io1a_cnf10(o,p,bn,bp)	HW_Y(_hw_io1a_cnf10_,_hw_is_1_##bn)(o,p,bn,bp)
#define _hw_io1a_cnf10_0(o,p,bn,bp)	,o,"is not a single pin"
#define _hw_io1a_cnf10_1(o,p,bn,bp)	_hw_io1a_cnf20(o,p,bp,hw__p16a_cnf_##bp,hw_##p)
#define _hw_io1a_cnf20(...)		_hw_io1a_cnf21(__VA_ARGS__)
#define _hw_io1a_cnf21(pin,port,bp,cr,r,rbn,rbp,cp,ca)	cp,port,(ca),x,cr,r,rbn,rbp


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t crl ;
  hwa_r32_t crh ;
  hwa_r32_t idr ;
  hwa_r32_t odr ;
  hwa_r32_t bsrr;
  hwa_r32_t brr ;
  hwa_r32_t lckr;

  uint32_t	toggles ;
} hwa_p16a_t ;

#endif
