
/*  Blink a LED using a software delay loop.
 *
 *  HW_DEVICE contains the target name. It is extended with the package name so
 *  that pin numbers can be used as well as pin names.
 *
 *  hw_syshz is the number of CPU cycles per second. This is computed by HWA
 *  according to the target name and its declared configuration.
 */

//#include "config.attiny84.h"
//#include "config.attiny85.h"
#include "boards/nanodccduino.h"
#include <hwa.h>

//#undef HW_DEVICE

#define PERIOD				0.5


int main ( )
{
  hw_config( PIN_LED, direction, output );

  for(;;) {
    hw_toggle( PIN_LED );
    hw_delay_cycles( PERIOD*hw_syshz/2 );
  }

  return 0 ;
}
