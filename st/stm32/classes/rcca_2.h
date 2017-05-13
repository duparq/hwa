
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

/**
 * @page stm32_rcca
 * @section stm32_rcca_sys SYSCLK signal
 * @subsection stm32_rcca_cnsys Connecting the SYSCLK signal
 * @code
 * hw | hwa ( connect, sysclk,   hsi
 *                             | pll
 *                             | hse );
 * @endcode
 */
#define _hw_mtd_hw_connect_sysclk	, _hw_cnsysclk
#define _hw_mtd_hwa_connect_sysclk	, _hwa_cnsysclk

#define _hw_sysclk_hsi			, 0
#define _hw_sysclk_hse			, 1
#define _hw_sysclk_pll			, 2

#define _hw_cnsysclk(i,a,v,g,...)	HW_X(_hwx_cnsysclk)(_hw,v,g)
#define _hwa_cnsysclk(i,a,v,g,...)	HW_X(_hwx_cnsysclk)(_hwa,v,g)

#define _hwx_cnsysclk_0(x,v,g)		HW_E_G(g)
#define _hwx_cnsysclk_1(x,v,g)		HW_X(_hwx_cnsysclk1,_hw_sysclk_##v)(x,v)
#define _hwx_cnsysclk1_0(x,v)		HW_E_VL(v,hsi | hse | pll)
#define _hwx_cnsysclk1_1(x,v)		x##_write_reg(rcc,sw,HW_A1(_hw_sysclk_##v))


/**
 * @page stm32_rcca
 * @section stm32_rcca_hse HSE oscillator
 * @subsection stm32_rcca_pwhse Turning the HSE oscillator on/off
 * @code
 * hw | hwa ( power, hse,   on
 *                        | off );
 * @endcode
 */
#define _hw_class__hsea


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_sthse Getting the HSE oscillator status
 * @code
 * while ( ! hw(stat,hse).ready ) {}	// Wait for the HSE clock to be stable
 * @endcode
 */
typedef struct {
    unsigned int _0_16  : 17 ;
    unsigned int ready  :  1 ;
    unsigned int _18_31 : 14 ;
} _hw_sthse_t ;

#define _hw_mtd_hw_stat_t_hse		, _hw_stthse
#define _hw_stthse(o,i,a,...)		HW_TX( _hw_sthse_t, __VA_ARGS__)

#define _hw_mtd_hw_stat_hse		, _hw_sthse
#define _hw_sthse(i,a,g,...)		HW_X(_hw_sthse1,g)(g)
#define _hw_sthse1_0(g)			HW_E_G(g)
#define _hw_sthse1_1(g)			(*(volatile _hw_sthse_t*)_HW_A(_HW_R(rcc,cr)))


/**
 * @page stm32_rcca
 * @section stm32_rcca_pll PLL
 * @subsection stm32_rcca_cnpll Connecting the PLL source
 * @code
 * hw | hwa ( connect, pll,   hsi
 *                          | hse
 *                          | hse_div_2 );
 * @endcode
 */
#define _hw_mtd_hw_connect_pll		, _hw_cnpll
#define _hw_mtd_hwa_connect_pll		, _hwa_cnpll

#define _hw_pll_hsi
#define _hw_pll_hse
#define _hw_pll_hse_div_2
//#define _hw_pll_hse_div(x)		_hw_pll_hse_div_##x

#define _hw_cnpll(i,a,v,g,...)		HW_X(_hwx_cnpll)(_hw,v,g)
#define _hwa_cnpll(i,a,v,g,...)		HW_X(_hwx_cnpll)(_hwa,v,g)

