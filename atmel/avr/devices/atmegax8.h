
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega48A/PA/88A/PA/168A/PA/328/P devices
 */

/**
 * @ingroup atmelavr_devices
 * @defgroup atmegax8 ATmega48A/PA/88A/PA/168A/PA/328/P
 * @{
 *
 * Content of the device:
 *
 *  * @ref atmelavr_coreb "core0":			the core
 *  * @ref atmelavr_wda "watchdog0":			watchdog (WDG)
 *  * @ref atmelavr_inta "int0":			Low level interrupt (INT0)
 *  * @ref atmelavr_inta "int1":			Low level interrupt (INT1)
 *  * @ref atmelavr_gpa "portb":			general purpose I/O port B (PORTB)
 *    * @ref atmelavr_ioa "(portb,0..7)":		general purpose I/O pins (PB0..PB7)
 *    * @ref atmelavr_pxa "(portb,pcic)":		pin-change interrupt controller
 *  * @ref atmelavr_gpa "portc":			general purpose I/O port C (PORTC)
 *    * @ref atmelavr_ioa "(portc,0..6)":		general purpose I/O pins (PC0..PC6)
 *    * @ref atmelavr_pxa "(portb,pcic)":		pin-change interrupt controller
 *  * @ref atmelavr_gpa "portd":			general purpose I/O port D (PORTD)
 *    * @ref atmelavr_ioa "(portd,0..7)":		general purpose I/O pins (PD0..PD7)
 *    * @ref atmelavr_pxa "(portd,pcic)":		pin-change interrupt controller
 *  * @ref atmelavr_cta "counter0":			8-bit counter-timer
 *    * @ref atmelavr_psa "(counter0,prescaler)":	counter0/counter1 prescaler
 *    * @ref atmelavr_oca "(counter0,compare0)":	compare unit 0 of counter0
 *      * @ref atmelavr_ioa "(counter0,compare0,pin)":	counter0 compare0 output (OC0A)
 *    * @ref atmelavr_oca "(counter0,compare1)":	compare unit 1 of counter0
 *      * @ref atmelavr_ioa "(counter0,compare1,pin)":	counter0 compare1 output (OC0B)
 *    * @ref atmelavr_ioa "(counter0,pin)":		external clock source (T0)
 *  * @ref atmelavr_ctd "counter1":			16-bit counter-timer
 *    * @ref atmelavr_psa "(counter1,prescaler)":	counter0/counter1 prescaler
 *    * @ref atmelavr_occ "(counter1,compare0)":	compare unit 0 of counter1
 *      * @ref atmelavr_ioa "(counter1,compare0,pin)":	counter1 compare0 output (OC1A)
 *    * @ref atmelavr_occ "(counter1,compare1)":	compare unit 1 of counter1
 *      * @ref atmelavr_ioa "(counter1,compare1,pin)":	counter1 compare1 output (OC1B)
 *    * @ref atmelavr_ica "(counter1,capture0)":	capture unit 0 of counter1
 *      * @ref atmelavr_ioa "(counter1,capture0,pin)":	counter1 capture0 input (ICP1)
 *    * @ref atmelavr_ioa "(counter1,pin)":		external clock source (T1)
 *  * @ref atmelavr_ctc "counter2":			8-bit counter-timer
 *    * @ref atmelavr_psa "(counter2,prescaler)":	counter0/counter1 prescaler
 *    * @ref atmelavr_oca "(counter2,compare0)":	compare unit 0 of counter0
 *      * @ref atmelavr_ioa "(counter2,compare0,pin)":	counter0 compare0 output (OC0A)
 *    * @ref atmelavr_oca "(counter2,compare1)":	compare unit 1 of counter0
 *      * @ref atmelavr_ioa "(counter2,compare1,pin)":	counter0 compare1 output (OC0B)
 *  * @ref atmelavr_spia "spi0":			Serial Peripheral Interface
 *    * @ref atmelavr_ioa "(spi0,mosi)":		  (MOSI)
 *    * @ref atmelavr_ioa "(spi0,mosi)":		  (MISO)
 *    * @ref atmelavr_ioa "(spi0,sck)":			  (SCK)
 *    * @ref atmelavr_ioa "(spi0,ss)":			  (SS)
 *  * @ref atmelavr_uarta "uart0":			Universal Asynchronous Receiver Transmitter (USART0)
 *  * @ref atmelavr_twia "twi0":			2-wire Serial Interface
 *  * @ref atmelavr_aca "acmp0":			analog Comparator
 *    * @ref atmelavr_ioa "(pin,ain0)":			analog comparator positive input (AIN0)
 *    * @ref atmelavr_ioa "(pin,ain1)":			analog comparator negative input (AIN1)
 *  * @ref atmelavr_adb "adc0":				10-bit Analog to Digital Converter (ADC)
 *    * @ref atmelavr_ioa "(pin,adc0..7)":		ADC inputs
 *  * @ref atmelavr_fla "flash0":			Flash memory
 *  * @ref atmelavr_eea "eeprom0":			EEPROM memory
 */

/* Litterature:
 * * AVR532: Migration from ATmega48/88/168 to ATmega48A/88A/168A
 * * AVR512: Migration from ATmega48/88/168 to ATmega48P/88P/168P
 * * AVR528: Migrating from ATmega48P/88P/168P to ATmega48PA/88PA/168PA
 */

/**
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name.
 *
 * @{
 */

/**
 *  Device family
 */
#define HW_DEVICE_ATMEGAX8

/**
 *  Address of first RAM byte
 */
#define HW_DEVICE_RAM_START		0x0100

/** @} */
/** @} */


#include "../hwa_1.h"
#include "atmegax8_fuses.h"


