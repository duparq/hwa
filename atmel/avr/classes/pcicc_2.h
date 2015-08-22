
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

#define _hwa_create__pcicc(o,i,a)		_hwa_create_reg( o, a, msk0 );

#define _hwa_init__pcicc(o,i,a)			_hwa_init_reg( o, msk, 0x00 );

#define _hwa_commit__pcicc(o,i,a)		_hwa_commit_reg( o, msk );

#define _hw_mthd_hw_write__pcicc		, _hw_write_pcicc
#define _hw_mthd_hw_turn__pcicc			, _hw_turn_pcicc


/**
 * @page atmelavr_pcicc
 * @section atmelavr_pcicc_select Changing the pins that are monitored
 *
 * @code
 * hw_write( hw_pcic0, hw_pin_pb0, 1 );
 * @endcode
 * @code
 * hw_turn( hw_pcic0, hw_pin_pb0, on );
 * @endcode
 */
#define _hw_write_pcicc(o,i,a, pn, v, ...)	HW_TX(_hw_write_pcicc_2(o,pn,v),__VA_ARGS__)
#define _hw_write_pcicc_2(p,pn,v)		hw_write_reg(p,pn,v)

#define _hw_turn_pcicc( p,i,a, pn, v, ...)	HW_TX(_hw_turn_pcicc_2(p,pn,v),__VA_ARGS__)
#define _hw_turn_pcicc_2(p,pn,v)		HW_G2(_hw_turn_pcicc,HW_IS(,_hw_state_##v))(p,pn,v)
#define _hw_turn_pcicc_1(p,pn,v)		hw_write_reg(p,pn,HW_A1(_hw_state_##v))


/**
 * @page atmelavr_pcicc
 * @section atmelavr_pcicc_turnirq Interrupts
 *
 * Use the `hw_turn_irq()` or `hwa_turn_irq()` instruction to enable or
 * disable a pin change IRQ.
 *
 * @code
 * hw_turn_irq( hw_pcic0, hw_pin_pb0, on );	// Enable IRQ on PB0 change
 * @endcode
 *
 * @code
 * HW_ISR( hw_pcic0, hw_pin_pb0 )
 * {
 *	// Service PB0 change interrupt
 * }
 * @endcode
 */
