
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*
 *	ATtinyX4 core & int0
 */


/*	Class & methods
 */
#define hw_class_eeprom
#define HW_POP_eeprom(c,n,i,a,...)	__VA_ARGS__


/*	Instance	        class, name, id, address
 */
#define hw_eeprom0		eeprom, eeprom0, 1000, 0


/*	Class regs		class, rw, ra, rwm, rfm
 */
#define hw_eeprom_arh		crg,  8, 0x3F,   0x01, 0x00
#define hw_eeprom_arl		crg,  8, 0x3E,   0xFF, 0x00
#define hw_eeprom_ar		crg, 16, 0x3E, 0x01FF, 0x00
#define hw_eeprom_dr		crg,  8, 0x3D,   0xFF, 0x00
#define hw_eeprom_cr		crg,  8, 0x3C,   0x3F, 0x00

#define hw_eeprom_pm		cb1, cr, 2, 4
#define hw_eeprom_rie		cb1, cr, 1, 3
#define hw_eeprom_mpe		cb1, cr, 1, 2
#define hw_eeprom_pe		cb1, cr, 1, 1
#define hw_eeprom_re		cb1, cr, 1, 0

/*
 *	No HWA declaration.
 */
