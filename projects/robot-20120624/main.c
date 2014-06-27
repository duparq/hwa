
#include "config.h"
//#include "swuart.h"
//#include "misc.h"
#include <hwa.h>


uint8_t		_ad[3] ;
uint8_t		ad[3] ;
uint8_t		phase ;
uint8_t		m1, m2 ;

#define DMAX	80


static void 
calc ( )
{
  uint8_t max = ad[0] ;
  if ( ad[1] > max )
    max = ad[1] ;
  if ( ad[2] > max )
    max = ad[2] ;

  uint8_t thrs = max - max/4 /* + max/16 */ ;

  uint8_t mode = 0 ;
  if (ad[0] > thrs)
    mode |= 4 ;
  if (ad[1] > thrs)
    mode |= 2 ;
  if (ad[2] > thrs)
    mode |= 1 ;

#if 0
  u16 _m1 = m1 ;
  u16 _m2 = m2 ;
  u16 xm1 = _m1 ;
  u16 xm2 = _m2 ;

  if (max < 150 || mode == 0 || mode == 2 || mode == 7) {
    xm1 = 0 ;
    xm2 = 0 ;
  }
  else if ( mode == 0b001 ) {
    xm1 = _m1/2 ;
    if (_m2 < DMAX)
      xm2 += (DMAX+1-_m2)/2 ;
  }
  else if ( mode == 0b011 ) {
    xm1 = 0 ;
    if (_m2 < DMAX)
      xm2 += (DMAX+1-_m2)/2 ;
  }
  else if ( mode == 0b100 ) {
    xm2 = _m2/2 ;
    if (_m1 < DMAX)
      xm1 += (DMAX+1-_m1)/2 ;
  }
  else if ( mode == 0b110 ) {
    xm2 = 0 ;
    if (_m1 < DMAX)
      xm1 += (DMAX+1-_m1)/2 ;
  }
  else {
    xm1 = DMAX ;
    xm2 = DMAX ;
  }

  _m1 = (_m1 * 7 + xm1)/8 ;
  _m2 = (_m2 * 7 + xm2)/8 ;
  m1 = _m1 & 0xFF ;
  m2 = _m2 & 0xFF ;
#else
  if (max < 150 || mode == 0 || mode == 2 || mode == 7) {
    m1 = 0 ;
    m2 = 0 ;
  }
  else if ( mode == 1 ) {
    m1 = m1/2 ;
    if (m2 < DMAX)
      m2 += (DMAX+1-m2)/2 ;
  }
  else if ( mode == 3 ) {
    m1 = 0 ;
    if (m2 < DMAX)
      m2 += (DMAX+1-m2)/2 ;
  }
  else if ( mode == 4 ) {
    m2 = m2/2 ;
    if (m1 < DMAX)
      m1 += (DMAX+1-m1)/2 ;
  }
  else if ( mode == 6 ) {
    m2 = 0 ;
    if (m1 < DMAX)
      m1 += (DMAX+1-m1)/2 ;
  }
  else {
    m1 = DMAX ;
    m2 = DMAX ;
  }

#endif

  hw_write( hw_counter0, ocra, m1 );
  hw_write( hw_counter0, ocrb, m2 );

  /* hw_pwm_set_duty( pwm0a, m1 ); */
  /* hw_pwm_set_duty( pwm0b, m2 ); */
}


/*	Acquisition des mesures de réflexion IR
 *	  12 phases : 4 conversions par canal, acquisition sur la 4e conversion
 */
hw_isr( hw_adc0, all, interruptible )
{
  uint8_t	ch = phase >> 2 ;
  uint8_t	ph = phase & 0x03 ;

  if ( ph == 3 ) {
    _ad[ch] = hw_read(hw_adc0,adc) >> 2 ;

    if ( phase >= 11 ) {
      hw_write( PIN_DBG, 0 );
      hw_write( hw_port_a, 0 );
      ad[0] = _ad[0] ;
      ad[1] = _ad[1] ;
      ad[2] = _ad[2] ;
      calc();
      return ;
    }

    ch++ ;
    hw_write(hw_port_a, 1U<<ch);
  }

  phase++ ;
  hw_write(hw_adc0, sc, 1);
  hw_toggle(PIN_DBG);
}


/*	Lancement d'un cycle d'acquisition
 *	  Fréquence == SYSHZ/65536 == ~15 * (SYSHZ/1000000)
 */
#if SWUART
hw_isr( SWUART_TIMER, overflow, interruptible )
{
  phase = 0 ;
  hw_write( hw_adc0, adsc, 1 );
  //  hw_write( PIN_DBG, 1 );
  hw_write(hw_port_a, 1 );
  hw_toggle(PIN_DBG);
}
#endif


