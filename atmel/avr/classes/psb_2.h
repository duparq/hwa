
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @addtogroup atmelavr_psb
 * @section atmelavr_psb_act Actions
 *
 * <br>
 * `configure`:
 *
 * @code
 * hwa( configure, prescaler0,
 *
 *	clock,	 ioclk
 *	       | pll_32MHz
 *	       | pll_64MHz );
 * @endcode
 *
 * __Note 1__ `pll_32MHz` is not available when the PLL is used as system clock
 * (`HW_DEVICE_CLK_SRC` is "`rc_pll_16MHz`").
 *
 * __Note 2__ `pll_64MHz` is not available when supply voltage is below 2.7 V
 * (`HW_DEVICE_BODLEVEL` is "`1700_2000mV`").
 *
 * __Note 3__ It is highly recommended that the counter is stopped whenever the
 * prescaler clock is switched between "`pll_32MHz`" and "`pll_64MHz`".
 *
 * __Note 4__ Turning the PLL on requires a special procedure that taked about
 * 100 µs to execute.
 *
 * __Note 5__ The PLL is never stopped once it has been turned on.
 */
#define hwa_configure__psb		, _hwa_cfpsb

/*  Mandatory argument `clock`
 *
 *    A second void argument is added to the end of the list so that there are
 *    always at least 2 arguments following the last non-void argument.
 *
 *    The `clock` value is stored in the `config` part of the context. The
 *    `commit` function handles the hardware configuration.
 */
#define _hwa_cfpsb(o,a,k,...)					\
  do { HW_B(_hwa_cfpsb_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,) } while(0)

#define _hwa_cfpsb_kclock_0(o,k,...)	HW_E(HW_EM_AN(k,clock))
#define _hwa_cfpsb_kclock_1(o,k,v,...)	HW_B(_hwa_cfpsb_vclock_,_hw_psb_clock_##v)(o,v,__VA_ARGS__)

#define _hw_psb_clock_ioclk		, 0
#define _hw_psb_clock_pll_32MHz		, 1
#define _hw_psb_clock_pll_64MHz		, 2

#define _hwa_cfpsb_vclock_0(o,v,...)	HW_E(HW_EM_VAL(v,clock,(ioclk,pll_32MHz,pll_64MHz)))

#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_cfpsb_vclock_1(o,v,...)					\
  if ( HW_A1(_hw_psb_clock_##v) == HW_A1(_hw_psb_clock_pll_32MHz) )	\
    HWA_E(HW_EM_VAL(v,clock,(ioclk, pll_64MHz)));			\
  _hwa_write( o, pcke, HW_A1(_hw_psb_clock_##v) != HW_A1(_hw_psb_clock_ioclk) ); \
  HW_EOL(__VA_ARGS__)
#else
#  define _hwa_cfpsb_vclock_1(o,v,...)					\
  if ( HW_DEVICE_BODLEVEL==6 && HW_A1(_hw_psb_clock_##v)==HW_A1(_hw_psb_clock_pll_64MHz) ) \
    HWA_E(HW_EM_VAL(v,clock,(ioclk, pll_32MHz)));			\
  if ( HW_A1(_hw_psb_clock_##v) == HW_A1(_hw_psb_clock_pll_32MHz) )	\
    _hwa_write(o,lsm,1);						\
  else if ( HW_A1(_hw_psb_clock_##v) == HW_A1(_hw_psb_clock_pll_64MHz) ) \
    _hwa_write(o,lsm,0);						\
  hwa->o.config.clock = HW_A1(_hw_psb_clock_##v);			\
  HW_EOL(__VA_ARGS__)
#endif


/**
 * @addtogroup atmelavr_psb
 * @section atmelavr_psb_reset Reset
 *
 * The `reset` action resets the prescaler immediately without stopping it:
 *
 * @code
 * hw( reset, prescaler0 );
 * @endcode
 */
#define hw_reset__psb			, _hw_psb_reset
#define _hw_psb_reset(o,a, ...)	_hw_write(o,psr,1)


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__psb(o,a)			\
  _hwa_setup_r( o, pllcsr );			\
  hwa->o.config.clock = 0xFF ;

#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_init__psb(o,a)		_hwa_init_r( o, pllcsr, 0x02 );
#else
#  define _hwa_init__psb(o,a)		_hwa_init_r( o, pllcsr, 0x00 );
#endif


#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_commit__psb(o,a)		_hwa_commit_r(o,pllcsr);
#else
#  define _hwa_commit__psb(o,a)					\
  if ( hwa->o.config.clock != 0xFF ) {					\
    if ( hwa->o.config.clock == HW_A1(_hw_psb_clock_ioclk) )		\
      _hwa_write( o, pcke, 0 );					\
    else if ( _hwa_ovalue( o, plle ) == 0 ) {				\
      /* PLL start procedure (once started, it is never stopped). */	\
      _hwa_write(o,plle,1);						\
      _hwa_commit_r(o,pllcsr);					\
      hw_waste_cycles(100e-6 * HW_SYSHZ);				\
      while( !_hw_read(o,plock) ) {}				\
      _hwa_write(o,pcke,1);						\
    }									\
  }									\
  _hwa_commit_r(o,pllcsr)
#endif
