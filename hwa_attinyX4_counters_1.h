
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_counters_1.h"
#include "hwa_atmelavr_c8a_1.h"
#include "hwa_atmelavr_c16a_1.h"


/*	Instance		class, name, id, address
 */
#define hw_counter0		c8a, counter0, 400, 0x0050

/*	Registers		'reg', rw, ra, riv, rwm
 */
#define hw_c8a_ocrb		reg, 8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_compare_b	reg, 8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_imsk		reg, 8, 0x59-0x50, 0x00, 0x07
#define hw_c8a_ifr		reg, 8, 0x58-0x50, 0x00, 0x07
#define hw_c8a_ocra		reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_compare_a	reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_ccrb		reg, 8, 0x53-0x50, 0x00, 0xCF
#define hw_c8a_count		reg, 8, 0x52-0x50, 0x00, 0xFF
#define hw_c8a_ccra		reg, 8, 0x50-0x50, 0x00, 0xF3

/*	Bits
 */
#define hw_c8a_coma		rb1, ccra, 2, 6
#define hw_c8a_comb		rb1, ccra, 2, 4
#define hw_c8a_wgm		rb2, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_c8a_foca		rb1, ccrb, 1, 7
#define hw_c8a_focb		rb1, ccrb, 1, 6
#define hw_c8a_cs		rb1, ccrb, 3, 0

#define hw_c8a_ocieb		rb1, imsk, 1, 2
#define hw_c8a_ociea		rb1, imsk, 1, 1
#define hw_c8a_oie		rb1, imsk, 1, 0

#define hw_c8a_ocfb		rb1, ifr, 1, 2
#define hw_c8a_ocfa		rb1, ifr, 1, 1
#define hw_c8a_ov		rb1, ifr, 1, 0


/*	Counter0 compare units
 *
 *	Instance		class, name, id, (address) ; hw_counter, ocr, io
 */
#define hw_counter0_compare_a		ocu, counter0_compare_a, 401,
#define hw_counter0_compare_a_ext	hw_counter0, ocra, pin_pb2 /* pin 5 */

#define hw_counter0_compare_b		ocu, counter0_compare_b, 402,
#define hw_counter0_compare_b_ext	hw_counter0, ocrb, pin_pa7 /* pin 6 */


/*	Counter1		class, name, id, address
 */
#define hw_counter1		c16a, counter1, 410, 0x002B

/*	Registers		'reg', rw, ra, riv, rwm
 */
#define hw_c16a_ccra		reg,  8, 0x4F -0x2B, 0x00,   0xF3
#define hw_c16a_ccrb		reg,  8, 0x4E -0x2B, 0x00,   0xDF
#define hw_c16a_ccrc		reg,  8, 0x42 -0x2B, 0x00,   0xC0
#define hw_c16a_count		reg, 16, 0x4C -0x2B, 0x0000, 0xFFFF
#define hw_c16a_countl		reg,  8, 0x4C -0x2B, 0x00,   0xFF
#define hw_c16a_counth		reg,  8, 0x4D -0x2B, 0x00,   0xFF
#define hw_c16a_ocra		reg, 16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_a	reg, 16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocral		reg,  8, 0x4A -0x2B, 0x00,   0xFF
#define hw_c16a_ocrah		reg,  8, 0x4B -0x2B, 0x00,   0xFF
#define hw_c16a_ocrb		reg, 16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_b	reg, 16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocrbl		reg,  8, 0x48 -0x2B, 0x00,   0xFF
#define hw_c16a_ocrbh		reg,  8, 0x49 -0x2B, 0x00,   0xFF
#define hw_c16a_icr		reg, 16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_capture		reg, 16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_icrl		reg,  8, 0x44 -0x2B, 0x00,   0xFF
#define hw_c16a_icrh		reg,  8, 0x45 -0x2B, 0x00,   0xFF
#define hw_c16a_imsk		reg,  8, 0x2C -0x2B, 0x00,   0x27
#define hw_c16a_ifr		reg,  8, 0x2B -0x2B, 0x00,   0x27
#define hw_c16a_acic		xreg, hw_acmp0, acic

/*	Bits
 */
#define hw_c16a_coma		rb1, ccra, 2, 6
#define hw_c16a_comocra		rb1, ccra, 2, 6 /* FIXME: for hw_config(ocu,...) */
#define hw_c16a_comb		rb1, ccra, 2, 4
#define hw_c16a_icnc		rb1, ccrb, 1, 7
#define hw_c16a_ices		rb1, ccrb, 1, 6
#define hw_c16a_cs		rb1, ccrb, 3, 0
#define hw_c16a_wgm		rb2, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define hw_c16a_icie		rb1, imsk, 1, 5
#define hw_c16a_ocieb		rb1, imsk, 1, 2
#define hw_c16a_ociea		rb1, imsk, 1, 1
#define hw_c16a_oie		rb1, imsk, 1, 0
#define hw_c16a_icf		rb1, imsk, 1, 5
#define hw_c16a_ocfb		rb1, imsk, 1, 2
#define hw_c16a_ocfa		rb1, imsk, 1, 1
#define hw_c16a_ov		rb1, imsk, 1, 0


/*	Counter1 compare units		class, name, id, (address) ; hw_counter, reg, io
 */
#define hw_counter1_compare_a		ocu, counter1_compare_a, 411,
#define hw_counter1_compare_a_ext	hw_counter1, ocra, pin_pa6	/* DIL pin_7 */

#define hw_counter1_compare_b		ocu, counter1_compare_b, 412,
#define hw_counter1_compare_b_ext	hw_counter1, ocrb, pin_pa5	/* DIL pin_8 */


/*	Counter1 capture unit		class, name, id, (address) ; hw_counter, reg, io
 */
#define hw_counter1_capture		icu, counter1_capture, 413,
#define hw_counter1_capture_ext		hw_counter1, icr, pin_pa7	/* DIL pin_6 */


#define HWA_DCL_COUNTERS			\
  hwa_c8a_t	counter0 ;			\
  hwa_c16a_t	counter1 ;
