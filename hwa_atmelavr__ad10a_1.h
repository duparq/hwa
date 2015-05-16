
/*
 *	Atmel AVR 10-bit analog-digital converter model 'a'
 *
 *	Used in:	ATtinyX4
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/**
 * @page atmelavr_ad10a _ad10a
 *
 * A class `_ad10a` object is a 10-bit analog to digital converter.
 */
#define _hw_class__ad10a


/**
 * @page atmelavr_ad10a
 * @par Number of bits of the conversion register
 *
 * @code
 * #define ADC		hw_adc0
 *
 * #if hw_bn( ADC ) < 10
 * #  error At least 10-bit ADC is required!
 * #endif
 * @endcode
 */
#define _hw_mthd_hw_bn__ad10a		, _hw_bn_ad10a
#define _hw_bn_ad10a(p,i,a,_)		10


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_ad10a_t ;

#endif
