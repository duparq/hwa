
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Watchdog class methods
 */
#define hw_def_hw_turn_wdogB		, _hw_turn_wdog
#define hw_def_hwa_turn_wdogB		, _hwa_turn_wdog
#define hw_def_hw_reset_wdogB		, _hw_wdreset
#define hw_def_hwa_config_wdogB		, _hwa_cfwdog
#define hw_def_hw_stat_wdogB		, _hw_stat_wdog


HW_INLINE void _hwa_commit_wdogB( hwa_t *hwa, hwa_wdogB_t *wdog )
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
      //      _hwa_write_reg( hw_watchdog0, wdif, 1 );
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
      //      _hwa_write_reg( hw_watchdog0, wdif, 1 );
      _hwa_write_reg( hw_watchdog0, wdce, 1 );
      _hwa_write_reg( hw_watchdog0, wde,  1 );
      _hwa_commit_reg( hw_watchdog0, csr, hwa->commit );
      _hwa_write_reg( hw_watchdog0, wdce, 0 );
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
