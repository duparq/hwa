
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
#define hwa_config_ocu(n,_ocu_, _ctr_,cn,cc,ca, reg, ion, mode, _)	\
  HW_G2(hwa_config_ocu, HW_IS(ok,hw_ocu_mode_##mode))(n,mode)
#define hwa_config_ocu_0(n,mode)					\
  HW_PPERROR( "`" #mode "` is not a valid mode for hw_" #n "." )
#define hwa_config_ocu_1(n,zmode)					\
  do { hwa->n.config = 1 ; hwa->n.mode = HW_A1(hw_ocu_mode_##zmode) ; } while(0)


/*	Write the output-compare register of counter from output-compare unit
 */
#define hwa_write_ocu_isfn
#define hwa_write_ocu(n,_ocu_,_ctr_,cn,cc,ca, reg, ion, value)\
  _hwa_write_2(_ctr_,cn,cc,ca, reg, value)
