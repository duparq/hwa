
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
  /*	Configure hardware
   */
  hwa_begin_from_reset();
  swuart_configure(hwa);
  hwa_config(PIN_DBG, output);
  hwa_write(PIN_DBG, 0);

  hwa_config( hw_counter1,
	      clock,		syshz,
	      countmode,	loop_up,
	      top,		compare_a );

  hwa_write_bits( hw_counter1, compare_a, 0xFFFF) ;

  hwa_config( hw_oc1b,	set_at_bottom_clear_on_match );

  hwa_config( hw_ic1a,
	      input,	pin_icp,
	      edge,	rising );

  hwa_commit();

  /*	Synchronize UART
   */
  swuart_set_dt( swuart_sync_10_1() );
  swuart_wait_rxidle(20);
  hw_write(PIN_DBG, 1);

  /*	Put prompt
   */
  hw_enable_irqs();
  swuart_putbyte('#');
  swuart_enable_rx();

  /*	Return received characters with a leading '>'
   */
  for(;;) {
    uint8_t c = swuart_rx();    
    hw_toggle( PIN_DBG );
    swuart_putbyte('>');
    swuart_putbyte(c);
  }
}
