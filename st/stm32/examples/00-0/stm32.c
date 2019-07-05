

#if 0
#  define DEFAULT_ESR(n)		{ while(1); }
#  define DEFAULT_ISR(n)		{ while(1); }
#elif 0
#  include BOARD_H
#  define DEFAULT_ESR(n)		{ hw_isr_default(n); }
#  define DEFAULT_ISR(n)		{ hw_isr_default(n); }
void WEAK hw_isr_default ( unsigned int n __attribute__((unused)) )
{
  while(1) hw(sleep_until_event);
}
#elif 0
#  define DEFAULT_ESR(n)		__attribute__((alias("hw_isr_default")));
#  define DEFAULT_ISR(n)		__attribute__((alias("hw_isr_default")));
void WEAK hw_isr_default ( )
{
}
#elif 0
#  define DEFAULT_ESR(n)		{ while(1) hw(sleep_until_event); }
#  define DEFAULT_ISR(n)		{ while(1) hw(sleep_until_event); }
#endif

#include "../stm32.c"
