
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*	Atmel AVR 16-bit timer-counter model 'a'
 *
 *	Used in:	ATtinyX4 counter1
 *			ATmegaX8 counter1 ?
 */


/**
 * @page atmelavr_c16a Class _c16a: 16-bit counter/timer
 *
 * A class `_c16a` object is a 16-bit counter/timer with two compare units and
 * waveform generators and one capture unit.
 */
#define _hw_class__c16a


/**
 * @page atmelavr_c16a
 * @section atmelavr_c16a_macros Instructions that do not produce code
 * @subsection atmelavr_c16a_sub Name of a compare unit
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
 * @page atmelavr_c16a
 * @subsection atmelavr_c16a_bn Number of bits of the counting register
 *
 * The `hw_bn(...)` instruction retrieves the number of bits of a counter:
 *
 * @code
 * #if hw_bn( COUNTER ) != 16
 * #  error You must choose a 16-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__c16a		, _hw_bn_c16a
#define _hw_bn_c16a(p,i,a,...)		HW_TX(16, __VA_ARGS__)


/*  Registers
 */
#define _hw__c16a_compare0_mode		_cb1, ccra, 2, 6	/* COMA */
#define _hw__c16a_compare1_mode		_cb1, ccra, 2, 4	/* COMB */

#define _hw__c16a_icnc			_cb1, ccrb, 1, 7
#define _hw__c16a_ices			_cb1, ccrb, 1, 6
#define _hw__c16a_cs			_cb1, ccrb, 3, 0
#define _hw__c16a_wgm			_cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define _hw__c16a_foca			_cb1, ccrc, 1, 7
#define _hw__c16a_focb			_cb1, ccrc, 1, 6

#define _hw__c16a_icie			_cb1, imsk, 1, 5
#define _hw__c16a_ocieb			_cb1, imsk, 1, 2
#define _hw__c16a_ociea			_cb1, imsk, 1, 1
#define _hw__c16a_oie			_cb1, imsk, 1, 0

#define _hw__c16a_icf			_cb1, ifr, 1, 5
#define _hw__c16a_ocfb			_cb1, ifr, 1, 2
#define _hw__c16a_ocfa			_cb1, ifr, 1, 1
#define _hw__c16a_ov			_cb1, ifr, 1, 0


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	ccrc ;
  hwa_r16_t	count ;
  hwa_r16_t	compare0 ;
  hwa_r16_t	compare1 ;
  hwa_r16_t	capture0 ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

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
    struct {
      uint8_t	input, edge, filter ;
    } capture0 ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	cs, wgm, coma, comb, acic, ices, icnc ;
  } solved ;

} hwa_c16a_t ;

#endif