#define hw_int0_irq			_irq,  1, int0,	     ie,     if
#define hw_int1_irq			_irq,  2, int1,	     ie,     if
#define hw_pcic0_irq			_irq,  3, pcic0,     ie,     if
#define hw_pcic1_irq			_irq,  4, pcic1,     ie,     if
#define hw_pcic2_irq			_irq,  5, pcic2,     ie,     if
#define hw_watchdog0_irq		_irq,  6, watchdog0, ie,     if
#define hw_counter2_irq_compare0	_irq,  7, counter2,  ocie0,  ocif0
#define hw_counter2_compare0_irq	_irq,  7, counter2,  ocie0,  ocif0
#define hw_counter2_irq_compare1	_irq,  8, counter2,  ocie1,  ocif1
#define hw_counter2_compare1_irq	_irq,  8, counter2,  ocie1,  ocif1
#define hw_counter2_irq_overflow	_irq,  9, counter2,  ie,     if
#define hw_counter2_irq			_irq,  9, counter2,  ie,     if
#define hw_counter1_irq_capture0	_irq, 10, counter1,  icie0,  icif0
#define hw_counter1_capture0_irq	_irq, 10, counter1,  icie0,  icif0
#define hw_counter1_irq_compare0	_irq, 11, counter1,  ocie0,  ocif0
#define hw_counter1_compare0_irq	_irq, 11, counter1,  ocie0,  ocif0
#define hw_counter1_irq_compare1	_irq, 12, counter1,  ocie1,  ocif1
#define hw_counter1_compare1_irq	_irq, 12, counter1,  ocie1,  ocif1
#define hw_counter1_irq_overflow	_irq, 13, counter1,  ie,     if
#define hw_counter1_irq			_irq, 13, counter1,  ie,     if
#define hw_counter0_irq_compare0	_irq, 14, counter0,  ocie0,  ocif0
#define hw_counter0_compare0_irq	_irq, 14, counter0,  ocie0,  ocif0
#define hw_counter0_irq_compare1	_irq, 15, counter0,  ocie1,  ocif1
#define hw_counter0_compare1_irq	_irq, 15, counter0,  ocie1,  ocif1
#define hw_counter0_irq_overflow	_irq, 16, counter0,  ie,     if
#define hw_counter0_irq			_irq, 16, counter0,  ie,     if
#define hw_spi0_irq			_irq, 17, spi0,	     ie,     if
#define hw_spi0_irq_txc			_irq, 17, spi0,	     ie,     if
#define hw_uart0_irq			_irq,   , , , /* FIXME: should create a class for concatenation */
#define hw_uart0_irq_rxc		_irq, 18, uart0,     ierxc,  ifrxc
#define hw_uart0_irq_txqnf		_irq, 19, uart0,     ietxqe, iftxqnf
#define hw_uart0_irq_txc		_irq, 20, uart0,     ietxc,  iftxc
#define hw_adc0_irq			_irq, 21, adc0,	     ie,     if
#define hw_eeprom0_irq			_irq, 22, eeprom0,   ie,     /* no irq flag */
#define hw_eeprom0_irq_ready		_irq, 22, eeprom0,   ie,
#define hw_acmp0_irq			_irq, 23, acmp0,     ie,     if
#define hw_twi0_irq			_irq, 24, twi0,	     ie,     if
#define hw_flash0_irq			_irq, 25, flash0,    ie,     if



/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#define hw_class__shared
#define hw_shared			_shared, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_shared_did1			_r8, 0x7F, 0x03, 0x00	/* DID for AIN0/AIN1 */
#define hw_shared_did0			_r8, 0x7E, 0x3F, 0x00	/* DID for PORTC */
#define hw_shared_eicr			_r8, 0x69, 0x0F, 0x00
#define hw_shared_pcicr			_r8, 0x68, 0x07, 0x00
#define hw_shared_prr			_r8, 0x64, 0xEF, 0x00
#define hw_shared_gpior2		_r8, 0x4B, 0xFF, 0x00
#define hw_shared_gpior1		_r8, 0x4A, 0xFF, 0x00
#define hw_shared_gtccr			_r8, 0x43, 0x83, 0x00
#define hw_shared_gpior0		_r8, 0x3E, 0xFF, 0x00
#define hw_shared_eimsk			_r8, 0x3D, 0x03, 0x00
#define hw_shared_eifr			_r8, 0x3C, 0x03, 0x03
#define hw_shared_pcifr			_r8, 0x3B, 0x07, 0x07

#if !defined __ASSEMBLER__
/*
 *  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	eimsk ;
  hwa_r8_t	eicr ;
  hwa_r8_t	eifr ;
  hwa_r8_t	gtccr ;
  hwa_r8_t	prr ;
  hwa_r8_t	did1 ;
  hwa_r8_t	did0 ;
  hwa_r8_t	pcicr ;
  hwa_r8_t	pcifr ;
} hwa_shared_t ;
#endif


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/

/*	Objects				class, address
 */
#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"

#define hw_portb			_gpa, 0x23
#define hw_portc			_gpa, 0x26
#define hw_portd			_gpa, 0x29

/*  Not-connected pins
 */
#if !defined HW_NC_PB0
#  define HW_NC_PB0			0
#endif

#if !defined HW_NC_PB6
#  define HW_NC_PB6			0
#endif

#if !defined HW_NC_PB7
#  define HW_NC_PB7			0
#endif

#if !defined HW_NC_PC6
#  define HW_NC_PC6			0
#endif

#define HW_PORTB_NCMSK			HW_NC_PB7*0x80 + HW_NC_PB6*0x40 + HW_NC_PB0

#if HW_PORTB_NCMSK
#  define _hw_portb_ncmsk		, HW_PORTB_NCMSK
#endif

