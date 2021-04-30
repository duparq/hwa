
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief RCC
 */

#define hw_class__rccb

#include "hsia_1.h"
#include "hsea_1.h"
#include "pllb_1.h"
#include "ahba_1.h"

#define hw_hsi				_hsia, 0
#define hw_hse				_hsea, 0
#define hw_pll				_pllb, 0

#define hw_class__apba

#define hw_apb1				_apba, 0
#define hw_apb2				_apba, 0

/**
 * @ingroup stm32_classes
 * @defgroup stm32_rccb Class _rccb: Reset and Clock Control (RCC)
 *
 * This class has no method. It is mainly a collection of registers that are
 * accessed through the following objects:
 *
 *  * @ref stm32_hsia "hsi"
 *  * @ref stm32_hsea "hse"
 *  * @ref stm32_plla "pll"
 *  * @ref stm32_ahba "ahb"
 *  * @ref stm32_apba "apb1", @ref stm32_apba "apb2"
 *
 * @section stm32_rccbrel Relatives
 *
 * * Hardware registers:
 *   * `cr`
 *   * `cfgr`
 *   * `cir`
 *   * `apb2enr`
 *   * `apb1enr`
 *
 * Logical registers:
 *
 * * `csson`
 * <br>
 * * `mco`
 * * `sws`
 * * `sw`
 */

/*  Hardware registers								   Reset value
 */
#define hw_rcc_cr			_r32, 0x00, 0x050D00F9, 0		// 0x0000 XX81
#define hw_rcc_pllcfgr			_r32, 0x04, 0x0F437FFF, 0		// 0x2400 3010
#define hw_rcc_cfgr			_r32, 0x08, 0xFFFFFCF3, 0		// 0x0000 0000
#define hw_rcc_cir			_r32, 0x0C, 0x00BF3F00, 0x00BF0000 	// 0x0000 0000
//#define hw_rcc_ahb1rstr			_r32, 0x10, 
//#define hw_rcc_ahb2rstr			_r32, 0x14, 

//#define hw_rcc_apb1rstr			_r32, 0x20, 
//#define hw_rcc_apb2rstr			_r32, 0x24, 

#define hw_rcc_ahb1enr			_r32, 0x30, 0x0060109F, 0		// 0x0000 0000
#define hw_rcc_ahb2enr			_r32, 0x34, 0x00000080, 0		// 0x0000 0000

#define hw_rcc_apb1enr			_r32, 0x40, 0x10E2C80F, 0		// 0x0000 0000
#define hw_rcc_apb2enr			_r32, 0x44, 0x00177931, 0		// 0x0000 0000

/* Logical registers are implemented as object registers since there is only one
 * RCC in the device and HW_X() will find them faster this way.
 */
#define hw_i2s_pll_rdy			_xb1, rcc, cr, 1, 27
#define hw_i2s_pll_on			_xb1, rcc, cr, 1, 26

#define hw_pll_rdy			_xb1, rcc, cr, 1, 25
#define hw_pll_on			_xb1, rcc, cr, 1, 24

#define hw_rcc_csson			_ob1,      cr, 1, 19
#define hw_css_on			_xb1, rcc, cr, 1, 19

#define hw_hse_byp			_xb1, rcc, cr, 1, 18
#define hw_hse_rdy			_xb1, rcc, cr, 1, 17
#define hw_hse_on			_xb1, rcc, cr, 1, 16
#define hw_hse_cken			_xb1, rcc, cr, 1, 16		/* Convenient */

#define hw_hsi_cal			_xb1, rcc, cr, 8,  8
#define hw_hsi_trim			_xb1, rcc, cr, 5,  3
#define hw_hsi_rdy			_xb1, rcc, cr, 1,  1
#define hw_hsi_on			_xb1, rcc, cr, 1,  0
#define hw_hsi_cken			_xb1, rcc, cr, 1,  0		/* Convenient */

#define hw_pll_q			_xb1, rcc, pllcfgr, 4, 24
#define hw_pll_src			_xb1, rcc, pllcfgr, 1, 22
#define hw_pll_xtpresrc			_xb1, rcc, pllcfgr, 1, 22		/* Convenient */
#define hw_pll_p			_xb1, rcc, pllcfgr, 2, 16
#define hw_pll_n			_xb1, rcc, pllcfgr, 9,  6
#define hw_pll_m			_xb1, rcc, pllcfgr, 6,  0

#define hw_rcc_mco2			_ob1,      cfgr, 2, 30
#define hw_rcc_mco2pre			_ob1,      cfgr, 3, 27
#define hw_rcc_mco1pre			_ob1,      cfgr, 3, 24

#define hw_i2s_scr			_xb1, rcc, cfgr, 1, 23

#define hw_rcc_mco1			_xb1, rcc, cfgr, 2, 21

#define hw_rtc_pre			_xb1, rcc, cfgr, 5, 16

