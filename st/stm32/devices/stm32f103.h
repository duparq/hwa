
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*  LITERATURE:
 *
 *  * PM0056: Programming Manual
 *  * RM008:  Reference Manual
 *  * Cortex M3 Devices Generic User Guide
 *  * Cortex M3 Technical Reference Manual
 *  * Discovering the STM32 Microcontroller, by Geoffrey Brown
 *  * M3 Guide: The Definitive Guide to the ARM CORTEX-M3, by Joseph Yiu
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
 * @page stm32f103
 * @section stm32f103_interrupts Interrupts
 *
 * The device has a Nested Vectored Interrupt Controller (@ref stm32_nvica "NVIC").
 * 
 * Interrupt name	| Comments
 * :--------------------|------------------------
 * `systick`		| SysTick timer reached 0
 * `systick,alarm`	| SysTick timer reached 0
 * `counter2`	  	| Counter 2 update
 * `counter3`	  	| Counter 3 update
 * `counter4`	  	| Counter 4 update
 *
 */
#define hw_irq_nmi_			_irq, core, x2, ,
#define hw_irq_systick_			_irq, systick, x15, ie, if
#define hw_irq_systick_alarm		_irq, systick, x15, ie, if
#define hw_irq_counter2_		_irq, counter2, 28, ie, if
#define hw_irq_counter3_		_irq, counter3, 29, ie, if
#define hw_irq_counter4_		_irq, counter4, 30, ie, if
/* #define hw_irq_counter5_		_irq, counter5, 50, ie, if */

#define __vector_x2			hw_esr_nmi
#define __vector_x3			hw_esr_hard
#define __vector_x4			hw_esr_memory
#define __vector_x5			hw_esr_bus
#define __vector_x6			hw_esr_usage
#define __vector_x11			hw_esr_swi
#define __vector_x12			hw_esr_debug
#define __vector_x14			hw_esr_pendswi
#define __vector_x15			hw_esr_systick

#define __vector_28			hw_isr_counter2
#define __vector_29			hw_isr_counter3
#define __vector_30			hw_isr_counter4
/* #define hw_isr_50			hw_isr_counter5 */


#include "../classes/nvica_1.h"

#define hw_nvic				_nvica, 101, 0xE000E100


/*******************************************************************************
 *									       *
 *	Clocks								       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_rcc Clocks
 *
 * Low-, medium-, high- and XL-density devices embed a RCC of class @ref
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
 * @note Connectivity line devices embed a RCC of class `_rccb` that is not implemented yet.
 */

#include "../classes/rcca_1.h"

#define hw_rcc				_rcca, 101, 0x40021000

//#define hw_rcc_usart1			_rccp, 1, 0


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_pins Ports and pins
 *
 * STM32 devices have up to 7 GPIO ports each holding 16 GPIO pins:
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
#define hw_port0			_p16a, 108, 0x40010800
#define hw_port0_rcc			_rccen, port0en

#define hw_port1			_p16a, 109, 0x40010C00
#define hw_port2			_p16a, 110, 0x40011000
#define hw_port3			_p16a, 111, 0x40011400
#define hw_port4			_p16a, 112, 0x40011800
/* #define hw_port5			_p16a, 113, 0x40011C00 */
/* #define hw_port6			_p16a, 114, 0x40012000 */

/*	Object registers
 */
#define hw_reg_port0_cken		_xob1, rcc, apb2enr, 1, 2	/* convenient */
#define hw_reg_port1_cken		_xob1, rcc, apb2enr, 1, 3	/* convenient */
#define hw_reg_port2_cken		_xob1, rcc, apb2enr, 1, 4	/* convenient */
#define hw_reg_port3_cken		_xob1, rcc, apb2enr, 1, 5	/* convenient */
#define hw_reg_port4_cken		_xob1, rcc, apb2enr, 1, 6	/* convenient */
/* #define hw_reg_port5_cken		_xob1, rcc, apb2enr, 1, 7	/\* convenient *\/ */
/* #define hw_reg_port6_cken		_xob1, rcc, apb2enr, 1, 8	/\* convenient *\/ */
#define hw_reg_counter2_cken		_xob1, rcc, apb1enr, 1, 0	/* convenient */
#define hw_reg_counter3_cken		_xob1, rcc, apb1enr, 1, 1	/* convenient */
#define hw_reg_counter4_cken		_xob1, rcc, apb1enr, 1, 2	/* convenient */
#define hw_reg_counter5_cken		_xob1, rcc, apb1enr, 1, 3	/* convenient */

