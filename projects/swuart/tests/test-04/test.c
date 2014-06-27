
/*	test-02 modified
 *
 *	RX on swuart @ 115200 bps -> TX on UART @ 230400 bps
 */

#include "config.h"
#include "swuart/swuart.h"

#define UART			hw_usart0
#define UART_BPS		230400


static char i2h ( uint8_t i )
{
  char c = '0'+i ;
  if ( c > '9' )
    c += 'A'-'9'-1 ;
  return c ;
}


static void uart_tx ( char c )
{
  while ( !hw_read(UART, txqnf) ) {}
  hw_write( UART, data, c );
}


static void uart_tx_2h ( uint8_t n )
{
  uart_tx(i2h(n>>4));
  uart_tx(i2h(n&0x0F));
}

int
main ( )
{
  hwa_begin(reset);
  swuart_hwa();
  hwa_config( UART, rxtx, UART_BPS, noparity, 8bits, 1stop );
  hwa_config( PIN_DBG, output );
  hwa_connect_clock( TIMER, syshz_div_64 );

  hwa_commit();

  swuart_set_dt(hw_syshz() / SWUART_BPS);

  swuart_enable_rx();

  hw_enable_interrupts();

  hw_write( PIN_DBG, 1 );

  for(;;) {
  next:
    hw_write( TIMER, match_b, hw_read(TIMER, count)+40 ); /* 100 µs */
    hw_write( TIMER, flag_match_b, 1 );
    while ( !hw_read(TIMER, flag_match_b) ) {
      if ( swuart_is_busy() ) {
	uint8_t b = swuart_rx();
	hw_write( PIN_DBG, 0 );
	uart_tx_2h(b);
	hw_write( PIN_DBG, 1 );
	goto next ;
      }
    }
    hw_toggle( PIN_DBG );
  }
}
