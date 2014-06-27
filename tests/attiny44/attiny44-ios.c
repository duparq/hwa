
#include <hwa.h>

void test_hw_config_pa0_input() { hw_config(hw_pin_pa0, input); }
void test_hw_config_pa1_input() { hw_config(hw_pin_pa1, input); }
void test_hw_config_pa2_input() { hw_config(hw_pin_pa2, input); }
void test_hw_config_pa3_input() { hw_config(hw_pin_pa3, input); }
void test_hw_config_pa4_input() { hw_config(hw_pin_pa4, input); }
void test_hw_config_pa5_input() { hw_config(hw_pin_pa5, input); }
void test_hw_config_pa6_input() { hw_config(hw_pin_pa6, input); }
void test_hw_config_pa7_input() { hw_config(hw_pin_pa7, input); }

void test_hw_config_pb0_input() { hw_config(hw_pin_pb0, input); }
void test_hw_config_pb1_input() { hw_config(hw_pin_pb1, input); }
void test_hw_config_pb2_input() { hw_config(hw_pin_pb2, input); }
void test_hw_config_pb3_input() { hw_config(hw_pin_pb3, input); }


void test_hw_config_pa0_input_pullup() { hw_config(hw_pin_pa0, input_pullup); }
void test_hw_config_pa1_input_pullup() { hw_config(hw_pin_pa1, input_pullup); }
void test_hw_config_pa2_input_pullup() { hw_config(hw_pin_pa2, input_pullup); }
void test_hw_config_pa3_input_pullup() { hw_config(hw_pin_pa3, input_pullup); }
void test_hw_config_pa4_input_pullup() { hw_config(hw_pin_pa4, input_pullup); }
void test_hw_config_pa5_input_pullup() { hw_config(hw_pin_pa5, input_pullup); }
void test_hw_config_pa6_input_pullup() { hw_config(hw_pin_pa6, input_pullup); }
void test_hw_config_pa7_input_pullup() { hw_config(hw_pin_pa7, input_pullup); }

void test_hw_config_pb0_input_pullup() { hw_config(hw_pin_pb0, input_pullup); }

void test_hwa_config_pb0_input_pullup_1 ( )
{
  hwa_begin();
  hwa_config(hw_pin_pb0, input_pullup);
  hwa_commit();
}

void test_hw_config_pb1_input_pullup() { hw_config(hw_pin_pb1, input_pullup); }
void test_hw_config_pb2_input_pullup() { hw_config(hw_pin_pb2, input_pullup); }
void test_hw_config_pb3_input_pullup() { hw_config(hw_pin_pb3, input_pullup); }


void test_hw_config_pa0_output() { hw_config(hw_pin_pa0, output); }
void test_hw_config_pa1_output() { hw_config(hw_pin_pa1, output); }
void test_hw_config_pa2_output() { hw_config(hw_pin_pa2, output); }
void test_hw_config_pa3_output() { hw_config(hw_pin_pa3, output); }
void test_hw_config_pa4_output() { hw_config(hw_pin_pa4, output); }
void test_hw_config_pa5_output() { hw_config(hw_pin_pa5, output); }
void test_hw_config_pa6_output() { hw_config(hw_pin_pa6, output); }
void test_hw_config_pa7_output() { hw_config(hw_pin_pa7, output); }

void test_hw_config_pb0_output() { hw_config(hw_pin_pb0, output); }
void test_hw_config_pb1_output() { hw_config(hw_pin_pb1, output); }
void test_hw_config_pb2_output() { hw_config(hw_pin_pb2, output); }
void test_hw_config_pb3_output() { hw_config(hw_pin_pb3, output); }


