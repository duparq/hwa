
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*
 * @file
 * @brief This file is not used yet.
 *
 * This file is intended to be included once instead of hwa.h for example in the
 * main source file in order to make additionnal HWA material available.
 */

#if !defined __ASSEMBLER__

#if defined HWA_CFILE
#  include "hwa.h"
#  include HWA_CFILE
#endif

/*	ISO forbids an empty translation unit
 */
void hw_foo() {}

#endif /* !defined __ASSEMBLER__ */
