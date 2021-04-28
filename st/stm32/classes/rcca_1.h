
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief RCC
 */

#define hw_class__rcca

#include "hsia_1.h"
#include "hsea_1.h"
#include "plla_1.h"

#define hw_hsi				_hsia, 0
#define hw_hse				_hsea, 0
#define hw_pll				_plla, 0

#define hw_class__ahba

#define hw_ahb				_ahba, 0

#define hw_class__apba

#define hw_apb1				_apba, 0
#define hw_apb2				_apba, 0

/**
 * @ingroup stm32_classes
 * @defgroup stm32_rcca Class _rcca: Reset and Clock Control (RCC)
 *
 * This class has no method and no relatives, it is just a collection of
 * registers used by the following objects:
 *
 *  * @ref stm32_hsia "hsi"
 *  * @ref stm32_hsea "hse"
 *  * @ref stm32_plla "pll"
 *  * @ref stm32_ahba "ahb"
 *  * @ref stm32_apba "apb1", @ref stm32_apba "apb2"
 *
 * @section stm32_rccareg Registers
 *
 * Hardware registers:
 *
 * * `cr`
 * * `cfgr`
 * * `cir`
 * * `apb2enr`
 * * `apb1enr`
 *
 * Logical registers:
 *
 * * `csson`
 * <br>
 * * `mco`
 * * `sws`
 * * `sw`
 */

/*  Hardware registers
 */
#define hw_rcc_cr			_r32, 0x00, 0x010D00F9, 0
#define hw_rcc_cfgr			_r32, 0x04, 0x077FFFF3, 0
#define hw_rcc_cir			_r32, 0x08, 0x00FFFFFF, 0
#define hw_rcc_apb2enr			_r32, 0x18, 0x0038FFFD, 0
#define hw_rcc_apb1enr			_r32, 0x1C, 0x3AFED3FF, 0

/* Logical registers are implemented as object registers since there is only one
 * RCC in the device and HW_X() will find them faster this way.
 */
#define hw_rcc_csson			_ob1, cr, 1, 19

#define hw_pll_rdy			_xb1, rcc, cr, 1, 25
#define hw_pll_on			_xb1, rcc, cr, 1, 24
#define hw_pll_cken			_xb1, rcc, cr, 1, 24	/* convenient */

#define hw_hse_byp			_xb1, rcc, cr, 1, 18
#define hw_hse_rdy			_xb1, rcc, cr, 1, 17
#define hw_hse_on			_xb1, rcc, cr, 1, 16
#define hw_hse_cken			_xb1, rcc, cr, 1, 16	/* convenient */

#define hw_hsi_cal			_xb1, rcc, cr, 8,  8
#define hw_hsi_trim			_xb1, rcc, cr, 5,  3
#define hw_hsi_rdy			_xb1, rcc, cr, 1,  1
#define hw_hsi_on			_xb1, rcc, cr, 1,  0
#define hw_hsi_cken			_xb1, rcc, cr, 1,  0	/* convenient */

#define hw_rcc_mco			_ob1, cfgr, 3, 24
#define hw_rcc_usbpre			_ob1, cfgr, 1, 22
#define hw_rcc_adcpre			_ob1, cfgr, 2, 14
#define hw_rcc_ppre2			_ob1, cfgr, 3, 11
#define hw_rcc_apb2			_ob1, cfgr, 3, 11	/* convenient */
//#define hw_rcc_apb2prescaler		_ob1, cfgr, 3, 11	/* convenient */
#define hw_rcc_ppre1			_ob1, cfgr, 3,	8
#define hw_rcc_apb1			_ob1, cfgr, 3,	8	/* convenient */
//#define hw_rcc_apb1prescaler		_ob1, cfgr, 3,	8	/* convenient */
#define hw_rcc_hpre			_ob1, cfgr, 4,	4
#define hw_rcc_sws			_ob1, cfgr, 2,	2
#define hw_rcc_sw			_ob1, cfgr, 2,	0

#define hw_pll_mul			_xb1, rcc, cfgr, 4, 18
#define hw_pll_xtpre			_xb1, rcc, cfgr, 1, 17
#define hw_pll_src			_xb1, rcc, cfgr, 1, 16
#define hw_pll_xtpresrc			_xb1, rcc, cfgr, 2, 16	/* convenient */

#define hw_hse_rdyc			_xb1, rcc, cir, 1, 19
#define hw_hse_rdye			_xb1, rcc, cir, 1, 11
#define hw_hse_rdyf			_xb1, rcc, cir, 1,  3

#define hw_hsi_rdyc			_xb1, rcc, cir, 1, 18
#define hw_hsi_rdye			_xb1, rcc, cir, 1, 10
#define hw_hsi_rdyf			_xb1, rcc, cir, 1,  2

