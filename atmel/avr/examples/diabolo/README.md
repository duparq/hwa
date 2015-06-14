
Diabolo bootloader {#atmelavr_diabolo}
==================

Diabolo is a bootloader (Diabolo Is A BOot LOader) developed using HWA for
assembler programming for the device side, and Python for the host application.

 * It is fast, as the host application uses a __cache mecanism__ to determine
   the pages that have to be programmed;

 * It is not too big: ~ __640 bytes__;

 * It is very convenient since it can use __any pin__ for __1 or 2-wire serial
   communication__ with __auto-detection__ and __auto-synchronization__ so that
   no baudrate has to be hardcoded in the project and __no crystal__ is required
   on the target.

The source code of Diabolo is in the `atmel/avr/examples/diabolo/` directory.


Installing Diabolo on an AVR
----------------------------

In order to install Diabolo on the microcontroller, you must enter the `device/`
directory and edit the file `diabolo.sx` to either include a preconfigured
target definition or define the following symbols:

@code
    #define HW_DEVICE_SELF_PROGRAMMING      enabled

    #define DIABOLO_PIN_RX                  hw_pin_2
    #define DIABOLO_PIN_TX                  hw_pin_2
@endcode

Optionnally, you can also define:

@code
    #define HW_DEVICE_CLK_SRC               rc_8MHz
    #define HW_DEVICE_CLK_PSC               1
    #define HW_DEVICE_EXTERNAL_RESET        enabled
    #define HW_DEVICE_DEBUG_WIRE            disabled
    #define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
    #define HW_DEVICE_CLOCK_OUTPUT          disabled
    #define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV
@endcode

Then, you must include the HWA header:

@code
    #include <atmel/avr/atmega328p_au.h>
@endcode


If you have `avrdude` installed and your ISP is `usbasp` you just have to wire
the target device to your programmer and type `make install`.

Otherwise, you'll have to edit the `device/Makefile` to suit your programming
tools.


Using the Diabolo host application
----------------------------------

Once you have installed Diabolo, you can check that everything works with
`python host/diabolo.py`. It should display the status of your device.
