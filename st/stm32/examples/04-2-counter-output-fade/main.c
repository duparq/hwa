
/*  This file is part of the HWA project.
 *  Copyright (c) 2020 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * This program fades LED1 (porta,2) using one channel output of a counter.
 *
 * The counting direction of the counter (up/down) is output on LED2. It can
 * synchronize an oscilloscope to view the PWM signal.
 *
 * You can direct the output signal to (portb,10) instead of LED2 (porta,3)
 * after having powered its port and the afio. This requires a remapping of the
 * counter that is handled by HWA.
 *
 * @par main.c
 */
#include BOARD_H

#define AHBHZ		HW_DEVICE_HSIHZ		// AHB frequency
#define COUNTER		counter2
#define CHANNEL		channel3
#define DUTYMAX		100

#if HW_ADDRESS(LED2) == -1
#  define LED2		fake
#endif

/*  Service the counter IRQ (every overflow or underflow, then the frequency of
 *  the IRQ does not depend on the counting mode of the counter, but the
 *  frequency of the PWM output does): compute the next value of the compare
 *  unit.
 *
 *    Phase 0: increase duty cycle from 0 to DUTYMAX
 *    Phase 1: decrease duty cycle from DUTYMAX to 0 (use ~duty)
 *    Phase 2: off
 *    Phase 3: off
 */
HW_ISR(COUNTER)
{
  static uint16_t	duty ;
  static uint8_t	phase ;

  hw( clear, (COUNTER,irq) );

  hw( write, LED2, hw(read,(COUNTER,dir))==0 );

  if ( phase == 0 )
    hw( write, (COUNTER,CHANNEL), duty );
  else if ( phase == 1 )
    hw( write, (COUNTER,CHANNEL), DUTYMAX-duty );

  duty++ ;

  if ( duty > DUTYMAX ) {
    duty = 0 ;
    phase = (phase+1) & 3 ;
  }
}


int main ( )
{
  hwa( begin, reset );

  /*  Power the controllers we use
   */
  hwa( power, (LED1,port), on );
  hwa( power, (LED2,port), on );
  hwa( power, COUNTER, on );
  hwa( power, afio, on );
  hwa( commit );

  /*  Configure GPIOs
   */
  hwa( configure, LED1, function, (COUNTER,CHANNEL), mode, digital_output );
  hwa( configure, LED2, function, gpio, mode, digital_output );

  /* FIXME: no error triggered when setting function gpio and (counter2,channel1) to pa0 */

  /*  Configure and start the counter (sms=0, cms=3, opm=0, cen=1)
   */
  hwa( configure, COUNTER,
       clock,     from_apb1_psc,
       direction, updown_loop,
       prescaler, AHBHZ/DUTYMAX/100 - 1,
       reload,    DUTYMAX,
       run,       yes );

  /*  Configure the channel used as PWM output
   */
  hwa( configure, (COUNTER,CHANNEL),
       function,  compare,
       level,     clear_on_match_up_set_on_match_down,
       output,    connected );

  hwa( commit );

  hw( enable, (nvic,COUNTER) );
  hw( enable, (COUNTER,irq) );

  /*  Sleep between IRQs.
   */
  for(;;) hw( wait, irq );
}
