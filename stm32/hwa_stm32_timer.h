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

#define HWA_TIMER_HWA_CR1		volatile, u32, 0x00, 0x00000000, 0x000003FF
#define HWA_TIMER_HWA_CR2		volatile, u32, 0x04, 0x00000000, 0x000000F8
#define HWA_TIMER_HWA_SMCR		volatile, u32, 0x08, 0x00000000, 0x0000FFF7
#define HWA_TIMER_HWA_DIER		volatile, u32, 0x0C, 0x00000000, 0x00005F5F
#define HWA_TIMER_HWA_SR		volatile, u32, 0x10, 0x00000000, 0x00001E7F
#define HWA_TIMER_HWA_EGR		volatile, u32, 0x14, 0x00000000, 0x0000005F
#define HWA_TIMER_HWA_CNT		volatile, u32, 0x24, 0x00000000, 0x0000FFFF
#define HWA_TIMER_HWA_PSC		volatile, u32, 0x28, 0x00000000, 0xFFFFFFFF
#define HWA_TIMER_HWA_ARR		volatile, u32, 0x2C, 0x00000000, 0xFFFFFFFF


/*	Convenient registers
 */
#define HWA_TIMER_HWA_MODE		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLK		, u8,  -1, 0, 0xFF
#define HWA_TIMER_HWA_CLKHZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_HZ		, u32, -1, 0, 0xFFFFFFFF
#define HWA_TIMER_HWA_PERIOD		, u32, -1, 0, 0xFFFFFFFF


#define HWA_TIMER_COUNT_MAX(pname)	65535

#define HWA_TIMER_IRQ_OVERFLOW		0
#define HWA_TIMER_IRQ_ALL		64

#define HWA_TIMER_MMS			HWA_CR2, 0b111, 4
#define HWA_TIMER_MMS_

#define HWA_TIMER_SMS			HWA_SMCR, 0b111, 0


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

/*	Flags
 */
#define HWA_TIMER_FLAG_LOOP		HWA_SR, 0b1, 0
#define HWA_TIMER_FLAG_PERIOD		HWA_SR, 0b1, 0

/*	Interrupts
 */
#define HWA_TIMER_UIE			HWA_DIER, 0b1, 0	/* Update interrupt enable */
#define HWA_TIMER_IRQE_LOOP		HWA_DIER, 0b1, 0
#define HWA_TIMER_IRQE_PERIOD		HWA_DIER, 0b1, 0


/*	Parameters
 */
#define HWA_TIMER_MODE_ONESHOT		1
#define HWA_TIMER_MODE_LOOP		2	/* Compatible ATmega */

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
  HWA_VDCL(HWA_TIMER, HWA_ARR);
  HWA_VDCL(HWA_TIMER, HWA_PSC);

  HWA_VDCL(HWA_TIMER, HWA_MODE);
  HWA_VDCL(HWA_TIMER, HWA_CLK);
  HWA_VDCL(HWA_TIMER, HWA_CLKHZ);
  HWA_VDCL(HWA_TIMER, HWA_HZ);
  HWA_VDCL(HWA_TIMER, HWA_PERIOD);
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
  HWA_VINIT(HWA_TIMER, pname, HWA_ARR, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_PSC, reset);		\
							\
  HWA_VINIT(HWA_TIMER, pname, HWA_MODE, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_CLK, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_CLKHZ, reset);	\
  HWA_VINIT(HWA_TIMER, pname, HWA_HZ, reset);		\
  HWA_VINIT(HWA_TIMER, pname, HWA_PERIOD, reset);

#define hwa_commit_timer()			\
  hwa_timer_commit(HWA_CORE0, HWA_TIMER2);	\
  hwa_timer_commit(HWA_CORE0, HWA_TIMER3);	\
  hwa_timer_commit(HWA_CORE0, HWA_TIMER4);	\
  hwa_timer_commit(HWA_CORE0, HWA_TIMER5);


/*	FIXME / TODO : to be reworked.
 */
