
/*	Atmel AVR 8-bit timer-counter model 'b'
 *
 *	Used in: ATmegaX8 hw_counter2
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

//#include "hwa_atmelavr__counters.h"
#include "hwa_atmelavr__ocua_2.h"


HW_INLINE void __hwa_begin__c8b ( hwa_c8b_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _c8b, ccra  );
  _hwa_begin_reg_p( p, a, _c8b, ccrb  );
  _hwa_begin_reg_p( p, a, _c8b, count );
  _hwa_begin_reg_p( p, a, _c8b, ocra  );
  _hwa_begin_reg_p( p, a, _c8b, ocrb  );
  _hwa_begin_reg_p( p, a, _c8b, imsk  );
  _hwa_begin_reg_p( p, a, _c8b, ifr   );
  _hwa_begin_reg_p( p, a, _c8b, assr  );

  p->clock           = 0xFF ;
  p->countmode       = 0xFF ;
  p->top             = 0xFF ;
  p->overflow        = 0xFF ;
  p->compare0_update = 0xFF ;
  p->compare0_output = 0xFF ;
  p->compare1_update = 0xFF ;
  p->compare1_output = 0xFF ;

  /* p->solved.cs       = 0xFF ; */
  /* p->solved.wgm      = 0xFF ; */
  /* p->solved.coma     = 0xFF ; */
  /* p->solved.comb     = 0xFF ; */
}


HW_INLINE void __hwa_init__c8b ( hwa_c8b_t *p )
{
  _hwa_set_r8( &p->ccra,  0x00 );
  _hwa_set_r8( &p->ccrb,  0x00 );
  _hwa_set_r8( &p->count, 0x00 );
  _hwa_set_r8( &p->ocra,  0x00 );
  _hwa_set_r8( &p->ocrb,  0x00 );
  _hwa_set_r8( &p->imsk,  0x00 );
  _hwa_set_r8( &p->ifr,   0x00 );
  _hwa_set_r8( &p->assr,  0x00 );
}


HW_INLINE void __hwa_commit__c8b ( hwa_t *hwa, hwa_c8b_t *p )
{
  _hwa_commit_reg_p( p, _c8b, ccra  );
  _hwa_commit_reg_p( p, _c8b, ccrb  );
  _hwa_commit_reg_p( p, _c8b, count );
  _hwa_commit_reg_p( p, _c8b, ocra  );
  _hwa_commit_reg_p( p, _c8b, ocrb  );
  _hwa_commit_reg_p( p, _c8b, imsk  );
  _hwa_commit_reg_p( p, _c8b, ifr   );
  _hwa_commit_reg_p( p, _c8b, assr  );
}


#define hw_c8b_countmode_loop_up		, 1
#define hw_c8b_countmode_loop_updown		, 2

#define hw_c8b_top_fixed_0xFF			, 1
#define hw_c8b_top_max				, 1
#define hw_c8b_top_compare0			, 2

#define hw_c8b_clock_none			, 0
#define hw_c8b_clock_syshz			, 1
#define hw_c8b_clock_syshz_div_1		, 1	/* Useful for concat */
#define hw_c8b_clock_syshz_div_8		, 2
#define hw_c8b_clock_syshz_div_32		, 3
#define hw_c8b_clock_syshz_div_64		, 4
#define hw_c8b_clock_syshz_div_128		, 5
#define hw_c8b_clock_syshz_div_256		, 6
#define hw_c8b_clock_syshz_div_1024		, 7
//#define hw_c8b_clock_external			,


/*	hwa_config( COUNTER,
 *
 *	            clock,       none,
 *	                       | syshz,
 *	                       | syshz_div_1,
 *	                       | syshz_div_8,
 *	                       | syshz_div_32,
 *	                       | syshz_div_64,
 *	                       | syshz_div_128,
 *	                       | syshz_div_256,
 *	                       | syshz_div_1024,
 *	                       | external,
 *
 *	            countmode,   loop_up,
 *	                       | loop_updown,
 *
 *	           [bottom,      0,]
 *
 *	            top,         fixed_0xFF,
 *	                       | max,
 *	                       | compare0,
 *
 *	           [overflow,    at_bottom,
 *	                       | at_top,
 *	                       | at_max,]	)
 */