void test_hw_read_pa0() { hw_read(hw_pin_pa0); }
void test_hw_read_pa1() { hw_read(hw_pin_pa1); }
void test_hw_read_pa2() { hw_read(hw_pin_pa2); }
void test_hw_read_pa3() { hw_read(hw_pin_pa3); }
void test_hw_read_pa4() { hw_read(hw_pin_pa4); }
void test_hw_read_pa5() { hw_read(hw_pin_pa5); }
void test_hw_read_pa6() { hw_read(hw_pin_pa6); }
void test_hw_read_pa7() { hw_read(hw_pin_pa7); }

void test_hw_read_pb0() { hw_read(hw_pin_pb0); }
void test_hw_read_pb1() { hw_read(hw_pin_pb1); }
void test_hw_read_pb2() { hw_read(hw_pin_pb2); }
void test_hw_read_pb3() { hw_read(hw_pin_pb3); }


/*	Write 1 pin
 */
void test_hw_write_pa0_0() { hw_write(hw_pin_pa0, 0); }
void test_hw_write_pa1_0() { hw_write(hw_pin_pa1, 0); }
void test_hw_write_pa2_0() { hw_write(hw_pin_pa2, 0); }
void test_hw_write_pa3_0() { hw_write(hw_pin_pa3, 0); }
void test_hw_write_pa4_0() { hw_write(hw_pin_pa4, 0); }
void test_hw_write_pa5_0() { hw_write(hw_pin_pa5, 0); }
void test_hw_write_pa6_0() { hw_write(hw_pin_pa6, 0); }
void test_hw_write_pa7_0() { hw_write(hw_pin_pa7, 0); }

void test_hw_write_pb0_0() { hw_write(hw_pin_pb0, 0); }
void test_hw_write_pb1_0() { hw_write(hw_pin_pb1, 0); }
void test_hw_write_pb2_0() { hw_write(hw_pin_pb2, 0); }
void test_hw_write_pb3_0() { hw_write(hw_pin_pb3, 0); }

void test_hw_write_pa0_1() { hw_write(hw_pin_pa0, 1); }
void test_hw_write_pa1_1() { hw_write(hw_pin_pa1, 1); }
void test_hw_write_pa2_1() { hw_write(hw_pin_pa2, 1); }
void test_hw_write_pa3_1() { hw_write(hw_pin_pa3, 1); }
void test_hw_write_pa4_1() { hw_write(hw_pin_pa4, 1); }
void test_hw_write_pa5_1() { hw_write(hw_pin_pa5, 1); }
void test_hw_write_pa6_1() { hw_write(hw_pin_pa6, 1); }
void test_hw_write_pa7_1() { hw_write(hw_pin_pa7, 1); }

void test_hw_write_pb0_1() { hw_write(hw_pin_pb0, 1); }
void test_hw_write_pb1_1() { hw_write(hw_pin_pb1, 1); }
void test_hw_write_pb2_1() { hw_write(hw_pin_pb2, 1); }
void test_hw_write_pb3_1() { hw_write(hw_pin_pb3, 1); }


#define hw_io	io	// Anonymous io pin

/*	Write 2 consecutive pins
 */
void test_hw_write_pa01_0() { hw_write(io, io, hw_porta, 2, 0, 0); }
void test_hw_write_pa12_0() { hw_write(io, io, hw_porta, 2, 1, 0); }
void test_hw_write_pa23_0() { hw_write(io, io, hw_porta, 2, 2, 0); }
void test_hw_write_pa34_0() { hw_write(io, io, hw_porta, 2, 3, 0); }
void test_hw_write_pa45_0() { hw_write(io, io, hw_porta, 2, 4, 0); }
void test_hw_write_pa56_0() { hw_write(io, io, hw_porta, 2, 5, 0); }
void test_hw_write_pa67_0() { hw_write(io, io, hw_porta, 2, 6, 0); }
void test_hw_write_pa78_0() { hw_write(io, io, hw_porta, 2, 7, 0); }

void test_hw_write_pb01_0() { hw_write(io, io, hw_porta, 2, 0, 0); }
void test_hw_write_pb12_0() { hw_write(io, io, hw_porta, 2, 1, 0); }
void test_hw_write_pb23_0() { hw_write(io, io, hw_porta, 2, 2, 0); }

