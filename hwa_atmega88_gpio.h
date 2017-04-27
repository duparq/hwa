#ifndef HWA_GPIO_H
#define HWA_GPIO_H

#include "hwa_gpio.h"

/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/

#define hw_gpio_config_pin(pinname, mode)	\
  do {						\
    hwa_gpio_begin(UNKNOWN);			\
    hwa_gpio_config_pin(pinname, mode) ;	\
    hwa_gpio_commit();				\
  } while(0)

#define hw_gpio_write_pin(pinname, value)				\
  hw_gpio_write_pins(HWA_PORTNAME(pinname), 1<<HWA_PINNUM(pinname),	\
		     (value)<<HWA_PINNUM(pinname))

#define hw_gpio_write_pins(pname, mask, value)				\
  HWA_HREG(pname, PORT) = (HWA_HREG(pname, PIN) & (u8)~(mask)) | ((value) & (mask)) ;

#define hw_gpio_toggle_pin(pinname)					\
  hw_gpio_toggle_pins(HWA_PORTNAME(pinname), 1<<HWA_PINNUM(pinname))

#define hw_gpio_toggle_pins(portname, mask)				\
  HWA_HREG(pname, PORT) = (HWA_HREG(pname, PIN) ^ ((value) & (mask)) ;


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_gpio_config_pin(pinname, mode)				\
  _hwa_gpio_config_pin(HWA_PORTNAME(pinname), HWA_PINNUM(pinname), HWA_GPIO_MODE_##mode)

#define _hwa_gpio_config_pin(pname, bit, mmode)		\
  do {							\
    HWA_VSET(u8, pname, DDR, 0b1, bit, mmode>>1);	\
    if ( mmode >> 1 == 0 )				\
      HWA_VSET(u8, pname, PORT, 0b1, bit, mmode & 1);	\
  } while(0)

#define hwa_gpio_config_port(pname, mode)			\
  do {								\
    HWA_VSET(u8, pname, DDR, 0xFF, 0, (mmode>>1)*0xFF);		\
    if ( mmode >> 1 == 0 )					\
      HWA_VSET(u8, pname, PORT, 0xFF, 0, (mmode & 1)*0xFF);	\
  } while(0)

#define hwa_gpio_write_pin(pinname, value)				\
  hwa_gpio_write_pins(HWA_PORTNAME(pinname), 1<<HWA_PINNUM(pinname), (value)<<HWA_PINNUM(pinname))
  

/*	mode[1:0] = DDRx:PORTx
 */
#define HWA_GPIO_MODE_INPUT_FLOATING	0b00	/* DDRx=0, PORTx=0 */
#define HWA_GPIO_MODE_INPUT		0b00	/* DDRx=0, PORTx=0 */
#define HWA_GPIO_MODE_INPUT_PULLUP	0b01	/* DDRx=0, PORTx=1 */
#define HWA_GPIO_MODE_OUTPUT		0b10	/* DDRx=1, PORTx unchanged */


/********************************************************************************
 *										*
 *				Internal definitions				*
 *										*
 ********************************************************************************/

#define HWA_PORTB			0x23
#define HWA_PORTC			0x26
#define HWA_PORTD			0x29

#define HWA_PORTB_PIN		((volatile u8 *)(HWA_PORTB+0x00)) /* 0x23 */
#define HWA_PORTB_DDR		((volatile u8 *)(HWA_PORTB+0x01)) /* 0x24 */
#define HWA_PORTB_PORT		((volatile u8 *)(HWA_PORTB+0x02)) /* 0x25 */

#define HWA_PORTC_PIN		((volatile u8 *)(HWA_PORTC+0x00)) /* 0x26 */
#define HWA_PORTC_DDR		((volatile u8 *)(HWA_PORTC+0x01)) /* 0x27 */
#define HWA_PORTC_PORT		((volatile u8 *)(HWA_PORTC+0x02)) /* 0x28 */

#define HWA_PORTD_PIN		((volatile u8 *)(HWA_PORTD+0x00)) /* 0x29 */
#define HWA_PORTD_DDR		((volatile u8 *)(HWA_PORTD+0x01)) /* 0x2A */
#define HWA_PORTD_PORT		((volatile u8 *)(HWA_PORTD+0x02)) /* 0x2B */

/*	Register declaration: type, port_name, reg_name, reset value, write mask
 */
#define hwa_gpio_begin(state)			\
  HWA_VDCL(u8, PORTB, DDR,  0, 0xFF, state);	\
  HWA_VDCL(u8, PORTB, PORT, 0, 0xFF, state);	\
  HWA_VDCL(u8, PORTC, DDR,  0, 0x7F, state);	\
  HWA_VDCL(u8, PORTC, PORT, 0, 0x7F, state);	\
  HWA_VDCL(u8, PORTD, DDR,  0, 0xFF, state);	\
  HWA_VDCL(u8, PORTD, PORT, 0, 0xFF, state);


#define hwa_gpio_commit()			\
  do {						\
    HWA_COMMIT(u8, PORTB, DDR);			\
    HWA_COMMIT(u8, PORTB, PORT);		\
    HWA_COMMIT(u8, PORTC, DDR);			\
    HWA_COMMIT(u8, PORTC, PORT);		\
    HWA_COMMIT(u8, PORTD, DDR);			\
    HWA_COMMIT(u8, PORTD, PORT);		\
  } while(0)

#endif
