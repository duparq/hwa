
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
 *
 * The `_rcca` class is not used directly. Several objects access the RCC to
 * configure the different clocks in the device.
 *
 * @section stm32_rcca_sys SYSCLK
 * @subsection stm32_rcca_cnsys Source
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

#define _hw_cnsysclk(i,a,v,g,...)	HW_X(_hwx_cnsysclk1,g)(_hw,v,g)
#define _hwa_cnsysclk(i,a,v,g,...)	HW_X(_hwx_cnsysclk1,g)(_hwa,v,g)

#define _hwx_cnsysclk1_0(x,v,g)		HW_E_G(g)
#define _hwx_cnsysclk1_1(x,v,g)		HW_X(_hwx_cnsysclk2,_hw_sysclk_##v)(x,v)
#define _hwx_cnsysclk2_0(x,v)		HW_E_VL(v,hsi | hse | pll)
#define _hwx_cnsysclk2_1(x,v)		x##_write_reg(rcc,sw,HW_A1(_hw_sysclk_##v))


/**
 * @page stm32_rcca
 * @section stm32_rcca_hse HSE oscillator
 *
 * You should define the HW_DEVICE_HSEHZ symbol if you use the HSE oscillator.
 *
 * @subsection stm32_rcca_pwhse Turning on/off
 * @code
 * hw | hwa ( power, hse,   on
 *                        | off );
 * @endcode
 */


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_sthse Status
 * @code
 * while ( ! hw(stat,hse).ready ) {}	// Wait for the HSE clock to be stable.
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
 *
 * The PLL must be configured (source, multiplier) before it is turned on.
 *
 * @subsection stm32_rcca_cnpll Source
 * @code
 * hw | hwa ( connect, pll,   hsi / 2
 *                          | hse
 *                          | hse / 2 );
 * @endcode
 */
#define _hw_mtd_hw_connect_pll		, _hw_cnpll
#define _hw_mtd_hwa_connect_pll		, _hwa_cnpll

#define _hw_cnpll_hsi			, 17
#define _hw_cnpll_hse			, 19

#define _hw_cnpll(i,a,v,g,...)		HW_X(_hwx_cnpll1)(_hw,v,g)
#define _hwa_cnpll(i,a,v,g,...)		HW_X(_hwx_cnpll1)(_hwa,v,g)
#define _hwx_cnpll1_0(x,v,g)		HW_E_G(g)
#define _hwx_cnpll1_1(x,v,g)		HW_X(_hwx_cnpll2,_hw_cnpll_##v)(x,v,_hw_cnpll_##v)
#define _hwx_cnpll2_0(x,v,xv)		HW_E_VL(v,hsi/2 | hse | hse/2)
#define _hwx_cnpll2_1(...)		_hwx_cnpll3(__VA_ARGS__)
#define _hwx_cnpll3(x,v,z,xv)						\
  do{									\
    if      ( 2*xv == 17 ) x##_write_reg(rcc,pllsrc,0);			\
    else if (   xv == 19 ) x##_write_reg(rcc,pllxtpresrc,1); /* pllxtpre=0, pllsrc=1 */ \
    else if ( 2*xv == 19 ) x##_write_reg(rcc,pllxtpresrc,3); /* pllxtpre=1, pllsrc=1 */ \
    else HWA_E_VL(v,hsi/2 | hse | hse/2);				\
  }while(0)


/**
 * @page stm32_rcca
 * @subsection stm32_rcca_wrpll Multiplier
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
 * @subsection stm32_rcca_tnpll Turning on/off
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
 * @subsection stm32_rcca_stpll Status
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


/**
 * @page stm32_rcca
 * @section stm32_rcca_usb USB prescaler
 *
 * You should configure the USB prescaler so that it provide a 48 MHz clock
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
 *  concatenate '_hw_is_' and '1.5'. Let's do it another way...
 */
#define _hwx_wrusbpsc1_0(x,v,g)		HW_E_G(g)
#define _hwx_wrusbpsc1_1(x,v,g)				\
  do{							\
    if      (v-1==  1-1) x##_write_reg(rcc,usbpre,1);	\
    else if (v-1==1.5-1) x##_write_reg(rcc,usbpre,0);	\
    else HWA_E_VL(v,1 | 1.5);				\
  }while(0)


/**
 * @page stm32_rcca
 * @section stm32_rcca_ahb AHB prescaler
 *
 * The AHB prescaler divides the SYSCLK to provide the clock of the AHB bus, the
 * core, the memory, and the DMA.
 *
 * @code
 * hw | hwa ( write, ahbprescaler,   1
 *                                 | 2
 *                                 | 4
 *                                 | 8
 *                                 | 16
 *                                 | 64
 *                                 | 128
 *                                 | 256
 *                                 | 512 );
 * @endcode
 */
#define _hw_mtd_hw_write_ahbprescaler	, _hw_wrahbpsc
#define _hw_mtd_hwa_write_ahbprescaler	, _hwa_wrahbpsc

#define _hw_wrahbpsc(i,a,v,g,...)	HW_X(_hwx_wrahbpsc1,g)(_hw,v,g)
#define _hwa_wrahbpsc(i,a,v,g,...)	HW_X(_hwx_wrahbpsc1,g)(_hwa,v,g)

