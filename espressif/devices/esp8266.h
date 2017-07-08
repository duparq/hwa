
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
 * @page esp8266 ESP8266
 */
#define hw_syshz				80000000
#define hw_apbhz				hw_syshz

#define hw_uptime_us				(*(volatile uint32_t*)0x3ff20c00)
#define hw_uptime				(hw_uptime_us / 1e6)


/*******************************************************************************
 *									       *
 *	Peripherals							       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section esp8266_peripherals Peripherals
 *
 * __Note__ All the peripherals are not completely implemented yet.
 *
 * Object name		  | Class		  | Comments
 * :----------------------|-----------------------|:--------------------------------------
 * `port0`	 | @ref espressif_p16a "_p16a"	  | General purpose I/O port
 * `timer1`	 | @ref espressif_tm23a "_tm23a"  | 23-bit timer
 * `uart0`	 | @ref esp8266_uarta "_uarta"	  | UART
 */


/*******************************************************************************
 *									       *
 *	Interrupts							       *
 *									       *
 *******************************************************************************/
/**
 * @ingroup esp8266_interrupts
 * @brief Definition of the interrupts
 */
/*  Interrupt definitions
 *
 *  'vector' is used to store the type of interrupt
 *
 *						class, vector, object, ie, if
 */
#define _hw_irq_timer1_nmi		_irq, nmi, timer1, ie,
#define _hw_irq_timer1_irq		_irq,	9, timer1, ie,


/*  ESP8266 interrupts are processed through OS calls to user service routines
 */
#define _os_handleirq_hw_timer1_nmi(fn)		NmiTimSetFunc(fn)
#define _os_handleirq_hw_timer1_9(fn)		ets_isr_attach(9, fn, 0)

extern void NmiTimSetFunc(void (*isr)(void));
extern void ets_isr_unmask(unsigned intr);


/**
 * @ingroup public_irq_instructions
 * @brief Declaration of an ISR
 *
 * The `os_handle_irq()` instruction declares a user ISR for an IRQ.
 *
 * @code
 * os_handle_irq( hw_timer1, irq, ev_timer );
 * @endcode
 * @hideinitializer
 */
#define _hw_mtd_os_handle_irq__irq	, _os_handle_irq

#define os_handle_irq(...)		_os_handleirq_2(hw_irqx(__VA_ARGS__,))
#define _os_handleirq_2(...)		HW_G2(_os_handleirq,HW_IS(_irq,__VA_ARGS__))(__VA_ARGS__)
#define _os_handleirq_0(...)		__VA_ARGS__
#define _os_handleirq_1(t,...)		_os_handle_irq(__VA_ARGS__)

#define _os_handle_irq(v,o,ie,if,fn,...)	HW_TX(_os_handleirq_##o##_##v(fn),__VA_ARGS__)


/*******************************************************************************
 *									       *
 *	Shared registers						       *
 *									       *
 *	This is an object used to gather hardware registers shared	       *
 *	by several objects						       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_class__shared
#define _hw_reg_shared			_shared, 0x3FF00000, 0x3FF00000

/*	Object hardware registers	class, address, write mask, w1tc mask
 */
#define _hw_reg_shared__edgeie		_r32, 0x04, 0xFFFFFFFF, 0
#define _hw_reg_shared__swap		_r32, 0x28, 0xFFFFFFFF, 0

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


#define _hwa_setup__shared(o,i,a)	\
  _hwa_setup_reg( o, _edgeie );	\
  _hwa_setup_reg( o, _swap )

#define _hwa_init__shared(o,i,a)	\
  /* _edgeie is UNKNOWN and 0 causes errors */	\
  _hwa_init_reg( o, _swap, 0 )

#define _hwa_commit__shared(o,i,a)	\
  _hwa_commit_reg( o, _edgeie );	\
  _hwa_commit_reg( o, _swap )

#endif


/*******************************************************************************
 *									       *
 *	GPIO ports							       *
 *									       *
 *******************************************************************************/

/*	Objects				class, id, address
 */
#include "../classes/p16a_1.h"
#include "../classes/io1a_1.h"

/*	Object				class, id, address
 */
#define _hw_def_port0			_p16a, 101, 0x60000300


/*	Class hardware registers	class, address, write mask, flags mask
 *
 *	See:
 *	  * ESP8266_GPIO_Register_141105.ods
 *	  * 2C-ESP8266__SDK__Programming Guide__EN_v1.4
 *	  * 0D-ESP8266__Pin_List__Release_15-11-2014.ods
 *	  * ESP8266_RTOS_SDK/blob/master/examples/driver_lib/driver/gpio.c
 */
