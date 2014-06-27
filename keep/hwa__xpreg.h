
/*	Check that the first arg is a controller
 */
#define HW_XPIRQ(...)		HW_G2(_hw_xpirq_xctr, HW_IS(ctr,__VA_ARGS__))(__VA_ARGS__,)

#define _hw_xpirq_xctr_no(...)	no, "`" HW_QUOTE(__VA_ARGS__) "`: is not a controller."

/*	The first arg is a controller.
 *	Check that the irq name is valid.
 */
#define _hw_xpirq_xctr_ok(_ctr_,cn,cc,ca, ...)	\
  HW_G2(_hw_xpirq_xisr,HW_IS(isr, hw_isr_##cn##_##__VA_ARGS__))(cn,cc,ca, __VA_ARGS__)

#define _hw_xpirq_xisr_no(cn,cc,ca,...) \
  no, "`" HW_QUOTE(__VA_ARGS__) "` is not a valid irq name."

/*	The irq name is valid.
 *	Check that the state is valid.
 */
#define _hw_xpirq_xisr_ok(cn,cc,ca, irq, ...)				\
  HW_G2(_hw_xpirq_xstate,HW_IS(state, hw_##__VA_ARGS__))(__VA_ARGS__, cn,cc,ca,irq)

#define _hw_xpirq_xstate_no(...) no, "got `" HW_QUOTE(__VA_ARGS__) "` instead of `on` or `off`."

/*	The state is valid.
 *	Check that there is nothing more.
 */
#define _hw_xpirq_xstate_ok(state, ...)	\
  HW_G2(_hw_xpirq,HW_IS(,__VA_ARGS__))(__VA_ARGS__, HW_A1(hw_##state))

#define _hw_xpirq_no(_, ...)	no, "too many arguments :`" HW_QUOTE(_) "`."


/*	Everithing is ok.
 */
#define _hw_xpirq_ok(_, ...)	ok, __VA_ARGS__
