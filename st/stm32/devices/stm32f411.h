
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32F411
 */

/**
 *  Literature:
 *  * [PM0214: Programming manual STM32F4xxx Cortex-M4](https://www.st.com/content/ccc/resource/technical/document/programming_manual/6c/3a/cb/e7/e4/ea/44/9b/DM00046982.pdf/files/DM00046982.pdf/jcr:content/translations/en.DM00046982.pdf)
 *  * [RM0383: Reference Manual STM32F411xC/E](https://www.st.com/resource/en/reference_manual/DM00119316-.pdf)
 *  * Cortex M3 Devices Generic User Guide
 *  * Cortex M3 Technical Reference Manual
 */

#include "../hwa_1.h"

/**
 * @addtogroup stm32f411
 * @section stm32f411_obj Objects
 *
 *  * Clocking
 *    * @ref stm32_rccb "rcc": reset & clock controller
 *    * @ref stm32_hsia "hsi": internal RC oscillator (`HW_DEVICE_HSIHZ`).
 *    * @ref stm32_hsea "hse": crystal external oscillator.
 *    * @ref stm32_pllb "pll": PLL multiplying HSI or HSE clock.
 *    * @ref stm32_sclka "sysclk": connected to HSI, HSE, or PLL
 *
 *  * Buses
 *    * @ref stm32_ahba "ahb"
 *    * @ref stm32_apba "apb1"
 *    * @ref stm32_apba "apb2"
 *
 *  * Interrupts
 *    * @ref stm32_nvica "nvic": Nested Vectored Interrupt Controller
 *
 *  * System Tick timer
 *    * @ref stm32_stka "systick"
 *
 *  * GPIOs
 *    * @ref stm32_gpb "porta..h": GPIO ports and @ref stm32_iob "pins"
 *
 *  * Counters (Timers)
 *    * @ref stm32_cta "counter3", @ref stm32_cta "counter4"
 *    * @ref stm32_ctb "counter2", @ref stm32_ctb "counter5"
 */

/**
 * @addtogroup stm32f411
 * @{
 * @name Definitions
 * @{
 */

/**
 *  Device family
 */
#define HW_DEVICE_STM32F411

/**
 *  Device family
 */
#define HW_DEVICE_STM32F4

/**
 * Frequency of the high-speed internal clock
 */
#define HW_DEVICE_HSIHZ			16000000

/**
 *  Frequency of the low-speed internal clock
 */
#define HW_DEVICE_LSIHZ			32000

/** @} */
/** @} */


/*******************************************************************************
 *									       *
 *	Exception & interrupt vectors					       *
 *									       *
 *******************************************************************************/

#define _hw_isr_nmi_			_isr, , hw_esr_nmi
#define _hw_isr_hardfault_		_isr, , hw_esr_hardfault
#define _hw_isr_systick_		_isr, , hw_esr_systick
#define _hw_isr_systick_alarm		_isr, , hw_esr_systick

#define _hw_isr_counter2_		_isr, 28, hw_isr_counter2
#define _hw_isr_counter3_		_isr, 29, hw_isr_counter3
#define _hw_isr_counter4_		_isr, 30, hw_isr_counter4
#define _hw_isr_counter5_		_isr, 50, hw_isr_counter5


/*******************************************************************************
 *									       *
 *	Objects								       *
 *									       *
 *	Object				class, address			       *
 *									       *
 *******************************************************************************/

/*	NVIC
 */
#include "../classes/nvica_1.h"

#define hw_nvic				_nvica, 0xE000E100


/*	SysTick
 *
 *	FIXME: stm32f4 systick does not have `skew` or `noref`
 */
#include "../classes/stka_1.h"

#define hw_systick			_stka, 0xE000E010


/*	RCC
 */
#include "../classes/rccb_1.h"

#define hw_rcc				_rccb, 0x40023800


/*	GPIO
 */
#include "../classes/gpb_1.h"

#define hw_porta			_gpb, 0x40020000
#define hw_portb			_gpb, 0x40020400
#define hw_portc			_gpb, 0x40020800
#define hw_portd			_gpb, 0x40020C00
#define hw_porte			_gpb, 0x40021000
#define hw_porth			_gpb, 0x40021C00


/*	AFIO					, AFR
 */
#define _hw_af_porta_1_0		(gpio,(counter2,channel1),(counter2,etr),(counter5,channel1),(usart2,cts),eventout))
#define _hw_af_porta_1_0_counter2_channel1	, 1
#define _hw_af_porta_1_0_counter2_etr		, 1
#define _hw_af_porta_1_0_counter5_channel1	, 2
#define _hw_af_porta_1_0_usart2_cts		, 7
#define _hw_af_porta_1_0_eventout		, 15
#define _hw_af_porta_1_1_usart2_rts		, 7
#define _hw_af_porta_1_2_usart2_tx		, 7

