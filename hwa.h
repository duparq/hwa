
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA global include file
 *
 * HWA definitions are spread over two layers:
 *
 * - The first layer (hwa_l1_*.h ) contains the definitions of
 * "synchronous" functions accessing the real hardware registers directly. It
 * also contains the declarations of the structures used by the second layer.
 *
 * - The second layer (hwa_l2_*.h ) contains the definitions of the
 * global HWA structure that virtualizes the hardware and that is used by all
 * the "advanced" or "asynchronous" functions also declared in these files.
 *
 * \req HW_DEVICE must be defined.
 *
 * \defgroup exp 	Macros that expand arguments for other macros.
 * \defgroup global	Global HWA definitions
 * \defgroup macro	General-purpose macro definitions
 */

#ifndef _HWA_H_
#define _HWA_H_

#ifndef HW_DEVICE
#  error "HW_DEVICE not defined."
#endif


/**
 * \brief	Set external system clock speed to 0 if none specified.
 * \ingroup	global
 */
#ifndef HW_XSOHZ
#  define HW_XSOHZ	0
#endif

#include "hwa__1.h"


#if !defined __ASSEMBLER__
struct hwa_t ;
#  include "hwa__2.h"
#endif

#endif /* _HWA_H_ */
