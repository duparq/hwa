
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief EEPROM
 */

/**
 * @page atmelavr_eea Class _eea: EEPROM memory
 *
 * A class `_eea` object is an EEPROM memory.
 *
 * It is used in:
 *  * @ref attinyx4 : `eeprom0`
 *  * @ref attinyx5 : `eeprom0`
 *  * @ref atmegax8 : `eeprom0`
 *  * @ref atmegaxu4 : `eeprom0`
 */
#define hw_class__eea

/*	Class logical registers
 */					
#define hw__eea_pm			_cb1, cr, 2, 4
#define hw__eea_rie			_cb1, cr, 1, 3
#define hw__eea_mpe			_cb1, cr, 1, 2
#define hw__eea_pe			_cb1, cr, 1, 1
#define hw__eea_re			_cb1, cr, 1, 0
