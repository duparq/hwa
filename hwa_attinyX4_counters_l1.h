
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_counters_l1.h"
#include "hwa_atmelavr_c8a_l1.h"
#include "hwa_atmelavr_c16a_l1.h"


/*	Counter0		class, name, id, address
 */
#define hw_counter0		c8a, counter0, 600, 0x0050

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c8a_ocrb		reg, 8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_imsk		reg, 8, 0x59-0x50, 0x00, 0x07
#define hw_c8a_ifr		reg, 8, 0x58-0x50, 0x00, 0x07
#define hw_c8a_ocra		reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_compare_a	reg, 8, 0x56-0x50, 0x00, 0xFF
#define hw_c8a_ccrb		reg, 8, 0x53-0x50, 0x00, 0xCF
#define hw_c8a_count		reg, 8, 0x52-0x50, 0x00, 0xFF
#define hw_c8a_ccra		reg, 8, 0x50-0x50, 0x00, 0xF3

/*	Bits
 */
#define hw_c8a_coma		regb,  ccra, 2, 6
#define hw_c8a_comb		regb,  ccra, 2, 4
#define hw_c8a_wgm		regbb, ccra, 2, 0, 0, ccrb, 1, 3, 2

#define hw_c8a_foca		regb,  ccrb, 1, 7
#define hw_c8a_focb		regb,  ccrb, 1, 6
#define hw_c8a_cs		regb,  ccrb, 3, 0

#define hw_c8a_ocieb		regb,  imsk, 1, 2
#define hw_c8a_ociea		regb,  imsk, 1, 1
#define hw_c8a_oie		regb,  imsk, 1, 0

#define hw_c8a_ocfb		regb,  ifr, 1, 2
#define hw_c8a_ocfa		regb,  ifr, 1, 1
#define hw_c8a_ov		regb,  ifr, 1, 0


/*	Counter0 output-compare units	class, name, id, address
 */
#define hw_oc0a			ocu, oc0a, 601,
#define hw_oc0a_ext		hw_counter0, ocra, pin_5

#define hw_oc0b			ocu, oc0b, 602,
#define hw_oc0b_ext		hw_counter0, ocrb, pin_6


/*	Counter1		class, name, id, address
 */
#define hw_counter1		c16a, counter1, 700, 0x002B

/*	Registers		'reg', name, rw, ra, riv, rwm
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

/*	Bits
 */
#define hw_c16a_coma		regb,  ccra, 2, 6
#define hw_c16a_comb		regb,  ccra, 2, 4
#define hw_c16a_icnc		regb,  ccrb, 1, 7
#define hw_c16a_ices		regb,  ccrb, 1, 6
#define hw_c16a_cs		regb,  ccrb, 3, 0
#define hw_c16a_wgm		regbb, ccrb, 2, 3, 2, ccra, 2, 0, 0
#define hw_c16a_icie		regb,  imsk, 1, 5
#define hw_c16a_ocieb		regb,  imsk, 1, 2
#define hw_c16a_ociea		regb,  imsk, 1, 1
#define hw_c16a_oie		regb,  imsk, 1, 0
#define hw_c16a_icf		regb,  imsk, 1, 5
#define hw_c16a_ocfb		regb,  imsk, 1, 2
#define hw_c16a_ocfa		regb,  imsk, 1, 1
#define hw_c16a_ov		regb,  imsk, 1, 0


/*	Counter1 output-compare units	class, name, id, address
 */
#define hw_oc1a			ocu, oc1a, 701,
#define hw_oc1a_ext		hw_counter1, ocra, pin_7 /* counter, register, io */

#define hw_oc1b			ocu, oc1b, 702,
#define hw_oc1b_ext		hw_counter1, ocrb, pin_8


#define HWA_DCL_COUNTERS			\
  hwa_c8a_t	counter0 ;			\
  hwa_ocu_t	oc0a ;				\
  hwa_ocu_t	oc0b ;				\
  hwa_c16a_t	counter1 ;			\
  hwa_ocu_t	oc1a ;				\
  hwa_ocu_t	oc1b ;
