
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Declarations for ATmega48A/PA/88A/PA/168A/PA/328/P that do not produce C code
 */

/**
 * @page atmegax8 ATmega48A/PA/88A/PA/168A/PA/328/P
 *
 * See also: @ref atmelavr "HWA definitions common to all Atmel AVRs"
 *
 * @section atmegax8_includes Including the proper header file
 *
 * You can include:
 * * `<hwa/atmega328p_au.h>`
 *
 * @section atmegax8_object Supported objects
 * 
 * Object name            | Class                 | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_core0`             | @ref atmelavr_coreb "_coreb" | The core
 * `hw_portb`             | @ref atmelavr_io8a "_io8a"   | General purpose I/O port B (PORTB)
 * `hw_portc`             | @ref atmelavr_io8a "_io8a"   | General purpose I/O port C (PORTC)
 * `hw_portd`             | @ref atmelavr_io8a "_io8a"   | General purpose I/O port D (PORTD)
 * `hw_pcic0`             | @ref atmelavr_pcicb "_pcicb" | Pin change interrupt controller
 * `hw_wdog0`             | @ref atmelavr_wdogb "_wdogb" | Watchdog (WDG)
 * `hw_counter0`          | @ref atmelavr_c8a "_c8a"     | 8-bit counter-timer (T0)
 * `hw_counter0_compare0` | @ref atmelavr_ocua "_ocua"   | Compare unit 0 of hw_counter0 (OC0A)
 * `hw_counter0_compare1` | @ref atmelavr_ocua "_ocua"   | Compare unit 1 of hw_counter0 (OC0B)
 * `hw_counter1`          | @ref atmelavr_c16a "_c16a"   | 16-bit counter-timer (T1)
 * `hw_counter1_compare0` | @ref atmelavr_ocua "_ocua"   | Compare unit 0 of hw_counter1 (OC1A)
 * `hw_counter1_compare1` | @ref atmelavr_ocua "_ocua"   | Compare unit 1 of hw_counter1 (OC1B)
 * `hw_counter1_capture0` | @ref atmelavr_icua "_icua"   | Capture unit 0 of hw_counter1 (ICP1)
 * `hw_counter2`          | @ref atmelavr_c8b "_c8b"     | 8-bit counter-timer (T2)
 * `hw_counter2_compare0` | @ref atmelavr_ocua "_ocua"   | Compare unit 0 of hw_counter2 (OC2A)
 * `hw_counter2_compare1` | @ref atmelavr_ocua "_ocua"   | Compare unit 1 of hw_counter2 (OC2B)
 * `hw_psc0`              | @ref atmelavr_psca "_psca"   | hw_counter0/hw_counter1 prescaler (PSC0)
 * `hw_uart0`             | @ref atmelavr_uarta "_uarta" | Universal Asynchronous Receiver Transmitter
 * `hw_acmp0`             | @ref atmelavr_acmpb "acmpb"  | Analog Comparator
 * `hw_adc0`              | @ref atmelavr_ad10b "ad10b"  | 10-bit Analog to Digital Converter
 * `hw_eeprom0`           | @ref atmelavr_eeproma "eeproma" | Eeprom memory
 * `hw_flash0`            | @ref atmelavr_flasha "flasha"   | Flash memory
 * 
 * A few additionnal objects are also provided for convenience:
 * 
 * Name                   | Class                 | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_swuart0`           | @ref atmelavr_swuarta "swuarta" | Software UART
 * `hw_swuart1`           | @ref atmelavr_swuarta "swuarta" | Software UART
 */
#include "../hwa/atmel/avr/1.h"
#include "../classes/atmel/avr/coreb_1.h"
#include "../classes/atmel/avr/io_1.h"
#include "../classes/atmel/avr/pin1a_1.h"
#include "../classes/atmel/avr/pcicb_1.h"
#include "../classes/atmel/avr/wdogb_1.h"
#include "../classes/atmel/avr/ocua_1.h"
#include "../classes/atmel/avr/icua_1.h"
#include "../classes/atmel/avr/psca_1.h"
#include "../classes/atmel/avr/c8a_1.h"
#include "../classes/atmel/avr/c8b_1.h"
#include "../classes/atmel/avr/c16a_1.h"
#include "../classes/atmel/avr/uarta_1.h"
#include "../classes/atmel/avr/acmpb_1.h"
#include "../classes/atmel/avr/ad10b_1.h"


/**
 * @brief  Declare the context
 */
#define HWA_DCL					\
  hwa_coreb_t	hw_core0 ;			\
  hwa_io8a_t	hw_portb ;			\
  hwa_io8a_t	hw_portc ;			\
  hwa_io8a_t	hw_portd ;			\
  hwa_pcicb_t	hw_pcic0 ;			\
  hwa_wdogb_t	hw_wdog0 ;			\
  hwa_c8a_t	hw_counter0 ;			\
  hwa_c16a_t	hw_counter1 ;			\
  hwa_c8b_t	hw_counter2 ;			\
  hwa_uarta_t	hw_uart0 ;			\
  hwa_acmpb_t	hw_acmp0 ;			\
  hwa_ad10b_t	hw_adc0 ;


  /* hwa_usia_t	hw_usi0 ;			\ */


/**
 * @page atmegax8
 * @section atmegax8_interrupts Interrupts
 * 
 * Interrupt definition   | Atmel label     | Comments
 * :----------------------|-----------------|------------------------
 * `hw_core0,int0`        | INT0            | External Interrupt Request 0
 * `hw_core0,int1`        | INT1            | External Interrupt Request 1
 * `hw_pin_*,change`      | PCINT0/1/2      | Pin Change Interrupt Request 0/1/2
 * `hw_wdog0`             | WDT             | Watchdog Time-out Interrupt
 * `hw_counter2,compare0` | TIMER2 COMPA    | Timer/Counter2 Compare Match A
 * `hw_counter2,compare1` | TIMER2 COMPB    | Timer/Counter2 Compare Match B
 * `hw_counter2,overflow` | TIMER2 OVF      | Timer/Counter2 Overflow
 * `hw_counter1,capture0` | TIMER1 CAPT     | Timer/Counter1 Capture Event
 * `hw_counter1,compare0` | TIMER1 COMPA    | Timer/Counter1 Compare Match A
 * `hw_counter1,compare1` | TIMER1 COMPB    | Timer/Coutner1 Compare Match B
 * `hw_counter1,overflow` | TIMER1 OVF      | Timer/Counter1 Overflow
 * `hw_counter0,compare0` | TIMER0 COMPA    | Timer/Counter0 Compare Match A
 * `hw_counter0,compare1` | TIMER0 COMPB    | Timer/Counter0 Compare Match B
 * `hw_counter0,overflow` | TIMER0 OVF      | Timer/Counter0 Overflow
 * `hw_spi0`              | SPI,STC         | SPI Serial Transfer Complete
 * `hw_usart0,rxc`        | USART,RXC       | USART Rx Complete
 * `hw_usart0,txqne`      | USART,UDRE      | USART, Data Register Empty
 * `hw_usart0,txc`        | USART,TXC       | USART, Tx Complete
 * `hw_adc0`              | ADC             | ADC conversion complete
 * `hw_eeprom0`           | EE READY        | EEPROM ready
 * `hw_eeprom0,ready`     | EE READY        | EEPROM ready
 * `hw_acmp0`             | ANALOG COMP     | Analog comparator
 * `hw_twi0`              | TWI             | 2-wire Serial Interface
 * `hw_flash0`            | SPM READY       | Store Program Memory Ready
 */
