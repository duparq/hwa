
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_c8a Class _c8a: 8-bit counter/timer
 *
 * A class `_c8a` object is an 8-bit counter/timer with two compare units and
 * waveform generators.
 *
 * It is used in:
 * * ATtinyX4 counter0
 * * ATtinyX5 counter0
 * * ATmegaX8 counter0
 */
#define _hw_class__c8a

/*
 *	Note: ATtinyX5 has a different cabling of masks and flags.
 */

/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_macros Instructions that do not produce code
 * @subsection atmelavr_c8a_sub Name of a compare unit
 * 
 * The compare units (class @ref atmelavr_ocua "_ocua") are named `compare0` and
 * `compare1`, corresponding to `OCRxA` and `OCRxB` registers in Atmel
 * terminology.
 *
 * The `hw_sub(...)` instruction retrieves the compare unit name of a counter:
 *
 * @code
 * #if hw_id( hw_sub(hw_counter0, compare0) ) == 0
 * #  error This counter has no compare0 unit !
 * #endif
 * @endcode
 */

/**
 * @page atmelavr_c8a
 * @subsection atmelavr_c8a_bn Number of bits of the counting register
 *
 * The `hw_bn(...)` instruction retrieves the number of bits of a counter:
 *
 * @code
 * #if hw_bn( COUNTER ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__c8a		, _hw_bn_c8a
#define _hw_bn_c8a(p,i,a,...)		HW_TX(8, __VA_ARGS__)


#if !defined __ASSEMBLER__


typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  hwa_r8_t	compare0 ;
  hwa_r8_t	compare1 ;
#ifndef HW_DEVICE_ATTINYX5
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;
#endif

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, countmode, top, overflow ;
    struct {
      uint8_t	update, output ;
    } compare0 ;
    struct {
      uint8_t	update, output ;
    } compare1 ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	cs, wgm, coma, comb ;
  } solved ;

} hwa_c8a_t ;

#endif
