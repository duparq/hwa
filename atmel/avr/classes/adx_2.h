
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 10-bit analog to digital converter common methods
 */


#define _hw_adxclock_ioclk		, _hw_adxckdiv, 1.0
#define _hw_adxclock_min		, _hw_adxckmin, 1.0
#define _hw_adxclock_max		, _hw_adxckmax, 1.0


HW_INLINE uint8_t _hw_adxckdiv( float v )
{
  if ( v == 1.0 / 128 ) return 7 ;
  if ( v == 1.0 / 64 )  return 6 ;
  if ( v == 1.0 / 32 )  return 5 ;
  if ( v == 1.0 / 16 )  return 4 ;
  if ( v == 1.0 / 8 )   return 3 ;
  if ( v == 1.0 / 4 )   return 2 ;
  if ( v == 1.0 / 2 )   return 1 ;

  HWA_E(HW_EM_AVL(clock,(ioclk/2**(1..7))));

  return 0 ;
}


HW_INLINE uint8_t _hw_adxckmin( float v __attribute__((unused)) )
{
  if ( HW_SYSHZ / 128 >= 50000 ) return 7 ;
  if ( HW_SYSHZ / 64 >= 50000 )  return 6 ;
  if ( HW_SYSHZ / 32 >= 50000 )  return 5 ;
  if ( HW_SYSHZ / 16 >= 50000 )  return 4 ;
  if ( HW_SYSHZ / 8 >= 50000 )   return 3 ;
  if ( HW_SYSHZ / 4 >= 50000 )   return 2 ;
  return 1 ;
}


HW_INLINE uint8_t _hw_adxckmax( float v __attribute__((unused)) )
{
  if ( HW_SYSHZ / 2 < 200000 )  return 1 ;
  if ( HW_SYSHZ / 4 < 200000 )  return 2 ;
  if ( HW_SYSHZ / 8 < 200000 )  return 3 ;
  if ( HW_SYSHZ / 16 < 200000 ) return 4 ;
  if ( HW_SYSHZ / 32 >= 50000 ) return 5 ;
  if ( HW_SYSHZ / 64 >= 50000 ) return 6 ;
  return 7 ;
}


/*	Enable / disable
 */
#define _hw_enable_adx_(o,a,...)	_hw_write(o,en,1) HW_EOL(__VA_ARGS__)
#define _hwa_enable_adx_(o,a,...)	_hwa_write(o,en,1) HW_EOL(__VA_ARGS__)

#define _hw_disable_adx_(o,a,...)	_hw_write(o,en,0) HW_EOL(__VA_ARGS__)
#define _hwa_disable_adx_(o,a,...)	_hwa_write(o,en,0) HW_EOL(__VA_ARGS__)


/*	Start a conversion
 */
#define _hw_trigger_adx_(o,a,...)	_hw_write( o, sc, 1 )
#define _hwa_trigger_adx_(o,a,...)	_hwa_write( o, sc, 1 )


/*	Read the result of the conversion
 */
#define _hw_rdadx_(o,a,...)		_HW_B(_hw_rdadx,__VA_ARGS__)(o,__VA_ARGS__,)
#define _hw_rdadx1(o,...)		_hw_read(o, adc)
#define _hw_rdadx0(o,k,...)		HW_BW(_hw_rdadx0,hi8,k)(o,k,__VA_ARGS__)	// `hi8` ?
#define _hw_rdadx01(o,k,...)		(*(volatile uint8_t*)(HW_ADDRESS((o,adc))+1))
#define _hw_rdadx00(o,k,...)		HW_BW(_hw_rdadx00,lo8,k)(o,k,__VA_ARGS__)	// `lo8` ?
#define _hw_rdadx001(o,k,...)		(*(volatile uint8_t*)(HW_ADDRESS((o,adc))))
#define _hw_rdadx000(o,k,...)		HW_E(HW_EM_AL(k,(lo8,hi8)))


/*	Read the ADC result with interrupts disabled and restore state as soon
 *	as possible.
 */
#define _hw_ardadx_(o,a,...)		_hw_atomic_read(o, adc)


/*	Status
 */
typedef union {
  uint8_t	  byte ;
  struct {
    unsigned int  __0_5 : 6 ;
    unsigned int  busy	: 1 ;
    unsigned int  __7	: 1 ;
  };
} _hw_adx__status_t ;

#define _hw_stat_adx_(o,a,...)	_hw_adx__status(_hw_read(o,sra)) HW_EOL(__VA_ARGS__)

HW_INLINE _hw_adx__status_t _hw_adx__status( uint8_t byte )
{
  _hw_adx__status_t	st ;
  st.byte = byte ;
  return st ;
}


/*******************************************************************************
 *									       *
 *	Context management						       *
 *									       *
 *******************************************************************************/

#define _hwa_setup__adx_(o)			\
  _hwa_setup_r( o, admux );			\
  _hwa_setup_r( o, sra	 );			\
  _hwa_setup_r( o, srb	 )

#define _hwa_init__adx_(o)			\
  _hwa_init_r( o, admux, 0x00 );		\
  _hwa_init_r( o, sra,	 0x00 );		\
  _hwa_init_r( o, srb,	 0x00 )

#define _hwa_commit__adx_(o)			\
  _hwa_commit_r( o, admux );			\
  _hwa_commit_r( o, sra	  );			\
  _hwa_commit_r( o, srb	  )