/**
 * @ingroup atmegax8_interrupts
 * @brief Definition of the interrupts
 */
#define _hw_irq_hw_core0_int0		_irq,  1, hw_core0,    ie0, if0
#define _hw_irq_hw_core0_int1		_irq,  2, hw_core0,    ie1, if1

#define _hw_irq_hw_pin_pb0_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb1_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb2_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb3_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb4_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb5_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb6_change	_irq,  3, hw_pcic0,    ie0, if0
#define _hw_irq_hw_pin_pb7_change	_irq,  3, hw_pcic0,    ie0, if0

#define _hw_irq_hw_pin_pc0_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc1_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc2_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc3_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc4_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc5_change	_irq,  4, hw_pcic0,    ie1, if1
#define _hw_irq_hw_pin_pc6_change	_irq,  4, hw_pcic0,    ie1, if1

#define _hw_irq_hw_pin_pd0_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd1_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd2_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd3_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd4_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd5_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd6_change	_irq,  5, hw_pcic0,    ie2, if2
#define _hw_irq_hw_pin_pd7_change	_irq,  5, hw_pcic0,    ie2, if2

#define _hw_irq_hw_wdog0		_irq,  6, hw_wdog0,    ie,  if

#define _hw_irq_hw_counter2_compare0	_irq,  7, hw_counter2, iecm0, ifcm0
#define _hw_irq_hw_counter2_compare1	_irq,  8, hw_counter2, iecm1, ifcm1
#define _hw_irq_hw_counter2_overflow	_irq,  9, hw_counter2, ieov,  ifov

#define _hw_irq_hw_counter1_capture0	_irq, 10, hw_counter1, ieic,  ific
#define _hw_irq_hw_counter1_compare0	_irq, 11, hw_counter1, iecm0, ifcm0
#define _hw_irq_hw_counter1_compare1	_irq, 12, hw_counter1, iecm1, ifcm1
#define _hw_irq_hw_counter1_overflow	_irq, 13, hw_counter1, ieov,  ifov

#define _hw_irq_hw_counter0_compare0	_irq, 14, hw_counter0, iecm0, ifcm0
#define _hw_irq_hw_counter0_compare1	_irq, 15, hw_counter0, iecm1, ifcm1
#define _hw_irq_hw_counter0_overflow	_irq, 16, hw_counter0, ieov,  ifov

#define _hw_irq_hw_spi0			_irq, 17, hw_spi0,     ie,    if
#define _hw_irq_hw_spi0_txc		_irq, 17, hw_spi0,     ie,    if

#define _hw_irq_hw_usart0_rxc		_irq, 18, hw_usart0,   ierxc,  ifrxc
#define _hw_irq_hw_usart0_txqnf		_irq, 19, hw_usart0,   ietxqe, iftxqnf
#define _hw_irq_hw_usart0_txc		_irq, 20, hw_usart0,   ietxc,  iftxc

#define _hw_irq_hw_adc0			_irq, 21, hw_adc0,     ie,    if

#define _hw_irq_hw_eeprom0		_irq, 22, hw_eeprom0,  ie, /* no irq flag */
#define _hw_irq_hw_eeprom0_ready	_irq, 22, hw_eeprom0,  ie,

#define _hw_irq_hw_acmp0		_irq, 23, hw_acmp0,    ie, if

#define _hw_irq_hw_twi0			_irq, 24, hw_twi0,     ie, if

#define _hw_irq_hw_flash0		_irq, 25, hw_flash0,   ie, if


/**
 * @page atmegax8
 * @section atmegax8_pins Ports and pins
 *
 * Some of the pins may not be available depending on the fuses configuration.
 *
 * HWA name     | 32qfp/mlf   | Class                      | Atmel name
 * -------------|-------------|----------------------------|-----------
 * `hw_port_b`  |             | @ref atmelavr_pin1 "_pin1" | PORTB
 * `hw_pin_pb0` | `hw_pin_12` | @ref atmelavr_pin1 "_pin1" | PB0
 * `hw_pin_pb1` | `hw_pin_13` | @ref atmelavr_pin1 "_pin1" | PB1
 * `hw_pin_pb2` | `hw_pin_14` | @ref atmelavr_pin1 "_pin1" | PB2
 * `hw_pin_pb3` | `hw_pin_15` | @ref atmelavr_pin1 "_pin1" | PB3
 * `hw_pin_pb4` | `hw_pin_16` | @ref atmelavr_pin1 "_pin1" | PB4
 * `hw_pin_pb5` | `hw_pin_17` | @ref atmelavr_pin1 "_pin1" | PB5
 * `hw_pin_pb6` | `hw_pin_7`  | @ref atmelavr_pin1 "_pin1" | PB6
 * `hw_pin_pb7` | `hw_pin_8`  | @ref atmelavr_pin1 "_pin1" | PB7
 * `hw_port_c`  |             | @ref atmelavr_pin1 "_pin1" | PORTC
 * `hw_pin_pc0` | `hw_pin_23` | @ref atmelavr_pin1 "_pin1" | PC0
 * `hw_pin_pc1` | `hw_pin_24` | @ref atmelavr_pin1 "_pin1" | PC1
 * `hw_pin_pc2` | `hw_pin_25` | @ref atmelavr_pin1 "_pin1" | PC2
 * `hw_pin_pc3` | `hw_pin_26` | @ref atmelavr_pin1 "_pin1" | PC3
 * `hw_pin_pc4` | `hw_pin_27` | @ref atmelavr_pin1 "_pin1" | PC4
 * `hw_pin_pc5` | `hw_pin_28` | @ref atmelavr_pin1 "_pin1" | PC5
 * `hw_pin_pc6` | `hw_pin_29` | @ref atmelavr_pin1 "_pin1" | PC6
 * `hw_port_d`  |             | @ref atmelavr_pin1 "_pin1" | PORTD
 * `hw_pin_pd0` | `hw_pin_30` | @ref atmelavr_pin1 "_pin1" | PD0
 * `hw_pin_pd1` | `hw_pin_31` | @ref atmelavr_pin1 "_pin1" | PD1
 * `hw_pin_pd2` | `hw_pin_32` | @ref atmelavr_pin1 "_pin1" | PD2
 * `hw_pin_pd3` | `hw_pin_1`  | @ref atmelavr_pin1 "_pin1" | PD3
 * `hw_pin_pd4` | `hw_pin_2`  | @ref atmelavr_pin1 "_pin1" | PD4
 * `hw_pin_pd5` | `hw_pin_9`  | @ref atmelavr_pin1 "_pin1" | PD5
 * `hw_pin_pd6` | `hw_pin_10` | @ref atmelavr_pin1 "_pin1" | PD6
 * `hw_pin_pd7` | `hw_pin_11` | @ref atmelavr_pin1 "_pin1" | PD7
 */
/*	Instances			class, id, address
 */
