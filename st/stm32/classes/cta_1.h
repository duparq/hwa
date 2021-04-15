
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General-purpose 16-bit counter-timer
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_cta Class _cta: General-purpose 16-bit counter-timer
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `counter2`, `counter3`, `counter4`
 *
 * @section stm32f103_ctarel Relatives
 *
 * * @ref hwa_irq "(COUNTER,irq)": counter overflow IRQ
 * * @ref hwa_cb1 "(COUNTER,prescaler)": one 16-bit prescaler
 * * @ref hwa_cb1 "(COUNTER,reload)": reload register (ARR)
 * * @ref stm32_cca "(COUNTER,channel1..4)": 4 independent channels of capture (input) or compare (output)
 * * . . .
 * * Hardware registers: @ref hwa_r16 "cr1", @ref hwa_r16 "cr2",
 *   @ref hwa_r16 "smcr", @ref hwa_r16 "dier", @ref hwa_r16 "sr", @ref hwa_r16
 *   "egr", @ref hwa_r16 "ccmr1", @ref hwa_r16 "ccmr2", @ref hwa_r16 "ccer",
 *   @ref hwa_r16 "cnt", @ref hwa_r16 "psc", @ref hwa_r16 "arr", @ref hwa_r16
 *   "ccr1", @ref hwa_r16 "ccr2", @ref hwa_r16 "ccr3", @ref hwa_r16 "ccr4",
 *   @ref hwa_r16 "dcr", @ref hwa_r16 "dmar".
 *
 * * Logical registers: @ref hwa_cb1 "ckd", @ref hwa_cb1 "arpe", @ref hwa_cb1
 *   "cms", @ref hwa_cb1 "dir", @ref hwa_cb1 "cmsdir", @ref hwa_cb1 "opm",
 *   @ref hwa_cb1 "cmsdiropm", @ref hwa_cb1 "urs", @ref hwa_cb1 "udis", @ref
 *   hwa_cb1 "cen", @ref hwa_cb1 "ti1s", @ref hwa_cb1 "mms", @ref hwa_cb1
 *   "ccds", @ref hwa_cb1 "etp", @ref hwa_cb1 "ece", @ref hwa_cb1 "etps", @ref
 *   hwa_cb1 "etf", @ref hwa_cb1 "msm", @ref hwa_cb1 "ts", @ref hwa_cb1 "sms",
 *   @ref hwa_cb1 "tde", @ref hwa_cb1 "cc4de", @ref hwa_cb1 "cc3de", @ref
 *   hwa_cb1 "cc2de", @ref hwa_cb1 "cc1de", @ref hwa_cb1 "ude", @ref hwa_cb1
 *   "tie", @ref hwa_cb1 "cc4ie", @ref hwa_cb1 "cc3ie", @ref hwa_cb1 "cc2ie",
 *   @ref hwa_cb1 "cc1ie", @ref hwa_cb1 "uie", @ref hwa_cb1 "ie", @ref hwa_cb1
 *   "if", @ref hwa_cb1 "cc4p", @ref hwa_cb1 "cc4e", @ref hwa_cb1 "cc3p", @ref
 *   hwa_cb1 "cc3e", @ref hwa_cb1 "cc2p", @ref hwa_cb1 "cc2e", @ref hwa_cb1
 *   "cc1p", @ref hwa_cb1 "cc1e", @ref hwa_cb1 "oc2ce", @ref hwa_cb1 "oc2m",
 *   @ref hwa_cb1 "ic2f", @ref hwa_cb1 "oc2pe", @ref hwa_cb1 "oc2fe", @ref
 *   hwa_cb1 "ic2psc", @ref hwa_cb1 "cc2s", @ref hwa_cb1 "oc1ce", @ref hwa_cb1
 *   "oc1m", @ref hwa_cb1 "ic1f", @ref hwa_cb1 "oc1pe", @ref hwa_cb1 "oc1fe",
 *   @ref hwa_cb1 "ic1psc", @ref hwa_cb1 "cc1s", @ref hwa_cb1 "oc4ce", @ref
 *   hwa_cb1 "oc4m", @ref hwa_cb1 "ic4f", @ref hwa_cb1 "oc4pe", @ref hwa_cb1
 *   "oc4fe", @ref hwa_cb1 "ic4psc", @ref hwa_cb1 "cc4s", @ref hwa_cb1
 *   "oc3ce", @ref hwa_cb1 "oc3m", @ref hwa_cb1 "ic3f", @ref hwa_cb1 "oc3pe",
 *   @ref hwa_cb1 "oc3fe", @ref hwa_cb1 "ic3psc", @ref hwa_cb1 "cc3s" 
