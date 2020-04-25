
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit analog to digital converter common methods
 */


#define _hw_ad10_clock_ioclk			, _hwa_ad10_clkdiv, 1.0
#define _hw_ad10_clock_min			, _hwa_ad10_clkmin, 1.0
#define _hw_ad10_clock_max			, _hwa_ad10_clkmax, 1.0


/*	Compute min / max acceptable value of clock prescaler
 */
#define HW_PRESCALER_MAX(o)			hw(prescaler_max,o)
#define HW_PRESCALER_MIN(o)			hw(prescaler_min,o)

#define hw_ad10_prescaler_max(o,a,...)	_hw_ad10_prescaler_max()
#define hw_ad10_prescaler_min(o,a,...)	_hw_ad10_prescaler_min()

HW_INLINE uint8_t _hw_ad10_prescaler_max()
{
  if ( HW_SYSHZ / 128 >= 50000 )
    return 128 ;
  if ( HW_SYSHZ / 64 >= 50000 )
    return 64 ;
  if ( HW_SYSHZ / 32 >= 50000 )
    return 32 ;
  if ( HW_SYSHZ / 16 >= 50000 )
    return 16 ;
  if ( HW_SYSHZ / 8 >= 50000 )
    return 8 ;
  if ( HW_SYSHZ / 4 >= 50000 )
    return 4 ;

  return 2 ;
}

HW_INLINE uint8_t _hw_ad10_prescaler_min()
{
  if ( HW_SYSHZ / 2 < 200000 )
    return 2 ;
  if ( HW_SYSHZ / 4 < 200000 )
    return 4 ;
  if ( HW_SYSHZ / 8 < 200000 )
    return 8 ;
  if ( HW_SYSHZ / 16 < 200000 )
    return 16 ;
  if ( HW_SYSHZ / 32 >= 50000 )
    return 32 ;
  if ( HW_SYSHZ / 64 >= 50000 )
    return 64 ;

  return 128 ;
}


HW_INLINE uint8_t _hwa_ad10_clkdiv( float v )
{
  uint8_t	ps = 0 ;

  if ( v == 1.0 / 128 )
    ps = 7 ;
  else if ( v == 1.0 / 64 )
    ps = 6 ;
  else if ( v == 1.0 / 32 )
    ps = 5 ;
  else if ( v == 1.0 / 16 )
    ps = 4 ;
  else if ( v == 1.0 / 8 )
    ps = 3 ;
  else if ( v == 1.0 / 4 )
    ps = 2 ;
  else if ( v == 1.0 / 2 )
    ps = 1 ;
  else
    HWA_E(value of `clock` must be in (`ioclk/2**n` with n in [1..7]));

  return ps ;
}

HW_INLINE uint8_t _hwa_ad10_clkmin( float v )
{
  if ( v != 1.0 )
    HWA_E(value of `clock` must be in (`ioclk/2**n` with n in [1..7]));

  if ( HW_SYSHZ / 128 >= 50000 )
    return 7 ;
  if ( HW_SYSHZ / 64 >= 50000 )
    return 6 ;
  if ( HW_SYSHZ / 32 >= 50000 )
    return 5 ;
  if ( HW_SYSHZ / 16 >= 50000 )
    return 4 ;
  if ( HW_SYSHZ / 8 >= 50000 )
    return 3 ;
  if ( HW_SYSHZ / 4 >= 50000 )
    return 2 ;

  return 1 ;
}

HW_INLINE uint8_t _hwa_ad10_clkmax( float v )
{
  if ( v != 1 )
    HWA_E(value of `clock` must be in (`ioclk/2**n` with n in [1..7]));

  if ( HW_SYSHZ / 2 < 200000 )
    return 1 ;
  if ( HW_SYSHZ / 4 < 200000 )
    return 2 ;
  if ( HW_SYSHZ / 8 < 200000 )
    return 3 ;
  if ( HW_SYSHZ / 16 < 200000 )
    return 4 ;
  if ( HW_SYSHZ / 32 >= 50000 )
    return 5 ;
  if ( HW_SYSHZ / 64 >= 50000 )
    return 6 ;

  return 7 ;
}


/*	Turn ADC on / off
 */
#define _hw_turn_ad10_(o,a, v, ...)			\
  HW_Y(_hwx_turn_ad10__,_hw_state_##v)(_hw,o,v,__VA_ARGS__)

#define _hwa_turn_ad10_(o,a, v, ...)			\
  HW_Y(_hwx_turn_ad10__,_hw_state_##v)(_hwa,o,v,__VA_ARGS__)

#define _hwx_turn_ad10__0(x,o, v, ...)			\
  HW_E_ST(v)

#define _hwx_turn_ad10__1(x,o, v, ...)					\
  x##_write(o, en, HW_A1(_hw_state_##v)) HW_EOL(__VA_ARGS__)


/*	Start a conversion
 */
#define _hw_trigger_ad10_(o,a,...)	_hw_write( o, sc, 1 )
#define _hwa_trigger_ad10_(o,a,...)	_hwa_write( o, sc, 1 )


/*	Read the result of the conversion
 */
#define _hw_rdad10_(o,a,...)		HW_Y0(_hw_rdad10__,__VA_ARGS__)(o,__VA_ARGS__,)

#define _hw_rdad10__1(o,...)		_hw_read(o, adc)

/*  Optionnal argument `hi8`
 */
#define _hw_rdad10__0(o,k,...)					\
  HW_G2(_hw_rdad10__khi8,HW_IS(hi8,k))(o,k,__VA_ARGS__)

#define _hw_rdad10__khi8_1(o,k,...)	(*(volatile uint8_t*)(HW_ADDRESS((o,adc))+1))

/*  Optionnal argument `lo8`
 */
#define _hw_rdad10__khi8_0(o,k,...)				\
  HW_G2(_hw_rdad10__klo8,HW_IS(lo8,k))(o,k,__VA_ARGS__)

#define _hw_rdad10__klo8_1(o,k,...)	(*(volatile uint8_t*)(HW_ADDRESS((o,adc))))
#define _hw_rdad10__klo8_0(o,k,...)	HW_E(optionnal parameter can be `lo8 | hi8` but not `k`)


/*	Read the ADC result with interrupts disabled and restore state as soon
 *	as possible.
 */
#define _hw_ardad10_(o,a,...)		_hw_atomic_read(o, adc)

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

#define _hw_stat_ad10_(o,a,...)	_hw_ad10__status(_hw_read(o,sra)) HW_EOL(__VA_ARGS__)

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
  _hwa_setup_r( o, admux );			\
  _hwa_setup_r( o, sra   );			\
  _hwa_setup_r( o, srb   )

#define _hwa_init__ad10_(o)			\
  _hwa_init_r( o, admux, 0x00 );		\
  _hwa_init_r( o, sra,   0x00 );		\
  _hwa_init_r( o, srb,   0x00 )

#define _hwa_commit__ad10_(o)			\
  _hwa_commit_r( o, admux );			\
  _hwa_commit_r( o, sra   );			\
  _hwa_commit_r( o, srb   )
