
/*  This file is part of the HWA project.
 *  Copyright (c) 2017 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program blinks a LED using the SysTick timer exception.
 *
 * @par main.c
 */
#include BOARD_H

#define SYSHZ		36e6		// Desired frequency for the SYSCLK signal
#define AHBHZ		9e6		// Desired frequency for the core (and systick)

#define PERIOD		0.5		// Blinking period


/*  The IRQ is used only to wake the core up.
 */
HW_ISR( (systick,irq) ) {}


int main ( )
{
  hwa( begin, reset );

  /* Configure the PLL source and multiplier (must be done before it is enabled).
   * Prepare the connection of the sysclk to the pll. The hardware will wait for
   * the PLL to be locked before actually switching.
   */
  hwa( configure,  pll,
       source,     hsi/2,
       multiplier, SYSHZ/(HW_DEVICE_HSIHZ/2) );
  hwa( connect, sysclk, pll );
  hwa( commit );

  /*  Turn the PLL on.
   */
  hwa( turn, pll, on );
  hwa( commit );

  /* Wait for the PLL to be locked.
   */
  while ( ! hw(stat,pll).ready ) {}

  /*  Configure the AHB
   */
  hwa( configure, ahb,
       clock,     sysclk,
       prescaler, SYSHZ/AHBHZ );
  hwa( commit );

  /*  Configure the GPIO pin
   */
  hwa( power, (LED1,port), on );
  hwa( commit );

  hwa( configure, LED1,
       mode,      digital_output,
       frequency, lowest );
  hwa( commit );

  /*  Configure the system tick timer
   */
  uint32_t onems = hw(read, (systick,onems));

  hwa( configure, systick,
       clock,     ahb,
       reload,    ((uint32_t)(PERIOD/2 / 0.001)*onems - 1) & 0xFFFFFF );
  hwa( turn, systick, on );
  hwa( enable, (systick,irq) );
  hwa( commit );

  /*  Toggle the LED between sleeps
   */
  for(;;) {
    hw( wait, irq );
    hw( toggle, LED );
  }
}
