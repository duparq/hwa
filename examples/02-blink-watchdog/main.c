
/*	Blink a LED at ~2 Hz using watchdog interrupt requests (without
 *	servicing) and status flag
 */

//#include "config.attiny85.h"
#include "config.nanodccduino.h"
#include <hwa.h>


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( PIN_LED, direction, output );
  hwa_config( hw_watchdog0,
  	      timeout,		250ms,
  	      action,		irq );
  hwa_commit();

  for(;;) {
    if ( hw_stat( hw_watchdog0 ).irq ) {
    /* hw_status_t( hw_watchdog0 ) s ; */
    /* s = hw_status( hw_watchdog0 ) ; */
    /* if ( s.irq ) { */
      hw_clear_irq( hw_watchdog0 );
      hw_toggle( PIN_LED );
    }
  }
    
  return 0 ;
}
