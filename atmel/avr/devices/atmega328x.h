
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Atmel AVR ATmega328 / ATmega328P
 *
 *  Differences between versions:
 *    brown-out detector can be disabled by software in P versions
 */
#define HW_DEVICE_FLASH_SIZE				32768
#define HW_DEVICE_FLASH_PAGE_SIZE			128
#define HW_DEVICE_EEPROM_SIZE				1024
#define HW_DEVICE_EEPROM_PAGE_SIZE			4
#define HW_DEVICE_RAM_SIZE				2048
#define HW_DEVICE_RAM_START				0x0100
#define HW_DEVICE_APP_START				0x0068


#if !defined HW_DEVICE_BOOTSECTION_SIZE
#  define HW_DEVICE_BOOTSECTION_SIZE			4096
#endif
#if HW_DEVICE_BOOTSECTION_SIZE == 512
#  define HW_DEVICE_BOOTSZ				3
#elif HW_DEVICE_BOOTSECTION_SIZE == 1024
#  define HW_DEVICE_BOOTSZ				2
#elif HW_DEVICE_BOOTSECTION_SIZE == 2048
#  define HW_DEVICE_BOOTSZ				1
#elif HW_DEVICE_BOOTSECTION_SIZE == 4096
#  define HW_DEVICE_BOOTSZ				0
#else
#  error HW_DEVICE_BOOTSECTION_SIZE must be `512`, `1024`, `2048`, or `4096` (default).
#endif

/*  Default: 0xFF
 *	FIXME: there's a problem with avrdude reading/writing unprogrammed
 *	fuses of extended byte as 0 instead of 1.
 */
#define HW_DEVICE_FUSE_EB			\
  /* 0xF8 | */					\
  HW_DEVICE_BODLEVEL

/*  Default: 0xD9
 */
#define HW_DEVICE_FUSE_HB			\
  HW_DEVICE_RSTDISBL<<7 |			\
  HW_DEVICE_DWEN<<6 |				\
  HW_DEVICE_SPIEN<<5 |				\
  HW_DEVICE_WDTON<<4 |				\
  HW_DEVICE_EESAVE<<3 |				\
  HW_DEVICE_BOOTSZ<<1 |				\
  HW_DEVICE_BOOTRST

/*  Default: 0x62
 */
#define HW_DEVICE_FUSE_LB			\
  HW_DEVICE_CKDIV8<<7 |				\
  HW_DEVICE_CKOUT<<6 |				\
  HW_DEVICE_SUT10<<4 |				\
  HW_DEVICE_CKSEL31<<1 |			\
  HW_DEVICE_CKSEL0

#include "atmegax8.h"
