
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions for Atmel AVR analog comparator 'a' that do not produce C code
 *
 *	Used in: ATtinyX4
 *
 */


/**
 * @page atmelavr_acmpa Class _acmpa: analog comparator
 *
 * A class `_acmpa` object is an analog comparator.
 */
#define _hw_class__acmpa


#define _hw__acmpa_acd			_cb1, csr, 1, 7
#define _hw__acmpa_acbg			_cb1, csr, 1, 6
#define _hw__acmpa_aco			_cb1, csr, 1, 5
#define _hw__acmpa_aci			_cb1, csr, 1, 4
#define _hw__acmpa_acie			_cb1, csr, 1, 3
#define _hw__acmpa_acic			_cb1, csr, 1, 2
#define _hw__acmpa_acis			_cb1, csr, 2, 0


#if !defined __ASSEMBLER__

typedef struct { hwa_r8_t csr ; } hwa_acmpa_t ;

#endif
