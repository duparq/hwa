
/* This file is part of the HWA project.
 * Copyright (c) Christophe Duparquet <duparq at free dot fr>
 * All rights reserved. Read LICENSE.TXT for details.
 */


/*	Symbols
 */
#define hw_is_trigger_trigger			, 1
#define hw_is_vref_vref				, 1
#define hw_is_align_align			, 1
#define hw_is_polarity_polarity			, 1
#define hw_is_input_mode_input_mode		, 1
#define hw_is_input_input			, 1
#define hw_is_gain_gain				, 1
#define hw_is_positive_input_positive_input	, 1
#define hw_is_negative_input_negative_input	, 1

#define hw_ad10a_clock_syshz_div_2		, 1	/* , ps */
#define hw_ad10a_clock_syshz_div_4		, 2
#define hw_ad10a_clock_syshz_div_8		, 3
#define hw_ad10a_clock_syshz_div_16		, 4
#define hw_ad10a_clock_syshz_div_32		, 5
#define hw_ad10a_clock_syshz_div_64		, 6
#define hw_ad10a_clock_syshz_div_128		, 7

#define hw_ad10a_trigger_manual			, 0, 0	/* , ate, ts */
#define hw_ad10a_trigger_auto			, 1, 0
#define hw_ad10a_trigger_acmp0			, 1, 1
#define hw_ad10a_trigger_int0			, 1, 2
#define hw_ad10a_trigger_counter0_compare_a	, 1, 3
#define hw_ad10a_trigger_counter0_overflow	, 1, 4
#define hw_ad10a_trigger_counter1_compare_b	, 1, 5
#define hw_ad10a_trigger_counter1_overflow	, 1, 6
#define hw_ad10a_trigger_counter1_capture	, 1, 7

#define hw_ad10a_vref_vcc			, 0	/* , refs */
#define hw_ad10a_vref_pin_aref			, 1
#define hw_ad10a_vref_bandgap			, 2

#define hw_ad10a_align_left			, 1	/* , lar */
#define hw_ad10a_align_right			, 0

#define hw_ad10a_input_mode_single_end		, im1	/* drive the parser */
#define hw_ad10a_input_mode_differential	, im2

#define hw_ad10a_input_pin_adc0			, 0
#define hw_ad10a_input_pin_adc1			, 1
#define hw_ad10a_input_pin_adc2			, 2
#define hw_ad10a_input_pin_adc3			, 3
#define hw_ad10a_input_pin_adc4			, 4
#define hw_ad10a_input_pin_adc5			, 5
#define hw_ad10a_input_pin_adc6			, 6
#define hw_ad10a_input_pin_adc7			, 7


/*	Read the ADC
 */
#define hw_def_hw_read_ad10a		, _hw_read_ad10a
#define _hw_read_ad10a(c,n,i,a)		_hw_read_reg(c,n,i,a, adc)


/*	Trigger the ADC
 */
#define hw_def_hw_trigger_ad10a		, _hw_trigger_ad10a
#define _hw_trigger_ad10a(c,n,i,a)	_hw_write_reg(c,n,i,a, sc, 1 )

#define hw_def_hwa_trigger_ad10a	, _hwa_trigger_ad10a
#define _hwa_trigger_ad10a(c,n,i,a)	_hwa_write_r8( &hwa->n.sra, 1, 6, 1 );
//#define _hwa_trigger_ad10a(c,n,i,a)	_hwa_write_reg(c,n,i,a, sc, 1 )


/*	Configure the ADC
 */
#define hw_def_hwa_config_ad10a		, _hwa_cfad10a
#define _hwa_cfad10a(c,n,i,a,...)					\
  do {									\
    uint8_t gain __attribute__((unused)) = 1 ;				\
    _hwa_write_reg(ad10a,n,,,en,1);					\
    HW_G2(_hwa_cfad10a_xclock, HW_IS(clock,__VA_ARGS__))(n,__VA_ARGS__,) \
      } while(0)
#define _hwa_cfad10a_xclock_0(n,...)					\
  HW_ERR("expected `clock` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xclock_1(n,clock,...)				\
  HW_G2(_hwa_cfad10a_vclock, HW_IS(,hw_ad10a_clock_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vclock_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `clock`.")
#define _hwa_cfad10a_vclock_1(n,vclock,...)				\
  _hwa_write_reg(ad10a,n,,,ps, HW_A1(hw_ad10a_clock_##vclock));	\
  HW_G2(_hwa_cfad10a_xtrigger, HW_IS(trigger,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfad10a_xtrigger_0(n,...)					\
  HW_ERR("expected `trigger` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xtrigger_1(n,trigger,...)				\
  HW_G2(_hwa_cfad10a_vtrigger, HW_IS(,hw_ad10a_trigger_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vtrigger_0(n,x,...)		\
  HW_ERR("`"#x"` is not a valid value for `trigger`.")
#define _hwa_cfad10a_vtrigger_1(n,vtrigger,...)				\
  _hwa_write_reg(ad10a,n,,,ate, HW_A1(hw_ad10a_trigger_##vtrigger));	\
  _hwa_write_reg(ad10a,n,,,ts, HW_A2(hw_ad10a_trigger_##vtrigger));	\
  HW_G2(_hwa_cfad10a_xvref, HW_IS(vref,__VA_ARGS__))(n,__VA_ARGS__)

#define _hwa_cfad10a_xvref_0(n,...)					\
  HW_ERR("expected `vref` instead of `" HW_QUOTE(__VA_ARGS__) "`.")
#define _hwa_cfad10a_xvref_1(n,vref,...)				\
  HW_G2(_hwa_cfad10a_vvref, HW_IS(,hw_ad10a_vref_##__VA_ARGS__))(n,__VA_ARGS__)
#define _hwa_cfad10a_vvref_0(n,x,...)			\
  HW_ERR("`"#x"` is not a valid value for `vref`.")
#define _hwa_cfad10a_vvref_1(n,vvref,...)				\
  _hwa_write_reg(ad10a,n,,,refs, HW_A1(hw_ad10a_vref_##vvref));	\
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
    _hwa_write_reg(ad10a,n,,,lar, HW_A1(hw_ad10a_align_##valign));	\
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
  _hwa_write_reg(ad10a,n,,,lar, HW_A1(hw_ad10a_polarity_##vpolarity));	\
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
  _hwa_write_reg(ad10a,n,,,mux, HW_A1(hw_ad10a_input_##vinput));	\
  HW_EOP(__VA_ARGS__)

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
  _hwa_write_reg(ad10a,n,,,mux,					\
		    _hwa_ad10a_compute_mux( positive_input, negative_input, gain )); \
  HW_EOP(__VA_ARGS__)


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


/*	Class & methods
 */
#define hw_class_adpin

#define hw_def_hwa_config_adpin		, _hwa_config_adpin
#define _hwa_config_adpin(c,n,i,bp, mode)		\
  HW_G2(_hwa_config_adpin, HW_IS(input,mode))(n,bp)
#define _hwa_config_adpin_0(n,...)			\
  HW_ERR("`"#n"` can only be configured as `input`")
#define _hwa_config_adpin_1(n,bp)			\
  do {							\
    _hwa_write_r8( &hwa->porta.port, 1, bp, 0 );	\
    _hwa_write_r8( &hwa->porta.ddr, 1, bp, 0 );		\
    _hwa_write_r8( &hwa->adc0.did, 1, bp, 1 );		\
  } while(0)
