
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

/**
 * @ingroup stm32_classes
 * @defgroup stm32_stka Class _stka: SysTick timer (STK)
 *
 * @section stm32_stkarel Relatives
 *
 * * @ref hwa_irq "Interrupts"
 *   * `(systick,irq)`
 *
 * * @ref hwa_reg "Registers"
 *   * `(systick,tenms)`
 *   * `(systick,onems)`
 *
 * According to PM0056, the `_stka` class SysTick timer has a `tenms` logical
 * register that holds the factory calibration value for a 10 ms period.
 *
 * In fact, for the STM32F103, the value of `tenms` is 9000. Then, the
 * calibration value minus 1 gives a 1 ms period (yes, ONE ms) when the SysTick
 * is clocked at 9 MHz (72 MHz / 8).
 *
 * For that reason, HWA also provides a `onems` logical register that is the
 * same as `tenms` but maybe less confusing.
 *
 * @code
 * //  1 ms period when AHB is clocked at 9 MHz
 * //
 * hw( configure, systick,
 *     clock,	  ahb,
 *     reload,	  (hw(read, (systick,onems)) - 1) & 0xFFFFFF,
 *     run,	  yes );
 * @endcode
 */
#define hw_class__stka

#define hw__stka_ctrl			_r32, 0x00, 0x00010007, 0
#define hw__stka_load			_r32, 0x04, 0x00FFFFFF, 0
#define hw__stka_val			_r32, 0x08, 0x00FFFFFF, 0
#define hw__stka_calib			_r32, 0x0C, 0x00000000, 0

#define hw__stka_countflag		_cb1, ctrl, 1, 16
#define hw__stka_if			_cb1, ctrl, 1, 16	// Convenient
#define hw__stka_clksource		_cb1, ctrl, 1, 2
#define hw__stka_tickint		_cb1, ctrl, 1, 1
#define hw__stka_ie			_cb1, ctrl, 1, 1	// Convenient
#define hw__stka_enable			_cb1, ctrl, 1, 0
#define hw__stka_reload			_cb1, load, 24, 0
#define hw__stka_current		_cb1, val,  24, 0
#define hw__stka_noref			_cb1, calib, 1, 31
#define hw__stka_skew			_cb1, calib, 1, 30
#define hw__stka_tenms			_cb1, calib, 24, 0
#define hw__stka_onems			_cb1, calib, 24, 0	// PM0056 fix

#define hw__stka_irq			_irq, ie, if, 0		// Clear flag writing 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t ctrl ;
  hwa_r32_t load ;
  hwa_r32_t val ;
} hwa_stka_t ;

#endif
