
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

#define UART			swuart0


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  hwa( configure, UART );

  /*  Configure the LED pin
   */
  hwa( configure, PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle	    );

  /*  We can change the system clock frequency if we do not use
   *  a crystal oscillator.
   */
#if !defined HW_DEVICE_CLK_SRC_HZ
  hwa( write, HW_REGISTER(core0, osccal), 0xFF );
#endif

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  /*  Interrupt requests must be serviced for swuart
   */
  hw_enable_interrupts();


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
      hw_sleep_until_irq();

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
	hw_sleep_until_irq();

      uint8_t byte = hw( read, UART );

      /*  Process it
       */
      if ( byte=='A' ) {
	hw( write, PIN_LED, 1 );
	/*
	 *  Known command: reply with values of UART registers dtn, dt0
	 */
	uint16_t dt ;

	dt = hw( read, HW_REGISTER(UART,dtn) ) ;
	hw( write, UART, (dt>>0) & 0xFF );
	hw( write, UART, (dt>>8) & 0xFF );

	dt = hw( read, HW_REGISTER(UART,dt0) ) ;
	hw( write, UART, (dt>>0) & 0xFF );
	hw( write, UART, (dt>>8) & 0xFF );

	hw( write, UART,'$');

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
