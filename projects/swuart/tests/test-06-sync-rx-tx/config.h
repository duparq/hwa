#ifndef CONFIG_H
#define CONFIG_H

//#define HW_XSOHZ		16000000UL

/*	The name of the RX pin determines the interrupt used as the start condition
 *
 *	NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohm.
 */
#define SWUART_PIN_TX		hw_pin_pcint8
#define SWUART_PIN_RX		hw_pin_pcint8

/* #define SWUART_PIN_TX		hw_pin_int0 */
/* #define SWUART_PIN_RX		hw_pin_int0 */

/* #define SWUART_PIN_TX		hw_pin_ain1 */
/* #define SWUART_PIN_RX		hw_pin_ain1 */

#define SWUART_PIN_DBG		hw_pin_6
#define SWUART_COUNTER		hw_counter0
#define SWUART_COUNTER_CLOCK	syshz
#define SWUART_COUNTER_MATCH	compare_a	// Compare-match interrupt used for bit rx/tx
#define SWUART_BPS		100000

#define PIN_DBG			hw_pin_7

#endif
