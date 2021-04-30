
/* This file is part of the HWA project.
 * Copyright (c) 2021 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal synchronous asynchronous receiver transmitter (USART)
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_sab Class _sab: Universal Synchronous Asynchronous Receiver Transmitter
 *
 * @section stm32_sabrl Relatives
 *
 * * @ref hwa_reg "Registers"
 *   * Hardware registers: `sr`, `dr`, `brr`, `cr1`, `cr2`, `cr3`, `gtpr`
 *   * Logical registers: `over8`, `ue`, `m`, `wake`, `pce`, `ps`, `peie`,
 *     `txeie`, `tcie`, `rxneie`, `idleie`, `te`, `re`, `rwu`, `sbk`, `linen`,
 *     `stop`, `clken`, `cpol`, `cpha`, `lbcl`, `lbdie`, `lbdl`, `add`,
 *     `onebit`, `ctsie`, `ctse`, `rtse`, `dmat`, `dmar`, `scen`, `nack`,
 *     `hdsel`, `irlp`, `iren`, `eie`, `gt`, `psc`
 * * @ref hwa_irq "Interrupts"
 */
#define hw_class__sab

/*  Differences with STM32F103:
 *    cr1: over8
 *    cr3: onebit
 */

/*  Hardware registers							// Reset value
 */
#define hw__sab_sr			_r32, 0x00, 0x00000360, 0	// 0x00C0
#define hw__sab_dr			_r32, 0x04, 0x000001FF, 0	// X
#define hw__sab_brr			_r32, 0x08, 0x0000FFFF, 0	// 0
#define hw__sab_cr1			_r32, 0x0C, 0x0000BFFF, 0	// 0
#define hw__sab_cr2			_r32, 0x10, 0x00007F6F, 0	// 0
#define hw__sab_cr3			_r32, 0x14, 0x00000FFF, 0	// 0
#define hw__sab_gtpr			_r32, 0x18, 0x0000FFFF, 0	// 0

/*  Logical registers
 */
#define hw__sab_cts			_cb1, sr, 1, 9
#define hw__sab_lbd			_cb1, sr, 1, 8
#define hw__sab_txe			_cb1, sr, 1, 7
#define hw__sab_tc			_cb1, sr, 1, 6
#define hw__sab_rxne			_cb1, sr, 1, 5
#define hw__sab_idle			_cb1, sr, 1, 4
#define hw__sab_ore			_cb1, sr, 1, 3
#define hw__sab_ne			_cb1, sr, 1, 2
#define hw__sab_fe			_cb1, sr, 1, 1
#define hw__sab_pe			_cb1, sr, 1, 0

#define hw__sab_divmantissa		_cb1, brr, 12, 4
#define hw__sab_divfraction		_cb1, brr,  4, 0

#define hw__sab_over8			_cb1, cr1, 1, 15
#define hw__sab_ue			_cb1, cr1, 1, 13
#define hw__sab_m			_cb1, cr1, 1, 12
#define hw__sab_wake			_cb1, cr1, 1, 11
#define hw__sab_pce			_cb1, cr1, 1, 10
#define hw__sab_ps			_cb1, cr1, 1,  9
#define hw__sab_pceps			_cb1, cr1, 2,  9	/* convenient */
#define hw__sab_peie			_cb1, cr1, 1,  8
#define hw__sab_txeie			_cb1, cr1, 1,  7
#define hw__sab_tcie			_cb1, cr1, 1,  6
#define hw__sab_rxneie			_cb1, cr1, 1,  5
#define hw__sab_idleie			_cb1, cr1, 1,  4
#define hw__sab_te			_cb1, cr1, 1,  3
#define hw__sab_re			_cb1, cr1, 1,  2
#define hw__sab_rwu			_cb1, cr1, 1,  1
#define hw__sab_sbk			_cb1, cr1, 1,  0

#define hw__sab_linen			_cb1, cr2, 1, 14
#define hw__sab_stop			_cb1, cr2, 2, 12
#define hw__sab_clken			_cb1, cr2, 1, 11
#define hw__sab_cpol			_cb1, cr2, 1, 10
#define hw__sab_cpha			_cb1, cr2, 1,  9
#define hw__sab_lbcl			_cb1, cr2, 1,  8
#define hw__sab_lbdie			_cb1, cr2, 1,  6
#define hw__sab_lbdl			_cb1, cr2, 1,  5
#define hw__sab_add			_cb1, cr2, 4,  0

#define hw__sab_onebit			_cb1, cr3, 1, 11
#define hw__sab_ctsie			_cb1, cr3, 1, 10
#define hw__sab_ctse			_cb1, cr3, 1,  9
#define hw__sab_rtse			_cb1, cr3, 1,  8
#define hw__sab_dmat			_cb1, cr3, 1,  7
#define hw__sab_dmar			_cb1, cr3, 1,  6
#define hw__sab_scen			_cb1, cr3, 1,  5
#define hw__sab_nack			_cb1, cr3, 1,  4
#define hw__sab_hdsel			_cb1, cr3, 1,  3
#define hw__sab_irlp			_cb1, cr3, 1,  2
#define hw__sab_iren			_cb1, cr3, 1,  1
#define hw__sab_eie			_cb1, cr3, 1,  0

#define hw__sab_gt			_cb1, gtpr, 8, 8
#define hw__sab_psc			_cb1, gtpr, 8, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t brr ;
  hwa_r32_t cr1 ;
  hwa_r32_t cr2 ;
  hwa_r32_t cr3 ;
  hwa_r32_t gtpr ;
} hwa_sab_t ;

#endif
