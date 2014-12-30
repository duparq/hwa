
/*  Blink a LED using a software delay loop.
 *
 *  HW_DEVICE contains the target name and its package so that pin numbers
 *  can be used as well as pin names.
 *
 *  hw_syshz is the number of CPU cycles per second. This is defined by HWA
 *  according to the target name and its fuses values.
 */

//#define HW_DEVICE			attiny84, dil
//#define	LED_PIN				hw_pin_2

#define HW_DEVICE			atmega328p, 32MLF
#define	LED_PIN				hw_pin_17
/* #define HW_DEVICE_CLK_SRC		internal_rc */
/* #define HW_DEVICE_CLK_HZ		8000000 */
/* #define HW_DEVICE_CLK_PSC		1 */
/* #define HW_DEVICE_STARTUP_DELAYS	6CK_14CK_64ms */
/* #define HW_DEVICE_BROWNOUT_DETECTION	4100_4500mV */

#define PERIOD				0.5

#include <hwa.h>


int main ( )
{
  /* hwa_begin_from_reset(); */
  /* hwa_config( hw_core0, */
  /* 	      entering_sleep,	enabled, */
  /* 	      sleep_mode,	idle */
  /* 	      ); */
  /* hwa_commit(); */
  /* hw_sleep_until_irq(); */

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
