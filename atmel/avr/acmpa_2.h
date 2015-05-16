
/*	Atmel AVR 16-bit analog comparator model 'a'
 *
 *	Used in:	ATtinyX4
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

HW_INLINE void __hwa_begin__acmpa ( hwa_acmpa_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _acmpa, csr  );
}

HW_INLINE void __hwa_init__acmpa ( hwa_acmpa_t *p )
{
  _hwa_set_r8(  &p->csr,  0x00 );
}

HW_INLINE void __hwa_commit__acmpa ( hwa_t *hwa, hwa_acmpa_t *p )
{
  _hwa_commit_reg_p( p, _acmpa, csr );
}
