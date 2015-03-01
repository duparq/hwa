
/*	Atmel AVR 8-bit timer-counter model 'a'
 *
 *	Used in: ATtinyX4 (TIM0)	hw_counter0
 *
 * This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */

#include "hwa_atmelavr__counters.h"
#include "hwa_atmelavr__ocua_2.h"


HW_INLINE void __hwa_begin__c8a ( hwa_c8a_t *p, intptr_t a )
{
  _hwa_begin_pacr( p, a, _c8a, ccra  );
  _hwa_begin_pacr( p, a, _c8a, ccrb  );
  _hwa_begin_pacr( p, a, _c8a, count );
  _hwa_begin_pacr( p, a, _c8a, ocra  );
  _hwa_begin_pacr( p, a, _c8a, ocrb  );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_begin_pacr( p, a, _c8a, imsk  );
  _hwa_begin_pacr( p, a, _c8a, ifr   );
#endif

  p->clock           = 0xFF ;
  p->countmode       = 0xFF ;
  p->top             = 0xFF ;
  p->overflow        = 0xFF ;
  p->compare0_update = 0xFF ;
  p->compare0_output = 0xFF ;
  p->compare1_update = 0xFF ;
  p->compare1_output = 0xFF ;
}


HW_INLINE void __hwa_init__c8a ( hwa_c8a_t *p )
{
  _hwa_set_r8( &p->ccra,  0x00 );
  _hwa_set_r8( &p->ccrb,  0x00 );
  _hwa_set_r8( &p->count, 0x00 );
  _hwa_set_r8( &p->ocra,  0x00 );
  _hwa_set_r8( &p->ocrb,  0x00 );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_set_r8( &p->imsk,  0x00 );
  _hwa_set_r8( &p->ifr,   0x00 );
#endif
}


HW_INLINE void __hwa_commit__c8a ( hwa_t *hwa, hwa_c8a_t *p )
{
  _hwa_commit_pcr( p, _c8a, ccra  );
  _hwa_commit_pcr( p, _c8a, ccrb  );
  _hwa_commit_pcr( p, _c8a, count );
  _hwa_commit_pcr( p, _c8a, ocra  );
  _hwa_commit_pcr( p, _c8a, ocrb  );
#ifndef HW_DEVICE_ATTINYX5
  _hwa_commit_pcr( p, _c8a, imsk  );
  _hwa_commit_pcr( p, _c8a, ifr   );
#endif
}


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


