
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA common declarations to all Atmel AVR counter-timers (layer 2)
 */


/*	Configure an output-compare unit
 */
#define hwa_config_ocu_isfn
#define hwa_config_ocu(ocn, ctr,cc,cn,ca, reg, ion, mode)	\
  HW_G2(hwa_config_ocu, HW_IS(ok,hw_ocu_mode_##mode))(ocn,mode)
#define hwa_config_ocu_0(ocn,mode)					\
  HW_ERR( "`" #mode "` is not a valid mode for `hw_" #ocn "`." )
#define hwa_config_ocu_1(ocn,zmode)					\
  do { hwa->ocn.config = 1 ; hwa->ocn.mode = HW_A1(hw_ocu_mode_##zmode) ; } while(0)


/*	Write the output-compare register of counter from output-compare unit
 */
#define hwa_write_ocu_isfn
#define hwa_write_ocu(ocn, ctr,cc,cn,ca, reg, ion, value)	\
  _hwa_write_mem(ctr,cc,cn,ca, reg, value)
