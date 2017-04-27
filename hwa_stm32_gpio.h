#ifndef HWA_GPIO_H
#define HWA_GPIO_H

#define HW_SPLITPORT_SPI1_MOSI		PORTA, 7
#define HW_SPLITPORT_SPI1_MISO		PORTA, 6
#define HW_SPLITPORT_SPI1_SCK		PORTA, 5

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_gpio_read(portname)			\
  *HWA_PTR_##portname##_IDR

#define hw_gpio_set_pin(pinname, value)					\
  hw_gpio_set_pins(HW_PORTNAME(pinname), 1<<HW_PINNUM(pinname), (value)<<HW_PINNUM(pinname))

#define hwac_gpio_set_pin(pinname, value)				\
  hw_gpio_set_pins(HW_PORTNAME(pinname), 1<<HW_PINNUM(pinname), (value)<<HW_PINNUM(pinname))

#define hw_gpio_set_pins(portname, mask, value)	\
  _hw_gpio_set_pins(portname, mask, value)

#define hw_gpio_toggle_pin(pinname)					\
  hw_gpio_toggle_pins(HW_PORTNAME(pinname), 1<<HW_PINNUM(pinname))

#define hw_gpio_toggle_pins(portname, mask)	\
  _hw_gpio_toggle_pins(portname, mask)		\


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_gpio_config_pin(pinname, mode)				\
  hwa_gpio_config_pins(HW_PORTNAME(pinname), 1<<HW_PINNUM(pinname), mode)

