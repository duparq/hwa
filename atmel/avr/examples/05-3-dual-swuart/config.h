#ifndef CONFIG_H
#define CONFIG_H

/*  The configuration of the software UART must be defined before including the
 *  HWA header
 */
#define hw_swuart0_pin_txd              DIABOLO_PIN_TX
#define hw_swuart0_pin_rxd              DIABOLO_PIN_RX
#define hw_swuart0_compare		hw_counter1compare0
#define hw_swuart0_clk_div		1
#define hw_swuart0_autosync             sync_5_1

#define hw_swuart1_pin_txd              PIN_TX2
#define hw_swuart1_pin_rxd              PIN_RX2
#define hw_swuart1_compare		hw_counter1compare1
#define hw_swuart1_clk_div		1
#define hw_swuart1_autosync             sync_5_1

#include BOARD_H

#endif
