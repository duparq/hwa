
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

/** \file
 *  \brief	HWA 16-bits version 'a' Atmel AVR timer-counters (layer 2)
 *
 *	Used in: ATtinyX4 Timer 1
 */


/*	Initialize a c16a instance
 */
#define hwa_begin_c16a(cn)			\
  HWA_INIT(hw_##cn, ccra);			\
  HWA_INIT(hw_##cn, ccrb);			\
  HWA_INIT(hw_##cn, ccrc);			\
  HWA_INIT(hw_##cn, count);			\
  HWA_INIT(hw_##cn, icr);			\
  HWA_INIT(hw_##cn, ocra);			\
  HWA_INIT(hw_##cn, ocrb);			\
  HWA_INIT(hw_##cn, imsk);			\
  HWA_INIT(hw_##cn, ifr);			\
  hwa->cn.config = 0;				\
  hwa->cn.countmode = 0;			\
  hwa->cn.top = 0;				\
  hwa->cn.clock = 0;				\
  hwa->cn.overflow_irq = 0;			\
  hwa->cn.update_compares = 0


/*	Configure counter unit
 */
#define hwa_config_c16a_isfn

#define hwa_config_c16a(cn,cc,ca, ...)					\
  do {									\
    hwa->cn.config = 1;							\
    HW_G2(hwa_config_c16a_xclock,HW_IS(clock,__VA_ARGS__))(cn,__VA_ARGS__) \
      } while(0)

#define hwa_config_c16a_xclock_0(cn,...)				\
  HW_PPERROR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_xclock_1(cn,_clock_,...)			\
  HW_G2(hwa_config_c16a_vclock,HW_IS(ok,hw_c16a_clock_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vclock_0(cn,...)				\
  HW_PPERROR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	      "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "	\
	      "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_vclock_1(cn,zclock,...)				\
  hwa->cn.clock = HW_A1(hw_c16a_clock_##zclock);			\
  HW_G2(hwa_config_c16a_xmode,HW_IS(countmode,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xmode_0(cn,...)					\
  HW_PPERROR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_xmode_1(cn,_countmode_,...)			\
  HW_G2(hwa_config_c16a_vmode,HW_IS(ok,hw_c16a_countmode_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vmode_0(cn,...)					\
  HW_PPERROR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define hwa_config_c16a_vmode_1(cn,vmode,...)				\
  hwa->cn.countmode = HW_A1(hw_c16a_countmode_##vmode);		\
  HW_G2(hwa_config_c16a_xbottom,HW_IS(bottom,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xbottom_1(cn,_bottom_,...)			\
  HW_G2(hwa_config_c16a_vbottom,HW_IS(0,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vbottom_0(cn,bottom,...)	\
  HW_PPERROR("bottom must be `0`, not `" #bottom "`.")

#define hwa_config_c16a_vbottom_1(cn,bottom,...)	\
  hwa_config_c16a_xbottom_0(cn,__VA_ARGS__)

#define hwa_config_c16a_xbottom_0(cn,...)		\
  HW_G2(hwa_config_c16a_xtop,HW_IS(top,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xtop_0(cn,...)					\
  HW_PPERROR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define hwa_config_c16a_xtop_1(cn,_top_,...)				\
  HW_G2(hwa_config_c16a_vtop,HW_IS(ok,hw_c16a_top_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vtop_0(cn,...)					\
  HW_PPERROR("`top` can be `fixed_0xFF`, `fixed_0x1FF`, `fixed_0x3FF`, " \
	     "`fixed_0xFFFF`, `register_capture`, or `register_compare_a`," \
	     " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_vtop_1(cn,ztop,...)				\
  hwa->cn.top = HW_A1(hw_c16a_top_##ztop);				\
  HW_G2(hwa_config_c16a_xuc,HW_IS(update_compares,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xuc_1(cn,uc,...)	\
  HW_G2(hwa_config_c16a_vuc, HW_IS(ok,hw_counter_update_compares_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_vuc_0(cn,vuc,...)			\
  HW_PPERROR("update_compares must be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define hwa_config_c16a_vuc_1(cn,vuc,...)				\
  hwa->cn.update_compares = HW_A1(hw_counter_update_compares_##vuc);	\
  hwa_config_c16a_xuc_0(cn,__VA_ARGS__);

#define hwa_config_c16a_xuc_0(cn,...)			\
  HW_G2(hwa_config_c16a_xoverflow,HW_IS(overflow_irq,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_xoverflow_1(cn,overflow_irq,...)	\
    HW_G2(hwa_config_c16a_voverflow,				\
	  HW_IS(ok,hw_counter_overflow_irq_##__VA_ARGS__))	\
    (cn,__VA_ARGS__)

#define hwa_config_c16a_voverflow_0(cn,overflow,...)			\
  HW_PPERROR("overflow_irq must be `at_bottom`, `at_top, or `at_max`, but `not `" #overflow "`.")

#define hwa_config_c16a_voverflow_1(cn,voverflow,...)			\
  hwa->cn.overflow_irq = HW_A1(hw_counter_overflow_irq_##voverflow);	\
  hwa_config_c16a_xoverflow_0(cn,__VA_ARGS__)

/* #define hwa_config_c16a_xoverflow_0(cn,...)			\ */
/*   HW_G2(hwa_config_c16a,HW_IS(,__VA_ARGS__))(cn,__VA_ARGS__) */

#define hwa_config_c16a_xoverflow_0(cn,...)			\
  HW_G2(hwa_config_c16a,HW_IS(,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c16a_0(cn,...)					\
  HW_PPERROR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c16a_1(...)


#define hw_is_overflow_irq_overflow_irq		, 1
#define hw_is_update_compares_update_compares	, 1

#define hw_counter_overflow_irq_at_bottom	ok, 1
#define hw_counter_overflow_irq_at_top		ok, 2
#define hw_counter_overflow_irq_at_max		ok, 3

#define hw_counter_update_compares_immediately	ok, 1
#define hw_counter_update_compares_at_bottom	ok, 2
#define hw_counter_update_compares_at_top	ok, 3


/*	Solve the configuration of the counter unit
 */
HW_INLINE void hwa_solve_c16a ( hwa_c16a_t *p )
{
  if ( p->config != 1 )
    return ;

  /* Mode WGM   Operation                     COUNTMODE    TOP     OCR/TOP      OVF  OCF  ICF
   *                                                               UPDATE
   *
   *   0  0000  Normal                        LOOP_UP      0xFFFF  Immediately  BOT          
   *  12  1100  CTC (Clear Timer on Match)    LOOP_UP      icr     Immediately  BOT       TOP
   *   4  0100  CTC (Clear Timer on Match)    LOOP_UP      ocra    Immediately  BOT  TOP     
   *								  	      	        
   *   5  0101  Fast PWM, 8-bit               LOOP_UP      0xFF    TOP	        TOP          
   *   6  0110  Fast PWM, 9-bit               LOOP_UP      0x1FF   TOP	        TOP          
   *   7  0111  Fast PWM, 10-bit              LOOP_UP      0x3FF   TOP	        TOP          
   *  14  1110  Fast PWM                      LOOP_UP      icr     TOP	        TOP       TOP
   *  15  1111  Fast PWM                      LOOP_UP      ocra    TOP	        TOP  TOP     
   *								  	      	        
   *   1  0001  PWM, Phase Correct, 8-bit     LOOP_UPDOWN  0xFF    TOP	        BOT          
   *   2  0010  PWM, Phase Correct, 9-bit     LOOP_UPDOWN  0x1FF   TOP	        BOT          
   *   3  0011  PWM, Phase Correct, 10-bit    LOOP_UPDOWN  0x3FF   TOP	        BOT          
   *  10  1010  PWM, Phase Correct            LOOP_UPDOWN  icr     TOP	        BOT       TOP
   *  11  1011  PWM, Phase Correct            LOOP_UPDOWN  ocra    TOP	        BOT  TOP     
   *								  	      	        
   *   8  1000  PWM, Phase & Freq. Correct    LOOP_UPDOWN  icr     BOT	        BOT       TOP
   *   9  1001  PWM, Phase & Freq. Correct    LOOP_UPDOWN  ocra    BOT	        BOT  TOP     
   *
   *  13  1101  *Reserved*
   */

  if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
    if ( p->update_compares == HW_A1(hw_counter_update_compares_at_bottom) )
      HW_RTERROR("c16a configuration: `update_compares` can not be set to "
		 "`at_bottom` when counter loops up.");
    if ( (p->top == HW_A1(hw_c16a_top_fixed_0xFF)
	  || p->top == HW_A1(hw_c16a_top_fixed_0x1FF)
	  || p->top == HW_A1(hw_c16a_top_fixed_0x3FF))
	 && p->update_compares == HW_A1(hw_counter_update_compares_immediately) )
      HW_RTERROR("c16a configuration: `update_compares` can not be set to "
		 "`immediately` when counter loops up with a fixed top.");
  }
  else if ( p->update_compares == HW_A1(hw_counter_update_compares_immediately) )
    HW_RTERROR("c16a configuration: `update_compares` can not be set to "
	       "`immediately` when counter loops up-down.");

  uint8_t mode = 0xFF ;

  if ( p->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
    if ( p->update_compares == 0 ||
	 p->update_compares == HW_A1(hw_counter_update_compares_immediately) ) {
      if (p->top == HW_A1(hw_c16a_top_fixed_0xFFFF))
	mode = 0 ;
      else if (p->top == HW_A1(hw_c16a_top_register_capture))
	mode = 12 ;
      else
	mode = 4 ;
      if ( p->overflow_irq != 0
	   && p->overflow_irq != HW_A1(hw_counter_overflow_irq_at_bottom) )
	HW_RTERROR("c16a configuration: `overflow` can only be set to `at_bottom`.");
    }
    else {
      if (p->top == HW_A1(hw_c16a_top_fixed_0xFF) )
	mode = 5 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	mode = 6 ;
      else if (p->top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	mode = 7 ;
      else if (p->top == HW_A1(hw_c16a_top_register_capture) )
	mode = 14 ;
      else
	mode = 15 ;
      if ( p->overflow_irq != 0
	   && p->overflow_irq != HW_A1(hw_counter_overflow_irq_at_top) )
	HW_RTERROR("c16a configuration: `overflow` can only be set to `at_top`.");
    }
  }
  else {
    if ( p->overflow_irq != 0
	 && p->overflow_irq != HW_A1(hw_counter_overflow_irq_at_bottom) )
      HW_RTERROR("c16a configuration: `overflow` can only be set to `at_bottom`.");

    if ( p->countmode == HW_A1(hw_c16a_countmode_loop_updown) ) {
      if ( p->update_compares == 0 ||
	   p->update_compares == HW_A1(hw_counter_update_compares_at_top) ) {
	if (p->top == HW_A1(hw_c16a_top_fixed_0xFF) )
	  mode = 1 ;
	else if (p->top == HW_A1(hw_c16a_top_fixed_0x1FF) )
	  mode = 2 ;
	else if (p->top == HW_A1(hw_c16a_top_fixed_0x3FF) )
	  mode = 3 ;
	else if (p->top == HW_A1(hw_c16a_top_register_capture) )
	  mode = 10 ;
	else
	  mode = 11 ;
      }
      else if ( p->update_compares == HW_A1(hw_counter_update_compares_at_bottom) ) {
	if (p->top == HW_A1(hw_c16a_top_register_capture) )
	  mode = 8 ;
	else
	  mode = 9 ;
      }
    }
  }

  if (mode != 0xFF)
    _hwa_write_cp(p, hw_c16a_wgm, mode);
  else
    HW_RTERROR("WGM value could not be solved for c16a class counter.");

  /*	CS
   */
  _hwa_write_cp(p, hw_c16a_cs, p->clock);
}


/*	Solve the configuration of output-compare unit of class c16oc1
 */
HW_INLINE void hwa_solve_c16aoc1 ( hwa_c16a_t *counter, hwa_ocu_t *p )
{
  if ( p->config != 1 )
    return ;

  if ( counter->config == 0 )
    HW_RTERROR("configuration of hw_counter1 must be set.");

  if ( counter->top == HW_A1(hw_c16a_top_register_compare_a) )
    HW_RTERROR("ocra is used as top value for hw_counter1.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_ocu_mode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
    /*
     * Non PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match) )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_up/*_pwm*/) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match)
	 && counter->countmode > 8 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_updown/*_pwm*/) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match)
	 && counter->countmode > 8 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HW_RTERROR("incompatible counting mode / output-compare mode.");

  /*  Write the hardware configuration bits
   */
  _hwa_write_cp(counter, hw_c16a_coma, mode );
}


/*	Solve the configuration of output-compare unit of class c16oc2
 */
HW_INLINE void hwa_solve_c16aoc2 ( hwa_c16a_t *counter, hwa_ocu_t *p )
{
  if ( p->config != 1 )
    return ;

  if ( counter->config == 0 )
    HW_RTERROR("configuration of hw_counter0 must be set.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_ocu_mode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_up) ) {
    /*
     * Non PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match) )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_up/* _pwm */) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c16a_countmode_loop_updown/* _pwm */) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HW_RTERROR("incompatible counting mode / output-compare mode.");

  _hwa_write_cp(counter, hw_c16a_comb, mode );
}


HW_INLINE void _hwa_reset_c16a ( hwa_c16a_t *timer )
{
  _hwa_reset_r8(  &timer->ccra );
  _hwa_reset_r8(  &timer->ccrb );
  _hwa_reset_r8(  &timer->ccrc );
  _hwa_reset_r16( &timer->count );
  _hwa_reset_r16( &timer->icr );
  _hwa_reset_r16( &timer->ocra );
  _hwa_reset_r16( &timer->ocrb );
  _hwa_reset_r8(  &timer->imsk );
  _hwa_reset_r8(  &timer->ifr );
}


HW_INLINE void _hwa_commit_c16a ( hwa_t *hwa, hwa_c16a_t *timer )
{
  _hwa_commit_r8(  hwa->commit, &timer->ccra,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ccrb,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ccrc,  -1 );
  _hwa_commit_r16( hwa->commit, &timer->count, -1 );
  _hwa_commit_r16( hwa->commit, &timer->icr,   -1 );
  _hwa_commit_r16( hwa->commit, &timer->ocra,  -1 );
  _hwa_commit_r16( hwa->commit, &timer->ocrb,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->imsk,  -1 );
  _hwa_commit_r8(  hwa->commit, &timer->ifr,   -1 );
}
