
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA header file for board WeMos D1 using Espressif's ESP8266
 */

#ifndef HW_MODULE

#define HW_MODULE			esp_wroom_02
#define HW_MODULE_ESP_WROOM_02
#define HW_MODULE_FLASH_SIZE		4*1024*1024
#define HW_MODULE_FLASH_PAGE_SIZE	4096

#define PIN_LED				gpio2		// Active low

#include "../common/c_types_fix.h"
#include <osapi.h>
#include <hwa/esp8266.h>
#include "../common/espmissingincludes.h"

#endif
