
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015,2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny24/44/84
 */

/**
 * @ingroup atmelavr_devices
 * @defgroup attinyx4 ATtiny24/44/84
 * @{
 *
 * Content of the device:
 *
 *  * @ref atmelavr_corea "core0":			the core
 *  * @ref atmelavr_wda "watchdog0":			watchdog (WDG)
 *  * @ref atmelavr_inta "int0":			Low level interrupt (INT0)
 *  * @ref atmelavr_gpa "porta":			general purpose I/O port A (PORTA)
 *    * @ref atmelavr_ioa "(porta,0..7)":		general purpose I/O pins (PA0..PA7)
 *    * @ref atmelavr_pxa "(porta,pcic)":		pin change interrupt controller
 *  * @ref atmelavr_gpa "portb":			general purpose I/O port B (PORTB)
 *    * @ref atmelavr_ioa "(portb,0..3)":		general purpose I/O pins (PB0..PB3)
 *    * @ref atmelavr_pxa "(portb,pcic)":		pin-change interrupt controller
 *  * @ref atmelavr_cta "counter0":			8-bit counter-timer (TCNT0)
 *    * @ref atmelavr_psa "(counter0,prescaler)":	counter0/counter1 prescaler
 *    * @ref atmelavr_oca "(counter0,compare0)":	compare unit 0 of counter0
 *      * @ref atmelavr_ioa "(counter0,compare0,pin)":	counter0 compare0 output (OC0A)
 *    * @ref atmelavr_oca "(counter0,compare1)":	compare unit 1 of counter0
 *      * @ref atmelavr_ioa "(counter0,compare1,pin)":	counter0 compare1 output (OC0B)
 *    * @ref atmelavr_ioa "(counter0,pin)":		external clock source (T0)
 *  * @ref atmelavr_ctd "counter1":			16-bit counter-timer (TCNT1)
 *    * @ref atmelavr_psa "(counter1,prescaler)":	counter0/counter1 prescaler
 *    * @ref atmelavr_occ "(counter1,compare0)":	compare unit 0 of counter1
 *      * @ref atmelavr_ioa "(counter1,compare0,pin)":	counter1 compare0 output (OC1A)
 *    * @ref atmelavr_occ "(counter1,compare1)":	compare unit 1 of counter1
 *      * @ref atmelavr_ioa "(counter1,compare1,pin)":	counter1 compare1 output (OC1B)
 *    * @ref atmelavr_ica "(counter1,capture0)":	capture unit 0 of counter1
 *      * @ref atmelavr_ioa "(counter1,capture0,pin)":	counter1 capture0 input (ICP1)
 *    * @ref atmelavr_ioa "(counter1,pin)":		external clock source (T1)
 *  * @ref atmelavr_usia "usi0":			Universal Serial Interface
 *    * @ref atmelavr_ioa "(pin,usck)":			USI clock (3 wire mode)
 *    * @ref atmelavr_ioa "(pin,di)":			USI data input (3 wire mode)
 *    * @ref atmelavr_ioa "(pin,do)":			USI data output (3 wire mode)
 *  * @ref atmelavr_aca "acmp0":			analog Comparator
 *    * @ref atmelavr_ioa "(pin,ain0)":			analog comparator positive input (AIN0)
 *    * @ref atmelavr_ioa "(pin,ain1)":			analog comparator negative input (AIN1)
 *  * @ref atmelavr_ada "adc0":				10-bit Analog to Digital Converter (ADC)
 *    * @ref atmelavr_ioa "(pin,adc0..7)":		ADC inputs
 *  * @ref atmelavr_fla "flash0":			Flash memory
 *  * @ref atmelavr_eea "eeprom0":			EEPROM memory
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
#define HW_DEVICE_ATTINYX4

/**
 *  Address of first RAM byte
 */
#define HW_DEVICE_RAM_START		0x0060

/**
 *  Address of first application byte (after IRQ vector table)
 */
#define HW_DEVICE_APP_START		0x0022

/** @} */ 
/** @} */ 


#include "../hwa_1.h"
#include "attinyx4_fuses.h"


