
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @page atmelavr_psca
 * @section atmelavr_psca_reset Reset
 *
 * The hw_reset() instruction resets the prescaler immediately without stopping
 * it:
 *
 * @code
 * hw_reset( hw_psc0 );
 * @endcode
 */
#define _hw_mthd_hw_reset__psca		, _hw_psca_reset

#define _hw_psca_reset(o,i,a,...)	HW_TX(_hw_resetpsca(o),__VA_ARGS__)

#define _hw_resetpsca(o)		_hw_write_reg(o,psr,1)


/**
 * @page atmelavr_psca
 * @section atmelavr_psca_stop Stop
 *
 * The hw_turn() instruction can reset and stop the prescaler:
 *
 * @code
 * hw_turn( hw_psc0, off );  //  Reset and halt the prescaler
 * @endcode
 *
 * or release it:
 *
 * @code
 * hw_turn( hw_psc0, on );   //  Release the prescaler
 * @endcode
 */
#define _hw_mthd_hw_turn__psca		, _hw_psca_turn
#define _hw_psca_turn(o,i,a,v,...)	HW_TX(HW_G2(_hw_turnpsca,	\
						    HW_IS(,_hw_state_##v))(o,v), \
					      __VA_ARGS__)

#define _hw_turnpsca_0(o,v)		HW_ERR("expected `on` or `off` but not `"#v"`.")
#define _hw_turnpsca_1(o,v)		HW_G2(_hw_turnpsca_1,HW_A1(_hw_state_##v))(o)

/*  Stopping the prescaler requires setting its `tsm` and `psr` bits to 1
 */
#define _hw_turnpsca_1_0(o)		_hw_write_reg(o,tsmpsr,3)

/*  Releasing the prescaler requires setting its `tsm` bit to 0
 */
#define _hw_turnpsca_1_1(o)		_hw_write_reg(o,tsm,0)


/**
 * @page atmelavr_psca
 * @section atmelavr_psca_acfg Configuration
 *
 * `_psca` class prescalers are all clocked by the system clock.
 *
 * @code
 * hwa_config( NAME,
 *
 *             clock,   system );
 * @endcode
 */
#define _hw_mthd_hwa_configure__psca		, _hwa_cfpsca

/*  Mandatory argument `clock`
 */
#define _hwa_cfpsca(o,i,a, ...)						\
  do { HW_G2(_hwa_cfpsca_kclock,HW_IS(clock,__VA_ARGS__))(o,__VA_ARGS__,,) } while(0)

#define _hw_is_clock_clock		, 1

#define _hwa_cfpsca_kclock_0(o,k,...)		\
  HW_ERR("expected `clock` instead of `" #k "`.");

#define _hwa_cfpsca_kclock_1(o,k,v,...)					\
  HW_G2(_hwa_cfpsca_vclock,HW_IS(,_hw_psca_clock_##v))(o,v,__VA_ARGS__)

#define _hw_psca_clock_system			, 0

#define _hwa_cfpsca_vclock_0(o,v,...)					\
  HW_ERR( "`clock` can only be `system`, not `" #v "`.");

#define _hwa_cfpsca_vclock_1(o,v,...)					\
  HW_EOL(__VA_ARGS__)
