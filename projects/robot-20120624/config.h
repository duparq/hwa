#ifndef CONFIG_H
#define CONFIG_H

#define PIN_DBG			hw_pin_pb1
#define	SWUART			0

#define SWUART_PIN_RX		hw_pin_pcint8	// Also determines interrupt used
#define SWUART_PIN_TX		hw_pin_pcint8
//#define SWUART_PIN_DBG		PIN_PB1

#define SWUART_TIMER		hw_timer1
#define SWUART_TIMER_CLKHZ	SYSHZ
#define SWUART_TIMER_MATCH	A		// Compare-match interrupt used for bit rx/tx

#define TIMER			SWUART_TIMER
#define TIMER_CLKHZ		SWUART_TIMER_CLKHZ

//#define SWUART_MATCH		16
//#define SWUART_CALLBACK		swuart_cb
//#define SWUART_CALLBACK_PTR	swuart_cb

#endif
