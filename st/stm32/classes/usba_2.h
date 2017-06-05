
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief USB
 */

/**
 * @page stm32_usba
 * @section stm32_usba USB
 *
 * You should configure the USB prescaler so that it provides a 48 MHz clock
 * signal from the PLLCLK.
 *
 * @code
 * hw | hwa ( write, usbprescaler,   1
 *                                 | 1.5 );
 * @endcode
 */
#define _hw_mtd_hw_write_usbprescaler	, _hw_wrusbpsc
#define _hw_mtd_hwa_write_usbprescaler	, _hwa_wrusbpsc

#define _hw_wrusbpsc(i,a,v,g,...)	HW_X(_hwx_wrusbpsc1,g)(_hw,v,g)
#define _hwa_wrusbpsc(i,a,v,g,...)	HW_X(_hwx_wrusbpsc1,g)(_hwa,v,g)

/*  Can not check that 'v' is not void since the preprocessor does not accept to
 *  concatenate '1.5'. Let's do it another way.
 */
#define _hwx_wrusbpsc1_0(h,v,g)		HW_E_G(g)
#define _hwx_wrusbpsc1_1(h,v,g)				\
  do{							\
    if      (v-1+1==  1) h##_write_reg(rcc,usbpre,1);	\
    else if (v-1+1==1.5) h##_write_reg(rcc,usbpre,0);	\
    else HWA_E_VL(v,1 | 1.5);				\
  }while(0)
