
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @example
 *
 *      Fade a LED according to ADC conversion
 *
 *      This can also be used to drive a servo (brown->ground, red->+6V,
 *      yellow->pwm). In that case, it is recommended to use a separated power
 *      supply for the servo as an USB RS232 module may not provide enough
 *      current.
 */

/*  Include the target board definitions (includes hwa.h)
 */
#if !defined BOARD_H
#  define BOARD_H               <boards/attiny84.h>
#endif

#include BOARD_H


/*  The pin at which the LED is connected (already defined for Arduino
 *  boards). The target also defines the package of the device, then pin
 *  numbers can be used as well as pin names.
 */
#ifndef PIN_LED
#  define PIN_LED               hw_pin_7
#endif


/*  The counter used for PWM
 */
#define COUNTER                 hw_counter1
#define COUNTER_CLK_DIV         8


/*  PWM timings
 */
#define PWM_PERIOD              0.020000        /* 50 Hz */
#define PWM_TMIN                0               /* set to 0.000300 for servo */
#define PWM_TMAX                PWM_PERIOD      /* set to 0.003000 for servo */


/*  The analog input pin
 */
#if defined HW_DEVICE_ATTINYX4
#  define INPUT                 hw_pin_13
#elif defined ARDUINO
#  define INPUT                 PIN_A0
#else
#  define INPUT                 hw_pin_adc0
#endif


/*  Clock divider for the ADC
 */
#define ADC_CLK_DIV             128     /* T=~13*128/8=208 µs @8MHz */


/*  Top value and range of duty value according to PWM timings
 */
#define count_t                 hw_rt(COUNTER,count)
#define COUNT_TOP               (uint32_t)(hw_syshz*PWM_PERIOD/COUNTER_CLK_DIV)
#define COMPARE_MIN             (count_t)(PWM_TMIN*hw_syshz/COUNTER_CLK_DIV)
#define COMPARE_MAX             (count_t)(PWM_TMAX*hw_syshz/COUNTER_CLK_DIV)


/*  Value to store in the compare unit (must be the same size as the count
 *  register)
 */
static volatile count_t         duty ;


/*  Service ADC "conversion completed" IRQ: compute duty
 *  Make the ISR interruptible so that counter IRQs are serviced promptly.
 */
HW_ISR( hw_adc0, isr_interruptible )
{
  /*  Get the new value
   */
  uint16_t adc = hw_read( hw_adc0 );

  /*  Low-pass filter
   */
  const uint8_t                 ns = 32 ;       /* # of samples   */
  static uint16_t               lpfsum ;        /* sum of samples */

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
  }
  else
    duty = tmp ;

  /*  Start a new conversion
   */
  hw_trigger( hw_adc0 );
}


/*  Service counter-overflow IRQ: turn the LED on and enable the compare IRQ
 *  that turns it off
 */
HW_ISR( COUNTER, overflow, isr_non_interruptible )
{
  /*  No need to protect access to duty since interrupts are not allowed */

  if ( duty ) {
    hw_write( PIN_LED, 1 );
    if ( duty < COUNT_TOP ) {
      hw_write( hw_sub(COUNTER, compare1), duty );
      hw_turn_irq( COUNTER, compare1, on );
    }
    else
      hw_turn_irq( COUNTER, compare1, off );
  }
  else {
    hw_write( PIN_LED, 0 );
    hw_turn_irq( COUNTER, compare1, off );
  }
}


/*  Service compare-match IRQ: turn the LED off
 *
 *  Note: if the address of the port register is < 0x40 (assembler 0x20) we can
 *  spare a few bytes and have a faster code with a naked ISR.
 */
#if hw_addr(hw_reg(hw_sup(PIN_LED), port)) < 0x40
HW_ISR( COUNTER, compare1, isr_naked )
{
  hw_write( PIN_LED, 0 );
  hw_asm("reti");
}
#else
HW_ISR( COUNTER, compare1 )
{
  hw_write( PIN_LED, 0 );
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
  hwa_config( hw_core0,
              sleep,      enabled,
              sleep_mode, idle
              );

  /*  Configure LED pin
   */
  hwa_config( PIN_LED,
              direction, output
              );

  /*  Configure INPUT pin in analog mode (disable digital input buffer)
   */
  hwa_config( INPUT,
              mode,      analog,
              direction, input,
              pullup,    on
              );

  /*  Check that the counter can handle the top value. This must be done
   *  here since the C preprocessor does not allow floats in expressions.
   */
  if ( COUNT_TOP > ((1UL<<hw_bn(COUNTER))-1) )
    HWA_ERR("PWM_COUNTER can not afford PWM_PERIOD.") ;

  /*  Configure the counter to overflow periodically and trigger an interrupt
   *  The counter overflow ISR manages the compare IRQ
   */
  hwa_config( COUNTER,
              clock,     HW_G2(syshz_div, COUNTER_CLK_DIV),
              countmode, loop_up,
              bottom,    0,
              top,       compare0,
              overflow,  at_top,
              );
  hwa_write( hw_sub(COUNTER, compare0), COUNT_TOP );
  hwa_turn_irq( COUNTER, overflow, on );

  /*  Configure the ADC to make a single conversion and trigger an
   *  IRQ. The ISR will start a new conversion after its hard job is done.
   */
  hwa_config( hw_adc0,
              clock,   HW_G2(syshz_div, ADC_CLK_DIV),
              trigger, manual,
              vref,    vcc,
              align,   right,
              input,   INPUT,
              );
  hwa_turn_irq( hw_adc0, on );
  hwa_trigger( hw_adc0 );

  /*  Write this configuration into the hardware
   */
  hwa_commit();

  hw_enable_interrupts();

  for(;;)
    hw_sleep();

  return 0 ;
}