#define _hw_portb			_io8a, 300, 0x23
#define _hw_portc			_io8a, 310, 0x26
#define _hw_portd			_io8a, 320, 0x29

/*	Pins				class, id, port, bn, bp
 *
 *	FIXME: port definitions do not take alternate functions into account
 */
#if !HW_IS(enabled,HW_DEVICE_CLOCK_OUTPUT)
#  define _hw_pin_pb0			_pin1, 301, hw_portb, 1, 0
#endif
#define _hw_pin_pb1			_pin1, 302, hw_portb, 1, 1
#define _hw_pin_pb2			_pin1, 303, hw_portb, 1, 2
#define _hw_pin_pb3			_pin1, 304, hw_portb, 1, 3
#define _hw_pin_pb4			_pin1, 305, hw_portb, 1, 4
#define _hw_pin_pb5			_pin1, 306, hw_portb, 1, 5

#if !HW_IS(external,HW_DEVICE_CLK_SRC) && !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#define _hw_pin_pb6			_pin1, 307, hw_portb, 1, 6
#endif
#if !HW_IS(xosc,HW_DEVICE_CLK_SRC)
#define _hw_pin_pb7			_pin1, 308, hw_portb, 1, 7
#endif
#define _hw_port_b			_pin1, 309, hw_portb, 8, 0

#define _hw_pin_pc0			_pin1, 311, hw_portc, 1, 0
#define _hw_pin_pc1			_pin1, 312, hw_portc, 1, 1
#define _hw_pin_pc2			_pin1, 313, hw_portc, 1, 2
#define _hw_pin_pc3			_pin1, 314, hw_portc, 1, 3
#define _hw_pin_pc4			_pin1, 315, hw_portc, 1, 4
#define _hw_pin_pc5			_pin1, 316, hw_portc, 1, 5
#if !HW_IS(enabled,HW_DEVICE_EXTERNAL_RESET)
#  define _hw_pin_pc6			_pin1, 317, hw_portc, 1, 6
#endif
#define _hw_port_c			_pin1, 319, hw_portc, 7, 0

#define _hw_pin_pd0			_pin1, 321, hw_portd, 1, 0
#define _hw_pin_pd1			_pin1, 322, hw_portd, 1, 1
#define _hw_pin_pd2			_pin1, 323, hw_portd, 1, 2
#define _hw_pin_pd3			_pin1, 324, hw_portd, 1, 3
#define _hw_pin_pd4			_pin1, 325, hw_portd, 1, 4
#define _hw_pin_pd5			_pin1, 326, hw_portd, 1, 5
#define _hw_pin_pd6			_pin1, 327, hw_portd, 1, 6
#define _hw_pin_pd7			_pin1, 328, hw_portd, 1, 7
#define _hw_port_d			_pin1, 329, hw_portd, 8, 0

/*  Aliases
 */
#define hw_pin_sck			hw_pin_pb5
#define hw_pin_miso			hw_pin_pb4
#define hw_pin_mosi			hw_pin_pb3
#define hw_pin_ss			hw_pin_pb2


/*  Analog input pins (with Digital Input Disable bits, stored in register `did`
 *  in hw_adc0)
 */
#define _hw_pin_pc0_did			, hw_adc0, did_0
#define _hw_pin_pc1_did			, hw_adc0, did_1
#define _hw_pin_pc2_did			, hw_adc0, did_2
#define _hw_pin_pc3_did			, hw_adc0, did_3
#define _hw_pin_pc4_did			, hw_adc0, did_4
#define _hw_pin_pc5_did			, hw_adc0, did_5

/* PD6 is AIN0
 * PD7 is AIN1
 */
#define _hw_pin_pd6_did			, hw_acmp0, did_0
#define _hw_pin_pd7_did			, hw_acmp0, did_1

/*  Pins ADC6/ADC7 are analog inputs only, no DID register.
 */
#define _hw_pin_adc6			_pin1a, 336
#define _hw_pin_adc7			_pin1a, 337
#define _hw_pin_adc6_did		,
#define _hw_pin_adc7_did		,

#define hw_pin_adc5			hw_pin_pc5
#define hw_pin_adc4			hw_pin_pc4
#define hw_pin_adc3			hw_pin_pc3
#define hw_pin_adc2			hw_pin_pc2
#define hw_pin_adc1			hw_pin_pc1
#define hw_pin_adc0			hw_pin_pc0
#define hw_pin_scl			hw_pin_pc5
#define hw_pin_sda			hw_pin_pc4

#define hw_pin_ain1			hw_pin_pd7
#define hw_pin_ain0			hw_pin_pd6
#define hw_pin_txd			hw_pin_pd1
#define hw_pin_rxd			hw_pin_pd0

#define hw_pin_oc0a			hw_pin_pd6
#define hw_pin_oc0b			hw_pin_pd5
#define hw_pin_oc1a			hw_pin_pb1
#define hw_pin_oc1b			hw_pin_pb2
#define hw_pin_oc2a			hw_pin_pb3
#define hw_pin_oc2b			hw_pin_pd3

/*  Pins by numbers
 */
/* #define _hw_is_dil_dil			, 1 */
/* #define _hw_is_28pdip_28pdip		, 1 */
/* #define _hw_is_28mlf_28mlf		, 1 */
/* #define _hw_is_32mlf_32mlf		, 1 */


#if defined HW_DEVICE_PACKAGE_28P
#
#  define hw_pin_1			hw_pin_pc6
#  define hw_pin_2			hw_pin_pd0
#  define hw_pin_3			hw_pin_pd1
#  define hw_pin_4			hw_pin_pd2
#  define hw_pin_5			hw_pin_pd3
#  define hw_pin_6			hw_pin_pd4
#  define hw_pin_9			hw_pin_pb6
#  define hw_pin_10			hw_pin_pb7
#  define hw_pin_11			hw_pin_pd5
#  define hw_pin_12			hw_pin_pd6
#  define hw_pin_13			hw_pin_pd7
#  define hw_pin_14			hw_pin_pb0
#  define hw_pin_15			hw_pin_pb1
#  define hw_pin_16			hw_pin_pb2
#  define hw_pin_17			hw_pin_pb3
#  define hw_pin_18			hw_pin_pb4
#  define hw_pin_19			hw_pin_pb5
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#
#elif defined HW_DEVICE_PACKAGE_28Q
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
/* #  define hw_pin_3			hw_pin_ */
/* #  define hw_pin_4			hw_pin_ */
#  define hw_pin_5			hw_pin_pb6
#  define hw_pin_6			hw_pin_pb7
#  define hw_pin_7			hw_pin_pd5
#  define hw_pin_8			hw_pin_pd6
#  define hw_pin_9			hw_pin_pd7
#  define hw_pin_10			hw_pin_pb0
#  define hw_pin_11			hw_pin_pb1
#  define hw_pin_12			hw_pin_pb2
#  define hw_pin_13			hw_pin_pb3
#  define hw_pin_14			hw_pin_pb4
#  define hw_pin_15			hw_pin_pb5
/* #  define hw_pin_16			hw_pin_ */
/* #  define hw_pin_17			hw_pin_ */
/* #  define hw_pin_18			hw_pin_ */
#  define hw_pin_19			hw_pin_pc0
#  define hw_pin_20			hw_pin_pc1
#  define hw_pin_21			hw_pin_pc2
#  define hw_pin_22			hw_pin_pc3
#  define hw_pin_23			hw_pin_pc4
#  define hw_pin_24			hw_pin_pc5
#  define hw_pin_25			hw_pin_pc6
#  define hw_pin_26			hw_pin_pd0
#  define hw_pin_27			hw_pin_pd1
#  define hw_pin_28			hw_pin_pd2
#
#elif defined HW_DEVICE_PACKAGE_32Q
#
#  define hw_pin_1			hw_pin_pd3
#  define hw_pin_2			hw_pin_pd4
#  define hw_pin_7			hw_pin_pb6
#  define hw_pin_8			hw_pin_pb7
#  define hw_pin_9			hw_pin_pd5
#  define hw_pin_10			hw_pin_pd6
#  define hw_pin_11			hw_pin_pd7
#  define hw_pin_12			hw_pin_pb0
#  define hw_pin_13			hw_pin_pb1
#  define hw_pin_14			hw_pin_pb2
#  define hw_pin_15			hw_pin_pb3
#  define hw_pin_16			hw_pin_pb4
#  define hw_pin_17			hw_pin_pb5
#  define hw_pin_19			hw_pin_adc6
#  define hw_pin_22			hw_pin_adc7
#  define hw_pin_23			hw_pin_pc0
#  define hw_pin_24			hw_pin_pc1
#  define hw_pin_25			hw_pin_pc2
#  define hw_pin_26			hw_pin_pc3
#  define hw_pin_27			hw_pin_pc4
#  define hw_pin_28			hw_pin_pc5
#  define hw_pin_29			hw_pin_pc6
#  define hw_pin_30			hw_pin_pd0
#  define hw_pin_31			hw_pin_pd1
#  define hw_pin_32			hw_pin_pd2
#
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Instance	        	class, id, address
 */
