
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @page atmelavr_pscb
 * @section atmelavr_pscb_acfg Configuration
 *
 * @code
 * hwa_config( NAME,
 *
 *             clock,   system
 *                    | pll_32MHz
 *                    | pll_64MHz );
 * @endcode
 *
 * __Note 1__: `pll_32MHz` is not available when the PLL is used as system clock
 * (`HW_DEVICE_CLK_SRC` is `rc_pll_16MHz`).
 *
 * __Note 2__: `pll_64MHz` is not available when supply voltage is below 2.7 V
 * (`HW_DEVICE_BODLEVEL` is `1700_2000mV`).
 *
 * __Note 3__: it is highly recommended that the counter is stopped whenever the
 * prescaler clock is switched between `pll_32MHz` and `pll_64MHz`.
 *
 * __Note 4__: turning the PLL on requires a special proc8adure that taked about
 * 100 µs to execute.
 *
 * __Note 5__: the PLL is never stopped once it has been turned on.
 */
#define _hw_mthd_hwa_config__pscb		, _hwa_cfpscb

/*  Mandatory argument `clock`
 *
 *    A second void argument is added to the end of the list so that there are
 *    always at least 2 arguments following the last non-void argument.
 *
 *    The `clock` value is stored in the `config` part of the context. The
 *    `commit` function handles the hardware configuration.
 */
#define _hwa_cfpscb(o,i,a, ...)						\
  do { HW_G2(_hwa_cfpscb_kclock,HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__,) } while(0)

#define _hw_is_clock_clock		, 1

#define _hwa_cfpscb_kclock_0(o,kw,...)		\
  HW_ERR("expected `clock` instead of `" #kw "`.");

#define _hwa_cfpscb_kclock_1(o,kw,v,...)					\
  HW_G2(_hwa_cfpscb_vclock,HW_IS(,_hw_pscb_clock_##v))(o,v,__VA_ARGS__)

#define _hw_pscb_clock_system			, 0
#define _hw_pscb_clock_pll_32MHz		, 1
#define _hw_pscb_clock_pll_64MHz		, 2

#define _hwa_cfpscb_vclock_0(o,v,...)					\
  HW_ERR( "`clock` can be `system`, `pll_32MHz`, or `pll_64MHz` "	\
	  "but not `" #v "`.");

#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_cfpscb_vclock_1(o,v,...)					\
  if ( HW_A1(_hw_pscb_clock_##v) == HW_A1(_hw_pscb_clock_pll_32MHz) )	\
    HWA_ERR( "`pll_32MHz` is not available when PLL is used as system clock." ); \
  _hwa_write_reg( o, pcke, HW_A1(_hw_pscb_clock_##v) != HW_A1(_hw_pscb_clock_system) ); \
  HW_EOL(__VA_ARGS__)
#else
#  define _hwa_cfpscb_vclock_1(o,v,...)					\
  if ( HW_DEVICE_BODLEVEL==6 && HW_A1(_hw_pscb_clock_##v)==HW_A1(_hw_pscb_clock_pll_64MHz) ) \
    HWA_ERR( "`pll_64MHz` is not available for suplly voltage < 2.7 V." ); \
  if ( HW_A1(_hw_pscb_clock_##v) == HW_A1(_hw_pscb_clock_pll_32MHz) )	\
    _hwa_write_reg(o,lsm,1);						\
  else if ( HW_A1(_hw_pscb_clock_##v) == HW_A1(_hw_pscb_clock_pll_64MHz) ) \
    _hwa_write_reg(o,lsm,0);						\
  hwa->o.config.clock = HW_A1(_hw_pscb_clock_##v);			\
  HW_EOL(__VA_ARGS__)
#endif


/**
 * @page atmelavr_pscb
 * @section atmelavr_pscb_reset Reset
 *
 * The hw_reset() instruction resets the prescaler immediately without stopping
 * it:
 *
 * @code
 * hw_reset( NAME );
 * @endcode
 */
#define _hw_mthd_hw_reset__pscb		, _hw_pscb_reset

#define _hw_pscb_reset(o,i,a, ...)	_hw_write_reg(o,psr,1)


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_create__pscb(o,i,a)			\
  _hwa_create_reg( o, pllcsr );			\
  hwa->o.config.clock = 0xFF ;

#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_init__pscb(o,i,a)		_hwa_init_reg( o, pllcsr, 0x02 );
#else
#  define _hwa_init__pscb(o,i,a)		_hwa_init_reg( o, pllcsr, 0x00 );
#endif


#if HW_IS(HW_DEVICE_CLK_SRC, rc_pll_16MHz)
#  define _hwa_commit__pscb(o,i,a)		_hwa_commit_reg(o,pllcsr);
#else
#  define _hwa_commit__pscb(o,i,a)					\
  if ( hwa->o.config.clock != 0xFF ) {					\
    if ( hwa->o.config.clock == HW_A1(_hw_pscb_clock_system) )		\
      _hwa_write_reg( o, pcke, 0 );					\
    else if ( _hwa_ovalue( o, plle ) == 0 ) {				\
      /* PLL start proc8adure (once started, it is never stopped). */	\
      _hwa_write_reg(o,plle,1);						\
      _hwa_commit_reg(o,pllcsr);					\
      hw_delay_cycles(100e-6 * hw_syshz);				\
      while( !_hw_read_reg(o,plock) ) {}				\
      _hwa_write_reg(o,pcke,1);						\
    }									\
  }									\
  _hwa_commit_reg(o,pllcsr)
#endif