void test_hw_write_pa01_1() { hw_write(io, io, hw_porta, 2, 0, 1); }
void test_hw_write_pa12_1() { hw_write(io, io, hw_porta, 2, 1, 1); }
void test_hw_write_pa23_1() { hw_write(io, io, hw_porta, 2, 2, 1); }
void test_hw_write_pa34_1() { hw_write(io, io, hw_porta, 2, 3, 1); }
void test_hw_write_pa45_1() { hw_write(io, io, hw_porta, 2, 4, 1); }
void test_hw_write_pa56_1() { hw_write(io, io, hw_porta, 2, 5, 1); }
void test_hw_write_pa67_1() { hw_write(io, io, hw_porta, 2, 6, 1); }
void test_hw_write_pa78_1() { hw_write(io, io, hw_porta, 2, 7, 1); }

void test_hw_write_pb01_1() { hw_write(io, io, hw_porta, 2, 0, 1); }
void test_hw_write_pb12_1() { hw_write(io, io, hw_porta, 2, 1, 1); }
void test_hw_write_pb23_1() { hw_write(io, io, hw_porta, 2, 2, 1); }

void test_hw_write_pa01_2() { hw_write(io, io, hw_porta, 2, 0, 2); }
void test_hw_write_pa12_2() { hw_write(io, io, hw_porta, 2, 1, 2); }
void test_hw_write_pa23_2() { hw_write(io, io, hw_porta, 2, 2, 2); }
void test_hw_write_pa34_2() { hw_write(io, io, hw_porta, 2, 3, 2); }
void test_hw_write_pa45_2() { hw_write(io, io, hw_porta, 2, 4, 2); }
void test_hw_write_pa56_2() { hw_write(io, io, hw_porta, 2, 5, 2); }
void test_hw_write_pa67_2() { hw_write(io, io, hw_porta, 2, 6, 2); }
void test_hw_write_pa78_2() { hw_write(io, io, hw_porta, 2, 7, 2); }

void test_hw_write_pb01_2() { hw_write(io, io, hw_porta, 2, 0, 2); }
void test_hw_write_pb12_2() { hw_write(io, io, hw_porta, 2, 1, 2); }
void test_hw_write_pb23_2() { hw_write(io, io, hw_porta, 2, 2, 2); }

void test_hw_write_pa01_3() { hw_write(io, io, hw_porta, 2, 0, 3); }
void test_hw_write_pa12_3() { hw_write(io, io, hw_porta, 2, 1, 3); }
void test_hw_write_pa23_3() { hw_write(io, io, hw_porta, 2, 2, 3); }
void test_hw_write_pa34_3() { hw_write(io, io, hw_porta, 2, 3, 3); }
void test_hw_write_pa45_3() { hw_write(io, io, hw_porta, 2, 4, 3); }
void test_hw_write_pa56_3() { hw_write(io, io, hw_porta, 2, 5, 3); }
void test_hw_write_pa67_3() { hw_write(io, io, hw_porta, 2, 6, 3); }
void test_hw_write_pa78_3() { hw_write(io, io, hw_porta, 2, 7, 3); }

void test_hw_write_pb01_3() { hw_write(io, io, hw_porta, 2, 0, 3); }
void test_hw_write_pb12_3() { hw_write(io, io, hw_porta, 2, 1, 3); }
void test_hw_write_pb23_3() { hw_write(io, io, hw_porta, 2, 2, 3); }



void test_hwa_config_pb0_output()
{
  hwa_begin();
  hwa_config(hw_pin_pb0, output);
  hwa_commit();
}


void test_hwa_write_pb0_1()
{
  hwa_begin();
  hwa_write(hw_pin_pb0, 1);
  hwa_commit();
}

void test_hw_toggle_pb0()
{
  hw_toggle(hw_pin_pb0);
}
