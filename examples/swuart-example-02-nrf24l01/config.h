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
#define SWUART_COUNTER		hw_counter1
#define SWUART_COUNTER_PSC	1
#define SWUART_COUNTER_MATCH	compare_a


/*	Use USI as SPI master with software-managed clocking
 */
#define SPI			hw_usi0_spimaster_swclk


/*	SPI slave (nRF24L01+) connections
 */
#define NRF_CE			hw_pin_10
#define NRF_CSN			hw_pin_11


/*	Debug pin
 */
#define DBG_PIN			hw_pin_12

#endif
