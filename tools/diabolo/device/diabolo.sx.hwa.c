
/* -*- c -*- */

//#include "config.attiny84.h"
//#include "config.atmega328p.h"
#include "config.attiny85.h"
#include <hwa.h>

#if defined HW_DEVICE_ATMELAVR
#  include "diabolo-atmelavr.sx"
#else
#  error Device other than Atmel AVR is not supported
#endif
HW_DEVICE_FLASH_SIZE
HW_DEVICE_FUSE_EB
HW_DEVICE_FUSE_HB
HW_DEVICE_FUSE_LB
HW_DEVICE
