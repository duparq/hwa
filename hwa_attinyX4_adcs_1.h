
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_ad10a_1.h"

/*
 *	Analog-Digital Converter
 */


/*	Instance			class, name, id, address
 */
#define hw_adc0				ad10a, adc0, 800, 0

/*	Interrupts			class, vector, controller, enable, flag
 */
#define hw_irq_adc0			irq, 13, adc0, ie, if

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw_ad10a_admux			crg,  8, 0x27,   0xFF,   0x00
#define hw_ad10a_sra			crg,  8, 0x26,   0xFF,   0x10
#define hw_ad10a_adc			crg, 16, 0x24, 0x0000, 0x0000
#define hw_ad10a_adch			crg,  8, 0x25,   0x00,   0x00
#define hw_ad10a_adcl			crg,  8, 0x24,   0x00,   0x00
#define hw_ad10a_srb			crg,  8, 0x23,   0xD7,   0x00
#define hw_ad10a_did			crg,  8, 0x21,   0xFF,   0x00   /* port A */

#define hw_ad10a_refs			cb1, admux, 2, 6
#define hw_ad10a_mux			cb1, admux, 6, 0

#define hw_ad10a_en			cb1, sra, 1, 7
#define hw_ad10a_sc			cb1, sra, 1, 6
#define hw_ad10a_ate			cb1, sra, 1, 5
#define hw_ad10a_if			cb1, sra, 1, 4
#define hw_ad10a_ie			cb1, sra, 1, 3
#define hw_ad10a_ps			cb1, sra, 3, 0

#define hw_ad10a_bin			cb1, srb, 1, 7
#define hw_ad10a_me			cb1, srb, 1, 6
#define hw_ad10a_lar			cb1, srb, 1, 4
#define hw_ad10a_ts			cb1, srb, 3, 0

#define hw_ad10a_did_0			cb1, did, 1, 0
#define hw_ad10a_did_1			cb1, did, 1, 1
#define hw_ad10a_did_2			cb1, did, 1, 2
#define hw_ad10a_did_3			cb1, did, 1, 3
#define hw_ad10a_did_4			cb1, did, 1, 4
#define hw_ad10a_did_5			cb1, did, 1, 5
#define hw_ad10a_did_6			cb1, did, 1, 6
#define hw_ad10a_did_7			cb1, did, 1, 7

/*	Instances			class, name, id, number
 */
#define hw_pin_adc0			adpin, pin_adc0, 801, 0
#define hw_pin_adc1			adpin, pin_adc1, 802, 1
#define hw_pin_adc2			adpin, pin_adc2, 803, 2
#define hw_pin_adc3			adpin, pin_adc3, 804, 3
#define hw_pin_adc4			adpin, pin_adc4, 805, 4
#define hw_pin_adc5			adpin, pin_adc5, 806, 5
#define hw_pin_adc6			adpin, pin_adc6, 807, 6
#define hw_pin_adc7			adpin, pin_adc7, 808, 7


#if !defined __ASSEMBLER__
#  define HWA_DCL_ADCS		hwa_ad10a_t  adc0
#endif
