
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Espressif's ESP8266
 */

#include "../hwa_1.h"

/**
 * @page esp8266 Espressif ESP8266
 */
#define hw_syshz				80000000


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section esp8266_peripherals Peripherals
 *
 * @note All the peripherals are not completely implemented yet.
 *
 * Object name		  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `hw_port0`	 | @ref espressif_p16a "_p16a"	  | General purpose I/O port
 * `hw_iomx0`	 | @ref espressif_iomxa "_iomxa"  | General purpose I/O port multiplexer
 * `hw_uart0`	 | @ref espressif_uarta "_uarta"  | UART
 *
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/
/**
 * @ingroup atmegax8_interrupts
 * @brief Definition of the interrupts
 */
/* #define _hw_irq_hw_int0			_irq,  1, hw_int0,     ie,  if */
/* #define _hw_irq_hw_int1			_irq,  2, hw_int1,     ie,  if */
/* #define _hw_irq_hw_pcic0		_irq,  3, hw_pcic0,    ie,  if */
/* #define _hw_irq_hw_pcic1		_irq,  4, hw_pcic1,    ie,  if */
/* #define _hw_irq_hw_pcic2		_irq,  5, hw_pcic2,    ie,  if */
/* #define _hw_irq_hw_wdog0		_irq,  6, hw_wdog0,    ie,  if */


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/


/*******************************************************************************
 *									       *
 *	GPIO multiplexer						       *
 *									       *
 *******************************************************************************/

#include "../classes/iomxa_1.h"

/*	Object				class, id, address
 */
#define _hw_iomux0			_iomxa, 0x60000800, 0x60000800

/*	Object hardware registers	class, address, write mask, flags mask
 *
 *	According to eagle_soc.h, each pin has one MUX register that contains:
 *	 * function associated to the pin:  b8,b5,b4
 *	 * pullup:		            b7
 *	 * pullup when sleeping:            b3
 *	 * output-enable when sleeping bit: b1
 *	 * output-enable (direction) bit:   b0
 *
 *	Note:
 *	  Roles of b1 and b0 are different in http://esp8266.ru/esp8266-pin-register-strapping 
 *
 *	Note: Arduino/cores/esp8266/esp8266_peri.h implements pulldown capability:
 *	 * pulldown:                        b6
 *	 * pulldown when sleeping bit:	    b2
 */
#define _hw_iomux0__conf		_r32, 0x00, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio12	_r32, 0x04, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio13	_r32, 0x08, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio14	_r32, 0x0C, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio15	_r32, 0x10, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio3		_r32, 0x14, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio1		_r32, 0x18, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio6		_r32, 0x1c, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio7		_r32, 0x20, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio8		_r32, 0x24, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio9		_r32, 0x28, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio10	_r32, 0x2c, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio11	_r32, 0x30, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio0		_r32, 0x34, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio2		_r32, 0x38, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio4		_r32, 0x3C, 0x01FF, 0
#define _hw_iomux0_hw_pin_gpio5		_r32, 0x40, 0x01FF, 0

/* #define _hw_iomux0_hw_pin_mtdi		_r32, 0x04, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_mtck		_r32, 0x08, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_mtdo		_r32, 0x10, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_mtms		_r32, 0x0C, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_clk	_r32, 0x1c, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_cmd	_r32, 0x30, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_data0	_r32, 0x20, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_data1	_r32, 0x24, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_data2	_r32, 0x28, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_sd_data3	_r32, 0x2c, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_u0rxd		_r32, 0x14, 0x01FF, 0 */
/* #define _hw_iomux0_hw_pin_u0txd		_r32, 0x18, 0x01FF, 0 */


/*  Pin functions
 *
 *	Taken from http://esp8266.ru/esp8266-pin-register-strapping
 *
 *	Each pin function is declared with the symbol _pinname_fn_function
 *	The symbol _pinname_functions is the string used to put the error
 *	message when an unavailable function is chosen with hw_config().
 */
#define _hw_pin_gpio0_fn_gpio		, 0
#define _hw_pin_gpio0_fn_spi_cs2	, 1
#define _hw_pin_gpio0_fn_clk_out	, 4
#define _hw_pin_gpio0_fn		"`gpio`, `spi_cs2`, or `clk_out`"

