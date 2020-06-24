
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA header file for board WeMos D1 using Espressif's ESP8266
 */

/**
 * @ingroup esp8266_boards
 * @defgroup wemosd1 WeMos D1
 * @{
 *
 * @image html wemos-d1-mini-nodemcu.jpg
 */

#ifndef HW_MODULE

/**
 * @name Board description
 * @{
 */

/**
 * Module name
 */
#define HW_MODULE			esp_wroom_02

/**
 * Module name
 */
#define HW_MODULE_ESP_WROOM_02

/**
 * Size in bytes of Flash memory installed
 */
#define HW_MODULE_FLASH_SIZE		4*1024*1024

/**
 * Size in bytes of Flash page
 */
#define HW_MODULE_FLASH_PAGE_SIZE	4096

/**
 * @name Pin definitions
 * @{
 */
#define PIN_LED				gpio2		/**< Active low */

/** @} */
/** @} */
/** @} */

#include "../common/c_types_fix.h"
#include <osapi.h>
#include <hwa/esp8266.h>
#include "../common/espmissingincludes.h"

#endif
