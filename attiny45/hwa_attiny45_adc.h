#ifndef HWA_ATMEGA88_ADC_H
#define HWA_ATMEGA88_ADC_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_ADC0_BASE			0x00

#define HWA_ADC_HWA_ADMUX		volatile, u8,  0x7C, 0x00, 0xEF
#define HWA_ADC_HWA_ADCSRA		volatile, u8,  0x7A, 0x00, 0xFF
#define HWA_ADC_HWA_ADCH		volatile, u8,  0x79, 0x00, 0x00
#define HWA_ADC_HWA_ADCL		volatile, u8,  0x78, 0x00, 0x00
#define HWA_ADC_HWA_ADC			volatile, u16, 0x78, 0x00, 0x00
#define HWA_ADC_HWA_ADCSRB		volatile, u8,  0x7B, 0x00, 0x47
#define HWA_ADC_HWA_DIDR0		volatile, u8,  0x7E, 0x00, 0x3F


/*	Register bits definitions
 */
#define HWA_ADC_REF			HWA_ADMUX, 0b11,   6
#define HWA_ADC_ADLAR			HWA_ADMUX, 0b1,    5
#define HWA_ADC_MUX			HWA_ADMUX, 0b1111, 0

#define HWA_ADC_ADEN			HWA_ADCSRA, 0b1,   7
#define HWA_ADC_ADSC			HWA_ADCSRA, 0b1,   6
#define HWA_ADC_ADATE			HWA_ADCSRA, 0b1,   5
#define HWA_ADC_ADIF			HWA_ADCSRA, 0b1,   4
#define HWA_ADC_ADIE			HWA_ADCSRA, 0b1,   3
#define HWA_ADC_ADPS			HWA_ADCSRA, 0b111, 0

// #define HWA_ADC_ACME			HWA_ADCSRB, 0b1,   6	/* Analog comparator */

#define HWA_ADC_ADTS			HWA_ADCSRB, 0b111, 0

#define HWA_ADC_ADC5D			HWA_DIDR0, 0b1, 5
#define HWA_ADC_ADC4D			HWA_DIDR0, 0b1, 4
#define HWA_ADC_ADC3D			HWA_DIDR0, 0b1, 3
#define HWA_ADC_ADC2D			HWA_DIDR0, 0b1, 2
#define HWA_ADC_ADC1D			HWA_DIDR0, 0b1, 1
#define HWA_ADC_ADC0D			HWA_DIDR0, 0b1, 0


/*	Convenient registers
 */
#define HWA_ADC_HWA_SPS			, u32, -1, 0, 0xFFFFFFFF


/*	Parameters
 */
#define HWA_ADC_REF_INTERNAL		0b11
#define HWA_ADC_REF_EXTERNAL		0b00
#define HWA_ADC_REF_AVCC		0b01

#define HWA_ADC_ALIGN_RIGHT		0
#define HWA_ADC_ALIGN_LEFT		1

#define HWA_ADC_MUX_CHAN0		0b0000
#define HWA_ADC_MUX_CHAN1		0b0001
#define HWA_ADC_MUX_CHAN2		0b0010
#define HWA_ADC_MUX_CHAN3		0b0011
#define HWA_ADC_MUX_CHAN4		0b0100
#define HWA_ADC_MUX_CHAN5		0b0101
#define HWA_ADC_MUX_CHAN6		0b0110
#define HWA_ADC_MUX_CHAN7		0b0111
#define HWA_ADC_MUX_BGAP		0b1110
#define HWA_ADC_MUX_GROUND		0b1111

#define HWA_ADC_TRIGGER_MANUAL		0b0000		/* ADATE, ADTS[2:0] */
#define HWA_ADC_TRIGGER_FREE_RUNNING	0b1000

#define HWA_ADC_IRQEN_COMPLETED		HWA_ADC_ADIE

#define HWA_ADC_PIN_ADC0		PC0
#define HWA_ADC_PIN_ADC1		PC1
#define HWA_ADC_PIN_ADC2		PC2


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_ADC, HWA_ADMUX);
  HWA_VDCL(HWA_ADC, HWA_ADCSRA);
  HWA_VDCL(HWA_ADC, HWA_ADCSRB);
  HWA_VDCL(HWA_ADC, HWA_DIDR0);

  HWA_VDCL(HWA_ADC, HWA_SPS);
} HWA_ADC ;


#define hwa_begin_adc(reset)				\
  HWA_PINIT(HWA_ADC, HWA_ADC0);				\
  HWA_VINIT(HWA_ADC, HWA_ADC0, HWA_ADMUX, reset);	\
  HWA_VINIT(HWA_ADC, HWA_ADC0, HWA_ADCSRA, reset);	\
  HWA_VINIT(HWA_ADC, HWA_ADC0, HWA_ADCSRB, reset);	\
  HWA_VINIT(HWA_ADC, HWA_ADC0, HWA_DIDR0, reset);	\
  HWA_VINIT(HWA_ADC, HWA_ADC0, HWA_SPS, reset);


#define hwa_commit_adc()			\
  hwa_adc_commit(HWA_CORE0, HWA_ADC0);


