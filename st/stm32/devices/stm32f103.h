
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


#include "../hwa_1.h"


/**
 * @ingroup stm32_devices
 * @defgroup stm32f103 STM32F103
 *
 * Content of the device:
 *
 *  * Clocks
 *    * @ref stm32_hsia "hsi": 8 MHz internal RC oscillator.
 *    * @ref stm32_hsea "hse": crystal external oscillator.
 *    * @ref stm32_plla "pll": PLL multiplying HSI or HSE clock.
 *    * @ref stm32_sclka "sysclk": connected to HSI, PLL, or HSE, clocks
 *      * @ref stm32_ahba "ahb": clocks
 *    	* sdio
 *    	* fsmc
 *    	* core
 *    	* memory
 *    	* dma
 *    	* Cortex system timer
 *    	* FCLK Cortex free running clock
 *    	* @ref stm32_apba "apb1" (low-speed): clocks (36 MHz max.)
 *    	  * counter2..7, counter12..14
 *    	  * APB1 peripherals
 *    	* @ref stm32_apba "apb2" (high-speed): clocks
 *    	  * counter1, counter8..11
 *    	  * adc and other APB2 peripherals
 *      * i2s2
 *      * i2s3
 *
 *  * Nested Vectored Interrupt Controller
 *    * @ref stm32_nvica "nvic"
 *
 *  * System Tick timer
 *    * @ref stm32_stka "systick"
 *
 *  * I/Os
 *    * @ref stm32_gpa "porta": @ref stm32_ioa "(porta,0..15)"
 *    * @ref stm32_gpa "portb": @ref stm32_ioa "(portb,0..15)"
 *    * @ref stm32_gpa "portc": @ref stm32_ioa "(portc,0..15)"
 *    * @ref stm32_gpa "portd": @ref stm32_ioa "(portd,0..15)"
 *    * @ref stm32_gpa "porte": @ref stm32_ioa "(porte,0..15)"
 *
 *  * Analog-to-digital converter
 *    * @ref stm32_ada "adc1"
 *    * @ref stm32_ada "adc2"
 *
 *  * Advanced-control counter-timer
 *    * counter1
 *
 *  * General-purpose counter-timers
 *    * @ref stm32_cta "counter2"
 *    * @ref stm32_cta "counter3"
 *    * @ref stm32_cta "counter4"
 *
 *  * Universal synchronous asynchronous receiver transmitter (USART)
 *    * @ref stm32_usarta "usart1"
 *    * @ref stm32_usarta "usart2"
 *    * @ref stm32_usarta "usart3"
 *    * uart4
 *    * uart5
 */

/**
 * @name Name
 * Name
 * @{
 */

/**
 *  Device family
 */
#define HW_DEVICE_STM32F103

/**
 *  Frequency of the high-speed internal clock
 */
#define HW_DEVICE_HSIHZ			8*1000000

/**
 *  Frequency of the low-speed internal clock
 */
#define HW_DEVICE_LSIHZ			40*1000

/** @} */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/

#define _hw_isr_nmi			,   x2
#define _hw_isr_systick			,  x15
#define _hw_isr_systick_alarm		,  x15
#define _hw_isr_counter2		,   28
#define _hw_isr_counter3		,   29
#define _hw_isr_counter4		,   30

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

#define hw_nmi_irq			_irq,  x2, core,       ,
#define hw_systick_irq			_irq, x15, systick,  ie, if
#define hw_systick_irq_alarm		_irq, x15, systick,  ie, if
#define hw_counter2_irq			_irq,  28, counter2, uie, uif
#define hw_counter2_channel3_irq	_irq,    , counter2, cc3ie, cc3if
#define hw_counter3_irq			_irq,  29, counter3, ie, if
#define hw_counter4_irq			_irq,  30, counter4, ie, if


#include "../classes/nvica_1.h"

/*	Object				class, address
 */
#define hw_nvic				_nvica, 0xE000E100


/*******************************************************************************
 *									       *
 *	Clocks								       *
 *									       *
 *******************************************************************************/

#include "../classes/rcca_1.h"

/*	Object				class, address
 */
#define hw_rcc				_rcca, 0x40021000


/*******************************************************************************
 *									       *
 *	SysTick								       *
 *									       *
 *******************************************************************************/

#include "../classes/stka_1.h"

/*	Object				class, address
 */
#define hw_systick			_stka, 0xE000E010


/*******************************************************************************
 *									       *
 *	I/Os								       *
 *									       *
 *******************************************************************************/

#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"
#include "../classes/afioa_1.h"

/*	Objects				class, address
 */
#define hw_afio				_afioa, 0x40010000
#define hw_afio_cken			_xb1, rcc, apb2enr, 1,  0	/* convenient */

#define hw_porta			_gpa, 0x40010800
#define hw_porta_rcc			_rccen, portaen

#define hw_portb			_gpa, 0x40010C00
#define hw_portc			_gpa, 0x40011000
#define hw_portd			_gpa, 0x40011400
#define hw_porte			_gpa, 0x40011800
#define hw_portf			_gpa, 0x40011C00
#define hw_portg			_gpa, 0x40012000

/*	Object registers
 */
