
Diabolo bootloader		{#diabolo}
==================

Diabolo is a bootloader (Diabolo Is A BOot LOader) developed using HWA for
assembler programming. It is fast, as the host side uses a cache mecanism to
determine pages that have to be programmed. It is not too big: ~640 bytes. It is
very convenient since it can use 1 or 2-wire serial lines with auto-detection
and auto-synchronization so that the baudrate does not have to be hardcoded in
the project and no crystal is required on the target.

The source code of Diabolo is in the `examples/atmel/avr/diabolo/` directory.


Installing Diabolo on an AVR
----------------------------

In order to install Diabolo on the microcontroller, you must enter the `device/`
directory and edit the file `diabolo.sx` to either include a preconfigured
target definition or define the following symbols:

    #define HW_DEVICE                       attiny84
    #define HW_DEVICE_PACKAGE               14pdip
    #define HW_DEVICE_SELF_PROGRAMMING      enabled

    #define DIABOLO_PIN_RX                  hw_pin_2
    #define DIABOLO_PIN_TX                  hw_pin_2

Optionnally, you can also define:

    #define HW_DEVICE_CLK_SRC               rc_8MHz
    #define HW_DEVICE_CLK_PSC               1
    #define HW_DEVICE_EXTERNAL_RESET        enabled
    #define HW_DEVICE_DEBUG_WIRE            disabled
    #define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
    #define HW_DEVICE_CLOCK_OUTPUT          disabled
    #define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV

If you have `avrdude` installed and your ISP is `usbasp` you just have to wire
the target device to your programmer and type `make install`.

Otherwise, edit the `device/Makefile` to suit your programming tools.


Using the Diabolo host application
----------------------------------

Once you have installed Diabolo, you can check that everything works with
`python host/diabolo.py`. It should display the status of your device.