inline void
hwa_adc_commit ( HWA_CORE *core, HWA_ADC *p )
{
  if ( !p->used )
    return ;

  u32	syshz	= HWA_GETVR(core, HWA_SYSHZ, 0) ;
  u32	adhz	= 0 ;
  u32	sps	= HWA_GETVR(p, HWA_SPS,   0);

  if ( HWA_SR(p, HWA_SPS, mmask) || sps==0 ) {
    /*
     *	SPS: samples per second. One conversion takes 13 cycles.
     *	ADC clock must be 50..1000 kHz, best results < 200 kHz.
     *	PSC: 2, 4, 8, 16, 32, 64, 128
     */

    /*	Select minimum frequency if 0 given.
     */
    if ( sps == 0 )
      adhz = 50000 ;
    else
      adhz = 13 * sps ;

    u32 psc = syshz / adhz ;
    s8 l2 = hwa_log2_ceil(psc);

    /* *(volatile u16*)0 = l2 ; */

    /* if ( sps != 0 && (l2 < 2 || l2 > 7) ) */
    /*   HWA_ERROR("ADC prescaler value out of 2..7.", 2); */

    if ( l2<2 )	l2 = 2 ;
    if ( l2>7 )	l2 = 7 ;

    psc = 1<<l2 ;
    adhz = syshz / psc ;

    if ( /* sps != 0 && */ (adhz < 50000 || adhz > 1000000) )
      HWA_ERROR("ADC clock frequency out of 50..1000 kHz.");

    if ( sps == 0 ) {
      sps = adhz / 13 ;
      HWA_SETVB(HWA_ADC, p, HWA_SPS, -1, 0, sps);
    }

    HWA_SETVB(HWA_ADC, p, HWA_ADC_ADPS, l2);
  }

  HWA_COMMIT(core, HWA_ADC, p, HWA_SPS);

  HWA_COMMIT(core, HWA_ADC, p, HWA_ADMUX);
  HWA_COMMIT(core, HWA_ADC, p, HWA_ADCSRA);
  HWA_COMMIT(core, HWA_ADC, p, HWA_ADCSRB);
  HWA_COMMIT(core, HWA_ADC, p, HWA_DIDR0);

  p->used = 0 ;
}


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_adc_read(pname)		HW_HR(HWA_ADC, pname, HWA_ADC)

#define hw_adc_trigger(pname)		HW_SETHB(HWA_ADC, pname, HWA_ADC_ADSC, 1)
#define hw_adc_start(pname)		HW_SETHB(HWA_ADC, pname, HWA_ADC_ADSC, 1)

#define hw_adc_connect(pptr, chan)				\
  do {								\
    if ( chan < 0 || chan > 15 || (chan >= 8 && chan <= 13) )	\
      HWA_ERROR("ADC Channel forbidden.");			\
    HW_SETHB(HWA_ADC, pptr, HWA_ADC_MUX, chan);			\
  } while(0)


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

/* #define hwa_adc_set_prescaler(pptr, psc)				\ */
/*   do {									\ */

#define hwa_adc_set_sps(pptr, sps)\
  HWA_SETVB(HWA_ADC, pptr, HWA_SPS, -1, 0, sps)

#define hwa_adc_get_sps(p)	hwa_adc_get_sps_(HWA_CORE0, p)


#define hwa_adc_connect_ref(pptr, ref)				\
  do {								\
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADEN, 1);			\
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_REF, HWA_ADC_REF_##ref);	\
  } while(0)

#define hwa_adc_align(pptr, align)				\
  HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADLAR, HWA_ADC_ALIGN_##align)

#define hwa_adc_connect_channel(pptr, chan)			\
  do {								\
    if ( chan < 0 || chan > 15 || (chan >= 8 && chan <= 13) )	\
      HWA_ERROR("ADC Channel forbidden.");			\
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADEN, 1);			\
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_MUX, chan);			\
    if ( chan >= 0 && chan <= 5 )				\
      HWA_SETVB(HWA_ADC, pptr, HWA_DIDR0, 0b1, chan, 1);		\
  } while(0)

#define hwa_adc_config_pin(pptr, p)				\
  hwa_adc_config_pin_(pptr, HWA_PINNUM(HWA_G2(HWA_ADC_PIN,p)))

#define hwa_adc_config_pin_(pptr, n)			\
  HWA_SETVB(HWA_ADC, pptr, HWA_DIDR0, 0b1, n, 1);

#define hwa_adc_start(pptr)			\
  HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADSC, 1)

#define hwa_adc_set_trigger(pptr, trig)					\
  do {									\
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADATE, ((HWA_ADC_TRIGGER_##trig & 0b1000) != 0)); \
    HWA_SETVB(HWA_ADC, pptr, HWA_ADC_ADTS, HWA_ADC_TRIGGER_##trig & 0b0111); \
  } while(0)

#define hwa_adc_turn_irq(pptr, irq, state)			\
  HWA_SETVB(HWA_ADC, pptr, HWA_ADC_IRQEN_##irq, HWA_STATE_##state)

inline u32 hwa_adc_get_sps_(HWA_CORE *c, HWA_ADC *p)
{
  u32	syshz	= HWA_GETVR(c, HWA_SYSHZ, 0) ;
  u8	adpsc	= 1 << HWA_GETSB(HWA_ADC, p, ovalue, HWA_ADC_ADPS);
  u32	adhz 	= syshz / adpsc ;
  return adhz/13 ;
}
  

#endif
