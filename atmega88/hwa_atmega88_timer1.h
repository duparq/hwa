#ifndef HWA_ATMEGA88_TIMER1_H
#define HWA_ATMEGA88_TIMER1_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_TIMER1_BASE			0x00

#define HWA_TIMER1_HWA_CCRA		volatile, u8,  0x80, 0x00,   0xF3
#define HWA_TIMER1_HWA_CCRB		volatile, u8,  0x81, 0x00,   0xDF
#define HWA_TIMER1_HWA_CCRC		volatile, u8,  0x82, 0x00,   0xC0
#define HWA_TIMER1_HWA_CNTL		volatile, u8,  0x84, 0x00,   0xFF
#define HWA_TIMER1_HWA_CNTH		volatile, u8,  0x85, 0x00,   0xFF
#define HWA_TIMER1_HWA_CNT		volatile, u16, 0x84, 0x0000, 0xFFFF
#define HWA_TIMER1_HWA_OCRAL		volatile, u8,  0x88, 0x00,   0xFF
#define HWA_TIMER1_HWA_OCRAH		volatile, u8,  0x89, 0x00,   0xFF
#define HWA_TIMER1_HWA_OCRA		volatile, u16, 0x88, 0x0000, 0xFFFF
#define HWA_TIMER1_HWA_OCRBL		volatile, u8,  0x8A, 0x00,   0xFF
#define HWA_TIMER1_HWA_OCRBH		volatile, u8,  0x8B, 0x00,   0xFF
#define HWA_TIMER1_HWA_OCRB		volatile, u16, 0x8A, 0x0000, 0xFFFF
#define HWA_TIMER1_HWA_ICRL		volatile, u8,  0x86, 0x00,   0xFF
#define HWA_TIMER1_HWA_ICRH		volatile, u8,  0x87, 0x00,   0xFF
#define HWA_TIMER1_HWA_ICR		volatile, u16, 0x86, 0x0000, 0xFFFF
#define HWA_TIMER1_HWA_IMSK		volatile, u8,  0x6F, 0x00,   0x27
#define HWA_TIMER1_HWA_IFR		volatile, u8,  0x36, 0x00,   0x27

#define HWA_TIMER1_HWA_GTCCR		volatile, u8,  0x43, 0x00,   0x83

/*	Register bits definitions
 */
#define HWA_TIMER1_COMA			HWA_CCRA, 0b11,  6
#define HWA_TIMER1_COMB			HWA_CCRA, 0b11,  4
#define HWA_TIMER1_WGM1			HWA_CCRA, 0b1,   1
#define HWA_TIMER1_WGM0			HWA_CCRA, 0b1,   0

#define HWA_TIMER1_ICNC			HWA_CCRB, 0b1,   7
#define HWA_TIMER1_ICES			HWA_CCRB, 0b1,   6
#define HWA_TIMER1_WGM3			HWA_CCRB, 0b1,   4
#define HWA_TIMER1_WGM2			HWA_CCRB, 0b1,   3
#define HWA_TIMER1_CS2			HWA_CCRB, 0b1,   2
#define HWA_TIMER1_CS1			HWA_CCRB, 0b1,   1
#define HWA_TIMER1_CS0			HWA_CCRB, 0b1,   0
#define HWA_TIMER1_CS			HWA_CCRB, 0b111, 0

#define HWA_TIMER1_FOCA			HWA_CCRC, 0b1,   7
#define HWA_TIMER1_FOCB			HWA_CCRC, 0b1,   6

#define HWA_TIMER1_OCIEA		HWA_IMSK, 0b1,   1

#define HWA_TIMER1_ICF			HWA_IFR,  0b1,   5
#define HWA_TIMER1_OCFB			HWA_IFR,  0b1,   2
#define HWA_TIMER1_OCFA			HWA_IFR,  0b1,   1
#define HWA_TIMER1_OVF			HWA_IFR,  0b1,   0

#define HWA_TIMER1_PSRSYNC		HWA_GTCCR, 0b1,  0

#define HWA_TIMER1_DRIVE_MATCH_LOOP_TOGGLE	HWA_CCRA, 0b11,  6, 0b01

#define HWA_TIMER1_COUNT_MAX		0xFFFF

#define HWA_TIMER1_MATCH_LOOP		HWA_OCRA
#define HWA_TIMER1_MATCHA		HWA_OCRA
#define HWA_TIMER1_MATCHB		HWA_OCRB

/*	Flags
 */
#define HWA_TIMER1_FLAG_CAPTURE		HWA_IFR,  0b1,   5
#define HWA_TIMER1_FLAG_MATCH_B		HWA_IFR,  0b1,   2
#define HWA_TIMER1_FLAG_LOOP		HWA_IFR,  0b1,   1
#define HWA_TIMER1_FLAG_MATCH_A		HWA_IFR,  0b1,   1
#define HWA_TIMER1_FLAG_OVF		HWA_IFR,  0b1,   0
#define HWA_TIMER1_FLAG_OVERFLOW	HWA_IFR,  0b1,   0

