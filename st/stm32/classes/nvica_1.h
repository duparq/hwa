
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _nvica
 */

/**
 * @page stm32_nvica Class _nvica: Nested Vectored Interrupt Controller (NVIC)
 */
#define hw_class__nvica

#define hw_reg__nvica_iser0		_r32, 0x0000, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_iser1		_r32, 0x0004, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_iser2		_r32, 0x0008, 0x0000FFFF, 0x0000FFFF

#define hw_reg__nvica_icer0		_r32, 0x0080, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_icer1		_r32, 0x0084, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_icer2		_r32, 0x0088, 0x0000FFFF, 0x0000FFFF

#define hw_reg__nvica_ispr0		_r32, 0x0100, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_ispr1		_r32, 0x0104, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_ispr2		_r32, 0x0108, 0x0000FFFF, 0x0000FFFF

#define hw_reg__nvica_icpr0		_r32, 0x0180, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_icpr1		_r32, 0x0184, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_reg__nvica_icpr2		_r32, 0x0188, 0x0000FFFF, 0x0000FFFF

/*  Relatives. Make HW_X() translate "(nvic,oject)" to "object_nvic".
 *    E.g. (nvic,counter2) -> counter2_nvic
 */
#define _hw_rel__nvica(o,d,r)		r##_##o


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t iser0, iser1, iser2 ;
  hwa_r32_t icer0, icer1, icer2 ;
  hwa_r32_t ispr0, ispr1, ispr2 ;
  hwa_r32_t icpr0, icpr1, icpr2 ;
  hwa_r32_t iabr0, iabr1, iabr2 ;
  hwa_r32_t ipr0, ipr1, ipr2, ipr3, ipr4, ipr5, ipr6, ipr7, ipr8, ipr9 ;
  hwa_r32_t ipr10, ipr11, ipr12, ipr13, ipr14, ipr15, ipr16, ipr17, ipr18, ipr19 ;
  hwa_r32_t ipr20 ;
  hwa_r32_t stir ;
} hwa_nvica_t ;

#endif
