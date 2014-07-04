
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#define hwa_begin_c8a(cn)			\
  HWA_INIT(hw_##cn, ccra);			\
  HWA_INIT(hw_##cn, ccrb);			\
  HWA_INIT(hw_##cn, count);			\
  HWA_INIT(hw_##cn, ocra);			\
  HWA_INIT(hw_##cn, ocrb);			\
  HWA_INIT(hw_##cn, imsk);			\
  HWA_INIT(hw_##cn, ifr);			\
  hwa->cn.config = 0 ;


#define hwa_is_clock_clock		,1

#define hw_fn_hwa_config_c8a		, _hwa_config_c8a

#define _hwa_config_c8a(c,n,i,a, ...)					\
  do {									\
    hwa->n.config = 1 ;							\
    hwa->n.countmode = 0 ;						\
    hwa->n.top = 0 ;							\
    hwa->n.clock = 0 ;							\
    HW_G2(hwa_config_c8a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__) \
      } while(0)

#define hwa_config_c8a_xclock_0(cn,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xclock_1(cn,_clock_,...)				\
  HW_G2(hwa_config_c8a_clock,HW_IS(,hw_c8a_clock_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c8a_clock_0(cn,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_8`, "		\
	      "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "	\
	      "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_clock_1(cn,zclock,...)				\
  hwa->cn.clock = HW_A1(hw_c8a_clock_##zclock) ;			\
  HW_G2(hwa_config_c8a_xcountmode,HW_IS(countmode,__VA_ARGS__))(cn,__VA_ARGS__) ; \

#define hwa_config_c8a_xcountmode_0(cn,...)				\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xcountmode_1(cn,_countmode_,...)			\
  HW_G2(hwa_config_c8a_countmode,HW_IS(,hw_c8a_countmode_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c8a_countmode_0(cn,...)				\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define hwa_config_c8a_countmode_1(cn,mode,...)				\
  hwa->cn.countmode = HW_A1(hw_c8a_countmode_##mode) ;			\
  HW_G2(hwa_config_c8a_xbottom,HW_IS(bottom,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c8a_xbottom_0(cn,...)			\
  HW_G2(hwa_config_c8a_xbottom_xtop,HW_IS(top,__VA_ARGS__))	\
  (cn,__VA_ARGS__,HW_A1(hw_c8a_countmode_##mode))

#define hwa_config_c8a_xbottom_xtop_0(cn,...)				\
  HW_ERR("expected `bottom` or `top` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xbottom_xtop_1	hwa_config_c8a_xtop_1

#define hwa_config_c8a_xbottom_1(cn,_bottom_,...)			\
  HW_G2(hwa_config_c8a_bottom,HW_IS(0,__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c8a_bottom_0(cn,bottom,...)			\
  HW_ERR("bottom must be `0`, not `" HW_QUOTE(bottom) "`.")

#define hwa_config_c8a_bottom_1(cn,bottom,...)				\
  HW_G2(hwa_config_c8a_xtop,HW_IS(top,__VA_ARGS__))(cn,__VA_ARGS__ /*,bottom*/)

#define hwa_config_c8a_xtop_0(cn,...)					\
  HW_ERR("expected `top` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_xtop_1(cn,_top_,...)				\
  HW_G2(hwa_config_c8a_vtop,HW_IS(,hw_c8a_top_##__VA_ARGS__))(cn,__VA_ARGS__)

#define hwa_config_c8a_vtop_0(cn,...)					\
    HW_ERR("`top` can be `fixed_0xFF` or `register_compare_a`,"	\
	       "but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_vtop_1(cn,ztop,...)				\
    hwa->cn.top = HW_A1(hw_c8a_top_##ztop);				\
    HW_G2(hwa_config_c8a,HW_IS(,__VA_ARGS__))(cn,__VA_ARGS__)

/* #define hwa_config_c8a_xocra_1(cn,_ocra_,...)			\ */
/*   hwa->cn.top = HW_A1(hw_c8a_top_ocra) ;			\ */
/*   HW_G2(hwa_config_c8a,HW_IS(,__VA_ARGS__))(cn,__VA_ARGS__) */

#define hwa_config_c8a_0(cn,...)					\
  HW_ERR( "too many arguments: `" HW_QUOTE(__VA_ARGS__) "`.")

#define hwa_config_c8a_1(...)


/*	Solve the configuration of the counter unit
 */
HW_INLINE void hwa_solve_c8a ( hwa_c8a_t *p )
{

  if ( p->config != 1 )
    return ;

  /*	WGM
   *
   * Mode WGM   Operation                     COUNTMODE    TOP    OVF    OCR UPDATED
   *
   *  0   000   Normal                        LOOP_UP      0xFF   0xFF   Immediately
   *  2   010   CTC (Clear Timer on Match)    LOOP_UP      OCRA   0xFF   Immediately
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

  uint8_t wgm = 0xFF ;

  if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) )
    if (p->top == HW_A1(hw_c8a_top_fixed_0xFF))
      wgm = 0 ;
    else
      wgm = 2 ;
  else if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) )
    if (p->top == HW_A1(hw_c8a_top_fixed_0xFF) )
      wgm = 3 ;
    else
      wgm = 7 ;
  else if ( p->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) )
    if (p->top == HW_A1(hw_c8a_top_fixed_0xFF) )
      wgm = 1 ;
    else
      wgm = 5 ;
  else
    HWA_ERR("WGM value could not be solved for c8a class counter.");

  if (wgm != 0xFF)
    _hwa_write_p(p, _hw_cbits(c8a,wgm), wgm);
  else
    HWA_ERR("WGM value could not be solved for c16a class counter.");


  /*	CS
   */
  _hwa_write_p(p, _hw_cbits(c8a, cs), p->clock);
}


/*	Solve the configuration of the 1st output-compare unit
 */
HW_INLINE void hwa_solve_c8aoc1 ( hwa_c8a_t *counter, hwa_ocu_t *p )
{
  if ( p->config != 1 )
    return ;

  if ( counter->config == 0 )
    HWA_ERR("configuration of hw_counter0 must be set.");

  if ( counter->top == HW_A1(hw_c8a_top_register_compare_a) )
    HWA_ERR("ocra is already used as top value for hw_counter0.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_ocu_mode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
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
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match)
	 && counter->countmode == 7 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_toggled_on_match)
	 && counter->countmode == 5 )
      mode = 1 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HWA_ERR("incompatible counting mode / output-compare mode.");

  /*  Set the hardware configuration bits
   */
  _hwa_write_p(counter, _hw_cbits(c8a, coma), mode );
}


/*	Solve the configuration of the 2nd output-compare unit (a little less
 *	possibilities than the 1st pin).
 */
HW_INLINE void hwa_solve_c8aoc2 ( hwa_c8a_t *counter, hwa_ocu_t *p )
{
  if ( p->config != 1 )
    return ;

  if ( counter->config == 0 )
    HWA_ERR("configuration of hw_counter0 must be set.");

  uint8_t	mode = 0xFF ;

  if ( p->mode == HW_A1(hw_ocu_mode_disconnected) )
    mode = 0 ;
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
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
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_up_pwm) ) {
    /*
     * Fast PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_set_at_bottom_cleared_on_match) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_cleared_at_bottom_set_on_match) )
      mode = 3 ;
  }
  else if ( counter->countmode == HW_A1(hw_c8a_countmode_loop_updown_pwm) ) {
    /*
     * Phase-correct PWM modes
     */
    if ( p->mode == HW_A1(hw_ocu_mode_cleared_on_match_up_set_on_match_down) )
      mode = 2 ;
    else if ( p->mode == HW_A1(hw_ocu_mode_set_on_match_up_cleared_on_match_down) )
      mode = 3 ;
  }

  if ( mode == 0xFF )
    HWA_ERR("incompatible counting mode / output-compare mode.");

  _hwa_write_p(counter, _hw_cbits(c8a, comb), mode );
}


HW_INLINE void _hwa_reset_c8a ( hwa_c8a_t *timer )
{
  _hwa_reset_r8( &timer->ccra );
  _hwa_reset_r8( &timer->ccrb );
  _hwa_reset_r8( &timer->count );
  _hwa_reset_r8( &timer->ocra );
  _hwa_reset_r8( &timer->ocrb );
  _hwa_reset_r8( &timer->imsk );
  _hwa_reset_r8( &timer->ifr );
}


HW_INLINE void _hwa_commit_c8a ( hwa_t *hwa, hwa_c8a_t *timer )
{
  _hwa_commit_r8( hwa->commit, &timer->ccra, -1 );
  _hwa_commit_r8( hwa->commit, &timer->ccrb, -1 );
  _hwa_commit_r8( hwa->commit, &timer->count, -1 );
  _hwa_commit_r8( hwa->commit, &timer->ocra, -1 );
  _hwa_commit_r8( hwa->commit, &timer->ocrb, -1 );
  _hwa_commit_r8( hwa->commit, &timer->imsk, -1 );
  _hwa_commit_r8( hwa->commit, &timer->ifr, -1 );
}
