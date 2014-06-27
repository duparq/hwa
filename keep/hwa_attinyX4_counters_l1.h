
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

//#include "hwa_l1_atmelavr_counters.h"
#include "hwa_atmelavr_c8a_l1.h"
#include "hwa_atmelavr_c16a_l1.h"


#define hw_max_c8a_isfn
#define hw_max_c8a(p,pc,pa)	255
#define hw_max_c16a_isfn
#define hw_max_c16a(p,pc,pa)	65535


/*	Peripheral		'per', name, class, base address
 */
#define hw_counter0		per, counter0, c8a, 0x0050

/*	Registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c8a_ocrb		reg, ocrb,  8, 0x5C-0x50, 0x00, 0xFF
#define hw_c8a_imsk		reg, imsk,  8, 0x59-0x50, 0x00, 0x07
#define hw_c8a_ifr		reg, ifr,   8, 0x58-0x50, 0x00, 0x07
#define hw_c8a_ocra		reg, ocra,  8, 0x56-0x50, 0x00, 0xFF
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



/*	Standard aliases
 */
#define hw_c8a_topreg		hw_c8a_ocra

#define hw_c8a_match_a		hw_c8a_ocra
#define hw_c8a_match_b		hw_c8a_ocrb

//#define hw_c8a_ie_overflow	hw_c8a_oie
//#define hw_c8a_ie_match_a	hw_c8a_ociea
//#define hw_c8a_ie_match_b	hw_c8a_ocieb
#define hw_c8a_ie_overflow	oie
#define hw_c8a_ie_match_a	ociea
#define hw_c8a_ie_match_b	ocieb

/* #define hw_c8a_if_overflow	regb, hw_c8a_ifr, 1, 0 */
/* #define hw_c8a_if_match_a	regb, hw_c8a_ifr, 1, 1 */
/* #define hw_c8a_if_match_b	regb, hw_c8a_ifr, 1, 2 */
#define hw_c8a_if_overflow	ov
#define hw_c8a_if_match_a	ocfa
#define hw_c8a_if_match_b	acfb


/*	Peripheral		'per', name, class, base address
 */
#define hw_is_ocu_ocu		, ok
#define hw_pertype_c8aoc	ok, ocu

#define hw_oc0a			per, oc0a, c8aoc, counter0, ocra
#define hw_oc0b			per, oc0b, c8aoc, counter0, ocrb


/*	Get the counter associated to an output-compare unit
 */
#define hw_pertype(...)		_hw_pertype_2(hw_pertype_##__VA_ARGS__)
#define _hw_pertype_2(...)	HW_G2(_hw_pertype_xok,HW_IS(ok,__VA_ARGS__))(__VA_ARGS__)
#define _hw_pertype_xok_no(...)	0
#define _hw_pertype_xok_ok(...)	HW_A1(__VA_ARGS__)

#define hw_counter(...)		HW_G2(hw_counter_xper, HW_IS(per,__VA_ARGS__))(__VA_ARGS__)
#define hw_counter_xper_no(pn)	HW_PPERROR("`" HW_QUOTE(pn) "` is not a peripheral.")

#define hw_counter_xper_ok(_per_,pn,pc,...)\
  HW_G2(hw_counter_xocu, HW_IS(ocu,hw_pertype(pc)))(pn)
#define hw_counter_xocu_ok(pn)	HW_G2(hw,HW_A3(hw_##pn))

#define hw_write_c8aoc_isfn
#define hw_write_c8aoc(pn,pc,counter,ocr, value)		\
  _hw_write(hw_##counter,ocr, value)


/*	Peripheral		'per', name, class, base address
 */
#define hw_counter1		per, counter1, c16a, 0x002B

/*	Class registers		'reg', name, rw, ra, riv, rwm
 */
#define hw_c16a_ccra		reg, ccra,     8, 0x4F -0x2B, 0x00,   0xF3
#define hw_c16a_ccrb		reg, ccrb,     8, 0x4E -0x2B, 0x00,   0xDF
#define hw_c16a_ccrc		reg, ccrc,     8, 0x42 -0x2B, 0x00,   0xC0
#define hw_c16a_count		reg, count,   16, 0x4C -0x2B, 0x0000, 0xFFFF
#define hw_c16a_countl		reg, countl,   8, 0x4C -0x2B, 0x00,   0xFF
#define hw_c16a_counth		reg, counth,   8, 0x4D -0x2B, 0x00,   0xFF
#define hw_c16a_match_a		reg, match_a, 16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocra		reg, ocra,    16, 0x4A -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocral		reg, ocral,    8, 0x4A -0x2B, 0x00,   0xFF
#define hw_c16a_ocrah		reg, ocrah,    8, 0x4B -0x2B, 0x00,   0xFF
#define hw_c16a_match_b		reg, match_b, 16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocrb		reg, ocrb,    16, 0x48 -0x2B, 0x0000, 0xFFFF
#define hw_c16a_ocrbl		reg, ocrbl,    8, 0x48 -0x2B, 0x00,   0xFF
#define hw_c16a_ocrbh		reg, ocrbh,    8, 0x49 -0x2B, 0x00,   0xFF
#define hw_c16a_icr		reg, icr,     16, 0x44 -0x2B, 0x0000, 0xFFFF
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
#define hw_c16a_ovf		regb, hw_c16a_imsk, 1, 0


#define HWA_DCL_COUNTERS			\
  hwa_c8a_t	counter0 ;			\
  hwa_c8aoc_t	oc0a ;				\
  hwa_c8aoc_t	oc0b ;				\
  hwa_c16a_t	counter1 ;
