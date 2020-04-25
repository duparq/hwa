
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

#define hw_reg__c16a_cr1		_r32, 0x00, 0x000003FF, 0
#define hw_reg__c16a_cr2		_r32, 0x04, 0x000000F8, 0
#define hw_reg__c16a_smcr		_r32, 0x08, 0x0000FFF7, 0
#define hw_reg__c16a_dier		_r32, 0x0C, 0x00005F5F, 0
#define hw_reg__c16a_sr			_r32, 0x10, 0x00001E7F, 0
#define hw_reg__c16a_egr		_r32, 0x14, 0x0000005F, 0
#define hw_reg__c16a_ccmr1		_r32, 0x18, 0x0000FFFF, 0
#define hw_reg__c16a_ccmr2		_r32, 0x1C, 0x0000FFFF, 0
#define hw_reg__c16a_ccer		_r32, 0x20, 0x00003333, 0
#define hw_reg__c16a_cnt		_r32, 0x24, 0x0000FFFF, 0
#define hw_reg__c16a_psc		_r32, 0x28, 0x0000FFFF, 0
#define hw_reg__c16a_arr		_r32, 0x2C, 0x0000FFFF, 0
#define hw_reg__c16a_reload		_r32, 0x2C, 0x0000FFFF, 0	// Synonym
#define hw_reg__c16a_ccr1		_r32, 0x34, 0x0000FFFF, 0
#define hw_reg__c16a_ccr2		_r32, 0x38, 0x0000FFFF, 0
#define hw_reg__c16a_ccr3		_r32, 0x3C, 0x0000FFFF, 0
#define hw_reg__c16a_ccr4		_r32, 0x40, 0x0000FFFF, 0
#define hw_reg__c16a_dcr		_r32, 0x48, 0x00001F1F, 0
#define hw_reg__c16a_dmar		_r32, 0x4C, 0x0000FFFF, 0

#define hw_reg__c16a_ckd		_cb1, cr1, 2, 8
#define hw_reg__c16a_arpe		_cb1, cr1, 1, 7
#define hw_reg__c16a_cms		_cb1, cr1, 2, 5
#define hw_reg__c16a_dir		_cb1, cr1, 1, 4
#define hw_reg__c16a_opm		_cb1, cr1, 1, 3
#define hw_reg__c16a_urs		_cb1, cr1, 1, 2
#define hw_reg__c16a_udis		_cb1, cr1, 1, 1
#define hw_reg__c16a_cen		_cb1, cr1, 1, 0
#define hw_reg__c16a_enable		_cb1, cr1, 1, 0		// Synonym

#define hw_reg__c16a_ti1s		_cb1, cr2, 1, 7
#define hw_reg__c16a_mms		_cb1, cr2, 3, 4
#define hw_reg__c16a_ccds		_cb1, cr2, 1, 3

#define hw_reg__c16a_etp		_cb1, smcr, 1, 15
#define hw_reg__c16a_ece		_cb1, smcr, 1, 14
#define hw_reg__c16a_etps		_cb1, smcr, 2, 12
#define hw_reg__c16a_etf		_cb1, smcr, 4, 8
#define hw_reg__c16a_msm		_cb1, smcr, 1, 7
#define hw_reg__c16a_ts			_cb1, smcr, 3, 4
#define hw_reg__c16a_sms		_cb1, smcr, 3, 0

#define hw_reg__c16a_tde		_cb1, dier, 1, 14
#define hw_reg__c16a_cc4de		_cb1, dier, 1, 12
#define hw_reg__c16a_cc3de		_cb1, dier, 1, 11
#define hw_reg__c16a_cc2de		_cb1, dier, 1, 10
#define hw_reg__c16a_cc1de		_cb1, dier, 1, 9
#define hw_reg__c16a_ude		_cb1, dier, 1, 8
#define hw_reg__c16a_tie		_cb1, dier, 1, 6
#define hw_reg__c16a_cc4ie		_cb1, dier, 1, 4
#define hw_reg__c16a_cc3ie		_cb1, dier, 1, 3
#define hw_reg__c16a_cc2ie		_cb1, dier, 1, 2
#define hw_reg__c16a_cc1ie		_cb1, dier, 1, 1
#define hw_reg__c16a_uie		_cb1, dier, 1, 0
#define hw_reg__c16a_ie			_cb1, dier, 1, 0	// Convenient

#define hw_reg__c16a_if			_cb1, sr, 16, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t cr1 ;
  hwa_r32_t cr2 ;
  hwa_r32_t smcr ;
  hwa_r32_t dier ;
  hwa_r32_t sr ;
  hwa_r32_t egr ;
  hwa_r32_t cnt ;
  hwa_r32_t psc ;
  hwa_r32_t arr ;
} hwa_c16a_t ;

#endif
