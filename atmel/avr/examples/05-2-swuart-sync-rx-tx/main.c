
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Reply to incoming 'A' with software UART registers dtn & dt0.
 *
 *  Test application:
 *
 *	./main.py
 *
 * @par config.h
 * @include 05-2-swuart-sync-rx-tx/config.h
 *
 * @par main.c
 */

#include "config.h"


void uart_putbyte ( uint8_t byte )
{
  while ( !hw(stat,UART).txc )
    hw( wait, irq );
  hw( write, UART, byte );
}


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Configure the software UART
   */
  hwa( configure, UART );
  hwa( enable, (DIABOLO_PIN_RX,port,pcic,irq) );
  hwa( turn, (DIABOLO_PIN_RX,port,pcic), DIABOLO_PIN_RX, on );

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, mode, digital_output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle	    );

  /*  We can change the system clock frequency if we do not use
   *  a crystal oscillator.
   */
#if !defined HW_DEVICE_CLK_SRC_HZ
  hwa( write, (core0, osccal), 0xFF );
#endif

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  /*  Interrupt requests must be serviced for swuart
   */
  hw( enable, interrupts );


  /*  Main loop:
   *	synchronize UART
   *	process incomming commands until error
   */
  for(;;) {

    /*	Signal UART desynchronization
     */
    hw( write, PIN_LED, 0 );

    /*	Force UART to re-synchronize
     */
    hw( reset, UART );

    /*	Wait for UART synchronization, then send the prompt
     */
    while ( !hw(stat,UART).sync )
      hw( wait, irq );

    hw( write, UART, '$');

    /*	Signal UART synchronization
     */
    hw( write, PIN_LED, 1 );

    /*	Process commands
     */
    for(;;) {

      /*  Wait for a command
       */
      while ( !hw(stat,UART).rxc )
	hw( wait, irq );

      uint8_t byte = hw( read, UART );

      /*  Process it
       */
      if ( byte=='A' ) {
	hw( write, PIN_LED, 1 );
	/*
	 *  Known command: reply with values of UART registers dtn, dt0
	 */
	uint16_t dt ;

	dt = hw( read, (UART,dtn) ) ;
	uart_putbyte( (dt>>0) & 0xFF );
	uart_putbyte( (dt>>8) & 0xFF );

	dt = hw( read, (UART,dt0) ) ;
	uart_putbyte( (dt>>0) & 0xFF );
	uart_putbyte( (dt>>8) & 0xFF );

	uart_putbyte( '$' );

	hw( write, PIN_LED, 0 );
      }
      else {
	/*
	 *  Unknown command: -> resync
	 */
	break ;
      }
    }
  }
}
