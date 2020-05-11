
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_ctc Class _ctc: 8-bit counter/timer
 *
 * A class `_ctc` object is an 8-bit counting unit. It has the following
 * relatives:
 *
 *  * one `prescaler` of class @ref atmelavr_psa "_psa"
 *
 *  * two compare units with waveform generators: `compare0` and `compare1`, of
 *    class @ref atmelavr_oca "_oca"
 *
 * __Note__ Currently, this class is not fully implemented. It lacks asynchronous
 * clocking possibilities.
 *
 * The only difference between this class and the `_cta` class is the different
 * clocking possibilities.
 *
 * It is used in:
 *
 *  * @ref atmegax8 : `counter2`
 */
#define hw_class__ctc

/**
 * @page atmelavr_ctc
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( counter0 ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define HW_BITS__ctc		, _hw_bn_ctc
#define _hw_bn_ctc(o,a,...)		8

/**
 * @page atmelavr_ctc
 * @par Interrupts
 *
 * Class `_ctc` objects can trigger the following IRQs:
 *
 *  * `counter0` or `counter0,overflow`: counter overflow
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	ccra ;
  hwa_r8_t	ccrb ;
  hwa_r8_t	count ;
  hwa_r8_t	imsk ;
  hwa_r8_t	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, direction, top, overflow ;
  } config ;

  /*  Computed logical register values
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_ctc_t ;

#endif