#define hwa_gpio_config_pins(portname, mask, mode)		\
  _hwa_gpio_config_pins(portname, mask, HWA_GPIO_MODE_##mode);

#define hwa_gpio_config_port(portname, mode)	\
  hwa_gpio_config_pins(portname, 0xffff, mode)

#define hwa_gpio_set_pin(pinname, value)				\
  _hwa_gpio_set_pins(HW_PORTNAME(pinname), 1<<HW_PINNUM(pinname), (value)<<HW_PINNUM(pinname))

/*	mode[4:3] = CNF[1:0],
 *	mode[2:1] = MODE[1:0],
 *	mode[0] = ODR when CNF[1:0]==0b10 (input with pullup/pulldown)
 */
#define HWA_GPIO_MODE_INPUT_ANALOG				0b00000
#define HWA_GPIO_MODE_INPUT_FLOATING				0b01000
#define HWA_GPIO_MODE_INPUT_PULLDOWN				0b10000
#define HWA_GPIO_MODE_INPUT_PULLUP				0b10001
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_10MHZ			0b00010
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_2MHZ			0b00100
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_50MHZ			0b00110
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_10MHZ			0b01010
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_2MHZ			0b01100
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_50MHZ			0b01110
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_10MHZ			0b10010
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_2MHZ			0b10100
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_50MHZ			0b10110
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_10MHZ			0b11010
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_2MHZ			0b11100
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_50MHZ			0b11110


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

/* #define _HW_PORTNAME(iopin)		HW_PORTNAME_##iopin */
/* #define _HW_PINNUM(iopin)		HW_PINNUM_##iopin */

#define HWA_PTR_PORTA			HWA_PTR_APB2+0x0800 /* 0x40010800 */
#define HWA_PTR_PORTB			HWA_PTR_APB2+0x0c00 /* 0x40010c00 */
#define HWA_PTR_PORTC			HWA_PTR_APB2+0x1000 /* 0x40011000 */
#define HWA_PTR_PORTD			HWA_PTR_APB2+0x1400 /* 0x40014000 */
#define HWA_PTR_PORTE			HWA_PTR_APB2+0x1800 /* 0x40011800 */
#define HWA_PTR_PORTF			HWA_PTR_APB2+0x1c00 /* 0x40011c00 */
#define HWA_PTR_PORTG			HWA_PTR_APB2+0x2000 /* 0x40012000 */

#define HWA_PTR_PORTA_CRL		((volatile u32 *)(HWA_PTR_PORTA+0x00))
#define HWA_PTR_PORTA_CRH		((volatile u32 *)(HWA_PTR_PORTA+0x04))
#define HWA_PTR_PORTA_IDR		((volatile u32 *)(HWA_PTR_PORTA+0x08))
#define HWA_PTR_PORTA_ODR		((volatile u32 *)(HWA_PTR_PORTA+0x0C))
#define HWA_PTR_PORTA_BSRR		((volatile u32 *)(HWA_PTR_PORTA+0x10))
#define HWA_PTR_PORTA_BRR		((volatile u32 *)(HWA_PTR_PORTA+0x14))
#define HWA_PTR_PORTA_LCKR		((volatile u32 *)(HWA_PTR_PORTA+0x18))

#define HWA_PTR_PORTB_CRL		((volatile u32 *)(HWA_PTR_PORTB+0x00))
#define HWA_PTR_PORTB_CRH		((volatile u32 *)(HWA_PTR_PORTB+0x04))
#define HWA_PTR_PORTB_IDR		((volatile u32 *)(HWA_PTR_PORTB+0x08))
#define HWA_PTR_PORTB_ODR		((volatile u32 *)(HWA_PTR_PORTB+0x0C))
#define HWA_PTR_PORTB_BSRR		((volatile u32 *)(HWA_PTR_PORTB+0x10))
#define HWA_PTR_PORTB_BRR		((volatile u32 *)(HWA_PTR_PORTB+0x14))
#define HWA_PTR_PORTB_LCKR		((volatile u32 *)(HWA_PTR_PORTB+0x18))

#define HWA_PTR_PORTC_CRL		((volatile u32 *)(HWA_PTR_PORTC+0x00))
#define HWA_PTR_PORTC_CRH		((volatile u32 *)(HWA_PTR_PORTC+0x04))
#define HWA_PTR_PORTC_IDR		((volatile u32 *)(HWA_PTR_PORTC+0x08))
#define HWA_PTR_PORTC_ODR		((volatile u32 *)(HWA_PTR_PORTC+0x0C))
#define HWA_PTR_PORTC_BSRR		((volatile u32 *)(HWA_PTR_PORTC+0x10))
#define HWA_PTR_PORTC_BRR		((volatile u32 *)(HWA_PTR_PORTC+0x14))
#define HWA_PTR_PORTC_LCKR		((volatile u32 *)(HWA_PTR_PORTC+0x18))

#define HWA_PTR_PORTD_CRL		((volatile u32 *)(HWA_PTR_PORTD+0x00))
#define HWA_PTR_PORTD_CRH		((volatile u32 *)(HWA_PTR_PORTD+0x04))
#define HWA_PTR_PORTD_IDR		((volatile u32 *)(HWA_PTR_PORTD+0x08))
#define HWA_PTR_PORTD_ODR		((volatile u32 *)(HWA_PTR_PORTD+0x0C))
#define HWA_PTR_PORTD_BSRR		((volatile u32 *)(HWA_PTR_PORTD+0x10))
#define HWA_PTR_PORTD_BRR		((volatile u32 *)(HWA_PTR_PORTD+0x14))
#define HWA_PTR_PORTD_LCKR		((volatile u32 *)(HWA_PTR_PORTD+0x18))

#define HWA_PTR_PORTE_CRL		((volatile u32 *)(HWA_PTR_PORTE+0x00))
#define HWA_PTR_PORTE_CRH		((volatile u32 *)(HWA_PTR_PORTE+0x04))
#define HWA_PTR_PORTE_IDR		((volatile u32 *)(HWA_PTR_PORTE+0x08))
#define HWA_PTR_PORTE_ODR		((volatile u32 *)(HWA_PTR_PORTE+0x0C))
#define HWA_PTR_PORTE_BSRR		((volatile u32 *)(HWA_PTR_PORTE+0x10))
#define HWA_PTR_PORTE_BRR		((volatile u32 *)(HWA_PTR_PORTE+0x14))
#define HWA_PTR_PORTE_LCKR		((volatile u32 *)(HWA_PTR_PORTE+0x18))

/*	Register declaration: name, type, address, reset value, write mask
 */
#define hwa_gpio_begin_port(pname, state)				\
  HWA_DECL(pname##_CRL,  u32, HWA_PTR_##pname+0x00, 0x44444444, 0xFFFFFFFF, state); \
  HWA_DECL(pname##_CRH,  u32, HWA_PTR_##pname+0x04, 0x44444444, 0xFFFFFFFF, state); \
  HWA_DECL(pname##_ODR,  u32, HWA_PTR_##pname+0x0C, 0x00000000, 0x0000FFFF, state);

#define hwa_gpio_begin(state)			\
  hwa_gpio_begin_port(PORTA, state);		\
  hwa_gpio_begin_port(PORTB, state);		\
  hwa_gpio_begin_port(PORTC, state);		\
  hwa_gpio_begin_port(PORTD, state);		\
  hwa_gpio_begin_port(PORTE, state);

#define hwa_gpio_commit_port(pname)		\
  HWA_COMMIT(pname##_CRL);			\
  HWA_COMMIT(pname##_CRH);			\
  HWA_COMMIT(pname##_ODR);

#define hwa_gpio_commit()			\
  hwa_gpio_commit_port(PORTA);			\
  hwa_gpio_commit_port(PORTB);			\
  hwa_gpio_commit_port(PORTC);			\
  hwa_gpio_commit_port(PORTD);			\
  hwa_gpio_commit_port(PORTE);


#define _hwa_gpio_config_bit(bitnum, portname, mask, mmode)		\
  if ( mask & (1<<bitnum) ) {						\
    if ( bitnum < 8 ) {							\
      HWA_SET(portname##_CRL, 0b1111, 4*(bitnum&0x07), mmode>>1);	\
    } else {								\
      HWA_SET(portname##_CRH, 0b1111, 4*(bitnum&0x07), mmode>>1);	\
    }									\
    if ( mmode == HWA_GPIO_MODE_INPUT_PULLDOWN				\
	 || mmode == HWA_GPIO_MODE_INPUT_PULLUP) {			\
      HWA_SET(portname##_ODR, 0b1, bitnum, mmode&1);			\
    }									\
  }

/*	It seems GCC can not optimize code when a loop is used.
 */
#define _hwa_gpio_config_pins(portname, mask, mmode)	\
  _hwa_gpio_config_bit( 0, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 1, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 2, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 3, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 4, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 5, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 6, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 7, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 8, portname, mask, mmode)	\
  _hwa_gpio_config_bit( 9, portname, mask, mmode)	\
  _hwa_gpio_config_bit(10, portname, mask, mmode)	\
  _hwa_gpio_config_bit(11, portname, mask, mmode)	\
  _hwa_gpio_config_bit(12, portname, mask, mmode)	\
  _hwa_gpio_config_bit(13, portname, mask, mmode)	\
  _hwa_gpio_config_bit(14, portname, mask, mmode)	\
  _hwa_gpio_config_bit(15, portname, mask, mmode)

/*	Set state of portlines.
 *	For each bit set to 1 in the upper word of BSSR
 *	the corresponding port line is set:
 *		* to 1 if the corresponding bit of the lower word of BSSR is 1;
 *		* to 0 otherwise.
 *	For each bit set to 0 in the upper word of BSSR
 *	the corresponding port line is set to 1 if the corresponding bit of the
 *	lower word of BSSR is 1.
 */
#define _hw_gpio_set_pins(portname, mask, value)			\
  *HWA_PTR_##portname##_BSRR = ((mask)<<16) | ((value) & (mask))

#define _hw_gpio_toggle_pins(portname, mask)				\
  _hw_gpio_set_pins(portname, mask, ~(*HWA_PTR_##portname##_IDR))

#endif
