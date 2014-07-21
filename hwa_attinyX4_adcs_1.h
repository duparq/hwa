
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_ad10a_1.h"

/*
 *	Analog-Digital Converter
 */


/*	Instance		class, name, id, address
 */
#define hw_adc0			ad10a, adc0, 800, 0x0021

/*	Class registers		rt, rw, ra, riv, rwm
 */
#define hw_ad10a_admux		crg,  8, 0x27 -0x0021, 0x00,   0xFF
#define hw_ad10a_sra		crg,  8, 0x26 -0x0021, 0x00,   0xFF
#define hw_ad10a_adc		crg, 16, 0x24 -0x0021, 0x0000, 0x0000
#define hw_ad10a_adch		crg,  8, 0x25 -0x0021, 0x00,   0x00
#define hw_ad10a_adcl		crg,  8, 0x24 -0x0021, 0x00,   0x00
#define hw_ad10a_srb		crg,  8, 0x23 -0x0021, 0x00,   0xFF
#define hw_ad10a_did		crg,  8, 0x21 -0x0021, 0x00,   0xFF /* port A */

/*	Class bits
 */
#define hw_ad10a_refs		cb1, admux, 2, 6
#define hw_ad10a_mux		cb1, admux, 6, 0
#define hw_ad10a_en		cb1, sra, 1, 7
#define hw_ad10a_sc		cb1, sra, 1, 6
#define hw_ad10a_ate		cb1, sra, 1, 5
#define hw_ad10a_if		cb1, sra, 1, 4
#define hw_ad10a_ie		cb1, sra, 1, 3
#define hw_ad10a_ps		cb1, sra, 3, 0

#define hw_ad10a_bin		cb1, srb, 1, 7
#define hw_ad10a_me		cb1, srb, 1, 6
#define hw_ad10a_lar		cb1, srb, 1, 4
#define hw_ad10a_ts		cb1, srb, 3, 0

#define hw_ad10a_did_0		cb1, did, 1, 0
#define hw_ad10a_did_1		cb1, did, 1, 1
#define hw_ad10a_did_2		cb1, did, 1, 2
#define hw_ad10a_did_3		cb1, did, 1, 3
#define hw_ad10a_did_4		cb1, did, 1, 4
#define hw_ad10a_did_5		cb1, did, 1, 5
#define hw_ad10a_did_6		cb1, did, 1, 6
#define hw_ad10a_did_7		cb1, did, 1, 7

/*	Instances		class, name, id, (address)
 */
#define hw_pin_adc0		adpin, pin_adc0, 801, 0
#define hw_pin_adc1		adpin, pin_adc1, 802, 1
#define hw_pin_adc2		adpin, pin_adc2, 803, 2
#define hw_pin_adc3		adpin, pin_adc3, 804, 3
#define hw_pin_adc4		adpin, pin_adc4, 805, 4
#define hw_pin_adc5		adpin, pin_adc5, 806, 5
#define hw_pin_adc6		adpin, pin_adc6, 807, 6
#define hw_pin_adc7		adpin, pin_adc7, 808, 7


#if !defined __ASSEMBLER__
#  define HWA_DCL_ADCS		hwa_ad10a_t  adc0
#endif


/*	OEM symbols		type, instance, reg...
 */
/* #define hw_ADMUX		ir, adc0, admux */
/* #define hw_ADREFS1		ib, adc0, admux, 0b1, 7 */
/* #define hw_ADREFS0		ib, adc0, admux, 0b1, 6 */

/* #define hw_ADCSRA		ir, adc0, sra */
/* #define hw_ADEN			ib, adc0, sra, 0b1,   7 */
/* #define hw_ADSC			ib, adc0, sra, 0b1,   6 */
/* #define hw_ADATE		ib, adc0, sra, 0b1,   5 */
/* #define hw_ADIF			ib, adc0, sra, 0b1,   4 */
/* #define hw_ADIE			ib, adc0, sra, 0b1,   3 */
/* #define hw_ADPS			ib, adc0, sra, 0b111, 0 */

/* #define hw_ADCH 		ir, adc0, adch */
/* #define hw_ADCL 		ir, adc0, adcl */
/* #define hw_ADC  		ir, adc0, adc */

/* #define hw_ADCSRB		ir, adc0, srb */
/* #define hw_BIN			ib, adc0, srb, 0b1,   7 */
/* #define hw_ACME			ib, adc0, srb, 0b1,   6 */
/* #define hw_ADLAR		ib, adc0, srb, 0b1,   4 */
/* #define hw_ADTS			ib, adc0, srb, 0b111, 0 */


/*	Useful OEM symbols extensions (groups of bits)
 */
/* #define hw_REFS			ib, adc0, admux, 0b11,     6 */
/* #define hw_MUX			ib, adc0, admux, 0b111111, 0 */

/* #define hw_adc_aden		xb, sra, 0b1,   7 */
/* #define hw_adc_adsc		xb, sra, 0b1,   6 */
/* #define hw_adc_adate		xb, sra, 0b1,   5 */
/* #define hw_adc_adif		xb, sra, 0b1,   4 */
/* #define hw_adc_adie		xb, sra, 0b1,   3 */
/* #define hw_adc_adps		xb, sra, 0b111, 0 */

/* #define hw_adc_refs		xb, admux, 0b11,     6 */
/* #define hw_adc_mux		xb, admux, 0b111111, 0 */
