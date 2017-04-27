#ifndef HWA_ATTINY45_H
#define HWA_ATTINY45_H

/*	HWA main header for Atmel AVR
 */
#define HWA_DEVICE_ATTINY45


#include "hwa_attiny45_core.h"
#include "hwa_attiny45_gpio.h"
#include "hwa_attiny45_irq.h"
#include "hwa_attiny45_timer.h"
#include "hwa_attiny45_usart.h"
#include "hwa_attiny45_adc.h"
#include "hwa_attiny45_acmp.h"
#include "hwa_attiny45_exti.h"
#include "hwa_attiny45_pchg.h"
#include "hwa_attiny45_watchdog.h"

#define hw_enable_interrupts()		__asm__ __volatile__ ("sei" ::)
#define hw_disable_interrupts()		__asm__ __volatile__ ("cli" ::)


#define hwa_begin_device(state)			\
  hwa_begin_core(state);			\
  hwa_begin_gpio(state);			\
  hwa_begin_timer(state);			\
  hwa_begin_usart(state);			\
  hwa_begin_acmp(state);			\
  hwa_begin_adc(state);				\
  hwa_begin_pchg(state);			\
  /* hwa_begin_watchdog(state); */


#define hwa_commit_device()			\
  hwa_commit_gpio();				\
  hwa_commit_timer();				\
  hwa_commit_usart();				\
  hwa_commit_acmp();				\
  hwa_commit_adc();				\
  hwa_commit_pchg();				\
  hwa_commit_core();				\

  /* hwa_commit_watchdog(); */


#endif
