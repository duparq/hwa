
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program blinks a LED using the SysTick timer.
 *
 * @par main.c
 */
#include BOARD_H

#define AHBHZ		8000000		// The HSI runs at 8 MHz

#define PERIOD		0.5		// Blinking period


int main ( )
{
  hwa_begin_from_reset();

  /*  Configure the GPIO pin
   */
  hwa( power, HW_RELATIVE(LED1,port), on );
  hwa_commit();

  hwa( configure, LED1,
       mode,      digital,
       direction, output,
       frequency, 50MHz );

  /*  Configure the system tick timer
   */
  hwa( configure, systick,
       clock,     ahb/8,
       reload,    PERIOD/2 * AHBHZ/8,
       run,       yes );

  //hwa( turn, systick, on );

  hwa_commit();

  for(;;) {
    if ( hw(read, HW_IRQFLAG(systick) ) )	/* Reading the flag clears it */
      hw( toggle, LED );
  }
}
