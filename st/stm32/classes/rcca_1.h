
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

/**
 * @page stm32_rcca Class _rcca: Reset and Clock Control (RCC)
 */
#define _hw_class__rcca

/*	Class registers
 */
#define _hw_reg__rcca_cr		_r32, 0x00, 0x010D00F9, 0
#define _hw_reg__rcca_cfgr		_r32, 0x04, 0x077FFFF3, 0
#define _hw_reg__rcca_apb2enr		_r32, 0x18, 0x0038FFFD, 0
#define _hw_reg__rcca_apb1enr		_r32, 0x1C, 0x3AFED3FF, 0

#define _hw_reg__rcca_pllrdy		_cb1, cr, 1, 25
#define _hw_reg__rcca_pllon		_cb1, cr, 1, 24
#define _hw_reg__rcca_csson		_cb1, cr, 1, 19
#define _hw_reg__rcca_hsebyp		_cb1, cr, 1, 18
#define _hw_reg__rcca_hserdy		_cb1, cr, 1, 17
#define _hw_reg__rcca_hseon		_cb1, cr, 1, 16
#define _hw_reg__rcca_hsical		_cb1, cr, 8,  8
#define _hw_reg__rcca_hsitrim		_cb1, cr, 5,  3
#define _hw_reg__rcca_hsirdy		_cb1, cr, 1,  1
#define _hw_reg__rcca_hsion		_cb1, cr, 1,  0

#define _hw_reg__rcca_mco		_cb1, cfgr, 3, 24
#define _hw_reg__rcca_usbpre		_cb1, cfgr, 1, 22
#define _hw_reg__rcca_pllmul		_cb1, cfgr, 4, 18
#define _hw_reg__rcca_pllxtpre		_cb1, cfgr, 1, 17
#define _hw_reg__rcca_pllsrc		_cb1, cfgr, 1, 16
#define _hw_reg__rcca_pllxtpresrc	_cb1, cfgr, 2, 16	/* convenient */
#define _hw_reg__rcca_adcpre		_cb1, cfgr, 2, 14
#define _hw_reg__rcca_ppre2		_cb1, cfgr, 3, 11
#define _hw_reg__rcca_apb2		_cb1, cfgr, 3, 11	/* convenient */
#define _hw_reg__rcca_apb2prescaler	_cb1, cfgr, 3, 11	/* convenient */
#define _hw_reg__rcca_ppre1		_cb1, cfgr, 3,  8
#define _hw_reg__rcca_apb1		_cb1, cfgr, 3,  8	/* convenient */
#define _hw_reg__rcca_apb1prescaler	_cb1, cfgr, 3,  8	/* convenient */
#define _hw_reg__rcca_hpre		_cb1, cfgr, 4,  4
#define _hw_reg__rcca_sws		_cb1, cfgr, 2,  2
#define _hw_reg__rcca_sw		_cb1, cfgr, 2,  0


/*	Convenient objects
 */
#define _hw_def_hse			_obj, 102, 0
#define _hw_reg_hse_cken		_xob1, rcc, cr, 1, 16	/* convenient */

#define _hw_def_hsi			_obj, 103, 0
#define _hw_reg_hsi_cken		_xob1, rcc, cr, 1,  0	/* convenient */

#define _hw_def_usbprescaler		_obj, 104, 0
#define _hw_def_adcprescaler		_obj, 105, 0

#define _hw_def_apb1			_apba, 106, 0
#define _hw_def_apb2			_apba, 107, 0


#if !defined __ASSEMBLER__

/*	HWA context
 */
typedef struct {
  hwa_r32_t cr ;
  hwa_r32_t cfgr ;
  hwa_r32_t apb2enr ;
  hwa_r32_t apb1enr ;
} hwa_rcca_t ;

#endif