#define HW_PORTC_NCMSK			HW_NC_PC6*0x40

#if HW_PORTC_NCMSK
#  define _hw_portc_ncmsk		, HW_PORTC_NCMSK
#endif

/*  Digital input disable bits for analog input pins
 */
#define hw_portc_1_0_did		_xb1, shared, did0, 1, 0	/* ADC0 */
#define hw_portc_1_1_did		_xb1, shared, did0, 1, 1	/* ADC1 */
#define hw_portc_1_2_did		_xb1, shared, did0, 1, 2	/* ADC2 */
#define hw_portc_1_3_did		_xb1, shared, did0, 1, 3	/* ADC3 */
#define hw_portc_1_4_did		_xb1, shared, did0, 1, 4	/* ADC4 */
#define hw_portc_1_5_did		_xb1, shared, did0, 1, 5	/* ADC5 */

#define hw_portd_1_6_did		_xb1, shared, did1, 1, 0	/* AIN0 */
#define hw_portd_1_7_did		_xb1, shared, did1, 1, 1	/* AIN1 */

/* /\*  TODO: handle these special pins differently. */
/*  *\/ */
/* #define hw_pc6a				_ioa, portc, 1, 8 */
/* #define hw_pc7a				_ioa, portc, 1, 9 */

/*  Relatives
 */
#define hw_portb_pcic			pcic0
#define hw_portc_pcic			pcic1
#define hw_portd_pcic			pcic2

/*  Canonical pin names
 */
#define hw_pin_sck			_ioa, portb, 1, 5
#define hw_pin_miso			_ioa, portb, 1, 4
#define hw_pin_mosi			_ioa, portb, 1, 3
#define hw_pin_ss			_ioa, portb, 1, 2

#define hw_pin_adc0			_ioa, portc, 1, 0
#define hw_pin_adc1			_ioa, portc, 1, 1
#define hw_pin_adc2			_ioa, portc, 1, 2
#define hw_pin_adc3			_ioa, portc, 1, 3
#define hw_pin_adc4			_ioa, portc, 1, 4
#define hw_pin_adc5			_ioa, portc, 1, 5
#define hw_pin_adc6			_ioa, portc, 1, 6 /* a */
#define hw_pin_adc7			_ioa, portc, 1, 7 /* a */

#define hw_pin_ain1			_ioa, portd, 1, 7
#define hw_pin_ain0			_ioa, portd, 1, 6

#define hw_pin_scl			_ioa, portc, 1, 5
#define hw_pin_sda			_ioa, portc, 1, 4

#define hw_pin_txd			_ioa, portd, 1, 1
#define hw_pin_rxd			_ioa, portd, 1, 0

#if defined HW_DEVICE_PACKAGE_28P
#
#  define hw_pin_1			_ioa, portc, 1, 6
#  define hw_pin_2			_ioa, portd, 1, 0
#  define hw_pin_3			_ioa, portd, 1, 1
#  define hw_pin_4			_ioa, portd, 1, 2
#  define hw_pin_5			_ioa, portd, 1, 3
#  define hw_pin_6			_ioa, portd, 1, 4
#  define hw_pin_9			_ioa, portb, 1, 6
#  define hw_pin_10			_ioa, portb, 1, 7
#  define hw_pin_11			_ioa, portd, 1, 5
#  define hw_pin_12			_ioa, portd, 1, 6
#  define hw_pin_13			_ioa, portd, 1, 7
#  define hw_pin_14			_ioa, portb, 1, 0
#  define hw_pin_15			_ioa, portb, 1, 1
#  define hw_pin_16			_ioa, portb, 1, 2
#  define hw_pin_17			_ioa, portb, 1, 3
#  define hw_pin_18			_ioa, portb, 1, 4
#  define hw_pin_19			_ioa, portb, 1, 5
#  define hw_pin_23			_ioa, portc, 1, 0
#  define hw_pin_24			_ioa, portc, 1, 1
#  define hw_pin_25			_ioa, portc, 1, 2
#  define hw_pin_26			_ioa, portc, 1, 3
#  define hw_pin_27			_ioa, portc, 1, 4
#  define hw_pin_28			_ioa, portc, 1, 5
#
#elif defined HW_DEVICE_PACKAGE_28Q
#
#  define hw_pin_1			_ioa, portd, 1, 3
#  define hw_pin_2			_ioa, portd, 1, 4
/* #  define _hw_pin_3			, pin_ */
/* #  define _hw_pin_4			, pin_ */
#  define hw_pin_5			_ioa, portb, 1, 6
#  define hw_pin_6			_ioa, portb, 1, 7
#  define hw_pin_7			_ioa, portd, 1, 5
#  define hw_pin_8			_ioa, portd, 1, 6
#  define hw_pin_9			_ioa, portd, 1, 7
#  define hw_pin_10			_ioa, portb, 1, 0
#  define hw_pin_11			_ioa, portb, 1, 1
#  define hw_pin_12			_ioa, portb, 1, 2
#  define hw_pin_13			_ioa, portb, 1, 3
#  define hw_pin_14			_ioa, portb, 1, 4
#  define hw_pin_15			_ioa, portb, 1, 5
/* #  define _hw_pin_16			, pin_ */
/* #  define _hw_pin_17			, pin_ */
/* #  define _hw_pin_18			, pin_ */
#  define hw_pin_19			_ioa, portc, 1, 0
#  define hw_pin_20			_ioa, portc, 1, 1
#  define hw_pin_21			_ioa, portc, 1, 2
#  define hw_pin_22			_ioa, portc, 1, 3
#  define hw_pin_23			_ioa, portc, 1, 4
#  define hw_pin_24			_ioa, portc, 1, 5
#  define hw_pin_25			_ioa, portc, 1, 6
#  define hw_pin_26			_ioa, portd, 1, 0
#  define hw_pin_27			_ioa, portd, 1, 1
#  define hw_pin_28			_ioa, portd, 1, 2
#
#elif defined HW_DEVICE_PACKAGE_32Q
#
#  define hw_pin_1			_ioa, portd, 1, 3
#  define hw_pin_2			_ioa, portd, 1, 4
#  define hw_pin_7			_ioa, portb, 1, 6
#  define hw_pin_8			_ioa, portb, 1, 7
#  define hw_pin_9			_ioa, portd, 1, 5
#  define hw_pin_10			_ioa, portd, 1, 6
#  define hw_pin_11			_ioa, portd, 1, 7
#  define hw_pin_12			_ioa, portb, 1, 0
#  define hw_pin_13			_ioa, portb, 1, 1
#  define hw_pin_14			_ioa, portb, 1, 2
#  define hw_pin_15			_ioa, portb, 1, 3
#  define hw_pin_16			_ioa, portb, 1, 4
#  define hw_pin_17			_ioa, portb, 1, 5
/* #  define _hw_pin_19			_ioa, portc, 1, 6a */
/* #  define _hw_pin_22			_ioa, portc, 1, 7a */
#  define hw_pin_23			_ioa, portc, 1, 0
#  define hw_pin_24			_ioa, portc, 1, 1
#  define hw_pin_25			_ioa, portc, 1, 2
#  define hw_pin_26			_ioa, portc, 1, 3
#  define hw_pin_27			_ioa, portc, 1, 4
#  define hw_pin_28			_ioa, portc, 1, 5
#  define hw_pin_29			_ioa, portc, 1, 6
#  define hw_pin_30			_ioa, portd, 1, 0
#  define hw_pin_31			_ioa, portd, 1, 1
#  define hw_pin_32			_ioa, portd, 1, 2
#
#endif


