
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Definitions common to all Atmel AVR devices that do not produce C code
 */

#include "../../hwa/hwa_1.h"

/**
 * @ingroup public_atmelavr_def
 * @brief Defined for all Atmel AVR devices
 * @hideinitializer
 */
#define HW_DEVICE_ATMELAVR

#if !defined DOXYGEN
#  define HW_DEVICE_VENDOR	atmel
#  define HW_DEVICE_ARCH	avr
#endif


/*  Address of a memory definition
 */
#define _HW_A__m1(o,a,r,rc,ra,...)		(a+ra)
#define _HW_A__r32(ra,rwm,rfm,o,c,a,r)		(a+ra)


/*  _hw_isr_(...): address (vector) of ISR
 *
 *	FIXME: should name it _vector(...)
 */
#if defined __ASSEMBLER__
#  define _HW_ISR_(vector, ...)			__vector_##vector
#endif
