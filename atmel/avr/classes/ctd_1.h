
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 16-bit counter
 */

/**
 * @page atmelavr_ctd Class _ctd: 16-bit counter/timer
 *
 * A class `_ctd` object is a 16-bit counting unit that has 4 relative objects:
 *  * one prescaler of class @ref atmelavr_psa "_psa": `(counter0,prescaler)`
 *  * two compare units with waveform generators, of class @ref atmelavr_occ "_occ":
 *    `(counter0,compare0)` and `(counter0,compare1)`
 *  * one capture unit of class @ref atmelavr_ica "_ica": `(counter0,capture0)`
 *
 * It is used by:
 *
 *  * @ref attinyx4 : `counter1`
 *  * @ref atmegax8 : `counter1`
 */
#define hw_class__ctd


/**
 * @page atmelavr_ctd
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( counter0 ) != 16
 * #  error You must choose a 16-bit counter!
 * #endif
 * @endcode
 */
#define HW_BITS__ctd			, _hw_bits_ctd
#define _hw_bits_ctd(...)		16

/**
 * @page atmelavr_ctd
 * @par Interrupts
 *
 * Class `_ctd` objects can trigger the following IRQs:
 *
 *  * `counter0` or `counter0,overflow`: counter overflow
 */


#if 0
/*  Class registers
 */
#define hw__ctd_compare0_mode		_cb1, ccra, 2, 6	/* COMA */
#define hw__ctd_compare1_mode		_cb1, ccra, 2, 4	/* COMB */

#define hw__ctd_icnc			_cb1, ccrb, 1, 7
#define hw__ctd_ices			_cb1, ccrb, 1, 6
#define hw__ctd_cs			_cb1, ccrb, 3, 0
#define hw__ctd_wgm			_cb2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define hw__ctd_foca			_cb1, ccrc, 1, 7
#define hw__ctd_focb			_cb1, ccrc, 1, 6

#define hw__ctd_ieic			_cb1, imsk, 1, 5
#define hw__ctd_iecm1			_cb1, imsk, 1, 2
#define hw__ctd_iecm0			_cb1, imsk, 1, 1
#define hw__ctd_ieov			_cb1, imsk, 1, 0

#define hw__ctd_ific			_cb1, ifr, 1, 5
#define hw__ctd_ifcm1			_cb1, ifr, 1, 2
#define hw__ctd_ifcm0			_cb1, ifr, 1, 1
#define hw__ctd_ifov			_cb1, ifr, 1, 0
#endif


#ifndef __ASSEMBLER__

typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	ccrc ;
  hwa_r16_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock,direction, top, overflow ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_ctd_t ;

#endif