#define hw_int0_irq			_irq,  1, int0,     ie,    if
#define hw_pcic0_irq			_irq,  2, pcic0,     ie,    if
#define hw_pcic1_irq			_irq,  3, pcic1,     ie,    if
#define hw_watchdog0_irq		_irq,  4, watchdog0, ie,    if
#define hw_counter1_irq_capture0	_irq,  5, counter1,  icie0, icif0
#define hw_counter1_capture0_irq	_irq,  5, counter1,  icie0, icif0
#define hw_counter1_irq_compare0	_irq,  6, counter1,  ocie0, ocif0
#define hw_counter1_compare0_irq	_irq,  6, counter1,  ocie0, ocif0
#define hw_counter1_irq_compare1	_irq,  7, counter1,  ocie1, ocif1
#define hw_counter1_compare1_irq	_irq,  7, counter1,  ocie1, ocif1
#define hw_counter1_irq_overflow	_irq,  8, counter1,  ie,    if
#define hw_counter1_irq			_irq,  8, counter1,  ie,    if
#define hw_counter0_irq_compare0	_irq,  9, counter0,  ocie0, ocif0
#define hw_counter0_compare0_irq	_irq,  9, counter0,  ocie0, ocif0
#define hw_counter0_irq_compare1	_irq, 10, counter0,  ocie1, ocif1
#define hw_counter0_compare1_irq	_irq, 10, counter0,  ocie1, ocif1
#define hw_counter0_irq_overflow	_irq, 11, counter0,  ie,    if
#define hw_counter0_irq			_irq, 11, counter0,  ie,    if
#define hw_acmp0_irq			_irq, 12, acmp0,     ie,    if
#define hw_adc0_irq			_irq, 13, adc0,	     ie,    if
#define hw_eeprom0_irq			_irq, 14, eeprom0,   sie,   /* no irq flag */
#define hw_eeprom0_irq_ready		_irq, 14, eeprom0,   sie,
#define hw_usi0_irq_start		_irq, 15, usi0,	     ies,   ifs
#define hw_usi0_irq_overflow		_irq, 16, usi0,	     ieov,  ifov
#define hw_usi0_irq_txc			_irq, 16, usi0,	     ieov,  ifov
#define hw_usi0_irq			_irq, 16, usi0,	     ieov,  ifov


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by other objects						       *
 *									       *
 *******************************************************************************/

#define hw_class__shared
#define hw_shared			_shared, 0

#define hw_shared_gimsk			_r8, 0x5B, 0x70, 0x00
#define hw_shared_gifr			_r8, 0x5A, 0x70, 0x70
#define hw_shared_timsk			_r8, 0x59, 0x7E, 0x00
#define hw_shared_tifr			_r8, 0x58, 0x7E, 0x7E
#define hw_shared_gtccr			_r8, 0x43, 0x81, 0x00
#define hw_shared_prr			_r8, 0x40, 0x0F, 0x00
#define hw_shared_gpior2		_r8, 0x35, 0xFF, 0x00
#define hw_shared_gpior1		_r8, 0x34, 0xFF, 0x00
#define hw_shared_gpior0		_r8, 0x33, 0xFF, 0x00
#define hw_shared_did			_r8, 0x21, 0xFF, 0x00

/*  FIXME: find a way for HW_X() to expand that correctly (without inserting the
 *  name in second position)
 */
#define hw_gpior2			_xb1, gpior2, shared, 8, 0
#define hw_gpior1			_xb1, gpior1, shared, 8, 0
#define hw_gpior0			_m11,(shared,gpior0),shared,gpior0,_r8,0 +0x33,0xFF,0x00,8,0;


#if !defined __ASSEMBLER__
/*
 *  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	gimsk ;
  hwa_r8_t	gifr ;
  hwa_r8_t	timsk ;
  hwa_r8_t	tifr ;
  hwa_r8_t	gtccr ;
  hwa_r8_t	prr ;
  hwa_r8_t	did ;
} hwa_shared_t ;
#endif


/*******************************************************************************
 *									       *
 *	Ports and pins							       *
 *									       *
 *******************************************************************************/


