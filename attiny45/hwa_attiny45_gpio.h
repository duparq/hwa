#ifndef HWA_ATTINY45_GPIO_H
#define HWA_ATTINY45_GPIO_H

#include "hwa_gpio.h"


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_PORTB_BASE			0x36

#define HWA_GPIO_HWA_PIN		volatile, u8, 0x00, 0x00, 0x3F
#define HWA_GPIO_HWA_DDR		volatile, u8, 0x01, 0x00, 0x3F
#define HWA_GPIO_HWA_PORT		volatile, u8, 0x02, 0x00, 0x3F

/*	Parameters
 */
#define HWA_GPIO_MODE_INPUT_FLOATING	0b000	/* DDRx=0, PORTx=0 */
#define HWA_GPIO_MODE_INPUT		0b000	/* DDRx=0, PORTx=0 */
#define HWA_GPIO_MODE_INPUT_PULLUP	0b001	/* DDRx=0, PORTx=1 */
#define HWA_GPIO_MODE_OUTPUT		0b010	/* DDRx=1, PORTx unchanged */
#define HWA_GPIO_MODE_INPUT_ANALOG	0b100	/* DIDRx=1, DDRx=0, PORTx=0 */


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_GPIO, HWA_DDR)
  HWA_VDCL(HWA_GPIO, HWA_PORT)
} HWA_GPIO ;


#define hwa_begin_gpio(reset)			\
  hwa_begin_gpio_port(HWA_PORTB, reset)


#define hwa_begin_gpio_port(pname, reset)	\
  HWA_PINIT(HWA_GPIO, pname)			\
  HWA_VINIT(HWA_GPIO, pname, HWA_DDR, reset);	\
  HWA_VINIT(HWA_GPIO, pname, HWA_PORT, reset);


#define hwa_commit_gpio()			\
  do {						\
    hwa_commit_gpio_port(HWA_PORTB);		\
  } while(0)


#define hwa_commit_gpio_port(p)				\
  do {							\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_DDR);	\
    HWA_COMMIT(HWA_CORE0, HWA_GPIO, p, HWA_PORT);	\
  } while(0)


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define hw_gpio_read_pin(pinname)					\
  ((hw_gpio_read_port(HWA_PORTNAME(pinname)) & 1<<HWA_PINNUM(pinname)) != 0)

#define hw_gpio_read_port(pname)		\
  HW_HR(HWA_GPIO, pname, HWA_PIN)

/* #define hw_gpio_write_pin(pinname, value)				\ */
/*   hw_gpio_write_pins(HWA_PORTNAME(pinname), 1<<HWA_PINNUM(pinname),	\ */
/* 		     (value)<<HWA_PINNUM(pinname)) */

#define hw_gpio_write_pin(pinname, value)				\
  HW_SETHB(HWA_GPIO, HWA_PORTNAME(pinname), HWA_PORT, 0b1, HWA_PINNUM(pinname), value)

#define hw_gpio_write_port(pname, value)	\
  hw_gpio_write_pins(pname, 0xFF, value)

#define hw_gpio_write_pins(pname, mask, value)				\
  do {									\
    if ( mask == 0xFF )							\
      HW_SETHR(HWA_GPIO, pname, HWA_PORT, value) ;			\
    else if ( mask != 0 )						\
      HW_SETHR(HWA_GPIO, pname, HWA_PORT,				\
	       (HW_HR(HWA_GPIO, pname, HWA_PORT) & ~(mask)) | ((value) & (mask))); \
  } while(0)

#define hw_gpio_toggle_pin(pinname)					\
  HW_SETHR(HWA_GPIO, HWA_PORTNAME(pinname), HWA_PIN, 1<<HWA_PINNUM(pinname))

#define hw_gpio_toggle_pins(pname, mask)				\
  HW_SETHR(HWA_GPIO, pname, HWA_PIN, mask)

/* #define hw_gpio_toggle_pins(pname, mask)				\ */
/*   HW_HR(HWA_GPIO, pname, HWA_PORT) = (HW_HR(HWA_GPIO, pname, HWA_PORT) ^ (mask)) */


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/

#define hwa_gpio_config_pin(pin, mode)					\
  hwa_gpio_config_pin_(HWA_PORTNAME(pin), HWA_PINNUM(pin), HWA_GPIO_MODE_##mode)

#define hwa_gpio_config_pin_(pptr, bit, mode)				\
  do {									\
    HWA_SETVB(HWA_GPIO, pptr, HWA_DDR, 0b1, bit, (mode&0b010)!=0);	\
    if ( (mode&0b110) == 0b000 )					\
      HWA_SETVB(HWA_GPIO, pptr, HWA_PORT, 0b1, bit, (mode&0b001)!=0);	\
  } while(0)

#define hwa_gpio_config_port(pptr, mode)	\
  hwa_gpio_config_pins(pptr, 0xFF, mode)

/*	It seems GCC can not optimize code when a loop is used.
 */
#define hwa_gpio_config_pins(pptr, mask, mode)			\
  hwa_gpio_config_pins__(pptr,  0, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  1, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  2, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  3, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  4, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  5, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  6, mask, HWA_GPIO_MODE_##mode)	\
  hwa_gpio_config_pins__(pptr,  7, mask, HWA_GPIO_MODE_##mode)

#define hwa_gpio_config_pins__(p, bitnum, mask, mode)			\
  if ( (mask) & (1<<(bitnum)) ) {					\
    HWA_SETVB(HWA_GPIO, p, HWA_DDR, 0b1, bitnum, (mode&0b010)!=0);	\
    if ( (mode&0b110) == 0b000 )					\
      HWA_SETVB(HWA_GPIO, p, HWA_PORT, 0b1, bitnum, (mode&0b010)!=0);	\
  }

#define hwa_gpio_write_pin(pinname, value)				\
  HWA_SETVB(HWA_GPIO, HWA_PORTNAME(pinname), HWA_PORT, 0b1, HWA_PINNUM(pinname), value)


#endif
