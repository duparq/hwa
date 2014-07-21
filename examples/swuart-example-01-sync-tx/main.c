
/*	Synchronize SWUART, then send '#' every period of 250 bytes
 *
 *	Tested with:
 *        ATtiny84 @8MHz internal oscillator:
 *		hw_counter0 PSC=1 compare_a/b 38400..115200 bps
 *		hw_counter1 PSC=1 compare_a/b 2400..115200 bps
 *
 *	Try it: ./talker.py
 */

#include "config.h"
#include <hwa.h>
#include <swuart-src.h>


int
main ( )
{
  hwa_begin_from_reset();

  swuart_configure(hwa);

  hwa_commit();

  /*	Synchronize
   */
  swuart_dt_t dt = swuart_sync_10_1();
  swuart_set_dt( dt );

  /*	Wait end of sync byte
   */
  swuart_wait_rxidle(20);

  /*	Send '#'
   */
  for(;;) {
#if defined SWUART_DBG_PIN
    hw_toggle( SWUART_DBG_PIN );
#endif
    swuart_putbyte('#');
    swuart_wait_rxidle(249);
  }
}