#define _hw_pin_gpio1_fn_u0_txd		, 0
#define _hw_pin_gpio1_fn_hw_uart0_txd	, 0
#define _hw_pin_gpio1_fn_spi_cs1	, 1
#define _hw_pin_gpio1_fn_gpio		, 3
#define _hw_pin_gpio1_fn_clk_rtc	, 4
#define _hw_pin_gpio1_fn		"`gpio`, `uart0_txd`, `spi_cs1`, or `clk_rtc`"

#define _hw_pin_gpio2_fn_gpio		, 0
#define _hw_pin_gpio2_fn_i2so_ws	, 1
#define _hw_pin_gpio2_fn_u1_txd		, 2
#define _hw_pin_gpio2_fn_u0_txd		, 4
#define _hw_pin_gpio2_fn_hw_uart0_txd	, 4
#define _hw_pin_gpio2_fn		"`gpio`, `i2so_ws`, `u1_txd`, or `u0_txd`"

#define _hw_pin_gpio3_fn_u0_rxd		, 0
#define _hw_pin_gpio3_fn_hw_uart0_rxd	, 0
#define _hw_pin_gpio3_fn_i2so_data	, 1
#define _hw_pin_gpio3_fn_gpio		, 3
#define _hw_pin_gpio3_fn_clk_xtal	, 4
#define _hw_pin_gpio3_fn		"`gpio`, `uart0_rxd`, `i2so_data`, or `fn_clk_xtal`"

#define _hw_pin_gpio4_fn_gpio		, 0
#define _hw_pin_gpio4_fn_clk_xtal	, 1
#define _hw_pin_gpio4_fn		"`gpio` or `clk_xtal`"

#define _hw_pin_gpio5_fn_gpio		, 0
#define _hw_pin_gpio5_fn_clk_rtc	, 1
#define _hw_pin_gpio5_fn		"`gpio`, or `clk_rtc`"

#define _hw_pin_gpio6_fn_sd_clk		, 0
#define _hw_pin_gpio6_fn_spi_clk	, 1
#define _hw_pin_gpio6_fn_gpio		, 3
#define _hw_pin_gpio6_fn_u1_cts		, 4
#define _hw_pin_gpio6_fn		"`gpio`, `sd_clk`, `spi_clk`, or `u1_cts`"

#define _hw_pin_gpio7_fn_sd_data0	, 0
#define _hw_pin_gpio7_fn_spi_q		, 1
#define _hw_pin_gpio7_fn_gpio		, 3
#define _hw_pin_gpio7_fn_u1_txd		, 4
#define _hw_pin_gpio7_fn		"`gpio`, `sd_data0`, `spi_q`, or `u1_txd`"

#define _hw_pin_gpio8_fn_sd_data1	, 0
#define _hw_pin_gpio8_fn_spi_d		, 1
#define _hw_pin_gpio8_fn_gpio		, 3
#define _hw_pin_gpio8_fn_u1_rxd		, 4
#define _hw_pin_gpio8_fn		"`gpio`, `sd_data1`, `spi_d`, or `u1_rxd`"

#define _hw_pin_gpio9_fn_sd_data2	, 0
#define _hw_pin_gpio9_fn_spi_hd		, 1
#define _hw_pin_gpio9_fn_gpio		, 3
#define _hw_pin_gpio9_fn_hspi_hd	, 4
#define _hw_pin_gpio9_fn		"`gpio`, `sd_data2`, `spi_hd`, or `hspi_hd`"

#define _hw_pin_gpio10_fn_sd_data3	, 0
#define _hw_pin_gpio10_fn_spi_wp	, 1
#define _hw_pin_gpio10_fn_gpio		, 3
#define _hw_pin_gpio10_fn_hspi_wp	, 4
#define _hw_pin_gpio10_fn		"`gpio`, `sd_data3`, `spi_wp`, or `hspi_wp`"