#define _hw_reg__p16a__out		_r32, 0x00, 0xFFFFFFFF, 0
#define _hw_reg__p16a__outw1ts		_r32, 0x04, 0x0000FFFF, 0
#define _hw_reg__p16a__outw1tc		_r32, 0x08, 0x0000FFFF, 0
#define _hw_reg__p16a__enb		_r32, 0x0C, 0x003FFFFF, 0
#define _hw_reg__p16a__enbw1ts		_r32, 0x10, 0x0000FFFF, 0
#define _hw_reg__p16a__enbw1tc		_r32, 0x14, 0x0000FFFF, 0
#define _hw_reg__p16a__in		_r32, 0x18, 0x00000000, 0
#define _hw_reg__p16a__ie		_r32, 0x1C, 0x0000FFFF, 0
#define _hw_reg__p16a__iew1ts		_r32, 0x20, 0x0000FFFF, 0
#define _hw_reg__p16a__iew1tc		_r32, 0x24, 0x0000FFFF, 0

/*	Class logical registers		class, reg, bn, bp
 */
#define _hw_reg__p16a_btsel		_cb1, _out,	16, 16
#define _hw_reg__p16a_out		_cb1, _out,	16,  0
#define _hw_reg__p16a_outw1ts		_cb1, _outw1ts, 16,  0
#define _hw_reg__p16a_outw1tc		_cb1, _outw1tc, 16,  0

#define _hw_reg__p16a_sdiosel		_cb1, _enb,	 6, 16
#define _hw_reg__p16a_enb		_cb1, _enb,	16,  0
#define _hw_reg__p16a_enbw1ts		_cb1, _enbw1ts, 16,  0
#define _hw_reg__p16a_enbw1tc		_cb1, _enbw1tc, 16,  0

#define _hw_reg__p16a_strapping		_cb1, _in,	16, 16
#define _hw_reg__p16a_in		_cb1, _in,	16,  0

#define _hw_reg__p16a_ie		_cb1, _ie,	16, 16
#define _hw_reg__p16a_iew1ts		_cb1, _iew1ts,	16, 16
#define _hw_reg__p16a_iew1tc		_cb1, _iew1tc,	16, 16


/*******************************************************************************
 *									       *
 *	I/O pins							       *
 *									       *
 *******************************************************************************/

/**
 * @page esp8266
 * @section esp8266_pins Pins
 *
 * Each pin can be connected to different signals with the `hw(configure,)` or
 * `hwa(configure,...)` instruction.
 *
 * Pin	  | HWA name	    | Class			  | Functions
 * -------|-----------------|-----------------------------|-------------
 * GPIO0  | `gpio0`	| @ref esp8266_io1a "_io1a" | `gpio` / `spi_cs2` / `clk_out`
 * GPIO1  | `gpio1`	| @ref esp8266_io1a "_io1a" | `gpio` / `uart0_txd` / `spi_cs1` / `clk_rtc`
 * GPIO2  | `gpio2`	| @ref esp8266_io1a "_io1a" | `gpio` / `i2so_ws` / `uart1_txd` / `uart0_txd`
 * GPIO3  | `gpio3`	| @ref esp8266_io1a "_io1a" | `gpio` / `uart0_rxd` / `i2so_data` / `fn_clk_xtal`
 * GPIO4  | `gpio4`	| @ref esp8266_io1a "_io1a" | `gpio` / `clk_xtal`
 * GPIO5  | `gpio5`	| @ref esp8266_io1a "_io1a" | `gpio` / `clk_rtc`
 * GPIO6  | `gpio6`	| @ref esp8266_io1a "_io1a" | `gpio` / `sd_clk` / `spi_clk` / `uart1_cts`
 * GPIO7  | `gpio7`	| @ref esp8266_io1a "_io1a" | `gpio` / `sd_data0` / `spi_q` / `uart1_txd`
 * GPIO8  | `gpio8`	| @ref esp8266_io1a "_io1a" | `gpio` / `sd_data1` / `spi_d` / `uart1_rxd`
 * GPIO9  | `gpio9`	| @ref esp8266_io1a "_io1a" | `gpio` / `sd_data2` / `spi_hd` / `hspi_hd`
 * GPIO10 | `gpio10` | @ref esp8266_io1a "_io1a" | `gpio` / `sd_data3` / `spi_wp` / `hspi_wp`
 * GPIO11 | `gpio11` | @ref esp8266_io1a "_io1a" | `gpio` / `sd_cmd` / `spi_cs0` / `uart1_rts`
 * GPIO12 | `gpio12` | @ref esp8266_io1a "_io1a" | `gpio` / `mtdi` / `i2si_data` / `hspiq_miso` / `uart0_dtr`
 * GPIO13 | `gpio13` | @ref esp8266_io1a "_io1a" | `gpio` / `mtck` / `i2s_bck` / `hspi_mosi` / `uart0_cts`
 * GPIO14 | `gpio14` | @ref esp8266_io1a "_io1a" | `gpio` / `mtms` / `i2si_ws` / `hspi_clk` / `uart0_dsr`
 * GPIO15 | `gpio15` | @ref esp8266_io1a "_io1a" | `gpio` / `mtdo` / `i2so_bck` / `hspi_cs` / `uart0_rts`
 * GPIO16 | `gpio16` | @ref esp8266_io1a "_io1a" | `gpio` / `xpd_dcdc` / `ext_wakeup` / `deep_sleep` / `bt_xtal_en`
 */


