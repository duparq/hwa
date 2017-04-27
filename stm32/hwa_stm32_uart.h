#ifndef HWA_STM32_UART_H
#define HWA_STM32_UART_H


/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_UART1_BASE			HWA_APB2+0x3800 /* 0x40013800 */
#define HWA_UART2_BASE			HWA_APB1+0x4400 /* 0x40004400 */
#define HWA_UART3_BASE			HWA_APB1+0x4800 /* 0x40004800 */
#define HWA_UART4_BASE			HWA_APB1+0x4c00 /* 0x40004c00 */
#define HWA_UART5_BASE			HWA_APB1+0x5000 /* 0x40005000 */

#define HWA_UART1_TYPE			HWA_UART
#define HWA_UART2_TYPE			HWA_UART
#define HWA_UART3_TYPE			HWA_UART
#define HWA_UART4_TYPE			HWA_UART
#define HWA_UART5_TYPE			HWA_UART

#define HWA_UART_HWA_SR			volatile, u16, 0x00, 0x00C0, 0x0360
#define HWA_UART_HWA_DR			volatile, u16, 0x04, 0x0000, 0x01FF
#define HWA_UART_HWA_BRR		volatile, u16, 0x08, 0x0000, 0xFFFF
#define HWA_UART_HWA_CR1		volatile, u16, 0x0C, 0x0000, 0x3FFF
#define HWA_UART_HWA_CR2		volatile, u16, 0x10, 0x0000, 0x7F7F
#define HWA_UART_HWA_CR3		volatile, u16, 0x14, 0x0000, 0x07FF
#define HWA_UART_HWA_GTPR		volatile, u16, 0x18, 0x0000, 0xFFFF

/*	Register bits definitions
 */
#define HWA_UART_TXE			HWA_SR, 0b1, 7
#define HWA_UART_TC			HWA_SR, 0b1, 6
#define HWA_UART_RXQNE			HWA_SR, 0b1, 5
#define HWA_UART_IDLE			HWA_SR, 0b1, 4

#define HWA_UART_UE			HWA_CR1, 0b1, 13
#define HWA_UART_M			HWA_CR1, 0b1, 12
#define HWA_UART_PCE			HWA_CR1, 0b1, 10
#define HWA_UART_PS			HWA_CR1, 0b1, 9
#define HWA_UART_TXEIE			HWA_CR1, 0b1, 7
#define HWA_UART_TCIE			HWA_CR1, 0b1, 6
#define HWA_UART_RXNEIE			HWA_CR1, 0b1, 5
#define HWA_UART_TE			HWA_CR1, 0b1, 3
#define HWA_UART_RE			HWA_CR1, 0b1, 2

#define HWA_UART_SBK			HWA_CR1, 0b1, 0

#define HWA_UART_STOP			HWA_CR2, 0b11, 12

#define HWA_UART_IRQF_TXC		HWA_UART_TXC


/*	Convenient registers
 */
#define HWA_UART_HWA_BAUD		, u32, -1, 0, 0xFFFFFFFF
#define HWA_UART_HWA_BAUDTOL		, u16, -1, 0, 0xFFFF

/*	Pins
 */
#define HWA_UART1_TX			PA9
#define HWA_UART1_RX			PA10

/*	Interrupts
 */
#define HWA_UART_IRQ_TX			HWA_UART_TXEIE
#define HWA_UART_IRQ_TXQNF		HWA_UART_TXEIE
#define HWA_UART_IRQ_TXC		HWA_UART_TCIE
#define HWA_UART_IRQ_RX			HWA_UART_RXNEIE
#define HWA_UART_IRQ_RXQNE		HWA_UART_RXNEIE

/*	Flags
 */
#define HWA_UART_FLAG_OVERRUN		HWA_SR, 0b1, 3


typedef struct {
  HWA_PDCL()
  HWA_VDCL(HWA_UART, HWA_SR);
  HWA_VDCL(HWA_UART, HWA_BRR);
  HWA_VDCL(HWA_UART, HWA_CR1);
  HWA_VDCL(HWA_UART, HWA_CR2);
  HWA_VDCL(HWA_UART, HWA_CR3);
  HWA_VDCL(HWA_UART, HWA_GTPR);

  HWA_VDCL(HWA_UART, HWA_BAUD);
  HWA_VDCL(HWA_UART, HWA_BAUDTOL);
} HWA_UART ;


