
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _nvica
 */

/* Logical registers are implemented as object registers since there is only one
 * NVIC in the device and HW_X() will find them faster this way.
 */
#define hw_class__nvica

#define hw_nvic_iser0			_r32, 0x0000, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_iser1			_r32, 0x0004, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_iser2			_r32, 0x0008, 0x0000FFFF, 0x0000FFFF

#define hw_nvic_icer0			_r32, 0x0080, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_icer1			_r32, 0x0084, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_icer2			_r32, 0x0088, 0x0000FFFF, 0x0000FFFF

#define hw_nvic_ispr0			_r32, 0x0100, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_ispr1			_r32, 0x0104, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_ispr2			_r32, 0x0108, 0x0000FFFF, 0x0000FFFF

#define hw_nvic_icpr0			_r32, 0x0180, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_icpr1			_r32, 0x0184, 0xFFFFFFFF, 0xFFFFFFFF
#define hw_nvic_icpr2			_r32, 0x0188, 0x0000FFFF, 0x0000FFFF


/*  NVIC relatives: _nvi object that holds an IRQ number
 */
#define hw_class__nvi

#define hw__nvica_			, _hw_nvicarl
#define _hw_nvicarl(o1,o2,...)		_hw_nvicarl1(o1,o2,hw_##o2##_irq,)
#define _hw_nvicarl1(...)		_hw_nvicarl2(__VA_ARGS__)
#define _hw_nvicarl2(o1,o2,x,...)	HW_BW(_hw_nvicarl2,_irq,x)(o1,o2,x,__VA_ARGS__) // PUSH
#define _hw_nvicarl21(o1,o2,c,a,...)	_nvi, a
#define _hw_nvicarl20(o1,o2,...)	,o1,HW_EM_OO(o1,o2)


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
