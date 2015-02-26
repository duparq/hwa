
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */
 

#if !defined __ASSEMBLER__

typedef struct {
  intptr_t	address ;
  uint8_t	action, timeout ;
  hwa_r8_t 	csr ;
} hwa_wdog_t ;

#endif
