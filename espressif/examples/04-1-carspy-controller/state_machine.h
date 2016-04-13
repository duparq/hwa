#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdint.h>

#define xassert(...)

#define STATE_MACHINE(depth)					\
  static void		(*sm_dbg)(uint8_t) = 0 ;		\
  static void		(*sm_yield_hook)() = 0 ;		\
  static void		(*sm_from)() ;				\
  static void		(*sm_to)() ;				\
  static void		(*sm_state[depth])() ;			\
  static uint8_t	sm_level ;

#define SM_RESUME()						\
  if ( sm_dbg ) sm_dbg(0);					\
  if ( sm_state[sm_level] )					\
    sm_state[sm_level]() ;					\
  else								\
    goto sm_init ;						\
sm_yield:							\
 __attribute__((unused))					\
 sm_state[sm_level] = sm_from ;					\
 if ( sm_yield_hook ) sm_yield_hook();				\
 if ( sm_dbg ) sm_dbg(1);					\
 return;							\
sm_call:							\
 __attribute__((unused))					\
 xassert(sm_level < sizeof(sm_state)/sizeof(sm_state[0]-1),	\
	 EXIT_CR_STACK_OVERFLOW);				\
 sm_state[sm_level] = sm_from ;					\
 sm_level++ ;							\
 goto *sm_to ;							\
sm_ret:								\
 __attribute__((unused))					\
 xassert(sm_level > 0, EXIT_CR_STACK_OVERFLOW);			\
 sm_level-- ;							\
 goto *sm_state[sm_level] ;					\
sm_init: ;


#define SM_YIELD()				\
  do {						\
    __label__ here ;				\
    sm_from = &&here ;				\
    goto sm_yield ;				\
  here: ;					\
  } while(0)


#define SM_CALL(to)				\
  do {						\
    __label__ from ;				\
    sm_from = &&from ;				\
    sm_to   = &&to ;				\
    goto sm_call ;				\
    /* sm_call(&&from, &&to); */		\
  from: ;					\
  } while(0)


#define SM_RET()	goto sm_ret


#define SM_RESET()				\
  do {						\
    sm_level = 0 ;				\
    sm_addr[0] = 0 ;				\
    if ( sm_dbg ) sm_dbg(2);			\
  } while(0)


#define SM_IS_IDLE()	(sm_addr[0] == 0)

#endif
