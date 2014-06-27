
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_counters_l1.h"
#include "hwa_atmelavr_c8a_l1.h"
#include "hwa_atmelavr_c16a_l1.h"


/*	Counter0		'ctr', name, class, base address
 */
#define hw_counter0		ctr, counter0, c8a, 0x0050

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c8a_ocrb		reg, ocrb,  8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_imsk		reg, imsk,  8, 0x59-0x50, 0x00, 0x07
#define hw_c8a_ifr		reg, ifr,   8, 0x58-0x50, 0x00, 0x07
#define hw_c8a_ocra		reg, ocra,  8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_compare_a	reg, ocra,  8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_ccrb		reg, ccrb,  8, 0x53-0x50, 0x00, 0xCF
#define hw_c8a_count		reg, count, 8, 0x52-0x50, 0x00, 0xFF
#define hw_c8a_ccra		reg, ccra,  8, 0x50-0x50, 0x00, 0xF3

/*	Bits
 */
#define hw_c8a_coma		regb,  hw_c8a_ccra, 2, 6
#define hw_c8a_comb		regb,  hw_c8a_ccra, 2, 4
#define hw_c8a_wgm		regbb, hw_c8a_ccra, 2, 0, 0, hw_c8a_ccrb, 1, 3, 2

#define hw_c8a_foca		regb,  hw_c8a_ccrb, 1, 7
#define hw_c8a_focb		regb,  hw_c8a_ccrb, 1, 6
#define hw_c8a_cs		regb,  hw_c8a_ccrb, 3, 0

#define hw_c8a_ocieb		regb,  hw_c8a_imsk, 1, 2
#define hw_c8a_ociea		regb,  hw_c8a_imsk, 1, 1
#define hw_c8a_oie		regb,  hw_c8a_imsk, 1, 0

#define hw_c8a_ocfb		regb,  hw_c8a_ifr, 1, 2
#define hw_c8a_ocfa		regb,  hw_c8a_ifr, 1, 1
#define hw_c8a_ov		regb,  hw_c8a_ifr, 1, 0


/*	Counter0 output-compare units	'ctr', name, class, counter, register
 */
#define hw_oc0a			ctr, oc0a, ocu, hw_counter0, ocra, pin_5
#define hw_oc0b			ctr, oc0b, ocu, hw_counter0, ocrb, pin_6


/*	Counter1		'ctr', name, class, base address
 */
#define hw_counter1		ctr, counter1, c16a, 0x002B

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c16a_ccra		reg, ccra,     8, 0x4F -0x2B, 0x00,   0xF3
#define hw_c16a_ccrb		reg, ccrb,     8, 0x4E -0x2B, 0x00,   0xDF
#define hw_c16a_ccrc		reg, ccrc,     8, 0x42 -0x2B, 0x00,   0xC0
#define hw_c16a_count		reg, count,   16, 0x4C -0x2B, 0x0000, 0xFFFF
#define hw_c16a_countl		reg, countl,   8, 0x4C -0x2B, 0x00,   0xFF
#define hw_c16a_counth		reg, counth,   8, 0x4D -0x2B, 0x00,   0xFF
#define hw_c16a_ocra		reg, ocra,    16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_a	reg, ocra,    16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocral		reg, ocral,    8, 0x4A -0x2B, 0x00,   0xFF
#define hw_c16a_ocrah		reg, ocrah,    8, 0x4B -0x2B, 0x00,   0xFF
#define hw_c16a_ocrb		reg, ocrb,    16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_b	reg, ocrb,    16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocrbl		reg, ocrbl,    8, 0x48 -0x2B, 0x00,   0xFF
#define hw_c16a_ocrbh		reg, ocrbh,    8, 0x49 -0x2B, 0x00,   0xFF
#define hw_c16a_icr		reg, icr,     16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_capture		reg, icr,     16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_icrl		reg, icrl,     8, 0x44 -0x2B, 0x00,   0xFF
#define hw_c16a_icrh		reg, icrh,     8, 0x45 -0x2B, 0x00,   0xFF
#define hw_c16a_imsk		reg, imsk,     8, 0x2C -0x2B, 0x00,   0x27
#define hw_c16a_ifr		reg, ifr,      8, 0x2B -0x2B, 0x00,   0x27

/*	Bits
 */
#define hw_c16a_coma		regb, hw_c16a_ccra, 2, 6
#define hw_c16a_comb		regb, hw_c16a_ccra, 2, 4
#define hw_c16a_icnc		regb, hw_c16a_ccrb, 1, 7
#define hw_c16a_ices		regb, hw_c16a_ccrb, 1, 6
#define hw_c16a_cs		regb, hw_c16a_ccrb, 3, 0
#define hw_c16a_wgm		regbb, hw_c16a_ccrb, 2, 3, 2, hw_c16a_ccra, 2, 0, 0
#define hw_c16a_icie		regb, hw_c16a_imsk, 1, 5
#define hw_c16a_ocieb		regb, hw_c16a_imsk, 1, 2
#define hw_c16a_ociea		regb, hw_c16a_imsk, 1, 1
#define hw_c16a_oie		regb, hw_c16a_imsk, 1, 0
#define hw_c16a_icf		regb, hw_c16a_imsk, 1, 5
#define hw_c16a_ocfb		regb, hw_c16a_imsk, 1, 2
#define hw_c16a_ocfa		regb, hw_c16a_imsk, 1, 1
#define hw_c16a_ov		regb, hw_c16a_imsk, 1, 0


/*	Counter1 output-compare units	'ctr', name, class, counter, register, io
 */
#define hw_oc1a			ctr, oc1a, ocu, hw_counter1, ocra, pin_7
#define hw_oc1b			ctr, oc1b, ocu, hw_counter1, ocrb, pin_8


#define HWA_DCL_COUNTERS			\
  hwa_c8a_t	counter0 ;			\
  hwa_ocu_t	oc0a ;				\
  hwa_ocu_t	oc0b ;				\
  hwa_c16a_t	counter1 ;			\
  hwa_ocu_t	oc1a ;				\
  hwa_ocu_t	oc1b ;
