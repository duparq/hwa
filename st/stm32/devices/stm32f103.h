
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32F103
 */

#include "../hwa_1.h"

/**
 * @page stm32f103 STM32F103
 *
 *  * @subpage stm32f103rbt6
 *  * @subpage stm32f103c8t6
 *  * @subpage stm32f103vct6
 */

/**
 * @page stm32f103
 * @section stm32f103_sym Defined symbols
 *
 * HWA defines the following symbols describing the target device and its
 * hardware configuration:
 *
 * Symbol		    | Value
 * :------------------------|:-----------
 * `HW_DEVICE_STM32F103`    |Void.
 * `HW_DEVICE_HSIHZ`        |8*1000000
 * `HW_DEVICE_LSIHZ`        |40*1000
 */
#define HW_DEVICE_STM32F103
/* #define HW_DEVICE_ARCH		arm */
#define HW_DEVICE_HSIHZ			8*1000000
#define HW_DEVICE_LSIHZ			40*1000



/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

/**
 * @page attinyx4
 * @section attinyx4_interrupts Interrupts
 * 
 * Interrupt name	  | Comments
 * :----------------------|------------------------
 * `systick`		  | SysTick timer reached 0
 *
 */
#define _hw_irq_systick_		_irq, systick, 1, ie, if


/*******************************************************************************
 *									       *
 *	Clocks								       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_rcc Clocks control
 *
 * Low-, medium-, high- and XL-density devices hold a RCC of class @ref
 * stm32_rcca "_rcca" that holds hardware registers shared by several objects to
 * access the device's RCC in order to configure various clocks in the device:
 *
 *  * @ref stm32_hsia "hsi": 8 MHz internal RC oscillator.
 *  * @ref stm32_hsea "hse": crystal external oscillator.
 *  * @ref stm32_plla "pll": PLL multiplying HSI or HSE clock.
 *  * @ref stm32_sclka "sysclk": connected to HSI, PLL, or HSE, clocks
 *    * @ref stm32_ahba "ahb": clocks
 *      * sdio
 *      * fsmc
 *      * core
 *      * memory
 *      * dma
 *      * Cortex system timer
 *      * FCLK Cortex free running clock
 *      * @ref stm32_apba "apb1" (low-speed): clocks (36 MHz max.)
 *        * counter2..7, counter12..14
 *        * APB1 peripherals
 *      * @ref stm32_apba "apb2" (high-speed): clocks
 *        * counter1, counter8..11
 *        * adc and other APB2 peripherals
 *    * i2s2
 *    * i2s3
 *
 * The RCC is also used transparently by several other objects to enable/disable
 * their clocking for power management purpose.
 *
 * @note Connectivity line devices hold a RCC of class `_rccb`. Not implemented yet.
 */

#include "../classes/rcca_1.h"

#define _hw_def_rcc			_rcca, 101, 0x40021000

/*	Object registers
 */
/* #define _hw_reg_rcc_cr			_r32, 0x00, 0x010D00F9, 0 */
/* #define _hw_reg_rcc_cfgr		_r32, 0x04, 0x077FFFF3, 0 */
/* #define _hw_reg_rcc_apb2enr		_r32, 0x18, 0x0038FFFD, 0 */

/* #define _hw_reg_rcc_pllrdy		_ob1, cr, 1, 25 */
/* #define _hw_reg_rcc_pllon		_ob1, cr, 1, 24 */
/* #define _hw_reg_rcc_csson		_ob1, cr, 1, 19 */
/* #define _hw_reg_rcc_hsebyp		_ob1, cr, 1, 18 */
/* #define _hw_reg_rcc_hserdy		_ob1, cr, 1, 17 */
/* #define _hw_reg_rcc_hseon		_ob1, cr, 1, 16 */
/* #define _hw_reg_rcc_hsical		_ob1, cr, 8,  8 */
/* #define _hw_reg_rcc_hsitrim		_ob1, cr, 5,  3 */
/* #define _hw_reg_rcc_hsirdy		_ob1, cr, 1,  1 */
/* #define _hw_reg_rcc_hsion		_ob1, cr, 1,  0 */

