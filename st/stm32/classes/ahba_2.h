
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief AHB
 */

#define _hw_actions__ahba	, (clock)
#define _hwa_actions__ahba	, (clock)

/**
 * @ingroup stm32_classes
 * @defgroup stm32_ahba Class _ahba: AMBA High-performance Bus (AHB)
 *
 * @section stm32_ahbaif Interface
 *
 * * Clocking
 *
 * The AHB is clocked from the SYSCLK through a prescaler.
 *
 * @code
 * hw|hwa( clock, ahb, sysclk [ /   2
 *				  | 4
 *				  | ...
 *				  | 512 ] );
 * @endcode
 */
#define hw_clock__ahba		, _hw_ckahba
#define _hw_ckahba(o,a,v,...)	do{ HW_BV(_hwx_ckahba,ckahba_,v,_hw,v,__VA_ARGS__) }while(0)

#define hwa_clock__ahba		, _hwa_ckahba
#define _hwa_ckahba(o,a,v,...)	do{ HW_BV(_hwx_ckahba,ckahba_,v,_hwa,v,__VA_ARGS__) }while(0)

#define _hw_ckahba_sysclk	, 1

#define _hwx_ckahba0(v,...)	HW_E(HW_EM_XNIL(v,(sysclk)))
#define _hwx_ckahba1(r,h,v,...)						\
  if	  ( r     == 1 ) h##_write(rcc,hpre, 0);			\
  else if ( 2*r   == 1 ) h##_write(rcc,hpre, 8);			\
  else if ( 4*r   == 1 ) h##_write(rcc,hpre, 9);			\
  else if ( 8*r   == 1 ) h##_write(rcc,hpre,10);			\
  else if ( 16*r  == 1 ) h##_write(rcc,hpre,11);			\
  else if ( 64*r  == 1 ) h##_write(rcc,hpre,12);			\
  else if ( 128*r == 1 ) h##_write(rcc,hpre,13);			\
  else if ( 256*r == 1 ) h##_write(rcc,hpre,14);			\
  else if ( 512*r == 1 ) h##_write(rcc,hpre,15);			\
  else HWA_E(HW_EM_VAL(v,clock,(1, 2, 4, 8, 16, 64, 128, 256, 512)));	\
  HW_EOL(__VA_ARGS__)
