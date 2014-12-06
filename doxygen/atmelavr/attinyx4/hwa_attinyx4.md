
Atmel ATtiny24, ATtiny44, ATtiny84 {#attinyx4}
==================================

HW_DEVICE
=========

In order to use the HWA facilities for the Atmel ATtiny24, ATtiny44, or ATtiny84
devices, you must define `HW_DEVICE` accordingly as one of:

* `attiny24`
* `attiny44`
* `attiny84`

@code
#define HW_DEVICE attiny44		/* Compile for Atmel AVR ATtiny44 */
@endcode

Optionnaly, `HW_DEVICE` can also define the target's package used, so that pin
numbers become available in addition to pin names:

@code
#define HW_DEVICE attiny44, dil		/* ATtiny44 in DIL package */
@endcode

The following symbols will then be defined:

Symbol               | Definition
---------------------|-----------
`HW_DEVICE_ATTINYX4` | Void
`HW_DEVICE_ATMELAVR` | Void
`HW_FLASHSIZE`       | The size of the flash memory in bytes
`HW_EEPROMSIZE`      | The size of the eeprom memory in bytes
`HW_RAMSIZE`         | The size of the ram memory in bytes


Modules
=======

- @subpage attinyx4_core "Device's core": `hw_core0`
- @subpage attinyx4_pwr "Power Management"
- @subpage attinyx4_ios "Digital I/Os":
  + `hw_port_a`: `hw_pin_pa0` .. `hw_pin_pa7`
  + `hw_port_b`: `hw_pin_pb0` .. `hw_pin_pb3`
- @subpage attinyx4_pcic "Pin Change Interrupt Controllers": `hw_pcic0`, `hw_pcic1`
- Counters:
  + @subpage atmelavr_c8a "8-bit Timer/Counter0 with 2 PWM outputs":
    + `hw_counter0`:
      + `hw_counter0_output0`
      + `hw_counter0_output1`
  + @subpage atmelavr_c16a "16-bit Timer/Counter1 with 2 PWM outputs and 1 capture input":
    + `hw_counter1`:
      + `hw_counter1_output0`
      + `hw_counter1_output1`
      + `hw_counter1_input0`
  + @subpage attinyx4_psc "Timer/Counters prescaler": `hw_psc0`
- @subpage atmelavr_usia "Universal Serial Interface": `hw_usi0`
- @subpage atmelavr_acmpa "Analog Comparator": `hw_acmp0`
- @subpage atmelavr_ad10a "10-bit Analog to Digital Converter": `hw_adc0`
- @subpage atmelavr_wdog "Watchdog Timer": `hw_watchdog0`
- @subpage atmelavr_eeprom "EEPROM Memory": `hw_eeprom0`
- @subpage atmelavr_flash "FLASH Memory": `hw_flash0`