/* #define _hw_reg_rcc_mco			_ob1, cfgr, 3, 24 */
/* #define _hw_reg_rcc_usbpre		_ob1, cfgr, 1, 22 */
/* #define _hw_reg_rcc_pllmul		_ob1, cfgr, 4, 18 */
/* #define _hw_reg_rcc_pllxtpre		_ob1, cfgr, 1, 17 */
/* #define _hw_reg_rcc_pllsrc		_ob1, cfgr, 1, 16 */
/* #define _hw_reg_rcc_pllxtpresrc		_ob1, cfgr, 2, 16	/\* convenient *\/ */
/* #define _hw_reg_rcc_adcpre		_ob1, cfgr, 2, 14 */
/* #define _hw_reg_rcc_ppre2		_ob1, cfgr, 3, 11 */
/* #define _hw_reg_rcc_apb2		_ob1, cfgr, 3, 11	/\* convenient *\/ */
/* #define _hw_reg_rcc_apb2prescaler	_ob1, cfgr, 3, 11	/\* convenient *\/ */
/* #define _hw_reg_rcc_ppre1		_ob1, cfgr, 3,  8 */
/* #define _hw_reg_rcc_apb1		_ob1, cfgr, 3,  8	/\* convenient *\/ */
/* #define _hw_reg_rcc_apb1prescaler	_ob1, cfgr, 3,  8	/\* convenient *\/ */
/* #define _hw_reg_rcc_hpre		_ob1, cfgr, 4,  4 */
/* #define _hw_reg_rcc_sws			_ob1, cfgr, 2,  2 */
/* #define _hw_reg_rcc_sw			_ob1, cfgr, 2,  0 */

#define _hw_reg__rcca_cr		_r32, 0x00, 0x010D00F9, 0
#define _hw_reg__rcca_cfgr		_r32, 0x04, 0x077FFFF3, 0
#define _hw_reg__rcca_apb2enr		_r32, 0x18, 0x0038FFFD, 0

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


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_pins Ports and pins
 *
 * Up to 7 GPIO ports of class @ref stm32_p16a "_p16a", each holding 16 GPIO
 * pins of class @ref stm32_io1a "_io1a":
 *
 *  * @ref stm32_p16a "port0" (PORTA): @ref stm32_io1a "pa0..15"
 *  * @ref stm32_p16a "port1" (PORTB): @ref stm32_io1a "pb0..15"
 *  * @ref stm32_p16a "port2" (PORTC): @ref stm32_io1a "pc0..15"
 *  * @ref stm32_p16a "port3" (PORTD): @ref stm32_io1a "pd0..15"
 *  * @ref stm32_p16a "port4" (PORTE): @ref stm32_io1a "pe0..15"
 */

#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"

/*	Objects				class, id, address
 */
#define _hw_def_port0			_p16a, 108, 0x40010800
#define _hw_def_port1			_p16a, 109, 0x40010C00
#define _hw_def_port2			_p16a, 110, 0x40011000
#define _hw_def_port3			_p16a, 111, 0x40011400
#define _hw_def_port4			_p16a, 112, 0x40011800
/* #define _hw_def_port5			_p16a, 113, 0x40011C00 */
/* #define _hw_def_port6			_p16a, 114, 0x40012000 */

/*	Object registers
 */
#define _hw_reg_port0_cken		_xob1, rcc, apb2enr, 1, 2	/* convenient */
#define _hw_reg_port1_cken		_xob1, rcc, apb2enr, 1, 3	/* convenient */
#define _hw_reg_port2_cken		_xob1, rcc, apb2enr, 1, 4	/* convenient */
#define _hw_reg_port3_cken		_xob1, rcc, apb2enr, 1, 5	/* convenient */
#define _hw_reg_port4_cken		_xob1, rcc, apb2enr, 1, 6	/* convenient */
/* #define _hw_reg_port5_cken		_xob1, rcc, apb2enr, 1, 7	/\* convenient *\/ */
/* #define _hw_reg_port6_cken		_xob1, rcc, apb2enr, 1, 8	/\* convenient *\/ */

