
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATtiny25/45/85
 */

/**
 * @ingroup atmelavr_devices
 * @defgroup attinyx5 ATtiny25/45/85
 * @{
 *
 * Content of the device:
 *
 *  * @ref atmelavr_corea "core0":			the core
 *  * @ref atmelavr_wda "watchdog0":			watchdog (WDG)
 *  * @ref atmelavr_inta "int0":			Low level interrupt (INT0)
 *  * @ref atmelavr_gpa "portb":			general purpose I/O port B (PORTB)
 *    * @ref atmelavr_ioa "(portb,0..5)":		general purpose I/O pins (PB0..PB5)
 *    * @ref atmelavr_pxa "(portb,pcic)":		pin change interrupt controller
 *  * @ref atmelavr_psa "prescaler0":			counter 0 prescaler
 *  * @ref atmelavr_cta "counter0":			8-bit counter-timer (T0)
 *    * @ref atmelavr_oca "(counter0,compare0)":	compare unit 0 of counter0 (OC0A)
 *    * @ref atmelavr_oca "(counter0,compare1)":	compare unit 1 of counter0 (OC0B)
 *  * @ref atmelavr_ctb "counter1":			8-bit counter-timer (T1)
 *    * @ref atmelavr_psb "(counter1,prescaler)":	counter 1 prescaler
 *    * @ref atmelavr_ocb "(counter1,compare0)":	compare unit 0 of counter1 (OC1A)
 *      * @ref atmelavr_ioa "(counter1,compare0,pin[_h])": high-side ouput pin (OC1A)
 *      * @ref atmelavr_ioa "(counter1,compare0,pin_l)": low-side ouput pin (/OC1A)
 *    * @ref atmelavr_ocb "(counter1,compare1)":	compare unit 1 of counter1 (OC1B)
 *      * @ref atmelavr_ioa "(counter1,compare1,pin[_h])": high-side ouput pin (OC1B)
 *      * @ref atmelavr_ioa "(counter1,compare1,pin_l)": low-side ouput pin (/OC1B)
 *    * @ref hwa_r8 "(counter1,compare2)":		compare unit 1 of counter1 (OC1C)
 *    * @ref atmelavr_dtga "(counter1,dtg)":		dead time generator for counter1 compare outputs
 *  * @ref atmelavr_usia "usi0":			Universal Serial Interface
 *  * @ref atmelavr_acb "acmp0":			analog Comparator (ACMP0)
 *  * @ref atmelavr_adc "adc0":				10-bit Analog to Digital Converter (ADC)
 *  * @ref atmelavr_fla "flash0":			flash memory
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
#define HW_DEVICE_ATTINYX5

/**
 *  Address of first RAM byte
 */
#define HW_DEVICE_RAM_START		0x0060

/**
 *  Address of first application byte (after IRQ vector table)
 */
#define HW_DEVICE_APP_START		0x001E

/** @} */ 
/** @} */ 

#include "../hwa_1.h"
#include "attinyx5_fuses.h"


#define hw_int0_irq			_irq,  1, core0,     ie,    if
#define hw_pcic0_irq			_irq,  2, pcic0,     ie,    if
#define hw_counter1_compare0_irq	_irq,  3, counter1,  ocie0, ocif0
#define hw_counter1_irq			_irq,  4, counter1,  ie,    if
#define hw_counter1_irq_overflow	_irq,  4, counter1,  ie,    if
#define hw_counter0_irq			_irq,  5, counter0,  ie,    if
#define hw_counter0_irq_overflow	_irq,  5, counter0,  ie,    if
#define hw_eeprom0_irq			_irq,  6, eeprom0,   ie, /* no irq flag */
#define hw_eeprom0_irq_ready		_irq,  6, eeprom0,   ie,
#define hw_acmp0_irq			_irq,  7, acmp0,     ie,    if
#define hw_adc0_irq			_irq,  8, adc0,	     ie,    if
#define hw_counter1_compare1_irq	_irq,  9, counter1,  ocie1, ocif1
#define hw_counter0_compare0_irq	_irq, 10, counter0,  ocie0, ocif0
#define hw_counter0_compare1_irq	_irq, 11, counter0,  ocie1, ocif1
#define hw_watchdog0_irq		_irq, 12, watchdog0, ie,    if
#define hw_usi0_irq			_irq, , , ,
#define hw_usi0_irq_start		_irq, 13, usi0,	     ies,   ifs
#define hw_usi0_irq_overflow		_irq, 14, usi0,	     ieov,  ifov
#define hw_usi0_irq_txc			_irq, 14, usi0,	     ieov,  ifov


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
 *	by other objects						       *
 *									       *
 *******************************************************************************/