/*	Pins				class, id, port, bn, bp
 */
#define _hw_def_gpio0			_io1a, 102, port0, 1, 0
#define _hw_def_gpio1			_io1a, 103, port0, 1, 1
#define _hw_def_gpio2			_io1a, 104, port0, 1, 2
#define _hw_def_gpio3			_io1a, 105, port0, 1, 3
#define _hw_def_gpio4			_io1a, 106, port0, 1, 4
#define _hw_def_gpio5			_io1a, 107, port0, 1, 5
#define _hw_def_gpio6			_io1a, 108, port0, 1, 6
#define _hw_def_gpio7			_io1a, 109, port0, 1, 7
#define _hw_def_gpio8			_io1a, 110, port0, 1, 8
#define _hw_def_gpio9			_io1a, 111, port0, 1, 9
#define _hw_def_gpio10			_io1a, 112, port0, 1, 10
#define _hw_def_gpio11			_io1a, 113, port0, 1, 11
#define _hw_def_gpio12			_io1a, 114, port0, 1, 12
#define _hw_def_gpio13			_io1a, 115, port0, 1, 13
#define _hw_def_gpio14			_io1a, 116, port0, 1, 14
#define _hw_def_gpio15			_io1a, 117, port0, 1, 15


/*	Pin GPIO16 (RTC_GPIO0 / xpd_dcdc) is of a different class
 *
 *	See esp_iot_sdk_v1.4.0/examples/driver_lib/driver/gpio16.c
 */
#define _hw_def_gpio16			_io1b, 118, port1, 1, 0


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
#define _hw_class__ionum

#define _hw_is_var_var			, 1

#define hw_pin_gpio(x)			HW_Y(hw_pin_gpio_var,_hw_is_var_##x)(x)

#define hw_pin_gpio_var_0(x)		hw_pin_gpio##x

#define hw_pin_gpio_var_1(x)		_ionum, 0, /* hw_port */, x


/*  Pin configuration objects
 *
 *	Each pin has a _pcfa object that handles its configuration.
 */
#include "../classes/pcfa_1.h"

#define _hw_def_gpio12_cf		_pcfa, 119, 0x60000804
#define _hw_def_gpio13_cf		_pcfa, 120, 0x60000808
#define _hw_def_gpio14_cf		_pcfa, 121, 0x6000080C
#define _hw_def_gpio15_cf		_pcfa, 122, 0x60000810
#define _hw_def_gpio3_cf		_pcfa, 123, 0x60000814
#define _hw_def_gpio1_cf		_pcfa, 124, 0x60000818
#define _hw_def_gpio6_cf		_pcfa, 125, 0x6000081c
#define _hw_def_gpio7_cf		_pcfa, 126, 0x60000820
#define _hw_def_gpio8_cf		_pcfa, 127, 0x60000824
#define _hw_def_gpio9_cf		_pcfa, 128, 0x60000828
#define _hw_def_gpio10_cf		_pcfa, 129, 0x6000082c
#define _hw_def_gpio11_cf		_pcfa, 130, 0x60000830
#define _hw_def_gpio0_cf		_pcfa, 131, 0x60000834
#define _hw_def_gpio2_cf		_pcfa, 132, 0x60000838
#define _hw_def_gpio4_cf		_pcfa, 133, 0x6000083C
#define _hw_def_gpio5_cf		_pcfa, 134, 0x60000840


/*  Pin functions
 *
 *	Each pin function is declared with the symbol _pinname_fn_function.
 *
 *	The value is the value of bits 8,5,4 (fn) in the I/O cf register.
 *
 *	The symbol _pinname_fns is used to build the error message when an
 *	unavailable function is chosen with hw_config().
 */
#define _hw_gpio0_fn_gpio		, 0
#define _hw_gpio0_fn_spi_cs2		, 1
#define _hw_gpio0_fn_clk_out		, 4 /* RESET */
#define _hw_gpio0_fns			"`gpio`, `spi_cs2`, or `clk_out`"

#define _hw_gpio1_fn_uart0_txd		, 0, _hwa_write_reg( uart0, swap, 0 );
#define _hw_gpio1_fn_spi_cs1		, 1
#define _hw_gpio1_fn_gpio		, 3
#define _hw_gpio1_fn_clk_rtc		, 4
#define _hw_gpio1_fns			"`gpio`, `uart0_txd`, `spi_cs1`, or `clk_rtc`"

