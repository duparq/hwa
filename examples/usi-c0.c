/*
 *	Configure radio module nRF24L01+ through spi master mode of USI
 */

#include <hwa.h>

#define DBG_PIN		hw_pin_7
//#define SPI		hw_usi0_spimaster_swclk
#define SPI		hw_usi0_spimaster_c0clk


HW_ISR( hw_irq(hw_counter1, capture) )
{
  /* hw_toggle( DBG_PIN ); */
  /* hw_write( SPI, 0x5A ); */
}

/* HW_ISR( hw_irq(hw_counter0, overflow) ) */
/* { */
/*   hw_toggle( DBG_PIN ); */
/*   hw_write( hw_counter0, 0xF0 ); */
/* } */

HW_ISR( hw_irq(hw_usi0, overflow) )
{
  hw_toggle( DBG_PIN );
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( DBG_PIN, output );

  hwa_config( hw_counter1,
	      clock,		syshz_div_8,
	      countmode,	loop_up,
	      top,		register_capture );
  hwa_write_bits( hw_counter1, capture, 0.001 * hw_syshz/8 );
  hwa_turn( hw_irq(hw_counter1, capture), on );

  hwa_config( hw_counter0,
	      clock,		syshz_div_8,
	      countmode,	loop_up,
	      top,		fixed_0xFF );
  /* hwa_write_bits( hw_counter0, compare_a, 0.000010 * hw_syshz/8 ); */
  //  hwa_write( hw_counter0, 0xF0 );
  //  hwa_turn( hw_irq(hw_counter0, overflow), on );
  hwa_write_bits( hw_counter0, compare_a, 0x80 );
  hwa_write_bits( hw_counter0, compare_b, 0x80 );

  hwa_turn( hw_irq(hw_usi0, overflow), on );

  hwa_config( SPI );

  hwa_commit();

  hw_enable_interrupts();

  for(;;) {
    hw_sleep_until_irq();
    /* hw_toggle( DBG_PIN ); */
    /* hw_write( SPI, 0x5A ); */
    //    uint8_t r = hw_read( SPI );
  }

  return 0 ;
}