/*  Special pins
 *    These definitions make the (pin,...) notation work and give
 *    them an address.
 */
#define hw_pin_aref			_pin, 0x1001
#define hw_pin_avcc			_pin, 0x1002


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/coreb_1.h"
#define hw_core0			_coreb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_core0_osccal			_r8, 0x66, 0xFF, 0x00
#define hw_core0_sreg			_r8, 0x5F, 0xFF, 0x00
#define hw_core0_sph			_r8, 0x5E, 0x03, 0x00
#define hw_core0_spl			_r8, 0x5D, 0xFF, 0x00
#define hw_core0_mcucr			_r8, 0x55, 0x73, 0x00
#define hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define hw_core0_smcr			_r8, 0x53, 0x0F, 0x00

/*	Object logical registers
 */
#define hw_core0_bods			_ob1, mcucr, 1, 6
#define hw_core0_bodse			_ob1, mcucr, 1, 5
#define hw_core0_pud			_ob1, mcucr, 1, 4
#define hw_core0_ivsel			_ob1, mcucr, 1, 1
#define hw_core0_ivce			_ob1, mcucr, 1, 0

#define hw_core0_wdrf			_ob1, mcusr, 1, 3
#define hw_core0_borf			_ob1, mcusr, 1, 2
#define hw_core0_extrf			_ob1, mcusr, 1, 1
#define hw_core0_porf			_ob1, mcusr, 1, 0
#define hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */

#define hw_core0_sm			_ob1, smcr, 3, 1
#define hw_core0_se			_ob1, smcr, 1, 0


/*******************************************************************************
 *									       *
 *	External interrupt controllers					       *
 *									       *
 *******************************************************************************/

#include "../classes/inta_1.h"

/*	Object				class, address
 */
#define hw_int0				_inta, 0

/*	Object logical registers
 */
#define hw_int0_sc			_xb1, shared, eicr,  2, 0
#define hw_int0_ie			_xb1, shared, eimsk, 1, 0
#define hw_int0_if			_xb1, shared, eifr,  1, 0

/*	Object				class, address
 */
#define hw_int1				_inta, 0

/*	Object logical registers
 */
#define hw_int1_sc			_xb1, shared, eicr,  2, 2
#define hw_int1_ie			_xb1, shared, eimsk, 1, 1
#define hw_int1_if			_xb1, shared, eifr,  1, 1


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

#include "../classes/pxa_1.h"

/*	Object				class, address
 */
#define hw_pcic0			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic0_msk			_r8, 0x6B, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_pcic0_ie			_xb1, shared, pcicr, 1, 0
#define hw_pcic0_if			_xb1, shared, pcifr, 1, 0

/*	Object				class, address
 */
#define hw_pcic1			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic1_msk			_r8, 0x6C, 0x7F, 0x00

/*	Object logical registers
 */
#define hw_pcic1_ie			_xb1, shared, pcicr, 1, 1
#define hw_pcic1_if			_xb1, shared, pcifr, 1, 1

/*	Object				class, address
 */
#define hw_pcic2			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic2_msk			_r8, 0x6D, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_pcic2_ie			_xb1, shared, pcicr, 1, 2
#define hw_pcic2_if			_xb1, shared, pcifr, 1, 2


/*******************************************************************************
 *									       *
 *	hw_watchdog0: watchdog						       *
 *									       *
 *******************************************************************************/

#include "../classes/wdb_1.h"

/*	Object				class, address
 */
#define hw_watchdog0			_wdb, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__wdb_csr			_r8, 0x60, 0xFF, 0x80

/*	Class logical registers
 */
#define hw__wdb_wdrf			_xb1, core0, mcusr, 1, 3


