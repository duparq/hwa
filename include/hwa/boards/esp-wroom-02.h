
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA header file for module ESP-WROOM-02 using Espressif's ESP8266
 */

/**
 * @ingroup esp8266_boards
 * @defgroup espwroom02 ESP-WROOM-02
 * @{
 *
 * @image html esp-wroom-02.webp
 */

#ifndef HW_MODULE

#include "../common/c_types_fix.h"
#include <osapi.h>


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
 *
 * From 0B-ESP8266__Hardware_User_Guide__EN_v1.1.pdf.
 *
 * @{
 */
#define PIN_3				gpio14	///< X
#define PIN_4				gpio12	///< X
#define PIN_5				gpio13	///< X
#define PIN_6				gpio15	///< X
#define PIN_7				gpio2	///< X
#define PIN_8				gpio0	///< X
#define PIN_10				gpio4	///< X
#define PIN_11				gpio3	///< X
#define PIN_12				gpio1	///< X
#define PIN_14				gpio5	///< X
#define PIN_17				gpio16	///< X

/** @} */
/** @} */
/** @} */


#include <hwa/esp8266.h>

#include "../common/espmissingincludes.h"

#endif
