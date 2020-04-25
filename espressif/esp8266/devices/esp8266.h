
/* This file is part of the HWA project.
 * Copyright (c) 2012,2015 Christophe Duparquet.
 * All rights reserved. Read LICENSE.TXT for details.
 */

/**
 * @file
 * @brief Espressif's ESP8266
 */

#include "../hwa_1.h"
#include "os.h"

/**
 * @page esp8266 ESP8266
 */
#define HW_SYSHZ				80000000
#define HW_APBHZ				HW_SYSHZ

#define hw_uptime_us()				(*(volatile uint32_t*)0x3ff20c00)
#define hw_uptime()				(hw_uptime_us / (1000*1000))


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section espressif_peripherals Peripherals
 *
 * __Note__ All the peripherals are not completely implemented yet.
 *
 * Object name	| Class		                 | Comments
 * :------------|--------------------------------|:-----------------------------
 * `port0`	| @ref espressif_p16a "_p16a"	 | General purpose I/O port
 * `timer1`	| @ref espressif_tm23a "_tm23a"  | 23-bit timer
 * `uart0`	| @ref espressif_uarta "_uarta"	 | UART
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/
/**
 * @ingroup espressif_interrupts
 * @brief Definition of the interrupts
 */
/*  Interrupt definitions
 *
 *  'vector' is used to store the type of interrupt
 *
 *						class, object, vector, ie, if
 */
#define hw_irq_timer1_nmi			_irq, timer1, nmi, ie,
#define hw_irq_timer1_irq			_irq, timer1,	9, ie,


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#define hw_class__shared
#define hw_shared			_shared, 0x3FF00000

/*	Object hardware registers	class, address, write mask, w1tc mask
 */
#define hw_reg_shared__edgeie		_r32, 0x04, 0xFFFFFFFF, 0
#define hw_reg_shared__swap		_r32, 0x28, 0xFFFFFFFF, 0

#if !defined __ASSEMBLER__
/*
 *  HWA context
 */
typedef struct {

  /*  Hardware registers
   */
  hwa_r32_t	_edgeie ;
  hwa_r32_t	_swap ;
} hwa_shared_t ;


#define _hwa_setup__shared(o,a)	\
  _hwa_setup_r( o, _edgeie );	\
  _hwa_setup_r( o, _swap )

#define _hwa_init__shared(o,a)	\
  /* _edgeie is UNKNOWN and 0 causes errors */	\
  _hwa_init_r( o, _swap, 0 )

#define _hwa_commit__shared(o,a)	\
  _hwa_commit_r( o, _edgeie );	\
  _hwa_commit_r( o, _swap )

#endif


/*******************************************************************************
 *									       *
 *	GPIO ports							       *
 *									       *
 *******************************************************************************/

#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"
#include "../classes/io1b_1.h"

/*	Object				class, address
 */
#define hw_port0			_p16a, 0x60000300


/*	Class hardware registers	class, address, write mask, flags mask
 *
 *	See:
 *	  * ESP8266_GPIO_Register_141105.ods
 *	  * 2C-ESP8266__SDK__Programming Guide__EN_v1.4
 *	  * 0D-ESP8266__Pin_List__Release_15-11-2014.ods
 *	  * ESP8266_RTOS_SDK/blob/master/examples/driver_lib/driver/gpio.c
 */
#define hw_reg__p16a__out		_r32, 0x00, 0xFFFFFFFF, 0
#define hw_reg__p16a__outw1ts		_r32, 0x04, 0x0000FFFF, 0
#define hw_reg__p16a__outw1tc		_r32, 0x08, 0x0000FFFF, 0
#define hw_reg__p16a__enb		_r32, 0x0C, 0x003FFFFF, 0
#define hw_reg__p16a__enbw1ts		_r32, 0x10, 0x0000FFFF, 0
#define hw_reg__p16a__enbw1tc		_r32, 0x14, 0x0000FFFF, 0
#define hw_reg__p16a__in		_r32, 0x18, 0x00000000, 0
#define hw_reg__p16a__ie		_r32, 0x1C, 0x0000FFFF, 0
#define hw_reg__p16a__iew1ts		_r32, 0x20, 0x0000FFFF, 0
#define hw_reg__p16a__iew1tc		_r32, 0x24, 0x0000FFFF, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define hw_reg__p16a_btsel		_cb1, _out,	16, 16
#define hw_reg__p16a_out		_cb1, _out,	16,  0
#define hw_reg__p16a_outw1ts		_cb1, _outw1ts, 16,  0
#define hw_reg__p16a_outw1tc		_cb1, _outw1tc, 16,  0

#define hw_reg__p16a_sdiosel		_cb1, _enb,	 6, 16
#define hw_reg__p16a_enb		_cb1, _enb,	16,  0
#define hw_reg__p16a_enbw1ts		_cb1, _enbw1ts, 16,  0
#define hw_reg__p16a_enbw1tc		_cb1, _enbw1tc, 16,  0

