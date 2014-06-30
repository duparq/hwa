
#include <hwa.h>


int main ( )
{
  hw_write(hw_counter2, count, 1);
  hw_write(hw_counter1, countx, 1);
  hw_write(hw_counter1, count, 1);
  hw_write(hw_counter1, cs, 1);
  hw_write(hw_counter1, wgm, 1);

  hw_write(hw_porta, pin, 1);
  hw_write(hw_port_a, 1);
  hw_write(hw_pin_pa0, 1);

  hwa_write(hw_counter1, count, 1);
  hwa_write(hw_counter1, cs, 1);
  hwa_write(hw_counter1, wgm, 1);

  hwa_write(hw_porta, pin, 1);
  hwa_write(hw_port_a, 1);
  hwa_write(hw_pin_pa0, 1);

  _hwa_write_pcr(z, c16a, wgm, 5);
}
