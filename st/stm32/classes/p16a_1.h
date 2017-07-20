
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
#define _hw_class__p16a

/*	Class registers			class, address, rwm, rfm
 */
#define _hw_reg__p16a_crl		_r32, 0x00, 0xffffffff, 0
#define _hw_reg__p16a_crh		_r32, 0x04, 0xffffffff, 0
#define _hw_reg__p16a_idr		_r32, 0x08, 0x00000000, 0
#define _hw_reg__p16a_odr		_r32, 0x0C, 0x0000ffff, 0
#define _hw_reg__p16a_bsrr		_r32, 0x10, 0xffffffff, 0xffffffff
#define _hw_reg__p16a_brr		_r32, 0x14, 0xffffffff, 0xffffffff
#define _hw_reg__p16a_lckr		_r32, 0x18, 0x0001ffff, 0


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