/*******************************************************************************
 *									       *
 *	Counter 0/1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psa_1.h"

/*	Object				class, address
 */
#define hw_prescaler0			_psa, 0

/*	Object logical registers
 */
#define hw_prescaler0_tsm		_xb1, shared, gtccr, 1, 7
#define hw_prescaler0_psr		_xb1, shared, gtccr, 1, 0

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define hw_prescaler0_tsmpsr		_xb2, shared, gtccr, 1, 7, 1, gtccr, 1, 0, 0


/*******************************************************************************
 *									       *
 *	Counter 0							       *
 *									       *
 *******************************************************************************/

#include "../classes/oca_1.h"
#include "../classes/cta_1.h"

/*	Object				class, address
 */
#define hw_counter0			_cta, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter0_imsk		_r8, 0x6E, 0x07, 0x00
#define hw_counter0_ocr1		_r8, 0x48, 0xFF, 0x00	/* OCR0B */
#define hw_counter0_ocr0		_r8, 0x47, 0xFF, 0x00	/* OCR0A */
#define hw_counter0_ccra		_r8, 0x44, 0xF3, 0x00
#define hw_counter0_ccrb		_r8, 0x45, 0xCF, 0x00
#define hw_counter0_count		_r8, 0x46, 0xFF, 0x00
#define hw_counter0_ifr			_r8, 0x35, 0x07, 0x07

/*	Logical registers
 */
#define hw_counter0_com0		_ob1, ccra, 2, 6
#define hw_counter0_com1		_ob1, ccra, 2, 4
#define hw_counter0_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_counter0_foc0		_ob1, ccrb, 1, 7
#define hw_counter0_foc1		_ob1, ccrb, 1, 6
#define hw_counter0_cs			_ob1, ccrb, 3, 0

#define hw_counter0_ocie1		_ob1, imsk, 1, 2
#define hw_counter0_ocie0		_ob1, imsk, 1, 1
#define hw_counter0_ie			_ob1, imsk, 1, 0

#define hw_counter0_ocif1		_ob1, ifr,  1, 2
#define hw_counter0_ocif0		_ob1, ifr,  1, 1
#define hw_counter0_if			_ob1, ifr,  1, 0

#define hw_counter0_prr			_xb1, shared, prr, 1, 5

/*	Relatives
 */
#define hw_counter0_prescaler0		prescaler0
#define hw_counter0_prescaler		prescaler0

#define hw_counter0_compare0		_oca, counter0, 0
#define hw_counter0_compare0_pin	_ioa, portd, 1, 6
#define hw_counter0_compare0_counter	counter0

#define hw_counter0_compare1		_oca, counter0, 1
#define hw_counter0_compare1_pin	_ioa, portd, 1, 5
#define hw_counter0_compare1_counter	counter0


/*******************************************************************************
 *									       *
 *	Counter 1							       *
 *									       *
 *******************************************************************************/

#include "../classes/occ_1.h"
#include "../classes/ica_1.h"
#include "../classes/ctd_1.h"

/*	Object				class, address
 */
#define hw_counter1			_ctd, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter1_ocr1		_r16, 0x8A, 0xFFFF, 0x0000	/* OCR1B */
#define hw_counter1_ocr0		_r16, 0x88, 0xFFFF, 0x0000	/* OCR1A */
#define hw_counter1_icr0		_r16, 0x86, 0xFFFF, 0x0000	/* ICR1 */
#define hw_counter1_count		_r16, 0x84, 0xFFFF, 0x0000
#define hw_counter1_ccrc		_r8,  0x82, 0xC0,   0x00
#define hw_counter1_ccrb		_r8,  0x81, 0xDF,   0x00
#define hw_counter1_ccra		_r8,  0x80, 0xF3,   0x00
#define hw_counter1_imsk		_r8,  0x6F, 0x27,   0x00
#define hw_counter1_ifr			_r8,  0x36, 0x27,   0x27

/*	Logical registers
 */
#define hw_counter1_foc0		_ob1, ccrc, 1, 7
#define hw_counter1_foc1		_ob1, ccrc, 1, 6

#define hw_counter1_icnc		_ob1, ccrb, 1, 7
#define hw_counter1_ices		_ob1, ccrb, 1, 6
#define hw_counter1_cs			_ob1, ccrb, 3, 0
#define hw_counter1_wgm			_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0

#define hw_counter1_com0		_ob1, ccra, 2, 6
#define hw_counter1_com1		_ob1, ccra, 2, 4

#define hw_counter1_icie0		_ob1, imsk, 1, 5
#define hw_counter1_ocie1		_ob1, imsk, 1, 2
#define hw_counter1_ocie0		_ob1, imsk, 1, 1
#define hw_counter1_ie			_ob1, imsk, 1, 0

#define hw_counter1_icif0		_ob1, ifr,  1, 5
#define hw_counter1_ocif1		_ob1, ifr,  1, 2
#define hw_counter1_ocif0		_ob1, ifr,  1, 1
#define hw_counter1_if			_ob1, ifr,  1, 0

#define hw_counter1_prr			_xb1, shared, prr, 1, 3

#define hw_counter1_acic		_xb1, acmp0,  csr, 1, 2

/*	Relatives
 */
#define hw_counter1_prescaler0		prescaler0
#define hw_counter1_prescaler		prescaler0

#define hw_counter1_compare0		_occ, counter1, 0
#define hw_counter1_compare0_pin	_ioa, portb, 1, 1
#define hw_counter1_compare0_counter	counter1

#define hw_counter1_compare1		_occ, counter1, 1
#define hw_counter1_compare1_pin	_ioa, portb, 1, 2
#define hw_counter1_compare1_counter	counter1

