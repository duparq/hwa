
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief UART
 */

/**
 * @ingroup atmelavr_classes
 * @defgroup atmelavr_uarta Class _uarta: Universal Asynchronous serial Receiver Transmitter
 *
 * This class is used by:
 *
 *  * @ref atmegax8 : `uart0`
 *
 * @note Synchronous mode of USART is not implemented.
 */
#define hw_class__uarta


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r16_t	ubrr ;
  hwa_r8_t	csra, csrb, csrc/* , dr */ ;

  struct {
    uint16_t	brr ;
    uint8_t	csz, pm, sbs, rxen, txen, u2x ;
  } config ;
} hwa_uarta_t ;

#endif
