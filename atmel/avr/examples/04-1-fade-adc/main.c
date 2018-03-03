
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 * Fade a LED according to ADC conversion.
 *
 * This can also be used to drive a servo (brown->ground, red->+6V,
 * yellow->pwm). In that case, it is recommended to use a separated power supply
 * for the servo as an USB RS232 module may not provide enough current.
 */

/*  Include the target board definitions (includes hwa.h)
 */
#include BOARD_H


/*  The counter used for PWM
 */
#define COUNTER			counter1
#define COUNTER_CLK_DIV		8


/*  PWM timings
 */
#if HW_BITS(COUNTER)==16
#  define PWM_PERIOD		0.02		/* 50 Hz */
#  define PWM_TMIN		0		/* set to 0.000300 for servo */
#  define PWM_TMAX		PWM_PERIOD	/* set to 0.003000 for servo */
#else
#  define PWM_PERIOD		0.0002		/* 5 kHz */
#  define PWM_TMIN		0
#  define PWM_TMAX		PWM_PERIOD
#endif


/*  Clock divider for the ADC
 */
#define ADC_CLK_DIV		128		/* T=~13*128/8=208 µs @8MHz */


/*  Top value and range of duty value according to PWM timings
 */
#define count_t			hw_uint_t(HW_BITS(COUNTER))
#define COUNT_TOP		(uint32_t)(HW_SYSHZ*PWM_PERIOD/COUNTER_CLK_DIV)
#define COMPARE_MIN		(count_t)(PWM_TMIN*HW_SYSHZ/COUNTER_CLK_DIV)
#define COMPARE_MAX		(count_t)(PWM_TMAX*HW_SYSHZ/COUNTER_CLK_DIV)


/*  ATtinyX5s use compare2 as top value, others use compare0
 */
#if defined HW_DEVICE_ATTINYX5
#  define TOP_OBJ		compare2
#else
#  define TOP_OBJ		compare0
#endif


/*  Value to store in the compare unit (must be the same size as the count
 *  register)
 */
static volatile count_t		duty ;


/*  Service ADC "conversion completed" IRQ: compute duty
 *  Make the ISR interruptible so that counter IRQs are serviced promptly.
 */
HW_ISR( adc0, interruptible )
{
  /*  Get the new value
   */
  uint16_t adc = hw( read, adc0 );

  /*  Low-pass filter
   */
  const uint8_t			ns = 32 ;	/* # of samples	  */
  static uint16_t		lpfsum ;	/* sum of samples */

  lpfsum = lpfsum - (lpfsum + ns/2)/ns + adc ;

  /*  Compute duty in the range [COMPARE_MIN .. COMPARE_MAX] from lpfsum in the
   *  range [0..ns*1023]
   */
  uint32_t tmp32 = lpfsum ;
  tmp32 = (tmp32 * (COMPARE_MAX-COMPARE_MIN) + ns*1023/2) / (ns*1023) + COMPARE_MIN ;

  count_t tmp = tmp32 ;
  if ( sizeof(count_t) > 1 ) {
    hw_disable_interrupts();
    duty = tmp ;
    hw_enable_interrupts();
    /* HW_ATOMIC( */
    /*	      duty = tmp ; */
    /*	      ); */
  }
  else
    duty = tmp ;

  /*  Start a new conversion
   */
  hw( trigger, adc0 );
}


/*  Service counter-overflow IRQ: turn the LED on and enable the compare IRQ
 *  that turns it off
 */
HW_ISR( COUNTER, overflow, non_interruptible )
{
  /*  No need to protect access to duty since interrupts are not allowed */

  if ( duty ) {
    hw( write, PIN_LED, 1 );
    if ( duty < COUNT_TOP ) {
      hw( write, (COUNTER,compare1), duty );
      hw( turn, HW_IRQ(COUNTER,compare1), on );
    }
    else
      hw( turn, HW_IRQ(COUNTER,compare1), off );
  }
  else {
    hw( write, PIN_LED, 0 );
    hw( turn, HW_IRQ(COUNTER,compare1), off );
  }
}


/*  Service compare-match IRQ: turn the LED off
 *
 *  Note: if the address of the port register is < 0x40 (assembler 0x20) we can
 *  spare a few bytes and have a faster code using a naked ISR.
 */
#if HW_ADDRESS(HW_REGISTER((PIN_LED,port),port)) < 0x40
HW_ISR( COUNTER, compare1, naked )
{
  hw( write, PIN_LED, 0 );
  hw_asm("reti");
}
#else
HW_ISR( COUNTER, compare1 )
{
  hw( write, PIN_LED, 0 );
}
#endif


int main ( )
{
  /*  Create a HWA context to collect the hardware configuration
   *  Preload this context with RESET values
   */
  hwa_begin_from_reset();

  /*  Have the CPU enter idle mode when the 'sleep' instruction is executed.
   */
  hwa( configure,  core0,
       sleep,	   enabled,
       sleep_mode, idle	     );

  /*  Configure LED pin
   */
  hwa( configure, PIN_LED,
       direction, output   );

  /*  Configure analog input pin in analog mode (disable digital input buffer)
   *  and enable the internal pull-up resistor
   */
  hwa( configure, PIN_ANALOG_INPUT,
       mode,	  analog,
       direction, input,
       pullup,	  on	   );

  /*  Check that the counter can handle the top value. This must be done
   *  here since the C preprocessor does not allow floats in expressions.
   */
  if ( COUNT_TOP > ((1UL<<HW_BITS(COUNTER))-1) )
    HWA_ERR("PWM_COUNTER can not afford PWM_PERIOD.") ;

  /*  Configure the counter prescaler
   */
  hwa( configure, (COUNTER,prescaler),
       clock,	  ioclk );

  /*  Configure the counter to overflow periodically and trigger an interrupt
   *  The counter overflow ISR manages the compare IRQ
   */
  hwa( configure, COUNTER,
       clock,	  ioclk / COUNTER_CLK_DIV,
       countmode, up_loop,
       bottom,	  0,
       top,	  TOP_OBJ,
       //	    overflow,  at_top,
       );
  hwa( write, (COUNTER, TOP_OBJ), COUNT_TOP );
  hwa( turn, HW_IRQ(COUNTER,overflow), on );

  /*  Configure the ADC to make a single conversion and trigger an
   *  IRQ. The ISR will start a new conversion after its hard job is done.
   */
  hwa( configure, adc0,
       clock,	  ioclk / ADC_CLK_DIV,
       trigger,	  manual,
       vref,	  vcc,
       align,	  right,
       input,	  PIN_ANALOG_INPUT );
  
  hwa( turn, HW_IRQ(adc0), on );
  hwa( trigger, adc0 );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep_until_irq();

  return 0 ;
}
