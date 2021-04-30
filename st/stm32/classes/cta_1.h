
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General-purpose 16-bit counter-timer
 */

/*  Load the channels implementation definitions
 */
#include "cca_1.h"

/**
 * @ingroup stm32_classes
 * @defgroup stm32_cta Class _cta: General-purpose 16-bit counter-timer
 *
 * This class is used by:
 *
 * * @ref stm32f103 "STM32F103": `counter2`, `counter3`, `counter4`
 * * @ref stm32f411 "STM32F411": `counter3`, `counter4`
 *
 * @section stm32_ctarel Relatives
 *
 * * @ref hwa_irq "Interrupts"
 *
 *   * `(COUNTER,irq)`: counter overflow IRQ (update event)
 *
 * * @ref hwa_reg "Registers"
 *
 *   * @ref hwa_cb1 "(COUNTER,prescaler)": one 16-bit prescaler
 *   * @ref hwa_cb1 "(COUNTER,reload)": reload register (ARR)
 *
 *   * Hardware registers: `cr1`, `cr2`, `smcr`, `dier`, `sr`, `egr`, `ccmr1`,
 *   `ccmr2`, `ccer`, `cnt`, `psc`, `arr`, `dcr`, `dmar`.
 *
 *   * Logical registers: `ckd`, `arpe`, `cms`, `dir`, `cmsdir`, `opm`,
 *   `cmsdiropm`, `urs`, `udis`, `cen`, `ti1s`, `mms`, `ccds`, `etp`, `ece`,
 *   `etps`, `etf`, `msm`, `ts`, `sms`, `tde`, `ude`, `tie`, `uie`, `ie`, `if`
 *
 * * @ref stm32_cca "(COUNTER,channel1..4)": 4 independent channels of capture (input) or compare (output)
 *
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

#define hw__cta_irq			_irq, uie, uif, 0		// Clear flag writing 0 (rc_w0)

/*	Generate relatives for channels:
 *	  _cca,(counterX,channelY),(Y)
 */
#define hw__cta_			, _hw_ctarl

#define _hw_ctarl(o,r,d)		HW_BED(_hw_ctarl,_hw__cta_##r,o,r)
#define _hw_ctarl0(o,r,...)		HW_E(HW_EM_OO(o,r))
#define _hw_ctarl1(o,r,c,...)		c,(o,r),(__VA_ARGS__)

#define _hw__cta_channel1		_cca, 1
#define _hw__cta_channel2		_cca, 2
#define _hw__cta_channel3		_cca, 3
#define _hw__cta_channel4		_cca, 4


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r16_t cr1 ;
  hwa_r16_t cr2 ;
  hwa_r16_t smcr ;
  hwa_r16_t dier ;
  hwa_r16_t egr ;
  hwa_r16_t ccmr1 ;
  hwa_r16_t ccmr2 ;
  hwa_r16_t ccer ;
  hwa_r16_t cnt ;
  hwa_r16_t psc ;
  hwa_r16_t arr ;
  hwa_r16_t ccr1 ;
  hwa_r16_t ccr2 ;
  hwa_r16_t ccr3 ;
  hwa_r16_t ccr4 ;
} hwa_cta_t ;

#endif
