
#include "hwa.h"

/*	Include device-specific definitions from "hwa_<device>.h"
 */
#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif

#if defined HWA_DBG
#  include "hwa_dbg.c"
#endif

#include HWA_STR(HWA_IP(HWA_DEVICE).c)
