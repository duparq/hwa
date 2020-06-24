
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
 * @defgroup atmelavr_ada Class _ada: 10-bit analog to digital converter
 *
 * This class is used by:
 *
 *  * @ref attinyx4 : `adc0`
 *
 * @section atmelavr_adaft Features
 *
 *  * 10-bit resolution, left or right adustement of the result
 *  * 8 multilexed single-ended input channels
 *  * 12 differential input channels with selectable gain, unipolar or bipolar
 *  	conversion
 *  * Temperature sensor input channel
 *  * 0..Vcc input voltage range
 *  * Internal 1,1 V bandgap, AVcc, or external voltage reference
 *  * Single conversion mode, free-running, and 7 auto trigger sources
 *  * 65-260 μs conversion time (3.8-15.4 ksps). A complete normal conversion
 *    takes 13 clock cycles, 13.5 in the auto-trigger mode, and 25 for the
 *    initial conversion.
 *
 * @section atmelavr_adairq Interrupts
 *
 *  * `(adc0,irq)`: conversion completed
 */
#define hw_class__ada

#define HW_BITS__ada		, _hw_bnada
#define _hw_bnada(p,a,_)	10


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_ada_t ;

#endif
