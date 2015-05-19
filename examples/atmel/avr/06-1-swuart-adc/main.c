
/*	Synchronize the software UART
 *	Send a '$' prompt
 *	Infinite loop:
 *	  wait 0.02 s
 *	  send '\r' + 4 hex characters of last ADC result
 *
 *	Test: ./main.py
 *
 *  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#include "config.h"
#include <hwa.h>


/*  Counter 
 *
 *    FIXME: using the same counter as for swuart overrides the configuration
 *    without error!
 */
#define COUNTER			hw_counter0


/*  Pin used as ADC input
 */
#define INPUT			hw_pin_8


#define PIN_LED			hw_pin_7


volatile uint16_t		adc ;	// Last adc value
volatile uint8_t		x_adc ;	// Set to 1 after adc is written


/*  Service counter overflow interrupt:
 *    turn the ADC on, it will start a conversion as the MCU enters sleep
 */
HW_ISR( COUNTER, overflow )
{
  hw_turn( hw_adc0, on );
  hw_toggle( PIN_LED );
}


/*  Service adc conversion interrupt:
 *    get adc result, stop the ADC, signal new data is ready
 */
HW_ISR( hw_adc0 )
{
  adc = hw_read( hw_adc0 );
  hw_turn( hw_adc0, off );
  x_adc = 1 ;
}


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

  /*  Configure LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle );

  /*  Configure the counter to overflow every 0.02 s.
   *
   *  The compare unit `compare0` (OCRxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will be automatically set to occur
   *  at top in `loop_up` counting mode, and at bottom in `loop_updown` counting
   *  mode.
   */
  hwa_config( COUNTER,
	      clock,     syshz_div_1024,
	      countmode, loop_up,
	      bottom,    0,
	      top,       compare0
	      );
  hwa_write( hw_sub(COUNTER, compare0), 0.02 * hw_syshz / 1024 );
  hwa_turn_irq( COUNTER, overflow, on );

  /*  Configure the ADC (this turns it on)
   */
  hwa_config( hw_adc0,
  	      clock,   syshz_div_128,
  	      trigger, manual,
  	      vref,    vcc,
  	      align,   right,
  	      input,   INPUT
  	      );
  hwa_turn_irq( hw_adc0, on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  /*  Wait for UART synchronization, then send the prompt
   */
  while ( !hw_stat(UART).synced )
    hw_sleep();
  hw_write( UART, '$' );

  /*  Main loop:
   *    Enter sleep mode
   *    Send new data to host
   */
  for(;;) {
    hw_sleep();
    if ( x_adc ) {
      uint16_t x ;
      do {
	x_adc = 0 ;
	x = adc ;
      } while( x_adc );
      hw_write( UART, (x & 0x00FF)>>0 );
      hw_write( UART, (x & 0xFF00)>>8 );
    }
  }
}
