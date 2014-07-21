#ifndef CONFIG_H
#define CONFIG_H

/*	SWUART configuration.
 *
 *	The name of the RX pin determines the interrupt used to detect the start
 *	condition.
 *
 *	NOTE: do not leave the RX pin floating. Fix-it to high level through 10 kohm.
 */
#define SWUART_PIN_TX		hw_pin_pcint8
#define SWUART_PIN_RX		hw_pin_pcint8
#define SWUART_COUNTER		hw_counter0
#define SWUART_COUNTER_PSC	1
#define SWUART_COUNTER_MATCH	compare_a

#endif
