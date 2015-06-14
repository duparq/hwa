
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR analog comparator model 'b'
 *
 *	Used in: ATmegaX8
 *
 */

/**
 * @page atmelavr_acmpb Class _acmpb: analog comparator
 *
 * A class `_acmpb` object is an analog comparator.
 *
 * `_acmpb` is the same as `_acmpa` except that it does not drive the AD
 * multiplexer itself.
 */
#define _hw_class__acmpb

#define _hw__acmpb_acd			_cb1, csr, 1, 7
#define _hw__acmpb_acbg			_cb1, csr, 1, 6
#define _hw__acmpb_aco			_cb1, csr, 1, 5
#define _hw__acmpb_aci			_cb1, csr, 1, 4
#define _hw__acmpb_acie			_cb1, csr, 1, 3
#define _hw__acmpb_acic			_cb1, csr, 1, 2
#define _hw__acmpb_acis			_cb1, csr, 2, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r8_t csr ;
  hwa_r8_t did ;
} hwa_acmpb_t ;

#endif
