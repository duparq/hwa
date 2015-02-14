
#define HW_DEVICE			attiny85, 8pdip
#define HW_DEVICE_CLK_SRC		rc_8MHz
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_SELF_PROGRAMMING	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled

/*	Settings for Diabolo
 */
//#define DIABOLO_PIN_RX			hw_pin_rxd
//#define DIABOLO_PIN_TX			hw_pin_txd
#define DIABOLO_BPS			115200
#define DIABOLO_RESET_SIGNAL		DTR

#define	PIN_LED				hw_pin_5
