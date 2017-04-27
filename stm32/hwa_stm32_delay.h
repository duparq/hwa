#ifndef HWA_STM32_DELAY_H
#define HWA_STM32_DELAY_H


#define hw_nops(n)			_hw_nops(n/4)


inline void
_hw_nops ( u32 cycles )
{
  __asm__
    __volatile__
    (
     "		mov	r0, %[cycles]"	"\n\t"
     "1:"				"\n\t"
     "		subs	r0, #1"		"\n\t"
     "		bne.n	1b"		"\n\t"
     :
     : [cycles] "r" (cycles)
     : "r0", "cc"
     ) ;
}


#endif
