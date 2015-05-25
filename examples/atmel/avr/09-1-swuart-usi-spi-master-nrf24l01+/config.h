#ifndef CONFIG_H
#define CONFIG_H

/*
 *  NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohm.
 */
#define HW_SWUART0_PIN_TX		DIABOLO_PIN_TX
#define HW_SWUART0_PIN_RX		DIABOLO_PIN_RX
#define HW_SWUART0_AUTOSYNC		5_1
#define HW_SWUART0_COUNTER		hw_counter1
#define HW_SWUART0_COUNTER_CLK_DIV	1
#define HW_SWUART0_COUNTER_COMP		compare0
#define UART				hw_swuart0

#include <boards/attiny84.h>

#endif
