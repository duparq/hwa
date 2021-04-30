
/*  This file is part of the HWA project.
 *  Copyright (c) 2021 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Use of the UART.
 *
 * @par main.c
 */
#include BOARD_H

#define AHBHZ		HW_DEVICE_HSIHZ		// AHB frequency
#define APBHZ		AHBHZ

#define UART		usart2
#define UART_TX		(porta,2)


int main ( )
{
  /*  Power the controllers we use
   */
  hw( power, (UART_TX,port), on );
  hw( power, UART, on );

  hw( configure, UART_TX, function, (UART,tx), mode, digital_output );
  
  hw( configure,	UART,
      mode,		uart,
      divider,		AHBHZ/10000,	// 10 kbps
      /* clockhz,		APBHZ, */
      /* bps,		100000, */
      /* tol,		0.01, */
      databits,		8,
      parity,		none,
      stopbits,		1,
      receiver,		off,
      transmitter,	on,
      run,		yes );

  for (;;) {
    while ( hw(read,(UART,txe)) != 1 ) {}
    hw_waste_cycles( 0.003*AHBHZ );
    hw( write, (UART,dr), '.' );
  }
}
