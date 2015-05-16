
/*	Target
 */
#include "targets/attiny84.h"
#include <hwa.h>


int main ( )
{
  /* hw_xpr(foo1, foo2); */
  /* hw_xpr(core0, foo2); */
  /* hw_xpr(core0, mcusr); */

  /* HW_GNRC(f,foo1, foo2); */
  /* HW_GNRC(f,core0, foo2); */
  /* HW_GNRC(f,core0, mcusr); */
  /* HW_GNRC(f,core0, porf); */

  /* hw_reg(foo1, foo2); */
  /* hw_reg(core0, foo2); */
  /* hw_reg(core0, mcusr); */
  /* hw_reg(core0, porf); */

  //  uint8_t x = hw_read(hw_reg(foo1, foo2));
  //  hw_read(hw_reg(core0, foo2));
  hw_read(hw_reg(core0, mcusr));
  hw_read_reg(core0, mcusr);

  //  _hw_read(hw_reg(core0, mcusr));
  /* hw_reg(core0,mcusr); */
  /* hw_reg(core0,porf); */

  /* _hw_reg(core0,mcusr); */
  /* _hw_reg(core0,porf); */

  _hw_read_reg(core0, mcusr);

  /* hw_read_reg(foo1, foo2); */
  /* hw_read_reg(core0, foo2); */
  /* hw_read_reg(core0, mcusr); */

  /* hw_write_reg(foo); */
  /* hw_write_reg(foo1, foo2); */
  /* hw_write_reg(core0, mcusr); */
  /* hw_write_reg(core0, foo); */
  /* hw_write_reg(core0, mcusr); */
  /* hw_write_reg(core0, mcusr, 0); */

  /* hw_write(_hw_xpb(core0, mcusr),0); */

  //  hw_errorx( _Static_assert(0, "HWA: " "`""foo1""` is not a HWA object") );

  //  hwa_config( pin_pa5, direction, output );

  uint8_t s = _hw_read_reg(core0,sreg);

  uint16_t MCUSR = hw_addr(hw_reg(core0, mcusr));

  //  hw_sub(foo, foo);
  /* hw_sub(counter0, foo); */
  /* hw_sub(counter0, compare0); */

  //  _hwa_config( pin_pa7, direction, output );
}
