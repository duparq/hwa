
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief GPIO port
 */

#define hw_class__gpb

/**
 * @ingroup stm32_classes
 * @defgroup stm32_gpb Class _gpb: 16-bit GPIO port
 *
 * @section stm32_gpbrel Relatives
 *
 *  * @ref hwa_reg "Registers"
 *    * `afrl`, `afrh`, `bsrr`, `idr`, `lckr`, `mode`, `odr`, `ospeed`, `otype`, `pupd`
 *
 *  * Access to GPIO @ref stm32_ioa "pins":
 *    * `(PORT,p)`, `(PORT,1,p)`: single pin at position `p`
 *    * `(PORT,n,p)`: `n` consecutive pins at position `p`
 */
#define hw__gpb_			, _hw_gpb_
#define _hw_gpb_(o,n,a)			HW_BX(_hw_gpb_,_hw_isa_4bn_,n)(o,n)
#define _hw_gpb_1(o,n)			_iob,o##_1_##n,(o,1,n)
#define _hw_gpb_0(o,n)			,(o,n),HW_EM(o has no relative n)


/*	Class registers			class, address, rwm, rfm
 */
#define hw__gpb_mode			_r32, 0x00, 0xffffffff, 0
#define hw__gpb_otype			_r32, 0x04, 0xffffffff, 0
#define hw__gpb_ospeed			_r32, 0x08, 0xffffffff, 0
#define hw__gpb_pupd			_r32, 0x0C, 0xffffffff, 0
#define hw__gpb_idr			_r32, 0x10, 0x00000000, 0
#define hw__gpb_odr			_r32, 0x14, 0x0000ffff, 0
#define hw__gpb_bsrr			_r32, 0x18, 0xffffffff, 0xffffffff
#define hw__gpb_lckr			_r32, 0x1C, 0x0001ffff, 0
#define hw__gpb_afrl			_r32, 0x20, 0xffffffff, 0
#define hw__gpb_afrh			_r32, 0x24, 0xffffffff, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t mode   ;
  hwa_r32_t otype  ;
  hwa_r32_t ospeed ;
  hwa_r32_t pupd   ;
  hwa_r32_t odr    ;
  hwa_r32_t bsrr   ;
  hwa_r32_t lckr   ;
  hwa_r32_t afrl   ;
  hwa_r32_t afrh   ;

  uint32_t	toggles ;
} hwa_gpb_t ;

#endif
