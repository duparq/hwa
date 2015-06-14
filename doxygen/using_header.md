
HWA header file {#using_header}
===============

In order to use the HWA facilities, you must first include the header file
corresponding to your device:

@code
#include <atmel/avr/attiny44a_pu.h>
@endcode

The header file is searched in the `include/` directory of HWA.

@par Configuration fuses

If your device can be configured via fuses, you can define the configuration
through the definition of symbols prefixed with `HW_DEVICE_` before including
the HWA header, otherwise HWA will revert to factory default values for
undefined fuses:

@code
#define HW_DEVICE_CLK_SRC               rc_8MHz
#define HW_DEVICE_CLK_PSC               1
#define HW_DEVICE_EXTERNAL_RESET        enabled
#define HW_DEVICE_SELF_PROGRAMMING      enabled
#define HW_DEVICE_DEBUG_WIRE            disabled
#define HW_DEVICE_WATCHDOG_ALWAYS_ON    no
#define HW_DEVICE_CLOCK_OUTPUT          disabled
#define HW_DEVICE_BROWNOUT_DETECTION    2500_2900mV

#include <atmel/avr/attiny44a_pu.h>
@endcode
