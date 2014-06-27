
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void hwa_begin_cores ( hwa_t *hwa )
{
  HWA_INIT(hw_core0, gimsk);
  HWA_INIT(hw_core0, gifr);
  HWA_INIT(hw_core0, mcucr);
  HWA_INIT(hw_core0, osccal);
  HWA_INIT(hw_core0, pcmsk1);
  HWA_INIT(hw_core0, gpior0);
  HWA_INIT(hw_core0, pcmsk0);
}


HW_INLINE void hwa_commit_cores ( hwa_t *hwa )
{
  hwa_commit_8( hwa->commit, &hwa->core0.gimsk, -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.gifr,  -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.mcucr, -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.osccal, -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.pcmsk1, -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.gpior0, -1 );
  hwa_commit_8( hwa->commit, &hwa->core0.pcmsk0, -1 );
}


/*	Put the MCU in sleep mode
 */
#define hwa_sleep_until_interrupt()		\
  do {						\
    hwa_write(hw_core0, se, 1);			\
    hwa_commit();				\
    __asm__ __volatile__ ( "sleep" "\n\t" :: );	\
    hwa_write(hw_core0, se, 0);			\
    hwa_commit();				\
  } while (0)
