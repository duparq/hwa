
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief STM32 12-bit A/D converter
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_ada Class _ada: 12-bit analog to digital converter
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `adc0`, `adc1`
 *
 * @section stm32_adadoc ST Documentation:
 *
 *  * AN3116 - ADC modes and their applications
 *  * AN2884 - How to get the best ADC accuracy in STM32 microcontrollers
 *
 * @section stm32_adaft Features
 *
 *  * 12-bit resolution, left or right adustement of the result
 *  * ~1 μs conversion time
 *  * Up to 16 multilexed single-ended input channels
 *  * Internal temperature sensor input
 *  * Internal 1,2 V bandgap input
 *  * Vref-..Vref+ input voltage range
 *  * Single / continuous / scan / discontinuous conversion mode
 *  * Self calibration
 *  * Analog watchdog
 *  * Channel-by-channel programmable sample time
 *  * Conversion on external trigger
 *  * DMA
 *  * Interrupts
 *  * Temperature sensor
 *
 * @note The ADC input clock is generated from the PCLK2 clock divided by a
 * prescaler and it must not exceed 14 MHz.
 *
 * @section Relatives
 *
 * * `(ADC,irq)`: conversion completed @ref hwa_irq "IRQ"
 */
#define hw_class__ada

/**
 * @addtogroup stm32_ada
 * @section stm32_adaact Interface
 *
 * * get the number of bits of the ADC:
 *
 * @code
 * HW_BITS(ADC);
 * @endcode
 */
#define HW_BITS__ada		, _hw_bnada
#define _hw_bnada(p,a,_)	12



#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
} hwa_ada_t ;

#endif
