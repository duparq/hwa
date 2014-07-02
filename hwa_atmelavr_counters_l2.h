
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA common declarations to all Atmel AVR counter-timers (layer 2)
 */


/*	Configure an output-compare unit
 */
#define hw_fn_hwa_config_ocu		, _hwa_config_ocu

#define _hwa_config_ocu(ocu,ocn,oci,_, mode)			\
  HW_G2(_hwa_config_ocu, HW_IS(ok,hw_ocu_mode_##mode))(ocn,mode)
#define _hwa_config_ocu_0(ocn,mode)					\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #ocn "`." )
#define _hwa_config_ocu_1(ocn,zmode)	\
  do { hwa->ocn.config = 1 ; hwa->ocn.mode = HW_A1(hw_ocu_mode_##zmode) ; } while(0)


//_hwa_config_ocu(ocu,oc1a, 701,, clearup_setdown);

/* #define _hwa_config_ocu_1(ocn,mode)	_hwa_config_ocu_2(hw_##ocn##_ext, mode) */
/* #define _hwa_config_ocu_2(...)		_hwa_config_ocu_3(__VA_ARGS__) */
/* #ëefine _hwa_config_ocu_3(cc,cn,ci,ca, reg,ion, mode)\ */
/* _hwa_config_ocu_2(c16a, counter1, 700, 0x002B, ocra, pin_7, clearup_setdown); */


/*	Write the output-compare register of counter from output-compare unit
 */
#define hw_fn_hwa_write_ocu		, _hwa_write_ocu

#define x_hwa_write_ocu(ocn, ctr,cc,cn,ca, reg, ion, value)	\
  _hwa_write_mem(ctr,cc,cn,ca, reg, value)
