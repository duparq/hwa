
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */

/**
 * @page stm32_gpa Class _gpa: 16-bit GPIO port
 *
 * A class `_gpa` object is a 16-bit GPIO port.
 */
#define hw_class__gpa


/*  Accept to append a number to a _gpa definition so that (portx,n) becomes a
 *  single pin at position n of portx.
 */
#define hw__gpa_			, _hw_gpa_
#define _hw_gpa_(o,n,a)			HW_BX(_hw_gpa_,_hw_isa_4bn_,n)(o,n)
#define _hw_gpa_1(o,n)			_ioa,o##_1_##n,(o,1,n)
#define _hw_gpa_0(o,n)			,(o,n),HW_EM(o has no relative n)


/*	Class registers			class, address, rwm, rfm
 */
#define hw__gpa_crl			_r32, 0x00, 0xffffffff, 0
#define hw__gpa_crh			_r32, 0x04, 0xffffffff, 0
#define hw__gpa_idr			_r32, 0x08, 0x00000000, 0
#define hw__gpa_odr			_r32, 0x0C, 0x0000ffff, 0
#define hw__gpa_bsrr			_r32, 0x10, 0xffffffff, 0xffffffff
#define hw__gpa_brr			_r32, 0x14, 0xffffffff, 0xffffffff
#define hw__gpa_lckr			_r32, 0x18, 0x0001ffff, 0

#define hw__gpa_cnf15			_cb1, crh, 2, 30
#define hw__gpa_mode15			_cb1, crh, 2, 28
#define hw__gpa_cnf14			_cb1, crh, 2, 26
#define hw__gpa_mode14			_cb1, crh, 2, 24
#define hw__gpa_cnf13			_cb1, crh, 2, 22
#define hw__gpa_mode13			_cb1, crh, 2, 20
#define hw__gpa_cnf12			_cb1, crh, 2, 18
#define hw__gpa_mode12			_cb1, crh, 2, 16
#define hw__gpa_cnf11			_cb1, crh, 2, 14
#define hw__gpa_mode11			_cb1, crh, 2, 12
#define hw__gpa_cnf10			_cb1, crh, 2, 10
#define hw__gpa_mode10			_cb1, crh, 2,  8
#define hw__gpa_cnf9			_cb1, crh, 2,  6
#define hw__gpa_mode9			_cb1, crh, 2,  4
#define hw__gpa_cnf8			_cb1, crh, 2,  2
#define hw__gpa_mode8			_cb1, crh, 2,  0

#define hw__gpa_cnf7			_cb1, crl, 2, 30
#define hw__gpa_mode7			_cb1, crl, 2, 28
#define hw__gpa_cnf6			_cb1, crl, 2, 26
#define hw__gpa_mode6			_cb1, crl, 2, 24
#define hw__gpa_cnf5			_cb1, crl, 2, 22
#define hw__gpa_mode5			_cb1, crl, 2, 20
#define hw__gpa_cnf4			_cb1, crl, 2, 18
#define hw__gpa_mode4			_cb1, crl, 2, 16
#define hw__gpa_cnf3			_cb1, crl, 2, 14
#define hw__gpa_mode3			_cb1, crl, 2, 12
#define hw__gpa_cnf2			_cb1, crl, 2, 10
#define hw__gpa_mode2			_cb1, crl, 2,  8
#define hw__gpa_cnf1			_cb1, crl, 2,  6
#define hw__gpa_mode1			_cb1, crl, 2,  4
#define hw__gpa_cnf0			_cb1, crl, 2,  2
#define hw__gpa_mode0			_cb1, crl, 2,  0


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
} hwa_gpa_t ;

#endif
