
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__c8a_1.h"
#include "hwa_atmelavr__c16a_1.h"
//#include "hwa_atmelavr__ocua_1.h"
#include "hwa_atmelavr__icua_1.h"


/*	Instance			class, name, id, address
 */
#define hw_counter0			_c8a, counter0, 400, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_counter0_compare0	irq,  9, counter0, ociea, ocfa
#define hw_irq_counter0_compare1	irq, 10, counter0, ocieb, ocfb
#define hw_irq_counter0_overflow	irq, 11, counter0, oie, ov

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__c8a_ocrb			crg, 8, 0x5C, 0xFF, 0x00
#define hw__c8a_compare1		crg, 8, 0x5C, 0xFF, 0x00
#define hw__c8a_imsk			crg, 8, 0x59, 0x07, 0x00
#define hw__c8a_ifr			crg, 8, 0x58, 0x07, 0x07
#define hw__c8a_ocra			crg, 8, 0x56, 0xFF, 0x00
#define hw__c8a_compare0		crg, 8, 0x56, 0xFF, 0x00
#define hw__c8a_ccrb			crg, 8, 0x53, 0xCF, 0x00
#define hw__c8a_count			crg, 8, 0x52, 0xFF, 0x00
#define hw__c8a_ccra			crg, 8, 0x50, 0xF3, 0x00


/*	Counter0 compare output units
 *
 *	Instance			class, name, id, counter, ocn, ion
 */
#define hw_counter0_compare0		_ocua, counter0_compare0, 401, counter0, 0, pin_pb2
#define hw_counter0_compare1		_ocua, counter0_compare1, 402, counter0, 1, pin_pa7


/*	Instance			class, name, id, address
 */
#define hw_counter1			_c16a, counter1, 410, 0

/*	Interrupts			class, vector, controller, enable bit, flag bit
 */
#define hw_irq_counter1_capture0	irq, 5, counter1, icie, icf
#define hw_irq_counter1_compare0	irq, 6, counter1, ociea, ocfa
#define hw_irq_counter1_compare1	irq, 7, counter1, ocieb, ocfb
#define hw_irq_counter1_overflow	irq, 8, counter1, oie, ov

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__c16a_ccra			crg,  8, 0x4F, 0xF3,   0x00
#define hw__c16a_ccrb			crg,  8, 0x4E, 0xDF,   0x00
#define hw__c16a_ccrc			crg,  8, 0x42, 0xC0,   0x00
#define hw__c16a_count			crg, 16, 0x4C, 0xFFFF, 0x0000
#define hw__c16a_countl			crg,  8, 0x4C, 0xFF,   0x00
#define hw__c16a_counth			crg,  8, 0x4D, 0xFF,   0x00
#define hw__c16a_ocra			crg, 16, 0x4A, 0xFFFF, 0x0000
#define hw__c16a_compare0		crg, 16, 0x4A, 0xFFFF, 0x0000
#define hw__c16a_ocral			crg,  8, 0x4A, 0xFF,   0x00
#define hw__c16a_ocrah			crg,  8, 0x4B, 0xFF,   0x00
#define hw__c16a_ocrb			crg, 16, 0x48, 0xFFFF, 0x0000
#define hw__c16a_compare1		crg, 16, 0x48, 0xFFFF, 0x0000
#define hw__c16a_ocrbl			crg,  8, 0x48, 0xFF,   0x00
#define hw__c16a_ocrbh			crg,  8, 0x49, 0xFF,   0x00
#define hw__c16a_icr			crg, 16, 0x44, 0xFFFF, 0x0000
#define hw__c16a_capture0		crg, 16, 0x44, 0xFFFF, 0x0000
#define hw__c16a_icrl			crg,  8, 0x44, 0xFF,   0x00
#define hw__c16a_icrh			crg,  8, 0x45, 0xFF,   0x00
#define hw__c16a_imsk			crg,  8, 0x2C, 0x27,   0x00
#define hw__c16a_ifr			crg,  8, 0x2B, 0x27,   0x27

#define hw__c16a_acic			irg, hw_acmp0, acic


/*	Counter1 compare output units	class, name, id, counter, channel, io
 */
#define hw_counter1_compare0	_ocua, counter1_compare0, 411, counter1, 0, pin_pa6 /* dil#7 */
#define hw_counter1_compare1	_ocua, counter1_compare1, 412, counter1, 1, pin_pa5 /* dil#8 */


/*	Counter1 input capture unit	class, name, id, counter, reg, io
 */
#define hw_counter1_capture0	_icua, counter1_capture0, 413, counter1, icr, pin_pa7 /* dil#6 */
