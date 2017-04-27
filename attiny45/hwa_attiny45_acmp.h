#ifndef HWA_ATTINY45_ACMP_H
#define HWA_ATTINY45_ACMP_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/


/********************************************************************************
 *										*
 *				Synchronous actions				*
 *										*
 ********************************************************************************/

#define HWA_ACMP_FLAG_IRQF		HWA_CORE_ACI
#define HWA_ACMP_FLAG_IRQE		HWA_CORE_ACIE

#define hw_acmp_clear_flag(pname, flag)					\
  HW_SETHB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_ACMP_FLAG, flag), 1)

#define hw_acmp_test_flag(pname, flag)				\
  (HW_TSTHB(HWA_CORE, HWA_CORE0, HWA_G2(HWA_ACMP_FLAG, flag)) != 0)

#define hw_acmp_turn_irq(pname, state)				\
  HW_SETHB(HWA_CORE, HWA_CORE0, HWA_CORE_ACIE, HWA_STATE(state))


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define HWA_ACMP0_BASE			0x20

#define HWA_BV_ACIS_CHANGE		0b00
#define HWA_BV_ACIS_FALL		0b10
#define HWA_BV_ACIS_RISE		0b11

#define HWA_ACMP_PIN_AIN0		PB0
#define HWA_ACMP_PIN_AIN1		PB1


/*	Convenient registers
 */
#define HWA_ACMP_HWA_CONNECT_NEG	, u8, -1, 0, 0xFF

#define HWA_ACMP_CONNECT_NEG_AIN1	0x01
#define HWA_ACMP_CONNECT_NEG_ADC0	0x10
#define HWA_ACMP_CONNECT_NEG_ADC1	0x11
#define HWA_ACMP_CONNECT_NEG_ADC2	0x12
#define HWA_ACMP_CONNECT_NEG_ADC3	0x13

#define HWA_ACMP_HWA_CONNECT_POS	, u8, -1, 0, 0xFF

#define HWA_ACMP_CONNECT_POS_AIN0	1
#define HWA_ACMP_CONNECT_POS_BANDGAP	2


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_ACMP, HWA_CONNECT_NEG)
  HWA_VDCL(HWA_ACMP, HWA_CONNECT_POS)
} HWA_ACMP ;


#define hwa_begin_acmp(reset)					\
  HWA_PINIT(HWA_ACMP, HWA_ACMP0);				\
  HWA_VINIT(HWA_ACMP, HWA_ACMP0, HWA_CONNECT_NEG, reset);	\
  HWA_VINIT(HWA_ACMP, HWA_ACMP0, HWA_CONNECT_POS, reset);	\

#define hwa_commit_acmp()\
  hwa_acmp_commit(HWA_CORE0, HWA_ACMP0)


/*  Only set virtual registers, based upon convenient registers
 *  'core' will set hardware registers at last
 */
inline void hwa_acmp_commit ( HWA_CORE *core, HWA_ACMP *p )
{
  if ( HWA_SR(p, HWA_CONNECT_NEG, mmask) ) {
    u8 con_neg = HWA_SR(p, HWA_CONNECT_NEG, mvalue);

    if ( con_neg & 0x10 ) /* Connect negative input to one of ADC0..ADC3 */
      HWA_SETVB(HWA_CORE, core, HWA_CORE_ACIS, con_neg & 0x03);
    else {
      /*  Connect negative input to AIN1
       *    set ACME=0, or ACME=1 && ADEN=1
       */
      u8 acme = HWA_GETVB(core, HWA_CORE_ACME, -1) ;
      if ( acme == 1 )
	HWA_SETVB(HWA_CORE, core, HWA_CORE_ADEN, 1);

      /*  Disable digital input buffer for AIN1
       */
      HWA_SETVB(HWA_CORE, core, HWA_CORE_AIN1D, 1);
    }
  }

  if ( HWA_SR(p, HWA_CONNECT_POS, mmask) ) {
    u8 con = HWA_SR(p, HWA_CONNECT_POS, mvalue);
    if ( con == HWA_ACMP_CONNECT_POS_AIN0 )
      HWA_SETVB(HWA_CORE, core, HWA_CORE_ACBG, 0);
    else
      HWA_SETVB(HWA_CORE, core, HWA_CORE_ACBG, 1);
  }

  HWA_COMMIT(core, HWA_ACMP, p, HWA_CONNECT_NEG);
  HWA_COMMIT(core, HWA_ACMP, p, HWA_CONNECT_POS);
}


#define hwa_acmp_connect(p, pin, source)	\
  HWA_G2(hwa_acmp_connect, pin)(source)

#define hwa_acmp_connect_NEGATIVE(source)				\
  HWA_SETVR(HWA_ACMP, HWA_ACMP0, HWA_CONNECT_NEG, HWA_G2(HWA_ACMP_CONNECT_NEG, source))

#define hwa_acmp_connect_POSITIVE(source)				\
  HWA_SETVR(HWA_ACMP, HWA_ACMP0, HWA_CONNECT_POS, HWA_G2(HWA_ACMP_CONNECT_POS, source))

#define hwa_acmp_config_pin(pin, mode)					\
  hwa_gpio_config_pin(HWA_G2(HWA_ACMP_PIN, pin), mode)

#define hwa_acmp_config_irq(p, mode)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_CORE_ACIS, HWA_G2(HWA_BV_ACIS, mode))

#define hwa_acmp_turn_irq(p, status)					\
  HWA_SETVB(HWA_CORE, HWA_CORE0, HWA_CORE_ACIE, HWA_STATE(status))


#endif
