#ifndef HWA_STM32_TIMER_H
#define HWA_STM32_TIMER_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_TIMER2_BASE			HWA_APB1+0x0000 /* 0x40000000 */
#define HWA_TIMER3_BASE			HWA_APB1+0x0400 /* 0x40000400 */
#define HWA_TIMER4_BASE			HWA_APB1+0x0800 /* 0x40000800 */
#define HWA_TIMER5_BASE			HWA_APB1+0x0C00 /* 0x40000C00 */

#define HWA_TIMER_HWA_CR1		volatile, u16, 0x00, 0x0000, 0x03FF
#define HWA_TIMER_HWA_CR2		volatile, u16, 0x04, 0x0000, 0x00F8
#define HWA_TIMER_HWA_SMCR		volatile, u16, 0x08, 0x0000, 0xFFF7
#define HWA_TIMER_HWA_DIER		volatile, u16, 0x0C, 0x0000, 0x5F5F
#define HWA_TIMER_HWA_SR		volatile, u16, 0x10, 
#define HWA_TIMER_HWA_CNT		volatile, u16, 0x24, 
#define HWA_TIMER_HWA_PSC		volatile, u16, 0x28, 
#define HWA_TIMER_HWA_ARR		volatile, u16, 0x2C,

/*	Non-committable registers
 */
#define HWA_TIMER_HWA_MODE		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLK		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLKHZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_IRQHZ		, u32, -1, 0, 0xFFFFFFFF

#define HWA_TIMER_COUNT_MAX(pname)	65535

#define HWA_TIMER_IRQ_OVERFLOW		0
/* #define HWA_TIMER_IRQBIT_OVERFLOW	0 */

#define HWA_TIMER_CR2_MMS		HWA_CR2, 0b111, 4
#define HWA_TIMER_CR2_MMS_

#define HWA_TIMER_SMCR_SMS		HWA_SMCR, 0b111, 0


/*	Center-aligned mode selection
 */
#define HWA_TIMER_CR1_CMS		HWA_CR1, 0b11, 5
#define HWA_TIMER_CR1_CMS_0		0b00	/* (RESET) Count up or down depending on DIR	*/
#define HWA_TIMER_CR1_CMS_1		0b01
#define HWA_TIMER_CR1_CMS_2		0b10
#define HWA_TIMER_CR1_CMS_3		0b11

/*	Count direction
 */
#define HWA_TIMER_CR1_DIR		HWA_CR1, 0b1, 4
#define HWA_TIMER_CR1_DIR_UP		0b0	/* (RESET) */
#define HWA_TIMER_CR1_DIR_DOWN		0b1

/*	OPM: One-pulse mode
 */
#define HWA_TIMER_CR1_OPM		HWA_CR1, 0b1, 3
#define HWA_TIMER_CR1_OPM_LOOP		0b0	/* (RESET) */
#define HWA_TIMER_CR1_OPM_ONCE		0b1

/*	URS: Update request source
 */
#define HWA_TIMER_CR1_URS		HWA_CR1, 0b1, 2
#define HWA_TIMER_CR1_URS_ANY		0b0	/* (RESET) */
#define HWA_TIMER_CR1_URS_XFLOW		0b1

/*	UDIS: Update disable
 */
#define HWA_TIMER_CR1_UDIS		HWA_CR1, 0b1, 1

/*	CEN: Counter enable
 */
#define HWA_TIMER_CR1_CEN		HWA_CR1, 0b1, 0
#define HWA_TIMER_CR1_CEN_DISABLE	0b0	/* (RESET) */
#define HWA_TIMER_CR1_CEN_ENABLE	0b1

/*	Interrupts
 */
#define HWA_TIMER_DIER_UIE		HWA_DIER, 0b1, 0	/* Update interrupt enable */

/*	High-level settings
 */
#define HWA_TIMER_MODE_PERIODIC_IRQ	1

#define HWA_TIMER_CLK_APB1_PSC		0b00	/* (RESET) */
#define HWA_TIMER_CLK_TOSC_PSC		0b01
#define HWA_TIMER_CLK_EXTERN		0b11

