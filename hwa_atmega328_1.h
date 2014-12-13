
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/*  Differences between P/non P versions:
 *    BOD can be disabled in P versions
 */
#define HW_DEVICE_ATMEGA328
#define HW_DEVICE_FLASHSIZE	32768
#define HW_DEVICE_EEPROMSIZE	1024
#define HW_DEVICE_RAMSIZE	2048
#define HW_DEVICE_NVECTORS	26
#define HW_DEVICE_RAMSTART	0x0100
#define HW_DEVICE_SIGNATURE	0x1E,0x95,0x14

#ifndef HW_DEVICE_FUSE_EB
#  define HW_DEVICE_FUSE_EB	0xFF
#endif

#ifndef HW_DEVICE_FUSE_HB
#  define HW_DEVICE_FUSE_HB	0xD9
#endif

#ifndef HW_DEVICE_FUSE_LB
#  define HW_DEVICE_FUSE_LB	0x62
#endif

#include "hwa_atmegax8_1.h"
