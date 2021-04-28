
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief AFIO for low-, medium- high- and XL-density devices
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_afioa Class _afioa: AFIO for low-, medium- high- and XL-density devices
 *
 */
#define hw_class__afioa

/*  Hardware registers							// Reset value
 */
/* #define hw__afioa_evcr			_r32, 0x00, 0x0000001F, 0	// 0 */
#define hw__afioa_mapr			_r32, 0x04, 0x071FFFFF, 0	// 0
/* #define hw__afioa_exticr1			_r32, 0x08, 0x0000FFFF, 0	// 0 */
/* #define hw__afioa_exticr2			_r32, 0x0C, 0x000003FF, 0	// 0 */
/* #define hw__afioa_exticr3			_r32, 0x10, 0x00007F6F, 0	// 0 */
/* #define hw__afioa_exticr4			_r32, 0x14, 0x000007FF, 0	// 0 */
/* #define hw__afioa_mapr2			_r32, 0x1C, 0x0000FFFF, 0	// 0 */

/*  Logical registers
 */
/* #define hw__afioa_evoe			_cb1, evcr, 1, 7 */
/* #define hw__afioa_port			_cb1, evcr, 3, 4 */
/* #define hw__afioa_pin			_cb1, evcr, 4, 0 */

#define hw__afioa_swj_cfg		_cb1, mapr, 3, 24
#define hw__afioa_adc2_etrgreg_remap	_cb1, mapr, 1, 20
#define hw__afioa_adc2_etrging_remap	_cb1, mapr, 1, 19
#define hw__afioa_adc1_etrgreg_remap	_cb1, mapr, 1, 18
#define hw__afioa_adc1_etrging_remap	_cb1, mapr, 1, 17
/* To be continued */
//#define hw__afioa_tim2_remap		_cb1, mapr, 2, 8
#define hw__afioa_counter2_remap	_cb1, mapr, 2, 8
//#define hw__afioa_counter2_remap	(tim2_remap)
/* To be continued */
#define hw__afioa_usart1_remap		_cb1, mapr, 1, 2
/* To be continued */


#if !defined __ASSEMBLER__

typedef struct {
  /* hwa_r32_t evcr ; */
  hwa_r32_t mapr ;
  /* hwa_r32_t exticr1 ; */
  /* hwa_r32_t exticr2 ; */
  /* hwa_r32_t exticr3 ; */
  /* hwa_r32_t exticr4 ; */
  /* hwa_r32_t mapr2 ; */
  /* struct { */
  /*   uint32_t usart1_tx, usart1_rx ; */
  /*   uint32_t counter2_channel1 ; */
  /*   uint32_t wkup ; */
  /* } map ; */
} hwa_afioa_t ;


/*  Table of signals mapping for alternate pin functions
 *
 *    Each signal name gets the address of the pin that must be configured for
 *    this alternate function.
 */
typedef struct {
  uint8_t	error ;

  int8_t	counter2_remap ;
  uint32_t	counter2_etr ;
  uint32_t	counter2_channel1 ;
  uint32_t	counter2_channel2 ;
  uint32_t	counter2_channel3 ;
  uint32_t	counter2_channel4 ;
} hwa_map_t ;


#endif
