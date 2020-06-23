
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief AHB
 */

/**
 * @page stm32_ahba Class _ahba: AMBA High-performance Bus (AHB)
 *
 * The AHB prescaler divides the SYSCLK to provide the clock of the AHB bus, the
 * core, the memory, and the DMA.
 *
 * `configure`:
 * @code
 * hw | hwa ( configure,   ahb,
 *
 *	    [ clock,	   sysclk, ]
 *
 *	      prescaler,   1
 *			 | 2
 *			 | 4
 *			 | 8
 *			 | 16
 *			 | 64
 *			 | 128
 *			 | 256
 *			 | 512 );
 * @endcode
 * <br>
 */
#define hw_class__ahba
#define hw_ahb				_ahba, 0
#define hw_ahbprescaler			_ahba, 0

#define hw_configure__ahba		, _hw_cfahba
#define hwa_configure__ahba		, _hwa_cfahba

#define _hw_cfahba(o,a,k,...)		do{ HW_B(_hwx_cfahba_k_,k)(_hw,k,__VA_ARGS__) }while(0)
#define _hwa_cfahba(o,a,k,...)	do{ HW_B(_hwx_cfahba_k_,k)(_hwa,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfahba_k_1(h,k,...)	HW_E_ML((clock, prescaler))
#define _hwx_cfahba_k_0(h,k,...)	HW_B(_hwx_cfahba_ksrc_,_hw_is_clock_##k)(h,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfahba_ksrc_1(h,k,v,...)	HW_B(_hwx_cfahba_vsrc_,_hw_is_sysclk_##v)(h,v,__VA_ARGS__)
#define _hwx_cfahba_vsrc_0(h,v,...)	HW_E_OKVL(clock,v,sysclk)
#define _hwx_cfahba_vsrc_1(h,v,k,...)	HW_B(_hwx_cfahba_kpsc_,_hw_is_prescaler_##k)(h,k,__VA_ARGS__)
#define _hwx_cfahba_ksrc_0(h,k,...)	HW_B(_hwx_cfahba_kpsc_,_hw_is_prescaler_##k)(h,k,__VA_ARGS__)

/*  Mandatory parameter `prescaler`
 */
#define _hwx_cfahba_kpsc_0(h,k,...)	HW_E_K(prescaler,k)
#define _hwx_cfahba_kpsc_1(h,k,v,g,...)	_hwx_cfahba_vpsc(h,v) HW_EOL(g)
#define _hwx_cfahba_vpsc(h,v)					\
  if	  ( (v+0) ==   1 ) h##_write(rcc,hpre, 0);		\
  else if ( (v+0) ==   2 ) h##_write(rcc,hpre, 8);		\
  else if ( (v+0) ==   4 ) h##_write(rcc,hpre, 9);		\
  else if ( (v+0) ==   8 ) h##_write(rcc,hpre,10);		\
  else if ( (v+0) ==  16 ) h##_write(rcc,hpre,11);		\
  else if ( (v+0) ==  64 ) h##_write(rcc,hpre,12);		\
  else if ( (v+0) == 128 ) h##_write(rcc,hpre,13);		\
  else if ( (v+0) == 256 ) h##_write(rcc,hpre,14);		\
  else if ( (v+0) == 512 ) h##_write(rcc,hpre,15);		\
  else HWA_E_NIL(v,(1, 2, 4, 8, 16, 64, 128, 256, 512));