#define _hw_gpio2_fn_gpio		, 0
#define _hw_gpio2_fn_i2so_ws		, 1
#define _hw_gpio2_fn_uart1_txd		, 2
#define _hw_gpio2_fn_uart0_txd		, 4, _hwa_write_reg( uart0, swap, 0 );
#define _hw_gpio2_fn_hw_uart0_txd	, 4
#define _hw_gpio2_fns			"`gpio`, `i2so_ws`, `uart1_txd`, or `uart0_txd`"

#define _hw_gpio3_fn_uart0_rxd		, 0, _hwa_write_reg( uart0, swap, 0 );
#define _hw_gpio3_fn_i2so_data		, 1
#define _hw_gpio3_fn_gpio		, 3
#define _hw_gpio3_fn_clk_xtal		, 4
#define _hw_gpio3_fns			"`gpio`, `uart0_rxd`, `i2so_data`, or `fn_clk_xtal`"

#define _hw_gpio4_fn_gpio		, 0
#define _hw_gpio4_fn_clk_xtal		, 1
#define _hw_gpio4_fns			"`gpio` or `clk_xtal`"

#define _hw_gpio5_fn_gpio		, 0
#define _hw_gpio5_fn_clk_rtc		, 1
#define _hw_gpio5_fns			"`gpio`, or `clk_rtc`"

#define _hw_gpio6_fn_sd_clk		, 0
#define _hw_gpio6_fn_spi_clk		, 1
#define _hw_gpio6_fn_gpio		, 3
#define _hw_gpio6_fn_uart1_cts		, 4
#define _hw_gpio6_fns			"`gpio`, `sd_clk`, `spi_clk`, or `uart1_cts`"

#define _hw_gpio7_fn_sd_data0		, 0
#define _hw_gpio7_fn_spi_q		, 1
#define _hw_gpio7_fn_gpio		, 3
#define _hw_gpio7_fn_uart1_txd		, 4
#define _hw_gpio7_fns			"`gpio`, `sd_data0`, `spi_q`, or `uart1_txd`"

#define _hw_gpio8_fn_sd_data1		, 0
#define _hw_gpio8_fn_spi_d		, 1
#define _hw_gpio8_fn_gpio		, 3
#define _hw_gpio8_fn_u1_rxd		, 4
#define _hw_gpio8_fns			"`gpio`, `sd_data1`, `spi_d`, or `u1_rxd`"

#define _hw_gpio9_fn_sd_data2		, 0
#define _hw_gpio9_fn_spi_hd		, 1
#define _hw_gpio9_fn_gpio		, 3
#define _hw_gpio9_fn_hspi_hd		, 4
#define _hw_gpio9_fns			"`gpio`, `sd_data2`, `spi_hd`, or `hspi_hd`"

#define _hw_gpio10_fn_sd_data3		, 0
#define _hw_gpio10_fn_spi_wp		, 1
#define _hw_gpio10_fn_gpio		, 3
#define _hw_gpio10_fn_hspi_wp		, 4
#define _hw_gpio10_fns			"`gpio`, `sd_data3`, `spi_wp`, or `hspi_wp`"

#define _hw_gpio11_fn_sd_cmd		, 0
#define _hw_gpio11_fn_spi_cs0		, 1
#define _hw_gpio11_fn_gpio		, 3
#define _hw_gpio11_fn_uart1_rts		, 4
#define _hw_gpio11_fns			"`gpio`, `sd_cmd`, `spi_cs0`, or `uart1_rts`"

#define _hw_gpio12_fn_mtdi		, 0
#define _hw_gpio12_fn_i2si_data		, 1
#define _hw_gpio12_fn_hspi_miso		, 2
#define _hw_gpio12_fn_gpio		, 3
#define _hw_gpio12_fn_uart0_dtr		, 4
#define _hw_gpio12_fns			"`gpio`, `mtdi`, `i2si_data`, `hspi_miso`, or `uart0_dtr`"

#define _hw_gpio13_fn_mtck		, 0
#define _hw_gpio13_fn_i2s_bck		, 1
#define _hw_gpio13_fn_hspi_mosi		, 2
#define _hw_gpio13_fn_gpio		, 3
#define _hw_gpio13_fn_uart0_cts		, 4
#define _hw_gpio13_fn_uart0_rxd		, 4, _hwa_write_reg( uart0, swap, 1 );
#define _hw_gpio13_fns			"`gpio`, `mtck`, `i2s_bck`, `hspi_mosi`, or `uart0_cts`"

#define _hw_gpio14_fn_mtms		, 0
#define _hw_gpio14_fn_i2si_ws		, 1
#define _hw_gpio14_fn_hspi_clk		, 2
#define _hw_gpio14_fn_gpio		, 3
#define _hw_gpio14_fn_uart0_dsr		, 4
#define _hw_gpio14_fns			"`gpio`, `mtms`, `i2si_ws`, `hspi_clk`, or `uart0_dsr`"

