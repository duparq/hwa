
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR 16-bit compare unit with waveform generator
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_occ Class _occ: 16-bit compare unit with waveform generator
 *
 * This class is used by:
 *
 * * @ref attinyx4 : `(counter1,compare0)`, `(counter1,compare1)`
 * * @ref atmegax8 : `(counter1,compare0)`, `(counter1,compare1)`
 *
 * @section atmelavr_occrl Relatives
 *
 * * `(counter0,compare0,counter)`: parent counter;
 * * `(counter0,compare0,pin)`: output pin.
 *
 * @section atmelavr_occirq Interrupts
 *
 * * `(COUNTER,COMPARE,irq)`: triggered on compare match
 */
#define hw_class__occ

#define HW_BITS__occ			, _hw_bits_occ
#define _hw_bits_occ(...)		16

/*  Return the compare register of a _occ
 */
#define hw__occ_reg			, _hw_occ_reg
#define _hw_occ_reg(oo,ct,cp)		HW_XOR(ct,ocr##cp)	/* HW_CODR is blued */


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

} hwa_occ_t ;

#endif