#define _hwx_cnpll_0(x,v,g)		HW_E_G(g)
#define _hwx_cnpll_1(x,v,g)		HW_X(_hwx_cnpll1,_hw_pll_##v)(x,v)
#define _hwx_cnpll1_0(x,v)		HW_E_VL(v,hsi | hse | hse_div_2)
#define _hwx_cnpll1_1(x,v)		_hwx_cnpll2_##v(x)
#define _hwx_cnpll2_hsi(x)		x##_write_reg(rcc,pllsrc,0)		/*             pllsrc=0 */
#define _hwx_cnpll2_hse(x)		x##_write_reg(rcc,pllxtpresrc,1)	/* pllxtpre=0, pllsrc=1 */
#define _hwx_cnpll2_hse_div_2(x)	x##_write_reg(rcc,pllxtpresrc,3)	/* pllxtpre=1, pllsrc=1 */


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_wrpll Setting the PLL multiplier
 * @code
 * hw | hwa ( write, pll,   2		// Any value in the range [ 2..16 ]
 *                        | 3
 *                        | ...
 *                        | 16 );
 * @endcode
 */
#define _hw_mtd_hw_write_pll		, _hw_wrpll
#define _hw_mtd_hwa_write_pll		, _hwa_wrpll

#define _hw_wrpll(i,a,v,g,...)		HW_X(_hwx_wrpll)(_hw,v,g)
#define _hwa_wrpll(i,a,v,g,...)		HW_X(_hwx_wrpll)(_hwa,v,g)

#define _hwx_wrpll_0(x,v,g)		HW_E_G(g)
#define _hwx_wrpll_1(x,v,g)		\
  do{ if (v<2 || v>16) HWA_ERR("HWA: value must be in the range 2..16."); else x##_write_reg(rcc,pllmul,((uint8_t)v-2)); }while(0)

#define _hw_mtd_hw_turn_pll		, _hw_tnpll
#define _hw_mtd_hwa_turn_pll		, _hwa_tnpll


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_tnpll Turning the PLL on/off
 * @code
 * hw | hwa ( turn, pll,   on
 *                       | off );
 * @endcode
 */
#define _hw_tnpll(i,a,v,g,...)		HW_X(_hwx_tnpll)(_hw,v,g)
#define _hwa_tnpll(i,a,v,g,...)		HW_X(_hwx_tnpll)(_hwa,v,g)

#define _hwx_tnpll_0(x,v,g)		HW_E_G(g)
#define _hwx_tnpll_1(x,v,g)		HW_X(_hwx_tnpll2,_hw_state_##v)(x,v)
#define _hwx_tnpll2_0(x,v)		HW_E_ST(v)
#define _hwx_tnpll2_1(x,v)		x##_write_reg(rcc,pllon,HW_A1(_hw_state_##v))


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_stpll Getting the PLL status
 * @code
 * while ( ! hw(stat,pll).ready ) {}	// Wait for the PLL to be locked
 * @endcode
 */
typedef struct {
  unsigned int _0_24  : 25 ;
  unsigned int ready  :  1 ;
  unsigned int _26_31 :  6 ;
} _hw_stpll_t ;

#define _hw_mtd_hw_stat_t_pll		, _hw_sttpll
#define _hw_sttpll(o,i,a,...)		HW_TX( _hw_stpll_t, __VA_ARGS__)

#define _hw_mtd_hw_stat_pll		, _hw_stpll
#define _hw_stpll(i,a,g,...)		HW_X(_hw_stpll1,g)(g)
#define _hw_stpll1_0(g)			HW_E_G(g)
#define _hw_stpll1_1(g)			(*(volatile _hw_stpll_t*)_HW_A(_HW_R(rcc,cr)))



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__rcca(o,i,a)			\
  _hwa_setup_reg( o, cr      );			\
  _hwa_setup_reg( o, cfgr    );			\
  _hwa_setup_reg( o, apb2enr )

#define _hwa_init__rcca(o,i,a)			\
  _hwa_init_reg( o, cr,      0x00000083 );	\
  _hwa_init_reg( o, cfgr,    0x00000000 );	\
  _hwa_init_reg( o, apb2enr, 0x00000000 )

#define _hwa_commit__rcca(o,i,a)		\
  _hwa_commit_reg( o, cr      );		\
  _hwa_commit_reg( o, cfgr    );		\
  _hwa_commit_reg( o, apb2enr )


/**
 * @page stm32_rcca
 * <br>
 */