#define hw_reg__p16a_strapping		_cb1, _in,	16, 16
#define hw_reg__p16a_in			_cb1, _in,	16,  0

#define hw_reg__p16a_ie			_cb1, _ie,	16, 16
#define hw_reg__p16a_iew1ts		_cb1, _iew1ts,	16, 16
#define hw_reg__p16a_iew1tc		_cb1, _iew1tc,	16, 16


/*******************************************************************************
 *									       *
 *	I/O pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section espressif_pins Pins
 *
 * Each pin can be connected to different signals with the `configure` action:
 *
 * Pin    | HWA name | Class                     | Functions
 * -------|----------|---------------------------|-------------
 * GPIO0  | `gpio0`  | @ref espressif_io1a "_io1a" | `gpio`, `(spi0,cs2)`, `clk_out`
 * GPIO1  | `gpio1`  | @ref espressif_io1a "_io1a" | `gpio`, `(uart0,txd)`, `(spi0,cs1)`, `clk_rtc`
 * GPIO2  | `gpio2`  | @ref espressif_io1a "_io1a" | `gpio`, `(i2so0,ws)`, `(uart1,txd)`, `(uart0,txd)`
 * GPIO3  | `gpio3`  | @ref espressif_io1a "_io1a" | `gpio`, `(uart0,rxd)`, `(i2so,data)`, `fn_clk_xtal`
 * GPIO4  | `gpio4`  | @ref espressif_io1a "_io1a" | `gpio`, `clk_xtal`
 * GPIO5  | `gpio5`  | @ref espressif_io1a "_io1a" | `gpio`, `clk_rtc`
 * GPIO6  | `gpio6`  | @ref espressif_io1a "_io1a" | `gpio`, `sd_clk`, `(spi0,clk)`, `(uart1,cts)`
 * GPIO7  | `gpio7`  | @ref espressif_io1a "_io1a" | `gpio`, `sd_data0`, `(spi0,q)`, `(uart1,txd)`
 * GPIO8  | `gpio8`  | @ref espressif_io1a "_io1a" | `gpio`, `sd_data1`, `(spi0,d)`, `(uart1,rxd)`
 * GPIO9  | `gpio9`  | @ref espressif_io1a "_io1a" | `gpio`, `sd_data2`, `(spi0,hd)`, `(hspi0,hd)`
 * GPIO10 | `gpio10` | @ref espressif_io1a "_io1a" | `gpio`, `sd_data3`, `(spi0,wp)`, `(hspi0,wp)`
 * GPIO11 | `gpio11` | @ref espressif_io1a "_io1a" | `gpio`, `sd_cmd`, `(spi0,cs0)`, `(uart1,rts)`
 * GPIO12 | `gpio12` | @ref espressif_io1a "_io1a" | `gpio`, `mtdi`, `(i2si,data)`, `(hspi0,miso)`, `(uart0,dtr)`
 * GPIO13 | `gpio13` | @ref espressif_io1a "_io1a" | `gpio`, `mtck`, `(i2s0,bck)`, `(hspi0,mosi)`, `(uart0,cts)`
 * GPIO14 | `gpio14` | @ref espressif_io1a "_io1a" | `gpio`, `mtms`, `(i2si,ws)`, `(hspi0,clk)`, `(uart0,dsr)`
 * GPIO15 | `gpio15` | @ref espressif_io1a "_io1a" | `gpio`, `mtdo`, `(i2so0,bck)`, `(hspi0,cs)`, `(uart0,rts)`, `(uart0,txd)`
 * GPIO16 | `gpio16` | @ref espressif_io1b "_io1b" | `gpio`, `xpd_dcdc`, `external_wakeup`, `deep_sleep`, `bt_xtal_en`
 */


/*	Pins
 *
 *	Pin GPIO16 (RTC_GPIO0 / xpd_dcdc) is of a different class.
 *	See esp_iot_sdk_v1.4.0/examples/driver_lib/driver/gpio16.c
 *
 *					class, port, bn, bp
 */
#define hw_gpio0			_io1a, port0, 1, 0
#define hw_gpio1			_io1a, port0, 1, 1
#define hw_gpio2			_io1a, port0, 1, 2
#define hw_gpio3			_io1a, port0, 1, 3
#define hw_gpio4			_io1a, port0, 1, 4
#define hw_gpio5			_io1a, port0, 1, 5
#define hw_gpio6			_io1a, port0, 1, 6
#define hw_gpio7			_io1a, port0, 1, 7
#define hw_gpio8			_io1a, port0, 1, 8
#define hw_gpio9			_io1a, port0, 1, 9
#define hw_gpio10			_io1a, port0, 1, 10
#define hw_gpio11			_io1a, port0, 1, 11
#define hw_gpio12			_io1a, port0, 1, 12
#define hw_gpio13			_io1a, port0, 1, 13
#define hw_gpio14			_io1a, port0, 1, 14
#define hw_gpio15			_io1a, port0, 1, 15

#define hw_gpio16			_io1b, rtc, 1, 0