#define _hw_pin_gpio11_fn_sd_cmd	, 0
#define _hw_pin_gpio11_fn_spi_cs0	, 1
#define _hw_pin_gpio11_fn_gpio		, 3
#define _hw_pin_gpio11_fn_u1_rts	, 4
#define _hw_pin_gpio11_fn		"`gpio`, `sd_cmd`, `spi_cs0`, or `u1_rts`"

#define _hw_pin_gpio12_fn_mtdi		, 0
#define _hw_pin_gpio12_fn_i2si_data	, 1
#define _hw_pin_gpio12_fn_hspiq_miso	, 2
#define _hw_pin_gpio12_fn_gpio		, 3
#define _hw_pin_gpio12_fn_u0_dtr	, 4
#define _hw_pin_gpio12_fn		"`gpio`, `mtdi`, `i2si_data`, `hspiq_miso`, or `u0_dtr`"

#define _hw_pin_gpio13_fn_mtck		, 0
#define _hw_pin_gpio13_fn_i2s_bck	, 1
#define _hw_pin_gpio13_fn_hspi_mosi	, 2
#define _hw_pin_gpio13_fn_gpio		, 3
#define _hw_pin_gpio13_fn_u0_cts	, 4
#define _hw_pin_gpio13_fn		"`gpio`, `mtck`, `i2s_bck`, `hspi_mosi`, or `u0_cts`"

#define _hw_pin_gpio14_fn_mtms		, 0
#define _hw_pin_gpio14_fn_i2si_ws	, 1
#define _hw_pin_gpio14_fn_hspi_clk	, 2
#define _hw_pin_gpio14_fn_gpio		, 3
#define _hw_pin_gpio14_fn_u0_dsr		, 4
#define _hw_pin_gpio14_fn		"`gpio`, `mtms`, `i2si_ws`, `hspi_clk`, or `u0_dsr`"

#define _hw_pin_gpio15_fn_mtdo		, 0
#define _hw_pin_gpio15_fn_i2so_bck	, 1
#define _hw_pin_gpio15_fn_hspi_cs	, 2
#define _hw_pin_gpio15_fn_gpio		, 3
#define _hw_pin_gpio15_fn_u0_rts		, 4
#define _hw_pin_gpio15_fn		"`gpio`, `mtdo`, `i2so_bck`, `hspi_cs`, or `u0_rts`"

#define _hw_pin_gpio16_fn_xpd_dcdc	, 0
#define _hw_pin_gpio16_fn_rtc_gpio0	, 1
#define _hw_pin_gpio16_fn_gpio		, 1
#define _hw_pin_gpio16_fn_ext_wakeup	, 2
#define _hw_pin_gpio16_fn_deep_sleep	, 3
#define _hw_pin_gpio16_fn_bt_xtal_en	, 4
#define _hw_pin_gpio16_fn		"`gpio`, `xpd_dcdc`, `ext_wakeup`, `deep_sleep`, or `bt_xtal_en`"


