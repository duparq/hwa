
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * \file
 * \brief This file includes HWA material for the target device HW_DEVICE.
 * \req HW_DEVICE must be defined.
 *
 * This file can be included once instead of hwa.h for example in the main
 * source file.
 */

#if defined HWA_CFILE
#  include "hwa.h"
#  include HWA_CFILE
#endif

#if !defined __ASSEMBLER__
/*	ISO forbids an empty translation unit
 */
void hwa_foo() {}
#endif