inline u32
_hwa_find_lowest_arr ( u32 div )
{
  u32 psc = 65536 ;
  u32 arr = div / psc ;
  if ( arr < 2 ) /* It seems that no reload event is generated when ARR==0 (arr==1) */
    arr = 2 ;
  arr-- ;

  /*	FIXME: can not have GCC optimize loops using constants only?
   *	Unroll it manually partly.
   */
#define inst						\
    arr++ ;						\
    psc = div/arr ;					\
    if ( arr > psc )					\
      return 0 ;					\
    if ( psc <= 65536 && psc*arr==div )			\
      return arr

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

  /* REVISION of 52-gps */

  u8  mode   = HWA_GETVR(p, HWA_MODE,   0) ; /* timer mode           */
  u8  clk    = HWA_GETVR(p, HWA_CLK,    0) ; /* prescaler source clk */
  u32 clkhz  = HWA_GETVR(p, HWA_CLKHZ,  0) ; /* prescaler output fq  */
  u32 hz     = HWA_GETVR(p, HWA_HZ,     0) ; /* timer loop fq        */
  u32 period = HWA_GETVR(p, HWA_PERIOD, 0) ; /* timer loop period    */
  u32 syshz  = HWA_GETVR(core, HWA_SYSHZ, 0) ;

  if ( mode == 0 )
    HWA_ERROR("Timer mode not set.");
  else if ( mode == HWA_TIMER_MODE_ONESHOT ) {
    /*
     *	Count from 0 to reload value, then stop
     */
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_URS, 1);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_CMS, HWA_TIMER_CMS_COUNT_SINGLE_DIR);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_DIR, HWA_TIMER_DIR_UP);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_OPM, HWA_TIMER_OPM_ONCE);
  }
  else if ( mode == HWA_TIMER_MODE_LOOP ) {
    /*
     *	Loop from 0 to reload value
     */
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_URS, 1);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_CMS, HWA_TIMER_CMS_COUNT_SINGLE_DIR);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_DIR, HWA_TIMER_DIR_UP);
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_OPM, HWA_TIMER_OPM_LOOP);
  }
  else
    HWA_ERROR("Timer mode not supported.");

  if ( core->commit && hz == 0 && period == 0 )
    HWA_ERROR("None of hz or period is set.");

  u32	srchz ;	/* srchz = div * hz */
  u32	div = 0 ;	/* div = psc * arr */
  u32	psc = 0 ;	/* PSC+1 */
  u32	arr = 0 ;	/* ARR+1 */

  /*	Source clock
   */
  if ( clk == 0xFF || clk == HWA_TIMER_CLK_APB1_PSC ) {
    HWA_SETVB(HWA_TIMER, p, HWA_TIMER_SMS, 0);
    srchz = HWA_GETVR(core, HWA_APB1HZ, 0) ;
    if (HWA_GETVR(core, HWA_APB1HZ, 0) != HWA_GETVR(core, HWA_AHBHZ, 0))
      srchz *= 2 ;
  }
  else
    HWA_ERROR("Timer source clock not supported.");

  /*	Prescaler
   */
  if ( clkhz )
    psc = srchz / clkhz ;

  /*	Global divisor: div = psc * arr
   */
  if ( hz ) {
    div = srchz / hz ;
    if ( div * hz != srchz )
      HWA_ERROR("No valid divisor found.");
  } else { /* period */
    if ( psc == 0 )
      div = period / (syshz / srchz);
    else {
      div = psc * period ;
      arr = period ;
      goto done ;
    }
  }

  /*	Reload value (arr) and prescaler (psc)
   */
  if ( clkhz ) {
    psc = srchz/clkhz ;
    arr = div / psc ;
  }
  else {
    arr = _hwa_find_lowest_arr(div);
    if ( arr == 0 )
      HWA_ERROR("No valid value found for prescaler.");
    psc = div / arr ;
    //    clkhz = srchz / psc ;
  }

 done:
  /*	Checks
   */
  if ( psc == 0 )
    HWA_ERROR("Timer: PSC == 0.");
  if ( psc > 0xFFFF )
    HWA_ERROR("Timer: PSC overflow.");
  if ( clkhz && psc * clkhz != srchz )
    HWA_ERROR("Timer: can not find PSC value for clkhz.");
  if ( hz && hz*arr*psc != srchz )
    HWA_ERROR("Timer: can not find ARR/PSC combination for hz.");

  /* if ( period && psc*arr*(syshz/srchz) != period ) */
  /*   HWA_ERROR("Timer: can not find ARR/PSC combination for period."); */

  HWA_SETVR(HWA_TIMER, p, HWA_PSC, psc-1);
  HWA_SETVR(HWA_TIMER, p, HWA_ARR, arr-1);

  HWA_COMMIT(core, HWA_TIMER, p, HWA_CR1);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CR2);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_SMCR);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_DIER);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_ARR);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PSC);

  HWA_COMMIT(core, HWA_TIMER, p, HWA_MODE);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLK);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_CLKHZ);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_HZ);
  HWA_COMMIT(core, HWA_TIMER, p, HWA_PERIOD);

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

