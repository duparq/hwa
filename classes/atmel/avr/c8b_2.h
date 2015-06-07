
/*  This file is part of the HWA project.
 *  Copyright (c) 2012,2015 Christophe Duparquet.
 *  All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 */


HW_INLINE void __hwa_begin__c8b ( hwa_c8b_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _c8b, ccra     );
  _hwa_begin_reg_p( p, a, _c8b, ccrb     );
  _hwa_begin_reg_p( p, a, _c8b, count    );
  _hwa_begin_reg_p( p, a, _c8b, compare0 );
  _hwa_begin_reg_p( p, a, _c8b, compare1 );
  _hwa_begin_reg_p( p, a, _c8b, imsk     );
  _hwa_begin_reg_p( p, a, _c8b, ifr      );
  _hwa_begin_reg_p( p, a, _c8b, assr     );

  p->config.clock           = 0xFF ;
  p->config.countmode       = 0xFF ;
  p->config.top             = 0xFF ;
  p->config.overflow        = 0xFF ;
  p->config.compare0.update = 0xFF ;
  p->config.compare0.output = 0xFF ;
  p->config.compare1.update = 0xFF ;
  p->config.compare1.output = 0xFF ;
}


HW_INLINE void __hwa_init__c8b ( hwa_c8b_t *p )
{
  _hwa_set_r8( &p->ccra,     0x00 );
  _hwa_set_r8( &p->ccrb,     0x00 );
  _hwa_set_r8( &p->count,    0x00 );
  _hwa_set_r8( &p->compare0, 0x00 );
  _hwa_set_r8( &p->compare1, 0x00 );
  _hwa_set_r8( &p->imsk,     0x00 );
  _hwa_set_r8( &p->ifr,      0x00 );
  _hwa_set_r8( &p->assr,     0x00 );
}


HW_INLINE void __hwa_commit__c8b ( hwa_t *hwa, hwa_c8b_t *p )
{
  _hwa_commit_reg_p( p, _c8b, ccra     );
  _hwa_commit_reg_p( p, _c8b, ccrb     );
  _hwa_commit_reg_p( p, _c8b, count    );
  _hwa_commit_reg_p( p, _c8b, compare0 );
  _hwa_commit_reg_p( p, _c8b, compare1 );
  _hwa_commit_reg_p( p, _c8b, imsk     );
  _hwa_commit_reg_p( p, _c8b, ifr      );
  _hwa_commit_reg_p( p, _c8b, assr     );
}


/**
 * @page atmelavr_c8b
 * @section atmelavr_c8b_config Configuring the counter
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
 *                        | syshz               // CPU clock frequency
 *                        | syshz_div_1         // CPU clock frequency
 *                        | syshz_div_8         // CPU clock, frequency / 8
 *                        | syshz_div_32        // CPU clock, frequency / 32
 *                        | syshz_div_64        // CPU clock, frequency / 64
 *                        | syshz_div_128       // CPU clock, frequency / 128
 *                        | syshz_div_256       // CPU clock, frequency / 256
 *                        | syshz_div_1024      // CPU clock, frequency / 1024
 *                        | hw_pin_tosc1        // External (edge?), crystal between TOSC1-TOSC2
 *
 *             //  How does this counter count
 *             //
 *             countmode,   loop_up             // Count up and loop
 *                        | loop_updown,        // Count up and down alternately
 *
 *             //  Class _c8b counters count from 0
 *             //
 *            [bottom,      0, ]
 *
 *             //  The maximum value the counter reaches (the default is `max`)
 *             //
 *            [top,         fixed_0xFF          // Hardware fixed value 0x00FF
 *                        | max                 // Hardware fixed value 0xFFFF
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
#define _hw_mthd_hwa_config__c8b			, _hwa_config_c8b

#define _hw_c8b_countmode_loop_up		, 1
#define _hw_c8b_countmode_loop_updown		, 2

#define _hw_c8b_top_fixed_0xFF			, 1
#define _hw_c8b_top_max				, 1
#define _hw_c8b_top_compare0			, 2

#define _hw_c8b_clock_none			, 0
#define _hw_c8b_clock_syshz			, 1
#define _hw_c8b_clock_syshz_div_1		, 1	/* Useful for concat */
#define _hw_c8b_clock_syshz_div_8		, 2
#define _hw_c8b_clock_syshz_div_32		, 3
#define _hw_c8b_clock_syshz_div_64		, 4
#define _hw_c8b_clock_syshz_div_128		, 5
#define _hw_c8b_clock_syshz_div_256		, 6
#define _hw_c8b_clock_syshz_div_1024		, 7
#define _hw_c8b_clock_hw_pin_tosc1		, 8

