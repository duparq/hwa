#ifndef HWA_ATMEGA88_TIMER2_H
#define HWA_ATMEGA88_TIMER2_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_TIMER2_BASE			0x00

#define HWA_TIMER2_HWA_CCRA		volatile, u8, 0xB0, 0x00, 0xF3
#define HWA_TIMER2_HWA_CCRB		volatile, u8, 0xB1, 0x00, 0xCF
#define HWA_TIMER2_HWA_CNT		volatile, u8, 0xB2, 0x00, 0xFF
#define HWA_TIMER2_HWA_OCRA		volatile, u8, 0xB3, 0x00, 0xFF
#define HWA_TIMER2_HWA_OCRB		volatile, u8, 0xB4, 0x00, 0xFF
#define HWA_TIMER2_HWA_IMSK		volatile, u8, 0x70, 0x00, 0x07
#define HWA_TIMER2_HWA_IFR		volatile, u8, 0x37, 0x00, 0x07
#define HWA_TIMER2_HWA_ASSR		volatile, u8, 0xB6, 0x00, 0x60
#define HWA_TIMER2_HWA_GTCCR		volatile, u8, 0x43, 0x00, 0x83

/*	Register bits definitions
 */
#define HWA_TIMER2_COMA			HWA_CCRA, 0b11,  6
#define HWA_TIMER2_COMB			HWA_CCRA, 0b11,  4
#define HWA_TIMER2_WGM1			HWA_CCRA, 0b1,   1
#define HWA_TIMER2_WGM0			HWA_CCRA, 0b1,   0

#define HWA_TIMER2_FOCA			HWA_CCRB, 0b11,  6
#define HWA_TIMER2_WGM2			HWA_CCRB, 0b1,   3
#define HWA_TIMER2_CS			HWA_CCRB, 0b111, 0

#define HWA_TIMER2_EXCLK		HWA_ASSR, 0b1,   6
#define HWA_TIMER2_AS			HWA_ASSR, 0b1,   5

#define HWA_TIMER2_IRQ_OCB		HWA_IMSK, 0b1,   2
#define HWA_TIMER2_IRQ_OCA		HWA_IMSK, 0b1,   1
#define HWA_TIMER2_IRQ_OVF		HWA_IMSK, 0b1,   0

#define HWA_TIMER2_IRQ_PERIODIC		HWA_TIMER2_IRQ_OCA

#define HWA_TIMER2_OCFB			HWA_IFR, 0b1, 2
#define HWA_TIMER2_OCFA			HWA_IFR, 0b1, 1
#define HWA_TIMER2_OVF			HWA_IFR, 0b1, 0

#define HWA_TIMER2_COUNT_MAX		255

/*	Flags
 */
#define HWA_TIMER2_FLAG_MATCH_B		HWA_IFR, 0b1, 2
#define HWA_TIMER2_FLAG_LOOP		HWA_IFR, 0b1, 1
#define HWA_TIMER2_FLAG_MATCH_A		HWA_IFR, 0b1, 1
#define HWA_TIMER2_FLAG_MATCH_LOOP	HWA_IFR, 0b1, 1
#define HWA_TIMER2_FLAG_OVF		HWA_IFR, 0b1, 0
#define HWA_TIMER2_FLAG_OVERFLOW	HWA_IFR, 0b1, 0

/*	Interrupts
 */
#define HWA_TIMER2_IRQE_MATCH_B		HWA_IMSK, 0b1, 2
#define HWA_TIMER2_IRQE_LOOP		HWA_IMSK, 0b1, 1
#define HWA_TIMER2_IRQE_MATCH_A		HWA_IMSK, 0b1, 1
#define HWA_TIMER2_IRQE_MATCH_LOOP	HWA_IMSK, 0b1, 1
#define HWA_TIMER2_IRQE_OVF		HWA_IMSK, 0b1, 0

/*	Pins
 */
#define OC2A				PB3
#define OC2B				PD3

#define HWA_TIMER2_PIN_MATCH_LOOP	OC2A
#define HWA_TIMER2_PIN_MATCH_A		OC2A
#define HWA_TIMER2_PIN_MATCH_B		OC2B


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_TIMER2, HWA_CCRA);
  HWA_VDCL(HWA_TIMER2, HWA_CCRB);
  HWA_VDCL(HWA_TIMER2, HWA_OCRA);
  HWA_VDCL(HWA_TIMER2, HWA_OCRB);
  HWA_VDCL(HWA_TIMER2, HWA_ASSR);
  HWA_VDCL(HWA_TIMER2, HWA_IMSK);

  HWA_VDCL(HWA_TIMER, HWA_MODE);
  HWA_VDCL(HWA_TIMER, HWA_CLK);
  HWA_VDCL(HWA_TIMER, HWA_PSC);
  HWA_VDCL(HWA_TIMER, HWA_MAX);
  HWA_VDCL(HWA_TIMER, HWA_HZ);
  HWA_VDCL(HWA_TIMER, HWA_PERIOD);
} HWA_TIMER2 ;


