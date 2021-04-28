
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief APB
 */

#define _hw_actions__apba	, (clock)
#define _hwa_actions__apba	, (clock)

/**
 * @ingroup stm32_classes
 * @defgroup stm32_apba Class _apba: Advanced Peripheral Bus (APB)
 *
 * @section stm32_apbaif Interface
 *
 * * Clock
 *
 * APB buses are clocked from the AHB through a prescaler.
 *
 * @code
 * hw|hwa( clock, APB, sysclk [ /   2
 *				  | 4
 *				  | 8
 *				  | 16 ] );
 * @endcode
 */
#define hw_clock__apba		, _hw_ckapba
#define _hw_ckapba(o,a,v,...)	do{ HW_BV(_hwx_ckapba,ckapba_,v,_hw,o,v,__VA_ARGS__) }while(0)

#define hwa_clock__apba		, _hwa_ckapba
#define _hwa_ckapba(o,a,v,...)	do{ HW_BV(_hwx_ckapba,ckapba_,v,_hwa,o,v,__VA_ARGS__) }while(0)

#define _hw_ckapba_ahb	, 1

#define _hwx_ckapba0(v,...)	HW_E(HW_EM_XNIL(v,(ahb)))
#define _hwx_ckapba1(r,h,o,v,...)					\
  if      (    r == 1 ) h##_write(rcc,o,0);				\
  else if (  2*r == 1 ) h##_write(rcc,o,4);				\
  else if (  4*r == 1 ) h##_write(rcc,o,5);				\
  else if (  8*r == 1 ) h##_write(rcc,o,6);				\
  else if ( 16*r == 1 ) h##_write(rcc,o,7);				\
  else HWA_E(HW_EM_VAL(v,clock,(ahb, ahb/2, ahb/4, ahb/8, ahb/16)));	\
  HW_EOL(__VA_ARGS__)