#define _hw_c8b_overflow_at_bottom		, 0
#define _hw_c8b_overflow_at_top			, 1
#define _hw_c8b_overflow_at_max			, 2

#define _hwa_config_c8b(p,i,a, ...)					\
  do { HW_G2(_hwa_cfc8b_kclock,HW_IS(clock,__VA_ARGS__))(p,__VA_ARGS__,) } while(0)

#define _hwa_cfc8b_kclock_0(o,k,...)					\
  HW_ERR("expected `clock` instead of `" #k "`.")

#define _hwa_cfc8b_kclock_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8b_vclock,HW_IS(,_hw_c8b_clock_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vclock_0(o,v,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_1`, "		\
	  "`syshz_div_8`, `syshz_div_32`, `syshz_div_64`, "		\
	  "`syshz_div_128`, `syshz_div_256`, `syshz_div_1024`, "	\
	  "or `hw_pin_tosc1`, but not `" #v "`.")

#define _hwa_cfc8b_vclock_1(o,v,k,...)					\
  hwa->o.config.clock = HW_A1(_hw_c8b_clock_##v);			\
  HW_G2(_hwa_cfc8b_kmode,HW_IS(countmode,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8b_kmode_0(o,k,...)			\
  HW_ERR("expected `countmode` instead of `" #k "`.")

#define _hwa_cfc8b_kmode_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8b_vmode,HW_IS(,_hw_c8b_countmode_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vmode_0(o,v,...)					\
  HW_ERR("`mode` can be `loop_up`, or `loo_updown`, but not `" #v "`.")

#define _hwa_cfc8b_vmode_1(o,v,k,...)					\
  hwa->o.config.countmode = HW_A1(_hw_c8b_countmode_##v);		\
  HW_G2(_hwa_cfc8b_kbottom,HW_IS(bottom,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8b_kbottom_1(o,k,v,...)				\
  HW_G2(_hwa_cfc8b_vbottom,HW_IS(0,v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vbottom_0(o,v,...)		\
  HW_ERR("bottom must be `0`, not `" #v "`.")

#define _hwa_cfc8b_vbottom_1(o,v,...)		\
  _hwa_cfc8b_kbottom_0(o,__VA_ARGS__)

#define _hwa_cfc8b_kbottom_0(o,k,...)			\
  HW_G2(_hwa_cfc8b_ktop,HW_IS(top,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8b_ktop_1(o,k,v,...)					\
  HW_G2(_hwa_cfc8b_vtop,HW_IS(,_hw_c8b_top_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_vtop_0(o,v,...)				\
  HW_ERR("`top` can be `fixed_0xFF`, `max`, or `compare0`,"	\
	 " but not `" #v "`.")

#define _hwa_cfc8b_vtop_1(o,v,...)		\
  hwa->o.config.top = HW_A1(_hw_c8b_top_##v);	\
  _hwa_cfc8b_ktop_0(o,__VA_ARGS__)

#define _hwa_cfc8b_ktop_0(o,k,...)					\
  HW_G2(_hwa_cfc8b_koverflow,HW_IS(overflow,k))(o,k,__VA_ARGS__)

#define _hwa_cfc8b_koverflow_1(o,k,v,...)				\
  HW_G2(_hwa_cfc8b_voverflow, HW_IS(,_hw_c8b_overflow_##v))(o,v,__VA_ARGS__)

#define _hwa_cfc8b_voverflow_0(o,v,...)				\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #v "`.")

#define _hwa_cfc8b_voverflow_1(o,v,...)					\
  if ( hwa->o.config.countmode == HW_A1(hw_c8b_countmode_loop_up)	\
       && HW_A1(_hw_c8b_overflow_##v) == HW_A1(_hw_c8b_overflow_at_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `at_bottom` "	\
	    "when countmode is `loop_up`.");				\
  HW_TX(hwa->o.config.overflow = HW_A1(_hw_c8b_overflow_##v); ,__VA_ARGS__)

#define _hwa_cfc8b_koverflow_0(o,...)		\
  HW_TX(,__VA_ARGS__)


/*  Solve the configuration of the counter and its compare and capture units
 *
 *  Except the structure hwa_c8b_t, this is exactly the same as
 *  __hwa_solve__c8b.
 *
 *  Alternatively, computed values to be written into hardware registers could
 *  be stored in a 'solved' structure. They would be written by the 'commit'
 *  function at device level which knows the register mapping of the counter
 *  that is used.
 */
HW_INLINE void _hwa_solve_c8b ( hwa_c8b_t *p )
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
    p->config.top = HW_A1(_hw_c8b_top_max);

  /*  Default config for overflow
   */
  uint8_t overflow = p->config.overflow ;
  if ( overflow == 0xFF && p->config.top == HW_A1(_hw_c8b_top_compare0) ) {
    if ( p->config.countmode == HW_A1(_hw_c8b_countmode_loop_up) )
      overflow = HW_A1(_hw_c8b_overflow_at_top);
    else /* if ( p->config.countmode == HW_A1(hw_c8b_countmode_loop_up) ) */
      overflow = HW_A1(_hw_c8b_overflow_at_bottom);
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
  if ( p->config.countmode == HW_A1(_hw_c8b_countmode_loop_up) ) {
    if ( p->config.top == HW_A1(_hw_c8b_top_fixed_0xFF) ) {
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
	   || overflow == HW_A1(_hw_c8b_overflow_at_top)
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
    if ( p->config.top == HW_A1(_hw_c8b_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    HWA_ERR("WGM value could not be solved for _c8b class counter.");
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
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==7 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==5 ) {
	if ( p->config.compare0.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare0.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
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
	  HWA_ERR("compare output B of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c8b counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( p->config.compare1.output != HW_A1(hw_ocu_output_disconnected)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->config.compare1.output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output B of class _c8b counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Update
     */
    if ( compare_update != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( compare_update != HW_A1(hw_ocu_update_immediately) )
	  HWA_ERR("optionnal parameter 'update' of class _c8b counter must be "\
		  "'immediately'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( compare_update != HW_A1(hw_ocu_update_at_bottom) )
	  HWA_ERR("optionnal parameter 'update' of class _c8b counter must be "
		  "'at_bottom'.");
      }
      else
	if( compare_update != HW_A1(hw_ocu_update_at_top) )
	  HWA_ERR("optionnal parameter 'update' of class _c8b counter must be "
		  "'at_top'.");
    }

    /*	Overflow
     */
    if ( overflow != 0xFF ) {
      if ( wgm==7 ) {
	if ( overflow != HW_A1(_hw_c8b_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8b counter must be "
		  "'at_top'.");
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(_hw_c8b_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8b counter must be "
		  "'at_bottom'.");
      }
      else if ( overflow != HW_A1(_hw_c8b_overflow_at_max) )
	HWA_ERR("optionnal parameter 'overflow' of class _c8b counter must be "
		"'at_max'.");
    }
  }
 }


	     /*	Read/write the 'count' register of a _c8b counter
	      */
#define _hw_mthd_hw_read__c8b		, _hw_read_c8b
#define _hw_read_c8b(p,i,a,...)		HW_TX(_hw_read_reg(p,count),__VA_ARGS__)

#define _hw_mthd_hw_write__c8b		, _hw_write_c8b
#define _hw_write_c8b(p,i,a,v)		_hw_write_reg(p,count,v)

#define _hw_mthd_hwa_write__c8b		, _hwa_write_c8b
#define _hwa_write_c8b(p,i,a,v)		_hwa_write_reg(p,count,v)

#define _hw_mthd_hw_clear__c8b		, _hw_clear_c8b
#define _hw_clear_c8b(p,i,a,...)	HW_TX(_hw_write_reg(p,count,0),__VA_ARGS__)

#define _hw_mthd_hwa_clear__c8b		, _hwa_clear_c8b
#define _hwa_clear_c8b(p,i,a,...)	HW_TX(_hwa_write_reg(p,count,0),__VA_ARGS__)


	     /*  Status
	      *
	      *	hw_stat_t(...) declares the structure that holds the status
	      *	hw_stat(...) reads and returns the status
	      *
	      *	The only flag that is available is the irq flag.
	      */
#define _hw_mthd_hw_stat__c8b		, _hw_stat_c8b
#define _hw_mthd_hw_stat_t__c8b		, _hw_statt_c8b

#define _hw_statt_c8b(p,i,a,...)	HW_TX(_hw_c8b_stat_t, __VA_ARGS__)

#ifndef HW_DEVICE_ATTINYX5

	     typedef union {
	       uint8_t         byte ;
	       struct {
		 unsigned int  overflow : 1 ;
		 unsigned int  compare0 : 1 ;
		 unsigned int  compare1 : 1 ;
		 unsigned int  __3to7   : 5 ;
	       };
	     } _hw_c8b_stat_t ;

#define _hw_stat_c8b(p,i,a,...)		HW_TX(_hw_c8b_stat(_hw_read_reg(p, ifr)),__VA_ARGS__)

	     HW_INLINE _hw_c8b_stat_t _hw_c8b_stat( uint8_t byte )
	  {
	    _hw_c8b_stat_t	st ;
	    st.byte = byte ;
	    return st ;
	  }

#endif

/**
 * @page atmelavr_c8b
 * <br>
 */
