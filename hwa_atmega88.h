#ifndef HWA_ATMEGA88_H
#define HWA_ATMEGA88_H

/*	HWA main header for Atmel AVR
 */
#define HWA_DEVICE_ATMEGA88

#include "hwa_atmega88_gpio.h"
#include "hwa_atmega88_irq.h"
#include "hwa_atmega88_timer.h"
#include "hwa_atmega88_watchdog.h"

#define hw_enable_interrupts()		__asm__ __volatile__ ("sei" ::)
#define hw_disable_interrupts()		__asm__ __volatile__ ("cli" ::)

#define hwa_begin_device(state)			\
  hwa_begin_gpio(state);			\
  hwa_begin_timer(state);			\
  hwa_begin_watchdog(state);

#define hwa_commit_device()			\
  hwa_commit_gpio();				\
  hwa_commit_timer();				\
  hwa_commit_watchdog();

#endif