/*	hwa_config( COUNTER,
 *
 *	            clock,       none,
 *	                       | syshz,
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
#define hw_def_hwa_config__c8a			, _hwa_cfc8a

#define _hwa_cfc8a(c,n,i,a, ...)					\
  do { HW_G2(_hwa_cfc8a_xclock,HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) } while(0)

#define _hwa_cfc8a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_xclock_1(n,_clock_,...)				\
  HW_G2(_hwa_cfc8a_vclock,HW_IS(,hw_c8a_clock_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vclock_0(n,...)					\
  HW_ERR( "`clock` can be `none`, `syshz`, `syshz_div_1`, `syshz_div_8`, " \
	  "`syshz_div_64`, `syshz_div_256`, `syshz_div_1024`, "		\
	  "`ext_falling`, `ext_rising`, but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_vclock_1(n,zclock,...)				\
  hwa->n.clock = HW_A1(hw_c8a_clock_##zclock);				\
  HW_G2(_hwa_cfc8a_xmode,HW_IS(countmode,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xmode_0(n,...)					\
  HW_ERR("expected `countmode` instead of `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_xmode_1(n,_countmode_,...)				\
  HW_G2(_hwa_cfc8a_vmode,HW_IS(,hw_c8a_countmode_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vmode_0(n,...)					\
  HW_ERR( "`" HW_QUOTE(__VA_ARGS__) "` is not a valid mode option.")

#define _hwa_cfc8a_vmode_1(n,vmode,...)					\
  hwa->n.countmode = HW_A1(hw_c8a_countmode_##vmode);			\
  HW_G2(_hwa_cfc8a_xbottom,HW_IS(bottom,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xbottom_1(n,_bottom_,...)			\
  HW_G2(_hwa_cfc8a_vbottom,HW_IS(0,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vbottom_0(n,bottom,...)		\
  HW_ERR("bottom must be `0`, not `" #bottom "`.")

#define _hwa_cfc8a_vbottom_1(n,bottom,...)	\
  _hwa_cfc8a_xbottom_0(n,__VA_ARGS__)

#define _hwa_cfc8a_xbottom_0(n,...)				\
  HW_G2(_hwa_cfc8a_xtop,HW_IS(top,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xtop_0(n,...)				\
  HW_ERR("expected `top` instead of `" #__VA_ARGS__ "`.")

#define _hwa_cfc8a_xtop_1(n,_top_,...)					\
  HW_G2(_hwa_cfc8a_vtop,HW_IS(,hw_c8a_top_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vtop_0(n,...)				\
  HW_ERR("`top` can be `fixed_0xFF`, `max`, or `compare0`,"	\
	 " but not `" HW_QUOTE(__VA_ARGS__) "`.")

#define _hwa_cfc8a_vtop_1(n,ztop,...)					\
  hwa->n.top = HW_A1(hw_c8a_top_##ztop);				\
  HW_G2(_hwa_cfc8a_xuc,HW_IS(update,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xuc_1(n,uc,...)					\
  HW_G2(_hwa_cfc8a_vuc, HW_IS(,hw_ocu_update_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_vuc_0(n,vuc,...)					\
  HW_ERR("`update` can be `at_bottom`, `at_top, or `at_max`, but `not `" #vuc "`.")

#define _hwa_cfc8a_vuc_1(n,vuc,...)		\
    hwa->n.update = HW_A1(hw_ocu_update_##vuc);	\
    _hwa_cfc8a_xuc_0(n,__VA_ARGS__);

#define _hwa_cfc8a_xuc_0(n,...)						\
  HW_G2(_hwa_cfc8a_xoverflow,HW_IS(overflow,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_xoverflow_1(n,overflow,...)				\
  HW_G2(_hwa_cfc8a_voverflow, HW_IS(,hw_counter_overflow_##__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfc8a_voverflow_0(n,overflow,...)			\
  HW_ERR("optionnal parameter `overflow` can be `at_bottom`, "	\
	 "`at_top, or `at_max`, but `not `" #overflow "`.")

#define _hwa_cfc8a_voverflow_1(n,voverflow,...)				\
  if ( hwa->n.countmode == HW_A1(hw_c8a_countmode_loop_up)		\
       && HW_A1(hw_counter_overflow_##voverflow) == HW_A1(hw_counter_overflow_at_bottom) ) \
    HWA_ERR("optionnal parameter `overflow` can not be `at_bottom` "	\
	    "when countmode is `loop_up`.");				\
  HW_TX(hwa->n.overflow = HW_A1(hw_counter_overflow_##voverflow); ,__VA_ARGS__)

#define _hwa_cfc8a_xoverflow_0(n,...)		\
  HW_TX(,__VA_ARGS__)


/*	Solve the configuration of the counter and its compare and capture units
 */
