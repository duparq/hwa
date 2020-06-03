
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 8-bit compare unit
 */

/**
 * @page atmelavr_oca Class _oca: 8-bit compare unit with waveform generator
 *
 * Class `_oca` objects are 8-bit compare units with waveform generator used in:
 * * @ref attinyx4 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref attinyx5 : `(counter0,compare0)`, `(counter0,compare1)`
 * * @ref atmegax8 : `(counter0,compare0)`, `(counter0,compare1)`, `(counter2,compare0)`, `(counter2,compare1)`
 *
 * @code
 * #if HW_BITS( (counter0,compare0) ) != 8
 * #  error A 8-bit compare unit is required!
 * #endif
 * @endcode
 *
 * @par Relatives
 *
 * * `(counter0,compare0, counter)`: parent counter;
 * * `(counter0,compare0, pin)`: output pin.
 */
#define hw_class__oca


#define HW_BITS__oca			, _hw_bits_oca
#define _hw_bits_oca(...)		8


/*  Return the compare register of a _oca
 *    HW_CODR is blued.
 */
#define hw__oca_reg			, _hw_oca_reg
#define _hw_oca_reg(oo,ct,cp)		HW_XOR(ct,ocr##cp)


/**
 * @page atmelavr_oca
 * @par Interrupts
 *
 * * `(counter0,compare0,irq)`: triggered on compare match A
 * * `(counter0,compare1,irq)`: triggered on compare match B
 */

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