/*  Pins				class, id, peripheral, bn, bp
 */
#define _hw_def_pa0			_io1a, 113, port0,  1,  0
#define _hw_def_pa1			_io1a, 114, port0,  1,  1
#define _hw_def_pa2			_io1a, 115, port0,  1,  2
#define _hw_def_pa3			_io1a, 116, port0,  1,  3
#define _hw_def_pa4			_io1a, 117, port0,  1,  4
#define _hw_def_pa5			_io1a, 118, port0,  1,  5
#define _hw_def_pa6			_io1a, 119, port0,  1,  6
#define _hw_def_pa7			_io1a, 120, port0,  1,  7
#define _hw_def_pa8			_io1a, 121, port0,  1,  8
#define _hw_def_pa9			_io1a, 122, port0,  1,  9
#define _hw_def_pa10		_io1a, 123, port0,  1, 10
#define _hw_def_pa11		_io1a, 124, port0,  1, 11
#define _hw_def_pa12		_io1a, 125, port0,  1, 12
#define _hw_def_pa13		_io1a, 126, port0,  1, 13
#define _hw_def_pa14		_io1a, 127, port0,  1, 14
#define _hw_def_pa15		_io1a, 128, port0,  1, 15
#define _hw_def_porta			_io1a, 129, port0, 16,  0

#define _hw_def_pb0			_io1a, 130, port1,  1,  0
#define _hw_def_pb1			_io1a, 131, port1,  1,  1
#define _hw_def_pb2			_io1a, 132, port1,  1,  2
#define _hw_def_pb3			_io1a, 133, port1,  1,  3
#define _hw_def_pb4			_io1a, 134, port1,  1,  4
#define _hw_def_pb5			_io1a, 135, port1,  1,  5
#define _hw_def_pb6			_io1a, 136, port1,  1,  6
#define _hw_def_pb7			_io1a, 137, port1,  1,  7
#define _hw_def_pb8			_io1a, 138, port1,  1,  8
#define _hw_def_pb9			_io1a, 139, port1,  1,  9
#define _hw_def_pb10		_io1a, 140, port1,  1, 10
#define _hw_def_pb11		_io1a, 141, port1,  1, 11
#define _hw_def_pb12		_io1a, 142, port1,  1, 12
#define _hw_def_pb13		_io1a, 143, port1,  1, 13
#define _hw_def_pb14		_io1a, 144, port1,  1, 14
#define _hw_def_pb15		_io1a, 145, port1,  1, 15
#define _hw_def_portb			_io1a, 146, port1, 16,  0

#define _hw_def_pc0			_io1a, 147, port2,  1,  0
#define _hw_def_pc1			_io1a, 148, port2,  1,  1
#define _hw_def_pc2			_io1a, 149, port2,  1,  2
#define _hw_def_pc3			_io1a, 150, port2,  1,  3
#define _hw_def_pc4			_io1a, 151, port2,  1,  4
#define _hw_def_pc5			_io1a, 152, port2,  1,  5
#define _hw_def_pc6			_io1a, 153, port2,  1,  6
#define _hw_def_pc7			_io1a, 154, port2,  1,  7
#define _hw_def_pc8			_io1a, 155, port2,  1,  8
#define _hw_def_pc9			_io1a, 156, port2,  1,  9
#define _hw_def_pc10		_io1a, 157, port2,  1, 10
#define _hw_def_pc11		_io1a, 158, port2,  1, 11
#define _hw_def_pc12		_io1a, 159, port2,  1, 12
#define _hw_def_pc13		_io1a, 160, port2,  1, 13
#define _hw_def_pc14		_io1a, 161, port2,  1, 14
#define _hw_def_pc15		_io1a, 162, port2,  1, 15
#define _hw_def_portc			_io1a, 163, port2, 16,  0