#define _hw_af_porta_1_3		(gpio,(counter2,channel4),(counter5,channel4),(counter9,channel2),(i2s2,mck),(usart2,rx),eventout))
#define _hw_af_porta_1_3_usart2_rx		, 7
#define _hw_af_porta_1_4_usart2_ck		, 7
#define _hw_af_porta_1_8_usart1_ck		, 7
#define _hw_af_porta_1_9_usart1_tx		, 7
#define _hw_af_porta_1_10_usart1_rx		, 7
#define _hw_af_porta_1_11_usart1_cts		, 7
#define _hw_af_porta_1_11_usart6_tx		, 8
#define _hw_af_porta_1_12_usart1_rts		, 7
#define _hw_af_porta_1_12_usart6_rx		, 8
#define _hw_af_porta_1_15_usart1_tx		, 7

#define _hw_af_portb_1_3_usart1_rx		, 7
#define _hw_af_portb_1_6_usart1_tx		, 7
#define _hw_af_portb_1_7_usart1_rx		, 7

#define _hw_af_portc_1_6_usart6_tx		, 8
#define _hw_af_portc_1_7_usart6_rx		, 8
#define _hw_af_portc_1_8_usart6_ck		, 8

#define _hw_af_portd_1_3_usart2_cts		, 7
#define _hw_af_portd_1_4_usart2_rts		, 7
#define _hw_af_portd_1_5_usart2_tx		, 7
#define _hw_af_portd_1_6_usart2_rx		, 7
#define _hw_af_portd_1_7_usart2_ck		, 7

#define _hw_af_portd_1_13		(gpio,(counter4,channel2),eventout))
#define _hw_af_portd_1_13_counter4_channel2	, 2
#define _hw_af_portd_1_13_eventout		, 15


/*	Counters
 */
#include "../classes/cta_1.h"

#define hw_counter3			_cta, 0x40000400
#define hw_counter4			_cta, 0x40000800

#include "../classes/ctb_1.h"

#define hw_counter2			_ctb, 0x40000000
#define hw_counter5			_ctb, 0x40000C00


/*	USART
 */
#include "../classes/sab_1.h"

#define hw_usart2			_sab, 0x40004400
#define hw_usart1			_sab, 0x40011000
#define hw_usart6			_sab, 0x40011400


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/

#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all hwa(...) instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_nvica_t	nvic ;
  hwa_stka_t	systick ;
  hwa_rccb_t	rcc ;

  hwa_gpb_t	porta ;
  hwa_gpb_t	portb ;
  hwa_gpb_t	portc ;
  hwa_gpb_t	portd ;
  hwa_gpb_t	porte ;
  hwa_gpb_t	porth ;

  hwa_ctb_t	counter2 ;
  hwa_cta_t	counter3 ;
  hwa_cta_t	counter4 ;
  hwa_ctb_t	counter5 ;

  hwa_sab_t	usart1 ;
  hwa_sab_t	usart2 ;
  hwa_sab_t	usart6 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/nvica_2.h"
#include "../classes/stka_2.h"
#include "../classes/rccb_2.h"
#include "../classes/gpb_2.h"
#include "../classes/cta_2.h"
#include "../classes/ctb_2.h"
#include "../classes/sab_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_o( nvic );
  _hwa_setup_o( systick );
  _hwa_setup_o( rcc );
  _hwa_setup_o( porta );
  _hwa_setup_o( portb );
  _hwa_setup_o( portc );
  _hwa_setup_o( portd );
  _hwa_setup_o( porte );
  _hwa_setup_o( porth );
  _hwa_setup_o( counter2 );
  _hwa_setup_o( counter3 );
  _hwa_setup_o( counter4 );
  _hwa_setup_o( counter5 );
  _hwa_setup_o( usart1 );
  _hwa_setup_o( usart2 );
  _hwa_setup_o( usart6 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_o( nvic );
  _hwa_init_o( systick );
  _hwa_init_o( rcc );
  _hwa_init_o( porta );
  _hwa_init_o( portb );
  _hwa_init_o( portc );
  _hwa_init_o( portd );
  _hwa_init_o( porte );
  _hwa_init_o( porth );
  _hwa_init_o( counter2 );
  _hwa_init_o( counter3 );
  _hwa_init_o( counter4 );
  _hwa_init_o( counter5 );
  _hwa_init_o( usart1 );
  _hwa_init_o( usart2 );
  _hwa_init_o( usart6 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit_o( nvic );
  _hwa_commit_o( systick );
  _hwa_commit_o( rcc );
  _hwa_commit_o( porta );
  _hwa_commit_o( portb );
  _hwa_commit_o( portc );
  _hwa_commit_o( portd );
  _hwa_commit_o( porte );
  _hwa_commit_o( porth );
  _hwa_commit_o( counter2 );
  _hwa_commit_o( counter3 );
  _hwa_commit_o( counter4 );
  _hwa_commit_o( counter5 );
  _hwa_commit_o( usart1 );
  _hwa_commit_o( usart2 );
  _hwa_commit_o( usart6 );
}

#endif /* !defined __ASSEMBLER__ */