#define hw_counter1_capture0		_ica, counter1, 0
#define hw_counter1_capture0_pin	_ioa, portb, 1, 0
#define hw_counter1_capture0_counter	counter1


/*******************************************************************************
 *									       *
 *	prescaler2: counter2 prescaler					       *
 *									       *
 *	prescaler0 and prescaler2 share the same tsm bit		       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#define hw_prescaler2			_psa, 0

/*	Object registers		class, address, write mask, flags mask
 */
#define hw_prescaler2_tsm		_xb1, shared, gtccr, 1, 7
#define hw_prescaler2_psr		_xb1, shared, gtccr, 1, 1

/*  This is a convenient logical register definition for stopping the prescaler
 */
#define hw_prescaler2_tsmpsr		_xb2, shared, gtccr, 1, 7, 1, gtccr, 1, 1, 0


/*******************************************************************************
 *									       *
 *	Counter 2							       *
 *									       *
 *******************************************************************************/

#include "../classes/ctc_1.h"	/* was ctb */

/*	Object				class, address
 */
#define hw_counter2			_ctc, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter2_assr		_r8, 0xB6, 0x60, 0x00
#define hw_counter2_ocr1		_r8, 0xB4, 0xFF, 0x00	/* OCR2B */
#define hw_counter2_ocr0		_r8, 0xB3, 0xFF, 0x00	/* OCR2A */
#define hw_counter2_count		_r8, 0xB2, 0xFF, 0x00
#define hw_counter2_ccrb		_r8, 0xB1, 0xCF, 0x00
#define hw_counter2_ccra		_r8, 0xB0, 0xF3, 0x00
#define hw_counter2_imsk		_r8, 0x70, 0x07, 0x00
#define hw_counter2_ifr			_r8, 0x37, 0x07, 0x07

/*	Logical registers
 */
#define hw_counter2_com0		_ob1, ccra, 2, 6
#define hw_counter2_com1		_ob1, ccra, 2, 4
#define hw_counter2_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_counter2_foc0		_ob1, ccrb, 1, 7
#define hw_counter2_foc1		_ob1, ccrb, 1, 6
#define hw_counter2_cs			_ob1, ccrb, 3, 0

#define hw_counter2_ocie1		_ob1, imsk, 1, 2
#define hw_counter2_ocie0		_ob1, imsk, 1, 1
#define hw_counter2_ie			_ob1, imsk, 1, 0

#define hw_counter2_ocif1		_ob1, ifr,  1, 2
#define hw_counter2_ocif0		_ob1, ifr,  1, 1
#define hw_counter2_if			_ob1, ifr,  1, 0

#define hw_counter2_prr			_xb1, shared, prr, 1, 6

/*	Relatives
 */
#define hw_counter2_prescaler0		prescaler2
#define hw_counter2_prescaler		prescaler2

#define hw_counter2_compare0		_oca, counter2, 0
#define hw_counter2_compare0_pin	_ioa, portb, 1, 3
#define hw_counter2_compare0_counter	counter2

#define hw_counter2_compare1		_oca, counter2, 1
#define hw_counter2_compare1_pin	_ioa, portd, 1, 3
#define hw_counter2_compare1_counter	counter2


/*******************************************************************************
 *									       *
 *	Serial Peripheral Interface					       *
 *									       *
 *******************************************************************************/

#include "../classes/spia_1.h"

/*	Object				class, address
 */
#define hw_spi0				_spia, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_spi0_dr			_r8, 0x4E, 0xFF, 0x00
#define hw_spi0_sr			_r8, 0x4D, 0xFF, 0x00
#define hw_spi0_cr			_r8, 0x4C, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_spi0_ie			_ob1, cr, 1, 7
#define hw_spi0_en			_ob1, cr, 1, 6
#define hw_spi0_dord			_ob1, cr, 1, 5
#define hw_spi0_mstr			_ob1, cr, 1, 4
#define hw_spi0_cpol			_ob1, cr, 1, 3
#define hw_spi0_cpha			_ob1, cr, 1, 2
#define hw_spi0_mode			_ob1, cr, 2, 2	/* convenient */

#define hw_spi0_if			_ob1, sr, 1, 7
#define hw_spi0_wpol			_ob1, sr, 1, 6

#define hw_spi0_xpr			_ob2, sr, 1, 0, 2, cr, 2, 0, 0

/*	Relatives
 */
#define hw_spi0_mosi			_ioa, portb, 1, 3
#define hw_spi0_miso			_ioa, portb, 1, 4
#define hw_spi0_sck			_ioa, portb, 1, 5
#define hw_spi0_ss			_ioa, portb, 1, 2


/*******************************************************************************
 *									       *
 *	UART								       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Object
 */
#define hw_uart0			_uarta, 0x00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__uarta_dr			_r8,  0xC6, 0xFF,   0x00
#define hw__uarta_ubrr			_r16, 0xC4, 0x0FFF, 0x0000
#define hw__uarta_csrc			_r8,  0xC2, 0xFF,   0x00
#define hw__uarta_csrb			_r8,  0xC1, 0xFD,   0x00
#define hw__uarta_csra			_r8,  0xC0, 0x43,   0x40

/*	Class logical registers
 */
#define hw__uarta_brr			_cb1, ubrr, 12, 0

#define hw__uarta_ifrxc			_cb1, csra, 1, 7
#define hw__uarta_iftxc			_cb1, csra, 1, 6
#define hw__uarta_iftxqnf		_cb1, csra, 1, 5
#define hw__uarta_fe			_cb1, csra, 1, 4
#define hw__uarta_dor			_cb1, csra, 1, 3
#define hw__uarta_pe			_cb1, csra, 1, 2
#define hw__uarta_2x			_cb1, csra, 1, 1
#define hw__uarta_mpcm			_cb1, csra, 1, 0

