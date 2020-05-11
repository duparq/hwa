
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
 * @page stm32f103 STM32F103
 */

#include "../hwa_1.h"

/**
 * @page stm32f103
 * @section stm32f103_objects Objects
 */


/**
 * @page stm32f103
 * @subsection stm32f103_interrupts Interrupts
 *
 * The device has a Nested Vectored Interrupt Controller (@ref stm32_nvica "NVIC").
 * 
 * Interrupt name	| Comments
 * :--------------------|------------------------
 * `systick`		| SysTick timer reached 0
 * `systick,alarm`	| SysTick timer reached 0
 * `counter2`		| Counter 2 update
 * `counter3`		| Counter 3 update
 * `counter4`		| Counter 4 update
 *
 */
#define hw_nmi_irq			_irq,  x2, core,     ,
#define hw_systick_irq			_irq, x15, systick,  ie, if
#define hw_systick_irq_alarm		_irq, x15, systick,  ie, if
#define hw_counter2_irq			_irq,  28, counter2, ie, if
#define hw_counter3_irq			_irq,  29, counter3, ie, if
#define hw_counter4_irq			_irq,  30, counter4, ie, if

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
/* #define hw_isr_50				hw_isr_counter5 */


/**
 * @page stm32f103
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
 * `HW_DEVICE_HSIHZ`	    |8*1000000
 * `HW_DEVICE_LSIHZ`	    |40*1000
 */
#define HW_DEVICE_STM32F103
/* #define HW_DEVICE_ARCH		arm */
#define HW_DEVICE_HSIHZ			8*1000000
#define HW_DEVICE_LSIHZ			40*1000





#include "../classes/nvica_1.h"

/*	Object				class, address
 */
#define hw_nvic				_nvica, 0xE000E100


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
 *	* sdio
 *	* fsmc
 *	* core
 *	* memory
 *	* dma
 *	* Cortex system timer
 *	* FCLK Cortex free running clock
 *	* @ref stm32_apba "apb1" (low-speed): clocks (36 MHz max.)
 *	  * counter2..7, counter12..14
 *	  * APB1 peripherals
 *	* @ref stm32_apba "apb2" (high-speed): clocks
 *	  * counter1, counter8..11
 *	  * adc and other APB2 peripherals
 *    * i2s2
 *    * i2s3
 *
 * The RCC is also used transparently by several other objects to enable/disable
 * their clocking for power management purpose.
 *
 * @note Connectivity line devices embed a RCC of class `_rccb` that is not implemented yet.
 */

#include "../classes/rcca_1.h"

/*	Object				class, address
 */
#define hw_rcc				_rcca, 0x40021000

//#define hw_rcc_usart1				_rccp, 0


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
 *  * @ref stm32_gpa "port0" (PORTA): @ref stm32_ioa "pa0..15"
 *  * @ref stm32_gpa "port1" (PORTB): @ref stm32_ioa "pb0..15"
 *  * @ref stm32_gpa "port2" (PORTC): @ref stm32_ioa "pc0..15"
 *  * @ref stm32_gpa "port3" (PORTD): @ref stm32_ioa "pd0..15"
 *  * @ref stm32_gpa "port4" (PORTE): @ref stm32_ioa "pe0..15"
 */

#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"
#include "../classes/afioa_1.h"

/*	Objects				class, address
 */
#define hw_afio				_afioa, 0x40010000
#define hw_afio_cken			_xob1, rcc, apb2enr, 1,  0	/* convenient */

#define hw_port0			_gpa, 0x40010800
#define hw_port0_rcc			_rccen, port0en

#define hw_port1			_gpa, 0x40010C00
#define hw_port2			_gpa, 0x40011000
#define hw_port3			_gpa, 0x40011400
#define hw_port4			_gpa, 0x40011800
/* #define hw_port5				_gpa, 0x40011C00 */
/* #define hw_port6				_gpa, 0x40012000 */

/*	Object registers
 */