/*  Pins				class, id, peripheral, bn, bp
 */
#define hw_pa0				_io1a, 113, port0,  1,  0
#define hw_pa1				_io1a, 114, port0,  1,  1
#define hw_pa2				_io1a, 115, port0,  1,  2
#define hw_pa3				_io1a, 116, port0,  1,  3
#define hw_pa4				_io1a, 117, port0,  1,  4
#define hw_pa5				_io1a, 118, port0,  1,  5
#define hw_pa6				_io1a, 119, port0,  1,  6
#define hw_pa7				_io1a, 120, port0,  1,  7
#define hw_pa8				_io1a, 121, port0,  1,  8
#define hw_pa9				_io1a, 122, port0,  1,  9
#define hw_pa10				_io1a, 123, port0,  1, 10
#define hw_pa11				_io1a, 124, port0,  1, 11
#define hw_pa12				_io1a, 125, port0,  1, 12
#define hw_pa13				_io1a, 126, port0,  1, 13
#define hw_pa14				_io1a, 127, port0,  1, 14
#define hw_pa15				_io1a, 128, port0,  1, 15
#define hw_porta			_io1a, 129, port0, 16,  0

#define hw_pb0				_io1a, 130, port1,  1,  0
#define hw_pb1				_io1a, 131, port1,  1,  1
#define hw_pb2				_io1a, 132, port1,  1,  2
#define hw_pb3				_io1a, 133, port1,  1,  3
#define hw_pb4				_io1a, 134, port1,  1,  4
#define hw_pb5				_io1a, 135, port1,  1,  5
#define hw_pb6				_io1a, 136, port1,  1,  6
#define hw_pb7				_io1a, 137, port1,  1,  7
#define hw_pb8				_io1a, 138, port1,  1,  8
#define hw_pb9				_io1a, 139, port1,  1,  9
#define hw_pb10				_io1a, 140, port1,  1, 10
#define hw_pb11				_io1a, 141, port1,  1, 11
#define hw_pb12				_io1a, 142, port1,  1, 12
#define hw_pb13				_io1a, 143, port1,  1, 13
#define hw_pb14				_io1a, 144, port1,  1, 14
#define hw_pb15				_io1a, 145, port1,  1, 15
#define hw_portb			_io1a, 146, port1, 16,  0

#define hw_pc0				_io1a, 147, port2,  1,  0
#define hw_pc1				_io1a, 148, port2,  1,  1
#define hw_pc2				_io1a, 149, port2,  1,  2
#define hw_pc3				_io1a, 150, port2,  1,  3
#define hw_pc4				_io1a, 151, port2,  1,  4
#define hw_pc5				_io1a, 152, port2,  1,  5
#define hw_pc6				_io1a, 153, port2,  1,  6
#define hw_pc7				_io1a, 154, port2,  1,  7
#define hw_pc8				_io1a, 155, port2,  1,  8
#define hw_pc9				_io1a, 156, port2,  1,  9
#define hw_pc10				_io1a, 157, port2,  1, 10
#define hw_pc11				_io1a, 158, port2,  1, 11
#define hw_pc12				_io1a, 159, port2,  1, 12
#define hw_pc13				_io1a, 160, port2,  1, 13
#define hw_pc14				_io1a, 161, port2,  1, 14
#define hw_pc15				_io1a, 162, port2,  1, 15
#define hw_portc			_io1a, 163, port2, 16,  0

