
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

/**
 * @page stm32_stka Class _stka: SysTick timer (STK)
 */
#define _hw_class__stka

#define _hw_reg__stka_ctrl		_r32, 0x00, 0x00010007, 0
#define _hw_reg__stka_load		_r32, 0x04, 0x00FFFFFF, 0
#define _hw_reg__stka_val		_r32, 0x08, 0x00FFFFFF, 0
#define _hw_reg__stka_calib		_r32, 0x0C, 0x00000000, 0

#define _hw_reg__stka_countflag		_cb1, ctrl, 1, 16
#define _hw_reg__stka_if		_cb1, ctrl, 1, 16	// Convenient
#define _hw_reg__stka_clksource		_cb1, ctrl, 1, 2
#define _hw_reg__stka_tickint		_cb1, ctrl, 1, 1
#define _hw_reg__stka_ie		_cb1, ctrl, 1, 1	// Convenient
#define _hw_reg__stka_enable		_cb1, ctrl, 1, 0
#define _hw_reg__stka_reload		_cb1, load, 24, 0
#define _hw_reg__stka_current		_cb1, val,  24, 0
#define _hw_reg__stka_noref		_cb1, calib, 1, 31
#define _hw_reg__stka_skew		_cb1, calib, 1, 30
#define _hw_reg__stka_tenms		_cb1, calib, 24, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t ctrl ;
  hwa_r32_t load ;
  hwa_r32_t val ;
} hwa_stka_t ;

#endif