/*  Association of pin numbers and pin names
 */
#define hw_pin_8			gpio16
#define hw_pin_9			gpio14
#define hw_pin_10			gpio12
#define hw_pin_12			gpio13
#define hw_pin_13			gpio15
#define hw_pin_14			gpio2
#define hw_pin_15			gpio0
#define hw_pin_16			gpio4
#define hw_pin_18			gpio9
#define hw_pin_19			gpio10
#define hw_pin_20			gpio11
#define hw_pin_21			gpio6
#define hw_pin_22			gpio7
#define hw_pin_23			gpio8
#define hw_pin_24			gpio5
#define hw_pin_25			gpio3
#define hw_pin_26			gpio1


/*  Pin designed by a number stored in a variable
 */
#define hw_class__ionum

#define hw_pin_gpio(x)			HW_Y(hw_pin_gpio_var_,_hw_is_var_##x)(x)
#define hw_pin_gpio_var_0(x)		hw_pin_gpio##x
#define hw_pin_gpio_var_1(x)		_ionum, 0, /* hw_port */, x


/*  Pin configuration objects
 *
 *	Each pin has a _pcf object that handles its configuration.
 */
#include "../classes/pcfa_1.h"
#include "../classes/pcfb_1.h"

#define hw_gpio12_cf			_pcfa, 0x60000804
#define hw_gpio13_cf			_pcfa, 0x60000808
#define hw_gpio14_cf			_pcfa, 0x6000080C
#define hw_gpio15_cf			_pcfa, 0x60000810
#define hw_gpio3_cf			_pcfa, 0x60000814
#define hw_gpio1_cf			_pcfa, 0x60000818
#define hw_gpio6_cf			_pcfa, 0x6000081c
#define hw_gpio7_cf			_pcfa, 0x60000820
#define hw_gpio8_cf			_pcfa, 0x60000824
#define hw_gpio9_cf			_pcfa, 0x60000828
#define hw_gpio10_cf			_pcfa, 0x6000082c
#define hw_gpio11_cf			_pcfa, 0x60000830
#define hw_gpio0_cf			_pcfa, 0x60000834
#define hw_gpio2_cf			_pcfa, 0x60000838
#define hw_gpio4_cf			_pcfa, 0x6000083C
#define hw_gpio5_cf			_pcfa, 0x60000840


/*  Pin functions
 *
 *	Each pin function is declared with the symbol _pinname_fn_function.
 *
 *	The value is the value of bits 8,5,4 (fn) in the I/O cf register.
 *
 *	The symbol _pinname_fns is used to build the error message when the
 *	'config' action asks for an unavailable function.
 */
#define _hw_pf_gpio0			(gpio, (spi0,cs2), clk_out)
#define _hw_pf_gpio0_gpio		, 0
#define _hw_pf_gpio0_spi0cs2		, 1
#define _hw_pf_gpio0_clk_out		, 4 /* RESET */

#define _hw_pf_gpio1			(gpio, (uart0,txd), (spi0,cs1), clk_rtc)
#define _hw_pf_gpio1_uart0txd		, 0, _hwa_write( uart0, swap, 0 );
#define _hw_pf_gpio1_spi0cs1		, 1
#define _hw_pf_gpio1_gpio		, 3
#define _hw_pf_gpio1_clk_rtc		, 4

#define _hw_pf_gpio2			(gpio, (i2so0,ws), (uart1,txd), (uart0,txd))
#define _hw_pf_gpio2_gpio		, 0
#define _hw_pf_gpio2_i2so_ws		, 1
#define _hw_pf_gpio2_uart1_txd		, 2
#define _hw_pf_gpio2_uart0_txd		, 4, _hwa_write( uart0, swap, 0 );

#define _hw_pf_gpio3			(gpio, (uart0,rxd), (i2so,data), fn_clk_xtal)
#define _hw_pf_gpio3_uart0rxd		, 0, _hwa_write( uart0, swap, 0 );
#define _hw_pf_gpio3_i2sodata		, 1
#define _hw_pf_gpio3_gpio		, 3
#define _hw_pf_gpio3_clk_xtal		, 4

#define _hw_pf_gpio4			(gpio, clk_xtal)
#define _hw_pf_gpio4_gpio		, 0
#define _hw_pf_gpio4_clk_xtal		, 1

#define _hw_pf_gpio5			(gpio, clk_rtc)
#define _hw_pf_gpio5_gpio		, 0
#define _hw_pf_gpio5_clk_rtc		, 1

#define _hw_pf_gpio6			(gpio, sd_clk, (spi0,clk), (uart1,cts))
#define _hw_pf_gpio6_sd_clk		, 0
#define _hw_pf_gpio6_spi0clk		, 1
#define _hw_pf_gpio6_gpio		, 3
#define _hw_pf_gpio6_uart1cts		, 4

