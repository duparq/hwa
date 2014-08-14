
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void _hwa_begin_cores ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_core0, gimsk  );
  _hwa_begin_reg( hw_core0, gifr   );
  _hwa_begin_reg( hw_core0, mcucr  );
  _hwa_begin_reg( hw_core0, mcusr  );
  _hwa_begin_reg( hw_core0, osccal );
  _hwa_begin_reg( hw_core0, gpior2 );
  _hwa_begin_reg( hw_core0, gpior1 );
  _hwa_begin_reg( hw_core0, gpior0 );
  _hwa_begin_reg( hw_core0, prr    );
}


HW_INLINE void _hwa_reset_cores ( hwa_t *hwa )
{
  _hwa_reset_r8( &hwa->core0.gimsk,  0x00 );
  _hwa_reset_r8( &hwa->core0.gifr,   0x00 );
  _hwa_reset_r8( &hwa->core0.mcucr,  0x00 );
  _hwa_reset_r8( &hwa->core0.mcusr,  0x00 );
  _hwa_reset_r8( &hwa->core0.osccal, 0x00 );
  _hwa_reset_r8( &hwa->core0.gpior2, 0x00 );
  _hwa_reset_r8( &hwa->core0.gpior1, 0x00 );
  _hwa_reset_r8( &hwa->core0.gpior0, 0x00 );
  _hwa_reset_r8( &hwa->core0.prr,    0x00 );
}


HW_INLINE void _hwa_commit_cores ( hwa_t *hwa )
{
  _hwa_commit_r8( hwa->commit, &hwa->core0.gimsk  );
  _hwa_commit_r8( hwa->commit, &hwa->core0.gifr   );
  _hwa_commit_r8( hwa->commit, &hwa->core0.mcucr  );
  _hwa_commit_r8( hwa->commit, &hwa->core0.mcusr  );
  _hwa_commit_r8( hwa->commit, &hwa->core0.osccal );
  _hwa_commit_r8( hwa->commit, &hwa->core0.gpior2 );
  _hwa_commit_r8( hwa->commit, &hwa->core0.gpior1 );
  _hwa_commit_r8( hwa->commit, &hwa->core0.gpior0 );
  _hwa_commit_r8( hwa->commit, &hwa->core0.prr    );
}


/*	Configure the MCU sleep mode
 */
#define hw_is_sleep_mode_sleep_mode	, 1

#define hw_core_sm_idle			, 0
#define hw_core_sm_adc_noise_reduction	, 1
#define hw_core_sm_power_down		, 2
#define hw_core_sm_standby		, 3


#define hw_def_hwa_config_core		, _hwa_config_core
#define _hwa_config_core(c,n,i,a,...)					\
  HW_G2(_hwa_cfcore_xsleepmode, HW_IS(sleep_mode,__VA_ARGS__))(__VA_ARGS__,)

#define _hwa_cfcore_xsleepmode_0(...)					\
  HW_ERR("expected `sleep_mode`, got `" HW_QUOTE(__VA_ARGS__) "` instead.")

#define _hwa_cfcore_xsleepmode_1(kw,...)				\
  HW_G2(_hwa_cfcore_vsleepmode, HW_IS(,hw_core_sm_##__VA_ARGS__))(__VA_ARGS__)

#define _hwa_cfcore_vsleepmode_0(...)					\
  HW_ERR("`sleep_mode` can be `idle`, `adc_noise_reduction`, `power_down`, or "	\
	 "`standby`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfcore_vsleepmode_1(vsleepmode,...)		\
  HW_TX(_hwa_write_reg(hw_core0, sm, HW_A1(hw_core_sm_##vsleepmode)),__VA_ARGS__)
