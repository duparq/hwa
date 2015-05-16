
/*	Atmel AVR pin change interrupt controller model 'a'
 *
 *	Used in: ATtinyX4
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void __hwa_begin__pcica ( hwa_pcica_t *p, intptr_t address )
{
  _hwa_begin_reg_p( p, address, _pcica, msk0 );
  _hwa_begin_reg_p( p, address, _pcica, msk1 );
  /* _hwa_begin_reg_p( p, address, _pcica, msk ); */
}


HW_INLINE void __hwa_init__pcica ( hwa_pcica_t *p )
{
  _hwa_set_r8( &p->msk0, 0x00 );
  _hwa_set_r8( &p->msk1, 0x00 );
  /* _hwa_set_r8( &p->msk, 0x00 ); */
}


HW_INLINE void __hwa_commit__pcica ( hwa_t *hwa, hwa_pcica_t *p )
{
  _hwa_commit_reg_p( p, _pcica, msk0 );
  _hwa_commit_reg_p( p, _pcica, msk1 );
  /* _hwa_commit_reg_p( p, _pcica, msk ); */
}


#define _hw_mthd_hw_write__pcica		, _hw_write_pcica
#define _hw_mthd_hw_turn__pcica			, _hw_turn_pcica

#define _hw_is__pin1__pin1			, 1

/* #define _hw_write_pcica( p,i,a, pn, v, ...)	HW_TX(_hw_write_pcica_2(p,pn,_##pn,v),__VA_ARGS__) */
/* #define _hw_write_pcica_2(...)		_hw_write_pcica_3(__VA_ARGS__) */
/* #define _hw_write_pcica_3(p,pn,x,...)	HW_G2(_hw_write_pcica,HW_IS(_pin1,x))(p,pn,__VA_ARGS__) */
/* #define _hw_write_pcica_1(p,pn,ioi,iop,iobn,iobp,v) _hw_write_reg(p,pn, v) */


#define _hw_write_pcica( p,i,a, pn, v, ...)	HW_TX(_hw_write_pcica_2(p,pn,v),__VA_ARGS__)
#define _hw_write_pcica_2(p,pn,v)		hw_write_reg(p,pn,v)

#define _hw_turn_pcica( p,i,a, pn, v, ...)	HW_TX(_hw_turn_pcica_2(p,pn,v),__VA_ARGS__)
#define _hw_turn_pcica_2(p,pn,v)		HW_G2(_hw_turn_pcica,HW_IS(,hw_state_##v))(p,pn,v)
#define _hw_turn_pcica_1(p,pn,v)		hw_write_reg(p,pn,HW_A1(hw_state_##v))
