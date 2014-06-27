
/*	Yeahpad:	1 (noir)	GND
 *			2 (blanc)	TXD	(-> RXD contrôleur)
 *			3 (gris)	RXD	(-> TXD contrôleur)
 *
 *	PL2303     230400 bps -> 1 bit = ~4.34 µs (parfait)
 *	AVR 16 MHz 230400 bps -> 1 bit = ~4.50 µs (222222 bps)	BRR=8
 *	A13 ttyS1  230400 bps -> 1 bit = ~4.67 µs (214133 bps)
 *
 *	488/434 = 1.12		erreurs
 *	467/434 = 1.076		erreurs
 *	488/467 = 1.045		ok
 *	467/450 = 1.038		ok
 *	450/434 = 1.037		erreurs
 *
 *	Config 16 Mhz, Qz 14.7456 MHz 230400 (BRR=8) -> 4.88 µs (204918 bps) ok
 */

#include "config.h"
#include "swuart/swuart.h"
#include <stdbool.h>


static volatile bool		x_launch ;
static uint16_t			launch_ms = 10 ;
static volatile uint16_t	n_launch ;


static char i2h ( uint8_t i )
{
  if ( i < 10 )
    return '0'+i ;
  return 'A'+i-10 ;
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



HW_ISR( MS_TIMER, match_a, interruptible )
{
  static volatile uint16_t millis ;

  millis++ ;
  if ( millis == launch_ms ) {
    millis = 0 ;
    x_launch = 1 ;
    n_launch++ ;
  }
}


int
main ( )
{
  hwa_begin(reset);
  //  swuart_hwa();
  hwa_config( UART, rxtx, UART_BPS, noparity, 8bits, 1stop );
  /* hwa_config( MS_TIMER, MS_TIMER_CLK, loop_up, 250, match_a ); */
  hwa_set_countmode( MS_TIMER, loop_up );
  hwa_set_toptype(   MS_TIMER, match_a );
  hwa_set_top(       MS_TIMER, 250 );
  hwa_connect_clock( MS_TIMER, MS_TIMER_CLK );
  hwa_turn_irq(      MS_TIMER, match_a, on );
  hwa_commit();

  swuart_set_dt(hw_syshz() / SWUART_BPS);

  //  swuart_enable_rx();

  hw_enable_interrupts();

  uart_tx('\n');

  for(;;) {
    x_launch = 0 ;
    while ( !x_launch ) {}
    uart_tx_2h(n_launch);
    uart_tx(' ');

    for ( uint8_t i=1 ; i<=30 ; i++ ) {
      uart_tx_2h(i);
      if ( i<30 )
	uart_tx(' ');
      else
	uart_tx('\n');
    }
  }
}