#define _hw_core0			_coreb, 101, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define _hw__coreb_osccal		_r8, 0x66, 0xFF, 0x00
#define _hw__coreb_prr			_r8, 0x64, 0xEF, 0x00
#define _hw__coreb_sreg			_r8, 0x5F, 0xFF, 0x00
#define _hw__coreb_sph			_r8, 0x5E, 0x03, 0x00
#define _hw__coreb_spl			_r8, 0x5D, 0xFF, 0x00
#define _hw__coreb_mcucr		_r8, 0x55, 0x73, 0x00
#define _hw__coreb_mcusr		_r8, 0x54, 0x0F, 0x00
#define _hw__coreb_smcr			_r8, 0x53, 0x0F, 0x00
#define _hw__coreb_gpior2		_r8, 0x4B, 0xFF, 0x00
#define _hw__coreb_gpior1		_r8, 0x4A, 0xFF, 0x00
#define _hw__coreb_gpior0		_r8, 0x3E, 0xFF, 0x00
#define _hw__coreb_eimsk		_r8, 0x3D, 0x03, 0x00
#define _hw__coreb_eifr			_r8, 0x3C, 0x03, 0x03

#define _hw__coreb_bods			_cb1, mcucr, 1, 6
#define _hw__coreb_bodse		_cb1, mcucr, 1, 5
#define _hw__coreb_pud			_cb1, mcucr, 1, 4
#define _hw__coreb_ivsel		_cb1, mcucr, 1, 1
#define _hw__coreb_ivce			_cb1, mcucr, 1, 0

#define _hw__coreb_wdrf			_cb1, mcusr, 1, 3
#define _hw__coreb_borf			_cb1, mcusr, 1, 2
#define _hw__coreb_extrf		_cb1, mcusr, 1, 1
#define _hw__coreb_porf			_cb1, mcusr, 1, 0
#define _hw__coreb_allrf		_cb1, mcusr, 4, 0	/* convenient */

#define _hw__coreb_sm			_cb1, smcr, 3, 1
#define _hw__coreb_se			_cb1, smcr, 1, 0

#define _hw__coreb_ie1			_cb1, eimsk, 1, 1
#define _hw__coreb_ie0			_cb1, eimsk, 1, 0

#define _hw__coreb_if1			_cb1, eifr, 1, 1
#define _hw__coreb_if0			_cb1, eifr, 1, 0

#define _hw__coreb_prtwi		_cb1, prr, 1, 7
#define _hw__coreb_prtim2		_cb1, prr, 1, 6
#define _hw__coreb_prtim0		_cb1, prr, 1, 5
#define _hw__coreb_prtim1		_cb1, prr, 1, 3
#define _hw__coreb_prspi		_cb1, prr, 1, 2
#define _hw__coreb_prusart		_cb1, prr, 1, 1
#define _hw__coreb_pradc		_cb1, prr, 1, 0

/*	Object regs
 */
#define _hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_pcic0			_pcicb, 350, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define _hw_pcic0_msk2			_r8, 0x6D, 0xFF, 0x00
#define _hw_pcic0_msk1			_r8, 0x6C, 0x7F, 0x00
#define _hw_pcic0_msk0			_r8, 0x6B, 0xFF, 0x00
#define _hw_pcic0_cr			_r8, 0x68, 0x07, 0x00
#define _hw_pcic0_fr			_r8, 0x3B, 0x07, 0x07

/*	Object bits
 */
#define _hw_pcic0_ie2			_ob1, cr, 1, 2
#define _hw_pcic0_ie1			_ob1, cr, 1, 1
#define _hw_pcic0_ie0			_ob1, cr, 1, 0

#define _hw_pcic0_if2			_ob1, fr, 1, 2
#define _hw_pcic0_if1			_ob1, fr, 1, 1
#define _hw_pcic0_if0			_ob1, fr, 1, 0

#define _hw_pcic0_hw_pin_pb0		_ob1, msk0, 1, 0
#define _hw_pcic0_hw_pin_pb1		_ob1, msk0, 1, 1
#define _hw_pcic0_hw_pin_pb2		_ob1, msk0, 1, 2
#define _hw_pcic0_hw_pin_pb3		_ob1, msk0, 1, 3
#define _hw_pcic0_hw_pin_pb4		_ob1, msk0, 1, 4
#define _hw_pcic0_hw_pin_pb5		_ob1, msk0, 1, 5
#define _hw_pcic0_hw_pin_pb6		_ob1, msk0, 1, 6
#define _hw_pcic0_hw_pin_pb7		_ob1, msk0, 1, 7

#define _hw_pcic0_hw_pin_pc0		_ob1, msk1, 1, 0
#define _hw_pcic0_hw_pin_pc1		_ob1, msk1, 1, 1
#define _hw_pcic0_hw_pin_pc2		_ob1, msk1, 1, 2
#define _hw_pcic0_hw_pin_pc3		_ob1, msk1, 1, 3
#define _hw_pcic0_hw_pin_pc4		_ob1, msk1, 1, 4
#define _hw_pcic0_hw_pin_pc5		_ob1, msk1, 1, 5
#define _hw_pcic0_hw_pin_pc6		_ob1, msk1, 1, 6

