#ifndef HWA_STM32_DELAY_H
#define HWA_STM32_DELAY_H


#define hw_nops(n)			_hw_nops(n/4)


inline void
_hw_nops ( u32 cycles )
{
#if 1
  __asm__
    __volatile__
    (
     "		mov	r7, %[cycles]"	"\n\t"
     "1:"				"\n\t"
     "		subs	r7, #1"		"\n\t"
     "		bne.n	1b"		"\n\t"
     :
     : [cycles] "r" (cycles)
     : "r7", "cc"
     ) ;
#elif 1
  __asm__
    __volatile__
    (
     //     "		mov	r7, %[cycles]"	"\n\t"
     "1:"				"\n\t"
     "		subs	%[c], #1"		"\n\t"
     "		bne.n	1b"		"\n\t"
     : [c] "+r" (cycles)
     : [cycles] "r" (cycles)
     : "cc"
     ) ;
#else
  while ( cycles )
  {
    __asm__
      __volatile__
      (
       "		nop"				"\n\t"
       //       ""
       ) ;
    cycles-- ;
  }
 #endif
}


#endif
