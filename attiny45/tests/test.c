
#include "hwa.h"

#define XSO_HZ	16000000
#define SYS_HZ	16000000
//#define RAM


int main ( int ac __attribute__((unused)), char **av __attribute__((unused)))
{
/* #if defined RAM */
/*   hwa_begin(); */
/*   hwa_core_reset(); */
/*   hwa_core_set_xso_hz(XSO_HZ); */
/*   hwa_core_set_sys_hz(72000000); */
/*   /\* hwa_core_set_ahb_hz(72000000); *\/ */
/*   /\* hwa_core_set_apb1_hz(36000000); *\/ */
/*   /\* hwa_core_set_apb2_hz(72000000); *\/ */
/*   hwa_nocommit(); */
/*   hwa_core_set_sys_hz(SYS_HZ); */
/*   hwa_core_set_ahb_hz(SYS_HZ); */
/*   hwa_core_set_apb1_hz(SYS_HZ); */
/*   hwa_core_set_apb2_hz(SYS_HZ); */
/* #else */
/*   hwa_begin(RESET); */
/*   hwa_core_set_xso_hz(XSO_HZ); */
/*   hwa_core_set_sys_hz(SYS_HZ); */
/* #endif */

  hwa_begin(RESET);
  hwa_core_set_xso_hz(XSO_HZ);
  hwa_core_set_sys_hz(SYS_HZ);

  hwa_timer_set_mode(   HWA_TIMER0, NORMAL );
  hwa_timer_set_clkhz(  HWA_TIMER0, SYS_HZ/8 );
  hwa_timer_set_period( HWA_TIMER0, 128   ); /* À revoir */

  hwa_commit();

  return 0 ;
}
