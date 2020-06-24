
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit A/D converter
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_adb Class _adb: 10-bit analog to digital converter
 *
 * This class is used by:
 *
 *  * @ref atmegax8 : `adc0`
 *
 * @section atmelavr_adbft Features
 *
 *  * 10-bit resolution, left or right adustement of the result
 *  * 8 multiplexed single-ended input channels (6 available on PDIP packages)
 *  * Temperature sensor input channel
 *  * 0..Vcc input voltage range
 *  * Internal 1,1 V bandgap, AVcc, or external voltage reference
 *  * Single conversion mode, free-running, and 7 auto trigger sources
 *  * 65-260 μs conversion time (3.8-15.4 ksps). A complete normal conversion
 *    takes 13 clock cycles, 13.5 in the auto-trigger mode, and 25 for the
 *    initial conversion.
 */
#define hw_class__adb


#define HW_BITS__adb			, _hw_bnadb
#define _hw_bnadb(o,a,...)		10 HW_EOL(__VA_ARGS__)


/**
 * @addtogroup atmelavr_adb
 * @section atmelavr_adbirq Interrupts
 *
 *  * `(adc0,irq)`: conversion completed
 */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_adb_t ;

#endif
