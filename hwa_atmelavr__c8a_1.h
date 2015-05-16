
/*	Atmel AVR 8-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter0
 *			ATtinyX5 counter0
 *			ATmegaX8 counter0
 *
 *	Note: ATtinyX5 has a different cabling of masks and flags.
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_c8a _c8a
 *
 * A class `_c8a` object is an 8-bit counter/timer with two compare units and
 * waveform generators.
 *
 */
#define _hw_class__c8a


/**
 * @page atmelavr_c8a
 * @par Name of a compare unit
 * 
 * The compare units (class @ref atmelavr_ocua) are named `compare0` and
 * `compare1`, corresponding to `OCRxA` and `OCRxB` registers in Atmel
 * terminology.
 *
 * @code
 * #define COUNTER	hw_counter0
 * #define COMPARE	hw_sub(COUNTER, compare0)
 *
 * #if hw_id(COMPARE)==0
 * #  error This counter has no compare unit!
 * #endif
 * @endcode
 */


/**
 * @page atmelavr_c8a
 * @par Number of bits of the counting register
 *
 * @code
 * #if hw_bn( COUNTER ) != 16
 * #  error You must choose a 16-bit counter!
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
