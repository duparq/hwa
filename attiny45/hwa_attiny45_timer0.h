#ifndef HWA_ATTINY45_TIMER0_H
#define HWA_ATTINY45_TIMER0_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_TIMER0_BASE			0x20

#define HWA_TIMER0_HWA_CCRA		volatile, u8, 0x2A, 0x00, 0xF3
#define HWA_TIMER0_HWA_CCRB		volatile, u8, 0x33, 0x00, 0xCF
#define HWA_TIMER0_HWA_CNT		volatile, u8, 0x32, 0x00, 0xFF
#define HWA_TIMER0_HWA_OCRA		volatile, u8, 0x29, 0x00, 0xFF
#define HWA_TIMER0_HWA_OCRB		volatile, u8, 0x28, 0x00, 0xFF
#define HWA_TIMER0_HWA_IMSK		volatile, u8, 0x39, 0x00, 0x1A
#define HWA_TIMER0_HWA_IFR		volatile, u8, 0x38, 0x00, 0x1A


/*	Register bits definitions
 */
#define HWA_TIMER0_COMA			HWA_CCRA, 0b11,  6
#define HWA_TIMER0_COMB			HWA_CCRA, 0b11,  4
#define HWA_TIMER0_WGM1			HWA_CCRA, 0b1,   1
#define HWA_TIMER0_WGM0			HWA_CCRA, 0b1,   0

#define HWA_TIMER0_FOCA			HWA_CCRB, 0b1,   7
#define HWA_TIMER0_FOCB			HWA_CCRB, 0b1,   6
#define HWA_TIMER0_WGM2			HWA_CCRB, 0b1,   3
#define HWA_TIMER0_CS2			HWA_CCRB, 0b1,   2
#define HWA_TIMER0_CS1			HWA_CCRB, 0b1,   1
#define HWA_TIMER0_CS0			HWA_CCRB, 0b1,   0
#define HWA_TIMER0_CS			HWA_CCRB, 0b111, 0

#define HWA_TIMER0_EXCLK		HWA_ASSR, 0b1,   6
#define HWA_TIMER0_AS			HWA_ASSR, 0b1,   5

/* #define HWA_TIMER0_IRQ_OCB		HWA_IMSK, 0b1,   2 */
/* #define HWA_TIMER0_IRQ_OCA		HWA_IMSK, 0b1,   1 */
/* #define HWA_TIMER0_IRQ_OVF		HWA_IMSK, 0b1,   0 */
/* #define HWA_TIMER0_IRQ_OVIE		HWA_IMSK, 0b1,   0 */
/* #define HWA_TIMER0_IRQ_PERIODIC		HWA_TIMER0_IRQ_OCA */
/* #define HWA_TIMER0_OCFB			HWA_IFR, 0b1, 2 */
/* #define HWA_TIMER0_OCFA			HWA_IFR, 0b1, 1 */
/* #define HWA_TIMER0_OVF			HWA_IFR, 0b1, 0 */

#define HWA_TIMER0_COUNT_MAX		255

#define HWA_TIMER0_MATCH_A		HWA_OCRA
#define HWA_TIMER0_MATCH_B		HWA_OCRB

/*	Flags
 */
#define HWA_TIMER0_FLAG_MATCH_A		HWA_IFR, 0b1, 4
#define HWA_TIMER0_FLAG_MATCH_B		HWA_IFR, 0b1, 3
#define HWA_TIMER0_FLAG_OVERFLOW	HWA_IFR, 0b1, 1

/* #define HWA_TIMER0_FLAG_LOOP		HWA_IFR, 0b1, 1 */
/* #define HWA_TIMER0_FLAG_MATCH_A		HWA_IFR, 0b1, 1 */
/* #define HWA_TIMER0_FLAG_MATCH_LOOP	HWA_IFR, 0b1, 1 */
/* #define HWA_TIMER0_FLAG_OVF		HWA_IFR, 0b1, 0 */

/*	Interrupts
 */
#define HWA_TIMER0_IRQE_MATCH_A		HWA_IMSK, 0b1, 4
#define HWA_TIMER0_IRQE_MATCH_B		HWA_IMSK, 0b1, 3
#define HWA_TIMER0_IRQE_OVERFLOW	HWA_IMSK, 0b1, 1
/* #define HWA_TIMER0_IRQE_MATCH_B		HWA_IMSK, 0b1, 2 */
/* #define HWA_TIMER0_IRQE_LOOP		HWA_IMSK, 0b1, 1 */
/* #define HWA_TIMER0_IRQE_MATCH_A		HWA_IMSK, 0b1, 1 */
/* #define HWA_TIMER0_IRQE_MATCH_LOOP	HWA_IMSK, 0b1, 1 */
/* #define HWA_TIMER0_IRQE_OVF		HWA_IMSK, 0b1, 0 */
/* #define HWA_TIMER0_IRQE_OVERFLOW	HWA_IMSK, 0b1, 0 */

/*	Pins
 */
/* #define OC2A				PB3 */
/* #define OC2B				PD3 */