#define _hw_pf_gpio7			(gpio, sd_data0, (spi0,q), (uart1,txd))
#define _hw_pf_gpio7_sd_data0		, 0
#define _hw_pf_gpio7_spi0_q		, 1
#define _hw_pf_gpio7_gpio		, 3
#define _hw_pf_gpio7_uart1txd		, 4

#define _hw_pf_gpio8			(gpio, sd_data1, (spi0,d), (uart1,rxd))
#define _hw_pf_gpio8_sd_data1		, 0
#define _hw_pf_gpio8_spi0_d		, 1
#define _hw_pf_gpio8_gpio		, 3
#define _hw_pf_gpio8_uart1rxd		, 4

#define _hw_pf_gpio9			(gpio, sd_data2, (spi0,hd), (hspi0,hd))
#define _hw_pf_gpio9_sd_data2		, 0
#define _hw_pf_gpio9_spi0hd		, 1
#define _hw_pf_gpio9_gpio		, 3
#define _hw_pf_gpio9_hspi0hd		, 4

#define _hw_pf_gpio10			(gpio, sd_data3, (spi0,wp), (hspi0,wp))
#define _hw_pf_gpio10_sd_data3		, 0
#define _hw_pf_gpio10_spi0wp		, 1
#define _hw_pf_gpio10_gpio		, 3
#define _hw_pf_gpio10_hspi0wp		, 4

#define _hw_pf_gpio11			(gpio, sd_cmd, (spi0,cs0), (uart1,rts))
#define _hw_pf_gpio11_sd_cmd		, 0
#define _hw_pf_gpio11_spi0cs0		, 1
#define _hw_pf_gpio11_gpio		, 3
#define _hw_pf_gpio11_uart1rts		, 4

#define _hw_pf_gpio12			(gpio, mtdi, (i2si,data), (hspi0,miso), (uart0,dtr))
#define _hw_pf_gpio12_mtdi		, 0
#define _hw_pf_gpio12_i2si_data		, 1
#define _hw_pf_gpio12_hspi0miso		, 2
#define _hw_pf_gpio12_gpio		, 3
#define _hw_pf_gpio12_uart0dtr		, 4

#define _hw_pf_gpio13			(gpio, mtck, (i2s0,bck), (hspi0,mosi), (uart0,cts))
#define _hw_pf_gpio13_mtck		, 0
#define _hw_pf_gpio13_i2s0bck		, 1
#define _hw_pf_gpio13_hspi0mosi		, 2
#define _hw_pf_gpio13_gpio		, 3
#define _hw_pf_gpio13_uart0cts		, 4
#define _hw_pf_gpio13_uart0rxd		, 4, _hwa_write( uart0, swap, 1 );

#define _hw_pf_gpio14			(gpio, mtms, (i2si,ws), (hspi0,clk), (uart0,dsr))
#define _hw_pf_gpio14_mtms		, 0
#define _hw_pf_gpio14_i2siws		, 1
#define _hw_pf_gpio14_hspi0clk		, 2
#define _hw_pf_gpio14_gpio		, 3
#define _hw_pf_gpio14_uart0dsr		, 4

#define _hw_pf_gpio15			(gpio, mtdo, (i2so0,bck), (hspi0,cs), (uart0,rts), (uart0,txd))
#define _hw_pf_gpio15_mtdo		, 0
#define _hw_pf_gpio15_i2so0bck		, 1
#define _hw_pf_gpio15_hspi0cs		, 2
#define _hw_pf_gpio15_gpio		, 3
#define _hw_pf_gpio15_uart0rts		, 4
#define _hw_pf_gpio15_uart0txd		, 4, _hwa_write( uart0, swap, 1 );

#define _hw_pf_gpio16			(gpio, xpd_dcdc, external_wakeup, deep_sleep, bt_xtal_en)
#define _hw_pf_gpio16_xpd_dcdc		, 0
#define _hw_pf_gpio16_rtc_gpio0		, 1
#define _hw_pf_gpio16_gpio		, 1
#define _hw_pf_gpio16_external_wakeup	, 2
#define _hw_pf_gpio16_deep_sleep	, 3
#define _hw_pf_gpio16_bt_xtal_en	, 4


/*******************************************************************************
 *									       *
 *	RTC								       *
 *									       *
 *	The RTC handles the GPIO16 pin					       *
 *									       *
 *******************************************************************************/

#include "../classes/rtca_1.h"

#define hw_rtc				_rtca, 0x60000700

/* #define hw_reg__rtca__store0		_r32, 0x30, 0xFFFFFFFF, 0 */
/* #define hw_reg__rtca__store1		_r32, 0x34, 0xFFFFFFFF, 0 */
/* #define hw_reg__rtca__store2		_r32, 0x38, 0xFFFFFFFF, 0 */
/* #define hw_reg__rtca__store3		_r32, 0x3C, 0xFFFFFFFF, 0 */

