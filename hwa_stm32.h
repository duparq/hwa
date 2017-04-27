#ifndef HWA_STM32_H
#define HWA_STM32_H

/*	HWA main header for ST STM32
 */
#define HWA_DEVICE_STM32


/*	ARM Cortex-M3 specific definitions
 */
#define HWA_PERIPH			0x40000000
#define HWA_APB1			HWA_PERIPH+0x00000000 /* 0x40000000 */
#define HWA_APB2			HWA_PERIPH+0x00010000 /* 0x40010000 */
#define HWA_AHB				HWA_PERIPH+0x00018000 /* 0x40018000 */


/*	Load from modules
 */
#include "hwa_stm32_clock.h"
#include "hwa_stm32_flash.h"
#include "hwa_stm32_prph.h"
#include "hwa_stm32_gpio.h"
#include "hwa_stm32_spi.h"
#include "hwa_stm32_timer.h"
#include "hwa_stm32_irq.h"


/*	Init HWA structure
 */
#define hwa_begin_device(reset)			\
  hwa_begin_clock(reset);			\
  hwa_begin_flash(reset);			\
  hwa_begin_prph(reset);			\
  hwa_begin_gpio(reset);			\
  hwa_begin_spi(reset);				\
  hwa_begin_timer(reset);			\
  hwa_begin_irq(reset);


/*	In this order:
 *
 *	* system clocks configuration
 *	* peripheral clocks
 *	* gpio configuration
 */
#define hwa_commit_device()			\
  do {						\
    hwa_commit_clock();				\
    hwa_commit_flash();				\
    hwa_commit_prph();				\
    hwa_commit_gpio();				\
    hwa_commit_spi();				\
    hwa_commit_timer();				\
    hwa_commit_irq();				\
  } while(0)

#endif
