
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


HW_INLINE void __hwa_begin__ad10a ( hwa_ad10a_t *p, intptr_t a )
{
  _hwa_begin_reg_p( p, a, _ad10a, admux );
  _hwa_begin_reg_p( p, a, _ad10a, sra   );
  _hwa_begin_reg_p( p, a, _ad10a, srb   );
  _hwa_begin_reg_p( p, a, _ad10a, did   );
}


HW_INLINE void __hwa_init__ad10a ( hwa_ad10a_t *p )
{
  _hwa_set_r8( &p->admux, 0x00 );
  _hwa_set_r8( &p->sra,   0x00 );
  _hwa_set_r8( &p->srb,   0x00 );
  _hwa_set_r8( &p->did,   0x00 );
}


HW_INLINE void __hwa_commit__ad10a ( hwa_t *hwa, hwa_ad10a_t *p )
{
  _hwa_commit_reg_p( p, _ad10a, admux );
  _hwa_commit_reg_p( p, _ad10a, sra   );
  _hwa_commit_reg_p( p, _ad10a, srb   );
  _hwa_commit_reg_p( p, _ad10a, did   );
}


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_config1 Configuring the ADC in single-end mode
 *
 * Note: the ADC is turned off by default. Configuring the ADC will
 * automatically turn it on.
 *
 * @code
 * hwa_config( ADC,
 * 
 *             clock,        syshz_div_2
 *                         | syshz_div_4
 *                         | syshz_div_8
 *                         | syshz_div_16
 *                         | syshz_div_32
 *                         | syshz_div_64
 *                         | syshz_div_128,
 * 
 *             trigger,      manual
 *                         | auto
 *                         | hw_acmp0
 *                         | hw_int0
 *                         | hw_counter0_output0
 *                         | hw_counter0_overflow
 *                         | hw_counter1_output1
 *                         | hw_counter1_overflow
 *                         | hw_counter1_input0,
 * 
 *             vref,         vcc
 *                         | pin_aref
 *                         | bandgap,
 * 
 *           [ align,        left
 *                         | right, ]
 * 
 *           [ polarity,     unipolar
 *                         | bipolar, ]
 * 
 *           [ gain,         1
 *                         | 20, ]
 * 
 *           [ input_mode,   single_end, ]
 * 
 *             input,        pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
 *                         | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7
 *                         | agnd
 *                         | bandgap
 *                         | temperature
 *           );
 * @endcode
 *
 * @section atmelavr_ad10a_config2 Configuring the ADC in differential mode
 * @code
 * hwa_config( ADC,
 * 
 *             clock,            syshz_div_2
 *                             | syshz_div_4
 *                             | syshz_div_8
 *                             | syshz_div_16
 *                             | syshz_div_32
 *                             | syshz_div_64
 *                             | syshz_div_128,
 * 
 *             trigger,          manual
 *                             | auto
 *                             | hw_acmp0
 *                             | hw_int0
 *                             | hw_counter0_output0
 *                             | hw_counter0_overflow
 *                             | hw_counter1_output1
 *                             | hw_counter1_overflow
 *                             | hw_counter1_input0,
 * 
 *             vref,             vcc
 *                             | pin_aref
 *                             | bandgap,
 * 
 *           [ align,            left
 *                             | right, ]
 * 
 *           [ polarity,         unipolar
 *                             | bipolar, ]
 * 
 *           [ gain,             1
 *                             | 20, ]
 * 
 *           [ input_mode,       differential, ]
 * 
 *             positive_input,   pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
 *                             | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7,
 * 
 *             negative_input,   pin_adc0 | pin_adc1 | pin_adc2 | pin_adc3
 *                             | pin_adc4 | pin_adc5 | pin_adc6 | pin_adc7
 *           );
 * @endcode
 *
 */
#define _hw_mthd_hwa_config__ad10a		, _hwa_cfad10a

#define _hw_is_trigger_trigger			, 1
#define _hw_is_vref_vref			, 1
#define _hw_is_align_align			, 1
#define _hw_is_polarity_polarity		, 1
#define _hw_is_input_mode_input_mode		, 1
#define _hw_is_input_input			, 1
#define _hw_is_gain_gain			, 1
#define _hw_is_positive_input_positive_input	, 1
#define _hw_is_negative_input_negative_input	, 1

