
/*  This file is part of the HWA project.
 *  Copyright (c) Christophe Duparquet <duparq at free dot fr>
 *  All rights reserved. Read LICENSE.TXT for details.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <targets/attiny84.h>

#define HW_SWUART0_PIN_TX               DIABOLO_PIN_TX
#define HW_SWUART0_PIN_RX               DIABOLO_PIN_RX
#define HW_SWUART0_AUTOSYNC             5_1
#define HW_SWUART0_COUNTER              hw_counter1
#define HW_SWUART0_COUNTER_CLK_DIV      1
#define HW_SWUART0_COUNTER_COMP         compare0

#endif
