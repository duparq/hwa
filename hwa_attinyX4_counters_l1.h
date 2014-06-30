
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_counters_l1.h"
#include "hwa_atmelavr_c8a_l1.h"
#include "hwa_atmelavr_c16a_l1.h"


/*	Counter0		'ctr', class, name, base address
 */
#define hw_counter0		ctr, c8a, counter0, 0x0050

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c8a_ocrb		mem, reg, 8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_imsk		mem, reg, 8, 0x59-0x50, 0x00, 0x07
#define hw_c8a_ifr		mem, reg, 8, 0x58-0x50, 0x00, 0x07
#define hw_c8a_ocra		mem, reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_compare_a	mem, reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_ccrb		mem, reg, 8, 0x53-0x50, 0x00, 0xCF
#define hw_c8a_count		mem, reg, 8, 0x52-0x50, 0x00, 0xFF
#define hw_c8a_ccra		mem, reg, 8, 0x50-0x50, 0x00, 0xF3

/*	Bits
 */
#define hw_c8a_coma		mem, regb,  ccra, 2, 6
#define hw_c8a_comb		mem, regb,  ccra, 2, 4
#define hw_c8a_wgm		mem, regbb, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_c8a_foca		mem, regb,  ccrb, 1, 7
#define hw_c8a_focb		mem, regb,  ccrb, 1, 6
#define hw_c8a_cs		mem, regb,  ccrb, 3, 0

#define hw_c8a_ocieb		mem, regb,  imsk, 1, 2
#define hw_c8a_ociea		mem, regb,  imsk, 1, 1
#define hw_c8a_oie		mem, regb,  imsk, 1, 0

#define hw_c8a_ocfb		mem, regb,  ifr, 1, 2
#define hw_c8a_ocfa		mem, regb,  ifr, 1, 1
#define hw_c8a_ov		mem, regb,  ifr, 1, 0


/*	Counter0 output-compare units	'ctr', class, name, counter, register
 */
#define hw_oc0a			ctr, ocu, oc0a, hw_counter0, ocra, pin_5
#define hw_oc0b			ctr, ocu, oc0b, hw_counter0, ocrb, pin_6


/*	Counter1		'ctr', name, class, base address
 */
#define hw_counter1		ctr, c16a, counter1, 0x002B

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c16a_ccra		mem, reg,  8, 0x4F -0x2B, 0x00,   0xF3
#define hw_c16a_ccrb		mem, reg,  8, 0x4E -0x2B, 0x00,   0xDF
#define hw_c16a_ccrc		mem, reg,  8, 0x42 -0x2B, 0x00,   0xC0
#define hw_c16a_count		mem, reg, 16, 0x4C -0x2B, 0x0000, 0xFFFF
#define hw_c16a_countl		mem, reg,  8, 0x4C -0x2B, 0x00,   0xFF
#define hw_c16a_counth		mem, reg,  8, 0x4D -0x2B, 0x00,   0xFF
#define hw_c16a_ocra		mem, reg, 16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_a	mem, reg, 16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocral		mem, reg,  8, 0x4A -0x2B, 0x00,   0xFF
#define hw_c16a_ocrah		mem, reg,  8, 0x4B -0x2B, 0x00,   0xFF
#define hw_c16a_ocrb		mem, reg, 16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_compare_b	mem, reg, 16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocrbl		mem, reg,  8, 0x48 -0x2B, 0x00,   0xFF
#define hw_c16a_ocrbh		mem, reg,  8, 0x49 -0x2B, 0x00,   0xFF
#define hw_c16a_icr		mem, reg, 16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_capture		mem, reg, 16, 0x44 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_icrl		mem, reg,  8, 0x44 -0x2B, 0x00,   0xFF
#define hw_c16a_icrh		mem, reg,  8, 0x45 -0x2B, 0x00,   0xFF
#define hw_c16a_imsk		mem, reg,  8, 0x2C -0x2B, 0x00,   0x27
#define hw_c16a_ifr		mem, reg,  8, 0x2B -0x2B, 0x00,   0x27

/*	Bits
 */
#define hw_c16a_coma		mem, regb,  ccra, 2, 6
#define hw_c16a_comb		mem, regb,  ccra, 2, 4
#define hw_c16a_icnc		mem, regb,  ccrb, 1, 7
#define hw_c16a_ices		mem, regb,  ccrb, 1, 6
#define hw_c16a_cs		mem, regb,  ccrb, 3, 0
#define hw_c16a_wgm		mem, regbb, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define hw_c16a_icie		mem, regb,  imsk, 1, 5
#define hw_c16a_ocieb		mem, regb,  imsk, 1, 2
#define hw_c16a_ociea		mem, regb,  imsk, 1, 1
#define hw_c16a_oie		mem, regb,  imsk, 1, 0
#define hw_c16a_icf		mem, regb,  imsk, 1, 5
#define hw_c16a_ocfb		mem, regb,  imsk, 1, 2
#define hw_c16a_ocfa		mem, regb,  imsk, 1, 1
#define hw_c16a_ov		mem, regb,  imsk, 1, 0


/*	Counter1 output-compare units	'ctr', name, class, counter, register, io
 */
#define hw_oc1a			ctr, ocu, oc1a, hw_counter1, ocra, pin_7
#define hw_oc1b			ctr, ocu, oc1b, hw_counter1, ocrb, pin_8


#define HWA_DCL_COUNTERS			\
  hwa_c8a_t	counter0 ;			\
  hwa_ocu_t	oc0a ;				\
  hwa_ocu_t	oc0b ;				\
  hwa_c16a_t	counter1 ;			\
  hwa_ocu_t	oc1a ;				\
  hwa_ocu_t	oc1b ;
