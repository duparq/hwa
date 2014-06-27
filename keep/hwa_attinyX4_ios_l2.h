
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr_ios_l2.h"


HW_INLINE void hwa_begin_ios ( hwa_t *hwa )
{
  HWA_INIT(hw_porta, port);
  HWA_INIT(hw_porta, ddr );
  HWA_INIT(hw_porta, didr);

  HWA_INIT(hw_portb, port);
  HWA_INIT(hw_portb, ddr );
}


HW_INLINE void hwa_commit_ios ( hwa_t *hwa )
{
  hwa_commit_8( hwa->commit, &hwa->porta.port, -1 );
  hwa_commit_8( hwa->commit, &hwa->porta.ddr,  -1 );
  hwa_commit_8( hwa->commit, &hwa->porta.didr, -1 );

  hwa_commit_8( hwa->commit, &hwa->portb.port, -1 );
  hwa_commit_8( hwa->commit, &hwa->portb.ddr,  -1 );
}
