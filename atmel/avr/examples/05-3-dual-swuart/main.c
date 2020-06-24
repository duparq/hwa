
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Dual software UART
 *
 * Echo what is received from one software UART to both. The first UART that
 * synchronizes sets the other up.
 *
 * This is totally reversible, the LED shows when one UART resynchronizes.
 *
 * Notes:
 *
 * 1. Do not leave an RX pin floating!
 *
 * 2. Choose a moderate baudrate so that the CPU has the time to service
 * interrupts in a relatively reasonable time (115200 bps seems OK for
 * `counter1` with internal 8 MHz RC oscilltor and OSCCAL=0xFF or the 16 MHz
 * Nanodccduino).
 *
 * 3. CH340 USB/Serial adapter does not send parity bits under Linux (though no
 * error is triggered). Then, the software UART never resynchronizes (it works
 * in a Windows XP VirtualBoxed under Linux, so there must be a bug in the Linux
 * driver).
 *
 * @par Test application
 *
 *	./main.py -b BAUDRATE
 *
 * @par config.h
 * @include 05-3-dual-swuart/config.h
 *
 * @par main.c
 */

#include "config.h"

#if defined HW_DEVICE_ATTINYX5
#  error ATtinyX5 devices are not supported because the same pin-change interrupt controller can not be used for 2 different software UARTS
#endif


void uart0_putbyte ( uint8_t byte )
{
  while ( !hw(stat,UART0).txc ) {}
  hw( write, UART0, byte );
}


void uart1_putbyte ( uint8_t byte )
{
  while ( !hw(stat,UART1).txc ) {}
  hw( write, UART1, byte );
}


int
main ( )
{
  /*  Increase the frequency of the RC oscillator to the max
   */
  hw( write, (core0, osccal), 0xFF );

  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Configure the software UARTs
   */
  hwa( configure, UART0 );
  hwa( configure, UART1 );

  hwa( configure, PIN_LED, mode, digital_output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  /*  Interrupt requests must be serviced for swuart
   */
  hw( enable, interrupts );


  /*  Main loop
   */
  for(;;) {
    /*
     *	Wait that one UART resynchronizes and configure the other with the same
     *	baudrate
     */
    hw( write, PIN_LED, 1 );

    hw( reset, UART0 );
    hw( reset, UART1 );
    for(;;) {
      hw( wait, irq );
      if ( hw(stat,UART0).sync ) {
	/*
	 *  Configure UART1 with the baudrate detected on UART0
	 */
	uart0_putbyte( '$' );	// signal the synchronization
	hw( write, (UART1,dt0), hw( read, (UART0,dt0) ) );
	hw( write, (UART1,dtn), hw( read, (UART0,dtn) ) );
	hw( write, (UART1,sync), 1 );
	uart1_putbyte( '$' );	// signal the synchronization
	break ;
      }
      if ( hw(stat,UART1).sync ) {
	/*
	 *  Configure UART0 with the baudrate detected on UART1
	 */
	uart1_putbyte( '$' );	// signal the synchronization
	hw( write, (UART0,dt0), hw( read, (UART1,dt0) ) );
	hw( write, (UART0,dtn), hw( read, (UART1,dtn) ) );
	hw( write, (UART0,sync), 1 );
	uart0_putbyte( '$' );	// signal the synchronization
	break ;
      }
    }
    hw( write, PIN_LED, 0 );

    /*
     *	Send on one UART what has been received from the other
     */
    for(;;) {
      hw( wait, irq );
      if ( hw(stat,UART0).rxc ) {
	/*
	 *  UART0 -> UART0 + UART1
	 */
	if ( hw(stat,UART0).stop == 0 )
	  break ;	/* null stop bit -> resynchronize */

	uint8_t byte = hw( read, UART0 );
	uart0_putbyte( byte );
	uart1_putbyte( byte );
      }
      if ( hw(stat,UART1).rxc ) {
	/*
	 *  UART1 -> UART1 + UART0
	 */
	if ( hw(stat,UART1).stop == 0 )
	  break ;	/* null stop bit -> resynchronize */

	uint8_t byte = hw( read, UART1 );
	uart1_putbyte( byte );
	uart0_putbyte( byte );
      }
    }
  }
}