#define hw_port0_cken			_xob1, rcc, apb2enr, 1, 2	/* convenient */
#define hw_port1_cken			_xob1, rcc, apb2enr, 1, 3	/* convenient */
#define hw_port2_cken			_xob1, rcc, apb2enr, 1, 4	/* convenient */
#define hw_port3_cken			_xob1, rcc, apb2enr, 1, 5	/* convenient */
#define hw_port4_cken			_xob1, rcc, apb2enr, 1, 6	/* convenient */
/* #define hw_port5_cken			_xob1, rcc, apb2enr, 1, 7	/\* convenient *\/ */
/* #define hw_port6_cken			_xob1, rcc, apb2enr, 1, 8	/\* convenient *\/ */
#define hw_counter2_cken		_xob1, rcc, apb1enr, 1, 0	/* convenient */
#define hw_counter3_cken		_xob1, rcc, apb1enr, 1, 1	/* convenient */
#define hw_counter4_cken		_xob1, rcc, apb1enr, 1, 2	/* convenient */
#define hw_counter5_cken		_xob1, rcc, apb1enr, 1, 3	/* convenient */

/*  Pins				class, peripheral, bn, bp
 */
#define hw_pa0				_ioa, port0,  1,  0
#define hw_pa1				_ioa, port0,  1,  1
#define hw_pa2				_ioa, port0,  1,  2
#define hw_pa3				_ioa, port0,  1,  3
#define hw_pa4				_ioa, port0,  1,  4
#define hw_pa5				_ioa, port0,  1,  5
#define hw_pa6				_ioa, port0,  1,  6
#define hw_pa7				_ioa, port0,  1,  7
#define hw_pa8				_ioa, port0,  1,  8
#define hw_pa9				_ioa, port0,  1,  9
#define hw_pa10				_ioa, port0,  1, 10
#define hw_pa11				_ioa, port0,  1, 11
#define hw_pa12				_ioa, port0,  1, 12
#define hw_pa13				_ioa, port0,  1, 13
#define hw_pa14				_ioa, port0,  1, 14
#define hw_pa15				_ioa, port0,  1, 15

#define hw_porta_0			_ioa, port0,  1,  0
#define hw_porta_1			_ioa, port0,  1,  1
#define hw_porta_2			_ioa, port0,  1,  2
#define hw_porta_3			_ioa, port0,  1,  3
#define hw_porta_4			_ioa, port0,  1,  4
#define hw_porta_5			_ioa, port0,  1,  5
#define hw_porta_6			_ioa, port0,  1,  6
#define hw_porta_7			_ioa, port0,  1,  7
#define hw_porta_8			_ioa, port0,  1,  8
#define hw_porta_9			_ioa, port0,  1,  9
#define hw_porta_10			_ioa, port0,  1, 10
#define hw_porta_11			_ioa, port0,  1, 11
#define hw_porta_12			_ioa, port0,  1, 12
#define hw_porta_13			_ioa, port0,  1, 13
#define hw_porta_14			_ioa, port0,  1, 14
#define hw_porta_15			_ioa, port0,  1, 15

#define hw_porta			_ioa, port0, 16,  0

#define hw_pb0				_ioa, port1,  1,  0
#define hw_pb1				_ioa, port1,  1,  1
#define hw_pb2				_ioa, port1,  1,  2
#define hw_pb3				_ioa, port1,  1,  3
#define hw_pb4				_ioa, port1,  1,  4
#define hw_pb5				_ioa, port1,  1,  5
#define hw_pb6				_ioa, port1,  1,  6
#define hw_pb7				_ioa, port1,  1,  7
#define hw_pb8				_ioa, port1,  1,  8
#define hw_pb9				_ioa, port1,  1,  9
#define hw_pb10				_ioa, port1,  1, 10
#define hw_pb11				_ioa, port1,  1, 11
#define hw_pb12				_ioa, port1,  1, 12
#define hw_pb13				_ioa, port1,  1, 13
#define hw_pb14				_ioa, port1,  1, 14
#define hw_pb15				_ioa, port1,  1, 15
#define hw_portb			_ioa, port1, 16,  0