#define hw_pd0				_io1a, 164, port3,  1,  0
#define hw_pd1				_io1a, 165, port3,  1,  1
#define hw_pd2				_io1a, 166, port3,  1,  2
#define hw_pd3				_io1a, 167, port3,  1,  3
#define hw_pd4				_io1a, 168, port3,  1,  4
#define hw_pd5				_io1a, 169, port3,  1,  5
#define hw_pd6				_io1a, 170, port3,  1,  6
#define hw_pd7				_io1a, 171, port3,  1,  7
#define hw_pd8				_io1a, 172, port3,  1,  8
#define hw_pd9				_io1a, 173, port3,  1,  9
#define hw_pd10				_io1a, 174, port3,  1, 10
#define hw_pd11				_io1a, 175, port3,  1, 11
#define hw_pd12				_io1a, 176, port3,  1, 12
#define hw_pd13				_io1a, 177, port3,  1, 13
#define hw_pd14				_io1a, 178, port3,  1, 14
#define hw_pd15				_io1a, 179, port3,  1, 15
#define hw_portd			_io1a, 180, port3, 16,  0

#define hw_pe0				_io1a, 181, port4,  1,  0
#define hw_pe1				_io1a, 182, port4,  1,  1
#define hw_pe2				_io1a, 183, port4,  1,  2
#define hw_pe3				_io1a, 184, port4,  1,  3
#define hw_pe4				_io1a, 185, port4,  1,  4
#define hw_pe5				_io1a, 186, port4,  1,  5
#define hw_pe6				_io1a, 187, port4,  1,  6
#define hw_pe7				_io1a, 188, port4,  1,  7
#define hw_pe8				_io1a, 189, port4,  1,  8
#define hw_pe9				_io1a, 190, port4,  1,  9
#define hw_pe10				_io1a, 191, port4,  1, 10
#define hw_pe11				_io1a, 192, port4,  1, 11
#define hw_pe12				_io1a, 193, port4,  1, 12
#define hw_pe13				_io1a, 194, port4,  1, 13
#define hw_pe14				_io1a, 195, port4,  1, 14
#define hw_pe15				_io1a, 196, port4,  1, 15
#define hw_porte			_io1a, 197, port4, 16,  0

/* #define hw_pf0			_io1a, 200, port5,  1,  0 */
/* #define hw_pf1			_io1a, 201, port5,  1,  1 */
/* #define hw_pf2			_io1a, 202, port5,  1,  2 */
/* #define hw_pf3			_io1a, 203, port5,  1,  3 */
/* #define hw_pf4			_io1a, 204, port5,  1,  4 */
/* #define hw_pf5			_io1a, 205, port5,  1,  5 */
/* #define hw_pf6			_io1a, 206, port5,  1,  6 */
/* #define hw_pf7			_io1a, 207, port5,  1,  7 */
/* #define hw_pf8			_io1a, 208, port5,  1,  8 */
/* #define hw_pf9			_io1a, 209, port5,  1,  9 */
/* #define hw_pf10			_io1a, 210, port5,  1, 10 */
/* #define hw_pf11			_io1a, 211, port5,  1, 11 */
/* #define hw_pf12			_io1a, 212, port5,  1, 12 */
/* #define hw_pf13			_io1a, 213, port5,  1, 13 */
/* #define hw_pf14			_io1a, 214, port5,  1, 14 */
/* #define hw_pf15			_io1a, 215, port5,  1, 15 */
/* #define hw_portf		_io1a, 216, port5, 16,  0 */

/* #define hw_pg0			_io1a, 217, port6,  1,  0 */
/* #define hw_pg1			_io1a, 218, port6,  1,  1 */
/* #define hw_pg2			_io1a, 219, port6,  1,  2 */
/* #define hw_pg3			_io1a, 220, port6,  1,  3 */
/* #define hw_pg4			_io1a, 221, port6,  1,  4 */
/* #define hw_pg5			_io1a, 222, port6,  1,  5 */
/* #define hw_pg6			_io1a, 223, port6,  1,  6 */
/* #define hw_pg7			_io1a, 224, port6,  1,  7 */
/* #define hw_pg8			_io1a, 225, port6,  1,  8 */
/* #define hw_pg9			_io1a, 226, port6,  1,  9 */
/* #define hw_pg10			_io1a, 227, port6,  1, 10 */
/* #define hw_pg11			_io1a, 228, port6,  1, 11 */
/* #define hw_pg12			_io1a, 229, port6,  1, 12 */
/* #define hw_pg13			_io1a, 230, port6,  1, 13 */
/* #define hw_pg14			_io1a, 231, port6,  1, 14 */
/* #define hw_pg15			_io1a, 232, port6,  1, 15 */
/* #define hw_portg		_io1a, 233, port6, 16,  0 */

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