#define _hw_def_pd0			_io1a, 164, port3,  1,  0
#define _hw_def_pd1			_io1a, 165, port3,  1,  1
#define _hw_def_pd2			_io1a, 166, port3,  1,  2
#define _hw_def_pd3			_io1a, 167, port3,  1,  3
#define _hw_def_pd4			_io1a, 168, port3,  1,  4
#define _hw_def_pd5			_io1a, 169, port3,  1,  5
#define _hw_def_pd6			_io1a, 170, port3,  1,  6
#define _hw_def_pd7			_io1a, 171, port3,  1,  7
#define _hw_def_pd8			_io1a, 172, port3,  1,  8
#define _hw_def_pd9			_io1a, 173, port3,  1,  9
#define _hw_def_pd10		_io1a, 174, port3,  1, 10
#define _hw_def_pd11		_io1a, 175, port3,  1, 11
#define _hw_def_pd12		_io1a, 176, port3,  1, 12
#define _hw_def_pd13		_io1a, 177, port3,  1, 13
#define _hw_def_pd14		_io1a, 178, port3,  1, 14
#define _hw_def_pd15		_io1a, 179, port3,  1, 15
#define _hw_def_portd			_io1a, 180, port3, 16,  0

#define _hw_def_pe0			_io1a, 181, port4,  1,  0
#define _hw_def_pe1			_io1a, 182, port4,  1,  1
#define _hw_def_pe2			_io1a, 183, port4,  1,  2
#define _hw_def_pe3			_io1a, 184, port4,  1,  3
#define _hw_def_pe4			_io1a, 185, port4,  1,  4
#define _hw_def_pe5			_io1a, 186, port4,  1,  5
#define _hw_def_pe6			_io1a, 187, port4,  1,  6
#define _hw_def_pe7			_io1a, 188, port4,  1,  7
#define _hw_def_pe8			_io1a, 189, port4,  1,  8
#define _hw_def_pe9			_io1a, 190, port4,  1,  9
#define _hw_def_pe10		_io1a, 191, port4,  1, 10
#define _hw_def_pe11		_io1a, 192, port4,  1, 11
#define _hw_def_pe12		_io1a, 193, port4,  1, 12
#define _hw_def_pe13		_io1a, 194, port4,  1, 13
#define _hw_def_pe14		_io1a, 195, port4,  1, 14
#define _hw_def_pe15		_io1a, 196, port4,  1, 15
#define _hw_def_porte			_io1a, 197, port4, 16,  0

/* #define _hw_def_pf0			_io1a, 200, port5,  1,  0 */
/* #define _hw_def_pf1			_io1a, 201, port5,  1,  1 */
/* #define _hw_def_pf2			_io1a, 202, port5,  1,  2 */
/* #define _hw_def_pf3			_io1a, 203, port5,  1,  3 */
/* #define _hw_def_pf4			_io1a, 204, port5,  1,  4 */
/* #define _hw_def_pf5			_io1a, 205, port5,  1,  5 */
/* #define _hw_def_pf6			_io1a, 206, port5,  1,  6 */
/* #define _hw_def_pf7			_io1a, 207, port5,  1,  7 */
/* #define _hw_def_pf8			_io1a, 208, port5,  1,  8 */
/* #define _hw_def_pf9			_io1a, 209, port5,  1,  9 */
/* #define _hw_def_pf10		_io1a, 210, port5,  1, 10 */
/* #define _hw_def_pf11		_io1a, 211, port5,  1, 11 */
/* #define _hw_def_pf12		_io1a, 212, port5,  1, 12 */
/* #define _hw_def_pf13		_io1a, 213, port5,  1, 13 */
/* #define _hw_def_pf14		_io1a, 214, port5,  1, 14 */
/* #define _hw_def_pf15		_io1a, 215, port5,  1, 15 */
/* #define _hw_def_portf			_io1a, 216, port5, 16,  0 */

