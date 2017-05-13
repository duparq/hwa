
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
 * @section stm32f103_dev Supported devices
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
 *	Clocks								       *
 *									       *
 *******************************************************************************/

#include "../classes/rcca_1.h"

#define _hw_def_rcc			_rcca, 100, 0x40021000

/*	Object registers
 */
#define _hw_reg_rcc_cr			_r32, 0x00, 0x010D00F9, 0
#define _hw_reg_rcc_cfgr		_r32, 0x04, 0x077FFFC3, 0
#define _hw_reg_rcc_apb2enr		_r32, 0x18, 0x0038FFFD, 0

#define _hw_reg_rcc_pllrdy		_ob1, cr, 1, 25
#define _hw_reg_rcc_pllon		_ob1, cr, 1, 24
#define _hw_reg_rcc_csson		_ob1, cr, 1, 19
#define _hw_reg_rcc_hsebyp		_ob1, cr, 1, 18
#define _hw_reg_rcc_hserdy		_ob1, cr, 1, 17
#define _hw_reg_rcc_hseon		_ob1, cr, 1, 16
#define _hw_reg_rcc_hsical		_ob1, cr, 8,  8
#define _hw_reg_rcc_hsitrim		_ob1, cr, 5,  3
#define _hw_reg_rcc_hsirdy		_ob1, cr, 1,  1
#define _hw_reg_rcc_hsion		_ob1, cr, 1,  0

#define _hw_reg_rcc_mco			_ob1, cfgr, 3, 24
#define _hw_reg_rcc_usbpre		_ob1, cfgr, 1, 22
#define _hw_reg_rcc_pllmul		_ob1, cfgr, 4, 18
#define _hw_reg_rcc_pllxtpre		_ob1, cfgr, 1, 17
#define _hw_reg_rcc_pllsrc		_ob1, cfgr, 1, 16
#define _hw_reg_rcc_pllxtpresrc		_ob1, cfgr, 2, 16	/* convenient */
#define _hw_reg_rcc_adcpre		_ob1, cfgr, 2, 14
#define _hw_reg_rcc_ppre2		_ob1, cfgr, 3, 11
#define _hw_reg_rcc_ppre1		_ob1, cfgr, 3,  8
#define _hw_reg_rcc_hpre		_ob1, cfgr, 4,  4
#define _hw_reg_rcc_sws			_ob1, cfgr, 2,  2
#define _hw_reg_rcc_sw			_ob1, cfgr, 2,  0


/*	HSE oscillator
 */
#define _hw_def_hse			_hsea, 100, 0

#define _hw_reg_hse_cken		_xob1, rcc, cr, 1, 16	/* convenient */

#define _hw_class__sysclka
#define _hw_def_sysclk			_sysclka, 100, 0

#define _hw_class__plla
#define _hw_def_pll			_plla, 100, 0


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_pins Ports and pins
 *
 * Up to 7 GPIO ports of class @ref stm32_p16a "_p16a".
 *
 * Each GPIO port drives up to 16 GPIO pins of class @ref stm32_io1a "_io1a".
 */

#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"

/*	Objects				class, id, address
 */
#define _hw_def_port0			_p16a, 100, 0x40010800
#define _hw_def_port1			_p16a, 100, 0x40010c00
#define _hw_def_port2			_p16a, 100, 0x40011000
#define _hw_def_port3			_p16a, 100, 0x40014000
#define _hw_def_port4			_p16a, 100, 0x40011800
#define _hw_def_port5			_p16a, 100, 0x40011c00
#define _hw_def_port6			_p16a, 100, 0x40012000

/*	Object registers
 */
#define _hw_reg_port0_cken		_xob1, rcc, apb2enr, 1, 2	/* convenient */
#define _hw_reg_port1_cken		_xob1, rcc, apb2enr, 1, 3	/* convenient */
#define _hw_reg_port2_cken		_xob1, rcc, apb2enr, 1, 4	/* convenient */
#define _hw_reg_port3_cken		_xob1, rcc, apb2enr, 1, 5	/* convenient */
#define _hw_reg_port4_cken		_xob1, rcc, apb2enr, 1, 6	/* convenient */
#define _hw_reg_port5_cken		_xob1, rcc, apb2enr, 1, 7	/* convenient */
#define _hw_reg_port6_cken		_xob1, rcc, apb2enr, 1, 8	/* convenient */

/*  Pins				class, id, peripheral, bn, bp
 */
#define _hw_def_pin_pa0			_io1a, 104, port0,  1,  0
#define _hw_def_pin_pa1			_io1a, 105, port0,  1,  1
#define _hw_def_pin_pa2			_io1a, 106, port0,  1,  2
#define _hw_def_pin_pa3			_io1a, 107, port0,  1,  3
#define _hw_def_pin_pa4			_io1a, 108, port0,  1,  4
#define _hw_def_pin_pa5			_io1a, 109, port0,  1,  5
#define _hw_def_pin_pa6			_io1a, 110, port0,  1,  6
#define _hw_def_pin_pa7			_io1a, 111, port0,  1,  7
#define _hw_def_pin_pa8			_io1a, 111, port0,  1,  8
#define _hw_def_pin_pa9			_io1a, 111, port0,  1,  9
#define _hw_def_pin_pa10		_io1a, 111, port0,  1, 10
#define _hw_def_pin_pa11		_io1a, 111, port0,  1, 11
#define _hw_def_pin_pa12		_io1a, 111, port0,  1, 12
#define _hw_def_pin_pa13		_io1a, 111, port0,  1, 13
#define _hw_def_pin_pa14		_io1a, 111, port0,  1, 14
#define _hw_def_pin_pa15		_io1a, 111, port0,  1, 15
#define _hw_def_porta			_io1a, 112, port0, 16,  0

