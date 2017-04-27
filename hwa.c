
#include "hwa.h"


void hwa_warn ( ) {}


void __attribute__((noreturn))
hwa_exit ( HwaExitValue xv __attribute__((unused)) )
{
  hw_irq_turn(ALL, OFF);
  hw_irq_clear(ALL);
  while(1) {}
}


/*	Include device-specific definitions from "hwa_<device>.h"
 */
#ifndef HWA_DEVICE
#  error "HWA_DEVICE not defined."
#endif

#include HWA_STR(HWA_G2(hwa, HWA_DEVICE).c)