/* #define _hw_def_pg0			_io1a, 217, port6,  1,  0 */
/* #define _hw_def_pg1			_io1a, 218, port6,  1,  1 */
/* #define _hw_def_pg2			_io1a, 219, port6,  1,  2 */
/* #define _hw_def_pg3			_io1a, 220, port6,  1,  3 */
/* #define _hw_def_pg4			_io1a, 221, port6,  1,  4 */
/* #define _hw_def_pg5			_io1a, 222, port6,  1,  5 */
/* #define _hw_def_pg6			_io1a, 223, port6,  1,  6 */
/* #define _hw_def_pg7			_io1a, 224, port6,  1,  7 */
/* #define _hw_def_pg8			_io1a, 225, port6,  1,  8 */
/* #define _hw_def_pg9			_io1a, 226, port6,  1,  9 */
/* #define _hw_def_pg10		_io1a, 227, port6,  1, 10 */
/* #define _hw_def_pg11		_io1a, 228, port6,  1, 11 */
/* #define _hw_def_pg12		_io1a, 229, port6,  1, 12 */
/* #define _hw_def_pg13		_io1a, 230, port6,  1, 13 */
/* #define _hw_def_pg14		_io1a, 231, port6,  1, 14 */
/* #define _hw_def_pg15		_io1a, 232, port6,  1, 15 */
/* #define _hw_def_portg			_io1a, 233, port6, 16,  0 */

/* #if defined HW_DEVICE_PACKAGE_LQFP64 */
/* # */
/* #  define _hw_pin_14			, pa0 */
/* #  define _hw_pin_15			, pa1 */
/* #  define _hw_pin_16			, pa2 */
/* #  define _hw_pin_17			, pa3 */
/* #  define _hw_pin_20			, pa4 */
/* #  define _hw_pin_21			, pa5 */
/* #  define _hw_pin_22			, pa6 */
/* #  define _hw_pin_23			, pa7 */
/* #  define _hw_pin_41			, pa8 */
/* #  define _hw_pin_42			, pa9 */
/* #  define _hw_pin_43			, pa10 */
/* #  define _hw_pin_44			, pa11 */
/* #  define _hw_pin_45			, pa12 */
/* #  define _hw_pin_46			, pa13 */
/* #  define _hw_pin_49			, pa14 */
/* #  define _hw_pin_50			, pa15 */
/* # */
/* #endif */


/*******************************************************************************
 *									       *
 *	SysTick								       *
 *									       *
 *******************************************************************************/

#include "../classes/stka_1.h"

#define _hw_def_systick			_stka, 101, 0xE000E010



#if !defined __ASSEMBLER__

/**
 * @brief The HWA context
 *
 * This structure is instanciated by hwa_begin() or hwa_begin_from_reset() and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_rcca_t	rcc ;

  hwa_p16a_t	port0 ;
  hwa_p16a_t	port1 ;
  hwa_p16a_t	port2 ;
  hwa_p16a_t	port3 ;
  hwa_p16a_t	port4 ;
  /* hwa_p16a_t	port5 ; */
  /* hwa_p16a_t	port6 ; */
  hwa_stka_t	systick ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/rcca_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p16a_2.h"
#include "../classes/stka_2.h"

HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup( rcc );
  _hwa_setup( port0 );
  _hwa_setup( port1 );
  _hwa_setup( port2 );
  _hwa_setup( port3 );
  _hwa_setup( port4 );
  /* _hwa_setup( port5 ); */
  /* _hwa_setup( port6 ); */
  _hwa_setup( systick );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init( rcc );
  _hwa_init( port0 );
  _hwa_init( port1 );
  _hwa_init( port2 );
  _hwa_init( port3 );
  _hwa_init( port4 );
  /* _hwa_init( port5 ); */
  /* _hwa_init( port6 ); */
  _hwa_init( systick );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit( rcc );
  _hwa_commit( port0 );
  _hwa_commit( port1 );
  _hwa_commit( port2 );
  _hwa_commit( port3 );
  _hwa_commit( port4 );
  /* _hwa_commit( port5 ); */
  /* _hwa_commit( port6 ); */
  _hwa_commit( systick );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page stm32f103
 * <br>
 */