#define hw_class__shared

/*	Object				class, address
 */
#define hw_shared			_shared, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_shared_gimsk			_r8, 0x5B, 0x60, 0x00
#define hw_shared_gifr			_r8, 0x5A, 0x60, 0x60
#define hw_shared_timsk			_r8, 0x59, 0x7E, 0x00
#define hw_shared_tifr			_r8, 0x58, 0x7E, 0x7E
#define hw_shared_gtccr			_r8, 0x4C, 0xFF, 0x00
#define hw_shared_prr			_r8, 0x40, 0x0F, 0x00
#define hw_shared_gpior2		_r8, 0x33, 0xFF, 0x00
#define hw_shared_gpior1		_r8, 0x32, 0xFF, 0x00
#define hw_shared_gpior0		_r8, 0x31, 0xFF, 0x00
#define hw_shared_did			_r8, 0x34, 0x3F, 0x00


#if !defined __ASSEMBLER__

/*  HWA context
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

/*	Object				class, address
 */
#define hw_portb			_gpa, 0x36

/*  Not-connected pins
 */
#if !defined HW_NC_PB3
#  define HW_NC_PB3			0
#endif

#if !defined HW_NC_PB4
#  define HW_NC_PB4			0
#endif

#if !defined HW_NC_PB5
#  define HW_NC_PB5			0
#endif

#define HW_PORTB_NCMSK			0xC0 + HW_NC_PB5*0x20 + HW_NC_PB4*0x10 + HW_NC_PB3*0x08

#define _hw_portb_ncmsk			, HW_PORTB_NCMSK

/*  Digital input disable bits for analog input pins
 */
#define hw_portb_1_5_did		_xb1, shared, did, 1, 5	/* ADC0 PB5 */
#define hw_portb_1_4_did		_xb1, shared, did, 1, 4	/* ADC2 PB4 */
#define hw_portb_1_3_did		_xb1, shared, did, 1, 3	/* ADC3 PB3 */
#define hw_portb_1_2_did		_xb1, shared, did, 1, 2	/* ADC1 PB2 */
#define hw_portb_1_1_did		_xb1, shared, did, 1, 1	/* AIN1 PB1 */
#define hw_portb_1_0_did		_xb1, shared, did, 1, 0	/* AIN0 PB0 */

/*  Relatives
 */
#define hw_portb_pcic			pcic0

/*  (pin,...) notation
 */
#define hw_pin_usck			_ioa, portb, 1, 2
#define hw_pin_do			_ioa, portb, 1, 1
#define hw_pin_di			_ioa, portb, 1, 0

#if defined HW_DEVICE_PACKAGE_8P3
#  define hw_pin_1			_ioa, portb, 1, 5
#  define hw_pin_2			_ioa, portb, 1, 3
#  define hw_pin_3			_ioa, portb, 1, 4
#  define hw_pin_5			_ioa, portb, 1, 0
#  define hw_pin_6			_ioa, portb, 1, 1
#  define hw_pin_7			_ioa, portb, 1, 2
#endif


/*******************************************************************************
 *									       *
 *	Core								       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/corea_1.h"
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
#define hw_core0_isc0			_ob1, mcucr, 2, 0

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
 *	Pin-change interrupt controller					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/pxa_1.h"
#define hw_pcic0			_pxa, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_pcic0_msk			_r8, 0x35, 0x3F, 0x00

/*	Object logical registers
 */
#define hw_pcic0_ie			_xb1, shared, gimsk, 1, 5
#define hw_pcic0_if			_xb1, shared, gifr,  1, 5


