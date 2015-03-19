
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__c8a_1.h"
//#include "hwa_atmelavr__ocua_1.h"


/*	Instance			class, name, id, address
 */
#define hw_counter0			_c8a, counter0, 400, 0

/*	Interrupts			class, vad, controller, enable bit, flag bit
 */
#define hw_irq_counter0_compare0		irq, 14, counter0, ociea, ocfa
#define hw_irq_counter0_compare1		irq, 15, counter0, ocieb, ocfb
#define hw_irq_counter0_overflow	irq, 16, counter0, oie, ov

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__c8a_ccra			crg, 8, 0x44, 0xF3, 0x00
#define _hw__c8a_ccrb			crg, 8, 0x45, 0xCF, 0x00
#define _hw__c8a_count			crg, 8, 0x46, 0xFF, 0x00
#define _hw__c8a_ocra			crg, 8, 0x47, 0xFF, 0x00
#define _hw__c8a_compare0			crg, 8, 0x47, 0xFF, 0x00
#define _hw__c8a_ocrb			crg, 8, 0x48, 0xFF, 0x00
#define _hw__c8a_compare1			crg, 8, 0x48, 0xFF, 0x00
#define _hw__c8a_imsk			crg, 8, 0x6E, 0x07, 0x00
#define _hw__c8a_ifr			crg, 8, 0x35, 0x07, 0x07


/*	Counter0 compare output units
 *
 *	Instance			class, name, id, counter, ocn, ion
 */
#define hw_counter0_compare0		_ocua, counter0_compare0, 401, counter0, 0, pin_pd6
#define hw_counter0_compare1		_ocua, counter0_compare1, 402, counter0, 1, pin_pd5



#include "hwa_atmelavr__c16a_1.h"


/*	Instance			class, name, id, address
 */
#define hw_counter1			_c16a, counter1, 410, 0

/*	Interrupts			class, vad, controller, enable bit, flag bit
 */
#define hw_irq_counter1_capture0		irq, 10, counter1, icie,  icf
#define hw_irq_counter1_compare0		irq, 11, counter1, ociea, ocfa
#define hw_irq_counter1_compare1		irq, 12, counter1, ocieb, ocfb
#define hw_irq_counter1_overflow	irq, 13, counter1, oie,   ov

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define _hw__c16a_ccra			crg,  8, 0x80, 0xF3,   0x00
#define _hw__c16a_ccrb			crg,  8, 0x81, 0xDF,   0x00
#define _hw__c16a_ccrc			crg,  8, 0x82, 0xC0,   0x00
#define _hw__c16a_count			crg, 16, 0x84, 0xFFFF, 0x0000
#define _hw__c16a_countl			crg,  8, 0x84, 0xFF,   0x00
#define _hw__c16a_counth			crg,  8, 0x85, 0xFF,   0x00
#define _hw__c16a_ocra			crg, 16, 0x88, 0xFFFF, 0x0000
#define _hw__c16a_compare0		crg, 16, 0x88, 0xFFFF, 0x0000
#define _hw__c16a_ocral			crg,  8, 0x88, 0xFF,   0x00
#define _hw__c16a_ocrah			crg,  8, 0x89, 0xFF,   0x00
#define _hw__c16a_ocrb			crg, 16, 0x8A, 0xFFFF, 0x0000
#define _hw__c16a_compare1		crg, 16, 0x8A, 0xFFFF, 0x0000
#define _hw__c16a_ocrbl			crg,  8, 0x8A, 0xFF,   0x00
#define _hw__c16a_ocrbh			crg,  8, 0x8B, 0xFF,   0x00
#define _hw__c16a_icr			crg, 16, 0x86, 0xFFFF, 0x0000
#define _hw__c16a_capture0			crg, 16, 0x86, 0xFFFF, 0x0000
#define _hw__c16a_icrl			crg,  8, 0x86, 0xFF,   0x00
#define _hw__c16a_icrh			crg,  8, 0x87, 0xFF,   0x00
#define _hw__c16a_imsk			crg,  8, 0x6F, 0x27,   0x00
#define _hw__c16a_ifr			crg,  8, 0x36, 0x27,   0x27

#define _hw__c16a_acic			irg, hw_acmp0, acic


/*	Counter1 compare output units	class, name, id, counter, channel, io
 */
#define hw_counter1_compare0		_ocua, counter1_compare0, 411, counter1, 0, pin_pb1
#define hw_counter1_compare1		_ocua, counter1_compare1, 412, counter1, 1, pin_pb2


/*	Counter1 input capture unit	class, name, id, counter, reg, io
 */
#define hw_counter1_capture0		_icua, counter1_capture0, 413, counter1, icr, pin_pb0
#define hw_counter1_input		_icua, counter1_input,  413, counter1, icr, pin_pb0
