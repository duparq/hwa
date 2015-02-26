
/*	Atmel AVR watchdog model 'a'
 *
 *	Used in: ATtinyX4 (WDOG)	hw_watchdog0
 *		 ATtinyX5 (WDOG)	hw_watchdog0
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__wdog_2.h"

#define hwa_wdoga_t			hwa_wdog_t


/*	Watchdog class methods
 */
#define hw_def_hw_turn__wdoga		, _hw_turn_wdog
#define hw_def_hwa_turn__wdoga		, _hwa_turn_wdog
#define hw_def_hw_reset__wdoga		, _hw_wdreset
#define hw_def_hwa_config__wdoga	, _hwa_cfwdog
#define hw_def_hw_stat__wdoga		, _hw_stat_wdog
#define hw_def_hw_stat_t__wdoga		, _hw_statt_wdog


HW_INLINE void __hwa_begin__wdoga ( hwa_wdoga_t *p, intptr_t address )
{
  p->action = 0xFF ;
  p->timeout = 0xFF ;
  _hwa_begin_pacr( p, address, _wdoga, csr );
}


HW_INLINE void __hwa_init__wdoga ( hwa_wdoga_t *p )
{
  _hwa_set_r8( &p->csr, 0x00 );
}


#if 0
HW_INLINE void _hwa_commit_wdoga( hwa_t *hwa, hwa_wdoga_t *wdog )
{
  if ( wdog->action != 0xFF ) {
    if ( wdog->action == HW_A1(hw_wdog_action_none) ) {
      /*
       *  Turn the watchdog off. This requires that WDRF is 0 then:
       *    1. WDCE and WDE must be set to 1 in the same operation
       *    2. WDE must be set to 0 within 4 cycles after 1.
       */
#if HW_DEVICE_WDTON == 0
      HW_ERR( "watchdog can not be turned off because FUSE bit WDTON is " \
	      "programmed." );
#endif
      _hwa_write_reg( hw_core0, wdrf, 0 );
      _hwa_commit_reg( hw_core0, mcusr, hwa->commit );
      _hwa_write_reg( hw_watchdog0, wdif, 1 );
      _hwa_write_reg( hw_watchdog0, wdce, 1 );
      _hwa_write_reg( hw_watchdog0, wde,  1 );
      _hwa_commit_reg( hw_watchdog0, csr, hwa->commit );
      _hwa_write_reg( hw_watchdog0, wdie, 0 );
      _hwa_write_reg( hw_watchdog0, wdce, 0 );
      _hwa_write_reg( hw_watchdog0, wde, 0 );
      _hwa_write_reg( hw_watchdog0, wdp, 0 );
    }
    else {
      /*
       *  Configure the watchdog
       */
      _hwa_write_reg( hw_watchdog0, wde,  (wdog->action & 0x02)>>1 );
      _hwa_write_reg( hw_watchdog0, wdie, (wdog->action & 0x01)>>0 );
      if ( wdog->timeout != 0xFF )
	_hwa_write_reg( hw_watchdog0, wdp, wdog->timeout );
    }
    wdog->action = 0xFF ;
    wdog->timeout = 0xFF ;
  }
  _hwa_commit_reg( hw_watchdog0, csr, hwa->commit );
}
#endif


HW_INLINE void __hwa_commit__wdoga ( hwa_t *hwa, hwa_wdoga_t *p )
{
  if ( p->action != 0xFF ) {
    if ( p->action == HW_A1(hw_wdog_action_none) ) {
      /*
       *  Turn the watchdog off:
       *    1. Clear WDRF
       *    2. Set WDCE and WDE to 1 in the same operation
       *    3. Set WDE to 0 within 4 cycles after 2.
       */
#if HW_DEVICE_WDTON == 0
      HW_ERR( "watchdog can not be turned off because FUSE bit WDTON is " \
	      "programmed." );
#endif
      _hwa_write_pcr( p, _wdoga, wdrf, 0 );
      _hwa_commit_pcr( p, _wdoga, wdrf );

      // _hwa_write_pcr( p, _wdoga, wdif, 1 );
      _hwa_write_pcr( p, _wdoga, wdce, 1 );
      _hwa_write_pcr( p, _wdoga, wde,  1 );
      _hwa_commit_pcr( p, _wdoga, csr );
      _hwa_write_pcr( p, _wdoga, wdie, 0 );
      _hwa_write_pcr( p, _wdoga, wdce, 0 );
      _hwa_write_pcr( p, _wdoga, wde, 0 );
      _hwa_write_pcr( p, _wdoga, wdp, 0 );
    }
    else {
      /*
       *  Configure the watchdog
       */
      _hwa_write_pcr( p, _wdoga, wdeie, p->action );
      if ( p->timeout != 0xFF )
	_hwa_write_pcr( p, _wdoga, wdp, p->timeout );
    }
    p->action = 0xFF ;
    p->timeout = 0xFF ;
  }
  _hwa_commit_pcr( p, _wdoga, csr );
}
