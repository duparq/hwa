#ifndef CONFIG_H
#define CONFIG_H

//#define HW_XSOHZ		16000000UL

#define SWUART_PIN_TX		hw_pin_pb1
#define SWUART_PIN_DBG		hw_pin_pb0
#define SWUART_COUNTER		hw_counter0
#define SWUART_COUNTER_CLOCK	syshz
#define SWUART_COUNTER_MATCH	match_a		// Compare-match interrupt used for bit rx/tx
#define SWUART_BPS		100000

#endif