#include "../classes/gpa_1.h"
#include "../classes/ioa_1.h"


/*	Objects				class, address
 */

#define hw_porta			_gpa, 0x39
#define hw_portb			_gpa, 0x36

/*  Not-connected pins
 */
#if !defined HW_NC_PB0
#  define HW_NC_PB0			0
#endif

#if !defined HW_NC_PB1
#  define HW_NC_PB1			0
#endif

#if !defined HW_NC_PB2
#  define HW_NC_PB2			0
#endif

#if !defined HW_NC_PB3
#  define HW_NC_PB3			0
#endif

#define HW_PORTB_NCMSK			HW_NC_PB3*0x08 + HW_NC_PB2*0x04 + HW_NC_PB1*0x02 + HW_NC_PB0

#if HW_PORTB_NCMSK
#  define _hw_portb_ncmsk		, HW_PORTB_NCMSK
#endif

/*  Digital input disable bits for analog input pins
 */
#define hw_porta_1_0_did		_xb1, shared, did, 1, 0
#define hw_porta_1_1_did		_xb1, shared, did, 1, 1
#define hw_porta_1_2_did		_xb1, shared, did, 1, 2
#define hw_porta_1_3_did		_xb1, shared, did, 1, 3
#define hw_porta_1_4_did		_xb1, shared, did, 1, 4
#define hw_porta_1_5_did		_xb1, shared, did, 1, 5
#define hw_porta_1_6_did		_xb1, shared, did, 1, 6
#define hw_porta_1_7_did		_xb1, shared, did, 1, 7

/*  Pin-change controllers
 */
#define hw_porta_pcic			pcic0
#define hw_portb_pcic			pcic1

/*  Canonical pin names
 */
#define hw_pin_ain0			_ioa, porta, 1, 1
#define hw_pin_ain1			_ioa, porta, 1, 2

#define hw_pin_usck			_ioa, porta, 1, 4
#define hw_pin_do			_ioa, porta, 1, 5
#define hw_pin_di			_ioa, porta, 1, 6

//#define hw_pin_icp			_ioa, porta, 1, 7

#define hw_pin_adc0			_ioa, porta, 1, 0
#define hw_pin_adc1			_ioa, porta, 1, 1
#define hw_pin_adc2			_ioa, porta, 1, 2
#define hw_pin_adc3			_ioa, porta, 1, 3
#define hw_pin_adc4			_ioa, porta, 1, 4
#define hw_pin_adc5			_ioa, porta, 1, 5
#define hw_pin_adc6			_ioa, porta, 1, 6
#define hw_pin_adc7			_ioa, porta, 1, 7

#define hw_pin_int0			_ioa, portb, 1, 2

#if defined HW_DEVICE_PACKAGE_14P3
#
#  define hw_pin_2			_ioa, portb, 1, 0
#  define hw_pin_3			_ioa, portb, 1, 1
#  define hw_pin_4			_ioa, portb, 1, 3
#  define hw_pin_5			_ioa, portb, 1, 2
#  define hw_pin_6			_ioa, porta, 1, 7
#  define hw_pin_7			_ioa, porta, 1, 6
#  define hw_pin_8			_ioa, porta, 1, 5
#  define hw_pin_9			_ioa, porta, 1, 4
#  define hw_pin_10			_ioa, porta, 1, 3
#  define hw_pin_11			_ioa, porta, 1, 2
#  define hw_pin_12			_ioa, porta, 1, 1
#  define hw_pin_13			_ioa, porta, 1, 0
#
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

#include "../classes/corea_1.h"

/*	Object				class, address
 */
#define hw_core0			_corea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__corea_sreg			_r8, 0x5F, 0xFF, 0x00
#define hw__corea_sph			_r8, 0x5E, 0x03, 0x00
#define hw__corea_spl			_r8, 0x5D, 0xFF, 0x00

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_core0_mcucr			_r8, 0x55, 0xFF, 0x00
#define hw_core0_mcusr			_r8, 0x54, 0x0F, 0x00
#define hw_core0_osccal			_r8, 0x51, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_core0_bods			_ob1, mcucr, 1, 7
#define hw_core0_pud			_ob1, mcucr, 1, 6
#define hw_core0_se			_ob1, mcucr, 1, 5
#define hw_core0_sm			_ob1, mcucr, 2, 3
#define hw_core0_bodse			_ob1, mcucr, 1, 2

