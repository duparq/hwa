
/*	RX on swuart @ 115200 bps -> TX on UART @ 230400 bps
 */

#include "config.h"
#include "swuart/swuart.h"

int
main ( )
{
  hwa_begin(reset);
  swuart_hwa();
  hwa_config( hw_usart0, rxtx, 230400, noparity, 8bits, 1stop );
  hwa_commit();

  swuart_set_dt(hw_syshz() / SWUART_BPS);

  swuart_enable_rx();

  hw_enable_interrupts();

  for(;;) {
    uint8_t c = swuart_getbyte();
    hw_write(hw_usart0, data, c);
  }
}
