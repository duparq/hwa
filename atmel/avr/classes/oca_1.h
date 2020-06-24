
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 8-bit compare unit with waveform generator
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_oca Class _oca: 8-bit compare unit with waveform generator
 *
 * This class is used by:
 *
 * * @ref attinyx4 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref attinyx5 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref atmegax8 : `(counter0,compare0)`, `(counter0,compare1)`, `(counter2,compare0)`, `(counter2,compare1)`
 *
 * @section atmelavr_ocarl Relatives
 *
 * * `(counter0,compare0,counter)`: parent counter;
 * * `(counter0,compare0,pin)`: output pin.
 *
 * @section atmelavr_ocairq Interrupts
 *
 *  * `(COUNTER,COMPARE,irq)`: triggered on compare match
 */
#define hw_class__oca


#define HW_BITS__oca			, _hw_bits_oca
#define _hw_bits_oca(...)		8


/*  Return the compare register of a _oca
 */
#define hw__oca_reg			, _hw_oca_reg
#define _hw_oca_reg(oo,ct,cp)		HW_XOR(ct,ocr##cp) /* HW_CODR is blued */


#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Registers used for high-level configuration
   */
  struct {
    uint8_t	update ;
    uint8_t	output ;
  } config ;

  /*  Registers used for configuration resolution
   */
  struct {
    uint8_t	com ;
  } solved ;

} hwa_oca_t ;

#endif
