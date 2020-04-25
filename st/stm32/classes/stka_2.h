
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief SysTick timer
 */

#define hw_class__stka

/* #define hw__stka_irq			_irq, systick, x15, ie, if */
/* #define hw__stka_flag			_cb1, ctrl, 1, 16 */

/**
 * @page stm32_stka
 * __Actions__
 *
 * `configure`:
 * @code
 * hw | hwa ( configure,   systick,
 *
 *          [ clock,       ahb             // Clock source
 *                       | ahb/8 ],
 *
 *          [ reload,      x, ]            // Any value in 0..0xFFFFFF
 *
 *          [ run,         yes | no ] );   
 * @endcode
 */
#define hw_configure__stka		, _hw_cfstka
#define hwa_configure__stka		, _hwa_cfstka

#define _hw_cfstka_clk_ahb		, 17

#define _hw_cfstka(o,a,k,...)		do{ HW_Y(_hwx_cfstka_k_,k)(_hw,o,k,__VA_ARGS__) }while(0)
#define _hwa_cfstka(o,a,k,...)	do{ HW_Y(_hwx_cfstka_k_,k)(_hwa,o,k,__VA_ARGS__) }while(0)

/*  At least one keyword
 */
#define _hwx_cfstka_k_1(h,o,k,...)	HW_E_ML((clock,reload))
#define _hwx_cfstka_k_0(h,o,k,...)	HW_Y(_hwx_cfstka_kclk_,_hw_is_clock_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `clock`
 */
#define _hwx_cfstka_kclk_1(h,o,k,v,...)	HW_Y(_hwx_cfstka_vclk_,_hw_cfstka_clk_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfstka_vclk_0(h,o,v,...)	HW_E_NIL(v,(ahb, ahb/8))
#define _hwx_cfstka_vclk_1(h,o,v,...)	_hwx_cfstka_vclk_2(h,o,v,_hw_cfstka_clk_##v,__VA_ARGS__)
#define _hwx_cfstka_vclk_2(...)		_hwx_cfstka_vclk_3(__VA_ARGS__)
#define _hwx_cfstka_vclk_3(h,o,v,z,xv,k,...)				\
  if      ( 8*xv == 17 ) h##_write(o,clksource,0);			\
  else if (   xv == 17 ) h##_write(o,clksource,1);			\
  else HWA_E_NIL(v,(ahb/8, ahb));					\
  HW_Y(_hwx_cfstka_krld_,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfstka_kclk_0(h,o,k,...)	HW_Y(_hwx_cfstka_krld_,_hw_is_reload_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `reload`
 */
#define _hwx_cfstka_krld_1(h,o,k0,v,k,...)			\
  h##_write(o,reload,(uint32_t)(v));			\
  HW_Y(_hwx_cfstka_krn_,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

#define _hwx_cfstka_krld_0(h,o,k,...)	HW_Y(_hwx_cfstka_krn_,_hw_is_run_##k)(h,o,k,__VA_ARGS__)

/*  Optionnal parameter `enabled`
 */
#define _hwx_cfstka_krn_0(h,o,k,...)	HW_EOL(k)
#define _hwx_cfstka_krn_1(h,o,k,v,...)	HW_Y(_hwx_cfstka_vrn_,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_cfstka_vrn_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_cfstka_vrn_1(h,o,v,g,...)				\
  h##_write(o,enable,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * @page stm32_stka
 * <br>
 * `turn`:
 * @code
 * hw | hwa ( turn, systick, on | off );
 * @endcode
 */
#define hw_turn__stka			, _hw_tnstka
#define _hw_tnstka(o,a,...)		do{ _hwx_tnstka(_hw,o,__VA_ARGS__) }while(0)

#define hwa_turn__stka			, _hwa_tnstka
#define _hwa_tnstka(o,a,...)		do{ _hwx_tnstka(_hwa,o,__VA_ARGS__) }while(0)

#define _hwx_tnstka(h,o,v,...)		HW_Y(_hwx_tnstka_,_hw_state_##v)(h,o,v,__VA_ARGS__)
#define _hwx_tnstka_0(h,o,v,...)	HW_E_ST(v)
#define _hwx_tnstka_1(h,o,v,g,...)	h##_write(o,enable,HW_A1(_hw_state_##v)); HW_EOL(g)


/**
 * @page stm32_stka
 * <br>
 * `read:`
 * @code
 * uint32_t v = hw( read, systick );       // Returns the current value of the timer
 * @endcode
 */
#define hw_read__stka			, _hw_rdstka
#define _hw_rdstka(o,a,...)		_hw_read(o,current)


/**
 * @page stm32_stka
 * <br>
 * __IRQ__
 * @code
 * hw | hwa ( turn, irq(systick), on | off );
 * @endcode
 *
 * @code
 * hw | hwa ( turn, (systick,irq), on | off );
 * @endcode
 *
 * @code
 * if ( hw(read, irqflag(systick)) )       // Reading the flag clears it
 *   hw(toggle,LED);
 * @endcode
 */


/**
 * @page stm32_stka
 * <br>
 * __Registers__
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
 *     clock,     ahb,
 *     reload,    (hw(read, (systick,onems)) - 1) & 0xFFFFFF,
 *     run,       yes );
 * @endcode
 */



/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__stka(o,a)			\
  _hwa_setup_r( o, ctrl );			\
  _hwa_setup_r( o, load );			\
  _hwa_setup_r( o, val  )

#define _hwa_init__stka(o,a)			\
  _hwa_init_r( o, ctrl, 0x00000000 );		\
  _hwa_init_r( o, load, 0x00000000 );		\
  _hwa_init_r( o, val,  0x00000000 )

#define _hwa_commit__stka(o,a)		\
  _hwa_commit_r( o, ctrl );			\
  _hwa_commit_r( o, load );			\
  _hwa_commit_r( o, val  )
