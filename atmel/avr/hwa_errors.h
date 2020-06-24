
/*  Specific error messages
 */
#define HW_EM_1(o)	`o` does not trigger overflow IRQs when not using PWM mode for outputs
#define HW_EM_2(o)	can not use `compare0` of `o` as both compare unit and top value
#define HW_EM_3(o)	\
  o: `output_h` of o must be `set_at_bottom_clear_after_match` when `output_l` is `clear_at_bottom_set_after_match`
#define HW_EM_4		watchdog can not be turned off because HW_Q(HW_DEVICE_WATCHDOG_ALWAYS_ON) is `yes`
