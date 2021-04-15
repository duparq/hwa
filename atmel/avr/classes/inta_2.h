
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief External interrupt controller
 */

/**
 * @addtogroup atmelavr_inta
 * @section atmelavr_intaif Interface
 *
 * @act hw( configure, ... ) and hwa( configure, ... )
 *
 * @code
 * hw | hwa( configure,   int0,
 *
 *           sense,       low_level		//  What does trigger the IRQ
 *                      | edge
 *                      | falling_edge
 *                      | rising_edge  );
 * @endcode
 */
#define hw_configure__inta		, _hw_cfinta
#define _hw_cfinta( o,a, ...)		_hw_cfinta_(_hw,o,__VA_ARGS__,)

#define hwa_configure__inta		, _hwa_cfinta
#define _hwa_cfinta( o,a, ...)		_hw_cfinta_(_hwa,o,__VA_ARGS__,)


/*	Mandatory argument `sense`
 */
#define _hw_cfinta_(h,o,k,...)		HW_BW(_hw_cfinta1,sense,k)(h,o,k,__VA_ARGS__)
#define _hw_cfinta10(h,o,k,...)		HW_E(HW_EM_AN(k,sense))
#define _hw_cfinta11(h,o,k,v,...)	HW_BV(_hw_cfinta11,intasense_,v,o,h)(__VA_ARGS__) // PUSH
#define _hw_cfinta110(v,o,h)		HW_E(HW_EM_VAL(v,sense,(low_level,edge,falling_edge,rising_edge))) HW_EAT // POP
#define _hw_cfinta111(v,o,h)		h##_write(o,sc,v) HW_EOL // POP

#define _hw_intasense_low_level		, 0
#define _hw_intasense_edge		, 1
#define _hw_intasense_falling_edge	, 2
#define _hw_inta1sense_rising_edge	, 3


/**
 * @addtogroup atmelavr_inta
 * @section atmelavr_inta_stat Status
 *
 * The IRQ mask and flag can be accessed through interrupt-related instructions:
 *
 * @code
 * if ( hw( read, (int0,irq) ) ) {	   // Read IRQ flag
 *   hw( clear, (int0,irq) );		   // Clear IRQ flag
 *   hw( disable, (int0,irq) );	   // Disable IRQ
 * }
 * @endcode
 */


/**
 * @addtogroup atmelavr_inta
 * @section atmelavr_inta_internals Internals
 *
 * Class `_inta` objects hold the following hardware registers:
 *
 *  * `sc`: sense control
 *  * `ie`: IRQ mask
 *  * `if`: IRQ flag
 */
