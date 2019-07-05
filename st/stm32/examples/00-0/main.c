
#if 0
#include </home/indy/dev/hwa/st/stm32/classes/p16a_1.h>
/* #include </home/indy/dev/hwa/st/stm32/classes/p16a_2.h> */
#include </home/indy/dev/hwa/st/stm32/classes/io1a_1.h>
/* #include </home/indy/dev/hwa/st/stm32/classes/io1a_2.h> */
#include </home/indy/dev/hwa/st/stm32/classes/rcca_1.h>
/* #include </home/indy/dev/hwa/st/stm32/classes/rcca_2.h> */
#include </home/indy/dev/hwa/st/stm32/hwa_1.h>
//#include </home/indy/dev/hwa/st/stm32/hwa_2.h>



#define hw_rcc				_rcca, 101, 0x40021000


#define hw_port0			_p16a, 108, 0x40010800
#define hw_port0_rcc			_rccen, port0en

#define hw_pa9			_io1a, 122, port0,  1,  9

/* HW_SHOW( HW_X(pa9,port) ); */

/* HW_SHOW( HW_X(port0,rcc) ); */
/* HW_SHOW( HW_X(rcc,port0) ); */
/* HW_SHOW( HW_X(rcc,(pa9,port)) ); */

/* HW_SHOW( HW_XP(rcc,(pa9,port)) ); */

/* HW_SHOW( HW_OR(rcc,(pa9,port)) ); */
#endif




#if 1
#include BOARD_H

#define AHBHZ		HW_DEVICE_HSEHZ

#define COUNTER		counter2
#define PERIOD		0.25			// Blinking period


/*  The IRQ is used only to wake the core up.
 */
HW_ISR( COUNTER )
{
  hw( clear, (COUNTER,irq) );
  hw( toggle, pa8 );
}


int main ( )
{
  hwa( begin_from_reset );

  /*  Clock with 8 MHz external crystal (hse)
   */
  hwa( power, hse, on );
  hwa( connect, sysclk, hse );
  hwa( configure, ahb, clock, sysclk, prescaler, 1 );

  /*  Power on the controllers we use
   */
  /* hwa( turn, (rcc,(LED1,port)), on ); */
  hwa( turn, (LED1,port,rcc), on );
  hwa( turn, (rcc,port0), on );
  hwa( turn, (rcc,COUNTER), on );
  hwa( turn, (rcc,usart1), on );
  hwa( commit );

  /*  Configure the GPIO pin
   */
  hwa( configure, LED1, mode, digital_output, frequency, lowest );
  hwa( configure, pa8, mode, digital_output, frequency, lowest );
  hwa( configure, pa9, function, gpio, mode, digital_output, frequency, lowest );
  hwa( configure, pa9, function, (usart1,tx), mode, digital_output, frequency, lowest );
  hwa( configure, pa10, function, (usart1,rx), mode, digital_input );
  hwa( configure, pa0, function, wkup, mode, digital_input );
  //  hwa( configure, pa10, function, (counter2,channel2), mode, digital_input );
  hwa( commit );

  /*  Configure the counter
   */
  /* hwa( configure, COUNTER, */
  /*      clock,     from_apb1, */
  /*      direction, up_loop, */
  /*      prescaler, (uint16_t)(0.001*AHBHZ)-1, */
  /*      reload,    (uint16_t)(PERIOD/2 / 0.001)-1 ); */

  /* hwa( configure, COUNTER, */
  /*      mode,      counter, */
  /*      input,     from_apb1, */
  /*      direction, up_loop, */
  /*      prescaler, (uint16_t)(0.001*AHBHZ)-1, */
  /*      reload,    (uint16_t)(PERIOD/2 / 0.001)-1 ); */

  /* hwa( write, (COUNTER,dir), 0 ); */
  hwa( write, (COUNTER,cms), 3 );
  hwa( write, (COUNTER,psc), 0.001*AHBHZ-1 );
  /* hwa( write, (COUNTER,arr), (uint32_t)(PERIOD/2 / 0.001)-1 ); */
  hwa( write, (COUNTER,arr), 9 );
  //  hwa( write, (COUNTER,cen), 1 );
  hwa( turn, COUNTER, on );

  hwa( turn, (COUNTER,irq), on );
  /* hwa( turn, nvic, irq(COUNTER), on ); */
  hwa( turn, (COUNTER,nvic), on );
  /* hwa( turn, (nvic,COUNTER), on ); */
  hwa( commit );

  /*  Toggle the LED between sleeps
   */
  /* uint8_t n=0; */
  for(;;) {
    hw( write, pa9, hw(read,COUNTER)==8 );
    //    hw( sleep_until_irq );	// hw_sleep_until_event() is OK too.
    /* n++ ; */
    /* if ( n>20 ) */
    /*   hw( turn, nvic, irq(COUNTER), off ); */
      /* hw( turn, (COUNTER,nvic), off ); */
      /* hw( turn, (COUNTER,irq), off ); */
    //hw( power, COUNTER, off );
  }
}
#endif

/* hwa( configure, pa9, function, (usart0,tx), mode, digital_output, frequency, lowest ); */
/* hwa( configure, pa9, function, (usart1,tx,(garb)), mode, digital_output, frequency, lowest ); */
/* hwa( configure, pa9, function, foo, mode, digital_output, frequency, lowest ); */
/* hwa( configure, pa9, function, gpio, mode, digital_output, frequency, lowest ); */
/* hwa( configure, pa9, function, (usart1,tx), mode, digital_output, frequency, lowest ); */
/* hwa( configure, pa9, function, (usart1,rx), mode, digital_output, frequency, lowest ); */

/* HW_SHOW( HW_IDX(pa9) ); */
