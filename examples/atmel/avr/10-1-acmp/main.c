
/*  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Turn a LED on for 1 ms each time the analog comparator detects an edge
 *
 * @par targets/attiny84.h
 * @include targets/attiny84.h
 */


/*	Target
 */
#include <targets/attiny84.h>
#include <hwa.h>


/*  The pin at which the LED is connected (already done for Arduino
 *  targets). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED		hw_pin_7
#endif

/*  The analog comparator positive input
 *    This can be `bandgap` or `hw_pin_ain0` (or synonym)
 */
#define INPUT_POS		bandgap

/*  The analog comparator negative input
 *    This can be any analog input pin
 */
#define INPUT_NEG		hw_pin_6

/*  The analog comparator output edge that will trigger an IRQ
 *    This can be `falling`, `rising` or `both`
 */
#define EDGE			falling

/*  The counter used to produce the LED pulse
 */
#define COUNTER			hw_counter0
#define COUNTER_CLK_DIV		64
#define COMPARE			compare0

/*  The time the LED is turned on in seconds
 */
#define PERIOD			0.001

/*  The time the LED is turned on in counter units
 */
#define CPERIOD			PERIOD * hw_syshz / COUNTER_CLK_DIV


/*  Service counter-compare0 IRQ:
 *    disable this IRQ
 *    turn the LED off
 *    turn analog comparator IRQ on
 */
HW_ISR( COUNTER, COMPARE )
{
  hw_turn_irq( COUNTER, COMPARE, off );
  hw_write( PIN_LED, 0 );
  hw_clear_irqf( hw_acmp0 );
  hw_turn_irq( hw_acmp0, on );
}


/*  Service analog comparator interrupt:
 *    disable this IRQ off
 *    turn the LED on
 *    program a compare-match IRQ to occur in 1ms.
 *      (maybe reset the prescaler)
 */
HW_ISR( hw_acmp0 )
{
  hw_turn_irq( hw_acmp0, off );
  hw_write( PIN_LED, 1 );
  if ( COUNTER_CLK_DIV > 1 ) {
    hw_turn(hw_sub(COUNTER,prescaler0), off);
    hw_clear( COUNTER );
    hw_turn(hw_sub(COUNTER,prescaler0), on);
  }
  else
  hw_clear_irqf( COUNTER, COMPARE );
  hw_turn_irq( COUNTER, COMPARE, on );
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa_config( hw_core0,
  	      sleep,      enabled,
  	      sleep_mode, idle
	      );

  /*  Configure LED pin
   */
  hwa_config( PIN_LED, direction, output );

  /*  Configure INPUT_POS pin in analog mode (disable digital input buffer) if
   *  it is an i/o pin (not `bandgap`)
   */
#if hw_id( hw_io(INPUT_POS) )
  hwa_config( INPUT_POS,
	      mode,      analog,
	      direction, input
	      );
#endif

  /*  Configure INPUT_NEG pin in analog mode (disable digital input buffer)
   */
  hwa_config( INPUT_NEG,
	      mode,      analog,
	      direction, input
	      );

  /*  Check that the counter can handle the PERIOD value. This must be done
   *  here since the C preprocessor does not allow floats in expressions.
   */
  if ( CPERIOD > ((1UL<<hw_bn(COUNTER))-1) )
    HWA_ERR("COUNTER can not afford PERIOD.") ;

  /*  Configure the counter to count from 0 to max
   */
  hwa_config( COUNTER,
	      clock,     HW_G2(syshz_div, COUNTER_CLK_DIV),
	      countmode, loop_up
	      );

  /*  Prepare the compare value for the PIN_LED pulse
   */
  hwa_write( hw_sub(COUNTER,COMPARE), CPERIOD );

  /*  Configure the analog comparator
   */
  hwa_config( hw_acmp0,
  	      edge,           EDGE,
  	      positive_input, INPUT_POS,
  	      negative_input, INPUT_NEG
  	      );
  hwa_turn_irq( hw_acmp0, on );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();

  return 0 ;
}
