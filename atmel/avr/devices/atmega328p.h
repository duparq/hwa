
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

/*  Differences between P/non P versions:
 *    brown-out detector can be disabled by software in P versions
 */
#define HW_DEVICE_ATMEGA328P
#define HW_DEVICE_SIGNATURE		0x1E,0x95,0x0F

#include "atmega328x.h"
