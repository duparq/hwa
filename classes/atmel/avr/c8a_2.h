
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */

HW_INLINE void __hwa_begin__c8a ( hwa_c8a_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _c8a, ccra  );
  _hwa_begin_reg_p( p, a, _c8a, ccrb  );
  _hwa_begin_reg_p( p, a, _c8a, count );
  _hwa_begin_reg_p( p, a, _c8a, compare0 );
  _hwa_begin_reg_p( p, a, _c8a, compare1 );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_begin_reg_p( p, a, _c8a, imsk  );
  _hwa_begin_reg_p( p, a, _c8a, ifr   );
#endif

  p->config.clock           = 0xFF ;
  p->config.countmode       = 0xFF ;
  p->config.top             = 0xFF ;
  p->config.overflow        = 0xFF ;
  p->config.compare0.update = 0xFF ;
  p->config.compare0.output = 0xFF ;
  p->config.compare1.update = 0xFF ;
  p->config.compare1.output = 0xFF ;
}


HW_INLINE void __hwa_init__c8a ( hwa_c8a_t *p )
{
  _hwa_set_r8( &p->ccra,     0x00 );
  _hwa_set_r8( &p->ccrb,     0x00 );
  _hwa_set_r8( &p->count,    0x00 );
  _hwa_set_r8( &p->compare0, 0x00 );
  _hwa_set_r8( &p->compare1, 0x00 );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_set_r8( &p->imsk,     0x00 );
  _hwa_set_r8( &p->ifr,      0x00 );
#endif
}


HW_INLINE void __hwa_commit__c8a ( hwa_t *hwa, hwa_c8a_t *p )
{
  _hwa_commit_reg_p( p, _c8a, ccra  );
  _hwa_commit_reg_p( p, _c8a, ccrb  );
  _hwa_commit_reg_p( p, _c8a, count );
  _hwa_commit_reg_p( p, _c8a, compare0 );
  _hwa_commit_reg_p( p, _c8a, compare1 );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_commit_reg_p( p, _c8a, imsk  );
  _hwa_commit_reg_p( p, _c8a, ifr   );
#endif
}


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_config Configuring the counter
 *
 * Note: if `overflow` is not stated, HWA will select an acceptable value
 * according to the configuration of the comparison units found in the HWA
 * context. If `overflow` is stated, HWA will check the validity of its value.
 *
 * @code
 * hwa_config( COUNTER,
 *
 *             //  How the counter is clocked
 *             //
 *             clock,       none                // No clock, the counter is stopped
 *                        | syshz               // CPU clock, frequency
 *                        | syshz_div_1         // CPU clock, frequency
 *                        | syshz_div_8         // CPU clock, frequency / 8
 *                        | syshz_div_64        // CPU clock, frequency / 64
 *                        | syshz_div_256       // CPU clock, frequency / 256
 *                        | syshz_div_1024      // CPU clock, frequency / 1024
 *                        | syshz_ext_rising    // External input, rising edge
 *                        | syshz_ext_falling,  // External input, falling edge
 *
 *             //  How does this counter count
 *             //
 *             countmode,   loop_up             // Count up and loop
 *                        | loop_updown,        // Count up and down alternately
 *
 *             //  Class _c8a counters count from 0
 *             //
 *            [bottom,      0, ]
 *
 *             //  The maximum value the counter reaches (the default is `max`)
 *             //
 *            [top,         fixed_0xFF          // Hardware fixed value 0x00FF
 *                        | max                 // Hardware fixed value 0x00FF
 *                        | compare0,]          // Value stored in the compare0 unit
 *
 *             //  When the overflow flag is set
 *             //
 *            [overflow,    at_bottom           // When the counter resets to bottom
 *                        | at_top              // When the counter reaches the top value
 *                        | at_max ]            // When the counter reaches its max value
 *           );
 * @endcode
 */
#define _hw_mthd_hwa_config__c8a		, _hwa_config_c8a

#define hw_c8a_countmode_loop_up		, 1
#define hw_c8a_countmode_loop_updown		, 2

#define hw_c8a_top_fixed_0xFF			, 1
#define hw_c8a_top_max				, 1
#define hw_c8a_top_compare0			, 2

