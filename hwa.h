#ifndef HWA_H
#define HWA_H

/*!	\mainpage	HWA: Hardware Abstraction Facility
 */

/*!	\file hwa.h
 *	\brief Main include file for HWA facilities.
 */

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 ********************************************************************************/

/*!	\def hwa_begin(state)
 *
 *	\brief Start a new HWA configuration session.
 *
 *	If the optionnal parameter 'RESET' is used, hardware registers are
 *	supposed to contain reset values, helping optimization of the code.
 *
 *	@param state can be:
 *	\li '' : unknown hardware state.
 *	\li RESET : hardware in reset state.
 */

#define hwa_begin(state)						\
  u8 hwa_commit_policy __attribute__((unused)) = HWA_COMMIT_POLICY_WHEN_ASKED ; \
  u8 hwa_checking_policy __attribute__((unused)) = HWA_CHECKING_POLICY_COMPILE_TIME ; \
  _hwa_begin(state)

#define rem_hwa_begin(state)						\
  u8 hwa_commit_policy __attribute__((unused)) = HWA_COMMIT_POLICY_WHEN_ASKED ; \
  u8 hwa_checking_policy __attribute__((unused)) = HWA_CHECKING_POLICY_COMPILE_TIME ; \
  hwa_flash_begin(HWA_BEGIN_STATE_##state);				\
  hwa_gpio_begin(HWA_BEGIN_STATE_##state);				\
  hwa_irq_begin(HWA_BEGIN_STATE_##state);				\
  hwa_rcc_begin(HWA_BEGIN_STATE_##state);				\
  hwa_rtc_begin(HWA_BEGIN_STATE_##state);				\
  hwa_systick_begin(HWA_BEGIN_STATE_##state);				\
  hwa_timer_begin(HWA_BEGIN_STATE_##state);				\
  hwa_uart_begin(HWA_BEGIN_STATE_##state);


#define HWA_BEGIN_STATE_				0
#define HWA_BEGIN_STATE_RESET				1

/*!	\def hwa_set_commit_policy(policy)
 *
 *	\brief Select HWA commitment policy.
 *
 *	@param policy can be:
 *	\li WHEN_ASKED	: let the user decide when to commit.
 *	\li AUTO	: let HWA commit some registers automatically.
 *	\li ALWAYS	: HWA will commit after every modification (no optimization).
 */
#define hwa_set_commit_policy(policy)			\
  hwa_commit_policy = HWA_COMMIT_POLICY_##policy ;
#define HWA_COMMIT_POLICY_WHEN_ASKED			0
#define HWA_COMMIT_POLICY_AUTO				1
#define HWA_COMMIT_POLICY_ALWAYS			2


#define hwa_set_checking_policy(policy)			\
  hwa_checking_policy = HWA_CHECKING_POLICY_##policy ;
#define HWA_CHECKING_POLICY_NONE			0
#define HWA_CHECKING_POLICY_COMPILE_TIME		1
#define HWA_CHECKING_POLICY_RUN_TIME			2

/*	Write virtual registers to real registers
 */
#define hwa_commit()							\
  if (0) { HWA_WARN_CT(1, "Compiler should have discarded this!"); }	\
  _hwa_commit();

/*	Turn on/off peripheral.
 */
#define hwa_turn(name, state)			\
  hwa_turn_(name, state)

#define hwa_turn_(name, state)				\
  HWA_SET_VA(HWA_TURN_ARGS_##name, HWA_STATE_##state)

#define HWA_TURN_ARGS_USART1			USART1_CR1, 0b1, 13


/*	Reset peripheral
 */
#define hwa_reset(name)				\
  hwa_reset_(name)

#define hwa_reset_(name)			\
  HWA_SET_VA(HWA_RESET_ARGS_##name, 1)

#define HWA_RESET_ARGS_USART1			RCC_APB2RSTR, 0b1, 14


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#include "types.h"

__attribute__((noreturn)) void exit ( int status __attribute__((unused)) ) ;

/*	Useful definitions
 */
#define HWA_GLUE2_(a,b)			a##b
#define HWA_GLUE2(a,b)			HWA_GLUE2_(a,b)

#define HWA_GLUE3_(a,b,c)		a##b##c
#define HWA_GLUE3(a,b,c)		HWA_GLUE3_(a,b,c)

#define HWA_STR_(x)			#x
#define HWA_STR(x)			HWA_STR_(x)

#define HWA_1of2(x,y)			x
#define HWA_2of2(x,y)			y

#define HWA_STATE_OFF			0
#define HWA_STATE_ON			1

/*	Warnings & errors
 */
#define HWA_WARN_CT(num, msg)						\
  { extern void __attribute__((warning("Check #" HWA_STR(num) " failed"))) \
      HWA_GLUE2(hwa_warn_ct_, num)(void);				\
    HWA_GLUE2(hwa_warn_ct_, num)(); }

#define HWA_WARN_RT(num, msg)				\
  { extern void HWA_GLUE2(hwa_warn_rt_, num)(void);	\
    HWA_GLUE2(hwa_warn_rt_, num)(); }

#define HWA_ERROR_CT(num, msg)						\
  { extern void __attribute__((error("Check #" HWA_STR(num) " failed"))) \
      HWA_GLUE2(hwa_error_ct_, num)(void);				\
    HWA_GLUE2(hwa_error_ct_, num)(); }

#define HWA_ERROR_RT(num, msg)				\
  { extern void HWA_GLUE2(hwa_error_rt_, num)(void);	\
    HWA_GLUE2(hwa_error_rt_, num)(); }

/*	Declares 'virtual' registers associated to real register
 *	Register declaration: name, type, address, reset value, write mask
 */
#define HWA_DECL(reg, type, addr, reset_value, wmask, initialised)	\
  u8	HWA_##reg##_initialised = initialised ;				\
  type	HWA_##reg##_ovalue = initialised ? reset_value : ~reset_value ;	/* last commited value */ \
  type	HWA_##reg##_value = reset_value ;				/* new value */ \
  type	HWA_##reg##_mmask = 0 ;						/* modif mask */ \
  type	HWA_##reg##_wmask = wmask ;					/* reg write mask */

/*	Record register modification.
 *	If the commit policy is 'ALWAYS', apply modifications immediately on the
 *	real register.
 *	If the register real value is known (initialised != 0), only record modifications
 *	which would have an effect.
 */
#define HWA_SET(reg, mask, shift, value)				\
  if ( HWA_##reg##_initialised == 0 ) {					\
    HWA_##reg##_mmask |= ((mask) << (shift)) ;				\
    HWA_##reg##_value = (HWA_##reg##_value & ~((mask) << (shift))) | ((value) << (shift)) ; \
  } else {								\
    if ( (u32)(HWA_##reg##_value & ((mask) << (shift))) != (u32)((value) << (shift)) ) { \
      HWA_##reg##_mmask |= ((mask) << (shift)) ;			\
      HWA_##reg##_value = (HWA_##reg##_value & ~((mask) << (shift))) | ((value) << (shift)) ; \
    }									\
  }									\
  if ( hwa_commit_policy == HWA_COMMIT_POLICY_ALWAYS) {			\
    HWA_COMMIT(reg);							\
  }

#define HWA_SET_VA(args...)			\
  HWA_SET(args)

#define HWA_BITS(reg, mask, shift)		\
  (((reg) & ((mask) << (shift)))>> (shift))

/*	Commit if commit policy is set to 'auto'
 */
#define HWA_COMMIT_AUTO(reg, mask, shift)				\
  if ( hwa_commit_policy == HWA_COMMIT_POLICY_AUTO			\
       && HWA_BITS(HWA_GLUE3(HWA_, reg, _mmask), mask, shift) != 0)	\
    HWA_COMMIT(reg);							\

/*	Update real register if needed (mmask != 0).
 *
 *	The unmodified part of the writable register value is loaded the first
 *	time the register has to be modified (unless the modification applies to
 *	all the writable bits, i.e. mmask == wmask, reading the real register
 *	would then be useless).
 */
#define HWA_COMMIT(reg)							\
  if ( HWA_##reg##_mmask ) {						\
    if ( HWA_##reg##_initialised == 0					\
	 && HWA_##reg##_mmask != HWA_##reg##_wmask ) {			\
      HWA_##reg##_value |= *HWA_PTR_##reg & ~HWA_##reg##_mmask ;	\
    }									\
    HWA_##reg##_initialised = 1 ;					\
    HWA_##reg##_ovalue = HWA_##reg##_value ;				\
    *HWA_PTR_##reg = HWA_##reg##_value ;				\
    HWA_##reg##_mmask = 0 ;						\
  }

#define HWA_COMMIT_VA(args...)			\
  _HWA_COMMIT_VA(args)

#define _HWA_COMMIT_VA(a, b, c)			\
  HWA_COMMIT(a)


#include "hwa_gpio_ports.h"

/*	Include specific device definitions
 */
#define HWA_INC_STM32		"hwa_stm32.h"

#define _HWA_INC(dev)		HWA_INC_##dev
#define HWA_INC(dev)		_HWA_INC(dev)

#if defined HWA_DEVICE
#include HWA_INC(HWA_DEVICE)
#else
#error "HWA: undefined symbol HWA_DEVICE."
#endif

#endif
