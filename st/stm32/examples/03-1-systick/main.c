
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

#define AHBHZ		HW_DEVICE_HSIHZ		// The HSI runs at 8 MHz

#define PERIOD		0.5			// Blinking period


int main ( )
{
  hwa( begin, reset );

  /*  Configure the GPIO pin
   */
  hwa( power, (LED1,port), on );
  hwa( commit );

  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );

  /*  Configure the system tick timer
   */
  hwa( configure, systick,
       clock,     ahb/8,
       reload,    PERIOD/2 * AHBHZ/8 - 1,
       run,       yes );

  hwa( commit );

  for(;;) {
    if ( hw( read, (systick,irq) ) )	/* Reading the flag clears it */
      hw( toggle, LED );
  }
}