#define _hw_pcic0_hw_pin_pd0		_ob1, msk2, 1, 0
#define _hw_pcic0_hw_pin_pd1		_ob1, msk2, 1, 1
#define _hw_pcic0_hw_pin_pd2		_ob1, msk2, 1, 2
#define _hw_pcic0_hw_pin_pd3		_ob1, msk2, 1, 3
#define _hw_pcic0_hw_pin_pd4		_ob1, msk2, 1, 4
#define _hw_pcic0_hw_pin_pd5		_ob1, msk2, 1, 5
#define _hw_pcic0_hw_pin_pd6		_ob1, msk2, 1, 6
#define _hw_pcic0_hw_pin_pd7		_ob1, msk2, 1, 7


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_wdog0			_wdogb, 109, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define _hw__wdogb_csr			_r8, 0x60, 0xFF, 0x80

#define _hw__wdogb_if			_cb1, csr, 1, 7
#define _hw__wdogb_ie			_cb1, csr, 1, 6
#define _hw__wdogb_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define _hw__wdogb_wdce			_cb1, csr, 1, 4
#define _hw__wdogb_wde			_cb1, csr, 1, 3

#define _hw__wdogb_wdeie		_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define _hw__wdogb_wdifie		_cb1, csr, 2, 6 /* convenient for clearing irq */
#define _hw__wdogb_wdall		_cb1, csr, 7, 0 /* convenient for turning wd off */

#define _hw__wdogb_wdrf			_xob1, hw_core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Timer Counter 0							       *
 *									       *
 *	Derived from _c8a counter with specialized register map		       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_counter0			_c8a, 400, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define _hw__c8a_ccra			_r8, 0x44, 0xF3, 0x00
#define _hw__c8a_ccrb			_r8, 0x45, 0xCF, 0x00
#define _hw__c8a_count			_r8, 0x46, 0xFF, 0x00
#define _hw__c8a_ocra			_r8, 0x47, 0xFF, 0x00
#define _hw__c8a_compare0		_r8, 0x47, 0xFF, 0x00
#define _hw__c8a_ocrb			_r8, 0x48, 0xFF, 0x00
#define _hw__c8a_compare1		_r8, 0x48, 0xFF, 0x00
#define _hw__c8a_imsk			_r8, 0x6E, 0x07, 0x00
#define _hw__c8a_ifr			_r8, 0x35, 0x07, 0x07

#define _hw__c8a_compare0_mode		_cb1, ccra, 2, 6
#define _hw__c8a_compare1_mode		_cb1, ccra, 2, 4
#define _hw__c8a_wgm			_cb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define _hw__c8a_foca			_cb1, ccrb, 1, 7
#define _hw__c8a_focb			_cb1, ccrb, 1, 6
#define _hw__c8a_cs			_cb1, ccrb, 3, 0

#define _hw__c8a_iecm1			_cb1, imsk, 1, 2
#define _hw__c8a_iecm0			_cb1, imsk, 1, 1
#define _hw__c8a_ieov			_cb1, imsk, 1, 0

#define _hw__c8a_ifcm1			_cb1, ifr, 1, 2
#define _hw__c8a_ifcm0			_cb1, ifr, 1, 1
#define _hw__c8a_ifov			_cb1, ifr, 1, 0

/*	Compare units			class, id, counter, ocn, ion
 */
#define _hw_counter0_compare0		_ocua, 401, hw_counter0, compare0, hw_pin_oc0a
#define _hw_counter0_compare1		_ocua, 402, hw_counter0, compare1, hw_pin_oc0b

/*	Counter0 prescaler
 */
#define hw_counter0_prescaler0		hw_psc0


/*******************************************************************************
 *									       *
 *	Timer Counter 1							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, name, id, address
 */
#define _hw_counter1			_c16a, 410, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define _hw__c16a_ccra			_r8,  0x80, 0xF3,   0x00
#define _hw__c16a_ccrb			_r8,  0x81, 0xDF,   0x00
#define _hw__c16a_ccrc			_r8,  0x82, 0xC0,   0x00
#define _hw__c16a_count			_r16, 0x84, 0xFFFF, 0x0000
#define _hw__c16a_compare0		_r16, 0x88, 0xFFFF, 0x0000
#define _hw__c16a_compare1		_r16, 0x8A, 0xFFFF, 0x0000
#define _hw__c16a_capture0		_r16, 0x86, 0xFFFF, 0x0000
#define _hw__c16a_imsk			_r8,  0x6F, 0x27,   0x00
#define _hw__c16a_ifr			_r8,  0x36, 0x27,   0x27

#define _hw__c16a_acic			_xob1, hw_acmp0, csr, 1, 2

/*	Counter1 compare units		class, id, counter, channel, io
 */
#define _hw_counter1_compare0		_ocua, 411, hw_counter1, compare0, hw_pin_oc1a
#define _hw_counter1_compare1		_ocua, 412, hw_counter1, compare1, hw_pin_oc1b

/*	Counter1 capture unit		class, id, counter, reg, io
 */
#define _hw_counter1_capture0		_icua, 413, hw_counter1, capture0, hw_pin_icp1

/*	Counter1 prescaler
 */
#define hw_counter1_prescaler0		hw_psc0


/*******************************************************************************
 *									       *
 *	Timer Counter 2							       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */
#define _hw_counter2			_c8b, 420, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define _hw__c8b_ccra			_r8, 0xB0, 0xF3, 0x00
#define _hw__c8b_ccrb			_r8, 0xB1, 0xCF, 0x00
#define _hw__c8b_count			_r8, 0xB2, 0xFF, 0x00
#define _hw__c8b_ocra			_r8, 0xB3, 0xFF, 0x00
#define _hw__c8b_compare0		_r8, 0xB3, 0xFF, 0x00
#define _hw__c8b_ocrb			_r8, 0xB4, 0xFF, 0x00
#define _hw__c8b_compare1		_r8, 0xB4, 0xFF, 0x00
#define _hw__c8b_imsk			_r8, 0x70, 0x07, 0x00
#define _hw__c8b_ifr			_r8, 0x37, 0x07, 0x07
#define _hw__c8b_assr			_r8, 0xB6, 0x60, 0x00

#define _hw__c8b_compare0_mode		_cb1, ccra, 2, 6
#define _hw__c8b_compare1_mode		_cb1, ccra, 2, 4
#define _hw__c8b_wgm			_cb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define _hw__c8b_foca			_cb1, ccrb, 1, 7
#define _hw__c8b_focb			_cb1, ccrb, 1, 6
#define _hw__c8b_cs			_cb1, ccrb, 3, 0

#define _hw__c8b_iecm1			_cb1, imsk, 1, 2
#define _hw__c8b_iecm0			_cb1, imsk, 1, 1
#define _hw__c8b_ieov			_cb1, imsk, 1, 0

#define _hw__c8b_ifcm1			_cb1, ifr, 1, 2
#define _hw__c8b_ifcm0			_cb1, ifr, 1, 1
#define _hw__c8b_ifov			_cb1, ifr, 1, 0

//#define _hw__c8b_psrasy			_xob1, hw_core0, psrasy /* convenient */

/*	Counter2 compare units		class, id, counter, channel, io
 */
#define _hw_counter2_compare0		_ocua, 421, hw_counter2, compare0, hw_pin_oc2a
#define _hw_counter2_compare1		_ocua, 422, hw_counter2, compare1, hw_pin_oc2b

