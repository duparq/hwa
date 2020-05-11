
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

/*	Class registers			class, address, rwm, rfm
 */
#define hw__gpa_crl			_r32, 0x00, 0xffffffff, 0
#define hw__gpa_crh			_r32, 0x04, 0xffffffff, 0
#define hw__gpa_idr			_r32, 0x08, 0x00000000, 0
#define hw__gpa_odr			_r32, 0x0C, 0x0000ffff, 0
#define hw__gpa_bsrr			_r32, 0x10, 0xffffffff, 0xffffffff
#define hw__gpa_brr			_r32, 0x14, 0xffffffff, 0xffffffff
#define hw__gpa_lckr			_r32, 0x18, 0x0001ffff, 0

#define hw__gpa_cnf_15			_cb1, crh, 2, 30
#define hw__gpa_mode_15			_cb1, crh, 2, 28
#define hw__gpa_cnf_14			_cb1, crh, 2, 26
#define hw__gpa_mode_14			_cb1, crh, 2, 24
#define hw__gpa_cnf_13			_cb1, crh, 2, 22
#define hw__gpa_mode_13			_cb1, crh, 2, 20
#define hw__gpa_cnf_12			_cb1, crh, 2, 18
#define hw__gpa_mode_12			_cb1, crh, 2, 16
#define hw__gpa_cnf_11			_cb1, crh, 2, 14
#define hw__gpa_mode_11			_cb1, crh, 2, 12
#define hw__gpa_cnf_10			_cb1, crh, 2, 10
#define hw__gpa_mode_10			_cb1, crh, 2,  8
#define hw__gpa_cnf_9			_cb1, crh, 2,  6
#define hw__gpa_mode_9			_cb1, crh, 2,  4
#define hw__gpa_cnf_8			_cb1, crh, 2,  2
#define hw__gpa_mode_8			_cb1, crh, 2,  0

#define hw__gpa_cnf_7			_cb1, crl, 2, 30
#define hw__gpa_mode_7			_cb1, crl, 2, 28
#define hw__gpa_cnf_6			_cb1, crl, 2, 26
#define hw__gpa_mode_6			_cb1, crl, 2, 24
#define hw__gpa_cnf_5			_cb1, crl, 2, 22
#define hw__gpa_mode_5			_cb1, crl, 2, 20
#define hw__gpa_cnf_4			_cb1, crl, 2, 18
#define hw__gpa_mode_4			_cb1, crl, 2, 16
#define hw__gpa_cnf_3			_cb1, crl, 2, 14
#define hw__gpa_mode_3			_cb1, crl, 2, 12
#define hw__gpa_cnf_2			_cb1, crl, 2, 10
#define hw__gpa_mode_2			_cb1, crl, 2,  8
#define hw__gpa_cnf_1			_cb1, crl, 2,  6
#define hw__gpa_mode_1			_cb1, crl, 2,  4
#define hw__gpa_cnf_0			_cb1, crl, 2,  2
#define hw__gpa_mode_0			_cb1, crl, 2,  0


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
