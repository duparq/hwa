
/*	Configuration for Diabolo
 */	

#define HW_DEVICE			atmega328p, 32MLF
#define HW_DEVICE_BOOT			bootloader
#define HW_DEVICE_BOOTSECTION_SIZE	1024

#define HW_DEVICE_CLK_SRC		external_low_power_xo
#define HW_DEVICE_CLK_HZ		8000000
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_STARTUP_DELAYS	16KCK_14CK_64ms
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV

#define PIN_RXD				hw_pin_30
#define PIN_TXD				hw_pin_30

//#define PIN_DBG				hw_pin_17

/*  Define XSPEED to have OSCCAL set at 0xFF (max speed) between programmings
 */
//#define XSPEED
