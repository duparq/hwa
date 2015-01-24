
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_ios_2.h"


HW_INLINE void _hwa_begin_ios ( hwa_t *hwa )
{
  _hwa_begin_reg( hw_portb, port );
  _hwa_begin_reg( hw_portb, ddr  );
}


HW_INLINE void _hwa_init_ios ( hwa_t *hwa )
{
  _hwa_set_r8( &hwa->portb.port, 0x00 );
  _hwa_set_r8( &hwa->portb.ddr,  0x00 );
}


HW_INLINE void _hwa_commit_ios ( hwa_t *hwa )
{
  _hwa_commit_reg( hw_portb, port, hwa->commit );
  _hwa_commit_reg( hw_portb, ddr,  hwa->commit );
}
