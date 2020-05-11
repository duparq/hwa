
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit A/D converter
 */

/**
 * @page atmelavr_adc Class _adc: 10-bit analog to digital converter
 *
 * A class `_adc` object is an analog to digital converter with the following
 * features:
 *
 * * 10-bit resolution, left or right adustement of the result
 * * 4 multilexed single-ended input channels
 * * 2 differential input channels with selectable gain, unipolar or bipolar
 *     conversion
 * * Temperature sensor input channel
 * * 0..Vcc input voltage range
 * * Internal 1,1 V / 2.56 V bandgap, AVcc, or external voltage reference
 * * Single conversion mode, free-running, and 6 auto trigger sources
 * * 65-260 μs Conversion Time (3.8-15.4 ksps). A complete normal conversion
 *   takes 13 clock cycles, 13.5 in the auto-trigger mode, and 25 for the
 *   initial conversion.
 *
 * __Note__ The ADC and the analog comparator share the output of the analog
 * multiplexer. When the ADC is enabled, the analog comparator can not use the
 * analog multiplexer output. Thus, HWA implements these peripherals as if each
 * has his own analog multiplexer.
 *
 * It is used in:
 *
 * * @ref attinyx5 : `adc0`
 */
#define hw_class__adc


/**
 * @page atmelavr_adc
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS(...)` instruction returns the number of bits of the ADC:
 *
 * @code
 * #if HW_BITS( adc0 ) < 10
 * #  error At least 10-bit ADC is required!
 * #endif
 * @endcode
 */
#define HW_BITS__adc		, _hw_bn_adc
#define _hw_bn_adc(o,a,...)		10


/**
 * @page atmelavr_adc
 * @par Interrupts
 *
 * Class `_adc` objects can trigger the following IRQs:
 *
 *  * `adc0`: conversion completed
 */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_adc_t ;

#endif
