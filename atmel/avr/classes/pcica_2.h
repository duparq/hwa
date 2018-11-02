
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Pin change interrupt controller
 */


/**
 * @page atmelavr_pcica
 * @section atmelavr_pcica_mon Monitored pins
 *
 * The `turn` action is used to change the pins of a I/O definition (that can be
 * a single or several pins) that a class `_pcica` object monitors:
 *
 * @code
 * hw( turn, pcic0, pa0, on | off );
 * @endcode
 */
#define _hw_mtd_hw_turn__pcica		, _hw_tnpcica
#define _hw_tnpcica( o,i,a, ...)	_hwx_tnpcica1(_hw,o,__VA_ARGS__,,)


/**
 * @page atmelavr_pcica
 * @code
 * hw( turn, pcic0, pa0, on | off );
 * @endcode
 */
#define _hw_mtd_hwa_turn__pcica		, _hwa_tnpcica
#define _hwa_tnpcica( o,i,a, ...)	_hwx_tnpcica1(_hwa,o,__VA_ARGS__,,)

/*	Verify that a I/O name is given
 */
#define _hwx_tnpcica1(x,o,io,...)	HW_G2(_hwx_tnpcica1,HW_IS(_io1a,_hw_def_##io))(x,o,io,__VA_ARGS__)
#define _hwx_tnpcica1_0(x,o,io,...)	HW_E(`io` is not an i/o pin)

/*	Verify that a state is given
 */
#define _hwx_tnpcica1_1(x,o,io,v,...)	HW_Y(_hwx_tnpcica2,_hw_state_##v)(x,o,io,v,__VA_ARGS__)

#define _hwx_tnpcica2_0(x,o,io,v,...)	HW_E_ST(v)
#define _hwx_tnpcica2_1(x,o,io,v,...)	_hwx_tnpcica2_2(x,o,_hw_def_##io,v) HW_EOL(__VA_ARGS__)
#define _hwx_tnpcica2_2(...)			_hwx_tnpcica2_3(__VA_ARGS__)
#define _hwx_tnpcica2_3(x,o,c,i,p,bn,bp,v)	x##_write_reg_m(o,msk,((1U<<bn)-1)<<bp,(((1U<<bn)-1)*HW_A1(_hw_state_##v))<<bp)


/**
 * @page atmelavr_pcica
 * @section atmelavr_pcica_stat Status
 *
 * The pin change IRQ flag and the enable bit can be accessed through
 * interrupt-related instructions:
 *
 * @code
 * if ( hw( read, HW_IRQFLAG( pcic0 ) ) ) {	     // Read pin change flag
 *   hw( clear, HW_IRQFLAG( pcic0 ) );	     // Clear pin change flag
 *   hw( turn, HW_IRQ( pcic0, off ) );	     // Disable pin change IRQ
 * }
 * @endcode
 */


/**
 * @page atmelavr_pcica
 * @section atmelavr_pcica_internals Internals
 *
 * Class `_pcica` objects hold the following hardware registers:
 *
 *  * `msk`: mask of monitored pins
 *
 * and the following logical registers:
 *
 *  * `ie`: pin change IRQ mask
 *  * `if`: pin change IRQ flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__pcica(o,i,a)	_hwa_setup_reg( o, msk )

#define _hwa_init__pcica(o,i,a)		_hwa_init_reg( o, msk, 0x00 )

#define _hwa_commit__pcica(o,i,a)	_hwa_commit_reg( o, msk )


/**
 * @page atmelavr_pcica
 * <br>
 */
