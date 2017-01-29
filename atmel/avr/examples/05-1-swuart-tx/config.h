#ifndef CONFIG_H
#define CONFIG_H

/*  The UART and its baudrate
 *  Use software UART hw_swuart0 for devices that do not have a hardware UART
 */
#define UART				hw_swuart0
#define BPS				115200

/*  The configuration of the software UART must be defined before the
 *  HWA header is included
 */
#define hw_swuart0_pin_txd		DIABOLO_PIN_TX
#define hw_swuart0_compare		hw_counter0compare0
#define hw_swuart0_clk_div		1

/*  Include target board + device + HWA definitions
 */
#include BOARD_H

/*  Remove definitions for hw_swuart0 if it is not the chosen UART to avoid
 *  including useless code
 */
#if HW_ID(UART) != HW_ID(hw_swuart0)
#  undef hw_swuart0_pin_txd
#  undef hw_swuart0_compare
#  undef hw_swuart0_clk_div
#endif

#endif
