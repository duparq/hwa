#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/swuarta.h>

#define UART0			HW_SWUART( txd,       DIABOLO_PIN_TX,	\
					   rxd,       DIABOLO_PIN_RX,	\
					   counter,   counter1,		\
					   compare,   compare0,		\
					   clkdiv,    1,		\
					   autosync,  51,		\
					   fastreg,   (shared,gpior0) )

#define UART1			HW_SWUART( txd,       PIN_TX2,		\
					   rxd,       PIN_RX2,		\
					   counter,   counter1,		\
					   compare,   compare1,		\
					   clkdiv,    1,		\
					   autosync,  51,		\
					   fastreg,   (shared,gpior1) )

HW_DECLARE(UART0);
HW_DECLARE(UART1);

#endif
