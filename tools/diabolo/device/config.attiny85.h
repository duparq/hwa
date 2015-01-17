
/*	Configuration for Diabolo
 */	

#define HW_DEVICE	attiny85, 8pdip	/* Also define the package so that */
#define PIN_TXD		hw_pin_2	/* pin numbers can be used.        */
#define PIN_RXD		hw_pin_2
//#define PIN_DBG		hw_pin_3

#define HW_DEVICE_CLK_SRC		rc_8MHz
//#define HW_DEVICE_CLK_HZ		8000000
#define HW_DEVICE_CLK_PSC		1
//#define HW_DEVICE_STARTUP_DELAYS	6CK_14CK_4ms
//#define HW_DEVICE_STARTUP_DELAYS	16KCK_14CK_64ms
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV
//#define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV
#define HW_DEVICE_SELF_PROGRAMMING	enabled
