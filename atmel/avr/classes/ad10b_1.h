
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief A/D converter
 */

/**
 * @page atmelavr_ad10b Class _ad10b: 10-bit analog to digital converter
 *
 * A class `_ad10b` object is an analog to digital converter with the following
 * features:
 *
 * * 10-bit resolution, left or right adustement of the result
 * * 8 multilexed single-ended input channels (6 available on PDIP packages)
 * * Temperature sensor input channel
 * * 0..Vcc input voltage range
 * * Internal 1,1 V bandgap, AVcc, or external voltage reference
 * * Single conversion mode, free-running, and 7 auto trigger sources
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
 *  * @ref atmegax8 : `adc0`
 */
#define hw_class__ad10b


/**
 * @page atmelavr_ad10b
 * @par Instructions that do not produce C code
 *
 * The `HW_BITS()` instruction returns the number of bits of an ADC:
 *
 * @code
 * #if HW_BITS( adc0 ) < 10
 * #  error At least 10-bit ADC is required!
 * #endif
 * @endcode
 */
#define HW_BITS__ad10b		, _hw_bn_ad10b
#define _hw_bn_ad10b(o,i,a,...)		10 HW_EOL(__VA_ARGS__)


/**
 * @page atmelavr_ad10b
 * @par Interrupts
 *
 * Class `_ad10b` objects can trigger the following IRQs:
 *
 *  * `adc0`: conversion completed
 */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_ad10b_t ;

#endif
