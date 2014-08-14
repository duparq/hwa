
/*	Configuration for Diabolo
 */	

#define HW_DEVICE	attiny84, dil	/* Also define the package so that */
#define PIN_TXD		hw_pin_2	/* pin numbers can be used.        */
#define PIN_RXD		hw_pin_2

/*	1 to change OSCCAL to 0xFF between programmings
 *	0 to leave OSCCAL with its default value
 */
#define X_SPD		0
