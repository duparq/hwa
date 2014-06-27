
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hwa_begin_c8a(pn)			\
  HWA_INIT(hw_##pn, ccra);			\
  HWA_INIT(hw_##pn, ccrb);			\
  HWA_INIT(hw_##pn, count);			\
  HWA_INIT(hw_##pn, ocra);			\
  HWA_INIT(hw_##pn, ocrb);			\
  HWA_INIT(hw_##pn, imsk);			\
  HWA_INIT(hw_##pn, ifr);			\
  hwa->pn.config = 0

#define hwa_begin_c8aoc(pn)			\
  hwa->pn.config = 0



#define hwa_config_c8a_isfn

#if 0
#define hwa_config_c8a(pn,pc,pa, ...)	\
  HW_G2(hwa_config_c8a_xmode,HW_IS(countmode,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_xmode_no(pn,...)	\
  HW_PPERROR("expected _mode_ instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xmode_ok(pn,_countmode_,...)	\
  HW_G2(hwa_config_c8a_mode,HW_IS(ok,hw_c8a_countmode_##__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_mode_no(pn,...)\
  HW_PPERROR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define hwa_config_c8a_mode_ok(pn,mode,...)	\
  HW_G2(hwa_config_c8a_xbottom,HW_IS(bottom,__VA_ARGS__))(pn,__VA_ARGS__,HW_A1(hw_c8a_countmode_##mode))

#define hwa_config_c8a_xbottom_no(pn,...)	\
  HW_PPERROR("expected `bottom` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xbottom_ok(pn,_bottom_,...)	\
  HW_G2(hwa_config_c8a_bottom,HW_IS(0,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_bottom_no(pn,bottom,...)	\
  HW_PPERROR("bottom must be `0`, not `" HW_QUOTE(bottom) "`.")

#define hwa_config_c8a_bottom_ok(pn,bottom,...)\
  HW_G2(hwa_config_c8a_xtop,HW_IS(top,__VA_ARGS__))(pn,__VA_ARGS__ /*,bottom*/)

#define hwa_config_c8a_xtop_no(pn,...)\
  HW_PPERROR("expected `top` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xtop_ok(pn,_top_,...)				\
  HW_G2(hwa_config_c8a_top255,HW_IS(255,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_top255_no(pn,...)\
  HW_G2(hwa_config_c8a_topreg,HW_IS(topreg,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_topreg_no(pn,...)\
  HW_PPERROR("top must be `255` or `topreg`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_top255_ok(pn,_255_,...)				\
  HW_G2(hwa_config_c8a_xclk,HW_IS(clk,__VA_ARGS__))(pn,__VA_ARGS__,HW_A1(hw_c8a_toptype_max))

#define hwa_config_c8a_topreg_ok(pn,_topreg_,...)			\
  HW_G2(hwa_config_c8a_xclk,HW_IS(clk,__VA_ARGS__))(pn,__VA_ARGS__,HW_A1(hw_c8a_toptype_reg))

#define hwa_config_c8a_xclk_no(pn,...)\
  HW_PPERROR("expected `clk` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xclk_ok(pn,_clk_,...)\
  HW_G2(hwa_config_c8a_clk,HW_IS(ok,hw_c8a_clk_##__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_clk_no(pn,...)\
  HW_PPERROR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid clk option. Valid clock options are: `none`, `syshz`, `syshz_div_8`, `syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, `pin_t0_falling`, `pin_t0_rising`.")

#define hwa_config_c8a_clk_ok(pn,clk,...)\
  HW_G2(hwa_config_c8a,HW_IS(,__VA_ARGS__))(pn,clk,__VA_ARGS__,)

#define hwa_config_c8a_no(pn,clk,...)	\
  HW_PPERROR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_ok(pn,clk,_,mode,toptype,...)			\
  _hwa_config_c8a(&hwa->pn,mode,toptype,HW_A1(hw_c8a_clk_##clk))


HW_INLINE void _hwa_config_c8a( hwa_c8a_t *p, uint8_t countmode,
				uint8_t toptype, uint8_t clk )
{
  p->config = 1 ;
  p->countmode = countmode ;
  p->toptype = toptype ;
  p->clk = clk ;
}

#else

#define hwa_config_c8a(pn,pc,pa, ...)					\
  do {									\
    hwa->pn.config = 1 ;							\
    HW_G2(hwa_config_c8a_xmode,HW_IS(countmode,__VA_ARGS__))(pn,__VA_ARGS__) ; \
  } while(0)

#define hwa_config_c8a_xmode_no(pn,...)	\
  HW_PPERROR("expected _mode_ instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xmode_ok(pn,_countmode_,...)	\
  HW_G2(hwa_config_c8a_mode,HW_IS(ok,hw_c8a_countmode_##__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_mode_no(pn,...)\
  HW_PPERROR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define hwa_config_c8a_mode_ok(pn,mode,...)				\
  hwa->pn.countmode = HW_A1(hw_c8a_countmode_##mode) ;			\
  HW_G2(hwa_config_c8a_xbottom,HW_IS(bottom,__VA_ARGS__))(pn,__VA_ARGS__)

/* #define hwa_config_c8a_xbottom_no(pn,...)	\ */
/*   HW_PPERROR("expected `bottom` instead of `" HW_QUOTE(__VA_ARGS__) "`.") */

#define hwa_config_c8a_xbottom_no(pn,...)			\
  HW_G2(hwa_config_c8a_xbottom_xtop,HW_IS(top,__VA_ARGS__))	\
  (pn,__VA_ARGS__,HW_A1(hw_c8a_countmode_##mode))

#define hwa_config_c8a_xbottom_xtop_no(pn,...)				\
  HW_PPERROR("expected `bottom` or `top` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xbottom_xtop_ok	hwa_config_c8a_xtop_ok

#define hwa_config_c8a_xbottom_ok(pn,_bottom_,...)	\
  HW_G2(hwa_config_c8a_bottom,HW_IS(0,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_bottom_no(pn,bottom,...)	\
  HW_PPERROR("bottom must be `0`, not `" HW_QUOTE(bottom) "`.")

#define hwa_config_c8a_bottom_ok(pn,bottom,...)\
  HW_G2(hwa_config_c8a_xtop,HW_IS(top,__VA_ARGS__))(pn,__VA_ARGS__ /*,bottom*/)

#define hwa_config_c8a_xtop_no(pn,...)\
  HW_PPERROR("expected `top` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xtop_ok(pn,_top_,...)				\
  HW_G2(hwa_config_c8a_top255,HW_IS(255,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_top255_no(pn,...)\
  HW_G2(hwa_config_c8a_topreg,HW_IS(topreg,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_topreg_no(pn,...)\
  HW_PPERROR("top must be `255` or `topreg`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_top255_ok(pn,_255_,...)				\
  hwa->pn.toptype = HW_A1(hw_c8a_toptype_max) ;				\
  HW_G2(hwa_config_c8a_xclk,HW_IS(clk,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_topreg_ok(pn,_topreg_,...)			\
  hwa->pn.toptype = HW_A1(hw_c8a_toptype_reg) ;				\
  HW_G2(hwa_config_c8a_xclk,HW_IS(clk,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_xclk_no(pn,...)\
  HW_PPERROR("expected `clk` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xclk_ok(pn,_clk_,...)\
  HW_G2(hwa_config_c8a_clk,HW_IS(ok,hw_c8a_clk_##__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_clk_no(pn,...)					\
  HW_PPERROR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid clk option. "	\
	      "Valid clock options are: `none`, `syshz`, `syshz_div_8`, " \
	      "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "	\
	      "`ext_falling`, `ext_rising`.")

#define hwa_config_c8a_clk_ok(pn,zclk,...)				\
    hwa->pn.clk = HW_A1(hw_c8a_clk_##zclk) ;				\
    HW_G2(hwa_config_c8a,HW_IS(,__VA_ARGS__))(pn,__VA_ARGS__)

#define hwa_config_c8a_no(pn,...)	\
  HW_PPERROR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_ok(...)

#endif


/*	Configure Output-Compare unit
 */
#define hwa_config_c8aoc_isfn
#define hwa_config_c8aoc(pn,pc,counter,ocr,mode,_)			\
  HW_G2(hwa_config_c8aoc, HW_IS(ok,hw_c8a_ocmode_##mode))(pn,mode)

#define hwa_config_c8aoc_no(pn,mode)					\
  HW_PPERROR( "`"HW_QUOTE(mode) "` is not a valid mode for hw_" HW_QUOTE(pn) "." )

#define hwa_config_c8aoc_ok(pn,ocmode)					\
  do { hwa->pn.config = 1 ; hwa->pn.mode = HW_A1(hw_c8a_ocmode_##ocmode) ; } while(0)

#define hwa_write_c8aoc_isfn
#define hwa_write_c8aoc(pn,pc,counter,ocr, value)		\
  do {							\
    hwa->counter.config = 1 ;	\
    hwa_write_8(&hwa->counter.ocr, 8, 0, value) ;	\
  } while(0)

/*	Determine register values from user constraints
 */
HW_INLINE void hwa_solve_counter0 ( hwa_t *hwa )
{
  hwa_c8a_t *p = &hwa->counter0 ;

  if ( p->config != 1 )
    return ;

  /*	WGM
   *
   * Mode WGM   Operation                     COUNTMODE    TOP    OVF    OCR UPDATED
   *
   *  0   000   Normal                        LOOP_UP      0xFF   0xFF   Immediatly
   *  2   010   CTC (Clear Timer on Match)    LOOP_UP      OCRA   0xFF   Immediatly
   *           
   *  3   011   Fast PWM                      LOOP_UP      0xFF   0xFF   at BOTTOM
   *  7   111   Fast PWM                      LOOP_UP      OCRA   0xFF   at BOTTOM
   *           
   *  1   001   PWM, Phase Correct            LOOP_UPDOWN  0xFF   0x00   at TOP
   *  5   101   PWM, Phase Correct            LOOP_UPDOWN  OCRA   0x00   at TOP
   *           
   *  4   100   *Reserved*
   *  6   110   *Reserved*
   */

  if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) )
    if (p->toptype == HW_A1(hw_c8a_toptype_max))
      hwa_write_p(p, hw_c8a_wgm, 0);
    else
      hwa_write_p(p, hw_c8a_wgm, 2);
  else if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) )
    if (p->toptype == HW_A1(hw_c8a_toptype_max) )
      hwa_write_p(p, hw_c8a_wgm, 3);
    else
      hwa_write_p(p, hw_c8a_wgm, 7);
  else if ( p->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) )
    if (p->toptype == HW_A1(hw_c8a_toptype_max) )
      hwa_write_p(p, hw_c8a_wgm, 1);
    else
      hwa_write_p(p, hw_c8a_wgm, 5);
  else
    HW_RTERROR("WGM value could not be solved for c8a class counter.");

  /*	CS
   */
  hwa_write_p(p, hw_c8a_cs, p->clk);
}


/*	Solve the configuration of pin OC0A
 */
HW_INLINE void hwa_solve_oc0a ( hwa_t *hwa )
{
  hwa_c8aoc_t	*p = &hwa->oc0a ;
  hwa_c8a_t	*counter = &hwa->counter0 ;

  if ( p->config != 1 )
    return ;

  if ( counter->config == 0 )
    HW_RTERROR("configuration of hw_counter0 must be set.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_c8a_ocmode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
    /*
     * Non PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_toggled_on_match) )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_toggled_on_match)
	 && counter->countmode == 7 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_toggled_on_match)
	 && counter->countmode == 5 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HW_RTERROR("incompatible counting mode / output-compare mode.");

  /*  The pin must be configured as output
   */
  hwa_config( hw_pin_oc0a, output );

  /*  Write the hardware configuration bits
   */
  hwa_write_p(counter, hw_c8a_coma, mode );
}


/*	Solve the configuration of pin OC0B
 */
HW_INLINE void hwa_solve_oc0b ( hwa_t *hwa )
{
  hwa_c8aoc_t	*p = &hwa->oc0b ;

  if ( p->config != 1 )
    return ;

  hwa_c8a_t	*counter = &hwa->counter0 ;

  if ( counter->config == 0 )
    HW_RTERROR("configuration of hw_counter0 must be set.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_c8a_ocmode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
    /*
     * Non PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_toggled_on_match) )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_c8a_ocmode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_c8a_ocmode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HW_RTERROR("incompatible counting mode / output-compare mode.");

  hwa_config( hw_pin_oc0b, output );

  hwa_write_p(counter, hw_c8a_comb, mode );
}


HW_INLINE void hwa_commit_c8a ( hwa_t *hwa, hwa_c8a_t *timer )
{
  hwa_commit_8( hwa->commit, &timer->ccra, -1 );
  hwa_commit_8( hwa->commit, &timer->ccrb, -1 );
  hwa_commit_8( hwa->commit, &timer->count, -1 );
  hwa_commit_8( hwa->commit, &timer->ocra, -1 );
  hwa_commit_8( hwa->commit, &timer->ocrb, -1 );
  hwa_commit_8( hwa->commit, &timer->imsk, -1 );
  hwa_commit_8( hwa->commit, &timer->ifr, -1 );
}
