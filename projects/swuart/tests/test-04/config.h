#ifndef CONFIG_H
#define CONFIG_H

#define HW_XSOHZ		16000000UL

#define SWUART_PIN_RX		PIN_INT0	/*  4 */
#define SWUART_PIN_TX		PIN_PD3		/*  5 */
#define SWUART_PIN_DBG		PIN_PD4		/*  6 */
#define SWUART_TIMER		hw_timer0
#define SWUART_TIMER_CLKHZ	syshz
#define SWUART_TIMER_MATCH	match_a
/* #define SWUART_BPS		115200 */
#define SWUART_BPS		100000

#define TIMER			hw_timer2
#define PIN_DBG			PIN_PB0		/* 14 */

#endif
