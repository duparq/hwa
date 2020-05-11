
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Counter prescaler
 */

/**
 * @page atmelavr_psa
 * @section atmelavr_psa_act Actions
 *
 * <br>
 * `reset`:
 *
 * The `reset` action resets the prescaler immediately without stopping
 * it:
 *
 * @code
 * hw( reset, prescaler0 );
 * @endcode
 */
#define hw_reset__psa			, _hw_psa_reset

#define _hw_psa_reset(o,a,...)	_hw_resetpsa(o) HW_EOL(__VA_ARGS__)

#define _hw_resetpsa(o)		_hw_write(o,psr,1)


/**
 * @page atmelavr_psa
 * @section atmelavr_psa_stop Stop
 *
 * The `turn` action can reset and stop the prescaler:
 *
 * @code
 * hw( turn, prescaler0, off );	//  Reset and halt the prescaler
 * @endcode
 *
 * or release it:
 *
 * @code
 * hw( turn, prescaler0, on );	//  Release the prescaler
 * @endcode
 */
#define hw_turn__psa			, _hw_psa_turn
#define _hw_psa_turn(o,a,v,...)			\
  HW_G2(_hw_turnpsa, HW_IS(,_hw_state_##v))(o,v)	\
  HW_EOL(__VA_ARGS__)

#define _hw_turnpsa_0(o,v)		HW_E_VL(v, on | off)
#define _hw_turnpsa_1(o,v)		HW_G2(_hw_turnpsa_1,HW_A1(_hw_state_##v))(o)

/*  Stopping the prescaler requires setting its `tsm` and `psr` bits to 1
 */
#define _hw_turnpsa_1_0(o)		_hw_write(o,tsmpsr,3)

/*  Releasing the prescaler requires setting its `tsm` bit to 0
 */
#define _hw_turnpsa_1_1(o)		_hw_write(o,tsm,0)


/**
 * @page atmelavr_psa
 * @section atmelavr_psa_acfg Configuration
 *
 * `_psa` class prescalers are all clocked by the I/O clock.
 *
 * @code
 * hwa( configure, prescaler0,
 *	clock,	   ioclk       );
 * @endcode
 */
#define hwa_configure__psa		, _hwa_cfpsa

/*  Mandatory argument `clock`
 */
#define _hwa_cfpsa(o,a,k,...)					\
  do { HW_Y(_hwa_cfpsa_kclock_,_hw_is_clock_##k)(o,k,__VA_ARGS__,,) } while(0)

#define _hwa_cfpsa_kclock_0(o,k,...)		HW_E_VL(k,clock)

#define _hwa_cfpsa_kclock_1(o,k,v,...)					\
  HW_Y(_hwa_cfpsa_vclock_,_hw_psa_clock_##v)(o,v,__VA_ARGS__)

#define _hw_psa_clock_ioclk		, 0

#define _hwa_cfpsa_vclock_0(o,v,...)					\
  HW_E_AVL(`clock`, v, `ioclk`)

#define _hwa_cfpsa_vclock_1(o,v,...)					\
  HW_EOL(__VA_ARGS__)