#define hwa_timer_begin_timer2(reset)			\
  HWA_PINIT(HWA_TIMER2, HWA_TIMER2);			\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_CCRA, reset);	\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_CCRB, reset);	\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_OCRA, reset);	\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_OCRB, reset);	\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_ASSR, reset);	\
  HWA_VINIT(HWA_TIMER2, HWA_TIMER2, HWA_IMSK, reset);	\
							\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_MODE, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_CLK, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_PSC, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_MAX, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_HZ, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER2, HWA_PERIOD, reset);


inline void
hwa_timer_commit_timer2 ( HWA_CORE *core, HWA_TIMER2 *p )
{
  if ( !p->used )
    return ;

  u8	mode	= HWA_GETVR(p, HWA_MODE,   0);
  u8	clk	= HWA_GETVR(p, HWA_CLK,    0);
  u16	psc	= HWA_GETVR(p, HWA_PSC,    0);
  u32	max	= HWA_GETVR(p, HWA_MAX,    0);
  u32	hz	= HWA_GETVR(p, HWA_HZ,     0);

  u32	syshz	= HWA_GETVR(core, HWA_SYSHZ,  0);

  /*	Mode
   */
  if ( mode ) {
    if ( hz == 0 && psc == 0 && max == 0 )
      HWA_ERROR("TIMER2: loop mode needs at least two of HZ, PSC, or MAX to be set.");

    if ( psc == 0 &&
	 (syshz / (256 * hz)) * 256 * hz == syshz )
      max = 255 ;

    if ( mode == HWA_TIMER_MODE_LOOP_ON_OVERFLOW ) {
      if ( max != 255 )
	HWA_ERROR("TIMER2: mode LOOP_OVERFLOW requires MAX to be 255.");
      /*
       *	Mode Fast PWM: loops from 0 to 0xFF, IRQ on overflow
       */
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM2, 0 );
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM1, 1 );
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM0, 1 );
    }
    else if ( mode == HWA_TIMER_MODE_LOOP_ON_MATCH ) {
      /*
       *	Mode CTC: loops from 0 to OCRA, IRQ on compare match A
       */
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM2, 0 );
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM1, 1 );
      HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_WGM0, 0 );
    }
    else
      HWA_ERROR("Timer mode not supported.");
  }
  else
    HWA_ERROR("Timer mode not supported.");

  /*	Compute psc and/or max
   */
  if ( clk == 0 || clk == HWA_TIMER_CLK_SYS_PSC ) {
    HWA_SETVB(HWA_TIMER2, p, HWA_TIMER2_AS, 0);
    if ( psc == 0 ) {
      if ( max == 0 ) {
	/*
	 *  Prescaler value: 1, 8, 32, 64, 128, 256, 1024
	 */
	psc = 1 ; max = syshz / (hz * psc) ;
	if ( max > 0xFF ) { psc = 8 ;		max = syshz / (hz * psc) ; }
	if ( max > 0xFF ) { psc = 32 ;		max = syshz / (hz * psc) ; }
	if ( max > 0xFF ) { psc = 64 ;		max = syshz / (hz * psc) ; }
	if ( max > 0xFF ) { psc = 128 ;		max = syshz / (hz * psc) ; }
	if ( max > 0xFF ) { psc = 256 ;		max = syshz / (hz * psc) ; }
	if ( max > 0xFF ) { psc = 1024 ;	max = syshz / (hz * psc) ; }
      }
      else
	psc = syshz / (hz * max);

      if ( max < 1 || max > 0xFF )
	HWA_ERROR("No valid prescaler value for IRQ_HZ.");
    }
    else if ( max == 0 )
      max = syshz / psc / hz ;
  }
  else
    HWA_ERROR("Timer source clock not supported.");

  if ( hz * psc * max != syshz )
    HWA_ERROR("HWA_TIMER2: invalid prescaler/divisor.");

  HWA_SETVB( HWA_TIMER2, p, HWA_OCRA, -1, 0, max-1 );

  if ( psc == 1 )		HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b001 );
  else if ( psc == 8 )		HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b010 );
  else if ( psc == 32 )		HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b011 );
  else if ( psc == 64 )		HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b100 );
  else if ( psc == 128 )	HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b101 );
  else if ( psc == 256 )	HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b110 );
  else if ( psc == 1024 )	HWA_SETVB( HWA_TIMER2, p, HWA_TIMER2_CS, 0b111 );
  else
    HWA_ERROR("Invalid prescaler value.");

  HWA_COMMIT(core, HWA_TIMER, p, HWA_MODE);  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLK);	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PSC);	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_MAX);	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_HZ);	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PERIOD);

  HWA_COMMIT(core, HWA_TIMER2, p, HWA_CCRA);
  HWA_COMMIT(core, HWA_TIMER2, p, HWA_CCRB);
  HWA_COMMIT(core, HWA_TIMER2, p, HWA_OCRA);
  HWA_COMMIT(core, HWA_TIMER2, p, HWA_OCRB);
  HWA_COMMIT(core, HWA_TIMER2, p, HWA_IMSK);
  HWA_COMMIT(core, HWA_TIMER2, p, HWA_ASSR);

  p->used = 0 ;
}


#endif
