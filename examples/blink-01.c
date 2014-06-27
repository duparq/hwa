
/*	Blink a LED at ~5 Hz using a software delay loop.
 */

#include <hwa.h>

#define	LED		hw_pin_7

int main ( )
{
  hw_config( LED, output );

  for(;;) {
    hw_toggle( LED );
    hw_loop( hw_syshz/10 );
  }

  return 0 ;
}
