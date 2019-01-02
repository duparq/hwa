
#define HW_BOARD			nanodccduino

/*  These are mostly the values as the board is shipped, except the bootsection
 *  size which is 1024 with Diabolo instead of 2048 with the Arduino bootloader.
 */
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

/*  Settings for building the Diabolo bootloader
 *  Settings for the Diabolo application are in the board's Makefile
 */
#define DIABOLO_PIN_RX			HW_PIN(rxd)
#define DIABOLO_PIN_TX			HW_PIN(txd)
#define DIABOLO_SYNC			5_1

/*  Board pins
 */
#define ARDUINO
#define NANODCCDUINO

#define PIN_D2				pd2	// PCINT18 INT0
#define PIN_D3				pd3	// PCINT19 OC2B INT1
#define PIN_D4				pd4	// PCINT20 T0
#define PIN_D5				pd5	// PCINT21 OC0B T1
#define PIN_D6				pd6	// PCINT22 OC0A AIN0
#define PIN_D7				pd7	// PCINT23 AIN1
#define PIN_D8				pb0	// PCINT0  ICP1
#define PIN_D9				pb1	// PCINT1  OC1A
#define PIN_D10				pb2	// PCINT2  OC1B SS
#define PIN_D11				pb3	// PCINT3  OC2A MOSI
#define PIN_D12				pb4	// PCINT4  MISO
#define PIN_D13				pb5	// PCINT5  SCK

#define PIN_A0				pc0	// PCINT8
#define PIN_A1				pc1	// PCINT9
#define PIN_A2				pc2	// PCINT10
#define PIN_A3				pc3	// PCINT11
#define PIN_A4				pc4	// PCINT12 SDA
#define PIN_A5				pc5	// PCINT13 SCL
#define PIN_RST				pc6	// PCINT14 RESET
#define PIN_A6				adc6
#define PIN_A7				adc7

#define LED				fake

#include <hwa/atmega328p_au.h>
