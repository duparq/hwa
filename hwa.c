
#include "hwa.h"

void hwa_warn ( ) {}

/*	Include device-specific code
 */
#if ! defined __unix__
#  include HWA_STR(HWA_G2(hwa, HWA_DEVICE).c)
#endif
