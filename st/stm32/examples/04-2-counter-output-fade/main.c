
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
#define FREQUENCY	100
#define DUTYMAX		256


/*  Service the counter overflow IRQ:
 *    compute the next value of the compare unit
 *
 *    Phase 0: increase duty cycle from 0 to DUTYMAX
 *    Phase 1: decrease duty cycle from DUTYMAX to 0 (use ~duty)
 *    Phase 2: off
 *    Phase 3: off
 */
HW_ISR( COUNTER )
{
  static uint16_t		duty ;
  static uint8_t		phase ;

  hw( clear, (COUNTER,irq) );

  if ( phase == 0 )
    hw( write, COUNTER, duty );
  else if ( phase == 1 )
    hw( write, COUNTER, ~duty );

  duty++ ;

  if ( duty == DUTYMAX ) {
    duty = 0 ;
    phase = (phase + 1) & 3 ;
  }
}


int main ( )
{
  hwa( begin_from_reset );

  /*  Power the controllers we use
   */
  hwa( power, (LED,port), on );
  hwa( power, COUNTER, on );
  hwa( commit );

  /*  Configure GPIOs
   */
  hwa( configure, LED1, mode, digital_output, frequency, lowest );
  hwa( configure, pa8, mode, digital_output, frequency, lowest );
  hwa( configure, pa9, mode, digital_output, frequency, lowest );
  hwa( commit );

  /*  Configure the counter
   */
  hwa( configure, COUNTER,
       mode,      counter,
       clock,     from_apb1_psc,
       direction, up_loop,
       prescaler, AHBHZ / (FREQUENCY*DUTYMAX) - 1,
       reload,    DUTYMAX-1,
       run,	  yes );

  //  hwa( configure, (COUNTER,channel1) );

  hw( turn, (COUNTER,nvic), on );
  hw( turn, (COUNTER,irq), on );

  hwa( commit );

  /*  Toggle the LED between sleeps
   */
  for(;;) {
    hw( sleep_until_irq );	// sleep_until_event is OK too.
  }
}