#define hw_core0_wdrf			_ob1, mcusr, 1, 3
#define hw_core0_borf			_ob1, mcusr, 1, 2
#define hw_core0_extrf			_ob1, mcusr, 1, 1
#define hw_core0_porf			_ob1, mcusr, 1, 0
#define hw_core0_allrf			_ob1, mcusr, 4, 0	/* convenient */


/*******************************************************************************
 *									       *
 *	External interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/inta_1.h"
#define hw_int0				_inta, 0

#define hw_int0_sc			_xb1, core0,  mcucr, 2, 0
#define hw_int0_ie			_xb1, shared, gimsk, 1, 6
#define hw_int0_if			_xb1, shared, gifr,  1, 6


/*******************************************************************************
 *									       *
 *	Pin-change interrupt controllers				       *
 *									       *
 *******************************************************************************/

#include "../classes/pxa_1.h"

/*	Object				class, address
 */
#define hw_pcic0			_pxa, 0x32

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic0_msk			_r8, 0x00, 0xFF, 0x00

/*	Object logical registers
 */
#define hw_pcic0_ie			_xb1, shared, gimsk, 1, 4
#define hw_pcic0_if			_xb1, shared, gifr,  1, 4

/*	Object				class, address
 */
#define hw_pcic1			_pxa, 0x40

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic1_msk			_r8, 0x00, 0x0F, 0x00

/*	Object logical registers
 */
#define hw_pcic1_ie			_xb1, shared, gimsk, 1, 5
#define hw_pcic1_if			_xb1, shared, gifr,  1, 5


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/wda_1.h"
#define hw_watchdog0			_wda, 0

/*	Class registers			class, address, write mask, flags mask
 */
#define hw__wda_csr			_r8, 0x41, 0xFF, 0x80

#define hw__wda_if			_cb1, csr, 1, 7
#define hw__wda_ie			_cb1, csr, 1, 6
#define hw__wda_wdp			_cb2, csr, 1, 5, 3, csr, 3, 0, 0
#define hw__wda_wdce			_cb1, csr, 1, 4
#define hw__wda_wde			_cb1, csr, 1, 3

#define hw__wda_eie			_cb2, csr, 1, 3, 1, csr, 1, 6, 0 /* convenient */
#define hw__wda_ifie			_cb1, csr, 2, 6 /* convenient for clearing irq */

#define hw__wda_wdrf			_xb1, core0, mcusr, 1, 3


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

/*	Object				class, address
 */
#include "../classes/oca_1.h"
#include "../classes/cta_1.h"

#define hw_counter0			_cta, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter0_ocr1		_r8, 0x5C, 0xFF, 0x00	/* OCR0B */
#define hw_counter0_imsk		_r8, 0x59, 0x07, 0x00
#define hw_counter0_ifr			_r8, 0x58, 0x07, 0x07
#define hw_counter0_ocr0		_r8, 0x56, 0xFF, 0x00	/* OCR0A */
#define hw_counter0_ccrb		_r8, 0x53, 0xCF, 0x00
#define hw_counter0_count		_r8, 0x52, 0xFF, 0x00
#define hw_counter0_ccra		_r8, 0x50, 0xF3, 0x00

/*	Logical registers
 */
#define hw_counter0_com0		_ob1, ccra, 2, 6
#define hw_counter0_com1		_ob1, ccra, 2, 4
#define hw_counter0_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define hw_counter0_foc1		_ob1, ccrb, 1, 6
#define hw_counter0_foc0		_ob1, ccrb, 1, 7
#define hw_counter0_cs			_ob1, ccrb, 3, 0
#define hw_counter0_ocie1		_ob1, imsk, 1, 2
#define hw_counter0_ocie0		_ob1, imsk, 1, 1
#define hw_counter0_ie			_ob1, imsk, 1, 0
#define hw_counter0_ocif1		_ob1, ifr,  1, 2
#define hw_counter0_ocif0		_ob1, ifr,  1, 1
#define hw_counter0_if			_ob1, ifr,  1, 0

