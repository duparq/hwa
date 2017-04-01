
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit analog to digital converter common methods
 */


/*	Turn ADC on / off
 */
#define _hw_turn_ad10_(o,i,a, v, ...)			\
  HW_X(_hwx_turn_ad10_,_hw_state_##v)(_hw,o,v,__VA_ARGS__)

#define _hwa_turn_ad10_(o,i,a, v, ...)			\
  HW_X(_hwx_turn_ad10_,_hw_state_##v)(_hwa,o,v,__VA_ARGS__)

#define _hwx_turn_ad10__0(x,o, v, ...)			\
  HW_E_ST(v)

#define _hwx_turn_ad10__1(x,o, v, ...)					\
  HW_TX(x##_write_reg(o, en, HW_A1(_hw_state_##v)),__VA_ARGS__)


/*	Start a conversion
 */
#define _hw_trigger_ad10_(o,i,a,...)	_hw_write_reg( o, sc, 1 )
#define _hwa_trigger_ad10_(o,i,a,...)	_hwa_write_reg( o, sc, 1 )


/*	Read the result of the conversion
 */
#define _hw_rdad10_(o,i,a,...)					\
  HW_X(_hw_rdad10_,__VA_ARGS__)(o,__VA_ARGS__,)

#define _hw_rdad10__1(o,...)		_hw_read_reg(o, adc)

/*  Optionnal argument `hi8`
 */
#define _hw_rdad10__0(o,k,...)					\
  HW_G2(_hw_rdad10__khi8,HW_IS(hi8,k))(o,k,__VA_ARGS__)

#define _hw_rdad10__khi8_1(o,k,...)	(*(volatile uint8_t*)(_HW_A(_HW_M(o,adc))+1))

#define _hw_is_hi8_hi8			, 1

/*  Optionnal argument `lo8`
 */
#define _hw_rdad10__khi8_0(o,k,...)				\
  HW_G2(_hw_rdad10__klo8,HW_IS(lo8,k))(o,k,__VA_ARGS__)

#define _hw_rdad10__klo8_1(o,k,...)	(*(volatile uint8_t*)(_HW_A(_HW_M(o,adc))))
#define _hw_rdad10__klo8_0(o,k,...)	HW_E(optionnal parameter can be `lo8 | hi8` but not `k`)

#define _hw_is_lo8_lo8			, 1


/*	Read the ADC result with interrupts disabled and restore state as soon
 *	as possible.
 */
#define _hw_ardad10_(o,i,a,...)		_hw_atomic_read_reg(o, adc)

/*	Status
 */
typedef union {
  uint8_t	  byte ;
  struct {
    unsigned int  __0_5 : 6 ;
    unsigned int  busy	: 1 ;
    unsigned int  __7	: 1 ;
  };
} _hw_ad10__status_t ;

#define _hw_stat_ad10_(o,i,a,...)	HW_TX(_hw_ad10__status(_hw_read_reg(o,sra)), \
					      __VA_ARGS__)

HW_INLINE _hw_ad10__status_t _hw_ad10__status( uint8_t byte )
{
  _hw_ad10__status_t	st ;
  st.byte = byte ;
  return st ;
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__ad10_(o)			\
  _hwa_setup_reg( o, admux );			\
  _hwa_setup_reg( o, sra   );			\
  _hwa_setup_reg( o, srb   )

#define _hwa_init__ad10_(o)			\
  _hwa_init_reg( o, admux, 0x00 );		\
  _hwa_init_reg( o, sra,   0x00 );		\
  _hwa_init_reg( o, srb,   0x00 )

#define _hwa_commit__ad10_(o)			\
  _hwa_commit_reg( o, admux );			\
  _hwa_commit_reg( o, sra   );			\
  _hwa_commit_reg( o, srb   )
