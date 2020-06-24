#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/ext/swuarta.h>

#define UART0			HW_SWUARTA( txd,      DIABOLO_PIN_TX,	\
					    rxd,      DIABOLO_PIN_RX,	\
					    startirq, (DIABOLO_PIN_RX,port,pcic,irq), \
					    counter,  counter1,		\
					    compare,  compare0,		\
					    clkdiv,   1,		\
					    autosync, 51,		\
					    fastreg,  (shared,gpior0) )

#define UART1			HW_SWUARTA( txd,      PIN_TX2,		\
					    rxd,      PIN_RX2,		\
					    startirq, (PIN_RX2,port,pcic,irq), \
					    counter,  counter1,		\
					    compare,  compare1,		\
					    clkdiv,   1,		\
					    autosync, 51,		\
					    fastreg,  (shared,gpior1) )

HW_DECLARE(UART0);
HW_DECLARE(UART1);

#endif
