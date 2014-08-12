
/*	Translation of ASF's adc_example1.c written for ATmegaX8
 */

#define HWA_DEVICE		attiny84

#include <hwa.h>

#define OUTPORT			hw_port_b
#define ADC_INPUT		hw_pin_adc0
#define ADC_VREF		vcc

#define hw_def_hw_status_ad10a	, _hw_status_ad10a


int main ( )
{
  hwa_begin_from_reset();
  hwa_config( hw_port_a, output );
  //  hwa_config( ADC_INPUT, input );
  hwa_config( hw_adc0,
	      clock,	syshz_div_128,
	      trigger,	manual,
	      vref,	ADC_VREF,
	      align,	left,
	      input,	hw_name(ADC_INPUT) );
  hwa_commit();

  for(;;) {
    hw_trigger( hw_adc0 );
    while ( hw_status( hw_adc0 ).running ) {}
    hw_write( hw_port_a, ~hw_read_reg( hw_adc0, adch ) );
  }

  return 0 ;
}
