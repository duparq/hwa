#ifndef HWA_STM32_GPIO_H
#define HWA_STM32_GPIO_H

#include "hwa_gpio.h"

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_PORTA_BASE		HWA_APB2+0x0800 /* 0x40010800 */
#define HWA_PORTB_BASE		HWA_APB2+0x0c00 /* 0x40010c00 */
#define HWA_PORTC_BASE		HWA_APB2+0x1000 /* 0x40011000 */
#define HWA_PORTD_BASE		HWA_APB2+0x1400 /* 0x40014000 */
#define HWA_PORTE_BASE		HWA_APB2+0x1800 /* 0x40011800 */
#define HWA_PORTF_BASE		HWA_APB2+0x1c00 /* 0x40011c00 */
#define HWA_PORTG_BASE		HWA_APB2+0x2000 /* 0x40012000 */

#define HWA_GPIO_HWA_CRL	volatile, u32, 0x00, 0x44444444, 0xFFFFFFFF
#define HWA_GPIO_HWA_CRH	volatile, u32, 0x04, 0x44444444, 0xFFFFFFFF
#define HWA_GPIO_HWA_IDR	volatile, u32, 0x08, 
#define HWA_GPIO_HWA_ODR	volatile, u32, 0x0C, 0x00000000, 0x0000FFFF
#define HWA_GPIO_HWA_BSRR	volatile, u32, 0x10, 0x00000000, 0xFFFFFFFF
#define HWA_GPIO_HWA_BRR	volatile, u32, 0x14, 
#define HWA_GPIO_HWA_LCKR	volatile, u32, 0x18, 


/*	mode[4:3] = CNF[1:0],
 *	mode[2:1] = MODE[1:0],
 *	mode[0] = ODR when CNF[1:0]==0b10 (input with pullup/pulldown)
 */
#define HWA_GPIO_MODE_INPUT_ANALOG				0b00000
#define HWA_GPIO_MODE_INPUT_FLOATING				0b01000
#define HWA_GPIO_MODE_INPUT					0b01000
#define HWA_GPIO_MODE_INPUT_PULLDOWN				0b10000
#define HWA_GPIO_MODE_INPUT_PULLUP				0b10001
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_10MHZ			0b00010
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_2MHZ			0b00100
#define HWA_GPIO_MODE_OUTPUT_PUSHPULL_50MHZ			0b00110
#define HWA_GPIO_MODE_OUTPUT					0b00110
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_10MHZ			0b01010
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_2MHZ			0b01100
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN_50MHZ			0b01110
#define HWA_GPIO_MODE_OUTPUT_OPENDRAIN				0b01110
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_10MHZ			0b10010
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_2MHZ			0b10100
#define HWA_GPIO_MODE_ALTOUTPUT_PUSHPULL_50MHZ			0b10110
#define HWA_GPIO_MODE_ALTOUTPUT					0b10110
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_10MHZ			0b11010
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_2MHZ			0b11100
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN_50MHZ			0b11110
#define HWA_GPIO_MODE_ALTOUTPUT_OPENDRAIN			0b11110

typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_GPIO, HWA_CRL);
  HWA_VDCL(HWA_GPIO, HWA_CRH);
  HWA_VDCL(HWA_GPIO, HWA_ODR);
  HWA_VDCL(HWA_GPIO, HWA_BSRR);
} HWA_GPIO ;

#define hwa_begin_gpio(reset)			\
  hwa_begin_gpio_port(HWA_PORTA, reset)		\
  hwa_begin_gpio_port(HWA_PORTB, reset)		\
  hwa_begin_gpio_port(HWA_PORTC, reset)		\
  hwa_begin_gpio_port(HWA_PORTD, reset)		\
  hwa_begin_gpio_port(HWA_PORTE, reset)		\
  hwa_begin_gpio_port(HWA_PORTF, reset)		\
  hwa_begin_gpio_port(HWA_PORTG, reset)

#define hwa_begin_gpio_port(pname, reset)				\
  HWA_PINIT(HWA_GPIO, pname);						\
  HWA_VINIT(HWA_GPIO, pname, HWA_CRL, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_CRH, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_ODR, reset);				\
  HWA_VINIT(HWA_GPIO, pname, HWA_BSRR, 1);	/* Never need to read BSRR */

#define hwa_commit_gpio()			\
  do {						\
    _hwa_commit_gpio_port(HWA_PORTA);	\
    _hwa_commit_gpio_port(HWA_PORTB);	\
    _hwa_commit_gpio_port(HWA_PORTC);	\
    _hwa_commit_gpio_port(HWA_PORTD);	\
    _hwa_commit_gpio_port(HWA_PORTE);	\
    _hwa_commit_gpio_port(HWA_PORTF);	\
    _hwa_commit_gpio_port(HWA_PORTG);	\
  } while(0)

/*	Committing BSRR, ODR, CRL, CRH in this order avoids glitches at RESET
*/
#define _hwa_commit_gpio_port(p)		\
  do {						\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_BSRR);	\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_ODR);	\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_CRL);	\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_CRH);	\
  } while(0)


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define rem_hw_gpio_config_pin(pin, mode)		\
  do {						\
    hwa_begin_gpio(0);				\
    hwa_gpio_config_pin(pin, mode) ;		\
    hwa_commit_gpio(0);				\
  } while(0)


