
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief APB
 */

/**
 * @page stm32_apba Class _apba: Advanced Peripheral Bus (APB)
 *
 * `configure`:
 * @code
 * hw | hwa ( configure,   apb1,
 *
 *          [ clock,       ahb, ]
 *
 *            prescaler,   1
 *                       | 2
 *                       | 4
 *                       | 8
 *                       | 16 );
 * @endcode
 * <br>
 */
#define _hw_class__apba

#define _hw_mtd_hw_configure__apba	, _hw_cfapba
#define _hw_mtd_hwa_configure__apba	, _hwa_cfapba

#define _hw_is_clock_clock		, 1
#define _hw_is_prescaler_prescaler	, 1
#define _hw_is_ahb_ahb		, 1

#define _hw_cfapba(o,i,a,k,...)		do{ HW_X(_hwx_cfapba_k,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfapba(o,i,a,k,...)	do{ HW_X(_hwx_cfapba_k,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfapba_k_1(h,o,k,...)	HW_E_ML((clock, prescaler))
#define _hwx_cfapba_k_0(h,o,k,...)	HW_X(_hwx_cfapba_ksrc,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfapba_ksrc_1(h,o,k,v,...)	HW_X(_hwx_cfapba_vsrc,_hw_is_ahb_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfapba_vsrc_0(h,o,v,...)	HW_E_OKMV(clock,v,ahb)
#define _hwx_cfapba_vsrc_1(h,o,v,k,...)	HW_X(_hwx_cfapba_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfapba_ksrc_0(h,o,k,...)	HW_X(_hwx_cfapba_kpsc,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)

/*  Mandatory parameter `prescaler`
 */
#define _hwx_cfapba_kpsc_0(h,o,k,...)	HW_E_K(prescaler,k)
#define _hwx_cfapba_kpsc_1(h,o,k,v,g,...)	_hwx_cfapba_vpsc1_1(h,o,v,g) HW_EOL(g)
#define _hwx_cfapba_vpsc1_1(h,o,v,g)		HW_X(_hwx_cfapba_vpsc2,v)(h,o,v)
#define _hwx_cfapba_vpsc2_1(h,o,v)		HW_E_V()
#define _hwx_cfapba_vpsc2_0(h,o,v)				\
    if      ( v ==  1 ) h##_write_reg(rcc,o,0);	\
    else if ( v ==  2 ) h##_write_reg(rcc,o,4);	\
    else if ( v ==  4 ) h##_write_reg(rcc,o,5);	\
    else if ( v ==  8 ) h##_write_reg(rcc,o,6);	\
    else if ( v == 16 ) h##_write_reg(rcc,o,7);	\
    else HWA_E_NIL(v,(1, 2, 4, 8, 16));
