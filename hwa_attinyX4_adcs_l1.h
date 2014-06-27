
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	Analog-Digital Converter
 */


/*	Controller		'ctr', name, class, address
 */
#define hw_adc0			ctr, adc0, adc, 0x0021

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_adc_admux		reg, admux,  8, 0x27 -0x0021, 0x00,   0xFF
#define hw_adc_sra		reg, sra,    8, 0x26 -0x0021, 0x00,   0xFF
#define hw_adc_adc		reg, adc,   16, 0x24 -0x0021, 0x0000, 0x0000
#define hw_adc_adch		reg, adch,   8, 0x25 -0x0021, 0x00,   0x00
#define hw_adc_adcl		reg, adcl,   8, 0x24 -0x0021, 0x00,   0x00
#define hw_adc_srb		reg, srb,    8, 0x23 -0x0021, 0x00,   0xFF
#define hw_adc_did		reg, did,    8, 0x21 -0x0021, 0x00,   0xFF

/*	Bits
 */
#define hw_adc_refs		regb, hw_adc_admux, 2, 6
#define hw_adc_mux		regb, hw_adc_admux, 6, 0
#define hw_adc_en		regb, hw_adc_sra, 1, 7
#define hw_adc_sc		regb, hw_adc_sra, 1, 6
#define hw_adc_ate		regb, hw_adc_sra, 1, 5
#define hw_adc_if		regb, hw_adc_sra, 1, 4
#define hw_adc_ie		regb, hw_adc_sra, 1, 3
#define hw_adc_ps		regb, hw_adc_sra, 3, 0


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

//#define hw_read_adc_isfn
//#define hw_read_adc(cn,cc,ca)		hw_read(hw_##cn,adc)
//#define hw_read_adc(...)		_HW_APPLY_REG_1(hw_read,ctr,__VA_ARGS__,adc)


/******************************************************************************
 *									      *
 *			HWA structure					      *
 *									      *
 ******************************************************************************/

/**
 * \todo
 */
#ifndef __ASSEMBLER__
typedef struct {
  hwa_r8_t admux ;
  hwa_r8_t sra ;
  hwa_r8_t srb ;
  hwa_r8_t did ;
} hwa_adc_t ;
#endif

#define HWA_DCL_ADCS				\
  hwa_adc_t  adc0 ;