#define hw_rcc_tim11en			_ob1, apb2enr, 1, 21
#define hw_rcc_tim10en			_ob1, apb2enr, 1, 20
#define hw_rcc_tim9en			_ob1, apb2enr, 1, 19
#define hw_rcc_adc3en			_ob1, apb2enr, 1, 15
#define hw_rcc_usart1en			_ob1, apb2enr, 1, 14
#define hw_rcc_tim8en			_ob1, apb2enr, 1, 13
#define hw_rcc_spi1en			_ob1, apb2enr, 1, 12
#define hw_rcc_tim1en			_ob1, apb2enr, 1, 11
#define hw_rcc_adc2en			_ob1, apb2enr, 1, 10
#define hw_rcc_adc1en			_ob1, apb2enr, 1,  9
#define hw_rcc_port6en			_ob1, apb2enr, 1,  8
#define hw_rcc_port5en			_ob1, apb2enr, 1,  7
#define hw_rcc_port4en			_ob1, apb2enr, 1,  6
#define hw_rcc_port3en			_ob1, apb2enr, 1,  5
#define hw_rcc_port2en			_ob1, apb2enr, 1,  4
#define hw_rcc_port1en			_ob1, apb2enr, 1,  3
#define hw_rcc_port0en			_ob1, apb2enr, 1,  2
#define hw_rcc_afioen			_ob1, apb2enr, 1,  0

#define hw_porta_cken			_xb1, rcc, apb2enr, 1, 2	/* convenient */
#define hw_portb_cken			_xb1, rcc, apb2enr, 1, 3	/* convenient */
#define hw_portc_cken			_xb1, rcc, apb2enr, 1, 4	/* convenient */
#define hw_portd_cken			_xb1, rcc, apb2enr, 1, 5	/* convenient */
#define hw_porte_cken			_xb1, rcc, apb2enr, 1, 6	/* convenient */
#define hw_porth_cken			_xb1, rcc, apb2enr, 1, 8	/* convenient */
#define hw_afio_cken			_xb1, rcc, apb2enr, 1, 0	/* convenient */

#define hw_rcc_dacen			_ob1, apb1enr, 1, 29
#define hw_rcc_pwren			_ob1, apb1enr, 1, 28
#define hw_rcc_bkpen			_ob1, apb1enr, 1, 27
#define hw_rcc_canen			_ob1, apb1enr, 1, 25
#define hw_rcc_usben			_ob1, apb1enr, 1, 23
#define hw_rcc_i2c2en			_ob1, apb1enr, 1, 22
#define hw_rcc_i2c1en			_ob1, apb1enr, 1, 21
#define hw_rcc_uart5en			_ob1, apb1enr, 1, 20
#define hw_rcc_uart4en			_ob1, apb1enr, 1, 19
#define hw_rcc_usart3en			_ob1, apb1enr, 1, 18
#define hw_rcc_usart2en			_ob1, apb1enr, 1, 17
#define hw_rcc_spi3en			_ob1, apb1enr, 1, 15
#define hw_rcc_spi2en			_ob1, apb1enr, 1, 14
#define hw_rcc_wwdgen			_ob1, apb1enr, 1, 11
#define hw_rcc_tim14en			_ob1, apb1enr, 1,  8
#define hw_rcc_tim13en			_ob1, apb1enr, 1,  7
#define hw_rcc_tim12en			_ob1, apb1enr, 1,  6
#define hw_rcc_tim7en			_ob1, apb1enr, 1,  5
#define hw_rcc_tim6en			_ob1, apb1enr, 1,  4
#define hw_rcc_tim5en			_ob1, apb1enr, 1,  3
#define hw_rcc_tim4en			_ob1, apb1enr, 1,  2
#define hw_rcc_tim3en			_ob1, apb1enr, 1,  1
#define hw_rcc_tim2en			_ob1, apb1enr, 1,  0

/*  HWA names
 */
#define hw_rcc_dac			_ob1, apb1enr, 1, 29
#define hw_rcc_power			_ob1, apb1enr, 1, 28
#define hw_rcc_backup			_ob1, apb1enr, 1, 27
#define hw_rcc_can			_ob1, apb1enr, 1, 25
#define hw_rcc_usb			_ob1, apb1enr, 1, 23
#define hw_rcc_i2c2			_ob1, apb1enr, 1, 22
#define hw_rcc_i2c1			_ob1, apb1enr, 1, 21
#define hw_rcc_uart5			_ob1, apb1enr, 1, 20
#define hw_rcc_uart4			_ob1, apb1enr, 1, 19
#define hw_rcc_usart3			_ob1, apb1enr, 1, 18
#define hw_rcc_usart2			_ob1, apb1enr, 1, 17
#define hw_rcc_spi3			_ob1, apb1enr, 1, 15
#define hw_rcc_spi2			_ob1, apb1enr, 1, 14
#define hw_rcc_windiwwdg		_ob1, apb1enr, 1, 11
#define hw_rcc_counter14		_ob1, apb1enr, 1,  8
#define hw_rcc_counter13		_ob1, apb1enr, 1,  7
#define hw_rcc_counter12		_ob1, apb1enr, 1,  6
#define hw_rcc_counter7			_ob1, apb1enr, 1,  5
#define hw_rcc_counter6			_ob1, apb1enr, 1,  4
#define hw_rcc_counter5			_ob1, apb1enr, 1,  3
#define hw_rcc_counter4			_ob1, apb1enr, 1,  2
#define hw_rcc_counter3			_ob1, apb1enr, 1,  1
#define hw_rcc_counter2			_ob1, apb1enr, 1,  0

#define hw_counter2_cken		_xb1, rcc, apb1enr, 1, 0	/* convenient */
#define hw_counter3_cken		_xb1, rcc, apb1enr, 1, 1	/* convenient */
#define hw_counter4_cken		_xb1, rcc, apb1enr, 1, 2	/* convenient */
#define hw_counter5_cken		_xb1, rcc, apb1enr, 1, 3	/* convenient */


/*	Convenient objects
 */
#define hw_usbprescaler			_obj, 0
#define hw_adcprescaler			_obj, 0


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