/*******************************************************************************
 *									       *
 *	GPIO ports and pins						       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section esp8266_pins Ports and pins
 *
 * Each pin can be connected to different signals with the `hw_config()` or
 * `hwa_config()` instruction.
 *
 * Pin    | HWA name        | Class                       | Functions
 * -------|-----------------|-----------------------------|-------------
 * GPIO0  | `hw_pin_gpio0`  | @ref espressif_io1a "_io1a" | `gpio` / `spi_cs2` / `clk_out`
 * GPIO1  | `hw_pin_gpio1`  | @ref espressif_io1a "_io1a" | `gpio` / `uart0_txd` / `spi_cs1` / `clk_rtc`
 * GPIO2  | `hw_pin_gpio2`  | @ref espressif_io1a "_io1a" | `gpio` / `i2so_ws` / `u1_txd` / `u0_txd`
 * GPIO3  | `hw_pin_gpio3`  | @ref espressif_io1a "_io1a" | `gpio` / `uart0_rxd` / `i2so_data` / `fn_clk_xtal`
 * GPIO4  | `hw_pin_gpio4`  | @ref espressif_io1a "_io1a" | `gpio` / `clk_xtal`
 * GPIO5  | `hw_pin_gpio5`  | @ref espressif_io1a "_io1a" | `gpio` / `clk_rtc`
 * GPIO6  | `hw_pin_gpio6`  | @ref espressif_io1a "_io1a" | `gpio` / `sd_clk` / `spi_clk` / `u1_cts`
 * GPIO7  | `hw_pin_gpio7`  | @ref espressif_io1a "_io1a" | `gpio` / `sd_data0` / `spi_q` / `u1_txd`
 * GPIO8  | `hw_pin_gpio8`  | @ref espressif_io1a "_io1a" | `gpio` / `sd_data1` / `spi_d` / `u1_rxd`
 * GPIO9  | `hw_pin_gpio9`  | @ref espressif_io1a "_io1a" | `gpio` / `sd_data2` / `spi_hd` / `hspi_hd`
 * GPIO10 | `hw_pin_gpio10` | @ref espressif_io1a "_io1a" | `gpio` / `sd_data3` / `spi_wp` / `hspi_wp`
 * GPIO11 | `hw_pin_gpio11` | @ref espressif_io1a "_io1a" | `gpio` / `sd_cmd` / `spi_cs0` / `u1_rts`
 * GPIO12 | `hw_pin_gpio12` | @ref espressif_io1a "_io1a" | `gpio` / `mtdi` / `i2si_data` / `hspiq_miso` / `u0_dtr`
 * GPIO13 | `hw_pin_gpio13` | @ref espressif_io1a "_io1a" | `gpio` / `mtck` / `i2s_bck` / `hspi_mosi` / `u0_cts`
 * GPIO14 | `hw_pin_gpio14` | @ref espressif_io1a "_io1a" | `gpio` / `mtms` / `i2si_ws` / `hspi_clk` / `u0_dsr`
 * GPIO15 | `hw_pin_gpio15` | @ref espressif_io1a "_io1a" | `gpio` / `mtdo` / `i2so_bck` / `hspi_cs` / `u0_rts`
 * GPIO16 | `hw_pin_gpio16` | @ref espressif_io1a "_io1a" | `gpio` / `xpd_dcdc` / `ext_wakeup` / `deep_sleep` / `bt_xtal_en`
 */

/*	Objects				class, id, address
 */
#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"

/*	Object				class, id, address
 */
#define _hw_port0			_p16a, 0x60000300, 0x60000300
//#define _hw_port1			_p16a, 0x1000, 0x60000300


/*	Class hardware registers	class, address, write mask, flags mask
 *
 *	Definitions taken from ESP8266_GPIO_Register_141105.ods
 *	See also:
 *	  * 2C-ESP8266__SDK__Programming Guide__EN_v1.4
 *	  * http://esp8266.ru/esp8266-pin-register-strapping/
 *	  * https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/examples/driver_lib/driver/gpio.c
 */
#define _hw__p16a_hout			_r32, 0x00, 0xFFFFFFFF, 0
#define _hw__p16a_houtw1ts		_r32, 0x04, 0x0000FFFF, 0
#define _hw__p16a_houtw1tc		_r32, 0x08, 0x0000FFFF, 0

#define _hw__p16a_henb			_r32, 0x0C, 0x003FFFFF, 0
#define _hw__p16a__enbw1ts		_r32, 0x10, 0x0000FFFF, 0
#define _hw__p16a_henbw1tc		_r32, 0x14, 0x0000FFFF, 0

#define _hw__p16a_hin			_r32, 0x18, 0x00000000, 0

#define _hw__p16a_hie			_r32, 0x1C, 0x0000FFFF, 0
#define _hw__p16a_hiew1ts		_r32, 0x20, 0x0000FFFF, 0
#define _hw__p16a_hiew1tc		_r32, 0x24, 0x0000FFFF, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define _hw__p16a0_btsel		_cb1, hout,     16, 16
#define _hw__p16a0_out			_cb1, hout,     16,  0
#define _hw__p16a0_outw1ts		_cb1, houtw1ts, 16,  0
#define _hw__p16a0_outw1tc		_cb1, houtw1tc, 16,  0

