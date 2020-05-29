#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/swuarta.h>

#define UART			HW_SWUART( txd,      DIABOLO_PIN_TX,	\
					   rxd,      DIABOLO_PIN_RX,	\
					   startirq, (DIABOLO_PIN_RX,pcic,irq), \
					   counter,  counter1,		\
					   compare,  compare0,		\
					   clkdiv,   1,		\
					   autosync, 51,		\
					   fastreg,  (shared,gpior0) )

HW_DECLARE(UART);

#endif
