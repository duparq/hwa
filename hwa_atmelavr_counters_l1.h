
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA layer 1, common declarations for Atmel AVR counter-timers
 */


/*	Modes for output-compare units
 */
#define hw_ocu_mode_disconnected				ok, 1
#define hw_ocu_mode_toggled_on_match				ok, 2
#define hw_ocu_mode_cleared_on_match				ok, 3
#define hw_ocu_mode_set_on_match				ok, 4
#define hw_ocu_mode_set_at_bottom_cleared_on_match		ok, 5
#define hw_ocu_mode_cleared_at_bottom_set_on_match		ok, 6
#define hw_ocu_mode_cleared_on_match_up_set_on_match_down	ok, 7
#define hw_ocu_mode_clearup_setdown				ok, 7
#define hw_ocu_mode_set_on_match_up_cleared_on_match_down	ok, 8
#define hw_ocu_mode_setup_cleardown				ok, 8


/*	Write compare value of an ocu
 */
#define hw_write_ocu_isfn
#define hw_write_ocu(ocn, ctr,cc,cn,ca, reg, ion, value)	\
  _hw_write_mem(ctr,cc,cn,ca,reg,value)
//  hw_write(ctr,cc,cn,ca,reg,value)


/*	Definition of the io pin associated to an ocu
 */
#define hw_io_ocu_isfn
#define hw_io_ocu(ocun, ctr,cc,cn,ca, reg, ion)		hw_##ion


/*	Definition of the counter associated to an ocu
 */
#define hw_ctr_ocu_isfn
#define hw_ctr_ocu(ocn, ctr,cc,cn,ca, reg, ion)		ctr,cc,cn,ca


#if !defined __ASSEMBLER__

/*	Soft registers for output-compare units
 */
typedef struct {
  uint8_t 	config, mode ;
} hwa_ocu_t ;

#endif
