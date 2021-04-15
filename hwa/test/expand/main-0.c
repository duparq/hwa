
//#include <hwa/stm32f103c8t6.h>
#include <hwa/atmega328p.h>


#define HW_ISR(...)		_HW_ISR(__VA_ARGS__,,,)

/*  First arg must be an objet name
 */
#define _HW_ISR(o,...)		_HW_ISR0( HW_C3(HW_X(o)), __VA_ARGS__ )
#define _HW_ISR0(...)		_HW_ISR1(__VA_ARGS__)
#define _HW_ISR1(x,...)		HW_B(_HW_ISR1,x)(x,__VA_ARGS__)
#define _HW_ISR11(z,o,e,...)	HW_E(e) void HW_G2(hw,__COUNTER__)()

/*  Reason?
 */
#define _HW_ISR10(c,o,d,x,...)	HW_B(_HW_ISR3,_hw_isr_##o##_##x)(o,x,__VA_ARGS__)
#define _HW_ISR31(o,x,...)	_HW_ISR30(o##_##x,__VA_ARGS__)

/*  Attributes?
 */
#define _HW_ISR30(o,x,...)	HW_B(_HW_ISR4,_hw_israttr_##x)(o,x,__VA_ARGS__)
#define _HW_ISR41(o,x,y,...)	HW_B(_HW_ISR41,_hw_israttr_##y)(o,x,y,__VA_ARGS__)
#define _HW_ISR411(o,x,y,...)	_HW_ISR9(o, HW_A1(_hw_israttr_##x) HW_A1(_hw_israttr_##y), __VA_ARGS__)
#define _HW_ISR410(o,x,...)	_HW_ISR9(o, HW_A1(_hw_israttr_##x), __VA_ARGS__)

/*  Alias?
 */
#define _HW_ISR40(o1,x,...)	HW_BW(_HW_ISR5,alias,x)(o1,x,__VA_ARGS__)
#define _HW_ISR51(o1,x,y,...)	_HW_ISR52(o1,HW_C3(HW_X(y)), __VA_ARGS__ )
#define _HW_ISR52(o1,x,...)	HW_B(_HW_ISR52,x)(o1,x,__VA_ARGS__)
#define _HW_ISR521(o1,z,o,e,...)	HW_E(e) void HW_G2(hw,__COUNTER__)()
#define _HW_ISR520(o1,c,o2,d,x,...)	HW_B(_HW_ISR53,x)(o1,o2,x,__VA_ARGS__)
#define _HW_ISR531(o1,o2,...)	_HW_ISR_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2)) HW_EOL(__VA_ARGS__)

/*  	Reason?
 */
#define _HW_ISR530(o1,o2,x,...)	HW_B(_HW_ISR54,_hw_isr_##o2##_##x)(o1,o2,x,__VA_ARGS__)
#define _HW_ISR541(o1,o2,x,...)	_HW_ISR_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2##_##x)) HW_EOL(__VA_ARGS__)
#define _HW_ISR540(o1,o2,...)	_HW_ISR_ALIAS(HW_A1(_hw_isr_##o1),HW_A1(_hw_isr_##o2)) HW_EOL(__VA_ARGS__)
  
#define _HW_ISR50(o,...)	HW_B(_HW_ISR50,_hw_isr_##o)(o,__VA_ARGS__)
#define _HW_ISR500(o,...)	HW_E(HW_EM_OT(o,isr))
#define _HW_ISR501(...)		_HW_ISR9(__VA_ARGS__)

#define _HW_ISR9(o,...)		_HW_ISR_(HW_A1(_hw_isr_##o),__VA_ARGS__)



EXPAND
HW_ISR(counter2);
HW_ISR(counter2,compare0);
//HW_ISR(counter2,alias);
//HW_ISR(counter2_compare0,alias,);
//HW_ISR(counter2_compare0,alias,counter2,foo);
HW_ISR(counter2_compare0,alias,counter2,compare0);
HW_ISR(counter2,alias,counter2,compare0);
HW_ISR(counter2,naked);
HW_ISR(counter2,naked,interruptible);
HW_ISR(counter2,interruptible);
//HW_ISR(counter2,foo);
