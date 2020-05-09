
/*  This file is part of the HWA project.
 *  Copyright (c) 2020 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program blinks a LED using a counter reload event.
 *
 * @par main.c
 */
#include BOARD_H

#define AHBHZ		HW_DEVICE_HSIHZ		// AHB frequency
#define COUNTER		counter2
#define PERIOD		0.25			// Blinking period


/*  The IRQ is used only to wake the core up.
 */
HW_ISR( COUNTER )
{
  /* hw( clear, (COUNTER,if) ) ; // DOES NOT WORK BECAUSE SETS TO 1 */
  //  hw( write, irqflag(COUNTER), 0 );
  hw( clear, irq(COUNTER) );
}


int main ( )
{
  hwa( begin_from_reset );

  /*  Power the controllers we use
   */
  hwa( power, (LED1,port), on );
  hwa( power, COUNTER, on );
  hwa( commit );

  /*  Configure GPIOs
   */
  hwa( configure, LED1, mode, digital_output, frequency, lowest );
  hwa( commit );

  /*  Configure the counter
   */
  hwa( configure, COUNTER,
       mode,      counter,
       clock,     from_apb1_psc,
       direction, up,
       prescaler, AHBHZ*0.001 - 1,	// 1 ms clock period
       reload,    PERIOD/2 / 0.001 - 1,
       run,       yes );

  hwa( commit );

  hw( enable, nvic, irq(COUNTER) );
  hw( enable, irq(COUNTER) );

  /*  Toggle the LED between sleeps
   */
  for(;;) {
    hw( sleep_until_irq );	// sleep_until_event is OK too.
    hw( toggle, LED1 );
  }
}
