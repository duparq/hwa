
/*  Blink a LED using a software delay loop.
 *
 *  HW_DEVICE contains the target name. It is extended with the package name so
 *  that pin numbers can be used as well as pin names.
 *
 *  hw_syshz is the number of CPU cycles per second. This is computed by HWA
 *  according to the target name and its declared configuration.
 */

#define HW_DEVICE			atmega328p, 32MLF
#define	LED_PIN				hw_pin_17
#define HW_DEVICE_BOOT			bootloader
#define HW_DEVICE_BOOTSECTION_SIZE	1024
#define HW_DEVICE_STARTUP_DELAYS	16KCK_14CK_64ms
#define HW_DEVICE_CLK_SRC		external_low_power_xo
#define HW_DEVICE_CLK_HZ		16000000
#define HW_DEVICE_CLK_PSC		1
#define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV

#define PERIOD				0.5

#include <hwa.h>


int main ( )
{
  hw_config( LED_PIN, direction, output );
  hw_config( LED_PIN,
	     direction, input,
	     pullup, 	on );

  for(;;) {
    hw_toggle( LED_PIN );
    hw_delay_cycles( PERIOD*hw_syshz/2 );
  }

  return 0 ;
}