#define _hw_gpio15_fn_mtdo		, 0
#define _hw_gpio15_fn_i2so_bck		, 1
#define _hw_gpio15_fn_hspi_cs		, 2
#define _hw_gpio15_fn_gpio		, 3
#define _hw_gpio15_fn_uart0_rts		, 4
#define _hw_gpio15_fn_uart0_txd		, 4, _hwa_write_reg( uart0, swap, 1 );
#define _hw_gpio15_fns			"`gpio`, `mtdo`, `i2so_bck`, `hspi_cs`, `uart0_rts`, or `uart0_txd`"

#define _hw_gpio16_fn_xpd_dcdc		, 0
#define _hw_gpio16_fn_rtc_gpio0		, 1
#define _hw_gpio16_fn_gpio		, 1
#define _hw_gpio16_fn_ext_wakeup	, 2
#define _hw_gpio16_fn_deep_sleep	, 3
#define _hw_gpio16_fn_bt_xtal_en	, 4
#define _hw_gpio16_fns			"`gpio`, `xpd_dcdc`, `ext_wakeup`, `deep_sleep`, or `bt_xtal_en`"


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

/*	Object				class, id, address
 */
#define _hw_def_timer1			_tm23a, 135, 0x60000600

/*	Class hardware registers	class, address, write mask, w1tc mask
 */
#define _hw_reg__tm23a__load		_r32, 0x00, 0x7FFFFF, 0
#define _hw_reg__tm23a__count		_r32, 0x04, 0x0,      0
#define _hw_reg__tm23a__ctrl		_r32, 0x08, 0x0CD,    0
#define _hw_reg__tm23a__flags		_r32, 0x0C, 0x1,      0x1

/*	Class logical registers
 */
#define _hw_reg__tm23a_int		_cb1, _ctrl,  1, 8	// Interrupt status
#define _hw_reg__tm23a_en		_cb1, _ctrl,  1, 7	// Enable timer
#define _hw_reg__tm23a_arl		_cb1, _ctrl,  1, 6	// Auto-reload after 0
#define _hw_reg__tm23a_psc		_cb1, _ctrl,  2, 2	// Prescaler
#define _hw_reg__tm23a_irqtype		_cb1, _ctrl,  1, 0	// 0:Edge/1:Level interrupt

#define _hw_reg__tm23a_load		_cb1, _load,  23, 0	// Reload value
#define _hw_reg__tm23a_count		_cb1, _count, 23, 0	// Count

#define _hw_reg__tm23a_ifclr		_cb1, _flags,  1, 0	// Write 1 to clear interrupt flag

#define _hw_reg_timer1_ie		_xob1, shared, _edgeie, 1, 1


/*******************************************************************************
 *									       *
 *	Hardware timer 2						       *
 *									       *
 *	32-bit timer (up counter) clocked by the APB			       *
 *									       *
 *	See: 8M-ESP8266__Interface__Timer_Registers__Release_18-11-2014	       *
 *									       *
 *******************************************************************************/

/*	Object				class, id, address
 */
#define _hw_def_timer2			_tm32a, 136, 0x60000620

/*	Class hardware registers	class, address, write mask, flags mask
 */
#define _hw_reg__tm32a__load		_r32, 0x00, 0xFFFFFFFF, 0
#define _hw_reg__tm32a__count		_r32, 0x04, 0x00000000, 0
#define _hw_reg__tm32a__ctrl		_r32, 0x08, 0x000000CD, 0
#define _hw_reg__tm32a__flags		_r32, 0x0C, 0x00000001, 1
#define _hw_reg__tm32a__alarm		_r32, 0x10, 0xFFFFFFFF, 0

/*	Class logical registers
 */
#define _hw_reg__tm32a_int		_cb1, _ctrl,  1, 8	// Interrupt status
#define _hw_reg__tm32a_en		_cb1, _ctrl,  1, 7	// Enable timer
#define _hw_reg__tm32a_arl		_cb1, _ctrl,  1, 6	// Auto-reload after 0
#define _hw_reg__tm32a_psc		_cb1, _ctrl,  2, 2	// Prescaler
#define _hw_reg__tm32a_irqtype		_cb1, _ctrl,  1, 0	// 0:Edge/1:Level interrupt

#define _hw_reg__tm32a_load		_cb1, _load,  32, 0	// Reload value
#define _hw_reg__tm32a_count		_cb1, _count, 32, 0	// Count

#define _hw_reg__tm32a_ifclr		_cb1, _flags,  1, 0	// Write 1 to clear interrupt flag

//#define _hw_reg_timer1_ie		_xob1, shared, _edgeie, 1, 1


