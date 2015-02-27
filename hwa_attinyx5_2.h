
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_2.h"
#include "hwa_atmelavr__corea_2.h"
#include "hwa_atmelavr__io_2.h"
#include "hwa_atmelavr__wdoga_2.h"
#include "hwa_atmelavr__c8a_2.h"



HW_INLINE void _hwa_begin_all( hwa_t *hwa )
{
  _hwa_begin( hw_core0 );
  _hwa_begin( hw_portb );
  _hwa_begin( hw_watchdog0 );

  _hwa_begin_reg( hw_shared0, timsk );
  _hwa_begin_reg( hw_shared0, tifr );
  _hwa_begin( hw_counter0 );
}


HW_INLINE void _hwa_init_all( hwa_t *hwa )
{
  _hwa_init( hw_core0 );
  _hwa_init( hw_portb );
  _hwa_init( hw_watchdog0 );

  _hwa_set_r8( &hwa->shared0.timsk, 0x00 );
  _hwa_set_r8( &hwa->shared0.tifr,  0x00 );
  _hwa_init( hw_counter0 );
}


HW_INLINE void _hwa_commit_all( hwa_t *hwa )
{
  _hwa_solve( hw_counter0 );

  _hwa_commit( hw_core0 );
  _hwa_commit( hw_watchdog0 );
  _hwa_commit( hw_portb );
  _hwa_commit_reg( hw_shared0, timsk, hwa->commit );
  _hwa_commit_reg( hw_shared0, tifr,  hwa->commit );
  _hwa_commit( hw_counter0 );
}


/*	Status of hw_counter0
 */
typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  _0       : 1 ;
    unsigned int  overflow : 1 ;
    unsigned int  _2       : 1 ;
    unsigned int  output1  : 1 ;
    unsigned int  output0  : 1 ;
    unsigned int  _567     : 3 ;
  };
} _hw_c8a_stat_t ;

#define _hw_stat_c8a(c,n,i,a)		_hw_c8a_stat( _hw_read_reg(hw_shared0, tifr) )

HW_INLINE _hw_c8a_stat_t _hw_c8a_stat( uint8_t byte )
{
  _hw_c8a_stat_t	st ;
  st.byte = byte ;
  return st ;
}