#define _hw__p16a0_sdiosel		_cb1, henb,      6, 16
#define _hw__p16a0_enb			_cb1, henb,     16,  0
#define _hw__p16a0_enbw1ts		_cb1, henbw1ts, 16,  0
#define _hw__p16a0_enbw1tc		_cb1, henbw1tc, 16,  0

#define _hw__p16a0_strapping		_cb1, hin,      16, 16
#define _hw__p16a0_in			_cb1, hin,      16,  0

#define _hw__p16a0_ie			_cb1, hie,      16, 16
#define _hw__p16a0_iew1ts		_cb1, hiew1ts,  16, 16
#define _hw__p16a0_iew1tc		_cb1, hiew1tc,  16, 16


/*	Pins				class, id, port, bn, bp
 */
//#define _hw_pin_mtdi			_io1a, 301, hw_port0, 1, 0
#define _hw_pin_gpio0			_io1a, 301, hw_port0, 1, 0
#define _hw_pin_gpio1			_io1a, 301, hw_port0, 1, 1
#define _hw_pin_gpio2			_io1a, 301, hw_port0, 1, 2
#define _hw_pin_gpio3			_io1a, 301, hw_port0, 1, 3
#define _hw_pin_gpio4			_io1a, 301, hw_port0, 1, 4
#define _hw_pin_gpio5			_io1a, 301, hw_port0, 1, 5
#define _hw_pin_gpio6			_io1a, 301, hw_port0, 1, 6
#define _hw_pin_gpio7			_io1a, 301, hw_port0, 1, 7
#define _hw_pin_gpio8			_io1a, 301, hw_port0, 1, 8
#define _hw_pin_gpio9			_io1a, 301, hw_port0, 1, 9
#define _hw_pin_gpio10			_io1a, 301, hw_port0, 1, 10
#define _hw_pin_gpio11			_io1a, 301, hw_port0, 1, 11
#define _hw_pin_gpio12			_io1a, 301, hw_port0, 1, 12
#define _hw_pin_gpio13			_io1a, 301, hw_port0, 1, 13
#define _hw_pin_gpio14			_io1a, 301, hw_port0, 1, 14
#define _hw_pin_gpio15			_io1a, 301, hw_port0, 1, 15


/*	Pin GPIO16 (RTC_GPIO0 / xpd_dcdc) is of a different class
 *
 *	See esp_iot_sdk_v1.4.0/examples/driver_lib/driver/gpio16.c
 */
#define _hw_pin_gpio16			_io1b, 301, hw_port1, 1, 0


/*  Association of pin numbers and pin names
 */
//#define hw_pin_6			hw_pin_tout /* configurable? */
/* #define hw_pin_8			hw_pin_xpd_dcdc */
/* #define hw_pin_9			hw_pin_mtms */
/* #define hw_pin_10			hw_pin_mtdi */
/* #define hw_pin_12			hw_pin_mtck */
/* #define hw_pin_13			hw_pin_mtdo */
/* #define hw_pin_14			hw_pin_gpio2 */
/* #define hw_pin_15			hw_pin_gpio0 */
/* #define hw_pin_16			hw_pin_gpio4 */
/* #define hw_pin_18			hw_pin_sdio_data_2 */
/* #define hw_pin_19			hw_pin_sdio_data_3 */
/* #define hw_pin_20			hw_pin_sdio_cmd */
/* #define hw_pin_21			hw_pin_sdio_clk */
/* #define hw_pin_22			hw_pin_sdio_data_0 */
/* #define hw_pin_23			hw_pin_sdio_data_1 */
/* #define hw_pin_24			hw_pin_gpio5 */
/* #define hw_pin_25			hw_pin_u0rxd */
/* #define hw_pin_26			hw_pin_u0txd */

#define hw_pin_8			hw_pin_gpio16
#define hw_pin_9			hw_pin_gpio14
#define hw_pin_10			hw_pin_gpio12
#define hw_pin_12			hw_pin_gpio13
#define hw_pin_13			hw_pin_gpio15
#define hw_pin_14			hw_pin_gpio2
#define hw_pin_15			hw_pin_gpio0
#define hw_pin_16			hw_pin_gpio4
#define hw_pin_18			hw_pin_gpio9
#define hw_pin_19			hw_pin_gpio10
#define hw_pin_20			hw_pin_gpio11
#define hw_pin_21			hw_pin_gpio6
#define hw_pin_22			hw_pin_gpio7
#define hw_pin_23			hw_pin_gpio8
#define hw_pin_24			hw_pin_gpio5
#define hw_pin_25			hw_pin_gpio3
#define hw_pin_26			hw_pin_gpio1