#define _hw_def_pin_pb0			_io1a, 104, port1,  1,  0
#define _hw_def_pin_pb1			_io1a, 105, port1,  1,  1
#define _hw_def_pin_pb2			_io1a, 106, port1,  1,  2
#define _hw_def_pin_pb3			_io1a, 107, port1,  1,  3
#define _hw_def_pin_pb4			_io1a, 108, port1,  1,  4
#define _hw_def_pin_pb5			_io1a, 109, port1,  1,  5
#define _hw_def_pin_pb6			_io1a, 110, port1,  1,  6
#define _hw_def_pin_pb7			_io1a, 111, port1,  1,  7
#define _hw_def_pin_pb8			_io1a, 111, port1,  1,  8
#define _hw_def_pin_pb9			_io1a, 111, port1,  1,  9
#define _hw_def_pin_pb10		_io1a, 111, port1,  1, 10
#define _hw_def_pin_pb11		_io1a, 111, port1,  1, 11
#define _hw_def_pin_pb12		_io1a, 111, port1,  1, 12
#define _hw_def_pin_pb13		_io1a, 111, port1,  1, 13
#define _hw_def_pin_pb14		_io1a, 111, port1,  1, 14
#define _hw_def_pin_pb15		_io1a, 111, port1,  1, 15
#define _hw_def_portb			_io1a, 112, port1, 16,  0

#define _hw_def_pin_pc0			_io1a, 104, port2,  1,  0
#define _hw_def_pin_pc1			_io1a, 105, port2,  1,  1
#define _hw_def_pin_pc2			_io1a, 106, port2,  1,  2
#define _hw_def_pin_pc3			_io1a, 107, port2,  1,  3
#define _hw_def_pin_pc4			_io1a, 108, port2,  1,  4
#define _hw_def_pin_pc5			_io1a, 109, port2,  1,  5
#define _hw_def_pin_pc6			_io1a, 110, port2,  1,  6
#define _hw_def_pin_pc7			_io1a, 111, port2,  1,  7
#define _hw_def_pin_pc8			_io1a, 111, port2,  1,  8
#define _hw_def_pin_pc9			_io1a, 111, port2,  1,  9
#define _hw_def_pin_pc10		_io1a, 111, port2,  1, 10
#define _hw_def_pin_pc11		_io1a, 111, port2,  1, 11
#define _hw_def_pin_pc12		_io1a, 111, port2,  1, 12
#define _hw_def_pin_pc13		_io1a, 111, port2,  1, 13
#define _hw_def_pin_pc14		_io1a, 111, port2,  1, 14
#define _hw_def_pin_pc15		_io1a, 111, port2,  1, 15
#define _hw_def_portc			_io1a, 112, port2, 16,  0

#define _hw_def_pin_pd0			_io1a, 104, port3,  1,  0
#define _hw_def_pin_pd1			_io1a, 105, port3,  1,  1
#define _hw_def_pin_pd2			_io1a, 106, port3,  1,  2
#define _hw_def_pin_pd3			_io1a, 107, port3,  1,  3
#define _hw_def_pin_pd4			_io1a, 108, port3,  1,  4
#define _hw_def_pin_pd5			_io1a, 109, port3,  1,  5
#define _hw_def_pin_pd6			_io1a, 110, port3,  1,  6
#define _hw_def_pin_pd7			_io1a, 111, port3,  1,  7
#define _hw_def_pin_pd8			_io1a, 111, port3,  1,  8
#define _hw_def_pin_pd9			_io1a, 111, port3,  1,  9
#define _hw_def_pin_pd10		_io1a, 111, port3,  1, 10
#define _hw_def_pin_pd11		_io1a, 111, port3,  1, 11
#define _hw_def_pin_pd12		_io1a, 111, port3,  1, 12
#define _hw_def_pin_pd13		_io1a, 111, port3,  1, 13
#define _hw_def_pin_pd14		_io1a, 111, port3,  1, 14
#define _hw_def_pin_pd15		_io1a, 111, port3,  1, 15
#define _hw_def_portd			_io1a, 112, port3, 16,  0

