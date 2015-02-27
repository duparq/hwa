
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__c8a_1.h"
#include "hwa_atmelavr__ocua_1.h"


/*	Instance			class, name, id, address
 */
#define hw_counter0			_c8a, counter0, 400, 0

/*	Interrupts			class, vad, controller, enable bit, flag bit
 */
#define hw_irq_counter0_output0		irq, 10, counter0, ociea, ocfa
#define hw_irq_counter0_output1		irq, 11, counter0, ocieb, ocfb
#define hw_irq_counter0_overflow	irq,  5, counter0, oie, ov

/*	Class registers			class, rw, ra, rwm, rfm
 */
#define hw__c8a_ccra			crg, 8, 0x4A, 0xF3, 0x00
#define hw__c8a_ccrb			crg, 8, 0x53, 0xCF, 0x00
#define hw__c8a_count			crg, 8, 0x52, 0xFF, 0x00
#define hw__c8a_ocra			crg, 8, 0x49, 0xFF, 0x00
#define hw__c8a_output0			crg, 8, 0x49, 0xFF, 0x00
#define hw__c8a_ocrb			crg, 8, 0x48, 0xFF, 0x00
#define hw__c8a_output1			crg, 8, 0x48, 0xFF, 0x00
//#define hw__c8a_imsk			crg, 8, 0x59, 0x07, 0x00 /* shared */
//#define hw__c8a_ifr			crg, 8, 0x58, 0x07, 0x07 /* shared */


/*	Registers
 */
#define hw__c8a_ocieb			irg, hw_shared0, ocieb
#define hw__c8a_ociea			irg, hw_shared0, ociea
#define hw__c8a_oie			irg, hw_shared0, oie

#define hw__c8a_ocfb			irg, hw_shared0, ocf0b
#define hw__c8a_ocfa			irg, hw_shared0, ocf0a
#define hw__c8a_ov			irg, hw_shared0, ov0


/*	Counter0 compare output units
 *
 *	Instance			class, name, id, counter, ocn, ion
 */
#define hw_counter0_output0		_ocua, counter0_output0, 401, counter0, 0, pin_pb2
#define hw_counter0_output1		_ocua, counter0_output1, 402, counter0, 1, pin_pa7
