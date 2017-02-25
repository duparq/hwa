
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
 * hw_config( EI_NAME,
 *
 *            //  What does trigger the IRQ
 *            //
 *            sense,   low_level
 *                   | edge
 *                   | falling_edge
 *                   | rising_edge  );
 * @endcode
 */
#define _hw_mthd_hw_configure__inta	, _hw_cfinta
#define _hw_cfinta( o,i,a, ...)		_hwx_cfinta(_hw,o,__VA_ARGS__,)


/**
 * @page atmelavr_inta
 *
 * @code
 * hwa_config( EI_NAME,
 *
 *             //  What does trigger the IRQ
 *             //
 *             sense,   low_level
 *                    | edge
 *                    | falling_edge
 *                    | rising_edge  );
 * @endcode
 */
#define _hw_mthd_hwa_configure__inta	, _hwa_cfinta
#define _hwa_cfinta( o,i,a, ...)	_hwx_cfinta(_hwa,o,__VA_ARGS__,)


/*	Mandatory argument `sense`
 */
#define _hwx_cfinta(x,o,k,...)					\
  HW_GX(_hwx_cfinta_ksense,_hw_is_sense_##k)(x,o,k,__VA_ARGS__)

#define _hwx_cfinta_ksense_0(x,o,k,...)			\
  HW_E_VL(k,sense)

#define _hwx_cfinta_ksense_1(x,o,k,v,...)				\
  HW_GX(_hwx_cfinta_vsense,_hw_inta_sense_##v)(x,o,v,__VA_ARGS__)

#define _hwx_cfinta_vsense_0(x,o,v,...)					\
  HW_E_AVL(sense, v, low_level | edge | falling_edge | rising_edge)

#define _hwx_cfinta_vsense_1(x,o,v,...)				\
  HW_TX( x##_write_reg(o,sc,HW_A1(_hw_inta_sense_##v)), __VA_ARGS__ )

#define _hw_is_sense_sense		, 1
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
 * if ( hw_stat_irqf( EI_NAME ) ) {        // Read IRQ flag
 *   hw_clear_irqf( EI_NAME );             // Clear IRQ flag
 *   hw_turn_irq( EI_NAME, off );          // Disable IRQ
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
 * These registers are accessible through the @ref public_reg_instructions
 * "register access intructions".
 */


/**
 * @page atmelavr_inta
 * <br>
 */