#define hw_porta_cken			_xb1, rcc, apb2enr, 1, 2	/* convenient */
#define hw_portb_cken			_xb1, rcc, apb2enr, 1, 3	/* convenient */
#define hw_portc_cken			_xb1, rcc, apb2enr, 1, 4	/* convenient */
#define hw_portd_cken			_xb1, rcc, apb2enr, 1, 5	/* convenient */
#define hw_porte_cken			_xb1, rcc, apb2enr, 1, 6	/* convenient */
#define hw_portf_cken			_xb1, rcc, apb2enr, 1, 7	/* convenient */
#define hw_portg_cken			_xb1, rcc, apb2enr, 1, 8	/* convenient */

#define hw_counter2_cken		_xb1, rcc, apb1enr, 1, 0	/* convenient */
#define hw_counter3_cken		_xb1, rcc, apb1enr, 1, 1	/* convenient */
#define hw_counter4_cken		_xb1, rcc, apb1enr, 1, 2	/* convenient */
#define hw_counter5_cken		_xb1, rcc, apb1enr, 1, 3	/* convenient */


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
#define _hw_af_porta_1_0		(gpio,wkup,(usart2,cts),(adc12,in0),(counter2,channel1),(counter2,etr))
#define _hw_af_porta_1_1		(gpio,(usart2,rts),(adc12,in1),(counter2,channel2))

#define _hw_af_porta_1_2		(gpio,(usart2,tx),(adc12,in2),(counter2,channel3))
#define _hw_af_porta_1_2_usart2_tx
#define _hw_af_porta_1_2_adc12_in2
#define _hw_af_porta_1_2_counter2_channel3

#define _hw_af_porta_1_3		(gpio,(usart2,rx),(adc12,in3),(counter2,channel4))
#define _hw_af_porta_1_4		(gpio,(spi1,nss),(usart2,ck),(adc12,in4))
#define _hw_af_porta_1_5		(gpio,(spi1,sck),(adc12,in5))
#define _hw_af_porta_1_6		(gpio,(spi1,miso),(adc12,in6),(counter3,channel1),(counter1,bkin))
#define _hw_af_porta_1_7		(gpio,(spi1,mosi),(adc12,in7),(counter3,channel2),(counter1,ch1n))
#define _hw_af_porta_1_9		(gpio,(usart1,tx),(counter1,channel2))
#define _hw_af_porta_1_10		(gpio,(usart1,rx),(counter1,channel3))

#define _hw_af_portb_1_0		(gpio,(adc12,in8),(counter3,channel3),(counter1,ch2n))
#define _hw_af_portb_1_1		(gpio,(adc12,in9),(counter3,channel4),(counter1,ch3n))
#define _hw_af_portb_1_10		(gpio,(i2c2,scl),(usart3,tx),(counter2,channel3))

#define _hw_af_portc_1_4		(gpio,(adc12,in14))
#define _hw_af_portc_1_5		(gpio,(adc12,in15))
#define _hw_af_portc_1_13		(gpio,(tamper_rtc))
#define _hw_af_portc_1_14		(gpio,(osc32_in))
#define _hw_af_portc_1_15		(gpio,(osc32_out))

#define _hw_af_portd_1_0		(gpio,osc_in)
#define _hw_af_portd_1_1		(gpio,osc_out)

#define _hw_af_porte_1_2		(traceck)
#define _hw_af_porte_1_3		(traced0)
#define _hw_af_porte_1_4		(traced1)
#define _hw_af_porte_1_5		(traced2)
#define _hw_af_porte_1_6		(traced3)
#define _hw_af_porte_1_7		((counter1,etr))
#define _hw_af_porte_1_8		((counter1,ch1n))
#define _hw_af_porte_1_9		((counter1,ch1))
#define _hw_af_porte_1_10		((counter1,ch2n))


/*******************************************************************************
 *									       *
 *	Analog-to-digital converters					       *
 *									       *
 *******************************************************************************/

#include "../classes/ada_1.h"

#define hw_adc1				_ada, 0x40012400
#define hw_adc2				_ada, 0x40012800


/*******************************************************************************
 *									       *
 *	Counter-timers							       *
 *									       *
 *******************************************************************************/

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

#define hw_counter2_remap		_xb1, afio, mapr, 2,  8
#define hw_counter3_remap		_xb1, afio, mapr, 2, 10
#define hw_counter4_remap		_xb1, afio, mapr, 1, 12


/*******************************************************************************
 *									       *
 *	Universal synchronous asynchronous receiver transmitter (USART)	       *
 *									       *
 *******************************************************************************/

#include "../classes/usarta_1.h"

/*	Object				class, address
 */
#define hw_usart1			_usarta, 0x40013800

#define hw_usart1_nvic			_nvirq, 37
#define hw_usart1_rcc			_rccen, usart1en

#define hw_usart2			_usarta, 0x40004400
#define hw_usart3			_usarta, 0x40004800
/* #define hw_uart4			_uarta,	 0x40004C00 */
/* #define hw_uart5			_uarta,	 0x40005000 */


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
  hwa_gpa_t	porta ;
  hwa_gpa_t	portb ;
  hwa_gpa_t	portc ;
  hwa_gpa_t	portd ;
  hwa_gpa_t	porte ;
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
  _hwa_setup_o( porta );
  _hwa_setup_o( portb );
  _hwa_setup_o( portc );
  _hwa_setup_o( portd );
  _hwa_setup_o( porte );
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
  _hwa_init_o( porta );
  _hwa_init_o( portb );
  _hwa_init_o( portc );
  _hwa_init_o( portd );
  _hwa_init_o( porte );
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
  _hwa_commit_o( porta );
  _hwa_commit_o( portb );
  _hwa_commit_o( portc );
  _hwa_commit_o( portd );
  _hwa_commit_o( porte );
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
