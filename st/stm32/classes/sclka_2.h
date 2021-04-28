
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _sclka
 */
#define hw_class__sclka

#define hw_sysclk			_sclka, 0

/**
 * @ingroup stm32_classes
 * @defgroup stm32_sclka Class _sclka: SYSCLK
 *
 * @section stm32_sclkaif Interface
 *
 * * Source
 *
 * @code
 * hw|hwa( connect, sysclk,   hsi
 *			    | pll
 *			    | hse );
 * @endcode
 */
#define hw_connect__sclka		, _hw_cnsysclka
#define _hw_cnsysclka(o,a,v,...)	HW_BV(_hwx_cnsysclka,cnsysclka_,v,_hw,o,__VA_ARGS__)

#define hwa_connect__sclka		, _hwa_cnsysclka
#define _hwa_cnsysclka(o,a,v,...)	HW_BV(_hwx_cnsysclka,cnsysclka_,v,_hwa,o,__VA_ARGS__)

#define _hw_cnsysclka_hsi		, 0
#define _hw_cnsysclka_hse		, 1
#define _hw_cnsysclka_pll		, 2

#define _hwx_cnsysclka_(v,...)		HW_E(HW_EM_VL(v,(hsi,hse,pll)))
#define _hwx_cnsysclka0(v,...)		HW_E(HW_EM_VL(v,(hsi,hse,pll)))
#define _hwx_cnsysclka1(r,h,o,...)	h##_write(rcc,sw,r)
