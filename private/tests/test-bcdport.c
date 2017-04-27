
/*  Include the HWA definitions for the target device
 */
#include <hwa/attiny84a_pu.h>

/*  Create a HWA object named 'bcdport' as a set of 4 consecutive pins of port0:
 *  PA5,PA4,PA3,PA2
 */
#define _hw_def_bcdport         _io1a, 0, port0, 4, 2


int main ( )
{
  /*  Configure the 'bcdport' pins as digital (default) outputs.
   */
  hw( configure, bcdport, direction, output );

  /*  Write BCD digits on the 'bcdport' output pins.
   */
  for ( uint8_t i ; ; i++ )
    hw( write, bcdport, i & 0x0F );
}