#define hw_reg_rtc__gpioout		_r32, 0x68, 0xFFFFFFFF, 0
#define hw_reg_rtc__gpioen		_r32, 0x74, 0xFFFFFFFF, 0
#define hw_reg_rtc__gpioin		_r32, 0x8C, 0xFFFFFFFF, 0
#define hw_reg_rtc__gpiocf		_r32, 0x90, 0xFFFFFFFF, 0
#define hw_reg_rtc__gpiocr		_r32, 0xA0, 0xFFFFFFFF, 0

#define hw_reg_gpio16_fn		_xob2, rtc, _gpiocr, 1, 6, 2, _gpiocr, 2, 0, 0
#define hw_reg_gpio16_spd		_xob1, rtc, _gpiocr, 1, 5
#define hw_reg_gpio16_pd		_xob1, rtc, _gpiocr, 1, 3
#define hw_reg_gpio16_pdx		_xob2, rtc, _gpiocr, 1, 5, 1, _gpiocr, 1, 3, 0 /* convenient */
#define hw_reg_gpio16_oe		_xob1, rtc, _gpioen, 1, 0 /* convenient */
#define hw_reg_gpio16_cf		_xob1, rtc, _gpiocf, 1, 0 /* convenient */


/*******************************************************************************
 *									       *
 *	Hardware timer 1						       *
 *									       *
 *	23-bit timer (down counter) clocked by the APB			       *
 *									       *
 *	See: 8M-ESP8266__Interface__Timer_Registers__Release_18-11-2014	       *
 *									       *
 *******************************************************************************/

#include "../classes/tm23a_1.h"

/*	Object				class, address
 */
#define hw_timer1			_tm23a, 0x60000600

/*	Class hardware registers	class, address, write mask, w1tc mask
 */
#define hw_reg__tm23a__load		_r32, 0x00, 0x7FFFFF, 0
#define hw_reg__tm23a__count		_r32, 0x04, 0x0,      0
#define hw_reg__tm23a__ctrl		_r32, 0x08, 0x0CD,    0
#define hw_reg__tm23a__flags		_r32, 0x0C, 0x1,      0x1

/*	Class logical registers
 */
#define hw_reg__tm23a_int		_cb1, _ctrl,  1, 8	// Interrupt status
#define hw_reg__tm23a_en		_cb1, _ctrl,  1, 7	// Enable timer
#define hw_reg__tm23a_arl		_cb1, _ctrl,  1, 6	// Auto-reload after 0
#define hw_reg__tm23a_psc		_cb1, _ctrl,  2, 2	// Prescaler
#define hw_reg__tm23a_irqtype		_cb1, _ctrl,  1, 0	// 0:Edge/1:Level interrupt

#define hw_reg__tm23a_load		_cb1, _load,  23, 0	// Reload value
#define hw_reg__tm23a_count		_cb1, _count, 23, 0	// Count

#define hw_reg__tm23a_ifclr		_cb1, _flags,  1, 0	// Write 1 to clear interrupt flag

#define hw_reg_timer1_ie		_xob1, shared, _edgeie, 1, 1


/*******************************************************************************
 *									       *
 *	Hardware timer 2						       *
 *									       *
 *	32-bit timer (up counter) clocked by the APB			       *
 *									       *
 *	See: 8M-ESP8266__Interface__Timer_Registers__Release_18-11-2014	       *
 *									       *
 *******************************************************************************/

/*	Object				class, address
 */
#define hw_timer2			_tm32a, 0x60000620

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define hw_reg__tm32a__load		_r32, 0x00, 0xFFFFFFFF, 0
#define hw_reg__tm32a__count		_r32, 0x04, 0x00000000, 0
#define hw_reg__tm32a__ctrl		_r32, 0x08, 0x000000CD, 0
#define hw_reg__tm32a__flags		_r32, 0x0C, 0x00000001, 1
#define hw_reg__tm32a__alarm		_r32, 0x10, 0xFFFFFFFF, 0

/*	Class logical registers
 */
#define hw_reg__tm32a_int		_cb1, _ctrl,  1, 8	// Interrupt status
#define hw_reg__tm32a_en		_cb1, _ctrl,  1, 7	// Enable timer
#define hw_reg__tm32a_arl		_cb1, _ctrl,  1, 6	// Auto-reload after 0
#define hw_reg__tm32a_psc		_cb1, _ctrl,  2, 2	// Prescaler
#define hw_reg__tm32a_irqtype		_cb1, _ctrl,  1, 0	// 0:Edge/1:Level interrupt

#define hw_reg__tm32a_load		_cb1, _load,  32, 0	// Reload value
#define hw_reg__tm32a_count		_cb1, _count, 32, 0	// Count

#define hw_reg__tm32a_ifclr		_cb1, _flags,  1, 0	// Write 1 to clear interrupt flag

//#define hw_reg_timer1_ie		_xob1, shared, _edgeie, 1, 1