#define hwa_begin_uart(reset)			\
  hwa_uart_begin(HWA_UART1, reset)		\
  hwa_uart_begin(HWA_UART2, reset)		\
  hwa_uart_begin(HWA_UART3, reset)		\
  hwa_uart_begin(HWA_UART4, reset)		\
  hwa_uart_begin(HWA_UART5, reset)

#define hwa_uart_begin(pname, reset)		\
  HWA_PINIT(HWA_UART, pname);			\
  HWA_VINIT(HWA_UART, pname, HWA_SR, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_BRR, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_CR1, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_CR2, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_CR3, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_GTPR, reset);	\
  HWA_VINIT(HWA_UART, pname, HWA_BAUD, 0);	\
  HWA_VINIT(HWA_UART, pname, HWA_BAUDTOL, 0);

#define hwa_commit_uart()			\
  hwa_uart_commit(HWA_CORE0, HWA_UART1);	\
  hwa_uart_commit(HWA_CORE0, HWA_UART2);	\
  hwa_uart_commit(HWA_CORE0, HWA_UART3);	\
  hwa_uart_commit(HWA_CORE0, HWA_UART4);	\
  hwa_uart_commit(HWA_CORE0, HWA_UART5);


inline void
hwa_uart_commit ( HWA_CORE *core, HWA_UART *p )
{
  if ( !p->used )
    return ;

  /*	RM0008 Rev11 p. 747: BAUD = PCLK / (16 * USARTDIV)
   *
   *	USARTDIV = PCLK / (16 * BAUD)
   *
   *	PCLK == PCLK2 (i.e. APB2 clock, 72 MHz max) for USART1,
   *	PCLK == PCLK1 (36 MHz max) for all other.
   *
   *	USARTDIV is coded '12.4': 12 bits mantissa, 4 bits fraction, thus the
   *	16 bit value of this DIVISOR can be computed as:
   *		DIVISOR = (16 * PCLK) / (16 * BAUD)
   *	thus:
   *		DIVISOR = PCLK / BAUD
   *
   *	To get the nearest rounded value:
   *		DIVISOR = (PCLK + (BAUD+1)/2) / BAUD
   */
  if ( HWA_SR(p, HWA_BAUD, mmask) ) {
    u32 baudrate = HWA_GETVR(p, HWA_BAUD, 0) ;
    if ( baudrate != 0 ) {
      u32 clkhz ;

      if ( p->hwaddr == HWA_UART1_BASE )
	clkhz = HWA_GETVR(core, HWA_APB2HZ, 0) ;
      else
	clkhz = HWA_GETVR(core, HWA_APB1HZ, 0) ;

      if ( clkhz == 0 )
	HWA_ERROR("Bus frequency not set.");
    
      u16 divisor = (clkhz + (baudrate+1)/2) / baudrate ;

      //    HWA_SETVB(HWA_UART, p, HWA_UART_BRR, divisor);
      HWA_SETVB(HWA_UART, p, HWA_BRR, -1, 0, divisor);
    }
  }

  HWA_COMMIT(core, HWA_UART, p, HWA_SR,   -1, 0);
  HWA_COMMIT(core, HWA_UART, p, HWA_BRR,  -1, 0);
  HWA_COMMIT(core, HWA_UART, p, HWA_CR1,  -1, 0);
  HWA_COMMIT(core, HWA_UART, p, HWA_CR2,  -1, 0);
  HWA_COMMIT(core, HWA_UART, p, HWA_CR3,  -1, 0);
  HWA_COMMIT(core, HWA_UART, p, HWA_BAUD, -1, 0);

  p->used = 0 ;
}


/************************************************************************
 *									*
 *			Synchronous actions				*
 *									*
 ************************************************************************/

