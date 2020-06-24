
#ifndef HWA_H
#define HWA_H

/* This file is part of the HWA project.
 * Copyright (c) 2012,2015,2020 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief ATmega328P-AU 
 */

/**
 * @ingroup atmega328p
 * @defgroup atmega328p_au ATmega328P-AU
 *
 * This header file allows using the `(pin,number)` notation:
 *
 * @code
 * #include <hwa/atmega328p_au.h>
 * @endcode
 *
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
 *  Device family
 */
#define HW_DEVICE_ATMEGA328P_AU

/**
 *  Device package
 */
#define HW_DEVICE_PACKAGE_32Q

/** @} */
/** @} */


#include "atmega328p.h"

#endif
