
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/**
 * @page atmelavr_psca
 * @section atmelavr_psca_reset Resetting the prescaler
 *
 * @code
 * hw_clear( hw_psc0 );
 * @endcode
 */
#define _hw_mthd_hw_clear__psca		, _hw_psca_clear

#define _hw_psca_clear(o,i,a,...)	HW_TX(_hw_clrpsca(o),__VA_ARGS__)

#define _hw_clrpsca(o)			_hw_write_reg(o,psr,1)


/**
 * @page atmelavr_psca
 *
 * @code
 * hw_reset( hw_psc0 );
 * @endcode
 */
#define _hw_mthd_hw_reset__psca		, _hw_psca_clear



/**
 * @page atmelavr_psca
 * @section atmelavr_psca_freeze Freezing the prescaler
 *
 * Halt and reset the prescaler (and the counters connected to it) by turning it
 * off. The prescaler starts counting again after it has been turned on.
 *
 * @code
 * hw_turn( hw_psc0, off );  //  Reset and halt the prescaler
 * hw_turn( hw_psc0, on );   //  Release the prescaler
 * @endcode
 */
#define _hw_mthd_hw_turn__psca		, _hw_psca_turn
#define _hw_psca_turn(o,i,a,v,...)	HW_TX(HW_G2(_hw_turnpsca,	\
						    HW_IS(,_hw_state_##v))(o,v), \
					      __VA_ARGS__)

#define _hw_turnpsca_0(o,v)		HW_ERR("expected `on` or `off` but not `"#v"`.")
#define _hw_turnpsca_1(o,v)		HW_G2(_hw_turnpsca_1,HW_A1(_hw_state_##v))(o)
#define _hw_turnpsca_1_0(o)		_hw_write_reg(o,cr,		\
						      (1U<<_hw_rbp(o,tsm))| \
						      (1U<<_hw_rbp(o,psr)))
#define _hw_turnpsca_1_1(o)		_hw_write_reg(o,tsm,0)
