
/*	Atmel AVR watchdog model 'a'
 *
 *	Used in: ATtinyX4 (WDOG)	hw_wdog0
 *		 ATtinyX5 (WDOG)	hw_wdog0
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "wdog_2.h"

#define hwa_wdoga_t			hwa_wdog_t


/*	Watchdog class methods
 */
#define _hw_mthd_hw_turn__wdoga		, _hw_turn_wdog
#define _hw_mthd_hwa_turn__wdoga	, _hwa_turn_wdog
#define _hw_mthd_hw_reset__wdoga	, _hw_wdreset
#define _hw_mthd_hwa_config__wdoga	, _hwa_cfwdog
#define _hw_mthd_hw_stat__wdoga		, _hw_stat_wdog
#define _hw_mthd_hw_stat_t__wdoga	, _hw_statt_wdog


HW_INLINE void __hwa_begin__wdoga ( hwa_wdoga_t *p, intptr_t address )
{
  p->action = 0xFF ;
  p->timeout = 0xFF ;
  _hwa_begin_reg_p( p, address, _wdoga, csr );
}


HW_INLINE void __hwa_init__wdoga ( hwa_wdoga_t *p )
{
  _hwa_set_r8( &p->csr, 0x00 );
}


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
      _hwa_write_creg( p, _wdoga, wdrf, 0 );
      _hwa_commit_reg_p( p, _wdoga, wdrf );

      // _hwa_write_creg( p, _wdoga, wdif, 1 );
      _hwa_write_creg( p, _wdoga, wdce, 1 );
      _hwa_write_creg( p, _wdoga, wde,  1 );
      _hwa_commit_reg_p( p, _wdoga, csr );
      _hwa_write_creg( p, _wdoga, wdie, 0 );
      _hwa_write_creg( p, _wdoga, wdce, 0 );
      _hwa_write_creg( p, _wdoga, wde, 0 );
      _hwa_write_creg( p, _wdoga, wdp, 0 );
    }
    else {
      /*
       *  Configure the watchdog
       */
      _hwa_write_creg( p, _wdoga, wdeie, p->action );
      if ( p->timeout != 0xFF )
	_hwa_write_creg( p, _wdoga, wdp, p->timeout );
    }
    p->action = 0xFF ;
    p->timeout = 0xFF ;
  }
  _hwa_commit_reg_p( p, _wdoga, csr );
}