#define hw_pc0				_ioa, port2,  1,  0
#define hw_pc1				_ioa, port2,  1,  1
#define hw_pc2				_ioa, port2,  1,  2
#define hw_pc3				_ioa, port2,  1,  3
#define hw_pc4				_ioa, port2,  1,  4
#define hw_pc5				_ioa, port2,  1,  5
#define hw_pc6				_ioa, port2,  1,  6
#define hw_pc7				_ioa, port2,  1,  7
#define hw_pc8				_ioa, port2,  1,  8
#define hw_pc9				_ioa, port2,  1,  9
#define hw_pc10				_ioa, port2,  1, 10
#define hw_pc11				_ioa, port2,  1, 11
#define hw_pc12				_ioa, port2,  1, 12
#define hw_pc13				_ioa, port2,  1, 13
#define hw_pc14				_ioa, port2,  1, 14
#define hw_pc15				_ioa, port2,  1, 15
#define hw_portc			_ioa, port2, 16,  0

#define hw_pd0				_ioa, port3,  1,  0
#define hw_pd1				_ioa, port3,  1,  1
#define hw_pd2				_ioa, port3,  1,  2
#define hw_pd3				_ioa, port3,  1,  3
#define hw_pd4				_ioa, port3,  1,  4
#define hw_pd5				_ioa, port3,  1,  5
#define hw_pd6				_ioa, port3,  1,  6
#define hw_pd7				_ioa, port3,  1,  7
#define hw_pd8				_ioa, port3,  1,  8
#define hw_pd9				_ioa, port3,  1,  9
#define hw_pd10				_ioa, port3,  1, 10
#define hw_pd11				_ioa, port3,  1, 11
#define hw_pd12				_ioa, port3,  1, 12
#define hw_pd13				_ioa, port3,  1, 13
#define hw_pd14				_ioa, port3,  1, 14
#define hw_pd15				_ioa, port3,  1, 15
#define hw_portd			_ioa, port3, 16,  0

#define hw_pe0				_ioa, port4,  1,  0
#define hw_pe1				_ioa, port4,  1,  1
#define hw_pe2				_ioa, port4,  1,  2
#define hw_pe3				_ioa, port4,  1,  3
#define hw_pe4				_ioa, port4,  1,  4
#define hw_pe5				_ioa, port4,  1,  5
#define hw_pe6				_ioa, port4,  1,  6
#define hw_pe7				_ioa, port4,  1,  7
#define hw_pe8				_ioa, port4,  1,  8
#define hw_pe9				_ioa, port4,  1,  9
#define hw_pe10				_ioa, port4,  1, 10
#define hw_pe11				_ioa, port4,  1, 11
#define hw_pe12				_ioa, port4,  1, 12
#define hw_pe13				_ioa, port4,  1, 13
#define hw_pe14				_ioa, port4,  1, 14
#define hw_pe15				_ioa, port4,  1, 15
#define hw_porte			_ioa, port4, 16,  0

/* #define hw_pf0				_ioa, port5,  1,  0 */
/* #define hw_pf1				_ioa, port5,  1,  1 */
/* #define hw_pf2				_ioa, port5,  1,  2 */
/* #define hw_pf3				_ioa, port5,  1,  3 */
/* #define hw_pf4				_ioa, port5,  1,  4 */
/* #define hw_pf5				_ioa, port5,  1,  5 */
/* #define hw_pf6				_ioa, port5,  1,  6 */
/* #define hw_pf7				_ioa, port5,  1,  7 */
/* #define hw_pf8				_ioa, port5,  1,  8 */
/* #define hw_pf9				_ioa, port5,  1,  9 */
/* #define hw_pf10				_ioa, port5,  1, 10 */
/* #define hw_pf11				_ioa, port5,  1, 11 */
/* #define hw_pf12				_ioa, port5,  1, 12 */
/* #define hw_pf13				_ioa, port5,  1, 13 */
/* #define hw_pf14				_ioa, port5,  1, 14 */
/* #define hw_pf15				_ioa, port5,  1, 15 */
/* #define hw_portf				_ioa, port5, 16,  0 */

