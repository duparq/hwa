#ifndef HWA_ATTINY45_PCHG_H
#define HWA_ATTINY45_PCHG_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_PCHG0_BASE			0x20

#define HWA_PCHG_HWA_PCMSK		volatile, u8, 0x15, 0x00, 0x3F


typedef struct {
  u8	commit ;
  HWA_PDCL()

  HWA_VDCL(HWA_PCHG, HWA_PCMSK)
} HWA_PCHG ;


#define hwa_begin_pchg(reset)				\
  HWA_PINIT(HWA_PCHG, HWA_PCHG0);			\
  HWA_VINIT(HWA_PCHG, HWA_PCHG0, HWA_PCMSK,  reset);


#define hwa_commit_pchg()	hwa_pchg_commit(HWA_CORE0, HWA_PCHG0)


inline void hwa_pchg_commit ( HWA_CORE *core, HWA_PCHG *p )
{
  HWA_COMMIT(core, HWA_PCHG, p, HWA_PCMSK);
}


/********************************************************************************
 *										*
 *				Synchronous actions				*
 *										*
 ********************************************************************************/


#define HWA_FLAG_HWA_PCHG0_IRQE		HWA_CORE_PCIE
#define HWA_FLAG_HWA_PCHG0_IRQF		HWA_CORE_PCIF

#define HWA_FREG_HWA_PCHG0		HWA_GIFR
#define HWA_FMSK_HWA_PCHG0		1 << 5


#define HWA_PCHG0_PCINT0		HWA_PCMSK, 0b1, 0
#define HWA_PCHG0_PCINT1		HWA_PCMSK, 0b1, 1
#define HWA_PCHG0_PCINT2		HWA_PCMSK, 0b1, 2
#define HWA_PCHG0_PCINT3		HWA_PCMSK, 0b1, 3
#define HWA_PCHG0_PCINT4		HWA_PCMSK, 0b1, 4
#define HWA_PCHG0_PCINT5		HWA_PCMSK, 0b1, 5


#define hw_pchg_clear_flag(pname, flag)					\
  HW_SETHR(HWA_CORE, HWA_CORE0, HWA_G2(HWA_FREG, pname), HWA_G2(HWA_FMSK, pname))

#define hw_pchg_test_flag(pname, flag)				\
  (HW_TSTHB(HWA_CORE, HWA_CORE0, HWA_G3(HWA_FLAG, pname, flag)) != 0)

#define hw_pchg_turn_irq(pname, state)				\
  HW_SETHB(HWA_CORE, HWA_CORE0, HWA_G3(HWA_FLAG, pname, IRQE), HWA_STATE(state))


/********************************************************************************
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_pchg_turn(p, pin, state)					\
  HWA_SETVB(HWA_PCHG, p, HWA_G2(p, pin), HWA_STATE_##state )

#define hwa_pchg_turn_irq(p, status)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_G3(HWA_FLAG, p, IRQE), HWA_STATE(status))


#endif
