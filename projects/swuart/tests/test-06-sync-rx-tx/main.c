
/*	swuart : synchronize, rx, tx
 *
 *	./talker.py -b 115200
 */

#include "config.h"
#include <hwa.h>
#include <swuart.h>


int
main ( )
{
  hwa_begin_from_reset();
  swuart_hwa(hwa);
  hwa_config(PIN_DBG, output);
  hwa_write(PIN_DBG, 0);
  hwa_commit();

  swuart_set_dt( swuart_sync_10_1() );

  swuart_wait_rxidle(20);
  hw_write(PIN_DBG, 1);

  hw_enable_irqs();
  swuart_putbyte('#');
  swuart_enable_rx();

  for(;;) {
    uint8_t c = swuart_rx();    
    hw_toggle( PIN_DBG );
    swuart_putbyte('>');
    swuart_putbyte(c);
  }
}