/*******************************************************************************
 *									       *
 *	Watchdog							       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/wda_1.h"
#define hw_watchdog0			_wda, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__wda_csr			_r8, 0x41, 0xFF, 0x80

/*	Class logical registers
 */
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
 *	Counter 0							       *
 *									       *
 *******************************************************************************/

#include "../classes/oca_1.h"
#include "../classes/cta_1.h"

/*	Object				class, address
 */
#define hw_counter0			_cta, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_counter0_ccra		_r8, 0x4A, 0xF3, 0x00
#define hw_counter0_ocr0		_r8, 0x49, 0xFF, 0x00	/* OCR0A */
#define hw_counter0_ocr1		_r8, 0x48, 0xFF, 0x00	/* OCR0B */
#define hw_counter0_ccrb		_r8, 0x53, 0xCF, 0x00
#define hw_counter0_count		_r8, 0x52, 0xFF, 0x00
#define hw_counter0_imsk		_r8, -1, 0, 0	/* For compatibility */
#define hw_counter0_ifr			_r8, -1, 0, 0

/*	Object logical registers
 */
#define hw_counter0_com0		_ob1, ccra, 2, 6
#define hw_counter0_com1		_ob1, ccra, 2, 4
#define hw_counter0_wgm			_ob2, ccra, 2, 0, 0, ccrb, 1, 3, 2
#define hw_counter0_foc0		_ob1, ccrb, 1, 7
#define hw_counter0_foc1		_ob1, ccrb, 1, 6
#define hw_counter0_cs			_ob1, ccrb, 3, 0

#define hw_counter0_ie			_xb1, shared, timsk, 1, 1
#define hw_counter0_if			_xb1, shared, tifr,  1, 1

#define hw_counter0_ocie0		_xb1, shared, timsk, 1, 4
#define hw_counter0_ocif0		_xb1, shared, tifr,  1, 4

#define hw_counter0_ocie1		_xb1, shared, imsk,  1, 3
#define hw_counter0_ocif1		_xb1, shared, ifr,   1, 3

/*	Relatives
 */
#define hw_counter0_prescaler0		prescaler0
#define hw_counter0_prescaler		prescaler0

#define hw_counter0_compare0		_oca, counter0, 0
#define hw_counter0_compare0_pin	_ioa, portb, 1, 0
#define hw_counter0_compare0_counter	counter0

#define hw_counter0_compare1		_oca, counter0, 1
#define hw_counter0_compare1_pin	_ioa, portb, 1, 1
#define hw_counter0_compare1_counter	counter0


/*******************************************************************************
 *									       *
 *	Counter 0 prescaler						       *
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
 *	Counter 1							       *
 *									       *
 *******************************************************************************/

#include "../classes/ocb_1.h"
#include "../classes/dtga_1.h"
#include "../classes/ctb_1.h"

/*	Object				class, address
 */
#define hw_counter1			_ctb, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_counter1_ccr			_r8, 0x50, 0xFF, 0x00	/* TCCR1 */
#define hw_counter1_count		_r8, 0x4F, 0xFF, 0x00	/* TCNT1 */
#define hw_counter1_ocr0		_r8, 0x4E, 0xFF, 0x00	/* OCR1A */
#define hw_counter1_ocr2		_r8, 0x4D, 0xFF, 0x00	/* OCR1C */
#define hw_counter1_ocr1		_r8, 0x4B, 0xFF, 0x00	/* OCR1B */
#define hw_counter1_dta			_r8, 0x45, 0xFF, 0x00	/* DT1A */
#define hw_counter1_dtb			_r8, 0x44, 0xFF, 0x00	/* DT1B */
#define hw_counter1_dtps		_r8, 0x43, 0x03, 0x00	/* DTPS1 */

/*	Logical registers
 */
#define hw_counter1_ctc			_ob1, ccr, 1, 7
#define hw_counter1_pwm0		_ob1, ccr, 1, 6
#define hw_counter1_com0		_ob1, ccr, 2, 4
#define hw_counter1_cs			_ob1, ccr, 4, 0

