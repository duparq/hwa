/*
 *	Configure radio module nRF24L01+ through spi master mode of USI
 */

#include <hwa.h>

#define DBG_PIN		hw_pin_6
#define SPI		hw_usi0_spimaster_swclk

#define NRF_CE		hw_pin_10
#define NRF_CSN		hw_pin_11


#define NRF_CMD_R_REGISTER	0x00


static void delay_10us( )
{
  hw_nop_loop( 0.000010*hw_syshz );
}


static uint8_t nrf_read_reg( uint8_t n )
{
  delay_10us( 0.000010*hw_syshz );
  hw_write( NRF_CSN, 0 );
  delay_10us( 0.000010*hw_syshz );
  hw_write( SPI, NRF_CMD_R_REGISTER+n );
  delay_10us( 0.000010*hw_syshz );
  hw_write( SPI, 0 );
  uint8_t r = hw_read( SPI );
  delay_10us( 0.000010*hw_syshz );
  hw_write( NRF_CSN, 1 );
  return r ;
}


HW_ISR( hw_irq(hw_counter1, capture), interruptible )
{
  hw_toggle( DBG_PIN );
  nrf_read_reg(7);
}


int main ( )
{
  hwa_begin_from_reset();

  hwa_config( DBG_PIN,  output );

  hwa_config( NRF_CE,   output );
  hwa_write(  NRF_CE,   0 );
  hwa_config( NRF_CSN,  output );
  hwa_write(  NRF_CSN,  1 );

  hwa_config( hw_counter1,
	      clock,		syshz_div_8,
	      countmode,	loop_up,
	      top,		register_capture );
  hwa_write_bits( hw_counter1, capture, 0.001 * hw_syshz/8 );
  hwa_turn( hw_irq(hw_counter1, capture), on );

  hwa_config( SPI );

  hwa_commit();

  hw_enable_interrupts();

  for(;;) {
    hw_sleep_until_irq();
  }

  return 0 ;
}
