
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Transmit ADC conversion results through software UART
 *
 * Send '\\r'+ 4 hex characters of last ADC conversion every 20 ms
 *
 * @par Test application
 *
 * Display the ADC result on the command line:
 *
 *	./main.py
 *
 * You can add a low-pass filtering with the `--lpf` option.
 *
 * Display the ADC result on a graphical dial (requires wxPython):
 *
 *	./main.py --gfx
 *
 * ![Dial](dial.jpeg)
 *
 * @par config.h
 * @include 06-1-swuart-adc/config.h
 * 
 * @par main.c
 */

#include "config.h"


/*  The counter used to schedule the ADC conversions
 *
 *    FIXME: using the same counter as for swuart overrides the configuration
 *    without error!
 */
#define COUNTER			counter0

volatile uint16_t		adc ;	// Last adc value
volatile uint8_t		x_adc ; // Set to 1 after adc is written


/*  Service counter overflow interrupt:
 *    turn the ADC on, it will start a conversion as the MCU enters sleep
 */
HW_ISR( COUNTER, overflow )
{
  hw( turn, adc0, on );
  hw( toggle, PIN_LED );
}


/*  Service ADC conversion interrupt:
 *    get ADC result, stop the ADC, signal new data ready
 */
HW_ISR( adc0 )
{
  adc = hw( read, adc0 );
  hw( turn, adc0, off );
  x_adc = 1 ;
}


int
main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin_from_reset );

  /*  Configure the software UART
   */
  hwa( configure, UART );

  /*  Configure LED pin
   */
  hwa( configure, PIN_LED, mode, digital_output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Configure the counter to overflow every ~0.02 s.
   *
   *  The compare unit `compare0` (OCRxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will be automatically set to occur
   *  at top in `up_loop` counting mode, and at bottom in `updown_loop` counting
   *  mode.
   *
   *  We use the updown_loop counting mode so that an 8-bit counter can handle
   *  the delay at 16 MHz.
   */
  hwa( configure, COUNTER,
       clock,     ioclk / 1024,
       direction, updown_loop,
       bottom,    0,
       top,       compare0 );

  hwa( write, (COUNTER,compare0), 0.02 * HW_SYSHZ / 1024 / 2 );
  hwa( turn, irq(COUNTER,overflow), on );

  /*  Configure the ADC (this turns it on)
   */
  hwa( configure, adc0,
       clock,     ioclk / 128,
       trigger,   manual,
       vref,      vcc,
       align,     right,
       input,     PIN_ANALOG_INPUT );

  hwa( turn, irq(adc0), on );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  hw( enable_interrupts );

  /*  Wait for UART synchronization, then send the prompt
   */
  while ( !hw(stat,UART).sync )
    hw( sleep_until_irq );
  hw( write, UART, '$' );

  /*  Main loop:
   *	Enter sleep mode
   *	Send new data to host
   */
  for(;;) {
    hw( sleep_until_irq );
    if ( x_adc ) {
      uint16_t x ;
      do {
	x_adc = 0 ;
	x = adc ;
      } while( x_adc );
      hw( write, UART, (x & 0x00FF)>>0 );
      hw( write, UART, (x & 0xFF00)>>8 );
    }
  }
}