/* #define hw_pg0				_ioa, port6,  1,  0 */
/* #define hw_pg1				_ioa, port6,  1,  1 */
/* #define hw_pg2				_ioa, port6,  1,  2 */
/* #define hw_pg3				_ioa, port6,  1,  3 */
/* #define hw_pg4				_ioa, port6,  1,  4 */
/* #define hw_pg5				_ioa, port6,  1,  5 */
/* #define hw_pg6				_ioa, port6,  1,  6 */
/* #define hw_pg7				_ioa, port6,  1,  7 */
/* #define hw_pg8				_ioa, port6,  1,  8 */
/* #define hw_pg9				_ioa, port6,  1,  9 */
/* #define hw_pg10				_ioa, port6,  1, 10 */
/* #define hw_pg11				_ioa, port6,  1, 11 */
/* #define hw_pg12				_ioa, port6,  1, 12 */
/* #define hw_pg13				_ioa, port6,  1, 13 */
/* #define hw_pg14				_ioa, port6,  1, 14 */
/* #define hw_pg15				_ioa, port6,  1, 15 */
/* #define hw_portg				_ioa, port6, 16,  0 */

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


/*  Pin functions and mappings		STM32F103-x8-xB.pdf, p. 28
 *
 *  Each pin can be configured as a GPIO or as an "alternate" signal attached to
 *  a controller.
 *
 *  Routing of one controller's signal to a pin is controlled by the controller
 *  through various configurations numbered in the 'remap' register. As the same
 *  signal can be routed to the same pin by different configurations, it seems
 *  necessary to gather the configurations of all the pins and decide later of
 *  the 'remap' values.
 *
 *  The gpio/alternate function is set by the CNF bits in the pins' port
 *  registers. When an alternate function is selected, the pin is driven by the
 *  controller it is mapped to.
 *
 *  Solution: for each signal that can be mapped, we record the address of the
 *  pin to attach. The commit procedure browses the attachements and tries to
 *  find valid remap values for the controllers.
 */
#define _hw_af_pa0			(gpio,wkup,(usart2,cts),(adc12,in0),(counter2,channel1),(counter2,etr))
#define _hw_af_pa1			(gpio,(usart2,rts),(adc12,in1),(counter2,channel2))
#define _hw_af_pa2			(gpio,(usart2,tx),(adc12,in2),(counter2,channel3))
#define _hw_af_pa2			(gpio,(usart2,tx),(adc12,in2),(counter2,channel3))
#define _hw_af_pa3			(gpio,(usart2,rx),(adc12,in3),(counter2,channel4))
#define _hw_af_pa4			(gpio,(spi1,nss),(usart2,ck),(adc12,in4))
#define _hw_af_pa5			(gpio,(spi1,sck),(adc12,in5))
#define _hw_af_pa6			(gpio,(spi1,miso),(adc12,in6),(counter3,channel1),(counter1,bkin))
#define _hw_af_pa7			(gpio,(spi1,mosi),(adc12,in7),(counter3,channel2),(counter1,ch1n))
#define _hw_af_pa9			(gpio,(usart1,tx),(counter1,channel2))
#define _hw_af_pa10			(gpio,(usart1,rx),(counter1,channel3))

#define _hw_af_pb0			(gpio,(adc12,in8),(counter3,channel3),(counter1,ch2n))
#define _hw_af_pb1			(gpio,(adc12,in9),(counter3,channel4),(counter1,ch3n))
#define _hw_af_pb10			(gpio,(i2c2,scl),(usart3,tx),(counter2,channel3))

#define _hw_af_pc4			(gpio,(adc12,in14))
#define _hw_af_pc5			(gpio,(adc12,in15))
#define _hw_af_pc13			(gpio,(tamper_rtc))
#define _hw_af_pc14			(gpio,(osc32_in))
#define _hw_af_pc15			(gpio,(osc32_out))

#define _hw_af_pd0			(gpio,osc_in)
#define _hw_af_pd1			(gpio,osc_out)

#define _hw_af_pe2			(traceck)
#define _hw_af_pe3			(traced0)
#define _hw_af_pe4			(traced1)
#define _hw_af_pe5			(traced2)
#define _hw_af_pe6			(traced3)
#define _hw_af_pe7			((counter1,etr))
#define _hw_af_pe8			((counter1,ch1n))
#define _hw_af_pe9			((counter1,ch1))
#define _hw_af_pe10			((counter1,ch2n))


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

/*	Object				class, address
 */
#define hw_systick			_stka, 0xE000E010
//#define hw_systick_irq			_irq, systick, x15, ie, if