#define hw_uart_turn(pname, state)		\
  HW_SETHB(HWA_UART, pname, HWA_UART_UE, HWA_STATE_##state);

#define hw_uart_data(pname)		HW_HR(HWA_UART, pname, HWA_DR)
#define hw_uart_set_data(pname, value)	HW_HR(HWA_UART, pname, HWA_DR) = value
#define hw_uart_txq_full(pname)		(HW_TSTHB(HWA_UART, pname, HWA_UART_TXE) == 0)
#define hw_uart_tx_complete(pname)	(HW_TSTHB(HWA_UART, pname, HWA_UART_TC) != 0)

/* #define hw_uart_test_flag(pname, flag)				\ */
/*   HW_TSTHB(HWA_UART, pname, HWA_G2(HWA_UART_FLAG, flag)) */

#define hw_uart_write_safe(pname, c)		\
  do {						\
    while ( hw_uart_txq_full(pname) ) {}	\
    hw_uart_write(pname, c);			\
  } while(0)


#define hw_uart_read(pname)		HW_HR(HWA_UART, pname, HWA_DR)
#define hw_uart_write(pname, c)		HW_HR(HWA_UART, pname, HWA_DR) = c
#define hw_uart_break(pname)		HW_SETHB(HWA_UART, pname, HWA_UART_SBK, 1)

#define hw_uart_turn_irq(pname, irq, state)				\
  HW_SETHB(HWA_UART, pname, HWA_UART_IRQ_##irq, HWA_STATE_##state)

#define hw_uart_clr_irq(pname, irq)\
  HW_SETHB(HWA_UART, pname, HWA_UART_IRQF_##irq, 0)


/********************************************************************************
 *										*
 *				Asynchronous actions				*
 *										*
 ********************************************************************************/

#define HWA_UART_MODE_ASYNC		0
#define HWA_UART_LINES_RXTX		0b11
#define HWA_UART_LINES_RX		0b10
#define HWA_UART_LINES_TX		0b01

#define HWA_UART_NBITS_8BITS		0
#define HWA_UART_NBITS_9BITS		1
#define HWA_UART_PARITY_NOPARITY	0
#define HWA_UART_PARITY_EVENPARITY	1
#define HWA_UART_PARITY_ODDPARITY	2
#define HWA_UART_STOPS_0STOP5		0b101
#define HWA_UART_STOPS_1STOP		0b100
#define HWA_UART_STOPS_1STOP5		0b111
#define HWA_UART_STOPS_2STOP		0b110


#define hwa_uart_set_mode(pptr, mode, lines, nbits, parity, stops)	\
  do {									\
    hwa_prph_turn_clk(pptr, ON);					\
    /*									\
     *	Start configuration from RESET defaults				\
     */									\
    HWA_VINIT(HWA_UART, pptr, HWA_CR1, 1);				\
    HWA_VINIT(HWA_UART, pptr, HWA_CR2, 1);				\
    HWA_VINIT(HWA_UART, pptr, HWA_CR3, 1);				\
									\
    if (HWA_UART_MODE_##mode == HWA_UART_MODE_ASYNC) {			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_UE, 1);			\
    } else {								\
      HWA_ERROR("UART Mode not supported yet.");			\
    }									\
    									\
    if ( HWA_UART_LINES_##lines & 0b10 ) {				\
      hwa_gpio_config_pin(HWA_G2(pptr, RX), INPUT);			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_RE, 1);				\
    }									\
    else {								\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_RE, 0);				\
    }									\
    									\
    if ( HWA_UART_LINES_##lines & 0b01 ) {				\
      hwa_gpio_config_pin(HWA_G2(pptr, TX), ALTOUTPUT);			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_TE, 1);				\
    }									\
    else {								\
      hwa_gpio_config_pin(HWA_G2(pptr, TX), INPUT);			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_TE, 0);				\
    }									\
    									\
    if (HWA_UART_NBITS_##nbits == HWA_UART_NBITS_8BITS)			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_M, 0);				\
    else								\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_M, 1);				\
    									\
    if (HWA_UART_PARITY_##parity == HWA_UART_PARITY_NOPARITY)		\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_PCE, 0);			\
    else if (HWA_UART_PARITY_##parity == HWA_UART_PARITY_EVENPARITY) {	\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_PCE, 1);			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_PS, 0);				\
    } else {								\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_PCE, 1);			\
      HWA_SETVB(HWA_UART, pptr, HWA_UART_PS, 1);				\
    }									\
    									\
    HWA_SETVB(HWA_UART, pptr, HWA_UART_STOP, HWA_UART_STOPS_##stops);	\
    									\
  } while(0)


#define hwa_uart_set_baud(pptr, baudrate, baudtol)		\
  do {								\
    hwa_prph_turn_clk(pptr, ON);				\
    HWA_SETVB(HWA_UART, pptr, HWA_BAUD, -1, 0, baudrate);	\
    HWA_SETVB(HWA_UART, pptr, HWA_BAUDTOL, -1, 0, baudtol);	\
  } while(0)


#define hwa_uart_turn_irq(pptr, irq, state)				\
  HWA_SETVB(HWA_UART, pptr, HWA_UART_IRQ_##irq, HWA_STATE_##state)

#endif
