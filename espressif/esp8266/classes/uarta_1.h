
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief UART
 */

/**
 * @page espressif_uarta Class _uarta: Universal Asynchronous serial Receiver Transmitter
 *
 * A class `_uarta` object is a UART.
 *
 * It is used in:
 *
 *  * @ref esp8266 : `hw_uart0` and `hw_uart1`
 */
#define _hw_class__uarta


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t     _brr, _conf0, _conf1 ;

  struct {
    uint32_t	baudrate ;
    uint8_t	databits, parity, stopbits, rxen, txen ;
  } config ;
} hwa_uarta_t ;

#endif
