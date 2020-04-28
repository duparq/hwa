
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief 2-wire interface
 */

/**
 * @page atmelavr_twia Class _twia: 2-wire interface
 *
 * A class `_twia` object is a 2-wire interface.
 *
 * It is used in:
 *
 *  * @ref atmegax8 : `twi0`
 */
#define hw_class__twia

/*	Class logical registers
 */
#define hw__twia_if			_cb1, cr, 1, 7		// IRQ flasg
#define hw__twia_ack			_cb1, cr, 1, 6		// Enable ACK
#define hw__twia_start			_cb1, cr, 1, 5		// Tx START condition
#define hw__twia_stop			_cb1, cr, 1, 4		// Tx STOP condition
#define hw__twia_collision		_cb1, cr, 1, 3		// Collision flag
#define hw__twia_en			_cb1, cr, 1, 2		// Enable TWI (take I/Os)
#define hw__twia_ie			_cb1, cr, 1, 0		// Enable IRQs

#define hw__twia_status			_cb1, sr, 5, 3		// Status code
#define hw__twia_psc			_cb1, sr, 2, 0		// Prescaler

#define hw__twia_sla			_cb1, ar, 7, 1		// Slave address
#define hw__twia_gce			_cb1, ar, 1, 0		// General Call Enable

#define hw__twia_slam			_cb1, amr, 7, 1		// Slave address mask

/*	Values for CR
 */
#define _hw_twia_cr_ifenstart		0xA4
#define _hw_twia_cr_ifenstartie		0xA5
#define _hw_twia_cr_ifen		0x84
#define _hw_twia_cr_ifenie		0x85
#define _hw_twia_cr_ifenstop		0x94
#define _hw_twia_cr_ifenstopie		0x95
#define _hw_twia_cr_ifenack		0xC4
#define _hw_twia_cr_ifenackie		0xC5


/**
 * @page atmelavr_twia
 * @par Interrupts
 *
 * Class `_twia` objects can trigger the following IRQs:
 *
 *  * `twi0`
 */

#if !defined __ASSEMBLER__

/*  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r8_t	br ;
  hwa_r8_t	cr ;
  hwa_r8_t	sr ;
  hwa_r8_t	ar ;
  hwa_r8_t	amr ;
} hwa_twia_t ;

#endif
