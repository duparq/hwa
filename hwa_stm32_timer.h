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
#define HWA_TIMER_HWA_SR		volatile, u16, 0x10, 0x0000, 0x1E7F
#define HWA_TIMER_HWA_EGR		volatile, u16, 0x14, 0x0000, 0x005F
#define HWA_TIMER_HWA_CNT		volatile, u16, 0x24, 0x0000, 0xFFFF
#define HWA_TIMER_HWA_PSC		volatile, u16, 0x28, 0x0000, 0xFFFF
#define HWA_TIMER_HWA_ARR		volatile, u16, 0x2C, 0x0000, 0xFFFF


/*	Convenient registers
 */
#define HWA_TIMER_HWA_MODE		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLK		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLKHZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_IRQHZ		, u32, -1, 0, 0xFFFFFFFF



#define HWA_TIMER_COUNT_MAX(pname)	65535

#define HWA_TIMER_IRQ_OVERFLOW		0
#define HWA_TIMER_IRQ_ALL		64

#define HWA_TIMER_MMS			HWA_CR2, 0b111, 4
#define HWA_TIMER_MMS_

#define HWA_TIMER_SMCR_SMS		HWA_SMCR, 0b111, 0


#define HWA_TIMER_ARPE			HWA_CR1, 0b1, 7

/*	Center-aligned mode selection
 */
#define HWA_TIMER_CMS			HWA_CR1, 0b11, 5
#define HWA_TIMER_CMS_COUNT_SINGLE_DIR	0b00	/* (RESET) Count up or down depending on DIR	*/
#define HWA_TIMER_CMS_1			0b01
#define HWA_TIMER_CMS_2			0b10
#define HWA_TIMER_CMS_3			0b11

/*	Count direction
 */
#define HWA_TIMER_DIR			HWA_CR1, 0b1, 4
#define HWA_TIMER_DIR_UP		0b0	/* (RESET) */
#define HWA_TIMER_DIR_DOWN		0b1

/*	OPM: One-pulse mode
 */
#define HWA_TIMER_OPM			HWA_CR1, 0b1, 3
#define HWA_TIMER_OPM_LOOP		0b0	/* (RESET) */
#define HWA_TIMER_OPM_ONCE		0b1

/*	URS: Update request source
 */
#define HWA_TIMER_URS			HWA_CR1, 0b1, 2
#define HWA_TIMER_URS_ANY		0b0	/* (RESET) */
#define HWA_TIMER_URS_XFLOW		0b1

/*	UDIS: Update disable
 */
#define HWA_TIMER_UDIS			HWA_CR1, 0b1, 1

/*	CEN: Counter enable
 */
#define HWA_TIMER_CEN			HWA_CR1, 0b1, 0
#define HWA_TIMER_CEN_DISABLE		0b0	/* (RESET) */
#define HWA_TIMER_CEN_ENABLE		0b1

#define HWA_TIMER_UG			HWA_EGR, 0b1, 0

/*	Interrupts
 */
#define HWA_TIMER_UIE			HWA_DIER, 0b1, 0	/* Update interrupt enable */


/*	Parameters
 */
#define HWA_TIMER_MODE_PERIODIC_IRQ	1
#define HWA_TIMER_MODE_DELAYED_IRQ	2

#define HWA_TIMER_CLK_APB1_PSC		0b00	/* (RESET) */
#define HWA_TIMER_CLK_TOSC_PSC		0b01
#define HWA_TIMER_CLK_EXTERN		0b11

#define HWA_TIMER_DIR_COUNT_UP		0
#define HWA_TIMER_DIR_COUNT_DOWN	1