/*  Pin designed by a number stored in a variable
 */
#define _hw_class__ionum

#define _hw_is_var_var			, 1

//#define hw_pin_gpio(x)			_ionum, 0, /* hw_port */, x
#define hw_pin_gpio(x)			HW_G2(hw_pin_gpio_var,HW_IS(var,x))(x)

#define hw_pin_gpio_var_0(x)		hw_pin_gpio##x

#define hw_pin_gpio_var_1(x)		_ionum, 0, /* hw_port */, x

  /* uint8_t pin = 5 ; */

  /* hw_config( hw_pin_gpio(var(pin)), */
  /* 	     function,  gpio,			// Optionnal */
  /* 	     direction, output_when_awake */
  /* 	     ); */

  // Initialize UART0
  //  uart_div_modify(0, UART_CLK_FREQ / 115200);


/* #if !defined __ASSEMBLER__ */

/* typedef struct { */
/*   hwa_r32_t port ; */
/*   hwa_r32_t ddr ; */
/* } hwa_p16a_t ; */

/* #endif */


/*******************************************************************************
 *									       *
 *	UARTS								       *
 *									       *
 *	Translation of							       *
 *	 * Arduino/cores/esp8266/HardwareSerial.h			       *
 *	 * Arduino/cores/esp8266/HardwareSerial.coo			       *
 *	 * Arduino/cores/esp8266/esp8266_peri.h				       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Objects				class, id, address
 */
#define _hw_uart0			_uarta, 0x60000000, 0x60000000
#define _hw_uart1			_uarta, 0x60000F00, 0x60000F00

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw__uarta__fifo		_r32, 0x00, 0xFFFFFFFF, 0
#define _hw__uarta__irq			_r32, 0x04, 0xFFFFFFFF, 0
#define _hw__uarta__irqstat		_r32, 0x08, 0xFFFFFFFF, 0
#define _hw__uarta__irqenb		_r32, 0x0C, 0xFFFFFFFF, 0
#define _hw__uarta__irqclr		_r32, 0x10, 0xFFFFFFFF, 0
#define _hw__uarta__brr			_r32, 0x14, 0xFFFFFFFF, 0
#define _hw__uarta__autobaud		_r32, 0x18, 0xFFFFFFFF, 0
#define _hw__uarta__stat		_r32, 0x1C, 0xFFFFFFFF, 0
#define _hw__uarta__conf0		_r32, 0x20, 0xFFFFFFFF, 0
#define _hw__uarta__conf1		_r32, 0x24, 0xFFFFFFFF, 0
#define _hw__uarta__lopulse		_r32, 0x28, 0xFFFFFFFF, 0
#define _hw__uarta__hipulse		_r32, 0x2C, 0xFFFFFFFF, 0
#define _hw__uarta__pulsnum		_r32, 0x30, 0xFFFFFFFF, 0
#define _hw__uarta__date		_r32, 0x78, 0xFFFFFFFF, 0
#define _hw__uarta__id			_r32, 0x7C, 0xFFFFFFFF, 0

/*	Class logical registers
 */
#define _hw__uarta_uito			_cb1, _irq, 1, 8	// RX _IRQ TimeOut
#define _hw__uarta_uibd			_cb1, _irq, 1, 7	// Break Detected
#define _hw__uarta_uicts		_cb1, _irq, 1, 6	// CTS Changed
#define _hw__uarta_uidsr		_cb1, _irq, 1, 5	// DSR Change
#define _hw__uarta_uiof			_cb1, _irq, 1, 4	// RX _IRQ OverFlow
#define _hw__uarta_uifr			_cb1, _irq, 1, 3	// Frame Error
#define _hw__uarta_uipe			_cb1, _irq, 1, 2	// Parity Error
#define _hw__uarta_uife			_cb1, _irq, 1, 1	// TX _IRQ Empty
#define _hw__uarta_uiff			_cb1, _irq, 1, 0	// RX _IRQ Full