#define hw_ad10a_clock_syshz_div_2		, 1	/* , ps */
#define hw_ad10a_clock_syshz_div_4		, 2
#define hw_ad10a_clock_syshz_div_8		, 3
#define hw_ad10a_clock_syshz_div_16		, 4
#define hw_ad10a_clock_syshz_div_32		, 5
#define hw_ad10a_clock_syshz_div_64		, 6
#define hw_ad10a_clock_syshz_div_128		, 7

#define hw_ad10a_trigger_manual			, 0, 0	/* , ate, ts */
#define hw_ad10a_trigger_auto			, 1, 0
#define hw_ad10a_trigger_hw_acmp0		, 1, 1
#define hw_ad10a_trigger_hw_int0		, 1, 2
#define hw_ad10a_trigger_hw_counter0_compare0	, 1, 3
#define hw_ad10a_trigger_hw_counter0_overflow	, 1, 4
#define hw_ad10a_trigger_hw_counter1_compare1	, 1, 5
#define hw_ad10a_trigger_hw_counter1_overflow	, 1, 6
#define hw_ad10a_trigger_hw_counter1_capture0	, 1, 7


#define hw_ad10a_vref_vcc			, 0	/* , refs */
#define hw_ad10a_vref_pin_aref			, 1
#define hw_ad10a_vref_bandgap			, 2

#define hw_ad10a_align_left			, 1	/* , lar */
#define hw_ad10a_align_right			, 0

#define hw_ad10a_input_mode_single_end		, im1	/* drive the parser */
#define hw_ad10a_input_mode_differential	, im2

#define hw_ad10a_input_hw_pin_pa0		, 0
#define hw_ad10a_input_hw_pin_pa1		, 1
#define hw_ad10a_input_hw_pin_pa2		, 2
#define hw_ad10a_input_hw_pin_pa3		, 3
#define hw_ad10a_input_hw_pin_pa4		, 4
#define hw_ad10a_input_hw_pin_pa5		, 5
#define hw_ad10a_input_hw_pin_pa6		, 6
#define hw_ad10a_input_hw_pin_pa7		, 7


#define _hwa_cfad10a(p,i,a,...)						\
  do {									\
    uint8_t gain __attribute__((unused)) = 1 ;				\
    _hwa_write_reg( p, en, 1 ); /* turn the ADC on */			\
    HW_G2(_hwa_cfad10a_xclock, HW_IS(clock,__VA_ARGS__))(p,__VA_ARGS__); \
  } while(0)
