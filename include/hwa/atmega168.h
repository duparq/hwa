
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega168
 */

/**
 * @ingroup atmega168x
 *
 * Header file:
 *
 * @code
 * #include <hwa/atmega168.h>
 * @endcode
 *
 * @defgroup atmega168 ATmega168
 * @{
 */

/**
 * @name Target device description
 *
 * These definitions are computed by HWA from the target device name.
 *
 * @{
 */
  
/**
 *  Name of the device (for the compiler/programmer)
 */
#define HW_DEVICE			atmega168

/**
 *  Device family
 */
#define HW_DEVICE_ATMEGA168

/**
 *  Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x94,0x06

/** @} */
/** @} */


#include "atmega168x.h"
