#ifndef CONFIG_H
#define CONFIG_H

#define HW_SWUART0_PIN_TX		DIABOLO_PIN_TX
#define HW_SWUART0_PIN_RX		DIABOLO_PIN_RX
#define HW_SWUART0_AUTOSYNC		5_1
#define HW_SWUART0_COUNTER		hw_counter1
#define HW_SWUART0_COUNTER_CLK_DIV	1
#define HW_SWUART0_COUNTER_COMP		compare0

#define HW_SWUART1_PIN_TX		hw_pin_8
#define HW_SWUART1_PIN_RX		hw_pin_8
#define HW_SWUART1_AUTOSYNC		5_1
#define HW_SWUART1_COUNTER		hw_counter1
#define HW_SWUART1_COUNTER_CLK_DIV	1
#define HW_SWUART1_COUNTER_COMP		compare1

#include <boards/attiny84.h>

#endif