#define hw_counter1_dtgps		_ob1, dtps, 2, 0
#define hw_counter1_dtg0h		_ob1, dta,  4, 4
#define hw_counter1_dtg0l		_ob1, dta,  4, 0
#define hw_counter1_dtg1h		_ob1, dtb,  4, 4
#define hw_counter1_dtg1l		_ob1, dtb,  4, 0

#define hw_counter1_ocie0		_xb1, shared, timsk, 1, 6
#define hw_counter1_ocie1		_xb1, shared, timsk, 1, 5
#define hw_counter1_ie			_xb1, shared, timsk, 1, 2

#define hw_counter1_ocif0		_xb1, shared, tifr,  1, 6
#define hw_counter1_ocif1		_xb1, shared, tifr,  1, 5
#define hw_counter1_if			_xb1, shared, tifr,  1, 2

#define hw_counter1_pwm1		_xb1, shared, gtccr, 1, 6
#define hw_counter1_com1		_xb1, shared, gtccr, 2, 4
#define hw_counter1_foc1		_xb1, shared, gtccr, 1, 3
#define hw_counter1_foc0		_xb1, shared, gtccr, 1, 2

/*	Relatives
 */
#define hw_counter1_prescaler		prescaler1
#define hw_counter1_prescaler0		prescaler1

#define hw_counter1_compare0		_ocb, counter1, 0
#define hw_counter1_compare0_pin	_ioa, portb, 1, 1
#define hw_counter1_compare0_pin_h	_ioa, portb, 1, 1
#define hw_counter1_compare0_pin_l	_ioa, portb, 1, 0
#define hw_counter1_compare0_counter	counter1
#define hw_counter1_compare0_dtg	_dtga, counter1, 0

#define hw_counter1_compare1		_ocb, counter1, 1
#define hw_counter1_compare1_pin	_ioa, portb, 1, 4
#define hw_counter1_compare1_pin_h	_ioa, portb, 1, 4
#define hw_counter1_compare1_pin_l	_ioa, portb, 1, 3
#define hw_counter1_compare1_counter	counter1
#define hw_counter1_compare1_dtg	_dtga, counter1, 1

#define hw_counter1_compare2		_xb1, counter1, ocr2, 8, 0


/*******************************************************************************
 *									       *
 *	Counter 1 prescaler						       *
 *									       *
 *******************************************************************************/

#include "../classes/psb_1.h"

/*	Object				class, address
 */
#define hw_prescaler1			_psb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_prescaler1_pllcsr		_r8, 0x47, 0x86, 0x00	/* PLLCSR */

/*	Object logical registers
 */
#define hw_prescaler1_psr		_xb1, shared, gtccr, 1, 1

#define hw_prescaler1_lsm		_ob1, pllcsr, 1, 7
#define hw_prescaler1_pcke		_ob1, pllcsr, 1, 2
#define hw_prescaler1_plle		_ob1, pllcsr, 1, 1
#define hw_prescaler1_plock		_ob1, pllcsr, 1, 0


/*******************************************************************************
 *									       *
 *	Universal Serial Interface					       *
 *									       *
 *******************************************************************************/

#include "../classes/usia_1.h"

/*	Object				class, address
 */					
#define hw_usi0				_usia, 0

/*	Hardware registers		class, address, write mask, flags mask
 */
#define hw_usi0_dr			_r8, 0x2F, 0xFF, 0x00
#define hw_usi0_br			_r8, 0x30, 0xFF, 0x00
#define hw_usi0_sr			_r8, 0x2E, 0xFF, 0xE0
#define hw_usi0_cr			_r8, 0x2D, 0xFF, 0x00

/*	Logical registers
 */
#define hw_usi0_ies			_ob1, cr, 1, 7
#define hw_usi0_ieov			_ob1, cr, 1, 6
#define hw_usi0_iep			_ob1, cr, 1, 5
#define hw_usi0_wm			_ob1, cr, 2, 4
#define hw_usi0_cs			_ob1, cr, 2, 2
#define hw_usi0_clk			_ob1, cr, 1, 1
#define hw_usi0_tc			_ob1, cr, 1, 0