/*	Relatives
 */
#define hw_counter0_prescaler0		prescaler0
#define hw_counter0_prescaler		prescaler0

#define hw_counter0_compare0		_oca, counter0, 0
#define hw_counter0_compare0_pin	_ioa, portb, 1, 2
#define hw_counter0_compare0_counter	counter0

#define hw_counter0_compare1		_oca, counter0, 1
#define hw_counter0_compare1_pin	_ioa, porta, 1, 7
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
#define hw_counter1_ccra		_r8,  0x4F,   0xF3,   0x00
#define hw_counter1_ccrb		_r8,  0x4E,   0xDF,   0x00
#define hw_counter1_ocr0		_r16, 0x4A, 0xFFFF, 0x0000	/* OCR1A */
#define hw_counter1_ocr1		_r16, 0x48, 0xFFFF, 0x0000	/* OCR1B */
#define hw_counter1_icr0		_r16, 0x44, 0xFFFF, 0x0000	/* ICR1 */
#define hw_counter1_ccrc		_r8,  0x42,   0xC0,   0x00
#define hw_counter1_count		_r16, 0x4C, 0xFFFF, 0x0000
#define hw_counter1_imsk		_r8,  0x2C,   0x27,   0x00
#define hw_counter1_ifr			_r8,  0x2B,   0x27,   0x27

/*	Logical registers
 */
#define hw_counter1_com0		_ob1, ccra, 2, 6
#define hw_counter1_com1		_ob1, ccra, 2, 4
#define hw_counter1_icnc		_ob1, ccrb, 1, 7
#define hw_counter1_ices		_ob1, ccrb, 1, 6
#define hw_counter1_cs			_ob1, ccrb, 3, 0
#define hw_counter1_wgm			_ob2, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define hw_counter1_foc0		_ob1, ccrc, 1, 7
#define hw_counter1_foc1		_ob1, ccrc, 1, 6
#define hw_counter1_icie0		_ob1, imsk, 1, 5
#define hw_counter1_ocie1		_ob1, imsk, 1, 2
#define hw_counter1_ocie0		_ob1, imsk, 1, 1
#define hw_counter1_ie			_ob1, imsk, 1, 0
#define hw_counter1_icif0		_ob1, ifr,  1, 5
#define hw_counter1_ocif1		_ob1, ifr,  1, 2
#define hw_counter1_ocif0		_ob1, ifr,  1, 1
#define hw_counter1_if			_ob1, ifr,  1, 0

#define hw_counter1_acic		_xb1, acmp0, csr, 1, 2

/*	Relatives
 */
#define hw_counter1_prescaler0		prescaler0
#define hw_counter1_prescaler		prescaler0

#define hw_counter1_compare0		_occ, counter1, 0
#define hw_counter1_compare0_pin	_ioa, porta, 1, 6
#define hw_counter1_compare0_counter	counter1

#define hw_counter1_compare1		_occ, counter1, 1
#define hw_counter1_compare1_pin	_ioa, porta, 1, 5
#define hw_counter1_compare1_counter	counter1

#define hw_counter1_capture0		_ica, counter1, 0
#define hw_counter1_capture0_pin	_ioa, porta, 1, 7
#define hw_counter1_capture0_counter	counter1


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#include "../classes/usia_1.h"
#define hw_usi0				_usia, 0x2D

/*	Class registers			class, address, write mask, flags mask
 */					
#define hw__usia_cr			_r8, 0, 0xFF, 0x00
#define hw__usia_sr			_r8, 1, 0xFF, 0xE0
#define hw__usia_dr			_r8, 2, 0xFF, 0x00
#define hw__usia_br			_r8, 3, 0xFF, 0x00

#define hw__usia_ies			_cb1, cr, 1, 7
#define hw__usia_ieov			_cb1, cr, 1, 6
#define hw__usia_wm			_cb1, cr, 2, 4
#define hw__usia_cs			_cb1, cr, 2, 2
#define hw__usia_clk			_cb1, cr, 1, 1
#define hw__usia_tc			_cb1, cr, 1, 0