#define hw_gpio_config_pin(pin, mode)					\
  hw_gpio_config_pin_(HWA_PORTNAME(pin), HWA_PINNUM(pin), HWA_GPIO_MODE_##mode)

#define hw_gpio_config_pin_(p, bitnum, mode)				\
  do {									\
    if ( bitnum < 8 )							\
      HW_SETHB(HWA_GPIO, p, HWA_CRL, 0b1111, 4*(bitnum&0x07), mode>>1);	\
    else								\
      HW_SETHB(HWA_GPIO, p, HWA_CRH, 0b1111, 4*(bitnum&0x07), mode>>1);	\
    if ( mode == HWA_GPIO_MODE_INPUT_PULLDOWN				\
	 || mode == HWA_GPIO_MODE_INPUT_PULLUP )			\
      HW_SETHB(HWA_GPIO, p, HWA_ODR, 0b1, bitnum, mode&1);		\
  } while(0)

#define hw_gpio_read_port(pname)		\
  HW_HR(HWA_GPIO, pname, HWA_IDR)

/* #define hw_gpio_read_pins(pname, mask, shift)				\ */
/*   ((HW_HR(HWA_GPIO, pname, HWA_IDR) & ((u16)(mask)<<(shift))) >> shift) */

/* #define hw_gpio_read_pin(pin)					\ */
/*   hw_gpio_read_pins(HWA_PORTNAME(pin), 0b1, HWA_PINNUM(pin)) */

#define hw_gpio_read_pin(pin)					\
  ((HW_HR(HWA_GPIO, HWA_PORTNAME(pin), HWA_IDR) & (1<<HWA_PINNUM(pin))) != 0)

/* #define hw_gpio_test_pins(pname, mask, shift)				\ */
/*   ((HW_HR(HWA_GPIO, pname, HWA_IDR) & ((u16)(mask)<<(shift))) != 0) */

/* #define hw_gpio_test_pin(pin)					\ */
/*   hw_gpio_test_pins(HWA_PORTNAME(pin), 0b1, HWA_PINNUM(pin)) */

#define hw_gpio_write_port(pname, value)	\
  HW_HR(HWA_GPIO, pname, HWA_ODR) = value

/*	Set state of portlines.
 *	For each bit set to 1 in the upper word of BSSR
 *	the corresponding port line is set:
 *		* to 1 if the corresponding bit of the lower word of BSSR is 1;
 *		* to 0 otherwise.
 *	For each bit set to 0 in the upper word of BSSR
 *	the corresponding port line is set to 1 if the corresponding bit of the
 *	lower word of BSSR is 1.
 */
#define hw_gpio_write_pins(pname, mask, value)				\
  HW_HR(HWA_GPIO, pname, HWA_BSRR) = ((u32)(mask)<<16) | ((u16)(value) & (mask))

#define hw_gpio_write_pin(pin, value)				\
  hw_gpio_write_pins(HWA_PORTNAME(pin), 1<<HWA_PINNUM(pin),	\
		     (value)<<HWA_PINNUM(pin))

#define hw_gpio_toggle_pin(pin)					\
  hw_gpio_toggle_pins(HWA_PORTNAME(pin), 1<<HWA_PINNUM(pin))

#define hw_gpio_toggle_pins(pname, mask)			\
  hw_gpio_write_pins(pname, mask, ~hw_gpio_read_port(pname))


/************************************************************************
 *									*
 *			Asynchronous actions				*
 *									*
 ************************************************************************/

#define hwa_gpio_config_pin(pin, mode)					\
  _hwa_gpio_config_pins(HWA_PORTNAME(pin), 1<<HWA_PINNUM(pin), mode)

#define hwa_gpio_config_pins(va...)		\
  _hwa_gpio_config_pins(va)

#define hwa_gpio_config_port(pname, mode)	\
  _hwa_gpio_config_pins(pname, 0xffff, mode)


#define _hwa_gpio_config_bit(p, bitnum, mask, mode)			\
  if ( (mask) & (1<<(bitnum)) ) {					\
    if ( bitnum < 8 )							\
      HWA_SETVB(HWA_GPIO, p, HWA_CRL, 0b1111, 4*(bitnum&0x07), mode>>1); \
    else								\
      HWA_SETVB(HWA_GPIO, p, HWA_CRH, 0b1111, 4*(bitnum&0x07), mode>>1); \
    if ( mode == HWA_GPIO_MODE_INPUT_PULLDOWN				\
	 || mode == HWA_GPIO_MODE_INPUT_PULLUP)				\
      HWA_SETVB(HWA_GPIO, p, HWA_ODR, 0b1, bitnum, mode&1);		\
  }

/*	It seems GCC can not optimize code when a loop is used.
 */
#define _hwa_gpio_config_pins(pname, mask, mode)			\
  do {									\
    hwa_prph_turn_clk(pname, ON);					\
    _hwa_gpio_config_bit(pname,  0, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  1, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  2, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  3, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  4, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  5, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  6, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  7, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  8, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname,  9, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 10, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 11, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 12, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 13, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 14, mask, HWA_GPIO_MODE_##mode);	\
    _hwa_gpio_config_bit(pname, 15, mask, HWA_GPIO_MODE_##mode);	\
  } while(0)

#define hwa_gpio_write_pin(pin, value)					\
  hwa_gpio_write_pins(HWA_PORTNAME(pin), 1<<HWA_PINNUM(pin), (value)<<HWA_PINNUM(pin))

#define hwa_gpio_write_pins(p, mask, value)		\
  HWA_SETVB(HWA_GPIO, p, HWA_BSRR,			\
	    ((u32)(mask)<<16) | (mask), 0,		\
	    ((u32)(mask)<<16) | ((mask) & (value)))

#endif