/*	Counter2 prescaler
 */
#define hw_counter2_prescaler0		hw_psc1


/*******************************************************************************
 *									       *
 *	hw_counter0/hw_counter1 prescaler				       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */				        
#define _hw_psc0			_psca, 500, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define _hw_psc0_cr			_r8, 0x43, 0x81, 0x00

#define _hw_psc0_tsm			_cb1, cr, 1, 7
//#define _hw_psc0_psrasy			_cb1, cr, 1, 1
#define _hw_psc0_psr			_cb1, cr, 1, 0
//#define _hw_psc0_tsmpsr			_ob2, cr, 1, 7, 1, cr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	hw_counter2 prescaler						       *
 *									       *
 *	FIXME: hw_psc1 shares the tsm bit with hw_psc0			       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */				        
#define _hw_psc1			_psca, 510, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define _hw_psc1_psr			_xob1, hw_psc0, cr, 1, 1
#define _hw_psc1_tsm			_xob1, hw_psc0, tsm


/*******************************************************************************
 *									       *
 *	UART								       *
 *									       *
 *******************************************************************************/

/*	Object
 */
#define _hw_uart0			_uarta, 600, 0xC0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__uarta_dr			_r8,  0x06, 0xFF,   0x00
#define _hw__uarta_ubrr			_r16, 0x04, 0x0FFF, 0x0000
#define _hw__uarta_csrc			_r8,  0x02, 0xFF,   0x00
#define _hw__uarta_csrb			_r8,  0x01, 0xFD,   0x00
#define _hw__uarta_csra			_r8,  0x00, 0x43,   0x40

/*	Class bits
 */
#define _hw__uarta_brr			_cb1, ubrr, 12, 0

#define _hw__uarta_ifrxc		_cb1, csra, 1, 7
#define _hw__uarta_iftxc		_cb1, csra, 1, 6
#define _hw__uarta_iftxqnf		_cb1, csra, 1, 5
#define _hw__uarta_fe			_cb1, csra, 1, 4
#define _hw__uarta_dor			_cb1, csra, 1, 3
#define _hw__uarta_pe			_cb1, csra, 1, 2
#define _hw__uarta_2x			_cb1, csra, 1, 1
#define _hw__uarta_mpcm			_cb1, csra, 1, 0

#define _hw__uarta_ierxc		_cb1, csrb, 1, 7
#define _hw__uarta_ietxc		_cb1, csrb, 1, 6
#define _hw__uarta_ietxqnf		_cb1, csrb, 1, 5
#define _hw__uarta_rxen			_cb1, csrb, 1, 4
#define _hw__uarta_txen			_cb1, csrb, 1, 3
#define _hw__uarta_rxb8			_cb1, csrb, 1, 1
#define _hw__uarta_txb8			_cb1, csrb, 1, 0

#define _hw__uarta_msel			_cb1, csrc, 2, 6
#define _hw__uarta_pm			_cb1, csrc, 2, 4
#define _hw__uarta_sbs			_cb1, csrc, 1, 3
#define _hw__uarta_cpol			_cb1, csrc, 1, 0

#define _hw__uarta_csz			_cb2, csrb, 1, 2, 2, csrc, 2, 1, 0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, id, address
 */				        
#define _hw_acmp0			_acmpb, 710, 0

/*	Class registers			class, address, write mask, flags mask
 */				        
#define _hw__acmpb_csr			_r8, 0x50, 0xDF, 0x10
#define _hw__acmpb_did			_r8, 0x7F, 0x03, 0x00

#define _hw__acmpb_if			_cb1, csr, 1, 4
#define _hw__acmpb_ie			_cb1, csr, 1, 3

#define _hw__acmpb_acme			_xob1, hw_adc0, srb,   1, 6
#define _hw__acmpb_aden			_xob1, hw_adc0, sra,   1, 7
#define _hw__acmpb_admux		_xob1, hw_adc0, admux, 4, 0

#define _hw__acmpb_did_0		_cb1, did, 1, 0
#define _hw__acmpb_did_1		_cb1, did, 1, 1

/*	Object registers		class, address, write mask, flags mask
 */				        
#define _hw_acmp0_csr			_r8, 0x50, 0xDF, 0x10


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#define _hw_adc0			_ad10b, 720, 0

#define _hw__ad10b_admux		_r8,  0x7C,   0xEF,   0x00
#define _hw__ad10b_sra			_r8,  0x7A,   0xFF,   0x10
#define _hw__ad10b_adc			_r16, 0x78, 0x0000, 0x0000
#define _hw__ad10b_adch			_r8,  0x79,   0x00,   0x00
#define _hw__ad10b_adcl			_r8,  0x78,   0x00,   0x00
#define _hw__ad10b_srb			_r8,  0x7B,   0x47,   0x00
#define _hw__ad10b_did			_r8,  0x7E,   0x3F,   0x00 /* port C */

#define _hw__ad10b_refs			_cb1, admux, 2, 6
#define _hw__ad10b_lar			_cb1, admux, 1, 5
#define _hw__ad10b_mux			_cb1, admux, 4, 0

#define _hw__ad10b_en			_cb1, sra, 1, 7
#define _hw__ad10b_sc			_cb1, sra, 1, 6
#define _hw__ad10b_ate			_cb1, sra, 1, 5
#define _hw__ad10b_if			_cb1, sra, 1, 4
#define _hw__ad10b_ie			_cb1, sra, 1, 3
#define _hw__ad10b_ps			_cb1, sra, 3, 0

#define _hw__ad10b_me			_cb1, srb, 1, 6
#define _hw__ad10b_ts			_cb1, srb, 3, 0

#define _hw__ad10b_did_0		_cb1, did, 1, 0
#define _hw__ad10b_did_1		_cb1, did, 1, 1
#define _hw__ad10b_did_2		_cb1, did, 1, 2
#define _hw__ad10b_did_3		_cb1, did, 1, 3
#define _hw__ad10b_did_4		_cb1, did, 1, 4
#define _hw__ad10b_did_5		_cb1, did, 1, 5
#define _hw__ad10b_did_6		_cb1, did, 1, 6
#define _hw__ad10b_did_7		_cb1, did, 1, 7


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__eeproma

/*	Instance	        	class, id, address
 */
#define _hw_eeprom0			_eeproma, 1000, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define _hw__eeproma_arh		_r8,  0x42,   0x03, 0x00
#define _hw__eeproma_arl		_r8,  0x41,   0xFF, 0x00
#define _hw__eeproma_ar			_r16, 0x41, 0x03FF, 0x00
#define _hw__eeproma_dr			_r8,  0x40,   0xFF, 0x00
#define _hw__eeproma_cr			_r8,  0x3F,   0x3F, 0x00

#define _hw__eeproma_pm			_cb1, cr, 2, 4
#define _hw__eeproma_rie		_cb1, cr, 1, 3
#define _hw__eeproma_mpe		_cb1, cr, 1, 2
#define _hw__eeproma_pe			_cb1, cr, 1, 1
#define _hw__eeproma_re			_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

#define _hw_class__flasha

/*	Instance	        	class, id, address
 */
#define _hw_flash0			_flasha, 1100, 0