#define _hw__uarta_ustx			_cb1, _stat, 1, 31	// TX PIN Level	 
#define _hw__uarta_usrts		_cb1, _stat, 1, 30	// RTS PIN Level	 
#define _hw__uarta_usdtr		_cb1, _stat, 1, 39	// DTR PIN Level	 
#define _hw__uarta_ustxc		_cb1, _stat, 8, 16	// TX FIFO COUNT (8bit)
#define _hw__uarta_usrxd		_cb1, _stat, 1, 15	// RX PIN Level	 
#define _hw__uarta_uscts		_cb1, _stat, 1, 14	// CTS PIN Level	 
#define _hw__uarta_usdsr		_cb1, _stat, 1, 13	// DSR PIN Level	 
#define _hw__uarta_usrxc		_cb1, _stat, 8,	 0	// RX FIFO COUNT (8bit)

#define _hw__uarta_ucdtri		_cb1, _conf0, 1, 24	// Invert DTR
#define _hw__uarta_ucrtsi		_cb1, _conf0, 1, 23	// Invert RTS
#define _hw__uarta_uctxi		_cb1, _conf0, 1, 22	// Invert TX
#define _hw__uarta_ucdsri		_cb1, _conf0, 1, 21	// Invert DSR
#define _hw__uarta_ucctsi		_cb1, _conf0, 1, 20	// Invert CTS
#define _hw__uarta_ucrxi		_cb1, _conf0, 1, 19	// Invert RX
#define _hw__uarta_uctxrst		_cb1, _conf0, 1, 18	// Reset TX FIFO
#define _hw__uarta_ucrxrst		_cb1, _conf0, 1, 17	// Reset RX FIFO
#define _hw__uarta_uctxhfe		_cb1, _conf0, 1, 15	// TX Harware Flow Enable
#define _hw__uarta_uclbe		_cb1, _conf0, 1, 14	// LoopBack Enable
#define _hw__uarta_ucbrk		_cb1, _conf0, 1,  8	// Send Break on the TX line
#define _hw__uarta_ucswdtr		_cb1, _conf0, 1,  7	// Set this bit to assert DTR
#define _hw__uarta_ucswrts		_cb1, _conf0, 1,  6	// Set this bit to assert RTS
#define _hw__uarta_ucsbn		_cb1, _conf0, 2,  4	// StopBits Count (2bit) 0:disable, 1:1bit, 2:1.5bit, 3:2bit
#define _hw__uarta_ucbn			_cb1, _conf0, 2,  2	// DataBits Count (2bin) 0:5bit, 1:6bit, 2:7bit, 3:8bit
#define _hw__uarta_ucpae		_cb1, _conf0, 1,  1	// Parity Enable
#define _hw__uarta_ucpa			_cb1, _conf0, 1,  0	// Parity 0:even, 1:odd
#define _hw__uarta_ucpaex		_cb1, _conf0, 2,  0	// HWA convenience

#define _hw__uarta_uctoe		_cb1, _conf1, 1, 31	// RX TimeOut Enable
#define _hw__uarta_uctot		_cb1, _conf1, 7, 24	// RX TimeOut Treshold (7bit)
#define _hw__uarta_ucrxhfe		_cb1, _conf1, 1, 23	// RX Harware Flow Enable
#define _hw__uarta_ucrxhft		_cb1, _conf1, 7, 16	// RX Harware Flow Treshold (7bit)
#define _hw__uarta_ucfet		_cb1, _conf1, 7,  8	// TX FIFO Empty Treshold (7bit)
#define _hw__uarta_ucfft		_cb1, _conf1, 7,  0	// RX FIFO Full Treshold (7bit)

// #define _hw__uarta_		_cb1, _, 1,	//

#define hw_uart0pin_txd			hw_pin_gpio1
#define hw_uart0pin_rxd			hw_pin_gpio3


#include "../hwa_2.h"
#include "../classes/io1a_2.h"
#include "../classes/uarta_2.h"
