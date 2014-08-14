
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	Analog comparator
 *
 */

/*	Initialize a acmp instance
 */
HW_INLINE void _hwa_begin_acmps ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_acmp0, csr );
}


HW_INLINE void _hwa_init_acmps ( hwa_t *hwa )
{
  _hwa_init_r8( &hwa->acmp0.csr, 0x00 );
}


HW_INLINE void _hwa_commit_acmps ( hwa_t *hwa )
{
  _hwa_commit_r8( hwa->commit, &hwa->acmp0.csr );
}
