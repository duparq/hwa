
/*	Blink a LED at ~5 Hz using a software delay loop.
 */

#include <hwa.h>

#define	LED_PIN		hw_pin_7
#define PERIOD		0.2

int main ( )
{
  hw_config( LED_PIN, output );

  for(;;) {
    hw_toggle( LED_PIN );
    hw_nop_loop( PERIOD*hw_syshz/2 );
  }

  return 0 ;
}
