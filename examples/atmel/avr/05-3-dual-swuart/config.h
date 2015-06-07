#ifndef CONFIG_H
#define CONFIG_H

/*  The configuration of the software UART must be defined before including the
 *  HWA header
 */
#define hw_swuart0_pin_tx               DIABOLO_PIN_TX
#define hw_swuart0_pin_rx               DIABOLO_PIN_RX
#define hw_swuart0_autosync             sync_5_1
#define hw_swuart0_counter              hw_counter1
#define hw_swuart0_counter_clk_div      1
#define hw_swuart0_counter_compare      compare0

#define hw_swuart1_pin_tx               hw_pin_8
#define hw_swuart1_pin_rx               hw_pin_8
#define hw_swuart1_autosync             sync_5_1
#define hw_swuart1_counter              hw_counter1
#define hw_swuart1_counter_clk_div      1
#define hw_swuart1_counter_compare      compare1

/*  Include the target board (and device) definitions
 */
#if !defined BOARD_H
#  define BOARD_H                       <boards/attiny84.h>
#endif

#include BOARD_H

#endif
