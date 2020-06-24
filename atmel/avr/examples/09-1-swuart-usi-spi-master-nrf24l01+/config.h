#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/ext/swuarta.h>

/*
 *  NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohms.
 */
#define UART			HW_SWUARTA( txd,      DIABOLO_PIN_TX,	\
					    rxd,      DIABOLO_PIN_RX,	\
					    startirq, (DIABOLO_PIN_RX,port,pcic,irq), \
					    counter,  counter1,		\
					    compare,  compare0,		\
					    clkdiv,   1,		\
					    autosync, 51,		\
					    fastreg,  (shared,gpior0) )

HW_DECLARE(UART);

#endif