#include "../classes/afioa_1.h"

#define hw_afio				_afioa, 101, 0x40010000


/*  Pin functions and mappings		STM32F103-x8-xB.pdf, p. 28
 *
 *  The mapping of controller signals to device pins is configured by a 'remap'
 *  value associated to each controller and stored in the AFIO. Each 'remap'
 *  value associates a set of pins to a set of signals for one controller, but
 *  one pin can sometimes be associated to the same signal through different
 *  'remap' values. One pin does not connected to one signal, but one controller
 *  choses a mapping. Then, each pin can be configured to relay the "alternate"
 *  signal or remain a GPIO.
 *
 *  Solution 1: we build a table in the HWA context to record for each signal
 *  the pin it must be associated with. When the "commit" is invoked, a function
 *  checks that the wanted associations can be satisfied. This is the same kind
 *  of solution as for the Atmel AVR8 counters and their compare init outputs.
 *
 *  hw( configure, pa9,  function, (usart1,tx) );  // USART1_REMAP = 0
 *  hw( configure, pa10, function, (usart1,rx) );  // USART1_REMAP = 0
 *  hw( configure, pb6,  function, (usart1,tx) );  // USART1_REMAP = 1
 *  hw( configure, pb7,  function, (usart1,rx) );  // USART1_REMAP = 1
 *
 *  Solution 2: we configure the mapping through the 'configure' action of the
 *  controller.
 *
 *  hw( configure, counter2, 
 *      ...
 *      map_channel1, pa0,	// Remap '00'
 *      map_channel2, pa1,
 *      map_channel3, pa2,
 *      map_channel4, pa3 );
 *
 *  hw( configure, counter2, 
 *      ...
 *      map_channel1, pa15,	// Remap '01'
 *      map_channel2, pb3,
 *      map_channel3, pa2,
 *      map_channel4, pa3 );
 *
 */
//					, df/af, map
//
#define _hw_fn_pa0			(gpio,wkup,(usart2,cts),(adc12,in0),(counter2,channel1),etr)
#define _hw_fn_pa0_gpio			, df
#define _hw_fn_pa0_wkup			, af
#define _hw_fn_pa0_usart2_cts		, af 
#define _hw_fn_pa0_adc12_in0		, af 
#define _hw_fn_pa0_counter2_channel1	, af 
#define _hw_fn_pa0_etr			, af 

#define _hw_fn_pa9			(gpio,(usart1,tx),(counter1,channel2))
#define _hw_fn_pa9_gpio			, df 
#define _hw_fn_pa9_usart1_tx		, af
#define _hw_fn_pa9_counter1_channel2	, af

#define _hw_fn_pa10			(gpio,(usart1,rx),(counter1,channel3))
#define _hw_fn_pa10_gpio		, df
#define _hw_fn_pa10_usart1_rx		, af
#define _hw_fn_pa10_counter1_channel3	, af


/*******************************************************************************
 *									       *
 *	SysTick								       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_systick SysTick timer
 * The Cortex-M3 processor has a @ref stm32_stka "24 bit system timer".
 * 
 */

#include "../classes/stka_1.h"

#define hw_systick			_stka, 101, 0xE000E010
#define hw_systick_irq			_irq, systick, x15, ie, if


/*******************************************************************************
 *									       *
 *	General-purpose counter-timers					       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_gpc General-purpose counter-timers
 *
 * The STM32F103 devices have 3 general-purpose counter-timers: @ref stm32_c16a
 * "counter2..4".
 */

#include "../classes/c16a_1.h"

#define hw_counter2			_c16a, 102, 0x40000000
#define hw_counter2_irq			_irq, counter2, 28, ie, if
#define hw_counter2_nvic		_nvirq, 28
#define hw_counter2_rcc			_rccen, tim2en

#define hw_counter3			_c16a, 103, 0x40000400
#define hw_counter3_irq			_irq, counter3, 29, ie, if
#define hw_counter3_nvic		_nvirq, 29
#define hw_counter3_rcc			_rccen, tim3en

