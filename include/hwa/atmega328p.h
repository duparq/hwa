
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega328P
 */

/**
 * @ingroup atmega328x
 *
 * Header file:
 *
 * @code
 * #include <hwa/atmega328p.h>
 * @endcode
 *
 * @defgroup atmega328p ATmega328P
 * @{
 *
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name.
 *
 * @{
 */
  
/**
 *  Name of the device (for the compiler/programmer)
 */
#define HW_DEVICE			atmega328p

/**
 *  Device family
 */
#define HW_DEVICE_ATMEGA328P

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x95,0x0F

/** @} */
/** @} */


#include "atmega328x.h"