#define _hwa_cfad10a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xclock_1(n,clock,...)				\
  HW_G2(_hwa_cfad10a_vclock, HW_IS(,hw_ad10a_clock_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vclock_0(n,x,...)			\
  HW_ERR("`clock` can be `syshz_div_{1,2,4,8,16,32,64,128}`, not `"#x".")
#define _hwa_cfad10a_vclock_1(n,vclock,...)				\
  _hwa_write_reg(n,ps, HW_A1(hw_ad10a_clock_##vclock));	\
  HW_G2(_hwa_cfad10a_xtrigger, HW_IS(trigger,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfad10a_xtrigger_0(n,...)					\
  HW_ERR("expected `trigger` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xtrigger_1(n,trigger,...)				\
  HW_G2(_hwa_cfad10a_vtrigger, HW_IS(,hw_ad10a_trigger_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vtrigger_0(n,x,...)		\
  HW_ERR("`trigger` can be `manual`, `auto`, `hw_acmp0`, `int0`, `hw_counter0_compare0`, `hw_counter0_overflow`, `hw_counter1_compare1`, `hw_counter1_overflow`, `hw_counter1_capture0`, but not `" #x "`.")
#define _hwa_cfad10a_vtrigger_1(n,vtrigger,...)				\
  _hwa_write_reg(n,ate, HW_A1(hw_ad10a_trigger_##vtrigger));	\
  _hwa_write_reg(n,ts, HW_A2(hw_ad10a_trigger_##vtrigger));	\
  HW_G2(_hwa_cfad10a_xvref, HW_IS(vref,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfad10a_xvref_0(n,...)					\
  HW_ERR("expected `vref` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xvref_1(n,vref,...)				\
  HW_G2(_hwa_cfad10a_vvref, HW_IS(,hw_ad10a_vref_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vvref_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `vref`.")
#define _hwa_cfad10a_vvref_1(n,vvref,...)				\
  _hwa_write_reg(n,refs, HW_A1(hw_ad10a_vref_##vvref));	\
  _hwa_cfad10a_align(n,__VA_ARGS__)

/*	Optionnal parameter 'align'
 */
#define _hwa_cfad10a_align(n,...)					\
  HW_G2(_hwa_cfad10a_xalign, HW_IS(align,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xalign_0(n,...)					\
  _hwa_cfad10a_polarity(n,__VA_ARGS__) //  HW_ERR("expected `align` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xalign_1(n,align,...)				\
  HW_G2(_hwa_cfad10a_valign, HW_IS(,hw_ad10a_align_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_valign_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `align`.")
#define _hwa_cfad10a_valign_1(n,valign,...)				\
    _hwa_write_reg(n,lar, HW_A1(hw_ad10a_align_##valign));	\
    _hwa_cfad10a_polarity(n,__VA_ARGS__)

/*	Optionnal parameter 'polarity'
 */
#define _hwa_cfad10a_polarity(n,...)					\
    HW_G2(_hwa_cfad10a_xpolarity, HW_IS(polarity,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xpolarity_0(n,...)		\
  _hwa_cfad10a_gain(n,__VA_ARGS__)
#define _hwa_cfad10a_xpolarity_1(n,polarity,...)			\
  HW_G2(_hwa_cfad10a_vpolarity, HW_IS(,hw_ad10a_polarity_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vpolarity_0(n,x,...)		\
  HW_ERR("`"#x"` is not a valid value for `polarity`.")
#define _hwa_cfad10a_vpolarity_1(n,vpolarity,...)			\
  _hwa_write_reg(n,lar, HW_A1(hw_ad10a_polarity_##vpolarity));	\
  _hwa_cfad10a_gain(n,__VA_ARGS__)

/*	Optionnal parameter 'gain'
 */
#define _hwa_cfad10a_gain(n,...)					\
  HW_G2(_hwa_cfad10a_xgain, HW_IS(gain,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xgain_0(n,...)		\
  _hwa_cfad10a_input_mode(n,__VA_ARGS__)
#define _hwa_cfad10a_xgain_1(n,xgain,vgain,...)	\
  gain = (uint8_t)(vgain) ;			\
  if ( gain != 1 && gain != 20 )		\
    HWA_ERR("gain must be 1 or 20.");		\
  _hwa_cfad10a_input_mode(n,__VA_ARGS__)


/*	The optionnal parameter 'input_mode' drives the parser. If not
 *	specified, the mode is determined by the next parameter that must then
 *	be 'input' or positive_input'.
 */
#define _hwa_cfad10a_input_mode(n,...)					\
  HW_G2(_hwa_cfad10a_xinput_mode, HW_IS(input_mode,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xinput_mode_1(n,input_mode,...)			\
  HW_G2(_hwa_cfad10a_vinput_mode, HW_IS(,hw_ad10a_input_mode_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vinput_mode_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `input_mode`.")
#define _hwa_cfad10a_vinput_mode_1(n,vinput_mode,...)			\
  HW_G2(_hwa_cfad10a, HW_A1(hw_ad10a_input_mode_##vinput_mode))(n,__VA_ARGS__)
#define _hwa_cfad10a_xinput_mode_0(n,...)				\
  HW_G2(_hwa_cfad10a_xinput, HW_IS(input,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xinput_1(n,...)		\
  _hwa_cfad10a_im1(n,__VA_ARGS__)
#define _hwa_cfad10a_xinput_0(n,...)					\
  HW_G2(_hwa_cfad10a_xpositive_input, HW_IS(positive_input,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_xpositive_input_1(n,...)	\
  _hwa_cfad10a_im2(n,__VA_ARGS__)
#define _hwa_cfad10a_xpositive_input_0(n,...)				\
  HW_ERR("optionnal parameter `input_mode` must be specified as `single_end` or " \
	 "`differential`, or parameter `input` or `positive_input` must follow. " \
	 "Parameter `"HW_QUOTE(__VA_ARGS__)"` is not expected here.")

/*	Process 'input' in single-end mode
 */
#define _hwa_cfad10a_im1(n,...)						\
    HW_G2(_hwa_cfad10a_im1_xinput, HW_IS(input,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im1_xinput_0(n,...)				\
    HW_ERR("expected `input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_im1_xinput_1(n,input,...)				\
      HW_G2(_hwa_cfad10a_im1_vinput, HW_IS(,hw_ad10a_input_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im1_vinput_0(n,x,...)		\
  HW_ERR("`"#x"` is not a valid value for `input`.")
#define _hwa_cfad10a_im1_vinput_1(n,vinput,...)				\
  HW_TX(_hwa_write_reg(n,mux, HW_A1(hw_ad10a_input_##vinput)),__VA_ARGS__)

/*	Process 'positive_input' & 'negative_input' in differential mode
 */
#define _hwa_cfad10a_im2(n,...)						\
  HW_G2(_hwa_cfad10a_im2_xpositive_input, HW_IS(positive_input,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im2_xpositive_input_0(n,...)			\
  HW_ERR("expected `positive_input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_im2_xpositive_input_1(n,input,...)			\
  HW_G2(_hwa_cfad10a_im2_vpositive_input, HW_IS(,hw_ad10a_input_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im2_vpositive_input_0(n,x,...)		\
  HW_ERR("`"#x"` is not a valid value for `positive_input`.")
#define _hwa_cfad10a_im2_vpositive_input_1(n,vinput,...)		\
  uint8_t positive_input = HW_A1(hw_ad10a_input_##vinput);		\
  HW_G2(_hwa_cfad10a_im2_xnegative_input, HW_IS(negative_input,__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im2_xnegative_input_0(n,...)			\
  HW_ERR("expected `negative_input` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_im2_xnegative_input_1(n,input,...)			\
  HW_G2(_hwa_cfad10a_im2_vnegative_input, HW_IS(,hw_ad10a_input_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_im2_vnegative_input_0(n,x,...)		\
  HW_ERR("`"#x"` is not a valid value for `negative_input`.")
#define _hwa_cfad10a_im2_vnegative_input_1(n,vinput,...)		\
  uint8_t negative_input = HW_A1(hw_ad10a_input_##vinput);		\
  HW_TX(_hwa_write_reg(n,mux,						\
		       _hwa_ad10a_compute_mux( positive_input, negative_input, gain )), \
	__VA_ARGS__);


/*	Check the combination of differential inputs & gain, return the MUX
 *	value.
 */
HW_INLINE uint8_t _hwa_ad10a_compute_mux ( uint8_t pos, uint8_t neg, uint8_t gain )
{
  if ( pos==0 ) {
    if ( neg==0 ) {
      if ( gain != 20 )
	HWA_ERR("parameter `gain` must be set to 20 when pin_adc0 is used for both inputs.");
      else
	return 0x23 ;
    }
    else if ( neg==1 )
      return 0x08 + (gain==20);
    else if ( neg==3 )
      return 0x0A + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0`, `pin_adc1`, or `pin_adc3`.");
  }
  else if ( pos==1 ) {
    if ( neg==0 )
      return 0x28 + (gain==20);
    else if ( neg==2 )
      return 0x0C + (gain==20);
    else if ( neg==3 )
      return 0x0E + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc0`, `pin_adc2`, or `pin_adc3`.");
  }
  else if ( pos==2 ) {
    if ( neg==1 )
      return 0x2C + (gain==20);
    else if ( neg==3 )
      return 0x10 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc1` or `pin_adc3`.");
  }
  else if ( pos==3 ) {
    const uint8_t v[8] = { 0x2A, 0x2E, 0x30, 0x24, 0x12, 0x14, 0x16, 0x18 };
    return v[neg] + (gain==20);
  }
  else if ( pos==4 ) {
    if ( neg==3 )
      return 0x32 + (gain==20);
    else if ( neg==5 )
      return 0x1A + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3` or `pin_adc5`.");
  }
  else if ( pos==5 ) {
    if ( neg==3 )
      return 0x34 + (gain==20);
    else if ( neg==4 )
      return 0x3A + (gain==20);
    else if ( neg==6 )
      return 0x1C + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc4`, or `pin_adc6`.");
  }
  else if ( pos==6 ) {
    if ( neg==3 )
      return 0x36 + (gain==20);
    else if ( neg==5 )
      return 0x3C + (gain==20);
    else if ( neg==7 )
      return 0x1E + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc5`, or `pin_adc7`.");
  }
  else if ( pos==7 ) {
    if ( neg==3 )
      return 0x38 + (gain==20);
    else if ( neg==6 )
      return 0x3E + (gain==20);
    else if ( neg==7 )
      return 0x16 + (gain==20);
    HWA_ERR("`negative_input` must be `pin_adc3`, `pin_adc6`, or `pin_adc7`.");
  }
  else
    HWA_ERR("`positive_input` must be between 0 and 7.");
  return 0;
}


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_turn Turning the ADC on / off
 *
 * @code
 * hw/hwa_turn( ADC, on | off );
 * @endcode
 */
#define _hw_mthd_hw_turn__ad10a		, _hw_turn_ad10a

#define _hw_turn_ad10a(p,i,a, v, ...)			\
  HW_G2(_hw_turn_ad10a, HW_IS(,hw_state_##v))(p,i,a,v,__VA_ARGS__)
#define _hw_turn_ad10a_0(p,i,a, v, ...)			\
  HW_ERR("expected `on` or `off`, not `" #v "`.")
#define _hw_turn_ad10a_1(p,i,a, v, ...)					\
  HW_TX(_hw_write_reg(p, en, HW_A1(hw_state_##v)),__VA_ARGS__)


#define _hw_mthd_hwa_turn__ad10a	, _hwa_turn_ad10a

#define _hwa_turn_ad10a(p,i,a, ...)					\
  HW_G2(_hwa_turn_ad10a, HW_IS(,hw_state_##__VA_ARGS__))(p,i,a,__VA_ARGS__,)
#define _hwa_turn_ad10a_0(p,i,a, v, ...)			\
  HW_ERR("expected `on` or `off`, got `" #v "` instead.")
#define _hwa_turn_ad10a_1(p,i,a, v, ...)	\
  HW_TX(_hwa_write_reg(p, en, HW_A1(hw_state_##v)),__VA_ARGS__)


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_read Reading the result of conversion
 *
 * @code
 * uint16_t adc = hw_read( ADC );
 * @endcode
 */
#define _hw_mthd_hw_read__ad10a		, _hw_read_ad10a
#define _hw_read_ad10a(p,i,a,_)		_hw_read_reg(p, adc)

#define _hw_mthd_hw_atomic_read__ad10a	, _hw_atoread_ad10a
#define _hw_atoread_ad10a(p,i,a,_)	_hw_atomic_read_reg(p, adc)


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_trigger Starting a conversion
 *
 * @code
 * hw/hwa_trigger( ADC );
 * @endcode
 */
#define _hw_mthd_hw_trigger__ad10a	, _hw_trigger_ad10a
#define _hw_trigger_ad10a(p,i,a,_)	_hw_write_reg( p, sc, 1 )

#define _hw_mthd_hwa_trigger__ad10a	, _hwa_trigger_ad10a
#define _hwa_trigger_ad10a(p,i,a,_)	_hwa_write_reg( p, sc, 1 )


/**
 * @page atmelavr_ad10a
 * @section atmelavr_ad10a_stat Getting the status of the converter
 *
 * Available flags are:
 * * `irq`: the IRQ flag
 * * `busy`: a conversion is in progress
 *
 * @code
 * hw_stat_t(ADC) st ;
 * st = hw_stat( ADC );
 * if ( st.irq ) {
 *   hw_clear_irq( ADC );
 *   adc = hw_read( ADC );
 * }
 * @endcode
 */
typedef union {
  uint8_t         byte ;
  struct {
    unsigned int  __0_3 : 4 ;
    unsigned int  irq   : 1 ;
    unsigned int  __5   : 1 ;
    unsigned int  busy  : 1 ;
    unsigned int  __7   : 1 ;
  };
} _hw_ad10a_status_t ;

#define _hw_mthd_hw_stat__ad10a		, _hw_stat_ad10a
#define _hw_stat_ad10a(p,i,a,...)	HW_TX(_hw_ad10a_status(_hw_read_reg(p,sra)), \
					      __VA_ARGS__)

HW_INLINE _hw_ad10a_status_t _hw_ad10a_status( uint8_t byte )
{
  _hw_ad10a_status_t	st ;
  st.byte = byte ;
  return st ;
}


/**
 * @page atmelavr_ad10a
 * <br>
 */