*/

#define hw_class__cta

#define hw__cta_cr1			_r16, 0x00, 0x03FF, 0
#define hw__cta_cr2			_r16, 0x04, 0x00F8, 0
#define hw__cta_smcr			_r16, 0x08, 0xFFF7, 0
#define hw__cta_dier			_r16, 0x0C, 0x5F5F, 0
#define hw__cta_sr			_r16, 0x10, 0x1E7F, 0
#define hw__cta_egr			_r16, 0x14, 0x005F, 0
#define hw__cta_ccmr1			_r16, 0x18, 0xFFFF, 0
#define hw__cta_ccmr2			_r16, 0x1C, 0xFFFF, 0
#define hw__cta_ccer			_r16, 0x20, 0x3333, 0
#define hw__cta_cnt			_r16, 0x24, 0xFFFF, 0
#define hw__cta_psc			_r16, 0x28, 0xFFFF, 0
#define hw__cta_arr			_r16, 0x2C, 0xFFFF, 0
#define hw__cta_ccr1			_r16, 0x34, 0xFFFF, 0
#define hw__cta_ccr2			_r16, 0x38, 0xFFFF, 0
#define hw__cta_ccr3			_r16, 0x3C, 0xFFFF, 0
#define hw__cta_ccr4			_r16, 0x40, 0xFFFF, 0
#define hw__cta_dcr			_r16, 0x48, 0x1F1F, 0
#define hw__cta_dmar			_r16, 0x4C, 0xFFFF, 0

#define hw__cta_ckd			_cb1, cr1, 2, 8
#define hw__cta_arpe			_cb1, cr1, 1, 7
#define hw__cta_cms			_cb1, cr1, 2, 5
#define hw__cta_dir			_cb1, cr1, 1, 4
#define hw__cta_cmsdir			_cb1, cr1, 3, 4		// Convenient
#define hw__cta_opm			_cb1, cr1, 1, 3
#define hw__cta_cmsdiropm		_cb1, cr1, 4, 3		// Convenient
#define hw__cta_urs			_cb1, cr1, 1, 2
#define hw__cta_udis			_cb1, cr1, 1, 1
#define hw__cta_cen			_cb1, cr1, 1, 0

#define hw__cta_ti1s			_cb1, cr2, 1, 7
#define hw__cta_mms			_cb1, cr2, 3, 4
#define hw__cta_ccds			_cb1, cr2, 1, 3

#define hw__cta_etp			_cb1, smcr, 1, 15
#define hw__cta_ece			_cb1, smcr, 1, 14
#define hw__cta_etps			_cb1, smcr, 2, 12
#define hw__cta_etf			_cb1, smcr, 4, 8
#define hw__cta_msm			_cb1, smcr, 1, 7
#define hw__cta_ts			_cb1, smcr, 3, 4
#define hw__cta_sms			_cb1, smcr, 3, 0

#define hw__cta_tde			_cb1, dier, 1, 14
#define hw__cta_cc4de			_cb1, dier, 1, 12
#define hw__cta_cc3de			_cb1, dier, 1, 11
#define hw__cta_cc2de			_cb1, dier, 1, 10
#define hw__cta_cc1de			_cb1, dier, 1, 9
#define hw__cta_ude			_cb1, dier, 1, 8
#define hw__cta_tie			_cb1, dier, 1, 6
#define hw__cta_cc4ie			_cb1, dier, 1, 4
#define hw__cta_cc3ie			_cb1, dier, 1, 3
#define hw__cta_cc2ie			_cb1, dier, 1, 2
#define hw__cta_cc1ie			_cb1, dier, 1, 1
#define hw__cta_uie			_cb1, dier, 1, 0
//#define hw__cta_ie			_cb1, dier, 1, 0	// Convenient

