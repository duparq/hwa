
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 *
 * Atmel AVR 10-bit analog-digital converter model 'b'
 *
 * Used in:	ATmegaX8
 */

/**
 * @page atmelavr_ad10b Class _ad10b: 10-bit analog to digital converter
 *
 * A class `_ad10b` object is an analog to digital converter with the following
 * features:
 *
 * * 10-bit resolution, left or right adustement
 * * internal 1100 mV bandgap, AVCC, or external voltage reference
 * * 0..VREF input voltage range
 * * 2..128 system clock prescaler
 * * 13 cycles conversion time (25 cycles for the first conversion)
 * * single conversion mode, free-running, and 7 auto trigger sources
 *
 * This ADC shares the analog multiplexer output with the analog comparator. But
 * since the ADC must be turned off for the analog comparator to use the analog
 * multiplexer output, we can consider that these two peripheral have each his
 * own multiplexer and not create a HWA object.
 */
#define _hw_class__ad10b


/**
 * @page atmelavr_ad10b
 * @section atmelavr_ad10b_bn Number of bits of the conversion register
 *
 * The `hw_bn(...)` instruction retrieves the number of bits of the ADC.
 *
 * @code
 * #define ADC		hw_adc0
 *
 * #if hw_bn( ADC ) < 10
 * #  error At least 10-bit ADC is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__ad10b		, _hw_bn_ad10b
#define _hw_bn_ad10b(o,i,a,...)		HW_TX(10,__VA_ARGS__)


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_ad10b_t ;

#endif
