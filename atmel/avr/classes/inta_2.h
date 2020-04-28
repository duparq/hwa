
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief External interrupt controller
 */

/**
 * @page atmelavr_inta
 * @section atmelavr_inta_cf Configuration
 *
 * @code
 * hw( configure, int0,
 *
 *	      //  What does trigger the IRQ
 *	      //
 *	      sense,   low_level
 *		     | edge
 *		     | falling_edge
 *		     | rising_edge  );
 * @endcode
 */
#define hw_configure__inta		, _hw_cfinta
#define _hw_cfinta( o,a, ...)		_hwx_cfinta(_hw,o,__VA_ARGS__,)


/**
 * @page atmelavr_inta
 *
 * @code
 * hwa( configure, int0,
 *
 *	       //  What does trigger the IRQ
 *	       //
 *	       sense,	low_level
 *		      | edge
 *		      | falling_edge
 *		      | rising_edge  );
 * @endcode
 */
#define hwa_configure__inta		, _hwa_cfinta
#define _hwa_cfinta( o,a, ...)	_hwx_cfinta(_hwa,o,__VA_ARGS__,)


/*	Mandatory argument `sense`
 */
#define _hwx_cfinta(x,o,k,...)					\
  HW_Y(_hwx_cfinta_ksense_,_hw_is_sense_##k)(x,o,k,__VA_ARGS__)

#define _hwx_cfinta_ksense_0(x,o,k,...)			\
  HW_E_VL(k,sense)

#define _hwx_cfinta_ksense_1(x,o,k,v,...)				\
  HW_Y(_hwx_cfinta_vsense_,_hw_inta_sense_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfinta_vsense_0(x,o,v,...)					\
  HW_E_AVL(sense, v, low_level | edge | falling_edge | rising_edge)

#define _hwx_cfinta_vsense_1(x,o,v,...)				\
   x##_write(o,sc,HW_A1(_hw_inta_sense_##v)) HW_EOL(__VA_ARGS__)

#define _hw_inta_sense_low_level	, 0
#define _hw_inta_sense_edge		, 1
#define _hw_inta_sense_falling_edge	, 2
#define _hw_inta_sense_rising_edge	, 3


/**
 * @page atmelavr_inta
 * @section atmelavr_inta_stat Status
 *
 * The IRQ mask and flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, irqflag( int0 ) ) ) {	   // Read IRQ flag
 *   hw( clear, irqflag( int0 ) );		   // Clear IRQ flag
 *   hw( turn, irq(int0), off );	   // Disable IRQ
 * }
 * @endcode
 */


/**
 * @page atmelavr_inta
 * @section atmelavr_inta_internals Internals
 *
 * Class `_inta` objects hold the following hardware registers:
 *
 *  * `sc`: sense control
 *  * `ie`: IRQ mask
 *  * `if`: IRQ flag
 *
 * These registers are accessible through the @ref public_ins
 * "register access intructions".
 */


/**
 * @page atmelavr_inta
 * <br>
 */
