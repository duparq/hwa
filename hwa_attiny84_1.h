
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/** \brief Target device
 */
#define HW_DEVICE_ATTINY84

/** \brief Flash size
 */
#define HW_DEVICE_FLASHSIZE	8192

/** \brief Flash size
 */
#define HW_DEVICE_PAGESIZE	64

/** \brief EEPROM size
 */
#define HW_DEVICE_EEPROMSIZE	512

/** \brief RAM size
 */
#define HW_DEVICE_RAMSIZE	512

#define HW_DEVICE_NVECTORS	17
#define HW_DEVICE_RAMSTART	0x0060

#define HW_DEVICE_SIGNATURE	0x1E,0x93,0x0C

#include "hwa_attinyx4_1.h"