#define HWA_TIMER_DIR_COUNT_UP		0
#define HWA_TIMER_DIR_COUNT_DOWN	1


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_TIMER, HWA_CR1);
  HWA_VDCL(HWA_TIMER, HWA_CR2);
  HWA_VDCL(HWA_TIMER, HWA_SMCR);
  HWA_VDCL(HWA_TIMER, HWA_DIER);

  HWA_VDCL(HWA_TIMER, HWA_MODE);
  HWA_VDCL(HWA_TIMER, HWA_CLK);
  HWA_VDCL(HWA_TIMER, HWA_CLKHZ);
  HWA_VDCL(HWA_TIMER, HWA_IRQHZ);
} HWA_TIMER ;

#define hwa_begin_timer(reset)			\
  hwa_timer_begin(HWA_TIMER2, reset)		\
  hwa_timer_begin(HWA_TIMER3, reset)		\
  hwa_timer_begin(HWA_TIMER4, reset)		\
  hwa_timer_begin(HWA_TIMER5, reset)

#define hwa_timer_begin(pname, reset)			\
  HWA_PINIT(HWA_TIMER, pname);				\
  HWA_VINIT(HWA_TIMER, pname, HWA_CR1, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_CR2, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_SMCR, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_DIER, reset);		\
							\
  HWA_VINIT(HWA_TIMER, pname, HWA_MODE, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_CLK, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_CLKHZ, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_IRQHZ, reset);

#define hwa_commit_timer()						\
  _hwa_timer_commit(hwa_nocommit, HWA_P(HWA_TIMER2), HWA_P(HWA_CLOCK0)); \
  _hwa_timer_commit(hwa_nocommit, HWA_P(HWA_TIMER3), HWA_P(HWA_CLOCK0)); \
  _hwa_timer_commit(hwa_nocommit, HWA_P(HWA_TIMER4), HWA_P(HWA_CLOCK0)); \
  _hwa_timer_commit(hwa_nocommit, HWA_P(HWA_TIMER5), HWA_P(HWA_CLOCK0));


inline u32
_hwa_find_arrdiv ( u32 srcdiv )
{
  u32 pscdiv ;
  u32 arrdiv = srcdiv / 65536 ;
  if ( arrdiv < 1 )
    arrdiv = 1 ;

  /*	FIXME: can not have GCC optimize loops using constants only?
   *	Unroll it manually partly.
   */
#define inst						\
    arrdiv++ ;						\
    pscdiv = srcdiv/arrdiv ;				\
    if ( arrdiv > pscdiv )				\
      return 0 ;					\
    if ( pscdiv < 0x10000 && pscdiv*arrdiv==srcdiv )	\
      return arrdiv

  inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ;

  /* for(;;) { inst ; } */
  return 0 ;

#undef inst
}


