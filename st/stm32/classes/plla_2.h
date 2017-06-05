
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief PLL
 */

/**
 * @page stm32_plla Class _plla: PLL
 *
 * `configure`:
 * @code
 * hw | hwa ( configure,    pll,
 *
 *          [ source,       hsi/2
 *                        | hse
 *                        | hse/2, ]
 *
 *          [ multiplier,   2		// Any value in the range [ 2..16 ]
 *                        | 3
 *                        | ...
 *                        | 16 ] );
 * @endcode
 *
 * @note The PLL can not be configured while it is running.
 */
#define _hw_class__plla
#define _hw_def_pll			_plla, 0, 0

#define _hw_mtd_hw_configure__plla	, _hw_cfplla
#define _hw_mtd_hwa_configure__plla	, _hwa_cfplla

#define _hw_is_source_source		, 1
#define _hw_is_multiplier_multiplier	, 1

#define _hw_cfplla(o,i,a,k,...)		do{ HW_X(_hwx_cfplla_k,k)(_hw,k,__VA_ARGS__) }while(0)
#define _hwa_cfplla(o,i,a,k,...)	do{ HW_X(_hwx_cfplla_k,k)(_hwa,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfplla_k_1(h,k,...)	HW_E_ML((source, multiplier))
#define _hwx_cfplla_k_0(h,k,...)	HW_X(_hwx_cfplla_ksrc,_hw_is_source_##k)(h,k,__VA_ARGS__)

/*  Optionnal parameter `source`
 */
#define _hwx_cfplla_ksrc_1(h,k,v,...)	HW_X(_hwx_cfplla_vsrc,_hw_cnplla_##v)(h,v,__VA_ARGS__)
#define _hwx_cfplla_vsrc_0(h,v,...)	HW_E_NIL(v,(hsi/2, hse, hse/2))
#define _hwx_cfplla_vsrc_1(h,v,k,...)	_hwx_cnplla2_1(h,v,_hw_cnplla_##v) _hwx_cfplla_ksrc_0(h,k,__VA_ARGS__)

#define _hwx_cfplla_ksrc_0(h,k,...)	HW_X(_hwx_cfplla_kmul,_hw_is_multiplier_##k)(h,k,__VA_ARGS__)

/*  Optionnal parameter `multiplier`
 */
#define _hwx_cfplla_kmul_0(h,k,...)	HW_EOL(k)
#define _hwx_cfplla_kmul_1(h,k,v,g,...)	_hwx_wrplla_1(h,v,g) HW_EOL(g)


/**
 * @page stm32_plla
 *
 * Alternatively, the `connect` and `write` actions can be used.
 *
 * `connect`:
 * @code
 * hw | hwa ( connect, pll,   hsi / 2
 *                          | hse
 *                          | hse / 2 );
 * @endcode
 */
#define _hw_mtd_hw_connect__plla	, _hw_cnplla
#define _hw_mtd_hwa_connect__plla	, _hwa_cnplla

#define _hw_cnplla_hsi			, 17
#define _hw_cnplla_hse			, 19

#define _hw_cnplla(o,i,a,v,g,...)	do{ HW_X(_hwx_cnplla1)(_hw,v,g) }while(0)
#define _hwa_cnplla(o,i,a,v,g,...)	do{ HW_X(_hwx_cnplla1)(_hwa,v,g) }while(0)
#define _hwx_cnplla1_0(h,v,g)		HW_E_G(g)
#define _hwx_cnplla1_1(h,v,g)		HW_X(_hwx_cnplla2,_hw_cnplla_##v)(h,v,_hw_cnplla_##v)
#define _hwx_cnplla2_0(h,v,xv)		HW_E_NIL(v,(hsi/2, hse, hse/2))
#define _hwx_cnplla2_1(...)		_hwx_cnplla3(__VA_ARGS__)
#define _hwx_cnplla3(h,v,z,xv)						\
  if      ( 2*xv == 17 ) h##_write_reg(rcc,pllsrc,0);			\
  else if (   xv == 19 ) h##_write_reg(rcc,pllxtpresrc,1); /* pllxtpre=0, pllsrc=1 */ \
  else if ( 2*xv == 19 ) h##_write_reg(rcc,pllxtpresrc,3); /* pllxtpre=1, pllsrc=1 */ \
  else HWA_E_NIL(v,(hsi/2, hse, hse/2));


/**
 * @page stm32_plla
 *
 * `write`:
 * @code
 * hw | hwa ( write, pll,   2		// Any value in the range [ 2..16 ]
 *                        | 3
 *                        | ...
 *                        | 16 );
 * @endcode
 */
#define _hw_mtd_hw_write__plla		, _hw_wrplla
#define _hw_mtd_hwa_write__plla		, _hwa_wrplla

#define _hw_wrplla(o,i,a,v,g,...)	do{ HW_X(_hwx_wrplla,g)(_hw,v,g) }while(0)
#define _hwa_wrplla(o,i,a,v,g,...)	do{ HW_X(_hwx_wrplla,g)(_hwa,v,g) }while(0)
#define _hwx_wrplla_0(h,v,g)		HW_E_G(g)
#define _hwx_wrplla_1(h,v,g)				\
  if (v-1+1<2 || v-1+1>16)				\
    HWA_ERR("HWA: value must be in the range 2..16.");	\
  else h##_write_reg(rcc,pllmul,((uint8_t)(v)-2));


/**
 * @page stm32_plla
 *
 * `turn`:
 * @code
 * hw | hwa ( turn, pll,   on
 *                       | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__plla		, _hw_tnplla
#define _hw_mtd_hwa_turn__plla		, _hwa_tnplla

#define _hw_tnplla(o,i,a,v,g,...)	HW_X(_hwx_tnplla)(_hw,v,g)
#define _hwa_tnplla(o,i,a,v,g,...)	HW_X(_hwx_tnplla)(_hwa,v,g)

#define _hwx_tnplla_0(h,v,g)		HW_E_G(g)
#define _hwx_tnplla_1(h,v,g)		HW_X(_hwx_tnplla2,_hw_state_##v)(h,v)
#define _hwx_tnplla2_0(h,v)		HW_E_ST(v)
#define _hwx_tnplla2_1(h,v)		h##_write_reg(rcc,pllon,HW_A1(_hw_state_##v))


/**
 * @page stm32_plla
 *
 * `stat`:
 * @code
 * while ( ! hw(stat,pll).ready ) {}	// Wait for the PLL to be locked
 * @endcode
 * <br>
 */
typedef struct {
  unsigned int _0_24  : 25 ;
  unsigned int ready  :  1 ;
  unsigned int _26_31 :  6 ;
} _hw_stplla_t ;

#define _hw_mtd_hw_stat_t__plla		, _hw_sttplla
#define _hw_sttplla(o,i,a,...)		HW_TX( _hw_stplla_t, __VA_ARGS__)

#define _hw_mtd_hw_stat__plla		, _hw_stplla
#define _hw_stplla(o,i,a,g,...)		HW_X(_hw_stplla1,g)(g)
#define _hw_stplla1_0(g)		HW_E_G(g)
#define _hw_stplla1_1(g)		(*(volatile _hw_stplla_t*)_HW_A(_HW_R(rcc,cr)))