#define hw__uarta_ierxc			_cb1, csrb, 1, 7
#define hw__uarta_ietxc			_cb1, csrb, 1, 6
#define hw__uarta_ietxqnf		_cb1, csrb, 1, 5
#define hw__uarta_rxen			_cb1, csrb, 1, 4
#define hw__uarta_txen			_cb1, csrb, 1, 3
#define hw__uarta_rxb8			_cb1, csrb, 1, 1
#define hw__uarta_txb8			_cb1, csrb, 1, 0

#define hw__uarta_msel			_cb1, csrc, 2, 6
#define hw__uarta_pm			_cb1, csrc, 2, 4
#define hw__uarta_sbs			_cb1, csrc, 1, 3
#define hw__uarta_cpol			_cb1, csrc, 1, 0

#define hw__uarta_csz			_cb2, csrb, 1, 2, 2, csrc, 2, 1, 0

/*	Object logical registers
 */
#define hw_uart0_prr			_xb1, shared, prr, 1, 1


/*******************************************************************************
 *									       *
 *	2-wire interface						       *
 *									       *
 *******************************************************************************/

#include "../classes/twia_1.h"

/*	Object
 */
#define hw_twi0				_twia, 0xB8

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__twia_br			_r8, 0x00, 0xFF, 0x00
#define hw__twia_cr			_r8, 0x04, 0xF5, 0x80
#define hw__twia_sr			_r8, 0x01, 0x03, 0x00
#define hw__twia_dr			_r8, 0x03, 0xFF, 0x00
#define hw__twia_ar			_r8, 0x02, 0xFF, 0x00
#define hw__twia_amr			_r8, 0x05, 0xFE, 0x00

/*	Relatives
 */
#define hw_twi0_scl			_ioa, portc, 1, 5
#define hw_twi0_sda			_ioa, portc, 1, 4


/*******************************************************************************
 *									       *
 *	acmp0: analog comparator					       *
 *									       *
 *******************************************************************************/

#include "../classes/aca_1.h"

/*	Object				class, address
 */					
#define hw_acmp0			_aca, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__aca_csr			_r8, 0x50, 0xDF, 0x10

/*	Object hardware registers
 *	  Required for _hw_counter1capture0_acic
 */
#define hw_acmp0_csr			_r8, 0x50, 0xDF, 0x10

/*	Object logical registers
 */
#define hw_acmp0_acme			_xb1, adc0, srb,   1, 6
#define hw_acmp0_aden			_xb1, adc0, sra,   1, 7
#define hw_acmp0_admux			_xb1, adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/adb_1.h"

/*	Object				class, address
 */					
#define hw_adc0				_adb, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__adb_admux			_r8,  0x7C,   0xEF,   0x00
#define hw__adb_sra			_r8,  0x7A,   0xFF,   0x10
#define hw__adb_adc			_r16, 0x78, 0x0000, 0x0000
#define hw__adb_adch			_r8,  0x79,   0x00,   0x00
#define hw__adb_adcl			_r8,  0x78,   0x00,   0x00
#define hw__adb_srb			_r8,  0x7B,   0x47,   0x00

/*	Object hardware registers	class, address, write mask, flags mask
 *
 *	These are necessary for acmp0, and analog input pin configuration
 *	that needs access to the did register of the ADC object.
 */					
#define hw_adc0_admux			_r8,  0x7C,   0xEF,   0x00
#define hw_adc0_sra			_r8,  0x7A,   0xFF,   0x10
#define hw_adc0_srb			_r8,  0x7B,   0x47,   0x00

/*	Class logical registers
 */					
#define hw__adb_refs			_cb1, admux, 2, 6
#define hw__adb_lar			_cb1, admux, 1, 5
#define hw__adb_mux			_cb1, admux, 4, 0

#define hw__adb_en			_cb1, sra, 1, 7
#define hw__adb_sc			_cb1, sra, 1, 6
#define hw__adb_ate			_cb1, sra, 1, 5
#define hw__adb_if			_cb1, sra, 1, 4
#define hw__adb_ie			_cb1, sra, 1, 3
#define hw__adb_ps			_cb1, sra, 3, 0

#define hw__adb_me			_cb1, srb, 1, 6
#define hw__adb_ts			_cb1, srb, 3, 0

/*	Object logical registers
 */
#define hw_adc0_prr			_xb1, shared, prr, 1, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

#define hw_class__eea

/*	Object				class, address
 */					
#define hw_eeprom0			_eea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__eea_arh			_r8,  0x42,   0x03, 0x00
#define hw__eea_arl			_r8,  0x41,   0xFF, 0x00
#define hw__eea_ar			_r16, 0x41, 0x03FF, 0x00
#define hw__eea_dr			_r8,  0x40,   0xFF, 0x00
#define hw__eea_cr			_r8,  0x3F,   0x3F, 0x00

/*	Class logical registers
 */					
#define hw__eea_pm			_cb1, cr, 2, 4
#define hw__eea_rie			_cb1, cr, 1, 3
#define hw__eea_mpe			_cb1, cr, 1, 2
#define hw__eea_pe			_cb1, cr, 1, 1
#define hw__eea_re			_cb1, cr, 1, 0


/*******************************************************************************
 *									       *
 *	Flash memory							       *
 *									       *
 *******************************************************************************/

#define hw_class__fla

/*	Object				class, address
 */					
#define hw_flash0			_fla, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */					
#define hw__fla_csr			_r8, 0x57, 0xBF, 0x00

/*	Class logical registers
 */					
