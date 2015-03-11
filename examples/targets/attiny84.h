
/*	Device configuration
 */
#define HW_DEVICE			attiny84
#define HW_DEVICE_PACKAGE		14pdip
#define HW_DEVICE_CLK_SRC		rc_8MHz
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_EXTERNAL_RESET	enabled
#define HW_DEVICE_SELF_PROGRAMMING	enabled
#define HW_DEVICE_DEBUG_WIRE		disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON	no
#define HW_DEVICE_CLOCK_OUTPUT		disabled
#define HW_DEVICE_BROWNOUT_DETECTION	2500_2900mV

/*	Settings for Diabolo
 */
#define DIABOLO_PIN_RX			pin_2
#define DIABOLO_PIN_TX			pin_2
#define DIABOLO_BPS			115200
#define DIABOLO_RESET_SIGNAL		DTR
