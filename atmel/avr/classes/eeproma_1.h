
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief EEPROM
 */

/**
 * @page atmelavr_eeproma Class _eeproma: EEPROM memory
 *
 * A class `_eeproma` object is an EEPROM memory.
 *
 * It is used in:
 *  * @ref attinyx4 : `eeprom0`
 *  * @ref attinyx5 : `eeprom0`
 *  * @ref atmegax8 : `eeprom0`
 *  * @ref atmegaxu4 : `eeprom0`
 */
#define _hw_class__eeproma

/*	Class logical registers
 */					
#define _hw_reg__eeproma_pm		_cb1, cr, 2, 4
#define _hw_reg__eeproma_rie		_cb1, cr, 1, 3
#define _hw_reg__eeproma_mpe		_cb1, cr, 1, 2
#define _hw_reg__eeproma_pe		_cb1, cr, 1, 1
#define _hw_reg__eeproma_re		_cb1, cr, 1, 0