#define _hwx_wrahbpsc1_0(x,v,g)		HW_E_G(g)
#define _hwx_wrahbpsc1_1(x,v,g)		HW_X(_hwx_wrahbpsc2,v)(x,v)
#define _hwx_wrahbpsc2_1(x,v)		HW_E_V()
#define _hwx_wrahbpsc2_0(x,v)				\
  do{							\
    if      ( v ==   1 ) x##_write_reg(rcc,hpre, 0);	\
    else if ( v ==   2 ) x##_write_reg(rcc,hpre, 8);	\
    else if ( v ==   4 ) x##_write_reg(rcc,hpre, 9);	\
    else if ( v ==   8 ) x##_write_reg(rcc,hpre,10);	\
    else if ( v ==  16 ) x##_write_reg(rcc,hpre,11);	\
    else if ( v ==  64 ) x##_write_reg(rcc,hpre,12);	\
    else if ( v == 128 ) x##_write_reg(rcc,hpre,13);	\
    else if ( v == 256 ) x##_write_reg(rcc,hpre,14);	\
    else if ( v == 512 ) x##_write_reg(rcc,hpre,15);	\
    else HWA_E_VL(v,1|2|4|8|16|64|128|256|512);		\
  }while(0)


/**
 * @page stm32_rcca
 * @section stm32_rcca_apb1 APB1 prescaler
 *
 * The APB1 prescaler divides the AHB clock to provide the APB low-speed clock
 * (PCLK1) of the APB1 peripherals and the counters #2..7, and #12..14.
 *
 * @note: The frequency of PCLK1 must not exceed 36 MHz.
 *
 * @code
 * hw | hwa ( write, apb1prescaler,   1
 *                                  | 2
 *                                  | 4
 *                                  | 8
 *                                  | 16 );
 * @endcode
 */
#define _hw_mtd_hw_write_apb1prescaler	, _hw_wrapb1psc
#define _hw_mtd_hwa_write_apb1prescaler	, _hwa_wrapb1psc

#define _hw_wrapb1psc(i,a,v,g,...)	HW_X(_hwx_wrapb1psc1,g)(_hw,v,g)
#define _hwa_wrapb1psc(i,a,v,g,...)	HW_X(_hwx_wrapb1psc1,g)(_hwa,v,g)

#define _hwx_wrapb1psc1_0(x,v,g)	HW_E_G(g)
#define _hwx_wrapb1psc1_1(x,v,g)	HW_X(_hwx_wrapb1psc2,v)(x,v)
#define _hwx_wrapb1psc2_1(x,v)		HW_E_V()
#define _hwx_wrapb1psc2_0(x,v)				\
  do{							\
    if      ( v ==   1 ) x##_write_reg(rcc,ppre1, 0);	\
    else if ( v ==   2 ) x##_write_reg(rcc,ppre1, 4);	\
    else if ( v ==   4 ) x##_write_reg(rcc,ppre1, 5);	\
    else if ( v ==   8 ) x##_write_reg(rcc,ppre1, 6);	\
    else if ( v ==  16 ) x##_write_reg(rcc,ppre1, 7);	\
    else HWA_E_VL(v,1|2|4|8|16);			\
  }while(0)


/**
 * @page stm32_rcca
 * @section stm32_rcca_apb2 APB2 prescaler
 *
 * The APB2 prescaler divides the AHB clock to provide the APB high-peed clock
 * (PCLK2) of the APB2 peripherals and the counters #2..7, and #12..14.
 *
 * @code
 * hw | hwa ( write, apb2prescaler,   1
 *                                  | 2
 *                                  | 4
 *                                  | 8
 *                                  | 16 );
 * @endcode
 */
#define _hw_mtd_hw_write_apb2prescaler	, _hw_wrapb2psc
#define _hw_mtd_hwa_write_apb2prescaler	, _hwa_wrapb2psc

#define _hw_wrapb2psc(i,a,v,g,...)	HW_X(_hwx_wrapb2psc1,g)(_hw,v,g)
#define _hwa_wrapb2psc(i,a,v,g,...)	HW_X(_hwx_wrapb2psc1,g)(_hwa,v,g)

#define _hwx_wrapb2psc1_0(x,v,g)	HW_E_G(g)
#define _hwx_wrapb2psc1_1(x,v,g)	HW_X(_hwx_wrapb2psc2,v)(x,v)
#define _hwx_wrapb2psc2_1(x,v)		HW_E_V()
#define _hwx_wrapb2psc2_0(x,v)				\
  do{							\
    if      ( v ==   1 ) x##_write_reg(rcc,ppre2, 0);	\
    else if ( v ==   2 ) x##_write_reg(rcc,ppre2, 4);	\
    else if ( v ==   4 ) x##_write_reg(rcc,ppre2, 5);	\
    else if ( v ==   8 ) x##_write_reg(rcc,ppre2, 6);	\
    else if ( v ==  16 ) x##_write_reg(rcc,ppre2, 7);	\
    else HWA_E_VL(v,1|2|4|8|16);			\
  }while(0)


/**
 * @page stm32_rcca
 * @section stm32_rcca_adc ADC prescaler
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
#define _hw_mtd_hw_write_adcprescaler	, _hw_wradcpsc
#define _hw_mtd_hwa_write_adcprescaler	, _hwa_wradcpsc

#define _hw_wradcpsc(i,a,v,g,...)	HW_X(_hwx_wradcpsc1,g)(_hw,v,g)
#define _hwa_wradcpsc(i,a,v,g,...)	HW_X(_hwx_wradcpsc1,g)(_hwa,v,g)

#define _hwx_wradcpsc1_0(x,v,g)		HW_E_G(g)
#define _hwx_wradcpsc1_1(x,v,g)		HW_X(_hwx_wradcpsc2,v)(x,v)
#define _hwx_wradcpsc2_1(x,v)		HW_E_V()
#define _hwx_wradcpsc2_0(x,v)				\
  do{							\
    if ( v-1!=1 && v-1!=3 && v-1!=5 && v-1!=7 )		\
      HWA_E_VL(v,2|4|6|8);				\
    x##_write_reg(rcc,adcpre,(v-2)/3);			\
  }while(0)



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
