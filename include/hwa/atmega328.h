
/* This file is part of the HWA project.
 * Copyright (c) 2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega328
 */

/**
 * @ingroup atmega328x
 *
 * Header file:
 *
 * @code
 * #include <hwa/atmega328.h>
 * @endcode
 *
 * @defgroup atmega328 ATmega328
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
 * @brief Name of the device (for the compiler/programmer)
 */
#define HW_DEVICE			atmega328

/**
 * @brief Device family
 */
#define HW_DEVICE_ATMEGA328

/**
 * @brief Signature bytes
 */
#define HW_DEVICE_SIGNATURE		0x1E,0x95,0x14

/** @} */
/** @} */


#include "atmega328x.h"