/*******************************************************************************
 *									       *
 *	UARTS								       *
 *									       *
 *	See:								       *
 *	 * 8E-ESP8266__Interface_UART__EN_v0.2.pdf			       *
 *	 * 8F-ESP8266__Interface__UART_Registers_v0.1			       *
 *	 * Arduino/cores/esp8266/HardwareSerial.h			       *
 *	 * Arduino/cores/esp8266/HardwareSerial.cpp			       *
 *	 * Arduino/cores/esp8266/esp8266_peri.h				       *
 *									       *
 *******************************************************************************/

#include "../classes/uarta_1.h"

/*	Objects				class, id, address
 */
#define _hw_def_uart0			_uarta, 137, 0x60000000
#define _hw_def_uart1			_uarta, 138, 0x60000F00

/*	Class hardware registers	class, address, write mask, w1tc mask
 */
#define _hw_reg__uarta__fifo		_r32, 0x00, 0x0, 0
#define _hw_reg__uarta__ir		_r32, 0x04, 0x0, 0		// IRQ raw
#define _hw_reg__uarta__if		_r32, 0x08, 0x0, 0		// IRQ stat
#define _hw_reg__uarta__ie		_r32, 0x0C, 0x1FF, 0		// IRQ enable
#define _hw_reg__uarta__ic		_r32, 0x10, 0x1FF, 0x1FF	// IRQ clear
#define _hw_reg__uarta__clkdiv		_r32, 0x14, 0xFFFFF, 0
#define _hw_reg__uarta__autobaud	_r32, 0x18, 0xFF01, 0
#define _hw_reg__uarta__stat		_r32, 0x1C, 0x0, 0
#define _hw_reg__uarta__conf0		_r32, 0x20, 0x01FE61FF, 0
#define _hw_reg__uarta__conf1		_r32, 0x24, 0xFFFF7F7F, 0
#define _hw_reg__uarta__lopulse		_r32, 0x28, 0x0, 0
#define _hw_reg__uarta__hipulse		_r32, 0x2C, 0x0, 0
#define _hw_reg__uarta__pulsnum		_r32, 0x30, 0x0, 0
#define _hw_reg__uarta__date		_r32, 0x78, 0xFFFFFFFF, 0
#define _hw_reg__uarta__id		_r32, 0x7C, 0xFFFFFFFF, 0

/*	Class logical registers
 */
#define _hw_reg__uarta_rxqcnt		_cb1, _fifo, 8, 0	// RX fifo read position

#define _hw_reg__uarta_irrxto		_cb1, _ir, 1, 8		// IRQ RX timeout
#define _hw_reg__uarta_irrxbrk		_cb1, _ir, 1, 7		// IRQ break detected
#define _hw_reg__uarta_ircts		_cb1, _ir, 1, 6		// IRQ CTS changed
#define _hw_reg__uarta_irdsr		_cb1, _ir, 1, 5		// IRQ DSR changed
#define _hw_reg__uarta_irrxof		_cb1, _ir, 1, 4		// IRQ RX overflow
#define _hw_reg__uarta_irrxfe		_cb1, _ir, 1, 3		// IRQ frame error
#define _hw_reg__uarta_irrxpe		_cb1, _ir, 1, 2		// IRQ parity error
#define _hw_reg__uarta_irtxqe		_cb1, _ir, 1, 1		// IRQ TX fifo empty
#define _hw_reg__uarta_irrxqf		_cb1, _ir, 1, 0		// IRQ RX fifo full

#define _hw_reg__uarta_ifrxto		_cb1, _if, 1, 8		// IRQ RX timeout
#define _hw_reg__uarta_ifrxbrk		_cb1, _if, 1, 7		// IRQ break detected
#define _hw_reg__uarta_ifcts		_cb1, _if, 1, 6		// IRQ CTS changed
#define _hw_reg__uarta_ifdsr		_cb1, _if, 1, 5		// IRQ DSR changed
#define _hw_reg__uarta_ifrxof		_cb1, _if, 1, 4		// IRQ RX overflow
#define _hw_reg__uarta_ifrxfe		_cb1, _if, 1, 3		// IRQ frame error
#define _hw_reg__uarta_ifrxpe		_cb1, _if, 1, 2		// IRQ parity error
#define _hw_reg__uarta_iftxqe		_cb1, _if, 1, 1		// IRQ TX fifo empty
#define _hw_reg__uarta_ifrxqf		_cb1, _if, 1, 0		// IRQ RX fifo full

#define _hw_reg__uarta_ierxto		_cb1, _ie, 1, 8		// IRQ RX timeout
#define _hw_reg__uarta_ierxbrk		_cb1, _ie, 1, 7		// IRQ break detected
#define _hw_reg__uarta_iects		_cb1, _ie, 1, 6		// IRQ CTS changed
#define _hw_reg__uarta_iedsr		_cb1, _ie, 1, 5		// IRQ DSR changed
#define _hw_reg__uarta_ierxof		_cb1, _ie, 1, 4		// IRQ RX overflow
#define _hw_reg__uarta_ierxfe		_cb1, _ie, 1, 3		// IRQ frame error
#define _hw_reg__uarta_ierxpe		_cb1, _ie, 1, 2		// IRQ parity error
#define _hw_reg__uarta_ietxqe		_cb1, _ie, 1, 1		// IRQ TX fifo empty
#define _hw_reg__uarta_ierxqf		_cb1, _ie, 1, 0		// IRQ RX fifo full