typedef struct {
  HWA_PDCL()
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
  hwa_timer_commit(HWA_CORE0, HWA_TIMER2);			\
  hwa_timer_commit(HWA_CORE0, HWA_TIMER3); \
  hwa_timer_commit(HWA_CORE0, HWA_TIMER4); \
  hwa_timer_commit(HWA_CORE0, HWA_TIMER5);


inline u32
_hwa_find_arrdiv ( u32 srcdiv )
{
  u32 pscdiv = 65536 ;
  u32 arrdiv = srcdiv / pscdiv ;
  if ( arrdiv < 1 )
    arrdiv = 1 ;
  arrdiv-- ;

  /*	FIXME: can not have GCC optimize loops using constants only?
   *	Unroll it manually partly.
   */
#define inst						\
    arrdiv++ ;						\
    pscdiv = srcdiv/arrdiv ;				\
    if ( arrdiv > pscdiv )				\
      return 0 ;					\
    if ( pscdiv <= 0x10000 && pscdiv*arrdiv==srcdiv )	\
      return arrdiv

  inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ; inst ;

  /* for(;;) { inst ; } */
  return 0 ;

#undef inst
}


inline void
hwa_timer_commit ( HWA_CORE *core, HWA_TIMER *p )
{
  if ( !p->used )
    return ;

  /*	Mode
   */
  u8 mode	= HWA_NVAL(p, HWA_MODE,	0) ;
  u8 clk	= HWA_NVAL(p, HWA_CLK,	0) ;
  u32 clkhz	= HWA_NVAL(p, HWA_CLKHZ, 0) ;
  u32 irqhz	= HWA_NVAL(p, HWA_IRQHZ, 0) ;

  if ( mode == 0 )
    HWA_ERROR("Timer mode not set.");
  else if ( mode == HWA_TIMER_MODE_PERIODIC_IRQ ) {
    /*
     *	Counter loops from 0 to reload value and fires interrupt when restarts
     */
    if ( irqhz == 0 )
      HWA_ERROR("PERIODIC_IRQ mode needs IRQHZ to be set.");
    
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_CMS, HWA_TIMER_CMS_COUNT_SINGLE_DIR);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_DIR, HWA_TIMER_DIR_UP);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_OPM, HWA_TIMER_OPM_LOOP);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_UIE, 1);
  }
  else if ( mode == HWA_TIMER_MODE_DELAYED_IRQ ) {
    /*
     *	Counter counts from 0 to reload value and fires interrupt
     */
    if ( irqhz == 0 )
      HWA_ERROR("DELAYED_IRQ mode needs period to be set.");

    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_CMS, HWA_TIMER_CMS_COUNT_SINGLE_DIR);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_DIR, HWA_TIMER_DIR_UP);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_OPM, HWA_TIMER_OPM_ONCE);
    HWA_VBSET(HWA_TIMER, p, HWA_TIMER_UIE, 1);
  }
  else
    HWA_ERROR("Timer mode not supported.");


  if ( HWA_VREG(p, HWA_IRQHZ, mvmask) &&
       mode == HWA_TIMER_MODE_DELAYED_IRQ ) {
    /*
     *	Source clock
     */
    u32	srchz ;
    u32	srcdiv ;	/* srcdiv = pscdiv * arrdiv */
    u32	pscdiv ;	/* PSC+1 */
    u32	arrdiv ;	/* ARR+1 */
    u32	period = irqhz ;

    if ( clk == 0xFF || clk == HWA_TIMER_CLK_APB1_PSC ) {
      HWA_VBSET(HWA_TIMER, p, HWA_TIMER_SMCR_SMS, 0);
      srchz = HWA_NVAL(core, HWA_APB1HZ, 0) ;
      if (HWA_NVAL(core, HWA_APB1HZ, 0) != HWA_NVAL(core, HWA_AHBHZ, 0))
	srchz *= 2 ;
      srcdiv = (u64)srchz * period / 1000000 ;
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
      else {
	pscdiv = srchz/clkhz ;
	arrdiv = period * clkhz/1000000 ;
      }
      HWA_HREG(HWA_TIMER, p, HWA_ARR) = arrdiv-1 ;
    }

    /*	Prescaler
     */
    if ( pscdiv != 0 ) {
      if ( pscdiv > 0xFFFF )
	HWA_WARN("Prescaler value overflow.");
      /* if ( pscdiv * clkhz != srchz ) */
      /* 	HWA_WARN("Prescaler value error."); */

      HWA_HREG(HWA_TIMER, p, HWA_PSC) = (u16)pscdiv-1 ;
    }
    else
      HWA_WARN("Prescaler value error.");

    HWA_HBSET(HWA_TIMER, p, HWA_TIMER_OPM, 1) ;
    HWA_HREG(HWA_TIMER, p, HWA_EGR) = HWA_BMSK(HWA_TIMER_UG) ;
    HWA_HREG(HWA_TIMER, p, HWA_SR) = 0 ;
    //    HWA_HBSET(HWA_TIMER, p, HWA_TIMER_UIE, 1) ;	/* commit below */
  }


  if ( mode == HWA_TIMER_MODE_PERIODIC_IRQ ) {
    /*	Source clock
     */
    u32	srchz ;
    u32	srcdiv ;	/* srcdiv = pscdiv * arrdiv */
    u32	pscdiv ;	/* PSC+1 */
    u32	arrdiv ;	/* ARR+1 */
    if ( clk == 0xFF || clk == HWA_TIMER_CLK_APB1_PSC ) {
      HWA_VBSET(HWA_TIMER, p, HWA_TIMER_SMCR_SMS, 0);
      srchz = HWA_NVAL(core, HWA_APB1HZ, 0) ;
      if (HWA_NVAL(core, HWA_APB1HZ, 0) != HWA_NVAL(core, HWA_AHBHZ, 0))
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
      else {
	pscdiv = srchz/clkhz ;
	arrdiv = clkhz/irqhz ;
      }
      HWA_HREG(HWA_TIMER, p, HWA_ARR) = arrdiv-1 ;
    }

    /*	Prescaler
     */
    if ( pscdiv != 0 ) {
      if ( pscdiv > 0xFFFF )
	HWA_WARN("Prescaler value overflow.");
      if ( pscdiv * clkhz != srchz )
	HWA_WARN("Prescaler value error.");

      HWA_HREG(HWA_TIMER, p, HWA_PSC) = (u16)pscdiv-1 ;
    }
    else
      HWA_WARN("Prescaler value error.");
  }

  HWA_COMMIT(core, HWA_TIMER, p, HWA_CR1);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CR2);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_SMCR);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_DIER);

  p->used = 0 ;
}


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define hw_timer_read_count(pname)	\
  HW_HR(HWA_TIMER, pname, HWA_CNT)