/**
 * @page stm32f103
 * @section stm32f103_acc Advanced-control counter-timers
 *
 * STM32F103 devices have 1 advanced-control counter-timers: @ref stm32_cta "counter1".
 *
 * @note This counter is not implemented yet.
 */

/*******************************************************************************
 *									       *
 *	General-purpose counter-timers					       *
 *									       *
 *******************************************************************************/

/**
 * @page stm32f103
 * @section stm32f103_gpc General-purpose counter-timers
 *
 * The STM32F103 devices have 3 general-purpose counter-timers: @ref stm32_cta
 * "counter2..4".
 */

#include "../classes/cta_1.h"
#include "../classes/cca_1.h"

/*	Object				class, address
 */
#define hw_counter2			_cta, 0x40000000
#define hw_counter3			_cta, 0x40000400
#define hw_counter4			_cta, 0x40000800

#define hw_counter2_channel1		_cca, counter2, 1
#define hw_counter2_channel2		_cca, counter2, 2
#define hw_counter2_channel3		_cca, counter2, 3
#define hw_counter2_channel4		_cca, counter2, 4

#define hw_counter3_channel1		_cca, counter3, 1
#define hw_counter3_channel2		_cca, counter3, 2
#define hw_counter3_channel3		_cca, counter3, 3
#define hw_counter3_channel4		_cca, counter3, 4

#define hw_counter4_channel1		_cca, counter4, 1
#define hw_counter4_channel2		_cca, counter4, 2
#define hw_counter4_channel3		_cca, counter4, 3
#define hw_counter4_channel4		_cca, counter4, 4

#define hw_counter2_remap		_xob1, afio, mapr, 2,  8
#define hw_counter3_remap		_xob1, afio, mapr, 2, 10
#define hw_counter4_remap		_xob1, afio, mapr, 1, 12


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

/*	Object				class, address
 */
#define hw_usart1			_usarta, 0x40013800
//#define hw_usart1_irq			_irq, usart1, 37, ie, if
#define hw_usart1_nvic			_nvirq, 37
#define hw_usart1_rcc			_rccen, usart1en

#define hw_usart2			_usarta, 0x40004400
#define hw_usart3			_usarta, 0x40004800
#define hw_uart4			_uarta,	 0x40004C00
#define hw_uart5			_uarta,	 0x40005000


#if !defined __ASSEMBLER__


/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/
  hwa_map_t	map ;

  hwa_rcca_t	rcc ;
  hwa_nvica_t	nvic ;

  hwa_afioa_t	afio ;
  hwa_gpa_t	port0 ;
  hwa_gpa_t	port1 ;
  hwa_gpa_t	port2 ;
  hwa_gpa_t	port3 ;
  hwa_gpa_t	port4 ;
  /* hwa_gpa_t	port5 ; */
  /* hwa_gpa_t	port6 ; */
  hwa_stka_t	systick ;

  hwa_cta_t	counter2 ;
  hwa_cta_t	counter3 ;
  hwa_cta_t	counter4 ;
  /* hwa_cta_t	counter5 ; */
  hwa_usarta_t	usart1 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/rcca_2.h"
#include "../classes/afioa_2.h"
#include "../classes/nvica_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/stka_2.h"
#include "../classes/cta_2.h"
#include "../classes/cca_2.h"
#include "../classes/usarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  /*  Initialize the remaper
   */
  /* hwa->map.error = 0 ; */
  /* hwa->map.counter2_0 = 0 ; */
  /* hwa->map.counter2_1 = 0 ; */
  /* hwa->map.counter2_2 = 0 ; */
  /* hwa->map.counter2_3 = 0 ; */

  /* _hwa_setup_map(hwa); */

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
  /* _hwa_init_map(hwa); */

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
  /* if ( hwa->map.counter2_0 == 1 ) */
  /*   _hwa_write(counter2,remap,0); */
  /* if ( hwa->map.counter2_1 == 1 ) */
  /*   _hwa_write(counter2,remap,1); */
  /* if ( hwa->map.counter2_2 == 1 ) */
  /*   _hwa_write(counter2,remap,2); */
  /* if ( hwa->map.counter2_3 == 1 ) */
  /*   _hwa_write(counter2,remap,3); */

  /* _hwa_commit_map(hwa); */

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