#define hw_counter4			_c16a, 104, 0x40000800
#define hw_counter4_irq			_irq, counter4, 30, ie, if
#define hw_counter4_nvic		_nvirq, 30
#define hw_counter4_rcc			_rccen, tim4en


/*******************************************************************************
 *									       *
 *	Universal synchronous asynchronous receiver transmitter (USART)	       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_usarts USART
 *
 * The STM32F103 devices have 5 USARTs:
 *  * @ref stm32_usarta "_usarta": usart1, usart2, usart3
 *  * @ref stm32_usarta "_usartb": usart4, usart5
 */

#include "../classes/usarta_1.h"

#define hw_usart1		_usarta, 104, 0x40013800
#define hw_usart1_irq		_irq, usart1, 37, ie, if
#define hw_usart1_nvic		_nvirq, 37
#define hw_usart1_rcc		_rccen, usart1en

#define hw_usart2		_usarta, 105, 0x40004400
#define hw_usart3		_usarta, 106, 0x40004800
#define hw_uart4		_uarta,  107, 0x40004C00
#define hw_uart5		_uarta,  108, 0x40005000


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin_from_reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_rcca_t	rcc ;
  hwa_nvica_t	nvic ;

  hwa_afioa_t	afio ;
  hwa_p16a_t	port0 ;
  hwa_p16a_t	port1 ;
  hwa_p16a_t	port2 ;
  hwa_p16a_t	port3 ;
  hwa_p16a_t	port4 ;
  /* hwa_p16a_t	port5 ; */
  /* hwa_p16a_t	port6 ; */
  hwa_stka_t	systick ;

  hwa_c16a_t	counter2 ;
  hwa_c16a_t	counter3 ;
  hwa_c16a_t	counter4 ;
  /* hwa_c16a_t	counter5 ; */
  hwa_usarta_t	usart1 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/rcca_2.h"
#include "../classes/afioa_2.h"
#include "../classes/nvica_2.h"
#include "../classes/io1a_2.h"
#include "../classes/p16a_2.h"
#include "../classes/stka_2.h"
#include "../classes/c16a_2.h"
#include "../classes/usarta_2.h"

HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_o( rcc );
  _hwa_setup_o( nvic );
  _hwa_setup_o( afio );
  _hwa_setup_o( port0 );
  _hwa_setup_o( port1 );
  _hwa_setup_o( port2 );
  _hwa_setup_o( port3 );
  _hwa_setup_o( port4 );
  /* _hwa_setup_o( port5 ); */
  /* _hwa_setup_o( port6 ); */
  _hwa_setup_o( systick );
  _hwa_setup_o( counter2 );
  _hwa_setup_o( counter3 );
  _hwa_setup_o( counter4 );
  /* _hwa_setup_o( counter5 ); */
  _hwa_setup_o( usart1 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_o( rcc );
  _hwa_init_o( nvic );
  _hwa_init_o( afio );
  _hwa_init_o( port0 );
  _hwa_init_o( port1 );
  _hwa_init_o( port2 );
  _hwa_init_o( port3 );
  _hwa_init_o( port4 );
  /* _hwa_init_o( port5 ); */
  /* _hwa_init_o( port6 ); */
  _hwa_init_o( systick );
  _hwa_init_o( counter2 );
  _hwa_init_o( counter3 );
  _hwa_init_o( counter4 );
  /* _hwa_init_o( counter5 ); */
  _hwa_init_o( usart1 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit_o( rcc );
  _hwa_commit_o( nvic );
  _hwa_commit_o( afio );
  _hwa_commit_o( port0 );
  _hwa_commit_o( port1 );
  _hwa_commit_o( port2 );
  _hwa_commit_o( port3 );
  _hwa_commit_o( port4 );
  /* _hwa_commit_o( port5 ); */
  /* _hwa_commit_o( port6 ); */
  _hwa_commit_o( systick );
  _hwa_commit_o( counter2 );
  _hwa_commit_o( counter3 );
  _hwa_commit_o( counter4 );
  /* _hwa_commit_o( counter5 ); */
  _hwa_commit_o( usart1 );
}

#endif /* !defined __ASSEMBLER__ */
