
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 12-bit ADC
 */

/**
 * @page stm32_a12a
 * @section stm32_a12a 12-bit ADC
 *
 * The ADC prescaler divides the APB2 clock to provide the ADCs clock.
 * The ADC clock must not exceed 14 MHz.
 *
 * @code
 * hw | hwa ( write, adcprescaler,    2
 *                                  | 4
 *                                  | 6
 *                                  | 8 );
 * @endcode
 */
#define hw_write_adcprescaler	, _hw_wradcpsc
#define hwa_write_adcprescaler	, _hwa_wradcpsc

#define _hw_wradcpsc(i,a,v,g,...)	HW_Y(_hwx_wradcpsc1_,g)(_hw,v,g)
#define _hwa_wradcpsc(i,a,v,g,...)	HW_Y(_hwx_wradcpsc1_,g)(_hwa,v,g)

#define _hwx_wradcpsc1_0(h,v,g)		HW_E_G(g)
#define _hwx_wradcpsc1_1(h,v,g)		HW_Y(_hwx_wradcpsc2_,v)(h,v)
#define _hwx_wradcpsc2_1(h,v)		HW_E_V()
#define _hwx_wradcpsc2_0(h,v)				\
  do{							\
    if ( v-1!=1 && v-1!=3 && v-1!=5 && v-1!=7 )		\
      HWA_E_VL(v,2|4|6|8);				\
    h##_write(rcc,adcpre,(v-2)/3);			\
  }while(0)
