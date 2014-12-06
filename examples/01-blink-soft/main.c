
/*  Blink a LED at ~5 Hz using a software delay loop.
 *
 *  HW_DEVICE contains the target name and its package so that pin numbers
 *  can be used as well as pin names.
 *
 *  hw_syshz is the number of CPU cycles per second. This is defined by HWA
 *  according to the target name and its fuses values.
 */

/**
 *  See @ref HW_DEVICE
 */

#define HW_DEVICE		attiny84, dil

#define	LED_PIN			hw_pin_7
#define PERIOD			0.2

#include <hwa.h>


int main ( )
{
  hw_config( LED_PIN, output );

  for(;;) {
    hw_toggle( LED_PIN );
    hw_delay_cycles( PERIOD*hw_syshz/2 );
  }

  return 0 ;
}