#define hw_rcc_ppre2			_ob1,      cfgr, 3, 13
#define hw_apb2_psc			_xb1, rcc, cfgr, 3, 13

#define hw_rcc_ppre1			_ob1,      cfgr, 3, 10
#define hw_apb1_psc			_xb1, rcc, cfgr, 3, 10

//#define hw_rcc_hpre			_ob1,      cfgr, 4,  4
#define hw_ahb_pre			_xb1, rcc, cfgr, 4,  4

#define hw_rcc_sws			_ob1,      cfgr, 2,  2
#define hw_rcc_sw			_ob1,      cfgr, 2,  0

#define hw_css_c			_xb1, rcc, cir, 1, 23
#define hw_i2s_pll_rdyc			_xb1, rcc, cir, 1, 21
#define hw_pll_rdyc			_xb1, rcc, cir, 1, 20
#define hw_hse_rdyc			_xb1, rcc, cir, 1, 19
#define hw_hsi_rdyc			_xb1, rcc, cir, 1, 18
#define hw_lse_rdyc			_xb1, rcc, cir, 1, 17
#define hw_lsi_rdyc			_xb1, rcc, cir, 1, 16
#define hw_i2s_pll_rdyie		_xb1, rcc, cir, 1, 13
#define hw_pll_rdyie			_xb1, rcc, cir, 1, 12
#define hw_hse_rdyie			_xb1, rcc, cir, 1, 11
#define hw_hsi_rdyie			_xb1, rcc, cir, 1, 10
#define hw_lse_rdyie			_xb1, rcc, cir, 1,  9
#define hw_lsi_rdyie			_xb1, rcc, cir, 1,  8
#define hw_css_f			_xb1, rcc, cir, 1,  7
#define hw_i2s_pll_rdyf			_xb1, rcc, cir, 1,  5
#define hw_pll_rdyf			_xb1, rcc, cir, 1,  4
#define hw_hse_rdyf			_xb1, rcc, cir, 1,  3
#define hw_hsi_rdyf			_xb1, rcc, cir, 1,  2
#define hw_lse_rdyf			_xb1, rcc, cir, 1,  1
#define hw_lsi_rdyf			_xb1, rcc, cir, 1,  0

#define hw_dma2_en			_xb1, rcc, ahb1enr, 1, 22
#define hw_dma1_en			_xb1, rcc, ahb1enr, 1, 21
#define hw_crc_en			_xb1, rcc, ahb1enr, 1, 12
#define hw_gpioh_en			_xb1, rcc, ahb1enr, 1,  7
#define hw_gpioe_en			_xb1, rcc, ahb1enr, 1,  4
#define hw_gpiod_en			_xb1, rcc, ahb1enr, 1,  3
#define hw_gpioc_en			_xb1, rcc, ahb1enr, 1,  2
#define hw_gpiov_en			_xb1, rcc, ahb1enr, 1,  1
#define hw_gpioa_en			_xb1, rcc, ahb1enr, 1,  0

#define hw_porth_cken			_xb1, rcc, ahb1enr, 1,  7
#define hw_porte_cken			_xb1, rcc, ahb1enr, 1,  4
#define hw_portd_cken			_xb1, rcc, ahb1enr, 1,  3
#define hw_portc_cken			_xb1, rcc, ahb1enr, 1,  2
#define hw_portv_cken			_xb1, rcc, ahb1enr, 1,  1
#define hw_porta_cken			_xb1, rcc, ahb1enr, 1,  0

#define hw_usart2_en			_xb1, rcc, apb1enr, 1, 17
#define hw_usart2_cken			_xb1, rcc, apb1enr, 1, 17	/* convenient */

#define hw_counter5_cken		_xb1, rcc, apb1enr, 1, 3	/* convenient */
#define hw_counter4_cken		_xb1, rcc, apb1enr, 1, 2	/* convenient */
#define hw_counter3_cken		_xb1, rcc, apb1enr, 1, 1	/* convenient */
#define hw_counter2_cken		_xb1, rcc, apb1enr, 1, 0	/* convenient */

#define hw_usart1_en			_xb1, rcc, apb2enr, 1, 4
#define hw_usart1_cken			_xb1, rcc, apb2enr, 1, 4	/* convenient */
#define hw_usart6_en			_xb1, rcc, apb2enr, 1, 5
#define hw_usart6_cken			_xb1, rcc, apb2enr, 1, 5	/* convenient */


#if !defined __ASSEMBLER__

/*	HWA context
 */
typedef struct {
  hwa_r32_t cr ;
  hwa_r32_t pllcfgr ;
  hwa_r32_t cfgr ;
  hwa_r32_t cir ;
  hwa_r32_t ahb1enr ;
  hwa_r32_t ahb2enr ;
  hwa_r32_t apb1enr ;
  hwa_r32_t apb2enr ;
} hwa_rccb_t ;

#endif
