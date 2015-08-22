
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

#define _hw_mthd_hw_write__pcicd		, _hw_write_pcicd
#define _hw_mthd_hw_turn__pcicd			, _hw_turn_pcicd


/**
 * @page atmelavr_pcicd
 * @section atmelavr_pcicd_select Changing the pins that are monitored
 *
 * @code
 * hw_write( hw_pcic0, hw_pin_pa2, 1 );
 * @endcode
 * @code
 * hw_turn( hw_pcic0, hw_pin_pa2, on );
 * @endcode
 */
#define _hw_write_pcicd( o,i,a, ion, v, ...)	HW_TX(_hw_write_pcicd_2(o,ion,v),__VA_ARGS__)
#define _hw_write_pcicd_2(o,ion,v)		hw_write_reg(o,ion,v)

#define _hw_turn_pcicd( o,i,a, ion, v, ...)	HW_TX(_hw_turn_pcicd_2(o,ion,v),__VA_ARGS__)
#define _hw_turn_pcicd_2(o,ion,v)		HW_G2(_hw_turn_pcicd,HW_IS(,_hw_state_##v))(o,ion,v)
#define _hw_turn_pcicd_1(o,ion,v)		hw_write_reg(o,ion,HW_A1(_hw_state_##v))


/**
 * @page atmelavr_pcicd
 * @section atmelavr_pcicd_turnirq Interrupts
 *
 * Use the `hw_turn_irq(...)` or `hwa_turn_irq(...)` instruction to enable or
 * disable a pin change IRQ.
 *
 * @code
 * hw_turn_irq( hw_pcic0, hw_pin_pa2, on );	// Enable IRQ on PA2 change
 * hw_turn_irq( hw_pcic0, hw_pin_pb1, off );	// Disable IRQ on PB1 change
 * @endcode
 *
 * @code
 * HW_ISR( hw_pcic0, hw_pin_pa2 )
 * {
 *	// Service PA2 change interrupt
 * }
 * @endcode
 */


/*******************************************************************************
 *                                                                             *
 *      Context management						       *
 *                                                                             *
 *******************************************************************************/

#define _hwa_create__pcicd(o,i,a)	_hwa_create_reg( o, msk0 )

#define _hwa_init__pcicd(o,i,a)		_hwa_init_reg( o, msk0, 0x00 )

#define _hwa_commit__pcicd(o,i,a)	_hwa_commit_reg( o, msk0 )
