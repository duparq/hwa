
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * @par Turn a LED on for 1 ms each time the analog comparator output toggles.
 *
 * @par main.c
 */

#include BOARD_H


/*  The analog comparator positive input
 *    This can be `bandgap` or `pin_ain0` (or synonym)
 */
#define REFERENCE		bandgap

/*  The analog comparator output edge that will trigger an IRQ
 *    This can be `falling`, `rising` or `both`
 */
#define EDGE			falling

/*  The counter used to produce the LED pulse
 */
#define COUNTER			counter0
#define COUNTER_CLK_DIV		64
#define COMPARE			compare0

/*  The time the LED is turned on in seconds
 */
#define ON_TIME			0.001

/*  The time the LED is turned on in counter units
 */
#define ON_TIME_COUNT		ON_TIME * HW_SYSHZ / COUNTER_CLK_DIV


/*  Service counter-compare0 IRQ:
 *    disable this IRQ
 *    turn the LED off
 *    turn analog comparator IRQ on
 */
HW_ISR( (COUNTER,COMPARE,irq) )
{
  hw( disable, (COUNTER,COMPARE,irq) );
  hw( write, PIN_LED, 0 );
  hw( clear, (acmp0,irq) );
  hw( enable, (acmp0,irq) );
}


/*  Service analog comparator interrupt:
 *    disable this IRQ off
 *    turn the LED on
 *    program a compare-match IRQ to occur in 1ms.
 *	(maybe reset the prescaler)
 */
HW_ISR( (acmp0,irq) )
{
  hw( disable, (acmp0,irq) );
  hw( write, PIN_LED, 1 );

  if ( COUNTER_CLK_DIV > 1 )
    hw( turn, (COUNTER,prescaler0), off );

  hw( write, COUNTER, 0 );

  if ( COUNTER_CLK_DIV > 1 )
    hw( turn, (COUNTER,prescaler0), on);

  hw( clear, (COUNTER,COMPARE,irq) );
  hw( enable, (COUNTER,COMPARE,irq) );
}


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa( begin, reset );

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle );

  /*  Configure LED pin
   */
  hwa( configure, PIN_LED, mode, digital_output );

  /*  If REFERENCE is a pin, configure it in analog mode (disable its digital
   *  input buffer)
   */
#if HW_ADDRESS(REFERENCE) != -1
  hwa( configure, REFERENCE,
       mode,      analog_input );
#endif

  /*  Configure INPUT_NEG pin in analog mode (disable digital input buffer)
   */
  hwa( configure, PIN_ANALOG_INPUT,
       mode,      analog_input );

  /*  Check that the counter can handle the ON_TIME value. This must be done
   *  here since the C preprocessor does not allow floats in expressions.
   */
  if ( ON_TIME_COUNT > ((1UL<<HW_BITS(COUNTER))-1) )
    HWA_E("COUNTER can not afford ON_TIME.") ;

  /*  Configure the counter to count from 0 to max
   */
  hwa( configure, COUNTER,
       clock,	  ioclk / COUNTER_CLK_DIV,
       direction, up_loop );

  /*  Prepare the compare value for the PIN_LED pulse
   */
  hwa( write, (COUNTER,COMPARE), ON_TIME_COUNT );

  /*  Configure the analog comparator
   */
  hwa( configure,      acmp0,
       edge,	       EDGE,
       positive_input, REFERENCE,
       negative_input, PIN_ANALOG_INPUT );

  hwa( enable, (acmp0,irq) );

  /*  Write this configuration into the hardware
   */
  hwa( commit );

  hw( enable, interrupts );

  for(;;)
    hw( wait, irq );

  return 0 ;
}