#define _hw_def_pin_pe0			_io1a, 104, port4,  1,  0
#define _hw_def_pin_pe1			_io1a, 105, port4,  1,  1
#define _hw_def_pin_pe2			_io1a, 106, port4,  1,  2
#define _hw_def_pin_pe3			_io1a, 107, port4,  1,  3
#define _hw_def_pin_pe4			_io1a, 108, port4,  1,  4
#define _hw_def_pin_pe5			_io1a, 109, port4,  1,  5
#define _hw_def_pin_pe6			_io1a, 110, port4,  1,  6
#define _hw_def_pin_pe7			_io1a, 111, port4,  1,  7
#define _hw_def_pin_pe8			_io1a, 111, port4,  1,  8
#define _hw_def_pin_pe9			_io1a, 111, port4,  1,  9
#define _hw_def_pin_pe10		_io1a, 111, port4,  1, 10
#define _hw_def_pin_pe11		_io1a, 111, port4,  1, 11
#define _hw_def_pin_pe12		_io1a, 111, port4,  1, 12
#define _hw_def_pin_pe13		_io1a, 111, port4,  1, 13
#define _hw_def_pin_pe14		_io1a, 111, port4,  1, 14
#define _hw_def_pin_pe15		_io1a, 111, port4,  1, 15
#define _hw_def_porte			_io1a, 112, port4, 16,  0

#define _hw_def_pin_pf0			_io1a, 104, port5,  1,  0
#define _hw_def_pin_pf1			_io1a, 105, port5,  1,  1
#define _hw_def_pin_pf2			_io1a, 106, port5,  1,  2
#define _hw_def_pin_pf3			_io1a, 107, port5,  1,  3
#define _hw_def_pin_pf4			_io1a, 108, port5,  1,  4
#define _hw_def_pin_pf5			_io1a, 109, port5,  1,  5
#define _hw_def_pin_pf6			_io1a, 110, port5,  1,  6
#define _hw_def_pin_pf7			_io1a, 111, port5,  1,  7
#define _hw_def_pin_pf8			_io1a, 111, port5,  1,  8
#define _hw_def_pin_pf9			_io1a, 111, port5,  1,  9
#define _hw_def_pin_pf10		_io1a, 111, port5,  1, 10
#define _hw_def_pin_pf11		_io1a, 111, port5,  1, 11
#define _hw_def_pin_pf12		_io1a, 111, port5,  1, 12
#define _hw_def_pin_pf13		_io1a, 111, port5,  1, 13
#define _hw_def_pin_pf14		_io1a, 111, port5,  1, 14
#define _hw_def_pin_pf15		_io1a, 111, port5,  1, 15
#define _hw_def_portf			_io1a, 112, port5, 16,  0

#define _hw_def_pin_pg0			_io1a, 104, port6,  1,  0
#define _hw_def_pin_pg1			_io1a, 105, port6,  1,  1
#define _hw_def_pin_pg2			_io1a, 106, port6,  1,  2
#define _hw_def_pin_pg3			_io1a, 107, port6,  1,  3
#define _hw_def_pin_pg4			_io1a, 108, port6,  1,  4
#define _hw_def_pin_pg5			_io1a, 109, port6,  1,  5
#define _hw_def_pin_pg6			_io1a, 110, port6,  1,  6
#define _hw_def_pin_pg7			_io1a, 111, port6,  1,  7
#define _hw_def_pin_pg8			_io1a, 111, port6,  1,  8
#define _hw_def_pin_pg9			_io1a, 111, port6,  1,  9
#define _hw_def_pin_pg10		_io1a, 111, port6,  1, 10
#define _hw_def_pin_pg11		_io1a, 111, port6,  1, 11
#define _hw_def_pin_pg12		_io1a, 111, port6,  1, 12
#define _hw_def_pin_pg13		_io1a, 111, port6,  1, 13
#define _hw_def_pin_pg14		_io1a, 111, port6,  1, 14
#define _hw_def_pin_pg15		_io1a, 111, port6,  1, 15
#define _hw_def_portg			_io1a, 112, port6, 16,  0

/* #if defined HW_DEVICE_PACKAGE_LQFP64 */
/* # */
/* #  define _hw_pin_14			, pin_pa0 */
/* #  define _hw_pin_15			, pin_pa1 */
/* #  define _hw_pin_16			, pin_pa2 */
/* #  define _hw_pin_17			, pin_pa3 */
/* #  define _hw_pin_20			, pin_pa4 */
/* #  define _hw_pin_21			, pin_pa5 */
/* #  define _hw_pin_22			, pin_pa6 */
/* #  define _hw_pin_23			, pin_pa7 */
/* #  define _hw_pin_41			, pin_pa8 */
/* #  define _hw_pin_42			, pin_pa9 */
/* #  define _hw_pin_43			, pin_pa10 */
/* #  define _hw_pin_44			, pin_pa11 */
/* #  define _hw_pin_45			, pin_pa12 */
/* #  define _hw_pin_46			, pin_pa13 */
/* #  define _hw_pin_49			, pin_pa14 */
/* #  define _hw_pin_50			, pin_pa15 */
/* # */
/* #endif */


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
  hwa_p16a_t	port5 ;
  hwa_p16a_t	port6 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/rcca_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p16a_2.h"

HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup( rcc );
  _hwa_setup( port0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init( rcc );
  _hwa_init( port0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit( rcc );
  _hwa_commit( port0 );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page stm32f103
 * <br>
 */
