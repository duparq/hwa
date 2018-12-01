
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#ifndef CONFIG_H
#define CONFIG_H

#define hw_swuart0_pin_txd		DIABOLO_PIN_TX
#define hw_swuart0_pin_rxd		DIABOLO_PIN_RX
#define hw_swuart0_starter		(DIABOLO_PIN_RX,pcic)
#define hw_swuart0_compare		counter1compare0
#define hw_swuart0_clk_div		1
#define hw_swuart0_autosync		5_1

#define UART				swuart0

#define COUNTER				counter1
#define CAPTURE				counter1capture0
#define COMPARE				counter1compare1

/*  Include the target board (and device) definitions
 */
#include BOARD_H

#endif
