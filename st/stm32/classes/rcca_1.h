
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief RCC
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_rcca Class _rcca: Reset and Clock Control (RCC)
 *
 * This class has no method, it is just a collection of registers.
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
 * * `pllrdy`
 * * `pllon`
 * * `csson`
 * * `hsebyp`
 * * `hserdy`
 * * `hseon`
 * * `hsical`
 * * `hsitrim`
 * * `hsirdy`
 * * `hsion`
 * <br>
 * * `mco`
 * * `usbpre`
 * * `pllmul`
 * * `pllxtpre`
 * * `pllsrc`
 * * `pllxtpresrc`		( convenient )
 * * `adcpre`
 * * `ppre2`, `apb2`, `apb2prescaler`
 * * `ppre1`, `apb1`, `apb1prescaler`
 * * `hpre`
 * * `sws`
 * * `sw`
 * <br>
 * * `tim11en`
 * * `tim10en`
 * * `tim9en`
 * * `adc3en`
 * * `usart1en`
 * * `tim8en`
 * * `spi1en`
 * * `tim1en`
 * * `adc2en`
 * * `adc1en`
 * * `port6en`
 * * `port5en`
 * * `port4en`
 * * `port3en`
 * * `port2en`
 * * `port1en`
 * * `port0en`
 * * `afioen`
 * <br>
 * * `dacen`, `dac`
 * * `pwren`, `power`
 * * `bkpen`, `backup`
 * * `canen`, `can`
 * * `usben`, `usb`
 * * `i2c2en`, `i2c2`
 * * `i2c1en`, `i2c1`
 * * `uart5en`, `uart5`
 * * `uart4en`, `uart4`
 * * `usart3en`, `usart3`
 * * `usart2en`, `usart2`
 * * `spi3en`, `spi3`
 * * `spi2en`, `spi2`
 * * `wwdgen`, `windiwwdg`
 * * `tim14en`, `counter14`
 * * `tim13en`, `counter13`
 * * `tim12en`, `counter12`
 * * `tim7en`, `counter7`
 * * `tim6en`, `counter6`
 * * `tim5en`, `counter5`
 * * `tim4en`, `counter4`
 * * `tim3en`, `counter3`
 * * `tim2en`, `counter2`
 */

#define hw_class__rcca

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
#define hw_rcc_pllrdy			_ob1, cr, 1, 25
#define hw_rcc_pllon			_ob1, cr, 1, 24
#define hw_rcc_csson			_ob1, cr, 1, 19
#define hw_rcc_hsebyp			_ob1, cr, 1, 18
#define hw_rcc_hserdy			_ob1, cr, 1, 17
#define hw_rcc_hseon			_ob1, cr, 1, 16
#define hw_rcc_hsical			_ob1, cr, 8,  8
#define hw_rcc_hsitrim			_ob1, cr, 5,  3
#define hw_rcc_hsirdy			_ob1, cr, 1,  1
#define hw_rcc_hsion			_ob1, cr, 1,  0

#define hw_rcc_mco			_ob1, cfgr, 3, 24
#define hw_rcc_usbpre			_ob1, cfgr, 1, 22
#define hw_rcc_pllmul			_ob1, cfgr, 4, 18
#define hw_rcc_pllxtpre			_ob1, cfgr, 1, 17
#define hw_rcc_pllsrc			_ob1, cfgr, 1, 16
#define hw_rcc_pllxtpresrc		_ob1, cfgr, 2, 16	/* convenient */
#define hw_rcc_adcpre			_ob1, cfgr, 2, 14
#define hw_rcc_ppre2			_ob1, cfgr, 3, 11
#define hw_rcc_apb2			_ob1, cfgr, 3, 11	/* convenient */
#define hw_rcc_apb2prescaler		_ob1, cfgr, 3, 11	/* convenient */
#define hw_rcc_ppre1			_ob1, cfgr, 3,	8
#define hw_rcc_apb1			_ob1, cfgr, 3,	8	/* convenient */
#define hw_rcc_apb1prescaler		_ob1, cfgr, 3,	8	/* convenient */
#define hw_rcc_hpre			_ob1, cfgr, 4,	4
#define hw_rcc_sws			_ob1, cfgr, 2,	2
#define hw_rcc_sw			_ob1, cfgr, 2,	0

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


/*	Convenient objects
 */
#define hw_class__hsea
#define hw_hse				_hsea, 0
#define hw_hse_cken			_xb1, rcc, cr, 1, 16	/* convenient */

#define hw_class__hsia
#define hw_hsi				_hsia, 0
#define hw_hsi_cken			_xb1, rcc, cr, 1,  0	/* convenient */

#define hw_usbprescaler			_obj, 0
#define hw_adcprescaler			_obj, 0

#define hw_apb1				_apba, 0
#define hw_apb2				_apba, 0


//#define hw_class__rccen


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