/*******************************************************************************
 *									       *
 *	UARTS								       *
 *									       *
 *	See:								       *
 *	 * 8E-ESP8266__Interface_UART__EN_v0.2.pdf			       *
 *	 * 8F-ESP8266__Interface__UART_Registers_v0.1			       *
 *	 * Arduino/cores/esp8266/HardwareSerial.h			       *
 *	 * Arduino/cores/esp8266/HardwareSerial.cpp			       *
 *	 * Arduino/cores/esp8266/espressif_peri.h				       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Objects				class, address
 */
#define hw_uart0			_uarta, 0x60000000
#define hw_uart1			_uarta, 0x60000F00

/*	Class hardware registers	class, address, write mask, w1tc mask
 */
#define hw_reg__uarta__fifo		_r32, 0x00, 0x0, 0
#define hw_reg__uarta__ir		_r32, 0x04, 0x0, 0		// IRQ raw
#define hw_reg__uarta__if		_r32, 0x08, 0x0, 0		// IRQ stat
#define hw_reg__uarta__ie		_r32, 0x0C, 0x1FF, 0		// IRQ enable
#define hw_reg__uarta__ic		_r32, 0x10, 0x1FF, 0x1FF	// IRQ clear
#define hw_reg__uarta__clkdiv		_r32, 0x14, 0xFFFFF, 0
#define hw_reg__uarta__autobaud		_r32, 0x18, 0xFF01, 0
#define hw_reg__uarta__stat		_r32, 0x1C, 0x0, 0
#define hw_reg__uarta__conf0		_r32, 0x20, 0x01FE61FF, 0
#define hw_reg__uarta__conf1		_r32, 0x24, 0xFFFF7F7F, 0
#define hw_reg__uarta__lopulse		_r32, 0x28, 0x0, 0
#define hw_reg__uarta__hipulse		_r32, 0x2C, 0x0, 0
#define hw_reg__uarta__pulsnum		_r32, 0x30, 0x0, 0
#define hw_reg__uarta__date		_r32, 0x78, 0xFFFFFFFF, 0
#define hw_reg__uarta__id		_r32, 0x7C, 0xFFFFFFFF, 0

/*	Class logical registers
 */
#define hw_reg__uarta_rxqcnt		_cb1, _fifo, 8, 0	// RX fifo read position

#define hw_reg__uarta_irrxto		_cb1, _ir, 1, 8		// IRQ RX timeout
#define hw_reg__uarta_irrxbrk		_cb1, _ir, 1, 7		// IRQ break detected
#define hw_reg__uarta_ircts		_cb1, _ir, 1, 6		// IRQ CTS changed
#define hw_reg__uarta_irdsr		_cb1, _ir, 1, 5		// IRQ DSR changed
#define hw_reg__uarta_irrxof		_cb1, _ir, 1, 4		// IRQ RX overflow
#define hw_reg__uarta_irrxfe		_cb1, _ir, 1, 3		// IRQ frame error
#define hw_reg__uarta_irrxpe		_cb1, _ir, 1, 2		// IRQ parity error
#define hw_reg__uarta_irtxqe		_cb1, _ir, 1, 1		// IRQ TX fifo empty
#define hw_reg__uarta_irrxqf		_cb1, _ir, 1, 0		// IRQ RX fifo full

#define hw_reg__uarta_ifrxto		_cb1, _if, 1, 8		// IRQ RX timeout
#define hw_reg__uarta_ifrxbrk		_cb1, _if, 1, 7		// IRQ break detected
#define hw_reg__uarta_ifcts		_cb1, _if, 1, 6		// IRQ CTS changed
#define hw_reg__uarta_ifdsr		_cb1, _if, 1, 5		// IRQ DSR changed
#define hw_reg__uarta_ifrxof		_cb1, _if, 1, 4		// IRQ RX overflow
#define hw_reg__uarta_ifrxfe		_cb1, _if, 1, 3		// IRQ frame error
#define hw_reg__uarta_ifrxpe		_cb1, _if, 1, 2		// IRQ parity error
#define hw_reg__uarta_iftxqe		_cb1, _if, 1, 1		// IRQ TX fifo empty
#define hw_reg__uarta_ifrxqf		_cb1, _if, 1, 0		// IRQ RX fifo full

#define hw_reg__uarta_ierxto		_cb1, _ie, 1, 8		// IRQ RX timeout
#define hw_reg__uarta_ierxbrk		_cb1, _ie, 1, 7		// IRQ break detected
#define hw_reg__uarta_iects		_cb1, _ie, 1, 6		// IRQ CTS changed
#define hw_reg__uarta_iedsr		_cb1, _ie, 1, 5		// IRQ DSR changed
#define hw_reg__uarta_ierxof		_cb1, _ie, 1, 4		// IRQ RX overflow
#define hw_reg__uarta_ierxfe		_cb1, _ie, 1, 3		// IRQ frame error
#define hw_reg__uarta_ierxpe		_cb1, _ie, 1, 2		// IRQ parity error
#define hw_reg__uarta_ietxqe		_cb1, _ie, 1, 1		// IRQ TX fifo empty
#define hw_reg__uarta_ierxqf		_cb1, _ie, 1, 0		// IRQ RX fifo full

