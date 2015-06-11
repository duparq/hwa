#ifndef CONFIG_H
#define CONFIG_H

/*
 *  NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohms.
 */
#define hw_swuart0_pin_tx               DIABOLO_PIN_TX
#define hw_swuart0_pin_rx               DIABOLO_PIN_RX
#define hw_swuart0_autosync             sync_5_1
#define hw_swuart0_counter              hw_counter1
#define hw_swuart0_counter_clk_div      1
#define hw_swuart0_counter_compare      compare0

#define UART                            hw_swuart0


/*  Include the target board (and device) definitions
 */
#if !defined BOARD_H
#  define BOARD_H                       <boards/attiny84.h>
#endif

#include BOARD_H

#endif
