
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief General-purpose 16-bit counter-timer
 */

/**
 * @page stm32_c16a Class _c16a: General-purpose 16-bit counter-timer
 *
 * `_c16a` class objects are 16-bit counters able to count up, down, and
 * up/down with a programmable auto-reload value.
 *
 * `_c16a` counters have the following relatives:
 *
 * * one 16-bit prescaler,
 *
 * * 4 independent channels of capture (input) or compare (output)
 *
 * * . . .
 *
 */
#define hw_class__c16a

#define hw__c16a_cr1			_r16, 0x00, 0x03FF, 0
#define hw__c16a_cr2			_r16, 0x04, 0x00F8, 0
#define hw__c16a_smcr			_r16, 0x08, 0xFFF7, 0
#define hw__c16a_dier			_r16, 0x0C, 0x5F5F, 0
#define hw__c16a_sr			_r16, 0x10, 0x1E7F, 0
#define hw__c16a_egr			_r16, 0x14, 0x005F, 0
#define hw__c16a_ccmr1			_r16, 0x18, 0xFFFF, 0
#define hw__c16a_ccmr2			_r16, 0x1C, 0xFFFF, 0
#define hw__c16a_ccer			_r16, 0x20, 0x3333, 0
#define hw__c16a_cnt			_r16, 0x24, 0xFFFF, 0
#define hw__c16a_psc			_r16, 0x28, 0xFFFF, 0
#define hw__c16a_prescaler		psc			// Synonym
#define hw__c16a_arr			_r16, 0x2C, 0xFFFF, 0
#define hw__c16a_reload			arr			// Synonym
#define hw__c16a_ccr1			_r16, 0x34, 0xFFFF, 0
#define hw__c16a_ccr2			_r16, 0x38, 0xFFFF, 0
#define hw__c16a_ccr3			_r16, 0x3C, 0xFFFF, 0
#define hw__c16a_ccr4			_r16, 0x40, 0xFFFF, 0
#define hw__c16a_dcr			_r16, 0x48, 0x1F1F, 0
#define hw__c16a_dmar			_r16, 0x4C, 0xFFFF, 0

#define hw__c16a_ckd			_cb1, cr1, 2, 8
#define hw__c16a_arpe			_cb1, cr1, 1, 7
#define hw__c16a_cms			_cb1, cr1, 2, 5
#define hw__c16a_dir			_cb1, cr1, 1, 4
#define hw__c16a_cmsdir			_cb1, cr1, 3, 4		// Convenient
#define hw__c16a_opm			_cb1, cr1, 1, 3
#define hw__c16a_urs			_cb1, cr1, 1, 2
#define hw__c16a_udis			_cb1, cr1, 1, 1
#define hw__c16a_cen			_cb1, cr1, 1, 0

#define hw__c16a_ti1s			_cb1, cr2, 1, 7
#define hw__c16a_mms			_cb1, cr2, 3, 4
#define hw__c16a_ccds			_cb1, cr2, 1, 3

#define hw__c16a_etp			_cb1, smcr, 1, 15
#define hw__c16a_ece			_cb1, smcr, 1, 14
#define hw__c16a_etps			_cb1, smcr, 2, 12
#define hw__c16a_etf			_cb1, smcr, 4, 8
#define hw__c16a_msm			_cb1, smcr, 1, 7
#define hw__c16a_ts			_cb1, smcr, 3, 4
#define hw__c16a_sms			_cb1, smcr, 3, 0

#define hw__c16a_tde			_cb1, dier, 1, 14
#define hw__c16a_cc4de			_cb1, dier, 1, 12
#define hw__c16a_cc3de			_cb1, dier, 1, 11
#define hw__c16a_cc2de			_cb1, dier, 1, 10
#define hw__c16a_cc1de			_cb1, dier, 1, 9
#define hw__c16a_ude			_cb1, dier, 1, 8
#define hw__c16a_tie			_cb1, dier, 1, 6
#define hw__c16a_cc4ie			_cb1, dier, 1, 4
#define hw__c16a_cc3ie			_cb1, dier, 1, 3
#define hw__c16a_cc2ie			_cb1, dier, 1, 2
#define hw__c16a_cc1ie			_cb1, dier, 1, 1
#define hw__c16a_uie			_cb1, dier, 1, 0
#define hw__c16a_ie			_cb1, dier, 1, 0	// Convenient

#define hw__c16a_if			_cb1, sr, 1, 0

#define hw__c16a_cc4p			_cb1, ccer, 1, 13
#define hw__c16a_cc4e			_cb1, ccer, 1, 12
#define hw__c16a_cc3p			_cb1, ccer, 1,  9
#define hw__c16a_cc3e			_cb1, ccer, 1,  8
#define hw__c16a_cc2p			_cb1, ccer, 1,  5
#define hw__c16a_cc2e			_cb1, ccer, 1,  4
#define hw__c16a_cc1p			_cb1, ccer, 1,  1
#define hw__c16a_cc1e			_cb1, ccer, 1,  0

#define hw__c16a_oc2ce			_cb1, ccmr1, 1, 15
#define hw__c16a_oc2m			_cb1, ccmr1, 3, 12
#define hw__c16a_ic2f			_cb1, ccmr1, 4, 12
#define hw__c16a_oc2pe			_cb1, ccmr1, 1, 11
#define hw__c16a_oc2fe			_cb1, ccmr1, 1, 10
#define hw__c16a_ic2psc			_cb1, ccmr1, 2, 10
#define hw__c16a_cc2s			_cb1, ccmr1, 2,  8

#define hw__c16a_oc1ce			_cb1, ccmr1, 1,  7
#define hw__c16a_oc1m			_cb1, ccmr1, 3,  4
#define hw__c16a_ic1f			_cb1, ccmr1, 4,  4
#define hw__c16a_oc1pe			_cb1, ccmr1, 1,  3
#define hw__c16a_oc1fe			_cb1, ccmr1, 1,  2
#define hw__c16a_ic1psc			_cb1, ccmr1, 2,  2
#define hw__c16a_cc1s			_cb1, ccmr1, 2,  0

#define hw__c16a_oc4ce			_cb1, ccmr2, 1, 15
#define hw__c16a_oc4m			_cb1, ccmr2, 3, 12
#define hw__c16a_ic4f			_cb1, ccmr2, 4, 12
#define hw__c16a_oc4pe			_cb1, ccmr2, 1, 11
#define hw__c16a_oc4fe			_cb1, ccmr2, 1, 10
#define hw__c16a_ic4psc			_cb1, ccmr2, 2, 10
#define hw__c16a_cc4s			_cb1, ccmr2, 2,  8

#define hw__c16a_oc3ce			_cb1, ccmr2, 1,  7
#define hw__c16a_oc3m			_cb1, ccmr2, 3,  4
#define hw__c16a_ic3f			_cb1, ccmr2, 4,  4
#define hw__c16a_oc3pe			_cb1, ccmr2, 1,  3
#define hw__c16a_oc3fe			_cb1, ccmr2, 1,  2
#define hw__c16a_ic3psc			_cb1, ccmr2, 2,  2
#define hw__c16a_cc3s			_cb1, ccmr2, 2,  0

  
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
} hwa_c16a_t ;

#endif
