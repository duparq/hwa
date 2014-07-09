#ifndef CONFIG_H
#define CONFIG_H

/*	The name of the RX pin determines the interrupt used to detect the start
 *	condition
 *
 *	DO NOT LEAVE THE RX PIN FLOATING! Fix-it to high level through 10 kohm.
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