#define hw_timer_test_flag(pname, flag)				\
  (HW_TSTHB(HWA_TIMER, pname, HWA_G2(HWA_TIMER_FLAG, flag)) != 0)

#define hw_timer_clear_flag(pname, flag)			\
  HW_SETHB(HWA_TIMER, pname, HWA_G2(HWA_TIMER_FLAG, flag), 0)

#define hw_timer_clear_irq(pname, irq)					\
  do {									\
    if ( HWA_TIMER_IRQ_##irq == HWA_TIMER_IRQ_ALL )			\
      HW_HR(HWA_TIMER, pname, HWA_SR) = 0 ;				\
    else								\
      HW_HR(HWA_TIMER, pname, HWA_SR) = ~(0b1<<(HWA_TIMER_IRQ_##irq & 0x1F)) ; \
  } while(0)

#define rem_hw_timer_turn_irq(pname, irq, state)				\
  HW_SETHB(HWA_TIMER, pname, HWA_TIMER_IRQE_##irq, HWA_STATE_##state)

#define hw_timer_turn(pname, pstat)					\
  HW_SETHB(HWA_TIMER, pname, HWA_TIMER_CEN, HWA_STATE_##pstat)

#define hw_timer_reset(pname)						\
  do {									\
    uint dier = HW_HR(HWA_TIMER, pname, HWA_DIER);			\
    HW_SETHR(HWA_TIMER, pname, HWA_DIER, dier & ~HWA_BMSK(HWA_TIMER_UIE)); \
    HW_SETHR(HWA_TIMER, pname, HWA_EGR,  HWA_BMSK(HWA_TIMER_UG));	\
    HW_SETHR(HWA_TIMER, pname, HWA_SR,   0);				\
    HW_SETHR(HWA_TIMER, pname, HWA_DIER, dier);				\
  } while(0);

#define hw_timer_restart(pname)			\
  do {						\
    hw_timer_reset(pname);			\
    hw_timer_turn(pname, ON);			\
  } while(0);

#define hw_timer_start(pname)	hw_timer_turn(pname, ON)
#define hw_timer_stop(pname)	hw_timer_turn(pname, OFF)

#define hw_timer_set_period(pname, value)	\
  HW_SETHR(HWA_TIMER, pname, HWA_ARR, (value)-1)


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_timer_set_mode(pname, mode)			\
  hwa_prph_turn_clk(pname, ON);					\
  HWA_SETVB(HWA_TIMER, pname, HWA_MODE, -1, 0, HWA_TIMER_MODE_##mode);

/* Compatible ATmega
*/
#define hwa_timer_set_hz(pname, hz)				\
  HWA_SETVR(HWA_TIMER, pname, HWA_PERIOD, 0);			\
  HWA_SETVR(HWA_TIMER, pname, HWA_HZ, hz);

#define hwa_timer_set_period(pname, period)			\
  HWA_SETVR(HWA_TIMER, pname, HWA_HZ, 0);			\
  HWA_SETVR(HWA_TIMER, pname, HWA_PERIOD, period);

#define hwa_timer_turn_irq(p, irq, state)	\
  HWA_SETVB(HWA_TIMER, p, HWA_TIMER_IRQE_##irq, HWA_STATE_##state)

#define hwa_timer_set_clkhz(pname, hz)			\
  HWA_SETVR(HWA_TIMER, pname, HWA_CLKHZ, hz);

#define hwa_timer_turn(pname, pstat)					\
  HWA_SETVB(HWA_TIMER, pname, HWA_TIMER_CEN, HWA_STATE_##pstat)

#endif
