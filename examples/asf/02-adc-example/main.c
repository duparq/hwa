
/*	Translation of ASF's adc_example1.c written for ATmegaX8
 */

#define HWA_DEVICE		attiny84
#define HWA_NO_CHECK_LIMITS	/* let us write beyond existing port b pins */

#include <hwa.h>

#define OUTPORT			hw_port_b
#define ADC_INPUT		hw_pin_adc0
#define ADC_VREF		vcc
#define ADC			hw_adc0


volatile uint16_t avg;

/*
 * The interrupt accumulates the sum of 16 samples in the accum variable.
 * when 16 samples has been added, the sum is divided by 16 to find the average
 * and the result is stored in the global variable avg.
 */
HW_ISR( hw_adc0 )
{
  static uint16_t accum;
  static uint8_t i = 0;

  if (i == 16){
    avg = accum / 16;
    i = 0;
    accum = 0;
  } else {
    accum += hw_read( ADC );
    i++;
  }
}


/*
 * To ensure that the data is not modified by the interrupt handler
 * while we read it, we disable interrupts before reading the global variable.
 */
static inline uint16_t read_global(void)
{
  uint16_t retval;

#if 0
  hw_interrupts_status_t s = hw_get_interrupts_status();
  retval = avg ;
  hw_set_interrupts_status(s);
#else
  HW_ATOMIC(
	    retval = avg ;
	    );
#endif

  return retval;
}

int main(void)
{
  hwa_begin_from_reset();
  hwa_config( hw_port_b, output );
  hwa_config( hw_adc0,
	      clock,	syshz_div_128,
	      trigger,	auto,
	      vref,	vcc,
	      align,	right,
	      input,	pin_adc0 );
  hwa_turn( hw_irq( hw_adc0 ), on );
  hwa_trigger( hw_adc0 );
  hwa_commit();

  hw_enable_interrupts();

  while (1) {
    hw_write( hw_port_b, read_global() >> 8 );
  }
}