/*	Class regs			class, address, write mask, flags mask
 */
#define _hw__flasha_csr			_r8, 0x57, 0xBF, 0x00

#define _hw__flasha_spmie		_cb1, csr, 1, 7
#define _hw__flasha_rwwsb		_cb1, csr, 1, 6
#define _hw__flasha_sigrd		_cb1, csr, 1, 5
#define _hw__flasha_rwwsre		_cb1, csr, 1, 4
#define _hw__flasha_blbset		_cb1, csr, 1, 3
#define _hw__flasha_pgwrt		_cb1, csr, 1, 2
#define _hw__flasha_pgers		_cb1, csr, 1, 1
#define _hw__flasha_spmen		_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	Software UART							       *
 *									       *
 *******************************************************************************/

#define _hw_class__swuarta

#if defined hw_swuart0_pin_rx || defined hw_swuart0_pin_tx
/*
 *	Object hw_swuart0
 */
#define _hw_swuart0			_swuarta, 1200, 0
#define _hw_swuart0_dtn _hw_rc(hw_swuart0_counter,count), (intptr_t)&__hw_swuart0_dtn, -1, 0x00
#define _hw_swuart0_dt0	_hw_rc(hw_swuart0_counter,count), (intptr_t)&__hw_swuart0_dt0, -1, 0x00
#define _hw_swuart0__st			_hw_ra(hw_core0, gpior0)
#define _hw_swuart0_sr			_hw_core0_gpior0
#define _hw_swuart0_synced		_ob1, sr, 1, 0
#endif

#if defined hw_swuart1_pin_rx || defined hw_swuart1_pin_tx
/*
 *	Object hw_swuart1
 */
#define _hw_swuart1			_swuarta, 1210, 0
#define _hw_swuart1_dtn _hw_rc(hw_swuart1_counter,count), (intptr_t)&__hw_swuart1_dtn, -1, 0x00
#define _hw_swuart1_dt0	_hw_rc(hw_swuart1_counter,count), (intptr_t)&__hw_swuart1_dt0, -1, 0x00
#define _hw_swuart1__st			_hw_ra(hw_core0, gpior1)
#define _hw_swuart1_sr			_hw_core0_gpior1
#define _hw_swuart1_synced		_ob1, sr, 1, 0
#endif


/**
 * @page atmegax8
 *
 * @section atmegax8_target Target definition
 *
 * The inclusion of the device-specific header leads to the definition of the
 * following symbols:
 *
 * Symbol               | Possible values | Comments
 * :--------------------|--------------|:-----------
 * `HW_DEVICE`          | `attiny24`<br>`attiny44`<br>`attiny84` | Name of the device
 * `HW_DEVICE_PACKAGE`  | `14pdip`     | Packaging of the device.
 */

/**
 * @page atmegax8
 * @section atmegax8_fuses Defining the fuse values
 *
 * Optionnaly, before including the device-specific header, fuse symbols can be
 * defined to describe the target more precisely. If these symbols are not
 * defined by the user, HWA will define them from the default values.
 */

/**
 * @page atmegax8
 * @subsection atmegax8_fuses_clocking Clocking
 *
 * Symbol                |Valid values | Comments
 * :---------------------|-------------|:-----------
 * `HW_DEVICE_CLK_SRC`   |`external`<br>`rc_8MHz`<br>`rc_128kHz`<br>`xosc`|External source on pin CLKI<br>Internal RC oscillator<br>Internal RC oscillator<br>Crystal oscillator between pins XTAL1 and XTAL2
 * `HW_DEVICE_CLK_SRC_HZ`|Integer     | Clock frequency for `external` and `xosc` clock source
 * `HW_DEVICE_CLK_PSC`   |`8`<br>`1`  |Clock divided by 8<br>Clock not divided
 */
#define _hw_is_external_external			, 1
#define _hw_is_rc_8MHz_rc_8MHz				, 1
#define _hw_is_rc_128kHz_rc_128kHz			, 1
#define _hw_is_low_freq_xosc_low_freq_xosc		, 1
#define _hw_is_low_power_xosc_low_power_xosc		, 1
#define _hw_is_full_swing_xosc_full_swing_xosc		, 1

/*  Define default HW_DEVICE_CLK_SRC_HZ as void so that hw_syshz_base can be checked
 */
#ifndef HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_CLK_SRC_HZ
#endif

#ifndef HW_DEVICE_CLK_SRC
#  define HW_DEVICE_CLK_SRC				rc_8MHz
#endif

#if HW_IS(external,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				0
#  define HW_DEVICE_CKSEL0				0
#elif HW_IS(rc_8MHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				0
#  define hw_syshz_base					8000000
#elif HW_IS(rc_128kHz,HW_DEVICE_CLK_SRC)
#  define HW_DEVICE_CKSEL31				1
#  define HW_DEVICE_CKSEL0				1
#  define hw_syshz_base					128000
#elif HW_IS(HW_DEVICE_CLK_SRC, low_freq_xosc)
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#  define HW_DEVICE_CKSEL31				2
#
#elif HW_IS(HW_DEVICE_CLK_SRC, low_power_xosc)
#  define hw_syshz_base					HW_DEVICE_CLK_SRC_HZ
#  if HW_DEVICE_CLK_SRC_HZ < 900000
#    define HW_DEVICE_CKSEL31				4
#  elif HW_DEVICE_CLK_SRC_HZ < 3000000
#    define HW_DEVICE_CKSEL31				5
#  elif HW_DEVICE_CLK_SRC_HZ < 8000000
#    define HW_DEVICE_CKSEL31				6
#  else
#    define HW_DEVICE_CKSEL31				7
#  endif
#elif HW_IS(HW_DEVICE_CLK_SRC, full_swing_xosc)
#  ifndef HW_DEVICE_CLK_SRC_HZ
#    error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#  else
#    define hw_syshz_base				HW_DEVICE_CLK_SRC_HZ
#    define HW_DEVICE_CKSEL31				3
#  endif
#else
#  error HW_DEVICE_CLK_SRC can be `rc_8MHz`, `rc_128kHz`, `low_freq_xosc`, `low_power_xosc`, `full_swing_xosc`, or `external`.
#endif

/*  Check that we have a valid hw_syshz_base
 */
#if HW_IS(,hw_syshz_base)
#  error HW_DEVICE_CLK_SRC_HZ must be defined as the frequency of the crystal used for clocking
#endif

#define _hw_is_4CK_4CK					, 1
#define _hw_is_4CK_4ms_4CK_4ms				, 1
#define _hw_is_4CK_64ms_4CK_64ms			, 1
#define _hw_is_6CK_14CK_6CK_14CK			, 1
#define _hw_is_6CK_14CK_4ms_6CK_14CK_4ms		, 1
#define _hw_is_6CK_14CK_64ms_6CK_14CK_64ms		, 1
#define _hw_is_1KCK_4ms_1KCK_4ms			, 1
#define _hw_is_1KCK_64ms_1KCK_64ms			, 1
#define _hw_is_32KCK_64ms_32KCK_64ms			, 1
#define _hw_is_258CK_14CK_4ms_258CK_14CK_4ms		, 1
#define _hw_is_258CK_14CK_64ms_258CK_14CK_64ms		, 1
#define _hw_is_1KCK_14CK_1KCK_14CK			, 1
#define _hw_is_1KCK_14CK_4ms_1KCK_14CK_4ms		, 1
#define _hw_is_1KCK_14CK_64ms_1KCK_14CK_64ms		, 1
#define _hw_is_16KCK_14CK_16KCK_14CK			, 1
#define _hw_is_16KCK_14CK_4ms_16KCK_14CK_4ms		, 1
#define _hw_is_16KCK_14CK_64ms_16KCK_14CK_64ms		, 1

