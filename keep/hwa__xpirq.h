
/*	Check that the first arg is a controller
 */
#define HW_XPIRQ(...)		HW_G2(_hw_xpirq_xper, HW_IS(per,__VA_ARGS__))(__VA_ARGS__,)

#define _hw_xpirq_xper_no(...)	no("`" HW_QUOTE(__VA_ARGS__) "`: is not a controller.")

/*	The first arg is a controller.
 *	Check that the irq name is valid.
 */
#define _hw_xpirq_xper_ok(_per_,pn,pc,pa, ...)	\
  HW_G2(_hw_xpirq_xisr,HW_IS(isr, hw_isr_##pn##_##__VA_ARGS__))(pn,pc,pa, __VA_ARGS__)

#define _hw_xpirq_xisr_no(pn,pc,pa,...) \
  no("`" HW_QUOTE(__VA_ARGS__) "` is not a valid irq name.")

/*	The irq name is valid.
 *	Check that the state is valid.
 */
#define _hw_xpirq_xisr_ok(pn,pc,pa, irq, ...)				\
  HW_G2(_hw_xpirq_xstate,HW_IS(state, hw_##__VA_ARGS__))(__VA_ARGS__, pn,pc,pa,irq)

#define _hw_xpirq_xstate_no(...) no("invalid or missing argument: got `" HW_QUOTE(__VA_ARGS__) "` instead of `on` or `off`.")

/*	The state is valid.
 *	Check that there is no other argument.
 */
#define _hw_xpirq_xstate_ok(state, ...)	\
  HW_G2(_hw_xpirq,HW_IS(,__VA_ARGS__))(__VA_ARGS__, HW_A1(hw_##state))

#define _hw_xpirq_no(_, ...)	no("too many arguments:`" HW_QUOTE(_) "`.")

/*	Everithing is ok.
 */
#define _hw_xpirq_ok(_, ...)	ok(__VA_ARGS__)
