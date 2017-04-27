#ifndef HWA_ATMEGA88_CORE_H
#define HWA_ATMEGA88_CORE_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

/*	Convenient registers
 */
#define HWA_CORE_HWA_XSOHZ		, u32, -1,	 0, 0xFFFFFFFF
#define HWA_CORE_HWA_SYSHZ		, u32, -1, 1000000, 0xFFFFFFFF

#define HWA_CORE_HWA_OSCCAL		, u8, 0x66, 	0, 0xFF

#define HWA_CORE_HWA_PCICR		, u8, 0x68, 	0, 0x03
#define HWA_CORE_HWA_PCMSK2		, u8, 0x6D, 	0, 0xFF

/*	Hardware registers
 */
#define HWA_CORE0_BASE			0


typedef struct {
  u8	commit ;
  HWA_PDCL();

  HWA_VDCL(HWA_CORE, HWA_XSOHZ);
  HWA_VDCL(HWA_CORE, HWA_SYSHZ);
} HWA_CORE ;


#define hwa_begin_core(reset)				\
  HWA_PINIT(HWA_CORE, HWA_CORE0);			\
							\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_SYSHZ, reset);	\
  HWA_VINIT(HWA_CORE, HWA_CORE0, HWA_XSOHZ, 0);


#define hwa_commit_core()


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_core_set_xso_hz(hz)				\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_XSOHZ, -1, 0, hz)

#define hwa_core_set_sys_hz(hz)				\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_SYSHZ, -1, 0, hz)

#endif
