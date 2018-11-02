
/*  ESP8266 interrupts are processed through OS calls to user service routines
 */
#define _os_setisr_timer1_nmi(fn)	NmiTimSetFunc(fn)
#define _os_setisr_timer1_9(fn)		ets_isr_attach(9, fn, 0)

extern void NmiTimSetFunc(void (*isr)(void));
extern void ets_isr_unmask(unsigned intr);


/**
 * @ingroup public_irq_instructions
 * @brief Declaration of an ISR
 *
 * The `os_set_isr()` instruction declares a user ISR for an IRQ.
 *
 * @code
 * os_set_isr( HW_IRQ(timer1, irq), ev_timer );
 * @endcode
 * @hideinitializer
 */
#define _hw_mtd_os_set_isr__irq	, _os_set_isr

#define os_set_isr(...)			_os_setisr_2(__VA_ARGS__,)
#define _os_setisr_2(...)		HW_G2(_os_setisr,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _os_setisr_0(...)		__VA_ARGS__
#define _os_setisr_1(t,...)		_os_set_isr(__VA_ARGS__)

#define _os_set_isr(o,v,ie,if,fn,...)	_os_setisr_##o##_##v(fn) HW_EOL(__VA_ARGS__)
