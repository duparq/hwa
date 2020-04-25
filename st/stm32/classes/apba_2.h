
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
#define hw_class__apba

#define hw_configure__apba	, _hw_cfapba
#define hwa_configure__apba	, _hwa_cfapba

#define _hw_cfapba(o,a,k,...)		do{ HW_Y(_hwx_cfapba_k_,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfapba(o,a,k,...)	do{ HW_Y(_hwx_cfapba_k_,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfapba_k_1(h,o,k,...)	HW_E_ML((clock, prescaler))
#define _hwx_cfapba_k_0(h,o,k,...)	HW_Y(_hwx_cfapba_ksrc_,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfapba_ksrc_1(h,o,k,v,...)	HW_Y(_hwx_cfapba_vsrc_,_hw_is_ahb_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfapba_vsrc_0(h,o,v,...)	HW_E_OKMV(clock,v,ahb)
#define _hwx_cfapba_vsrc_1(h,o,v,k,...)	HW_Y(_hwx_cfapba_kpsc_,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)
#define _hwx_cfapba_ksrc_0(h,o,k,...)	HW_Y(_hwx_cfapba_kpsc_,_hw_is_prescaler_##k)(h,o,k,__VA_ARGS__)

/*  Mandatory parameter `prescaler`
 */
#define _hwx_cfapba_kpsc_0(h,o,k,...)	HW_E_K(prescaler,k)
#define _hwx_cfapba_kpsc_1(h,o,k,v,g,...)	_hwx_cfapba_vpsc1_1(h,o,v,g) HW_EOL(g)
#define _hwx_cfapba_vpsc1_1(h,o,v,g)		HW_Y(_hwx_cfapba_vpsc2_,v)(h,o,v)
#define _hwx_cfapba_vpsc2_1(h,o,v)		HW_E_V()
#define _hwx_cfapba_vpsc2_0(h,o,v)				\
    if      ( v ==  1 ) h##_write(rcc,o,0);	\
    else if ( v ==  2 ) h##_write(rcc,o,4);	\
    else if ( v ==  4 ) h##_write(rcc,o,5);	\
    else if ( v ==  8 ) h##_write(rcc,o,6);	\
    else if ( v == 16 ) h##_write(rcc,o,7);	\
    else HWA_E_NIL(v,(1, 2, 4, 8, 16));
