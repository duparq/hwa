
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit A/D converter
 */

/**
 * @page atmelavr_ad10c Class _ad10c: 10-bit analog to digital converter
 *
 * A class `_ad10c` object is an analog to digital converter with the following
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
 * __Note__: the ADC and the analog comparator share the output of the analog
 * multiplexer. When the ADC is enabled, the analog comparator can not use the
 * analog multiplexer output. Thus, HWA implements these peripherals as if each
 * has his own analog multiplexer.
 *
 * It is used in:
 *
 * * @ref attinyx5 : `hw_adc0`
 */
#define _hw_class__ad10c


/**
 * @page atmelavr_ad10c
 * @par Instructions that do not produce C code
 *
 * The `hw_bn(...)` instruction retrieves the number of bits of the ADC:
 *
 * @code
 * #if hw_bn( hw_adc0 ) < 10
 * #  error At least 10-bit ADC is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__ad10c		, _hw_bn_ad10c
#define _hw_bn_ad10c(o,i,a,_)		10


/**
 * @page atmelavr_ad10c
 * @par Interrupts
 *
 * Class `_ad10c` objects can trigger the following IRQs:
 *
 *  * `ADC_NAME`: conversion completed
 */


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_ad10c_t ;

#endif
