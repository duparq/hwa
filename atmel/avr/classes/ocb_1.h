
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit compare unit with waveform generator with complementary outputs
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_ocb Class _ocb: 8-bit compare unit with waveform generator with complementary outputs
 *
 * This class is used by:
 *
 * * @ref attinyx5 : `(counter1,compare0)`, `(counter1,compare1)`
 *
 * @section atmelavr_ocbrl Relatives
 *
 * * `(COUNTER,COMPARE,counter)`: parent counter;
 * * `(COUNTER,COMPARE,pin_h)`: high-side output pin.
 * * `(COUNTER,COMPARE,pin_l)`: low-side output pin.
 *
 * @section atmelavr_ocbirq Interrupts
 *
 * * `(COUNTER,COMPARE,irq)`: triggered on compare match
 */
#define hw_class__ocb

#define HW_BITS__ocb			, _hw_bn_ocb
#define _hw_bn_ocb(o,a,...)		8

/*  Return the compare register of a _ocb
 */
#define hw__ocb_reg			, _hw_ocb_reg
#define _hw_ocb_reg(oo,ct,cp)		HW_XOR(ct,ocr##cp)	/* HW_CODR is blued */


#if !defined __ASSEMBLER__

typedef struct {

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	outputh, outputl ;
  } config ;

} hwa_ocb_t ;

#endif