HW_INLINE void __hwa_solve__c8a ( hwa_t *hwa __attribute__((unused)), hwa_c8a_t *p )
{
  if ( p->clock == 0xFF )
    return ;

  /*	Clock selection
   */
  _hwa_write_pcr( p, _c8a, cs, p->clock );


  /*  Default config for overflow
   */
  uint8_t overflow = p->overflow ;
  if ( overflow == 0xFF && p->top == HW_A1(hw_c8a_top_compare0) ) {
    if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) )
      overflow = HW_A1(hw_counter_overflow_at_top);
    else /* if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) ) */
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
  if ( p->countmode == HW_A1(hw_c8a_countmode_loop_up) ) {
    if ( p->top == HW_A1(hw_c8a_top_fixed_0xFF) ) {
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
    if ( p->top == HW_A1(hw_c8a_top_fixed_0xFF) )
      wgm = 1 ;
    else /* top == ocra */
      wgm = 5 ;
  }

  if (wgm == 0xFF) {
    HWA_ERR("WGM value could not be solved for _c8a class counter.");
    return ;
  }

  _hwa_write_pcr(p, _c8a, wgm, wgm);


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

    _hwa_write_pcr(p, _c8a, coma, mode );
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

    _hwa_write_pcr(p, _c8a, comb, mode );
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
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==7 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', "
		  "'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
		  "'disconnected', 'clear_on_match_up_set_on_match_down', "
		  "or 'set_on_match_up_clear_on_match_down'.");
      }
      else if ( wgm==5 ) {
	if ( p->compare0_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare0_output != HW_A1(hw_ocu_output_toggle_on_match)
	     && p->compare0_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare0_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
	  HWA_ERR("compare output A of class _c8a counter mode must be "
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
	  HWA_ERR("compare output B of class _c8a counter mode must be "
		  "'disconnected', 'toggle_on_match', 'clear_on_match', or "
		  "'set_on_match'.");
      }
      else if ( wgm==3 || wgm==7 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_at_bottom_clear_on_match)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_at_bottom_set_on_match) )
	  HWA_ERR("compare output B of class _c8a counter mode must be "
		  "'disconnected', 'set_at_bottom_clear_on_match', or "
		  "'clear_at_bottom_set_on_match'.");
      }
      else if ( wgm==1 || wgm==5 ) {
	if ( p->compare1_output != HW_A1(hw_ocu_output_disconnected)
	     && p->compare1_output != HW_A1(hw_ocu_output_clear_on_match_up_set_on_match_down)
	     && p->compare1_output != HW_A1(hw_ocu_output_set_on_match_up_clear_on_match_down) )
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
	if ( overflow != HW_A1(hw_counter_overflow_at_top) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_top'.");
      }
      else if ( (wgm==1 || wgm==5) ) {
	if ( overflow != HW_A1(hw_counter_overflow_at_bottom) )
	  HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		  "'at_bottom'.");
      }
      else if ( overflow != HW_A1(hw_counter_overflow_at_max) )
	HWA_ERR("optionnal parameter 'overflow' of class _c8a counter must be "
		"'at_max'.");
    }
  }
}


/*	Read/write the 'count' register of a _c8a counter
 */
#define hw_def_hw_read__c8a		, _hw_read_c8a
#define _hw_read_c8a(c,n,i,a,...)	HW_TX(_hw_read_reg(c,n,i,a,count),__VA_ARGS__)

#define hw_def_hw_write__c8a		, _hw_write_c8a
#define _hw_write_c8a(c,n,i,a,v)	_hw_write_reg(c,n,i,a,count,v)

#define hw_def_hwa_write__c8a		, _hwa_write_c8a
#define _hwa_write_c8a(c,n,i,a,v)	_hwa_write_reg(c,n,i,a,count,v)

#define hw_def_hw_clear__c8a		, _hw_clear_c8a
#define _hw_clear_c8a(c,n,i,a,...)	HW_TX(_hw_write_reg(c,n,i,a,count,0),__VA_ARGS__)

#define hw_def_hwa_clear__c8a		, _hwa_clear_c8a
#define _hwa_clear_c8a(c,n,i,a)		_hwa_write_reg(c,n,i,a,count,0)


/*  Status
 *
 *	hw_stat_t(...) declares the structure that holds the status
 *	hw_stat(...) reads and returns the status
 *
 *	The only flag that is available is the irq flag.
 */
#define hw_def_hw_stat__c8a		, _hw_stat_c8a
#define hw_def_hw_stat_t__c8a		, _hw_statt_c8a

#define _hw_statt_c8a(c,n,i,a,...)	HW_TX(_hw_c8a_stat_t, __VA_ARGS__)

#ifndef HW_DEVICE_ATTINYX5

  typedef union {
    uint8_t         byte ;
    struct {
      unsigned int  overflow : 1 ;
      unsigned int  compare0  : 1 ;
      unsigned int  compare1  : 1 ;
      unsigned int  __3to7   : 5 ;
    };
  } _hw_c8a_stat_t ;

#define _hw_stat_c8a(c,n,i,a)		_hw_c8a_stat( _hw_read_reg(c,n,i,a, ifr) )

HW_INLINE _hw_c8a_stat_t _hw_c8a_stat( uint8_t byte )
{
  _hw_c8a_stat_t	st ;
  st.byte = byte ;
  return st ;
}

#endif