#define _hw_reg__uarta_icrxto		_cb1, _ic, 1, 8		// IRQ RX timeout
#define _hw_reg__uarta_icrxbrk		_cb1, _ic, 1, 7		// IRQ break detected
#define _hw_reg__uarta_iccts		_cb1, _ic, 1, 6		// IRQ CTS changed
#define _hw_reg__uarta_icdsr		_cb1, _ic, 1, 5		// IRQ DSR changed
#define _hw_reg__uarta_icrxof		_cb1, _ic, 1, 4		// IRQ RX overflow
#define _hw_reg__uarta_icrxfe		_cb1, _ic, 1, 3		// IRQ frame error
#define _hw_reg__uarta_icrxpe		_cb1, _ic, 1, 2		// IRQ parity error
#define _hw_reg__uarta_ictxqe		_cb1, _ic, 1, 1		// IRQ TX fifo empty
#define _hw_reg__uarta_icrxqf		_cb1, _ic, 1, 0		// IRQ RX fifo full

#define _hw_reg__uarta_clkdiv		_cb1, _clkdiv, 20, 0	// Baudrate divider

#define _hw_reg__uarta_stxd		_cb1, _stat, 1, 31	// TX PIN Level
#define _hw_reg__uarta_srtsn		_cb1, _stat, 1, 30	// RTS PIN Level
#define _hw_reg__uarta_sdtrn		_cb1, _stat, 1, 29	// DTR PIN Level
#define _hw_reg__uarta_stxcnt		_cb1, _stat, 8, 16	// TX FIFO COUNT (8bit)
#define _hw_reg__uarta_srxd		_cb1, _stat, 1, 15	// RX PIN Level
#define _hw_reg__uarta_sctsn		_cb1, _stat, 1, 14	// CTS PIN Level
#define _hw_reg__uarta_sdsrn		_cb1, _stat, 1, 13	// DSR PIN Level
#define _hw_reg__uarta_srxcnt		_cb1, _stat, 8,	 0	// RX FIFO COUNT (8bit)

#define _hw_reg__uarta_cdtri		_cb1, _conf0, 1, 24	// Invert DTR
#define _hw_reg__uarta_crtsi		_cb1, _conf0, 1, 23	// Invert RTS
#define _hw_reg__uarta_ctxi		_cb1, _conf0, 1, 22	// Invert TX
#define _hw_reg__uarta_cdsri		_cb1, _conf0, 1, 21	// Invert DSR
#define _hw_reg__uarta_cctsi		_cb1, _conf0, 1, 20	// Invert CTS
#define _hw_reg__uarta_crxi		_cb1, _conf0, 1, 19	// Invert RX
#define _hw_reg__uarta_ctxrst		_cb1, _conf0, 1, 18	// Reset TX FIFO
#define _hw_reg__uarta_crxrst		_cb1, _conf0, 1, 17	// Reset RX FIFO
#define _hw_reg__uarta_ctxhfe		_cb1, _conf0, 1, 15	// Enable TX harware flow
#define _hw_reg__uarta_clbe		_cb1, _conf0, 1, 14	// Enable loopback
#define _hw_reg__uarta_cbrk		_cb1, _conf0, 1,  8	// Keep TXD low (BRK)
#define _hw_reg__uarta_cswdtr		_cb1, _conf0, 1,  7	// Assert DTR
#define _hw_reg__uarta_cswrts		_cb1, _conf0, 1,  6	// Assert RTS
#define _hw_reg__uarta_csbn		_cb1, _conf0, 2,  4	// StopBits Count (2bit) 0:disable, 1:1bit, 2:1.5bit, 3:2bit
#define _hw_reg__uarta_cbn		_cb1, _conf0, 2,  2	// DataBits Count (2bin) 0:5bit, 1:6bit, 2:7bit, 3:8bit
#define _hw_reg__uarta_cpae		_cb1, _conf0, 1,  1	// Parity Enable
#define _hw_reg__uarta_cpa		_cb1, _conf0, 1,  0	// Parity 0:even, 1:odd
#define _hw_reg__uarta_cpx		_cb1, _conf0, 2,  0	// HWA convenience