/*	SUT
 */
#if defined HW_DEVICE_STARTUP_DELAYS
#  if HW_DEVICE_CKSEL31 < 2
#    define HW_DEVICE_CKSEL0				0
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_4ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 6CK_14CK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `6CK_14CK`, `6CK_14CK_4ms`, or `6CK_14CK_64ms`.
#    endif
#  elif HW_DEVICE_CKSEL31 == 2
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK)
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_4ms)
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 4CK_64ms)
#      define HW_DEVICE_SUT10				2
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `4CK`, `4CK_4ms`, or `4CK_64ms`.
#    endif
#  else
#    if HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 258CK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				0
#      define HW_DEVICE_SUT10				3
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 1KCK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				0
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				1
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_4ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				2
#    elif HW_IS(HW_DEVICE_STARTUP_DELAYS, 16KCK_14CK_64ms)
#      define HW_DEVICE_CKSEL0				1
#      define HW_DEVICE_SUT10				3
#    else
#      error HW_DEVICE_STARTUP_DELAYS must be defined as one of `258CK_14CK_4ms`, `258CK_14CK_64ms`, `1KCK_14CK`, `1KCK_14CK_4ms`, `1KCK_14CK_64ms`, `16KCK_14CK`, `16KCK_14CK_4ms`, or `16KCK_14CK_64ms`.
#    endif
#  endif
#else
#  define HW_DEVICE_SUT10				2
#endif


#if !defined HW_DEVICE_CLK_PSC
#  define HW_DEVICE_CLK_PSC				8
#endif
#if HW_DEVICE_CLK_PSC == 8
#  define HW_DEVICE_CKDIV8				0
#  define hw_syshz					hw_syshz_base/8
#elif HW_DEVICE_CLK_PSC == 1
#  define HW_DEVICE_CKDIV8				1
#  define hw_syshz					hw_syshz_base
#else
#  error HW_DEVICE_CLK_PSC must be defined as one of `8` or `1`.
#endif

#if !defined HW_DEVICE_CLOCK_OUTPUT
#  define HW_DEVICE_CLOCK_OUTPUT			disabled
#endif
#if HW_IS(HW_DEVICE_CLOCK_OUTPUT, enabled)
#  define HW_DEVICE_CKOUT				0
#elif HW_IS(HW_DEVICE_CLOCK_OUTPUT, disabled)
#  define HW_DEVICE_CKOUT				1
#else
#  error HW_DEVICE_CLOCK_OUTPUT must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_EXTERNAL_RESET
#  define HW_DEVICE_EXTERNAL_RESET			enabled
#endif
#if HW_IS(HW_DEVICE_EXTERNAL_RESET, enabled)
#  define HW_DEVICE_RSTDISBL				1
#elif HW_IS(HW_DEVICE_EXTERNAL_RESET, disabled)
#  define HW_DEVICE_RSTDISBL				0
#else
#  error HW_DEVICE_EXTERNAL_RESET must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_DEBUG_WIRE
#  define HW_DEVICE_DEBUG_WIRE				disabled
#endif
#if HW_IS(HW_DEVICE_DEBUG_WIRE, enabled)
#  define HW_DEVICE_DWEN				0
#elif HW_IS(HW_DEVICE_DEBUG_WIRE, disabled)
#  define HW_DEVICE_DWEN				1
#else
#  error HW_DEVICE_DEBUG_WIRE must be defined as `enabled` or `disabled` (default).
#endif

#if !defined HW_DEVICE_SERIAL_PROGRAMMING
#  define HW_DEVICE_SERIAL_PROGRAMMING			enabled
#endif
#if HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, enabled)
#  define HW_DEVICE_SPIEN				0
#elif HW_IS(HW_DEVICE_SERIAL_PROGRAMMING, disabled)
#  define HW_DEVICE_SPIEN				1
#else
#  error HW_DEVICE_SERIAL_PROGRAMMING must be defined as `enabled` (default) or `disabled`.
#endif

#if !defined HW_DEVICE_WATCHDOG_ALWAYS_ON
#  define HW_DEVICE_WATCHDOG_ALWAYS_ON			no
#endif
#if HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, yes)
#  define HW_DEVICE_WDTON				0
#elif HW_IS(HW_DEVICE_WATCHDOG_ALWAYS_ON, no)
#  define HW_DEVICE_WDTON				1
#else
#  error HW_DEVICE_WATCHDOG_ALWAYS_ON must be defined as `yes` or `no` (default).
#endif

#if !defined HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE
#  define HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE	no
#endif
#if HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, yes)
#  define HW_DEVICE_EESAVE				0
#elif HW_IS(HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE, no)
#  define HW_DEVICE_EESAVE				1
#else
#  error HW_DEVICE_PRESERVE_EEPROM_FROM_CHIP_ERASE must be defined as `yes` or `no` (default).
#endif

#define _hw_is_1700_2000mV_1700_2000mV			, 1
#define _hw_is_2500_2900mV_2500_2900mV			, 1
#define _hw_is_4100_4500mV_4100_4500mV			, 1

#if !defined HW_DEVICE_BROWNOUT_DETECTION
#  define HW_DEVICE_BROWNOUT_DETECTION			off
#endif
#if HW_IS(HW_DEVICE_BROWNOUT_DETECTION, off)
#  define HW_DEVICE_BODLEVEL				7
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 1700_2000mV)
#  define HW_DEVICE_BODLEVEL				6
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 2500_2900mV)
#  define HW_DEVICE_BODLEVEL				5
#elif HW_IS(HW_DEVICE_BROWNOUT_DETECTION, 4100_4500mV)
#  define HW_DEVICE_BODLEVEL				4
#else
#  error HW_DEVICE_BROWNOUT_DETECTION must be defined as `1700_2000mV`, `2500_2900mV`, `4100_4500mV` or `off` (default).
#endif

#define _hw_is_application_application			, 1
#define _hw_is_bootloader_bootloader			, 1

/**
 * @def HW_DEVICE_BOOT
 * @brief Whether the device starts the bootloader (in the boot Flash) or the application.
 * @hideinitializer
 */
#if !defined HW_DEVICE_BOOT
#  define HW_DEVICE_BOOT				application
#endif
#if HW_IS(HW_DEVICE_BOOT, application)
#  define HW_DEVICE_BOOTRST				1
#elif HW_IS(HW_DEVICE_BOOT, bootloader)
#  define HW_DEVICE_BOOTRST				0
#else
#  error HW_DEVICE_RESET_VECTOR must be defined as `bootloader` or `application` (default).
#endif

#define HW_DEVICE_ATMEGAX8

/**
 * @page atmegax8
 * <br>
 */