#define _hw_mthd_hwa_config__c8b			, _hwa_config_c8b

#define _hwa_config_c8b(p,i,a, ...)						\
  do { HW_G2(_hwa_cfc8b_xclock,HW_IS(clock,__VA_ARGS__))(p,__VA_ARGS__) } while(0)

#define _hwa_cfc8b_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8b_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_cfc8b_vclock,HW_IS(,hw_c8b_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_vclock_0(n,...)			\
  HW_ERR( "`clock` can be `none`, "			\
	  "`syshz`, "					\
	  "`syshz_div_1`, "				\
	  "`syshz_div_8`, "				\
	  "`syshz_div_32`, "				\
	  "`syshz_div_64`, "				\
	  "`syshz_div_128`, "				\
	  "`syshz_div_256`, "				\
	  "`syshz_div_1024`, "				\
	  "or `external` (not yet implemented), "	\
	  "but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8b_vclock_1(n,zclock,...)				\
  hwa->n.clock = HW_A1(hw_c8b_clock_##zclock);				\
  HW_G2(_hwa_cfc8b_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8b_xmode_1(n,_countmode_,...)				\
  HW_G2(_hwa_cfc8b_vmode,HW_IS(,hw_c8b_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_vmode_0(n,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_cfc8b_vmode_1(n,vmode,...)					\
  hwa->n.countmode = HW_A1(hw_c8b_countmode_##vmode);			\
  HW_G2(_hwa_cfc8b_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_cfc8b_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_cfc8b_vbottom_1(n,bottom,...)	\
  _hwa_cfc8b_xbottom_0(n,__VA_ARGS__)

#define _hwa_cfc8b_xbottom_0(n,...)				\
  HW_G2(_hwa_cfc8b_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_cfc8b_xtop_1(n,_top_,...)					\
  HW_G2(_hwa_cfc8b_vtop,HW_IS(,hw_c8b_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_vtop_0(n,...)				\
  HW_ERR("`top` can be `fixed_0xFF`, `max`, or `compare0`,"	\
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8b_vtop_1(n,ztop,...)					\
  hwa->n.top = HW_A1(hw_c8b_top_##ztop);				\
  HW_G2(_hwa_cfc8b_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_xuc_1(n,uc,...)					\
  HW_G2(_hwa_cfc8b_vuc, HW_IS(,hw_ocu_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_vuc_0(n,vuc,...)					\
  HW_ERR("`update` can be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_cfc8b_vuc_1(n,vuc,...)		\
    hwa->n.update = HW_A1(hw_ocu_update_##vuc);	\
    _hwa_cfc8b_xuc_0(n,__VA_ARGS__);

#define _hwa_cfc8b_xuc_0(n,...)						\
  HW_G2(_hwa_cfc8b_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_xoverflow_1(n,overflow,...)				\
  HW_G2(_hwa_cfc8b_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8b_voverflow_0(n,overflow,...)			\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_cfc8b_voverflow_1(n,voverflow,...)				\
  if ( hwa->n.countmode == HW_A1(hw_c8b_countmode_loop_up)		\
       && HW_A1(hw_counter_overflow_##voverflow) == HW_A1(hw_counter_overflow_at_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `at_bottom` "	\
	    "when countmode is `loop_up`.");				\
  HW_TX(hwa->n.overflow = HW_A1(hw_counter_overflow_##voverflow); ,__VA_ARGS__)

#define _hwa_cfc8b_xoverflow_0(n,...)		\
  HW_TX(,__VA_ARGS__)


/*  Solve the configuration of the counter and its compare and capture units
 *
 *  Except the structure hwa_c8b_t, this is exactly the same as
 *  __hwa_solve__c8a.
 *
 *  Alternatively, computed values to be written into hardware registers could
 *  be stored in a 'solved' structure. They would be written by the 'commit'
 *  function at device level which knows the register mapping of the counter
 *  that is used.
 */
HW_INLINE void __hwa_solve__c8b ( hwa_t *hwa __attribute__((unused)), hwa_c8b_t *p )
{
  if ( p->clock == 0xFF )
    return ;


  /*	Clock selection
   */
  _hwa_write_creg( p, _c8b, cs, p->clock );
  //  p->solved.cs = p->clock ;


  /*  Default config for overflow
   */
  uint8_t overflow = p->overflow ;
  if ( overflow == 0xFF && p->top == HW_A1(hw_c8b_top_compare0) ) {
    if ( p->countmode == HW_A1(hw_c8b_countmode_loop_up) )
      overflow = HW_A1(hw_counter_overflow_at_top);
    else /* if ( p->countmode == HW_A1(hw_c8b_countmode_loop_up) ) */
      overflow = HW_A1(hw_counter_overflow_at_bottom);
  }


  /*  Compare update setting
   */
  uint8_t compare_update = 0xFF ;
  if ( p->compare0_update != 0xFF && p->compare1_update != 0xFF
       && p->compare0_update != p->compare1_update )
    HWA_ERR("optionnal parameter 'update' of class _c16a counter must be " \
	    "'immediately'.");
  compare_update = p->compare0_update ;


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
  if ( p->countmode == HW_A1(hw_c8b_countmode_loop_up) ) {
    if ( p->top == HW_A1(hw_c8b_top_fixed_0xFF) ) {
      if ( compare_update == HW_A1(hw_ocu_update_at_bottom)
	   || p->compare0_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->compare0_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	   || p->compare1_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match))
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
	   || overflow == HW_A1(hw_counter_overflow_at_top)
	   || p->compare0_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->compare0_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	   || p->compare1_output == HW_A1(hw_ocu_output_clear_at_bottom_set_on_match)
	   || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match))
	wgm = 7 ;
      else
	wgm = 2 ;
    }
  }
  else /* countmode == loop_updown */ {
    if ( p->top == HW_A1(hw_c8b_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    HWA_ERR("WGM value could not be solved for _c8b class counter.");
    return ;
  }

  _hwa_write_creg(p, _c8b, wgm, wgm);
  //  p->solved.wgm = wgm ;


  /*	Solve the configuration of compare output A
   */
  if ( p->compare0_output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->compare0_output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->compare0_output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->compare0_output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->compare0_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->compare0_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_creg(p, _c8b, coma, mode );
    //    p->solved.coma = mode ;
  }


  /*	Solve the configuration of compare output B
   */
  if ( p->compare1_output != 0xFF ) {

    uint8_t	mode = 0xFF ;

    if ( p->compare1_output == HW_A1(hw_ocu_output_disconnected) )
      mode = 0 ;
    else if ( p->compare1_output == HW_A1(hw_ocu_output_toggle_on_match) )
      mode = 1 ;
    else if ( p->compare1_output == HW_A1(hw_ocu_output_clear_on_match)
	      || p->compare1_output == HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	      || p->compare1_output == HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down) )
      mode = 2 ;
    else
      mode = 3 ;

    _hwa_write_creg(p, _c8b, comb, mode );
    //    p->solved.comb = mode ;
  }


  /*	Check the validity of the configuration
   */
  if ( p->clock != 0xFF || p->compare0_output != 0xFF || p->compare1_output != 0xFF ) {

    if ( p->clock == 0xFF ) {
      HWA_ERR("configuration of counter is required.");
      return ;
    }

    /*	Compare output A
     */
    if ( p->compare0_output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match))
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==7 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==5 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
    }

    /*	Compare output B
     */
    if ( p->compare1_output != 0xFF ) {
      if ( wgm==0 || wgm==2 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_on_match))
	  HWA_ERR("compare output B of class _c8b counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c8b counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
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
	if ( overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8b counter must be "
		  "'at_top'.");
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(hw_counter_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8b counter must be "
		  "'at_bottom'.");
      }
      else if ( overflow != HW_A1(hw_counter_overflow_at_max) )
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
