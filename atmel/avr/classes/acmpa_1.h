
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Analog Comparator
 */

/**
 * @page atmelavr_acmpa Class _acmpa: analog comparator
 *
 * A class `_acmpa` object is an analog comparator.
 *
 * It is used in:
 *
 * * @ref attinyx4 : `acmp0`
 * * @ref atmegax8 : `acmp0`
 */
#define _hw_class__acmpa

/**
 * @page atmelavr_acmpa
 * @par Interrupts
 *
 * Class `_acmpa` objects can trigger the following IRQs:
 *
 *  * `OBJECT_NAME`: comparator output event
 */

/*	Class logical registers
 */
#define _hw_reg__acmpa_acd		_cb1, csr, 1, 7
#define _hw_reg__acmpa_acbg		_cb1, csr, 1, 6
#define _hw_reg__acmpa_aco		_cb1, csr, 1, 5
#define _hw_reg__acmpa_if		_cb1, csr, 1, 4
#define _hw_reg__acmpa_ie		_cb1, csr, 1, 3
#define _hw_reg__acmpa_acic		_cb1, csr, 1, 2
#define _hw_reg__acmpa_acis		_cb1, csr, 2, 0


#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acmpa_t ;

#endif