/* #define HWA_TIMER0_PIN_MATCH_LOOP	OC2A */
/* #define HWA_TIMER0_PIN_MATCH_A		OC2A */
/* #define HWA_TIMER0_PIN_MATCH_B		OC2B */


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_TIMER0, HWA_CCRA);
  HWA_VDCL(HWA_TIMER0, HWA_CCRB);
  HWA_VDCL(HWA_TIMER0, HWA_OCRA);
  HWA_VDCL(HWA_TIMER0, HWA_OCRB);
  HWA_VDCL(HWA_TIMER0, HWA_IMSK);
  HWA_VDCL(HWA_TIMER0, HWA_IFR);

  HWA_VDCL(HWA_TIMER, HWA_MODE);
  HWA_VDCL(HWA_TIMER, HWA_CLK);
  HWA_VDCL(HWA_TIMER, HWA_CLKHZ);
  HWA_VDCL(HWA_TIMER, HWA_PSC);
  HWA_VDCL(HWA_TIMER, HWA_MAX);
  HWA_VDCL(HWA_TIMER, HWA_HZ);
  HWA_VDCL(HWA_TIMER, HWA_PERIOD);
} HWA_TIMER0 ;


#define hwa_timer_begin_timer0(reset)			\
  HWA_PINIT(HWA_TIMER0, HWA_TIMER0)			\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_CCRA,  reset);	\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_CCRB,  reset);	\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_OCRA,  reset);	\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_OCRB,  reset);	\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_IMSK,  reset);	\
  HWA_VINIT(HWA_TIMER0, HWA_TIMER0, HWA_IFR,   reset);	\
							\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_MODE,   reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_CLK,    reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_CLKHZ,  reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_PSC,    reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_MAX,    reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_HZ,     reset);	\
  HWA_VINIT(HWA_TIMER, HWA_TIMER0, HWA_PERIOD, reset);


inline void
hwa_timer_commit_timer0 ( HWA_CORE *core, HWA_TIMER0 *p )
{
  if ( !p->used )
    return ;

  u8	mode	= HWA_GETVR(p, HWA_MODE,   0);
  u8	clk	= HWA_GETVR(p, HWA_CLK,    0);
  u32	clkhz	= HWA_GETVR(p, HWA_CLKHZ,  0);
  u16	psc	= HWA_GETVR(p, HWA_PSC,    0);
  //  u32	max	= HWA_GETVR(p, HWA_MAX,    0);
  //  u32	hz	= HWA_GETVR(p, HWA_HZ,     0);

  u32	syshz	= HWA_GETVR(core, HWA_SYSHZ,  0);

  /*  Mode
   */
  if ( mode == 0 ) {
    HWA_ERROR("TIMER0: mode is not set.");
  }
  else if ( mode == HWA_TIMER_MODE_NORMAL ) {

    /*  Timer loops from 0 to TIMER_MAX
     */
    HWA_SETVB(HWA_TIMER0, p, HWA_TIMER0_WGM2, 0 );
    HWA_SETVB(HWA_TIMER0, p, HWA_TIMER0_WGM1, 0 );
    HWA_SETVB(HWA_TIMER0, p, HWA_TIMER0_WGM0, 0 );
  }
  else
    HWA_ERROR("Timer mode not supported.");

  /*  Clock source
   */
  if ( clk == 0 ) {
    HWA_ERROR("TIMER0: clock source is not set.");
  }
  else if ( clk == HWA_TIMER_CLK_NONE ) {
    HWA_ERROR("");
    psc = 0 ;
  }
  else if ( clk == HWA_TIMER_CLK_SYSPSC ) {
    if ( psc == 0 ) {
      if ( clkhz == 0 )
	HWA_ERROR("TIMER0: neither clockhz nor prescaler is set.");
      if ( clkhz != 2000000 )
    HWA_ERROR("");
      if ( syshz != 16000000 )
	HWA_ERROR("");
      psc = syshz / clkhz ;
    }
    /* if ( psc != 8 ) */
  }
  else
    HWA_ERROR("TIMER0: clock source not supported.");

  /* *(u32*)0 = psc ; */

  if ( psc == 0 )         HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b000 );
  else if ( psc == 1 )    HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b001 );
  else if ( psc == 8 )    HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b010 );
  else if ( psc == 64 )   HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b011 );
  else if ( psc == 256 )  HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b100 );
  else if ( psc == 1024 ) HWA_SETVB( HWA_TIMER0, p, HWA_TIMER0_CS, 0b101 );
  else
    HWA_ERROR("TIMER0: invalid prescaler value.");

  /* if ( psc != 8 ) */
  /*   HWA_ERROR(""); */

  HWA_COMMIT(core, HWA_TIMER, p, HWA_MODE   );
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLK    );	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLKHZ  );	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PSC    );	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_MAX    );	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_HZ     );	  
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PERIOD );

  HWA_COMMIT(core, HWA_TIMER0, p, HWA_CCRA);
  HWA_COMMIT(core, HWA_TIMER0, p, HWA_CCRB);
  HWA_COMMIT(core, HWA_TIMER0, p, HWA_OCRA);
  HWA_COMMIT(core, HWA_TIMER0, p, HWA_OCRB);
  HWA_COMMIT(core, HWA_TIMER0, p, HWA_IFR );
  HWA_COMMIT(core, HWA_TIMER0, p, HWA_IMSK);

  p->used = 0 ;
}


#endif