#define hw__fla_spmie			_cb1, csr, 1, 7
#define hw__fla_rwwsb			_cb1, csr, 1, 6
#define hw__fla_sigrd			_cb1, csr, 1, 5
#define hw__fla_rwwsre			_cb1, csr, 1, 4
#define hw__fla_blbset			_cb1, csr, 1, 3
#define hw__fla_pgwrt			_cb1, csr, 1, 2
#define hw__fla_pgers			_cb1, csr, 1, 1
#define hw__fla_spmen			_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;

  hwa_coreb_t	core0 ;
  hwa_gpa_t	portb ;
  hwa_gpa_t	portc ;
  hwa_gpa_t	portd ;
  hwa_pxa_t	pcic0 ;
  hwa_pxa_t	pcic1 ;
  hwa_pxa_t	pcic2 ;
  hwa_wdb_t	watchdog0 ;

  hwa_cta_t	counter0 ;
  /* hwa_oca_t	counter0compare0 ; */
  /* hwa_oca_t	counter0compare1 ; */

  hwa_ctd_t	counter1 ;
  /* hwa_occ_t	counter1compare0 ; */
  /* hwa_occ_t	counter1compare1 ; */
  /* hwa_ica_t	counter1capture0 ; */

  hwa_ctc_t	counter2 ;
  /* hwa_oca_t	counter2compare0 ; */
  /* hwa_oca_t	counter2compare1 ; */

  hwa_spia_t	spi0 ;
  hwa_uarta_t	uart0 ;
  hwa_twia_t	twi0 ;
  hwa_aca_t	acmp0 ;
  hwa_adb_t	adc0 ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/coreb_2.h"
#include "../classes/inta_2.h"
#include "../classes/pxa_2.h"
#include "../classes/wdb_2.h"
#include "../classes/oca_2.h"
#include "../classes/cta_2.h"
#include "../classes/ctc_2.h"
#include "../classes/ica_2.h"
#include "../classes/occ_2.h"
#include "../classes/ctd_2.h"
#include "../classes/psa_2.h"
#include "../classes/spia_2.h"
#include "../classes/uarta_2.h"
#include "../classes/twia_2.h"
#include "../classes/aca_2.h"
#include "../classes/adb_2.h"
#include "../classes/eea_2.h"
#include "../classes/fla_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_r( shared, eimsk );
  _hwa_setup_r( shared, eifr	);
  _hwa_setup_r( shared, eicr	);
  _hwa_setup_r( shared, gtccr );
  _hwa_setup_r( shared, prr	);
  _hwa_setup_r( shared, did1	);
  _hwa_setup_r( shared, did0	);
  _hwa_setup_r( shared, pcicr	 );
  _hwa_setup_r( shared, pcifr	 );

  _hwa_setup_o( core0 );
  _hwa_setup_o( portb );
  _hwa_setup_o( portc );
  _hwa_setup_o( portd );
  _hwa_setup_o( pcic0 );
  _hwa_setup_o( pcic1 );
  _hwa_setup_o( pcic2 );
  _hwa_setup_o( watchdog0 );
  _hwa_setup_o( counter0 );
  _hwa_setup_o( counter1 );
  _hwa_setup_o( counter2 );

  _hwa_setup_o( spi0 );
  _hwa_setup_o( uart0 );
  _hwa_setup_o( twi0 );
  _hwa_setup_o( acmp0 );
  _hwa_setup_o( adc0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_r( shared, eimsk, 0 );
  _hwa_init_r( shared, eifr,	0 );
  _hwa_init_r( shared, eicr,	0 );
  _hwa_init_r( shared, gtccr, 0 );
  _hwa_init_r( shared, prr,	0 );
  _hwa_init_r( shared, did1,	0 );
  _hwa_init_r( shared, did0,	0 );
  _hwa_init_r( shared, pcicr, 0 );
  _hwa_init_r( shared, pcifr, 0 );

  _hwa_init_o( core0 );
  _hwa_init_o( portb );
  _hwa_init_o( portc );
  _hwa_init_o( portd );
  _hwa_init_o( pcic0 );
  _hwa_init_o( pcic1 );
  _hwa_init_o( pcic2 );
  _hwa_init_o( watchdog0 );
  _hwa_init_o( counter0 );
  _hwa_init_o( counter1 );
  _hwa_init_o( counter2 );
  _hwa_init_o( spi0 );
  _hwa_init_o( uart0 );
  _hwa_init_o( twi0 );
  _hwa_init_o( acmp0 );
  _hwa_init_o( adc0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve_o( counter0 );
  _hwa_solve_o( counter1 );
  _hwa_solve_o( counter2 );

  _hwa_commit_r( shared, eimsk );
  _hwa_commit_r( shared, eifr	 );
  _hwa_commit_r( shared, eicr	 );
  _hwa_commit_o( core0 );
  _hwa_commit_r( shared, prr	 );
  _hwa_commit_o( watchdog0 );
  _hwa_commit_o( portb );
  _hwa_commit_o( portc );
  _hwa_commit_o( portd );
  _hwa_commit_r( shared, pcifr );
  _hwa_commit_r( shared, pcicr );
  _hwa_commit_o( pcic0 );
  _hwa_commit_o( pcic1 );
  _hwa_commit_o( pcic2 );

  _hwa_commit_r( shared, gtccr );
  _hwa_commit_o( counter0 );
  _hwa_commit_o( counter1 );
  _hwa_commit_o( counter2 );

  _hwa_commit_o( spi0  );
  _hwa_commit_o( uart0 );
  _hwa_commit_o( twi0  );
  _hwa_commit_o( acmp0 );
  _hwa_commit_r( shared, did1	 );
  _hwa_commit_o( adc0 );
  _hwa_commit_r( shared, did0	 );
}

#endif /* !defined __ASSEMBLER__ */
