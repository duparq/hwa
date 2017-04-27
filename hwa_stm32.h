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
#include "hwa_stm32_rcc.h"
#include "hwa_stm32_systick.h"
#include "hwa_stm32_timer.h"
#include "hwa_stm32_uart.h"

#endif