#define hw__cta_cc4of			_cb1, sr, 1, 12
#define hw__cta_cc3of			_cb1, sr, 1, 11
#define hw__cta_cc2of			_cb1, sr, 1, 10
#define hw__cta_cc1of			_cb1, sr, 1, 9
#define hw__cta_tif			_cb1, sr, 1, 6
#define hw__cta_cc4if			_cb1, sr, 1, 4
#define hw__cta_cc3if			_cb1, sr, 1, 3
#define hw__cta_cc2if			_cb1, sr, 1, 2
#define hw__cta_cc1if			_cb1, sr, 1, 1
#define hw__cta_uif			_cb1, sr, 1, 0

#define hw__cta_cc4p			_cb1, ccer, 1, 13
#define hw__cta_cc4e			_cb1, ccer, 1, 12
#define hw__cta_cc3p			_cb1, ccer, 1,  9
#define hw__cta_cc3e			_cb1, ccer, 1,  8
#define hw__cta_cc2p			_cb1, ccer, 1,  5
#define hw__cta_cc2e			_cb1, ccer, 1,  4
#define hw__cta_cc1p			_cb1, ccer, 1,  1
#define hw__cta_cc1e			_cb1, ccer, 1,  0

#define hw__cta_oc2ce			_cb1, ccmr1, 1, 15
#define hw__cta_oc2m			_cb1, ccmr1, 3, 12
#define hw__cta_ic2f			_cb1, ccmr1, 4, 12
#define hw__cta_oc2pe			_cb1, ccmr1, 1, 11
#define hw__cta_oc2fe			_cb1, ccmr1, 1, 10
#define hw__cta_ic2psc			_cb1, ccmr1, 2, 10
#define hw__cta_cc2s			_cb1, ccmr1, 2,  8

#define hw__cta_oc1ce			_cb1, ccmr1, 1,  7
#define hw__cta_oc1m			_cb1, ccmr1, 3,  4
#define hw__cta_ic1f			_cb1, ccmr1, 4,  4
#define hw__cta_oc1pe			_cb1, ccmr1, 1,  3
#define hw__cta_oc1fe			_cb1, ccmr1, 1,  2
#define hw__cta_ic1psc			_cb1, ccmr1, 2,  2
#define hw__cta_cc1s			_cb1, ccmr1, 2,  0

#define hw__cta_oc4ce			_cb1, ccmr2, 1, 15
#define hw__cta_oc4m			_cb1, ccmr2, 3, 12
#define hw__cta_ic4f			_cb1, ccmr2, 4, 12
#define hw__cta_oc4pe			_cb1, ccmr2, 1, 11
#define hw__cta_oc4fe			_cb1, ccmr2, 1, 10
#define hw__cta_ic4psc			_cb1, ccmr2, 2, 10
#define hw__cta_cc4s			_cb1, ccmr2, 2,  8

#define hw__cta_oc3ce			_cb1, ccmr2, 1,  7
#define hw__cta_oc3m			_cb1, ccmr2, 3,  4
#define hw__cta_ic3f			_cb1, ccmr2, 4,  4
#define hw__cta_oc3pe			_cb1, ccmr2, 1,  3
#define hw__cta_oc3fe			_cb1, ccmr2, 1,  2
#define hw__cta_ic3psc			_cb1, ccmr2, 2,  2
#define hw__cta_cc3s			_cb1, ccmr2, 2,  0

/*  Relatives
 */
#define hw__cta_prescaler		_cb1, psc, 16, 0
#define hw__cta_reload			_cb1, arr, 16, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r16_t cr1 ;
  hwa_r16_t cr2 ;
  hwa_r16_t smcr ;
  hwa_r16_t dier ;
  //  hwa_r16_t sr ;
  hwa_r16_t egr ;
  hwa_r16_t ccmr1 ;
  hwa_r16_t ccmr2 ;
  hwa_r16_t ccer ;
  hwa_r16_t cnt ;
  hwa_r16_t psc ;
  hwa_r16_t arr ;
  hwa_r16_t ccr3 ;
} hwa_cta_t ;

#endif
