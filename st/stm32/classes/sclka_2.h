
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Class _sclka
 */

/**
 * @page stm32_sclka Class _sclka: SYSCLK
 *
 * `connect`:
 * @code
 * hw | hwa ( connect, sysclk,   hsi
 *                             | pll
 *                             | hse );
 * @endcode
 * <br>
 */
#define _hw_class__sclka
#define _hw_def_sysclk			_sclka, 0, 0

#define _hw_mtd_hw_connect__sclka	, _hw_cnsysclka
#define _hw_mtd_hwa_connect__sclka	, _hwa_cnsysclka

#define _hw_cnsysclka_hsi		, 0
#define _hw_cnsysclka_hse		, 1
#define _hw_cnsysclka_pll		, 2

#define _hw_cnsysclka(o,i,a,v,g,...)	HW_Y(_hwx_cnsysclka1,g)(_hw,v,g)
#define _hwa_cnsysclka(o,i,a,v,g,...)	HW_Y(_hwx_cnsysclka1,g)(_hwa,v,g)

#define _hwx_cnsysclka1_0(h,v,g)	HW_E_G(g)
#define _hwx_cnsysclka1_1(h,v,g)	HW_Y(_hwx_cnsysclka2,_hw_cnsysclka_##v)(h,v)
#define _hwx_cnsysclka2_0(h,v)		HW_E_VL(v,hsi | hse | pll)
#define _hwx_cnsysclka2_1(h,v)		h##_write_reg(rcc,sw,HW_A1(_hw_cnsysclka_##v))