/*	Interrupts
 */
#define HWA_TIMER1_IRQE_CAPTURE		HWA_IMSK, 0b1, 5
#define HWA_TIMER1_IRQE_MATCH_B		HWA_IMSK, 0b1, 2
#define HWA_TIMER1_IRQE_LOOP		HWA_IMSK, 0b1, 1
#define HWA_TIMER1_IRQE_MATCH_A		HWA_IMSK, 0b1, 1
#define HWA_TIMER1_IRQE_MATCH_LOOP	HWA_IMSK, 0b1, 1
#define HWA_TIMER1_IRQE_OVERFLOW	HWA_IMSK, 0b1, 0

/*	Pins
 */
#define ICP1				PB0
#define OC1A				PB1
#define OC1B				PB2

//#define HWA_TIMER1_PIN_MATCH_LOOP	OC1A
#define HWA_TIMER1_PIN_MATCH_A		OC1A
#define HWA_TIMER1_PIN_MATCH_B		OC1B
#define HWA_TIMER1_PIN_CAPTURE		ICP1


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_TIMER1, HWA_CCRA);
  HWA_VDCL(HWA_TIMER1, HWA_CCRB);
  HWA_VDCL(HWA_TIMER1, HWA_CCRC);
  HWA_VDCL(HWA_TIMER1, HWA_OCRA);
  HWA_VDCL(HWA_TIMER1, HWA_OCRB);
  HWA_VDCL(HWA_TIMER1, HWA_IMSK);

  HWA_VDCL(HWA_TIMER, HWA_MODE);
  HWA_VDCL(HWA_TIMER, HWA_CLK);
  HWA_VDCL(HWA_TIMER, HWA_CLKHZ);
  /* HWA_VDCL(HWA_TIMER, HWA_PSC); */
  /* HWA_VDCL(HWA_TIMER, HWA_MAX); */
  HWA_VDCL(HWA_TIMER, HWA_HZ);
  HWA_VDCL(HWA_TIMER, HWA_PERIOD);
} HWA_TIMER1 ;


#define hwa_timer_begin_timer1(reset)			\
  HWA_PINIT(HWA_TIMER1, HWA_TIMER1);			\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_CCRA, reset);	\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_CCRB, reset);	\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_CCRC, reset);	\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_OCRA, reset);	\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_OCRB, reset);	\
  HWA_VINIT(HWA_TIMER1, HWA_TIMER1, HWA_IMSK, reset);	\
							\
  HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_MODE,  reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_CLK,   reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_CLKHZ, reset);	\
  /* HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_PSC, reset); */	\
  /* HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_MAX, reset); */	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_HZ, reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER1, HWA_PERIOD, reset);


