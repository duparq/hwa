
/*	Send '.' on TXD
 *
 *	miniterm.py -p /dev/ttyUSB1 -b 115200
 */

#include "config.h"
#include <hwa.h>
#include <swuart.h>


int
main ( )
{
  hwa_begin_from_reset();
  swuart_hwa();
  hwa_commit();

  swuart_set_dt(hw_syshz / SWUART_BPS);

  hw_enable_irqs();

  for(;;) {
    hw_loop( hw_syshz / 10 );
    swuart_putbyte('.');
  }
}