#define _hw_reg__uarta_ctoe		_cb1, _conf1, 1, 31	// RX TimeOut Enable
#define _hw_reg__uarta_ctot		_cb1, _conf1, 7, 24	// RX TimeOut Treshold (7bit)
#define _hw_reg__uarta_crxhfe		_cb1, _conf1, 1, 23	// RX Harware Flow Enable
#define _hw_reg__uarta_crxhft		_cb1, _conf1, 7, 16	// RX Harware Flow Treshold (7bit)
#define _hw_reg__uarta_cfet		_cb1, _conf1, 7,  8	// TX FIFO Empty Treshold (7bit)
#define _hw_reg__uarta_cfft		_cb1, _conf1, 7,  0	// RX FIFO Full Treshold (7bit)

#define _hw_reg__uarta_swap		_xob1, shared, _swap, 1, 2

// #define _hw_reg__uarta_		_cb1, _, 1,	//

/*  Relatives
 */
//#define hw_uart0pin_txd			hw_gpio1
//#define hw_uart0pin_rxd			hw_gpio3


/*******************************************************************************
 *									       *
 *	HWA context							       *
 *									       *
 *******************************************************************************/

#if !defined __ASSEMBLER__

/**
 * @brief The HWA context
 *
 * This structure is instanciated by hwa_begin() or hwa_begin_from_reset() and
 * used by all HWA asynchronous instructions to bufferize hardware accesses.
 */
typedef struct {
  uint8_t	commit ;	/*!< 1 if commit does write into hardware registers	*/

  hwa_shared_t	shared ;

  hwa_p16a_t	port0 ;
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
  hwa_tm23a_t	timer1 ;
  hwa_uarta_t	uart0 ;
} hwa_t ;


#include "../hwa_2.h"
//#include "../classes/iocfa_2.h"
#include "../classes/pcfa_2.h"
#include "../classes/p16a_2.h"
#include "../classes/io1a_2.h"
#include "../classes/tm23a_2.h"
#include "../classes/uarta_2.h"


HW_INLINE void _hwa_setup_context( hwa_t *hwa )
{
  _hwa_setup( shared );
  _hwa_setup( port0 );
  _hwa_setup( gpio0_cf );
  _hwa_setup( gpio1_cf );
  _hwa_setup( gpio2_cf );
  _hwa_setup( gpio3_cf );
  _hwa_setup( gpio4_cf );
  _hwa_setup( gpio5_cf );
  _hwa_setup( gpio6_cf );
  _hwa_setup( gpio7_cf );
  _hwa_setup( gpio8_cf );
  _hwa_setup( gpio9_cf );
  _hwa_setup( gpio10_cf );
  _hwa_setup( gpio11_cf );
  _hwa_setup( gpio12_cf );
  _hwa_setup( gpio13_cf );
  _hwa_setup( gpio14_cf );
  _hwa_setup( gpio15_cf );

  _hwa_setup( timer1 );
  _hwa_setup( uart0 );
}


HW_INLINE void _hwa_init_context( hwa_t *hwa )
{
  _hwa_init( shared );
  _hwa_init( port0 );
  /* _hwa_init( gpio0_cf ); */
  /* _hwa_init( gpio1_cf ); */
  /* _hwa_init( gpio2_cf ); */
  /* _hwa_init( gpio3_cf ); */
  /* _hwa_init( gpio4_cf ); */
  /* _hwa_init( gpio5_cf ); */
  /* _hwa_init( gpio6_cf ); */
  /* _hwa_init( gpio7_cf ); */
  /* _hwa_init( gpio8_cf ); */
  /* _hwa_init( gpio9_cf ); */
  /* _hwa_init( gpio10_cf ); */
  /* _hwa_init( gpio11_cf ); */
  /* _hwa_init( gpio12_cf ); */
  /* _hwa_init( gpio13_cf ); */
  /* _hwa_init( gpio14_cf ); */
  /* _hwa_init( gpio15_cf ); */
  _hwa_init( timer1 );
  _hwa_init( uart0 );
}


HW_INLINE void _hwa_commit_context( hwa_t *hwa )
{
  _hwa_commit( gpio0_cf );
  _hwa_commit( gpio1_cf );
  _hwa_commit( gpio2_cf );
  _hwa_commit( gpio3_cf );
  _hwa_commit( gpio4_cf );
  _hwa_commit( gpio5_cf );
  _hwa_commit( gpio6_cf );
  _hwa_commit( gpio7_cf );
  _hwa_commit( gpio8_cf );
  _hwa_commit( gpio9_cf );
  _hwa_commit( gpio10_cf );
  _hwa_commit( gpio11_cf );
  _hwa_commit( gpio12_cf );
  _hwa_commit( gpio13_cf );
  _hwa_commit( gpio14_cf );
  _hwa_commit( gpio15_cf );
  _hwa_commit( port0 );

  _hwa_commit( timer1 );
  _hwa_commit( uart0 );

  //  _hwa_commit_reg( shared, _edgeie ); /* Process IRQ at last */
  _hwa_commit( shared );
}

#endif /* !defined __ASSEMBLER__ */

/**
 * @page esp8266
 * <br>
 */