#define hw__usia_ifs			_cb1, sr, 1, 7
#define hw__usia_ifov			_cb1, sr, 1, 6
#define hw__usia_pf			_cb1, sr, 1, 5
#define hw__usia_dc			_cb1, sr, 1, 4
#define hw__usia_cnt			_cb1, sr, 4, 0


/*	USI used as SPI master with software clock
 */
#define hw_spimaster_swclk0		_usia_spimaster_swclk, usi0

/*	USI used as SPI master with counter0 overflow clock
 */
#define hw_spimaster_c0clk0		_usia_spimaster_c0clk, usi0

/*	Pins
 */
#define hw_usi0_ck			_ioa, porta, 1, 4
#define hw_usi0_do			_ioa, porta, 1, 5
#define hw_usi0_di			_ioa, porta, 1, 6


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#include "../classes/aca_1.h"
#define hw_acmp0			_aca, 0

/*	Class registers			class, address, write mask, flags mask
 */					
#define hw__aca_csr			_r8, 0x28, 0xDF, 0x10

/*	Object registers		class, address, write mask, flags mask
 *
*	Required for _hw_counter1_acic
 */
#define hw_acmp0_csr			_r8, 0x28, 0xDF, 0x10

#define hw_acmp0_acme			_xb1, adc0, srb,   1, 6
#define hw_acmp0_aden			_xb1, adc0, sra,   1, 7
#define hw_acmp0_admux			_xb1, adc0, admux, 6, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

#include "../classes/ada_1.h"
#define hw_adc0				_ada, 0

#define hw__ada_admux			_r8,  0x27,   0xFF,   0x00
#define hw__ada_sra			_r8,  0x26,   0xFF,   0x10
#define hw__ada_adc			_r16, 0x24, 0x0000, 0x0000
#define hw__ada_adch			_r8,  0x25,   0x00,   0x00
#define hw__ada_adcl			_r8,  0x24,   0x00,   0x00
#define hw__ada_srb			_r8,  0x23,   0xD7,   0x00

#define hw_adc0_admux			_r8,  0x27,   0xFF,   0x00
#define hw_adc0_sra			_r8,  0x26,   0xFF,   0x10
#define hw_adc0_srb			_r8,  0x23,   0xD7,   0x00

#define hw__ada_refs			_cb1, admux, 2, 6
#define hw__ada_mux			_cb1, admux, 6, 0

#define hw__ada_en			_cb1, sra, 1, 7
#define hw__ada_sc			_cb1, sra, 1, 6
#define hw__ada_ate			_cb1, sra, 1, 5
#define hw__ada_if			_cb1, sra, 1, 4
#define hw__ada_ie			_cb1, sra, 1, 3
#define hw__ada_ps			_cb1, sra, 3, 0

#define hw__ada_bin			_cb1, srb, 1, 7
#define hw__ada_lar			_cb1, srb, 1, 4
#define hw__ada_ts			_cb1, srb, 3, 0


/*******************************************************************************
 *									       *
 *	EEPROM memory							       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#define hw_class__eea

/*	Object				class, address
 */
#define hw_eeprom0			_eea, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define hw__eea_arh			_r8,  0x3F,   0x01, 0x00
#define hw__eea_arl			_r8,  0x3E,   0xFF, 0x00
#define hw__eea_ar			_r16, 0x3E, 0x01FF, 0x00
#define hw__eea_dr			_r8,  0x3D,   0xFF, 0x00
#define hw__eea_cr			_r8,  0x3C,   0x3F, 0x00

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

/*	Class
 */
#define hw_class__fla

/*	Object				class, address
 */
#define hw_flash0			_fla, 0

/*	Class regs			class, address, write mask, flags mask
 */
#define hw__fla_csr			_r8,  0x57, 0x3F, 0x00

