#ifndef CONFIG_H
#define CONFIG_H

#define hw_swuart0_pin_tx		DIABOLO_PIN_TX
#define hw_swuart0_pin_rx		DIABOLO_PIN_RX
#define hw_swuart0_autosync		sync_5_1
#define hw_swuart0_counter		hw_counter1
#define hw_swuart0_counter_clk_div	1
#define hw_swuart0_counter_compare	compare0

#define hw_swuart1_pin_tx		hw_pin_8
#define hw_swuart1_pin_rx		hw_pin_8
#define hw_swuart1_autosync		sync_5_1
#define hw_swuart1_counter		hw_counter1
#define hw_swuart1_counter_clk_div	1
#define hw_swuart1_counter_compare	compare1

#include <boards/attiny84.h>

#endif