#define hw_reg__uarta_icrxto		_cb1, _ic, 1, 8		// IRQ RX timeout
#define hw_reg__uarta_icrxbrk		_cb1, _ic, 1, 7		// IRQ break detected
#define hw_reg__uarta_iccts		_cb1, _ic, 1, 6		// IRQ CTS changed
#define hw_reg__uarta_icdsr		_cb1, _ic, 1, 5		// IRQ DSR changed
#define hw_reg__uarta_icrxof		_cb1, _ic, 1, 4		// IRQ RX overflow
#define hw_reg__uarta_icrxfe		_cb1, _ic, 1, 3		// IRQ frame error
#define hw_reg__uarta_icrxpe		_cb1, _ic, 1, 2		// IRQ parity error
#define hw_reg__uarta_ictxqe		_cb1, _ic, 1, 1		// IRQ TX fifo empty
#define hw_reg__uarta_icrxqf		_cb1, _ic, 1, 0		// IRQ RX fifo full

#define hw_reg__uarta_clkdiv		_cb1, _clkdiv, 20, 0	// Baudrate divider

#define hw_reg__uarta_stxd		_cb1, _stat, 1, 31	// TX PIN Level
#define hw_reg__uarta_srtsn		_cb1, _stat, 1, 30	// RTS PIN Level
#define hw_reg__uarta_sdtrn		_cb1, _stat, 1, 29	// DTR PIN Level
#define hw_reg__uarta_stxcnt		_cb1, _stat, 8, 16	// TX FIFO COUNT (8bit)
#define hw_reg__uarta_srxd		_cb1, _stat, 1, 15	// RX PIN Level
#define hw_reg__uarta_sctsn		_cb1, _stat, 1, 14	// CTS PIN Level
#define hw_reg__uarta_sdsrn		_cb1, _stat, 1, 13	// DSR PIN Level
#define hw_reg__uarta_srxcnt		_cb1, _stat, 8,	 0	// RX FIFO COUNT (8bit)

#define hw_reg__uarta_cdtri		_cb1, _conf0, 1, 24	// Invert DTR
#define hw_reg__uarta_crtsi		_cb1, _conf0, 1, 23	// Invert RTS
#define hw_reg__uarta_ctxi		_cb1, _conf0, 1, 22	// Invert TX
#define hw_reg__uarta_cdsri		_cb1, _conf0, 1, 21	// Invert DSR
#define hw_reg__uarta_cctsi		_cb1, _conf0, 1, 20	// Invert CTS
#define hw_reg__uarta_crxi		_cb1, _conf0, 1, 19	// Invert RX
#define hw_reg__uarta_ctxrst		_cb1, _conf0, 1, 18	// Reset TX FIFO
#define hw_reg__uarta_crxrst		_cb1, _conf0, 1, 17	// Reset RX FIFO
#define hw_reg__uarta_ctxhfe		_cb1, _conf0, 1, 15	// Enable TX harware flow
#define hw_reg__uarta_clbe		_cb1, _conf0, 1, 14	// Enable loopback
#define hw_reg__uarta_cbrk		_cb1, _conf0, 1,  8	// Keep TXD low (BRK)
#define hw_reg__uarta_cswdtr		_cb1, _conf0, 1,  7	// Assert DTR
#define hw_reg__uarta_cswrts		_cb1, _conf0, 1,  6	// Assert RTS
#define hw_reg__uarta_csbn		_cb1, _conf0, 2,  4	// StopBits Count (2bit) 0:disable, 1:1bit, 2:1.5bit, 3:2bit
#define hw_reg__uarta_cbn		_cb1, _conf0, 2,  2	// DataBits Count (2bin) 0:5bit, 1:6bit, 2:7bit, 3:8bit
#define hw_reg__uarta_cpae		_cb1, _conf0, 1,  1	// Parity Enable
#define hw_reg__uarta_cpa		_cb1, _conf0, 1,  0	// Parity 0:even, 1:odd
#define hw_reg__uarta_cpx		_cb1, _conf0, 2,  0	// HWA convenience

#define hw_reg__uarta_ctoe		_cb1, _conf1, 1, 31	// RX TimeOut Enable
#define hw_reg__uarta_ctot		_cb1, _conf1, 7, 24	// RX TimeOut Treshold (7bit)
#define hw_reg__uarta_crxhfe		_cb1, _conf1, 1, 23	// RX Harware Flow Enable
#define hw_reg__uarta_crxhft		_cb1, _conf1, 7, 16	// RX Harware Flow Treshold (7bit)
#define hw_reg__uarta_cfet		_cb1, _conf1, 7,  8	// TX FIFO Empty Treshold (7bit)
#define hw_reg__uarta_cfft		_cb1, _conf1, 7,  0	// RX FIFO Full Treshold (7bit)

#define hw_reg__uarta_swap		_xob1, shared, _swap, 1, 2

// #define hw_reg__uarta_		_cb1, _, 1,	//

/*  Relatives
 */