#define hw_usi0_ifs			_ob1, sr, 1, 7
#define hw_usi0_ifov			_ob1, sr, 1, 6
#define hw_usi0_ifp			_ob1, sr, 1, 5
#define hw_usi0_dc			_ob1, sr, 1, 4
#define hw_usi0_cnt			_ob1, sr, 4, 0

/*	Relatives
 */
#define hw_usi0_ck			_ioa, portb, 1, 2
#define hw_usi0_do			_ioa, portb, 1, 1
#define hw_usi0_di			_ioa, portb, 1, 0

/*	USI used as SPI master with software clock
 *	  FIXME: should create an object for that.
 */
#define hw_spimaster_swclk0		_usia_spimaster_swclk, usi0

/*	USI used as SPI master with counter0 overflow clock
 *	  FIXME: should create an object for that.
 */
#define hw_spimaster_c0clk0		_usia_spimaster_c0clk, usi0


/*******************************************************************************
 *									       *
 *	Analog Comparator						       *
 *									       *
 *******************************************************************************/

/*	Instance			class, address
 */					
#include "../classes/acb_1.h"
#define hw_acmp0			_acb, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */					
#define hw_acmp0_csr			_r8, 0x28, 0xDF, 0x10

/*	Object logical registers
 */					
#define hw_acmp0_acd			_ob1, csr, 1, 7
#define hw_acmp0_acbg			_ob1, csr, 1, 6
#define hw_acmp0_aco			_ob1, csr, 1, 5
#define hw_acmp0_if			_ob1, csr, 1, 4
#define hw_acmp0_ie			_ob1, csr, 1, 3
#define hw_acmp0_acis			_ob1, csr, 2, 0

#define hw_acmp0_acme			_xb1, adc0, srb,   1, 6
#define hw_acmp0_aden			_xb1, adc0, sra,   1, 7
#define hw_acmp0_admux			_xb1, adc0, admux, 4, 0


/*******************************************************************************
 *									       *
 *	Analog-to-Digital Converter					       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#include "../classes/adc_1.h"
#define hw_adc0				_adc, 0

/*	Object hardware registers	class, address, write mask, flags mask
 */
#define hw_adc0_admux			_r8,  0x27,   0xFF,   0x00
#define hw_adc0_sra			_r8,  0x26,   0xFF,   0x10
#define hw_adc0_adc			_r16, 0x24, 0x0000, 0x0000
#define hw_adc0_adch			_r8,  0x25,   0x00,   0x00
#define hw_adc0_srb			_r8,  0x23,   0xE7,   0x00

/*	Object logical registers
 */
#define hw_adc0_refs			_ob2, admux, 2, 6, 0, admux, 1, 4, 2
#define hw_adc0_lar			_ob1, admux, 1, 5
#define hw_adc0_mux			_ob1, admux, 4, 0

#define hw_adc0_en			_ob1, sra, 1, 7
#define hw_adc0_sc			_ob1, sra, 1, 6
#define hw_adc0_ate			_ob1, sra, 1, 5
#define hw_adc0_if			_ob1, sra, 1, 4
#define hw_adc0_ie			_ob1, sra, 1, 3
#define hw_adc0_ps			_ob1, sra, 3, 0

#define hw_adc0_bin			_ob1, srb, 1, 7
#define hw_adc0_ipr			_ob1, srb, 1, 5
#define hw_adc0_ts			_ob1, srb, 3, 0

/*	Analog inputs
 */
#define hw_pin_adc0			_ioa, portb, 1, 5
#define hw_pin_adc1			_ioa, portb, 1, 2
#define hw_pin_adc2			_ioa, portb, 1, 4
#define hw_pin_adc3			_ioa, portb, 1, 3
#define hw_pin_ain1			_ioa, portb, 1, 1
#define hw_pin_ain0			_ioa, portb, 1, 0


/*******************************************************************************
 *									       *
 *	EEPROM								       *
 *									       *
 *******************************************************************************/

/*	Class
 */
#include "../classes/eea_1.h"

/*	Object				class, address
 */
