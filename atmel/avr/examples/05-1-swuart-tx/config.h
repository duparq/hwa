
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include BOARD_H

#include <hwa/swuarta.h>

#define UART			HW_SWUART( txd,       DIABOLO_PIN_TX,	\
					   counter,   counter0,		\
					   compare,   compare0,		\
					   clkdiv,    1,		\
					   autosync,  51,		\
					   fastreg,   (shared,gpior0) )

HW_DECLARE(UART);

#define BPS			115200

#endif
