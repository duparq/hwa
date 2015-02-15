
/*	These are mostly the values as the board was shipped, except
 *	the bootsection size which is 1024 instead of 2048.
 */
#define HW_DEVICE			atmega328p, 32MLF
#define HW_DEVICE_BOOT			bootloader
#define HW_DEVICE_BOOTSECTION_SIZE	1024

#define HW_DEVICE_CLK_SRC		low_power_xosc
#define HW_DEVICE_CLK_SRC_HZ		16000000
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_STARTUP_DELAYS	16KCK_14CK_64ms
#define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV
#define HW_DEVICE_SELF_PROGRAMMING	enabled

#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled

/*	Settings for Diabolo
 */
#define DIABOLO_PIN_RX			hw_pin_rxd
#define DIABOLO_PIN_TX			hw_pin_txd
#define DIABOLO_BPS			230400
#define DIABOLO_RESET_SIGNAL		DTR

#define	PIN_LED				hw_pin_pb5
