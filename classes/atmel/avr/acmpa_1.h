
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */


/**
 * @page atmelavr_acmpa Class _acmpa: analog comparator
 *
 * A class `_acmpa` object is an analog comparator.
 *
 * Used in: ATtinyX4
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
