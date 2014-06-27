
#include <hwa.h>

#define TEST(zbegin,zcounter,zmode,ztop,zclk)				\
  void test_hwa_config##zbegin##_##zcounter##_##zmode##_##ztop##_##zclk () \
  {									\
    hwa_begin ## zbegin ();						\
      hwa_config( hw_##zcounter,					\
		  countmode,	zmode,					\
		  top,		ztop,					\
		  clock,	zclk );					\
      hwa_commit();							\
  }

TEST(_from_reset,counter1,loop_up,fixed_0xFF,none)
TEST(_from_reset,counter1,loop_up,fixed_0xFF,syshz)
/* TEST(_from_reset,counter1,loop_up,fixed_ff,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_up,fixed_ff,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_up,fixed_ff,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_up,fixed_ff,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_up,fixed_ff,ext_rising) */
/* TEST(_from_reset,counter1,loop_up,fixed_ff,ext_falling) */

/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,none) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,syshz) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,ext_rising) */
/* TEST(_from_reset,counter1,loop_up_pwm,fixed_ff,ext_falling) */

/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,none) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,syshz) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,ext_rising) */
/* TEST(_from_reset,counter1,loop_updown_pwm,fixed_ff,ext_falling) */

/* TEST(_from_reset,counter1,loop_up,ocra,none) */
/* TEST(_from_reset,counter1,loop_up,ocra,syshz) */
/* TEST(_from_reset,counter1,loop_up,ocra,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_up,ocra,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_up,ocra,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_up,ocra,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_up,ocra,ext_rising) */
/* TEST(_from_reset,counter1,loop_up,ocra,ext_falling) */

/* TEST(_from_reset,counter1,loop_up_pwm,ocra,none) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,syshz) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,ext_rising) */
/* TEST(_from_reset,counter1,loop_up_pwm,ocra,ext_falling) */

/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,none) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,syshz) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,syshz_div_8) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,syshz_div_64) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,syshz_div_256) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,syshz_div_1024) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,ext_rising) */
/* TEST(_from_reset,counter1,loop_updown_pwm,ocra,ext_falling) */

/* TEST(,counter1,loop_up,fixed_ff,none) */
/* TEST(,counter1,loop_up,fixed_ff,syshz) */
/* TEST(,counter1,loop_up,fixed_ff,syshz_div_8) */
/* TEST(,counter1,loop_up,fixed_ff,syshz_div_64) */
/* TEST(,counter1,loop_up,fixed_ff,syshz_div_256) */
/* TEST(,counter1,loop_up,fixed_ff,syshz_div_1024) */
/* TEST(,counter1,loop_up,fixed_ff,ext_rising) */
/* TEST(,counter1,loop_up,fixed_ff,ext_falling) */

/* TEST(,counter1,loop_up_pwm,fixed_ff,none) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,syshz) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,syshz_div_8) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,syshz_div_64) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,syshz_div_256) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,syshz_div_1024) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,ext_rising) */
/* TEST(,counter1,loop_up_pwm,fixed_ff,ext_falling) */

/* TEST(,counter1,loop_updown_pwm,fixed_ff,none) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,syshz) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,syshz_div_8) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,syshz_div_64) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,syshz_div_256) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,syshz_div_1024) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,ext_rising) */
/* TEST(,counter1,loop_updown_pwm,fixed_ff,ext_falling) */

/* TEST(,counter1,loop_up,ocra,none) */
/* TEST(,counter1,loop_up,ocra,syshz) */
/* TEST(,counter1,loop_up,ocra,syshz_div_8) */
/* TEST(,counter1,loop_up,ocra,syshz_div_64) */
/* TEST(,counter1,loop_up,ocra,syshz_div_256) */
/* TEST(,counter1,loop_up,ocra,syshz_div_1024) */
/* TEST(,counter1,loop_up,ocra,ext_rising) */
/* TEST(,counter1,loop_up,ocra,ext_falling) */

/* TEST(,counter1,loop_up_pwm,ocra,none) */
/* TEST(,counter1,loop_up_pwm,ocra,syshz) */
/* TEST(,counter1,loop_up_pwm,ocra,syshz_div_8) */
/* TEST(,counter1,loop_up_pwm,ocra,syshz_div_64) */
/* TEST(,counter1,loop_up_pwm,ocra,syshz_div_256) */
/* TEST(,counter1,loop_up_pwm,ocra,syshz_div_1024) */
/* TEST(,counter1,loop_up_pwm,ocra,ext_rising) */
/* TEST(,counter1,loop_up_pwm,ocra,ext_falling) */

/* TEST(,counter1,loop_updown_pwm,ocra,none) */
/* TEST(,counter1,loop_updown_pwm,ocra,syshz) */
/* TEST(,counter1,loop_updown_pwm,ocra,syshz_div_8) */
/* TEST(,counter1,loop_updown_pwm,ocra,syshz_div_64) */
/* TEST(,counter1,loop_updown_pwm,ocra,syshz_div_256) */
/* TEST(,counter1,loop_updown_pwm,ocra,syshz_div_1024) */
/* TEST(,counter1,loop_updown_pwm,ocra,ext_rising) */
/* TEST(,counter1,loop_updown_pwm,ocra,ext_falling) */

/* void test_hw_write_counter1_ocra_0() { hw_write(hw_counter1, ocra, 0); } */
/* void test_hw_write_counter1_ocra_255() { hw_write(hw_counter1, ocra, 255); } */
/* void test_hw_write_counter1_ocrb_0() { hw_write(hw_counter1, ocrb, 0); } */
/* void test_hw_write_counter1_ocrb_255() { hw_write(hw_counter1, ocrb, 255); } */

/* void test_hw_write_counter1_oie_0() { hw_write(hw_counter1, oie, 0); } */
/* void test_hw_turn_irq_counter1_overflow_off() { hw_turn_irq(hw_counter1, overflow, off); } */
/* void test_hw_write_counter1_oie_1() { hw_write(hw_counter1, oie, 1); } */
/* void test_hw_turn_irq_counter1_overflow_on() { hw_turn_irq(hw_counter1, overflow, on); } */

/* void test_hw_write_counter1_ociea_0() { hw_write(hw_counter1, ociea, 0); } */
/* void test_hw_turn_irq_counter1_matcha_off() { hw_turn_irq(hw_counter1, match_a, off); } */
/* void test_hw_write_counter1_ociea_1() { hw_write(hw_counter1, ociea, 1); } */
/* void test_hw_turn_irq_counter1_matcha_on() { hw_turn_irq(hw_counter1, match_a, on); } */
/* void test_hw_write_counter1_ocieb_0() { hw_write(hw_counter1, ocieb, 0); } */
/* void test_hw_turn_irq_counter1_matchb_off() { hw_turn_irq(hw_counter1, match_b, off); } */
/* void test_hw_write_counter1_ocieb_1() { hw_write(hw_counter1, ocieb, 1); } */
/* void test_hw_turn_irq_counter1_matchb_on() { hw_turn_irq(hw_counter1, match_b, on); } */