#define hw_timer_write_count(pname, count)	\
  HW_HR(HWA_TIMER, pname, HWA_CNT) = count

#define hw_timer_clear_irq(pname, irq)					\
  do {									\
    if ( HWA_TIMER_IRQ_##irq == HWA_TIMER_IRQ_ALL )			\
      HW_HR(HWA_TIMER, pname, HWA_SR) = 0 ;				\
    else								\
      HW_HR(HWA_TIMER, pname, HWA_SR) = ~(0b1<<(HWA_TIMER_IRQ_##irq & 0x1F)) ; \
  } while(0)


#define hw_timer_turn(pname, pstat)					\
  HW_HBSET(HWA_TIMER, pname, HWA_TIMER_CEN, HWA_STATE_##pstat)

#define hw_timer_reset(pname)						\
  do {									\
    u16 dier = HW_HR(HWA_TIMER, pname, HWA_DIER);			\
    HW_HR(HWA_TIMER, pname, HWA_DIER) = dier & ~HWA_BMSK(HWA_TIMER_UIE); \
    HW_HR(HWA_TIMER, pname, HWA_EGR) = HWA_BMSK(HWA_TIMER_UG) ;	\
    HW_HR(HWA_TIMER, pname, HWA_SR) = 0 ;				\
    HW_HR(HWA_TIMER, pname, HWA_DIER) = dier;				\
  } while(0);

#define hw_timer_restart(pname)						\
  do {									\
    u16 dier = HW_HR(HWA_TIMER, pname, HWA_DIER);			\
    HW_HR(HWA_TIMER, pname, HWA_DIER) = dier & ~HWA_BMSK(HWA_TIMER_UIE); \
    HW_HR(HWA_TIMER, pname, HWA_EGR) = HWA_BMSK(HWA_TIMER_UG) ;	\
    HW_HR(HWA_TIMER, pname, HWA_SR) = 0 ;				\
    HW_HR(HWA_TIMER, pname, HWA_DIER) = dier;				\
    HW_HBSET(HWA_TIMER, pname, HWA_TIMER_CEN, 1);			\
  } while(0);

#define hw_timer_set_period(pname, value)				\
  do {									\
    if ( hwa_debug && HW_HR(HWA_TIMER, pname, HWA_CNT) > value-3 )	\
      while(1) {}							\
    HW_HR(HWA_TIMER, pname, HWA_ARR) = (value)-1 ;			\
  } while(0)


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_timer_set_mode(pname, mode)			\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_VBSET(HWA_TIMER, pname, HWA_MODE, -1, 0, HWA_TIMER_MODE_##mode);

#define hwa_timer_set_irqhz(pname, hz)				\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_VBSET(HWA_TIMER, pname, HWA_IRQHZ, -1, 0, hz);

#define hwa_timer_set_period(pname, us)				\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_VBSET(HWA_TIMER, pname, HWA_IRQHZ, -1, 0, us);

/* #define hwa_timer_set_top(pname, top)				\ */
/*   hwa_prph_turn_clk(pname, ON);					\ */
/*   HWA_VBSET(HWA_TIMER, pname, HWA_ARR, -1, 0, top); */

/* #define hwa_timer_connect_clk(pname, aclk)		\ */
/*   hwa_prph_turn_clk(pname, ON);				\ */
/*   HWA_XSET((pname), clk, HWA_TIMER_CLK_##aclk); */

#define hwa_timer_set_clkhz(pname, hz)			\
  hwa_prph_turn_clk(pname, ON);				\
  HWA_VBSET(HWA_TIMER, pname, HWA_CLKHZ, -1, 0, hz);

#define hwa_timer_turn_irq(pname, irq, state)				\
  hwa_prph_turn_clk(pname, ON);						\
  HWA_VBSET(HWA_TIMER, pname, HWA_DIER, 0b1, HWA_TIMER_IRQ_##irq, HWA_STATE_##state)

#define hwa_timer_turn(pname, pstat)					\
  hwa_prph_turn_clk(pname, ON);						\
  HWA_VBSET(HWA_TIMER, pname, HWA_TIMER_CEN, HWA_STATE_##pstat)

#endif
