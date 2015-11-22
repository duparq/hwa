
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief HWA header file for module ESP-WROOM-02 using Espressif's ESP8266
 */

#ifndef HW_MODULE

#include "c_types_fix.h"
#include <osapi.h>

#define HW_MODULE			esp_wroom_02
#define HW_MODULE_ESP_WROOM_02
#define HW_MODULE_FLASH_SIZE		4*1024*1024
#define HW_MODULE_FLASH_PAGE_SIZE	4096

/*	Pin definitions
 *
 *	Taken from 0B-ESP8266__Hardware_User_Guide__EN_v1.1.pdf
 */
#define PIN_3				hw_pin_gpio14
#define PIN_4				hw_pin_gpio12
#define PIN_5				hw_pin_gpio13
#define PIN_6				hw_pin_gpio15
#define PIN_7				hw_pin_gpio2 
#define PIN_8				hw_pin_gpio0 
#define PIN_10				hw_pin_gpio4 
#define PIN_11				hw_pin_gpio3 
#define PIN_12				hw_pin_gpio1 
#define PIN_14				hw_pin_gpio5 
#define PIN_17				hw_pin_gpio16

#include <hwa/esp8266.h>

#include "espmissingincludes.h"

#endif