inline void
_hwa_timer_commit ( u8 dry, HWA_TIMER *p, HWA_CLOCK *c )
{
  if ( !p->used )
    return ;

  /*	Mode
   */
  /* if ( p->mode == HWA_TIMER_MODE_PERIODIC_IRQ ) { */
  u8 mode = HWA_NVALP(p, HWA_MODE) ;
  u8 clk = HWA_NVALP(p, HWA_CLK) ;
  u32 clkhz = HWA_NVALP(p, HWA_CLKHZ) ;
  u32 irqhz = HWA_NVALP(p, HWA_IRQHZ) ;

  if ( mode == 0xFF )
    HWA_ERROR("Timer mode not set.");
  else if ( mode == HWA_TIMER_MODE_PERIODIC_IRQ ) {
    /*
     *	Counter loops from 0 to reload value and fires interrupt when restarts
     */
    if ( irqhz == HWA_NONE )
      HWA_ERROR("PERIODIC_IRQ mode needs IRQHZ to be set.");
    
    HWA_VSETP(HWA_TIMER, p, HWA_TIMER_CR1_CMS, HWA_TIMER_CR1_CMS_0);
    HWA_VSETP(HWA_TIMER, p, HWA_TIMER_CR1_DIR, HWA_TIMER_CR1_DIR_UP);
    HWA_VSETP(HWA_TIMER, p, HWA_TIMER_CR1_OPM, HWA_TIMER_CR1_OPM_LOOP);
    HWA_VSETP(HWA_TIMER, p, HWA_TIMER_DIER_UIE, 1);
  }
  else
    HWA_ERROR("Timer mode not supported.");

  /*	Source clock
   */
  u32	srchz ;
  u32	srcdiv ;	/* srcdiv = pscdiv * arrdiv */
  u32	pscdiv ;	/* PSC+1 */
  u32	arrdiv ;	/* ARR+1 */
  if ( clk == 0xFF || clk == HWA_TIMER_CLK_APB1_PSC ) {
    HWA_VSETP(HWA_TIMER, p, HWA_TIMER_SMCR_SMS, 0);
    srchz = HWA_NVALP(c, HWA_APB1HZ) ;
    if (HWA_NVALP(c, HWA_APB1HZ) != HWA_NVALP(c, HWA_AHBHZ))
      srchz *= 2 ;
    srcdiv = srchz / irqhz ;
    if ( srcdiv * irqhz != srchz )
      HWA_ERROR("No valid divisor for IRQ_HZ.");
  }
  else
    HWA_ERROR("Timer source clock not supported.");

  /*	Reload value
   */
  if ( irqhz != 0 ) {
    if ( clkhz == 0 ) {
      arrdiv = _hwa_find_arrdiv(srcdiv);
      if ( arrdiv == 0 )
	HWA_ERROR("No valid value found for prescaler.");
      pscdiv = srcdiv/arrdiv ;
      clkhz = srchz/pscdiv ;
    }
    HWA_HREGP(HWA_TIMER, p, HWA_ARR) = arrdiv-1 ;
  }

  /*	Prescaler
   */
  if ( pscdiv != 0 ) {
    if ( pscdiv > 0xFFFF )
      HWA_WARN("Prescaler value overflow.");
    if ( pscdiv * clkhz != srchz )
      HWA_WARN("Prescaler value error.");

    HWA_HREGP(HWA_TIMER, p, HWA_PSC) = (u16)pscdiv-1 ;
  }
  else
    HWA_WARN("Prescaler value error.");

  HWA_COMMITP(dry, HWA_TIMER, p, HWA_CR1);
  HWA_COMMITP(dry, HWA_TIMER, p, HWA_CR2);
  HWA_COMMITP(dry, HWA_TIMER, p, HWA_SMCR);
  HWA_COMMITP(dry, HWA_TIMER, p, HWA_DIER);

  p->used = 0 ;
}


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

/* #define hw_timer_read_count(mname)		\ */
/*   HWA_HREG(mname, CNT) */

#define hw_timer_write_count(pname, count)	\
  HWA_HREG(HWA_TIMER, pname, CNT) = count ;

#define hw_timer_clr_irq(pname, irq)					\
  HWA_HSET(HWA_TIMER, pname, SR, 0b1, HWA_G2(HWA_TIMER_IRQ, irq), 0)

#define hw_timer_turn(pname, pstat)					\
  HWA_HSET(HWA_TIMER, pname, HWA_TIMER_CR1_CEN, HWA_STATE_##pstat)


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_timer_set_mode(pname, mode)			\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_VSETP(HWA_TIMER, HWA_P(pname), HWA_MODE, -1, 0, HWA_TIMER_MODE_##mode);

#define hwa_timer_set_irqhz(pname, hz)				\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_VSETP(HWA_TIMER, HWA_P(pname), HWA_IRQHZ, -1, 0, hz);

/* #define hwa_timer_connect_clk(pname, aclk)		\ */
/*   hwa_prph_turn_clk(pname, ON);				\ */
/*   HWA_XSETP(HWA_P(pname), clk, HWA_TIMER_CLK_##aclk); */

/* #define hwa_timer_set_clk_hz(pname, hz)		\ */
/*   hwa_prph_turn_clk(pname, ON);			\ */
/*   HWA_XSETP(HWA_P(pname), clkhz, hz); */

#define hwa_timer_turn_irq(pname, irq, state)				\
  hwa_prph_turn_clk(pname, ON);						\
  HWA_VSETP(HWA_TIMER, HWA_P(pname), HWA_DIER, 0b1, HWA_TIMER_IRQ_##irq, HWA_STATE_##state)

#define hwa_timer_turn(pname, pstat)					\
  hwa_prph_turn_clk(pname, ON);						\
  HWA_VSETP(HWA_TIMER, HWA_P(pname), HWA_TIMER_CR1_CEN, HWA_STATE_##pstat)

#endif
