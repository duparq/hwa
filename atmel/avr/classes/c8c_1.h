
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit counter
 */

/**
 * @page atmelavr_c8c Class _c8c: 8-bit counter/timer
 *
 * A class `_c8c` object is an 8-bit counting unit. It has the following @ref
 * using_relatives "relatives":
 *
 *  * one `prescaler` of class @ref atmelavr_psca "_psca"
 *
 *  * two compare units with waveform generators: `compare0` and `compare1`, of
 *    class @ref atmelavr_cmp8a "_cmp8a"
 *
 * @note Currently, this class is not fully implemented. It lacks asynchronous
 * clocking possibilities.
 *
 * The only difference between this class and the `_c8a` class is the different
 * clocking possibilities.
 *
 * It is used in:
 *
 *  * @ref atmegax8 : `counter2`
 */
#define _hw_class__c8c

/**
 * @page atmelavr_c8c
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction retrieves the number of bits of the counting register:
 *
 * @code
 * #if HW_BITS( COUNTER_NAME ) != 8
 * #  error You must choose a 8-bit counter!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__c8c		, _hw_bn_c8c
#define _hw_bn_c8c(o,i,a,...)		8

/**
 * @page atmelavr_c8c
 * @par Interrupts
 *
 * Class `_c8c` objects can trigger the following IRQs:
 *
 *  * `COUNTER_NAME` or `COUNTER_NAME,overflow`: counter overflow
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t 	ccra ;
  hwa_r8_t 	ccrb ;
  hwa_r8_t 	count ;
  hwa_r8_t 	imsk ;
  hwa_r8_t 	ifr ;

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	clock, countmode, top, overflow ;
  } config ;

  /*  Computed logical register values
   */
  struct {
    uint8_t	cs, wgm ;
  } solved ;

} hwa_c8c_t ;

#endif
