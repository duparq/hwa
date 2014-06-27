#ifndef CONFIG_H
#define CONFIG_H

//#define HW_XSOHZ		14745600UL
#define HW_XSOHZ		16000000UL

#define SWUART_PIN_RX		PIN_INT0
#define SWUART_PIN_TX		PIN_PD3
#define SWUART_PIN_DBG		PIN_PB0
#define SWUART_TIMER		hw_timer2
#define SWUART_TIMER_CLKHZ	syshz
#define SWUART_TIMER_MATCH	match_a
#define SWUART_BPS		100000

#define MS_TIMER		hw_timer0
#define MS_TIMER_CLK		syshz_div_64

#define UART			hw_usart0
#define UART_BPS		230400
#endif