//#define hw_uart0pin_txd			hw_gpio1
//#define hw_uart0pin_rxd			hw_gpio3
#define hw_uart0_txd		gpio1


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/

#if !defined __ASSEMBLER__

/* This structure is instanciated by hwa( begin ) or hwa( begin_from_reset ) and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;
  hwa_p16a_t	port0 ;
  hwa_rtca_t	rtc ;
  hwa_pcfa_t	gpio0_cf ;
  hwa_pcfa_t	gpio1_cf ;
  hwa_pcfa_t	gpio2_cf ;
  hwa_pcfa_t	gpio3_cf ;
  hwa_pcfa_t	gpio4_cf ;
  hwa_pcfa_t	gpio5_cf ;
  hwa_pcfa_t	gpio6_cf ;
  hwa_pcfa_t	gpio7_cf ;
  hwa_pcfa_t	gpio8_cf ;
  hwa_pcfa_t	gpio9_cf ;
  hwa_pcfa_t	gpio10_cf ;
  hwa_pcfa_t	gpio11_cf ;
  hwa_pcfa_t	gpio12_cf ;
  hwa_pcfa_t	gpio13_cf ;
  hwa_pcfa_t	gpio14_cf ;
  hwa_pcfa_t	gpio15_cf ;
  hwa_pcfa_t	gpio16_cf ;
  hwa_tm23a_t	timer1 ;
  hwa_uarta_t	uart0 ;
} hwa_t ;


#include "../hwa_2.h"
#include "../classes/rtca_2.h"
#include "../classes/pcfa_2.h"
#include "../classes/pcfb_2.h"
#include "../classes/p16a_2.h"
#include "../classes/io1a_2.h"
#include "../classes/io1b_2.h"
#include "../classes/tm23a_2.h"
#include "../classes/uarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup_o( shared );
  _hwa_setup_o( port0 );
  _hwa_setup_o( rtc );
  _hwa_setup_o( gpio0_cf );
  _hwa_setup_o( gpio1_cf );
  _hwa_setup_o( gpio2_cf );
  _hwa_setup_o( gpio3_cf );
  _hwa_setup_o( gpio4_cf );
  _hwa_setup_o( gpio5_cf );
  _hwa_setup_o( gpio6_cf );
  _hwa_setup_o( gpio7_cf );
  _hwa_setup_o( gpio8_cf );
  _hwa_setup_o( gpio9_cf );
  _hwa_setup_o( gpio10_cf );
  _hwa_setup_o( gpio11_cf );
  _hwa_setup_o( gpio12_cf );
  _hwa_setup_o( gpio13_cf );
  _hwa_setup_o( gpio14_cf );
  _hwa_setup_o( gpio15_cf );

  _hwa_setup_o( timer1 );
  _hwa_setup_o( uart0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init_o( shared );
  _hwa_init_o( port0 );
  _hwa_init_o( rtc );
  /* _hwa_init_o( gpio0_cf ); */
  /* _hwa_init_o( gpio1_cf ); */
  /* _hwa_init_o( gpio2_cf ); */
  /* _hwa_init_o( gpio3_cf ); */
  /* _hwa_init_o( gpio4_cf ); */
  /* _hwa_init_o( gpio5_cf ); */
  /* _hwa_init_o( gpio6_cf ); */
  /* _hwa_init_o( gpio7_cf ); */
  /* _hwa_init_o( gpio8_cf ); */
  /* _hwa_init_o( gpio9_cf ); */
  /* _hwa_init_o( gpio10_cf ); */
  /* _hwa_init_o( gpio11_cf ); */
  /* _hwa_init_o( gpio12_cf ); */
  /* _hwa_init_o( gpio13_cf ); */
  /* _hwa_init_o( gpio14_cf ); */
  /* _hwa_init_o( gpio15_cf ); */
  _hwa_init_o( timer1 );
  _hwa_init_o( uart0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit_o( gpio0_cf );
  _hwa_commit_o( gpio1_cf );
  _hwa_commit_o( gpio2_cf );
  _hwa_commit_o( gpio3_cf );
  _hwa_commit_o( gpio4_cf );
  _hwa_commit_o( gpio5_cf );
  _hwa_commit_o( gpio6_cf );
  _hwa_commit_o( gpio7_cf );
  _hwa_commit_o( gpio8_cf );
  _hwa_commit_o( gpio9_cf );
  _hwa_commit_o( gpio10_cf );
  _hwa_commit_o( gpio11_cf );
  _hwa_commit_o( gpio12_cf );
  _hwa_commit_o( gpio13_cf );
  _hwa_commit_o( gpio14_cf );
  _hwa_commit_o( gpio15_cf );

  _hwa_commit_o( port0 );
  _hwa_commit_o( rtc );
  _hwa_commit_o( timer1 );
  _hwa_commit_o( uart0 );

  //  _hwa_commit_r( shared, _edgeie ); /* Process IRQ at last */
  _hwa_commit_o( shared );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page esp8266
 * <br>
 */
