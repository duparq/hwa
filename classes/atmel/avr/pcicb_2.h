
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

#define _hwa_begin__pcicb(i,a,o)		\
  _hwa_begin_reg( o, a, fr   );			\
  _hwa_begin_reg( o, a, cr   );			\
  _hwa_begin_reg( o, a, msk0 );			\
  _hwa_begin_reg( o, a, msk1 );			\
  _hwa_begin_reg( o, a, msk2 );

#define _hwa_init__pcicb(i,a,o)			\
  _hwa_init_reg( o, fr,   0 );			\
  _hwa_init_reg( o, cr,   0 );			\
  _hwa_init_reg( o, msk0, 0 );			\
  _hwa_init_reg( o, msk1, 0 );			\
  _hwa_init_reg( o, msk2, 0 );

#define _hwa_commit__pcicb(i,a,o)		\
  _hwa_commit_reg( o, fr   );			\
  _hwa_commit_reg( o, cr   );			\
  _hwa_commit_reg( o, msk0 );			\
  _hwa_commit_reg( o, msk1 );			\
  _hwa_commit_reg( o, msk2 );


/* HW_INLINE void _hwa_begin_p__pcicb ( hwa_pcicb_t *p, intptr_t address ) */
/* { */
/*   _hwa_begin_reg_p( p, address, _pcicb, fr   ); */
/*   _hwa_begin_reg_p( p, address, _pcicb, cr   ); */
/*   _hwa_begin_reg_p( p, address, _pcicb, msk0 ); */
/*   _hwa_begin_reg_p( p, address, _pcicb, msk1 ); */
/*   _hwa_begin_reg_p( p, address, _pcicb, msk2 ); */
/* } */


/* HW_INLINE void _hwa_init_p__pcicb ( hwa_pcicb_t *p ) */
/* { */
/*   _hwa_set__r8( &p->fr,   0x00 ); */
/*   _hwa_set__r8( &p->cr,   0x00 ); */
/*   _hwa_set__r8( &p->msk0, 0x00 ); */
/*   _hwa_set__r8( &p->msk1, 0x00 ); */
/*   _hwa_set__r8( &p->msk2, 0x00 ); */
/* } */


/* HW_INLINE void _hwa_commit_p__pcicb ( hwa_t *hwa, hwa_pcicb_t *p ) */
/* { */
/*   _hwa_commit_reg_p( p, _pcicb, fr   ); */
/*   _hwa_commit_reg_p( p, _pcicb, cr   ); */
/*   _hwa_commit_reg_p( p, _pcicb, msk0 ); */
/*   _hwa_commit_reg_p( p, _pcicb, msk1 ); */
/*   _hwa_commit_reg_p( p, _pcicb, msk2 ); */
/* } */


/**
 * @page atmelavr_pcicb
 * @section atmelavr_pcicb_select Selecting the pins that are monitored
 *
 * @code
 * hw_write( hw_pcic0, hw_pin_pa2, 1 );
 * @endcode
 */
#define _hw_mthd_hw_write__pcicb		, _hw_write_pcicb

#define _hw_write_pcicb( p,i,a, pn, v, ...)	HW_TX(_hw_write_pcicb_2(p,pn,v),__VA_ARGS__)
#define _hw_write_pcicb_2(p,pn,v)		hw_write_reg(p,pn,v)

/**
 * @page atmelavr_pcicb
 *
 * @code
 * hw_turn( hw_pcic0, hw_pin_pa2, on );
 * @endcode
 */
#define _hw_mthd_hw_turn__pcicb			, _hw_turn_pcicb

#define _hw_turn_pcicb( p,i,a, pn, v, ...)	HW_TX(_hw_turn_pcicb_2(p,pn,v),__VA_ARGS__)
#define _hw_turn_pcicb_2(p,pn,v)		HW_G2(_hw_turn_pcicb,HW_IS(,_hw_state_##v))(p,pn,v)
#define _hw_turn_pcicb_1(p,pn,v)		hw_write_reg(p,pn,HW_A1(_hw_state_##v))


/**
 * @page atmelavr_pcicb
 * @section atmelavr_pcicb_turnirq Interrupts
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
