#ifndef HWA_WATCHDOG_H
#define HWA_WATCHDOG_H

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_watchdog_reset()			\
  __asm__ __volatile__ ("wdr")

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_watchdog_set_timeout(timeout)			\
  do {								\
    HWA_VSET(u8, WATCHDOG, CR, 0b1,   4, 1); /* WDCE=1 */	\
    HWA_VSET(u8, WATCHDOG, CR, 0b1,   5, HWA_WDTO_##timeout >> 3);	\
    HWA_VSET(u8, WATCHDOG, CR, 0b111, 0, HWA_WDTO_##timeout &  7);	\
  } while(0)

#define HWA_WDTO_16MS			0b0000	/*    2 * 1024 / 128000 */
#define HWA_WDTO_32MS			0b0001	/*    4 * 1024 / 128000 */
#define HWA_WDTO_64MS			0b0010	/*    8 * 1024 / 128000 */
#define HWA_WDTO_128MS			0b0011	/*   16 * 1024 / 128000 */
#define HWA_WDTO_256MS			0b0100	/*   32 * 1024 / 128000 */
#define HWA_WDTO_512MS			0b0101	/*   64 * 1024 / 128000 */
#define HWA_WDTO_1S			0b0110	/*  128 * 1024 / 128000 */
#define HWA_WDTO_2S			0b0111	/*  256 * 1024 / 128000 */
#define HWA_WDTO_4S			0b1000	/*  512 * 1024 / 128000 */
#define HWA_WDTO_8S			0b1000	/* 1024 * 1024 / 128000 */

#define hwa_watchdog_set_action(action)				\
  do {								\
    HWA_VSET(u8, WATCHDOG, CR, 0b1, 4, 1); /* WDCE=1 */		\
    HWA_VSET(u8, WATCHDOG, CR, 0b1, 3, HWA_WDACTION_##action >> 1);	\
    HWA_VSET(u8, WATCHDOG, CR, 0b1, 6, HWA_WDACTION_##action &  1);	\
  } while(0)

#define HWA_WDACTION_NONE		0b00	/* WDE(3), WDIE(6) */
#define HWA_WDACTION_INTERRUPT		0b01
#define HWA_WDACTION_SYSTEM_RESET	0b10
#define HWA_WDACTION_RESET_IF_INTERRUPT	0b11

/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_WATCHDOG		0x60

#define HWA_WATCHDOG_CR		((volatile u8 *)(HWA_WATCHDOG))

/*	Register declaration: port_name, reg_name, type, reset value, write mask
 */
#define hwa_watchdog_begin(state)		\
  HWA_VDCL(u8, WATCHDOG, CR, 0, 0xFF, state);

#define hwa_watchdog_commit(dry, )						\
  do {									\
    if ( HWA_WATCHDOG_CR_mmask ) {					\
      if ( HWA_WATCHDOG_CR_mmask != HWA_WATCHDOG_CR_wmask		\
	   && HWA_WATCHDOG_CR_vmask != HWA_WATCHDOG_CR_wmask ) {	\
	HWA_WATCHDOG_CR_value =						\
	  (HWA_WATCHDOG_CR_value & HWA_WATCHDOG_CR_mmask)		\
	  | (*HWA_WATCHDOG_CR & ~HWA_WATCHDOG_CR_mmask) ;		\
	HWA_WATCHDOG_CR_vmask = HWA_WATCHDOG_CR_wmask ;			\
      }									\
      HWA_WATCHDOG_CR_ovalue = HWA_WATCHDOG_CR_value ;			\
      if ( HWA_WATCHDOG_CR_mmask & 1<<4 ) /* WDCE==1 */			\
	__asm__ __volatile__ (						\
			      "in __tmp_reg__,__SREG__"	"\n\t"		\
			      "cli"			"\n\t"		\
			      "wdr"			"\n\t"		\
			      "sts %0,%1"		"\n\t"		\
			      "out __SREG__,__tmp_reg__""\n\t"		\
			      "sts %0,%1"		"\n\t"		\
			      : /* no outputs */			\
			      : "M" (HWA_WATCHDOG_CR),		\
				"r" (HWA_WATCHDOG_CR_value)		\
			      : "r0") ;					\
      else								\
	*HWA_WATCHDOG_CR = HWA_WATCHDOG_CR_value ;			\
      HWA_WATCHDOG_CR_mmask = 0 ;					\
    }									\
  } while(0)


#endif
