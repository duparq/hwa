
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA header file for board WeMos D1 using Espressif's ESP8266
 */

#ifndef HW_MODULE

#include "../common/c_types_fix.h"
#include <osapi.h>

#define HW_MODULE			esp_wroom_02
#define HW_MODULE_ESP_WROOM_02
#define HW_MODULE_FLASH_SIZE		4*1024*1024
#define HW_MODULE_FLASH_PAGE_SIZE	4096

/*	Pin definitions
 *
 *	Taken from 0B-ESP8266__Hardware_User_Guide__EN_v1.1.pdf
 */
/* #define PIN_3				gpio14 */
/* #define PIN_4				gpio12 */
/* #define PIN_5				gpio13 */
/* #define PIN_6				gpio15 */
/* #define PIN_7				gpio2  */
/* #define PIN_8				gpio0  */
/* #define PIN_10				gpio4  */
/* #define PIN_11				gpio3  */
/* #define PIN_12				gpio1  */
/* #define PIN_14				gpio5  */
/* #define PIN_17				gpio16 */

#define PIN_LED				gpio16

#include <hwa/esp8266.h>

#include "../common/espmissingincludes.h"

#endif