#define hw_c8a_clock_none			, 0
#define hw_c8a_clock_syshz			, 1
#define hw_c8a_clock_syshz_div_1		, 1	/* Useful for concat */
#define hw_c8a_clock_syshz_div_8		, 2
#define hw_c8a_clock_syshz_div_64		, 3
#define hw_c8a_clock_syshz_div_256		, 4
#define hw_c8a_clock_syshz_div_1024		, 5
#define hw_c8a_clock_ext_rising			, 6
#define hw_c8a_clock_ext_falling		, 7

#define hw_c8a_overflow_at_bottom		, 0
#define hw_c8a_overflow_at_top			, 1
#define hw_c8a_overflow_at_max			, 2


#define _hwa_config_c8a(p,i,a, ...)						\
  do { HW_G2(_hwa_cfc8a_xclock,HW_IS(clock,__VA_ARGS__))(p,__VA_ARGS__) } while(0)

#define _hwa_cfc8a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_cfc8a_vclock,HW_IS(,hw_c8a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vclock_0(n,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_1`, `syshz_div_8`, " \
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_vclock_1(n,zclock,...)				\
  hwa->n.config.clock = HW_A1(hw_c8a_clock_##zclock);				\
  HW_G2(_hwa_cfc8a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_xmode_1(n,_countmode_,...)				\
  HW_G2(_hwa_cfc8a_vmode,HW_IS(,hw_c8a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vmode_0(n,v,...)					\
  HW_ERR("`mode` can be `loop_up`, or `loo_updown`, but not `" #v "`.")

#define _hwa_cfc8a_vmode_1(n,vmode,...)					\
  hwa->n.config.countmode = HW_A1(hw_c8a_countmode_##vmode);			\
  HW_G2(_hwa_cfc8a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_cfc8a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_cfc8a_vbottom_1(n,bottom,...)	\
  _hwa_cfc8a_xbottom_0(n,__VA_ARGS__)

#define _hwa_cfc8a_xbottom_0(n,...)				\
  HW_G2(_hwa_cfc8a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

/* #define _hwa_cfc8a_xtop_0(n,...)				\ */
/*   HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.") */

#define _hwa_cfc8a_xtop_1(n,_top_,...)					\
  HW_G2(_hwa_cfc8a_vtop,HW_IS(,hw_c8a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vtop_0(n,...)				\
  HW_ERR("`top` can be `fixed_0xFF`, `max`, or `compare0`,"	\
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_vtop_1(n,ztop,...)					\
  hwa->n.config.top = HW_A1(hw_c8a_top_##ztop);				\
  _hwa_cfc8a_xtop_0(n,__VA_ARGS__)

#define _hwa_cfc8a_xtop_0(n,...)					\
  HW_G2(_hwa_cfc8a_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xuc_1(n,uc,...)					\
  HW_G2(_hwa_cfc8a_vuc, HW_IS(,hw_ocu_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vuc_0(n,vuc,...)					\
  HW_ERR("`update` can be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_cfc8a_vuc_1(n,vuc,...)		\
    hwa->n.config.update = HW_A1(hw_ocu_update_##vuc);	\
    _hwa_cfc8a_xuc_0(n,__VA_ARGS__);

#define _hwa_cfc8a_xuc_0(n,...)						\
  HW_G2(_hwa_cfc8a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xoverflow_1(n,overflow,...)				\
  HW_G2(_hwa_cfc8a_voverflow, HW_IS(,hw_c8a_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_voverflow_0(n,overflow,...)			\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_cfc8a_voverflow_1(n,voverflow,...)				\
  if ( hwa->n.config.countmode == HW_A1(hw_c8a_countmode_loop_up)		\
       && HW_A1(hw_c8a_overflow_##voverflow) == HW_A1(hw_c8a_overflow_at_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `at_bottom` "	\
	    "when countmode is `loop_up`.");				\
  HW_TX(hwa->n.config.overflow = HW_A1(hw_c8a_overflow_##voverflow); ,__VA_ARGS__)

#define _hwa_cfc8a_xoverflow_0(n,...)		\
  HW_TX(,__VA_ARGS__)


/*  Solve the configuration of the counter and its compare and capture units
 *
 *  Alternatively, computed values to be written into hardware registers could
 *  be stored in a 'solved' structure. They would be written by the 'commit'
 *  function at device level which knows the register mapping of the counter
 *  that is used.
 */
/* HW_INLINE void __hwa_solve__c8a ( hwa_t* hwa __attribute__((unused)), */
/* 				  hwa_c8a_t *p ) */
HW_INLINE void _hwa_solve_c8a ( hwa_c8a_t *p )
{
  p->solved.cs   = 0xFF ;
  p->solved.wgm  = 0xFF ;
  p->solved.coma = 0xFF ;
  p->solved.comb = 0xFF ;

  if ( p->config.clock == 0xFF )
    return ;

  /*	Clock selection
   */
  p->solved.cs = p->config.clock ;

  /*  Default config for top
   */
  if ( p->config.top == 0xFF )
    p->config.top = HW_A1(hw_c8a_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(hw_c8a_top_compare0) ) {
    if ( p->config.countmode == HW_A1(hw_c8a_countmode_loop_up) )
      overflow = HW_A1(hw_c8a_overflow_at_top);
    else /* if ( p->config.countmode == HW_A1(hw_c8a_countmode_loop_up) ) */
      overflow = HW_A1(hw_c8a_overflow_at_bottom);
  }


  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( p->config.compare0.update != 0xFF && p->config.compare1.update != 0xFF
       && p->config.compare0.update != p->config.compare1.update )
    HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " \
	    "'immediately'.");
  compare_update = p->config.compare0.update ;


  /* Mode WGM  Operation  COUNTMODE    TOP   UPD  OVF  OCA                    OCB
   *                                            
   *  0   000  Normal     LOOP_UP      0xFF  IMM  MAX  DIS,ToM,CoM,SoM        DIS,ToM,CoM,SoM
   *  2   010  CTC        LOOP_UP      OCRA  IMM  MAX  DIS,ToM,CoM,SoM        DIS,ToM,CoM,SoM
   *
   *  3   011  Fast PWM   LOOP_UP      0xFF  BOT  MAX  DIS,SaBCoM,CaBSoM      DIS,SaBCoM,CaBSoM
   *  7   111  Fast PWM   LOOP_UP      OCRA  BOT  TOP  DIS,ToM,CoMSaB,SoMCaB  DIS,SaBCoM,CaBSoM
   *
   *  1   001  PWM, PhC   LOOP_UPDOWN  0xFF  TOP  BOT  DIS,CmuSmd,SmuCmd      DIS,CmuSmd,SmuCmd   
   *  5   101  PWM, PhC   LOOP_UPDOWN  OCRA  TOP  BOT  DIS,ToM,CmuSmd,SmuCmd  DIS,CmuSmd,SmuCmd
   *
   *  4   100  *Reserved*
   *  6   110  *Reserved*
   */

  /*	Determine WGM
   */
  uint8_t wgm = 0xFF ;
  if ( p->config.countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
    if ( p->config.top == HW_A1(hw_c8a_top_fixed_0xFF) ) {
      if ( compare_update == HW_A1(hw_ocu_update_at_bottom)
	   || p->config.compare0.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->config.compare0.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	   || p->config.compare1.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match))
	wgm = 3 ;
      else 
	wgm = 0 ;
    }
    else /* top == ocra */ {
      /*
       *  FIXME: a change of output_mode from one of the 4 modes below to
       *  'disconnected' causes a useless modification of wgm from 7 to 2. As
       *  wgm2 is not in the same register as wgm1:0, this generates useless
       *  code.
       */
      if ( compare_update == HW_A1(hw_ocu_update_at_bottom )
	   || overflow == HW_A1(hw_c8a_overflow_at_top)
	   || p->config.compare0.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->config.compare0.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	   || p->config.compare1.output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match))
	wgm = 7 ;
      else
	wgm = 2 ;
    }
  }
  else /* countmode == loop_updown */ {
    if ( p->config.top == HW_A1(hw_c8a_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    HWA_ERR("WGM value could not be solved for _c8a class counter.");
    return ;
  }

  p->solved.wgm = wgm ;


  /*	Solve the configuration of compare output A
   */
  if ( p->config.compare0.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->config.compare0.output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->config.compare0.output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->config.compare0.output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->config.compare0.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->config.compare0.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    p->solved.coma = mode ;
  }


  /*	Solve the configuration of compare output B
   */
  if ( p->config.compare1.output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->config.compare1.output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->config.compare1.output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->config.compare1.output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->config.compare1.output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    p->solved.comb = mode ;
  }


  /*	Check the validity of the configuration
   */
  if ( p->config.clock != 0xFF || p->config.compare0.output != 0xFF \
       || p->config.compare1.output != 0xFF ) {

    if ( p->config.clock == 0xFF ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( p->config.compare0.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match))
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==7 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==5 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Compare output B
     */
    if ( p->config.compare1.output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_on_match))
	  HWA_ERR("compare output B of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output B of class _c8a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare_update != HW_A1(hw_ocu_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class _c8a counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare_update != HW_A1(hw_ocu_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class _c8a counter must be "
		  "'at_bottom'.");
      }
      else
	if( compare_update != HW_A1(hw_ocu_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class _c8a counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
	if ( overflow != HW_A1(hw_c8a_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_top'.");
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(hw_c8a_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_bottom'.");
      }
      else if ( overflow != HW_A1(hw_c8a_overflow_at_max) )
	HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		"'at_max'.");
    }
  }
}


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_read Getting the value of the counter
 *
 * @code
 * hw_read( COUNTER );
 * @endcode
 */
#define _hw_mthd_hw_read__c8a		, _hw_read_c8a
#define _hw_read_c8a(p,i,a,...)		HW_TX(_hw_read_reg(p,count),__VA_ARGS__)


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_write Setting the value of the counter
 *
 * @code
 * hw/hwa_write( COUNTER, 42 );
 * @endcode
 * @code
 * hw/hwa_write_reg( COUNTER, count, 42 );
 * @endcode
 */
#define _hw_mthd_hw_write__c8a		, _hw_write_c8a
#define _hw_write_c8a(p,i,a,v)		_hw_write_reg(p,count,v)

#define _hw_mthd_hwa_write__c8a		, _hwa_write_c8a
#define _hwa_write_c8a(p,i,a,v)		_hwa_write_reg(p,count,v)


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_clear Clearing the counter (setting the value to 0)
 *
 * Note: this does not reset the prescaler.
 *
 * @code
 * hw/hwa_clear( COUNTER );
 * @endcode
 * @code
 * hw/hwa_write_reg( COUNTER, count, 0 );
 * @endcode
 */
#define _hw_mthd_hw_clear__c8a		, _hw_clear_c8a
#define _hw_clear_c8a(p,i,a,...)	HW_TX(_hw_write_reg(p,count,0),__VA_ARGS__)

#define _hw_mthd_hwa_clear__c8a		, _hwa_clear_c8a
#define _hwa_clear_c8a(p,i,a,...)	HW_TX(_hwa_write_reg(p,count,0),__VA_ARGS__)


/**
 * @page atmelavr_c8a
 * @section atmelavr_c8a_stat Getting the status of the counter
 *
 * Available flags are:
 * * overflow
 * * compare0
 * * compare1
 *
 * These flags correspond to the interrupt requests the counter can
 * trigger.
 *
 * @code
 * //  Create a structure to receive the counter status
 * //
 * hw_stat_t(COUNTER) st ;
 *
 * //  Copy the counter status to the structure
 * //
 * st = hw_stat( COUNTER );
 *
 * //  Process the overflow flag
 * //
 * if ( st.overflow ) {
 *   hw_clear_irq( COUNTER, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 *
 * @code
 * //  Process the overflow flag
 * //
 * if ( hw_stat( COUNTER ).overflow ) {
 *   hw_clear_irq( COUNTER, overflow );
 *   n_overflows++ ;
 * }
 * @endcode
 */
#define _hw_mthd_hw_stat__c8a		, _hw_stat_c8a
#define _hw_mthd_hw_stat_t__c8a		, _hw_statt_c8a

#define _hw_statt_c8a(p,i,a,...)	HW_TX(_hw_c8a_stat_t, __VA_ARGS__)

#ifndef HW_DEVICE_ATTINYX5

  typedef union {
    uint8_t         byte ;
    struct {
      unsigned int  overflow : 1 ;
      unsigned int  compare0 : 1 ;
      unsigned int  compare1 : 1 ;
      unsigned int  __3to7   : 5 ;
    };
  } _hw_c8a_stat_t ;

#define _hw_stat_c8a(p,i,a,...)		HW_TX(_hw_c8a_stat(_hw_read_reg(p, ifr)),__VA_ARGS__)

HW_INLINE _hw_c8a_stat_t _hw_c8a_stat( uint8_t byte )
{
  _hw_c8a_stat_t	st ;
  st.byte = byte ;
  return st ;
}

#endif


/**
 * @page atmelavr_c8a
 * <br>
 */
