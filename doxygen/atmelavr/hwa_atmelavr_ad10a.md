
Atmel AVR 10-bit Analog to Digital Converter: class ad108a  {#atmelavr_ad10a}
==========================================================

Class ad10a
===========

Class ad10a is a 10-bit analog to digital converter.

It is used in the following
devices:

* @ref attinyx4 "ATtiny24, ATtiny44, ATtiny84": `hw_adc0`

In the text below, the adc is referenced as `ADC`.

Generic operations               | Result
---------------------------------|--------------
`hw_bn( ADC )`                   | 10


Configuration in single-end mode
--------------------------------

@code
hwa_config( ADC,

            clock,        syshz_div_2
                        | syshz_div_4
                        | syshz_div_8
                        | syshz_div_16
                        | syshz_div_32
                        | syshz_div_64
                        | syshz_div_128,

            trigger,      manual
                        | auto
                        | acmp0
                        | int0
                        | counter0_output0
                        | counter0_overflow
                        | counter1_output1
                        | counter1_overflow
                        | counter1_input0,

            vref,         vcc
                        | pin_aref
                        | bandgap,

          [ align,        left
                        | right, ]

          [ polarity,     unipolar
                        | bipolar, ]

          [ gain,         1
                        | 20, ]

          [ input_mode,   single_end, ]

            input,        pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
                        | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7
                        | agnd
                        | bandgap
                        | temperature
          );
@endcode


Configuration in differential mode
----------------------------------

@code
hwa_config( ADC,

            clock,            syshz_div_2
                            | syshz_div_4
                            | syshz_div_8
                            | syshz_div_16
                            | syshz_div_32
                            | syshz_div_64
                            | syshz_div_128,

            trigger,          manual
                            | auto
                            | acmp0
                            | int0
                            | counter0_output0
                            | counter0_overflow
                            | counter1_output1
                            | counter1_overflow
                            | counter1_input0,

            vref,             vcc
                            | pin_aref
                            | bandgap,

          [ align,            left
                            | right, ]

          [ polarity,         unipolar
                            | bipolar, ]

          [ gain,             1
                            | 20, ]

          [ input_mode,       differential, ]

            positive_input,   pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
                            | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7,

            negative_input,   pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
                            | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7
          );
@endcode


Configuration of input pins
---------------------------

I/O pins used as ADC inputs must be configured using the name `hw_pin_adcX` so
that their digital input buffer will be disabled:

@code
  hw/hwa_config( hw_pin_adc0, input );
@endcode

If an ADC input must be turned into digital mode, it must be reconfigured using
its digital I/O definition:

@code
  hw/hwa_config( hw_io(hw_pin_adc0), output );
@endcode


Status of the ADC
-----------------

The status of the ADC can be obtained with the `hw_status(...)` instruction. It defines 2 bits:

* `interrupt`: is set each time a conversion ends
* `running`: is set while a conversion is running

@code
  while( hw_status(ADC).running ) {}
  result = hw_read(ADC);
@endcode

@code
  while( !hw_status(ADC).interrupt ) {}
  result = hw_read(ADC);
@endcode

Other operations
----------------

Pperations               | Result
-------------------------|--------------
`hw_read( ADC )`         | Value of the conversion register
`hw_atomic_read( ADC )`  | Value of the conversion register (16-bit atomic read)
`hw/hwa_trigger( ADC )`  | Trigger conversion




Interrupts
==========

Class ad10a can trigger the following interrupt requests:

* `hw_irq( ADC )`: conversion is done
