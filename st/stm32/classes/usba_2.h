
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief USB
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_usba Class _usba: USB
 *
 * <br><br>hw( write, usbprescaler, value) and hwa( write, usbprescaler, value) set the prescaler:
 *
 * @code
 * hw | hwa( write, usbprescaler,   1
 *				  | 1.5
 * );
 * @endcode
 *
 * @note You should configure the USB prescaler so that it provides a 48 MHz clock
 * signal from the PLLCLK.
 */
#define hw_write_usbprescaler		, _hw_wrusbpsc
#define hwa_write_usbprescaler		, _hwa_wrusbpsc

#define _hw_wrusbpsc(i,a,v,g,...)	HW_B(_hwx_wrusbpsc1_,g)(_hw,v,g)
#define _hwa_wrusbpsc(i,a,v,g,...)	HW_B(_hwx_wrusbpsc1_,g)(_hwa,v,g)

/*  Can not check that 'v' is not void since the preprocessor does not accept to
 *  concatenate '1.5'. Let's do it another way.
 */
#define _hwx_wrusbpsc1_0(h,v,g)		HW_E(HW_EM_G(g))
#define _hwx_wrusbpsc1_1(h,v,g)				\
  do{							\
    if	    (v-1+1==  1) h##_write(rcc,usbpre,1);	\
    else if (v-1+1==1.5) h##_write(rcc,usbpre,0);	\
    else HWA_E(HW_EM_VL(v,(1, 1.5)));			\
  }while(0)
