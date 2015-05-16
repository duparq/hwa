
/*	Synchronize the software UART
 *	Reply to 'A' with swuart timings dtn & dt0
 *
 *	Test: ./main.py
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#include "config.h"
#include <hwa.h>

#if !defined PIN_LED
#  define PIN_LED		hw_pin_7
#endif

#define UART			hw_swuart0


/*  We can change the system clock frequency if we do not use
 *  a crystal oscillator
 */
#if !defined HW_DEVICE_CLK_SRC_HZ
// #  define OSCCAL	0xFF
#endif


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Configure the software UART
   */
  hwa_config( UART );

  /*  Configure the LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Change the frequency of the RC oscillator
   */
#if defined OSCCAL
  hwa_write_reg( hw_core0, osccal, OSCCAL );
#endif

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  /*  Interrupt requests must be serviced for swuart
   */
  hw_enable_interrupts();


  /*  Main loop:
   *    synchronize UART
   *    process incomming commands until error
   */
  for(;;) {
    /*
     *  Resynchronize UART
     */
    hw_write( PIN_LED, 1 );

    /*  Force UART to re-synchronize
     */
    hw_reset( UART );

    /*  Wait for UART synchronization, then send the prompt
     */
    while ( !hw_stat(UART).synced )
      hw_sleep();
    hw_write( UART, '$');

    hw_write( PIN_LED, 0 );

    /*  Process commands
     */
    for(;;) {

      /*  Wait for a command
       */
      while ( !hw_stat(UART).rxc )
	hw_sleep();
      uint8_t byte = hw_read(UART);

      /*  Process it
       */
      if ( byte=='A' ) {
	hw_write( PIN_LED, 1 );
	/*
	 *  Known command: reply with values of UART timings
	 */
	uint16_t dt ;

	dt = hw_read_reg( UART, dtn ) ;
	hw_write( UART, (dt>>0) & 0xFF );
	hw_write( UART, (dt>>8) & 0xFF );

	dt = hw_read_reg( UART, dt0 ) ;
	hw_write( UART, (dt>>0) & 0xFF );
	hw_write( UART, (dt>>8) & 0xFF );

	hw_write( UART,'$');
	hw_write( PIN_LED, 0 );
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
