
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/swuarta.h>

/*
 *  NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohms.
 */
#define UART			HW_SWUART( txd,      DIABOLO_PIN_TX,	\
					   rxd,      DIABOLO_PIN_RX,	\
					   startirq, (DIABOLO_PIN_RX,pcic,irq), \
					   counter,  counter1,		\
					   compare,  compare0,		\
					   clkdiv,   1,		\
					   autosync, 51,		\
					   fastreg,  (shared,gpior0) )

HW_DECLARE(UART);

#define COUNTER			counter1
#define CAPTURE			(counter1,capture0)
#define COMPARE			(counter1,compare1)

#endif
