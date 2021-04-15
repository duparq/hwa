
//#include <hwa/stm32f103c8t6.h>
#include <hwa/atmega328p.h>
  
//    



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