#define hw__fla_sigrd			_cb1, csr, 1, 5
#define hw__fla_rsig			_cb1, csr, 1, 5	/* old definition */
#define hw__fla_rwwsre			_cb1, csr, 1, 4
#define hw__fla_ctpb			_cb1, csr, 1, 4	/* old definition */
#define hw__fla_blbset			_cb1, csr, 1, 3
#define hw__fla_rflb			_cb1, csr, 1, 3	/* old definition */
#define hw__fla_pgwrt			_cb1, csr, 1, 2
#define hw__fla_pgers			_cb1, csr, 1, 1
#define hw__fla_spmen			_cb1, csr, 1, 0


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;

  hwa_corea_t	core0 ;
  hwa_gpa_t	porta ;
  hwa_gpa_t	portb ;
  hwa_pxa_t	pcic0 ;
  hwa_pxa_t	pcic1 ;
  hwa_wda_t	watchdog0 ;
  hwa_cta_t	counter0 ;
  hwa_ctd_t	counter1 ;
  hwa_usia_t	usi0 ;
  hwa_aca_t	acmp0 ;
  hwa_ada_t	adc0 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/corea_2.h"
#include "../classes/inta_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/pxa_2.h"
#include "../classes/wda_2.h"
#include "../classes/psa_2.h"
#include "../classes/oca_2.h"
#include "../classes/cta_2.h"
#include "../classes/occ_2.h"
#include "../classes/ica_2.h"
#include "../classes/ctd_2.h"
#include "../classes/usia_2.h"
#include "../classes/aca_2.h"
#include "../classes/ada_2.h"
#include "../classes/eea_2.h"
#include "../classes/fla_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_r( shared, gimsk );
  _hwa_setup_r( shared, gifr	);
  _hwa_setup_r( shared, prr	);
  _hwa_setup_r( shared, gtccr );
  _hwa_setup_r( shared, timsk );
  _hwa_setup_r( shared, tifr	);
  _hwa_setup_r( shared, did	);

  _hwa_setup_o( core0 );
  _hwa_setup_o( porta );
  _hwa_setup_o( portb );
  _hwa_setup_o( pcic0 );
  _hwa_setup_o( pcic1 );
  _hwa_setup_o( watchdog0 );
  _hwa_setup_o( counter0 );
  _hwa_setup_o( counter1 );
  _hwa_setup_o( usi0 );
  _hwa_setup_o( adc0 );
  _hwa_setup_o( acmp0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_r( shared, gimsk, 0 );
  _hwa_init_r( shared, gifr,	0 );
  _hwa_init_r( shared, prr,	0 );
  _hwa_init_r( shared, gtccr, 0 );
  _hwa_init_r( shared, timsk, 0 );
  _hwa_init_r( shared, tifr,	0 );
  _hwa_init_r( shared, did,	0 );

  _hwa_init_o( core0 );
  _hwa_init_o( porta );
  _hwa_init_o( portb );
  _hwa_init_o( pcic0 );
  _hwa_init_o( pcic1 );
  _hwa_init_o( watchdog0 );
  _hwa_init_o( counter0 );
  _hwa_init_o( counter1 );
  _hwa_init_o( usi0 );
  _hwa_init_o( adc0 );
  _hwa_init_o( acmp0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  /*  Solve the configuration of the counters
   *
   *  The configuration values are written here since the solve function only
   *  has the address of the counter and does not know its name.
   */
  _hwa_solve_o( counter0 );
  _hwa_solve_o( counter1 );

  _hwa_commit_r( shared, gimsk );
  _hwa_commit_r( shared, gifr	 );
  _hwa_commit_o( core0 );
  _hwa_commit_r( shared, prr	 );

  _hwa_commit_o( watchdog0 );
  _hwa_commit_o( porta );
  _hwa_commit_o( portb );

  _hwa_commit_o( pcic0 );
  _hwa_commit_o( pcic1 );

  _hwa_commit_r( shared, gtccr );
  _hwa_commit_o( counter0 );
  _hwa_commit_o( counter1 );

  _hwa_commit_o( usi0 );
  _hwa_commit_o( adc0 );
  _hwa_commit_r( shared, did );
  _hwa_commit_o( acmp0 );
}

#endif /* !defined __ASSEMBLER__ */
