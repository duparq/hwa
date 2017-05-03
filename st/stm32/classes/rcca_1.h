
/* This file is part of the HWA project.
 * Copyright (c) 2017 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Clocks
 */

/**
 * @page stm32_rcca Class _rcca: clocking control
 */
#define _hw_class__rcca

/*	Class registers			class, address, wm, fm
 */
//#define _hw_reg__rcca_apb2enr		_r32, 0x18, 0x0038FFFD, 0


#if !defined __ASSEMBLER__

typedef struct {
  hwa_r32_t apb2enr ;
} hwa_rcca_t ;

#endif
