#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/*	State machine
 *
 *	Caution! This code uses GCC extensions. It is not ISO C compliant!
 *
 *	TODO: see "pragma GCC diagnostic" for warnings removal
 */

//#include "xfuncs.h"
#include <stdint.h>


#if !defined XFUNCS_H
#  define xassert(a,b)
#endif


/*	Declare the current function as the host of a state machine
 */
#define STATE_MACHINE(depth)				\
  uint8_t        sm_depth = depth ;			\
  void         (*sm_dbg)(uint8_t) = 0 ;			\
  void          *sm_from, *sm_to ;			\
  static void   *sm_addr[depth] ;			\
  static uint8_t sm_level  __attribute__((unused)) ;


/*	Reach the stored point of execution
 */
#define SM_RESUME()							\
  if ( sm_dbg ) sm_dbg(0);						\
  void *sm_ad ;								\
  if ( sm_depth > 1 )							\
    sm_ad = sm_addr[sm_level] ;						\
  else									\
    sm_ad = sm_addr[0] ;						\
  if ( sm_ad )								\
    goto *sm_ad ;							\
  else									\
    goto sm_start ;							\
									\
  /*	Store the next point of execution and return from the host function */ \
sm_yield:								\
 if ( sm_dbg ) sm_dbg(1);						\
 sm_addr[sm_level] = sm_from ;						\
 return;								\
									\
 /*	Store the current state and go to subroutine */			\
sm_call:								\
 __attribute__((unused))						\
 xassert(sm_level < sizeof(sm_addr)/sizeof(sm_addr[0]-1),		\
	 EXIT_CR_STACK_OVERFLOW);					\
 sm_addr[sm_level] = sm_from ;						\
 sm_level++ ;								\
 goto *sm_to ;								\
									\
 /*	Return from subroutine */					\
sm_ret:									\
 __attribute__((unused))						\
 xassert(sm_level > 0, EXIT_CR_STACK_OVERFLOW);				\
 sm_level-- ;								\
 goto *sm_addr[sm_level] ;						\
									\
 /*	Initial state starts here */					\
sm_start: ;


/*	Store the next point of execution and return from the host function
 */
#define SM_YIELD()				\
  do {						\
    __label__ here ;				\
    sm_from = &&here ;				\
    goto sm_yield ;				\
  here: ;					\
  } while(0)


/*	Store the current state and go to subroutine
 */
#define SM_CALL(to)				\
  do {						\
    __label__ from ;				\
    sm_from = &&from ;				\
    sm_to   = &&to ;				\
    goto sm_call ;				\
    /* sm_call(&&from, &&to); */		\
  from: ;					\
  } while(0)


/*	Return from subroutine
 */
#define SM_RET()	goto sm_ret


/*	Reset machine to initial state
 */
#define SM_RESET()				\
  do {						\
    sm_level = 0 ;				\
    sm_addr[0] = 0 ;				\
    if ( sm_dbg ) sm_dbg(2);			\
  } while(0)


/*	1 if state machine is in its initial state, 0 otherwise
 */
#define SM_IS_IDLE()	(sm_addr[0] == 0)

#endif
