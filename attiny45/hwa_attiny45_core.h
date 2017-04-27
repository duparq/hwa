#ifndef HWA_ATTINY45_CORE_H
#define HWA_ATTINY45_CORE_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/


/*	Shared hardware registers
 */
#define HWA_CORE0_BASE			0x20

#define HWA_CORE_HWA_GIMSK		volatile, u8, 0x3B, 0x00, 0x60
#define HWA_CORE_INT0			HWA_GIMSK, 0b1, 6
#define HWA_CORE_PCIE			HWA_GIMSK, 0b1, 5

#define HWA_CORE_HWA_GIFR		volatile, u8, 0x3A, 0x00, 0x60
#define HWA_CORE_INTF0			HWA_GIFR,  0b1, 6
#define HWA_CORE_PCIF			HWA_GIFR,  0b1, 5

#define HWA_CORE_HWA_MCUCR		volatile, u8, 0x35, 0x00, 0x03
#define HWA_CORE_ISC0			HWA_MCUCR, 0b11, 0

#define HWA_CORE_ISC0_LOW		HWA_MCUCR, 0b11, 0, 0b00
#define HWA_CORE_ISC0_CHANGE		HWA_MCUCR, 0b11, 0, 0b01
#define HWA_CORE_ISC0_FALL		HWA_MCUCR, 0b11, 0, 0b10
#define HWA_CORE_ISC0_RISE		HWA_MCUCR, 0b11, 0, 0b11

#define HWA_CORE_HWA_DIDR0		volatile, u8,  0x14, 0x00, 0x3F
#define HWA_CORE_AIN1D			HWA_DIDR0,  0b1,  1
#define HWA_CORE_AIN0D			HWA_DIDR0,  0b1,  0

#define HWA_CORE_HWA_ACSR		volatile, u8,  0x08, 0x00, 0xDB
#define HWA_CORE_ACD			HWA_ACSR,   0b1,  7
#define HWA_CORE_ACBG			HWA_ACSR,   0b1,  6
#define HWA_CORE_ACO			HWA_ACSR,   0b1,  5
#define HWA_CORE_ACI			HWA_ACSR,   0b1,  4
#define HWA_CORE_ACIE			HWA_ACSR,   0b1,  3
#define HWA_CORE_ACIS1			HWA_ACSR,   0b1,  1
#define HWA_CORE_ACIS0			HWA_ACSR,   0b1,  0
#define HWA_CORE_ACIS			HWA_ACSR,   0b11, 0

#define HWA_CORE_HWA_ADCSRA		volatile, u8,  0x06, 0x00, 0x40
#define HWA_CORE_ADEN			HWA_ADCSRB, 0b1,  7

#define HWA_CORE_HWA_ADCSRB		volatile, u8,  0x03, 0x00, 0x40
#define HWA_CORE_ACME			HWA_ADCSRB, 0b1,  6


/*	Convenient registers
 */
#define HWA_CORE_HWA_XSOHZ		, u32, -1,	 0, 0xFFFFFFFF
#define HWA_CORE_HWA_SYSHZ		, u32, -1, 1000000, 0xFFFFFFFF

#define HWA_CORE_HWA_OSCCAL		, u8, 0x66, 	0, 0xFF

#define HWA_CORE_HWA_PCICR		, u8, 0x68, 	0, 0x03
#define HWA_CORE_HWA_PCMSK2		, u8, 0x6D, 	0, 0xFF


typedef struct {
  u8	commit ;
  HWA_PDCL()

  HWA_VDCL(HWA_CORE, HWA_GIMSK)
  HWA_VDCL(HWA_CORE, HWA_GIFR)
  HWA_VDCL(HWA_CORE, HWA_MCUCR)
  HWA_VDCL(HWA_CORE, HWA_ADCSRB)
  HWA_VDCL(HWA_CORE, HWA_ACSR)
  HWA_VDCL(HWA_CORE, HWA_DIDR0)

  HWA_VDCL(HWA_CORE, HWA_XSOHZ)
  HWA_VDCL(HWA_CORE, HWA_SYSHZ)
} HWA_CORE ;


#define hwa_begin_core(reset)				\
  HWA_PINIT(HWA_CORE, HWA_CORE0);			\
							\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_GIMSK,  reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_GIFR,   reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_MCUCR,   reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_ADCSRB, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_ACSR,   reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_DIDR0,  reset);	\
							\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_SYSHZ,  reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_XSOHZ,  0);


#define hwa_commit_core()	hwa_core_commit(HWA_CORE0)


/*	Commit all registers
 */
inline void hwa_core_commit ( HWA_CORE *core )
{
  /* if ( !p->used ) */
  /*   return ; */

  HWA_COMMIT(core, HWA_CORE, core, HWA_GIMSK);
  HWA_COMMIT(core, HWA_CORE, core, HWA_GIFR);
  HWA_COMMIT(core, HWA_CORE, core, HWA_MCUCR);

  HWA_COMMIT(core, HWA_CORE, core, HWA_ADCSRB);
  HWA_COMMIT(core, HWA_CORE, core, HWA_ACSR);
  HWA_COMMIT(core, HWA_CORE, core, HWA_DIDR0);

  HWA_COMMIT(core, HWA_CORE, core, HWA_SYSHZ);
  HWA_COMMIT(core, HWA_CORE, core, HWA_XSOHZ);

  /* p->used = 0 ; */
}


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_core_set_xso_hz(hz)				\
  HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_XSOHZ, hz)

#define hwa_core_set_sys_hz(hz)				\
  HWA_SETVR(HWA_CORE, HWA_CORE0, HWA_SYSHZ, hz)

#endif
