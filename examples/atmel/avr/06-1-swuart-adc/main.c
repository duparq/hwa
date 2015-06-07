
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *  Send '\\r'+ 4 hex characters of last ADC conversion every 20 ms
 *
 *  Test application:
 *
 *      ./main.py
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
#define COUNTER                 hw_counter0


/*  Pin used as ADC input
 */
#if defined ARDUINO
#  define INPUT                 PIN_A0
#else
#  define INPUT                 hw_pin_8
#endif

#if !defined PIN_LED
#  define PIN_LED               hw_pin_7
#endif

volatile uint16_t               adc ;   // Last adc value
volatile uint8_t                x_adc ; // Set to 1 after adc is written


/*  Service counter overflow interrupt:
 *    turn the ADC on, it will start a conversion as the MCU enters sleep
 */
HW_ISR( COUNTER, overflow )
{
  hw_turn( hw_adc0, on );
  hw_toggle( PIN_LED );
}


/*  Service ADC conversion interrupt:
 *    get ADC result, stop the ADC, signal new data ready
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

  /*  Configure the counter to overflow every ~0.02 s.
   *
   *  The compare unit `compare0` (OCRxA) is used to store the top value.
   *  Unless otherwise stated, the overflow will be automatically set to occur
   *  at top in `loop_up` counting mode, and at bottom in `loop_updown` counting
   *  mode.
   *
   *  We use the loop_updown counting mode so that an 8-bit counter can handle
   *  the delay at 16 MHz.
   */
  hwa_config( COUNTER,
              clock,     syshz_div_1024,
              countmode, loop_updown,
              bottom,    0,
              top,       compare0
              );
  hwa_write( hw_sub(COUNTER, compare0), 0.02 * hw_syshz / 1024 / 2 );
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
