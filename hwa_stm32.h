#ifndef HWA_STM32_H
#define HWA_STM32_H

/*	ARM Cortex-M3 specific definitions
 */
#define HWA_PTR_PERIPH			0x40000000
#define HWA_PTR_APB1			HWA_PTR_PERIPH+0x00000000 /* 0x40000000 */
#define HWA_PTR_APB2			HWA_PTR_PERIPH+0x00010000 /* 0x40010000 */
#define HWA_PTR_AHB			HWA_PTR_PERIPH+0x00018000 /* 0x40018000 */
//#define HWA_AHB_PTR			0x40080000

#define HWA_PTR_SCB			0xE000ED00
#define HWA_PTR_SCB_VTOR		((volatile u32 *)(HWA_PTR_SCB+8)) /* 0xE000ED08 */

#include "hwa_stm32_flash.h"
#include "hwa_stm32_gpio.h"
#include "hwa_stm32_irq.h"
#include "hwa_stm32_pwr.h"
#include "hwa_stm32_rcc.h"
#include "hwa_stm32_rtc.h"
#include "hwa_stm32_spi.h"
#include "hwa_stm32_systick.h"
#include "hwa_stm32_timer.h"
#include "hwa_stm32_uart.h"

#define _hwa_begin(state)						\
  hwa_flash_begin(HWA_BEGIN_STATE_##state);				\
  hwa_gpio_begin(HWA_BEGIN_STATE_##state);				\
  hwa_irq_begin(HWA_BEGIN_STATE_##state);				\
  hwa_pwr_begin(HWA_BEGIN_STATE_##state);				\
  hwa_rcc_begin(HWA_BEGIN_STATE_##state);				\
  hwa_rtc_begin(HWA_BEGIN_STATE_##state);				\
  hwa_spi_begin(HWA_BEGIN_STATE_##state);				\
  hwa_systick_begin(HWA_BEGIN_STATE_##state);				\
  hwa_timer_begin(HWA_BEGIN_STATE_##state);				\
  hwa_uart_begin(HWA_BEGIN_STATE_##state);

#define _hwa_commit()							\
  hwa_flash_commit();							\
  hwa_gpio_commit();							\
  hwa_irq_commit();							\
  hwa_pwr_commit();							\
  hwa_rcc_commit();							\
  hwa_rtc_commit();							\
  hwa_spi_commit();							\
  hwa_systick_commit();							\
  hwa_timer_commit();							\
  hwa_uart_commit();

#endif