int
main ( )
{
  hw_write( hw_core0, osccal, 0);	// ~4 MHz

  hwa_begin(reset);

#if SWUART
  hwa_swuart();			// Initialise SWUART hardware
#endif

  hwa_config( PIN_DBG,  output );
  hwa_config( hw_pin_pa0,  output );
  hwa_config( hw_pin_pa1,  output );
  hwa_config( hw_pin_pa2,  output );

  hwa_config( hw_pin_adc3, input_analog );

  /*	PWM
   */
  /* hwa_write(hw_counter0, wgm,  3); */
  /* hwa_write(hw_counter0, coma, 2); */
  /* hwa_write(hw_counter0, comb, 2); */
  /* hwa_write(hw_counter0, cs,   3); */

  /* hwa_write(WGM0,  0b011);	// Fast PWM 0x00 -> 0xFF */
  /* hwa_write(COM0A, 0b10);	// Set at 0x00, clear on match */
  /* hwa_write(COM0B, 0b10);	// Set at 0x00, clear on match */
  /* hwa_write(CS0,   0b011);	// SYSHZ / 64 */

  /* hwa_write(hw_counter1, oie, 1);	// Timer1 overflow interrupt */
  /* hwa_write( TOIE1, 1 );	// Timer1 overflow interrupt */

  /* hwa_timer_turn_irq( timer1, OVERFLOW, ON ); */
  //  hwa_turn_irq( timer1, OVERFLOW, ON );

  /* hwa_timer_connect_clock( hw_timer1, SWUART_TIMER_CLKHZ ); */

  /* hwa_timer_connect_clock(   timer0, SYSHZ_DIV_64            ); */
  /* hwa_timer_set_countmode(   timer0, LOOP_UP                 ); */
  /* hwa_timer_set_ocmode(      timer0, MATCH_A, CLEAR_ON_MATCH ); */
  /* hwa_timer_set_ocmode(      timer0, MATCH_B, CLEAR_ON_MATCH ); */
  /* hwa_timer_set_toptype(     timer0, FIXED                   ); */
  /* hwa_timer_set_top(         timer0, 255                     ); */
  /* hwa_timer_set_updatematch( timer0, ON_BOTTOM               ); */

  /* hwa_pwm_config( pwm0b, 255, 64 ); */
  /* hwa_pwm_config( pwm0a, 255, 64 ); */
  /* hwa_pwm_set_duty( pwm0a, 0 ); */
  /* hwa_pwm_set_duty( pwm0b, 0 ); */

  /*	ADC
   */
  /* hwa_write(REFS, 0b00);	// Vref = Vcc */
  /* hwa_write(MUX,  3); */
  /* hwa_write(ADEN, 1); */
  /* hwa_write(ADPS, 0b111); */
  /* hwa_write(ADIE, 1); */

  hwa_write( hw_adc0, refs, 0);	// Vref = Vcc
  hwa_write( hw_adc0, mux,  3);
  hwa_write( hw_adc0, en,   1);
  hwa_write( hw_adc0, ps,   7);
  hwa_write( hw_adc0, ie,   1);

  /* hwa_adc_connect_ref(   adc0, VCC      ); */
  /* hwa_adc_connect_input( adc0, PIN_ADC3 ); */
  /* hwa_adc_set_prescaler( adc0, 128      ); */
  /* hwa_adc_turn_irq( adc0, DONE, ON  ); */
  /* hwa_turn_irq( adc0, DONE, ON  ); */
  //  hwa_adc_turn_irq( adc0, COMPLETED, ON );

#if SWUART
  hwa_commit();

  u16 n = swuart_sync(9);	// Detect baudrate with a least a 9/1 ratio
  swuart_set_dt(n);		// Set bit duration in SYSHZ cycles
  swuart_wait_rxidle(10);	// Wait RXD idle for 10 bits

  hw_enable_interrupts();	// So that SWUART can RX & TX

  swuart_putbyte(0x55);		// Tell the host that we synchronized
  swuart_putbyte(swuart_dtn&0xFF);
  swuart_putbyte(swuart_dtn>>8);

  /*	Connect PWM outputs
   */
  hwa_config( PIN_OC0A, OUTPUT );
  hwa_config( PIN_OC0B, OUTPUT );
  hwa_commit();
#else
  /* hwa_timer_connect_clk( TIMER, TIMER_CLKHZ ) ; */
  hwa_config( hw_pin_oc0a, output );
  hwa_config( hw_pin_oc0b, output );
  hwa_commit();
  hw_enable_interrupts();
#endif

  for(;;) {
#if SWUART
    swuart_getbyte() ;
    swuart_putbyte(ad[0]);
    swuart_putbyte(ad[1]);
    swuart_putbyte(ad[2]);
    swuart_putbyte(m1);
    swuart_putbyte(m2);
#endif
  }
}
