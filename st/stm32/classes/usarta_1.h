
/* This file is part of the HWA project.
 * Copyright (c) 2019 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Universal synchronous asynchronous receiver transmitter (USART)
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_usarta Class _usarta: Universal Synchronous Asynchronous Receiver Transmitter
 *
 * `_usarta` objects are universal synchronous asynchronous receivers transmitters.
 *
 * `_usarta` objects support several modes:
 *   * asynchronous
 *   * synchronous
 *   * smartcard 
 *   * singlewire
 *   * irda
 *   * lin
 */
#define hw_class__usarta

/*  Hardware registers							// Reset value
 */
#define hw__usarta_sr			_r32, 0x00, 0x00000360, 0	// 0x00C0
#define hw__usarta_dr			_r32, 0x04, 0x0000001F, 0	// X
#define hw__usarta_brr			_r32, 0x08, 0x0000FFFF, 0	// 0
#define hw__usarta_cr1			_r32, 0x0C, 0x000003FF, 0	// 0
#define hw__usarta_cr2			_r32, 0x10, 0x00007F6F, 0	// 0
#define hw__usarta_cr3			_r32, 0x14, 0x000007FF, 0	// 0
#define hw__usarta_gtpr			_r32, 0x18, 0x0000FFFF, 0	// 0

/*  Logical registers
 */
#define hw__usarta_reg_cts		_cb1, sr, 1, 9
#define hw__usarta_lbd			_cb1, sr, 1, 8
#define hw__usarta_txe			_cb1, sr, 1, 7
#define hw__usarta_tc			_cb1, sr, 1, 6
#define hw__usarta_rxne			_cb1, sr, 1, 5
#define hw__usarta_idle			_cb1, sr, 1, 4
#define hw__usarta_ore			_cb1, sr, 1, 3
#define hw__usarta_ne			_cb1, sr, 1, 2
#define hw__usarta_fe			_cb1, sr, 1, 1
#define hw__usarta_pe			_cb1, sr, 1, 0

#define hw__usarta_divmantissa		_cb1, brr, 12, 4
#define hw__usarta_divfraction		_cb1, brr,  4, 0

#define hw__usarta_ue			_cb1, cr1, 1, 13
#define hw__usarta_m			_cb1, cr1, 1, 12
#define hw__usarta_wake			_cb1, cr1, 1, 11
#define hw__usarta_pce			_cb1, cr1, 1, 10
#define hw__usarta_ps			_cb1, cr1, 1,  9
#define hw__usarta_peie			_cb1, cr1, 1,  8
#define hw__usarta_txeie		_cb1, cr1, 1,  7
#define hw__usarta_tcie			_cb1, cr1, 1,  6
#define hw__usarta_rxneie		_cb1, cr1, 1,  5
#define hw__usarta_idleie		_cb1, cr1, 1,  4
#define hw__usarta_te			_cb1, cr1, 1,  3
#define hw__usarta_re			_cb1, cr1, 1,  2
#define hw__usarta_rwu			_cb1, cr1, 1,  1
#define hw__usarta_sbk			_cb1, cr1, 1,  0

#define hw__usarta_linen		_cb1, cr2, 1, 14
#define hw__usarta_stop			_cb1, cr2, 2, 12
#define hw__usarta_clken		_cb1, cr2, 1, 11
#define hw__usarta_cpol			_cb1, cr2, 1, 10
#define hw__usarta_cpha			_cb1, cr2, 1,  9
#define hw__usarta_lbcl			_cb1, cr2, 1,  8
#define hw__usarta_lbdie		_cb1, cr2, 1,  6
#define hw__usarta_lbdl			_cb1, cr2, 1,  5
#define hw__usarta_add			_cb1, cr2, 4,  0

#define hw__usarta_ctsie		_cb1, cr3, 1, 10
#define hw__usarta_ctse			_cb1, cr3, 1,  9
#define hw__usarta_rtse			_cb1, cr3, 1,  8
#define hw__usarta_dmat			_cb1, cr3, 1,  7
#define hw__usarta_dmar			_cb1, cr3, 1,  6
#define hw__usarta_scen			_cb1, cr3, 1,  5
#define hw__usarta_nack			_cb1, cr3, 1,  4
#define hw__usarta_hdsel		_cb1, cr3, 1,  3
#define hw__usarta_irlp			_cb1, cr3, 1,  2
#define hw__usarta_iren			_cb1, cr3, 1,  1
#define hw__usarta_eie			_cb1, cr3, 1,  0

#define hw__usarta_gt			_cb1, gtpr, 8, 8
#define hw__usarta_psc			_cb1, gtpr, 8, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t brr ;
  hwa_r32_t cr1 ;
  hwa_r32_t cr2 ;
  hwa_r32_t cr3 ;
  hwa_r32_t gtpr ;
} hwa_usarta_t ;

#endif