#define hw_eeprom0			_eea, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__eea_ar			_r16, 0x3E, 0x01FF, 0x00
#define hw__eea_dr			_r8,  0x3D,   0xFF, 0x00
#define hw__eea_cr			_r8,  0x3C,   0x3F, 0x00

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

/*	Class
 */
#include "../classes/fla_1.h"

/*	Object				class, address
 */
#define hw_flash0			_fla, 0

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw__fla_csr			_r8,  0x57, 0x3F, 0x00

/*	Class logical registers
 */
#define hw__fla_sigrd			_cb1, csr, 1, 5
#define hw__fla_rsig			_cb1, csr, 1, 5 /* old name */
#define hw__fla_rwwsre			_cb1, csr, 1, 4
#define hw__fla_ctpb			_cb1, csr, 1, 4 /* old name */
#define hw__fla_blbset			_cb1, csr, 1, 3
#define hw__fla_rflb			_cb1, csr, 1, 3 /* old name */
#define hw__fla_pgwrt			_cb1, csr, 1, 2
#define hw__fla_pgers			_cb1, csr, 1, 1
#define hw__fla_spmen			_cb1, csr, 1, 0


/*******************************************************************************
 *									       *
 *			C O N T E X T					       *
 *									       *
 *******************************************************************************/


#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin, reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;

  hwa_shared_t	shared ;

  hwa_corea_t	core0 ;
  hwa_gpa_t	portb ;
  hwa_pxa_t	pcic0 ;
  hwa_wda_t	watchdog0 ;
  hwa_cta_t	counter0 ;
  hwa_psb_t	prescaler1 ;
  hwa_ctb_t	counter1 ;
  hwa_usia_t	usi0 ;
  hwa_acb_t	acmp0 ;
  hwa_adc_t	adc0 ;
} hwa_t ;

#include "../hwa_2.h"
#include "../classes/c1_2.h"
#include "../classes/corea_2.h"
#include "../classes/ioa_2.h"
#include "../classes/gpa_2.h"
#include "../classes/pxa_2.h"
#include "../classes/wda_2.h"
#include "../classes/psa_2.h"
#include "../classes/oca_2.h"
#include "../classes/cta_2.h"
#include "../classes/ctb_2.h"
#include "../classes/ocb_2.h"
#include "../classes/psb_2.h"
#include "../classes/dtga_2.h"
#include "../classes/usia_2.h"
#include "../classes/adc_2.h"
#include "../classes/acb_2.h"
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

  _hwa_setup_o( portb );
  _hwa_setup_o( pcic0 );
  _hwa_setup_o( watchdog0 );
  _hwa_setup_o( counter0 );
  _hwa_setup_o( prescaler1 );
  _hwa_setup_o( counter1 );

  _hwa_setup_o( usi0 );
  _hwa_setup_o( acmp0 );
  _hwa_setup_o( adc0 );
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
  _hwa_init_o( portb );
  _hwa_init_o( pcic0 );
  _hwa_init_o( watchdog0 );
  _hwa_init_o( counter0 );
  _hwa_init_o( prescaler1 );
  _hwa_init_o( counter1 );
  _hwa_init_o( usi0 );
  _hwa_init_o( acmp0 );
  _hwa_init_o( adc0 );
}

HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_solve_o( counter0 );
  _hwa_solve_o( counter1 );

  _hwa_commit_r( shared, gimsk );
  _hwa_commit_r( shared, gifr	 );
  _hwa_commit_o( core0 );
  _hwa_commit_r( shared, prr	 );

  _hwa_commit_o( watchdog0 );
  _hwa_commit_o( pcic0 );
  _hwa_commit_o( portb );

  _hwa_commit_r( shared, gtccr );
  _hwa_commit_o( counter0 );
  _hwa_commit_r( shared, timsk );
  _hwa_commit_r( shared, tifr );

  _hwa_commit_o( prescaler1 );
  _hwa_commit_o( counter1 );
  _hwa_commit_o( usi0 );
  _hwa_commit_o( acmp0 );
  _hwa_commit_o( adc0 );
  _hwa_commit_r( shared, did );
}

#endif /* !defined __ASSEMBLER__ */