inline void
hwa_timer_commit_timer1 ( HWA_CORE *core, HWA_TIMER1 *p )
{
  if ( !p->used )
    return ;

  /* u16       psc     = HWA_GETVR(p, HWA_PSC,   0); */
  /* u32       max     = HWA_GETVR(p, HWA_MAX,   0); */
  u8  mode   = HWA_GETVR(p,    HWA_MODE,   0);
  u8  clk    = HWA_GETVR(p,    HWA_CLK,    0);
  u32 clkhz  = HWA_GETVR(p,    HWA_CLKHZ,  0) ; /* prescaler output fq  */
  u32 hz     = HWA_GETVR(p,    HWA_HZ,     0);
  u32 period = HWA_GETVR(p,    HWA_PERIOD, 0);
  //  u32 syshz  = HWA_GETVR(core, HWA_SYSHZ,  0);

  u32 srchz ;
  u16 psc ;
  u32 max ;
  /* if ( max != 0 ) */
  /*   max++ ; */

  /*	Mode
   */
  /* if ( mode ) { */
    /* if ( hz == 0 && psc == 0 && max == 0 ) */
    /*   HWA_ERROR("HWA_TIMER1: needs at least two of HZ, PSC, or MAX to be set.", 0); */

  if ( mode == 0 ) {
  }
  /* else if ( mode == HWA_TIMER_MODE_PERIODIC_IRQ ) { */
  /*   HWA_ERROR("Not implemented."); */
  /* } */
  /*   else if ( mode == HWA_TIMER_MODE_COUNTER ) { */
  /*     HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM3, 0 ); */
  /*     HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM2, 0 ); */
  /*     HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM1, 0 ); */
  /*     HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM0, 0 ); */

  /*     /\* if ( (clk == 0 || clk == HWA_TIMER_CLK_SYS_PSC) && psc == 0 ) *\/ */
  /*     /\* 	HWA_ERROR("Missing prescaler setting."); *\/ */
  /*   } */
    else if ( mode == HWA_TIMER_MODE_LOOP ) {
      /*
       *	Mode CTC: loops from 0 to OCRA, IRQ on compare match A
       */
      HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM3, 0 );
      HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM2, 1 );
      HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM1, 0 );
      HWA_SETVB(HWA_TIMER1, p, HWA_TIMER1_WGM0, 0 );
      /* u32 match	= HWA_GETVR(p, HWA_TIMER1_MATCH_LOOP, 0); */
      /* if ( match ) */
      /* 	max = match+1 ; */
    }
    else
      HWA_ERROR("Timer mode not supported.");
  /* } */
  /* else */
  /*   HWA_ERROR("Timer mode not supported."); */


  /*	Source clock frequency
   */
  if ( clk == 0 ) {
    srchz = HWA_GETVR(core, HWA_SYSHZ, 0) ;
  }
  else
    HWA_ERROR("Timer source clock not supported.");

  /*	Prescaler
   */
  if ( clkhz )
    psc = srchz / clkhz ;

  /* if ( psc != 8 ) */
  /*   HWA_ERROR("FOO"); */

  if ( hz == 0 && period == 0 /* && HWA_SR(p, HWA_PERIOD, mmask) != 0 */ ) {
    /*
     *  period set to 0 means that the timer is stopped
     */
    HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b000 );
  }
  else if ( hz ) {
    if ( psc == 0 ) {
      /*
       *  Prescaler value: 1, 8, 64, 256, 1024
       */
      psc = 1024 ; max = srchz / (hz * psc) ;
      if ( max * psc * hz != srchz ) { psc = 256 ; max = srchz / (hz * psc) ; }
      if ( max * psc * hz != srchz ) { psc =  64 ; max = srchz / (hz * psc) ; }
      if ( max * psc * hz != srchz ) { psc =   8 ; max = srchz / (hz * psc) ; }
      if ( max * psc * hz != srchz ) { psc =   1 ; max = srchz / (hz * psc) ; }
    }
    else
      max = srchz / psc / hz ;
    if ( max * psc * hz != srchz )
      HWA_ERROR("Timer1: can not find valid PSC/MAX combination for clkhz.");
  }
  else { /* period */
    /* if ( srchz == 0 ) */
    /*   HWA_ERROR("PSC==0"); */
    if ( psc == 0 ) {
      /* HWA_ERROR("PSC"); */
      psc = 1024 ; max = period / psc ;
      if ( max * psc != period ) { psc = 256 ; max = period / psc ; }
      if ( max * psc != period ) { psc =  64 ; max = period / psc ; }
      if ( max * psc != period ) { psc =   8 ; max = period / psc ; }
      if ( max * psc != period ) { psc =   1 ; max = period / psc ; }
    }
    else {
      max = period / psc ;
      if ( max != 65536 )
	HWA_ERROR("FOO");
    }
    if ( max * psc != period )
      HWA_ERROR("Timer1: can not find valid PSC/MAX combination for period.");
  }

  if ( hz != 0 || period != 0 ) {
    HWA_SETVB( HWA_TIMER1, p, HWA_OCRA, -1, 0, max-1 );

    if ( psc == 1 )         HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b001 );
    else if ( psc == 8 )    HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b010 );
    else if ( psc == 64 )   HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b011 );
    else if ( psc == 256 )  HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b100 );
    else if ( psc == 1024 ) HWA_SETVB( HWA_TIMER1, p, HWA_TIMER1_CS, 0b101 );
  }

  HWA_COMMIT(core, HWA_TIMER, p, HWA_MODE);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLK);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLKHZ);
  /* HWA_COMMIT(core, HWA_TIMER, p, HWA_PSC); */
  /* HWA_COMMIT(core, HWA_TIMER, p, HWA_MAX); */
  HWA_COMMIT(core, HWA_TIMER, p, HWA_HZ);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PERIOD);

  HWA_COMMIT(core, HWA_TIMER1, p, HWA_CCRA);
  HWA_COMMIT(core, HWA_TIMER1, p, HWA_CCRB);
  HWA_COMMIT(core, HWA_TIMER1, p, HWA_CCRC);
  HWA_COMMIT(core, HWA_TIMER1, p, HWA_OCRA);
  HWA_COMMIT(core, HWA_TIMER1, p, HWA_OCRB);
  HWA_COMMIT(core, HWA_TIMER1, p, HWA_IMSK);

  p->used = 0 ;
}


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_timer_set_count(pname, value)	\
  HW_HR(pname, CNT) = value ;

#define HWA_TIMER1_set_period(p)		\
  HW_SETHR(HWA_TIMER1, HWA_TIMER1, HWA_OCRA, p-1)

#define HWA_TIMER1_set_prescaler(psc)					\
  do {									\
    if ( psc == 0 )         HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b000 ); \
    else if ( psc == 1 )    HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b001 ); \
    else if ( psc == 8 )    HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b010 ); \
    else if ( psc == 64 )   HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b011 ); \
    else if ( psc == 256 )  HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b100 ); \
    else if ( psc == 1024 ) HW_SETHB( HWA_TIMER1, HWA_TIMER1, HWA_TIMER1_CS, 0b101 ); \
    else HWA_ERROR("Invalid PSC");\
  } while(0)

#define HWA_TIMER_COUNT_MAX(pname)\
  HWA_G3(HWA, pname, COUNT_MAX)


#endif
