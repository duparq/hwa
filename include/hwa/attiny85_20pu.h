
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief ATtiny85-20PU header file
 */

#ifndef HW_DEVICE

#define HW_DEVICE_ATTINY85_20PU
#define HW_DEVICE_PACKAGE_8P3

#include "../../../atmel/avr/devices/attiny85.h"

#else
#  if !defined HW_DEVICE_ATTINY85_20PU
#    error HWA header was already included for another device!
#  endif
#endif
