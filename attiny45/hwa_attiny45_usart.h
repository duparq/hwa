#ifndef HWA_ATMEGA88_USART_H
#define HWA_ATMEGA88_USART_H

/************************************************************************
 *									*
 *			Internal definitions				*
 *									*
 ************************************************************************/

#define HWA_USART0_BASE			0xC0

#define HWA_USART_HWA_UCSRA		volatile, u8,  0x00, 0x20, 0x43
#define HWA_USART_HWA_UCSRB		volatile, u8,  0x01, 0x00, 0xFD
#define HWA_USART_HWA_UCSRC		volatile, u8,  0x02, 0x06, 0xFF
#define HWA_USART_HWA_UBRRL		volatile, u8,  0x04, 0x00, 0xFF
#define HWA_USART_HWA_UBRRH		volatile, u8,  0x05, 0x00, 0x0F
#define HWA_USART_HWA_UBRR		volatile, u16, 0x04, 0x00, 0x0FFF
#define HWA_USART_HWA_UDR		volatile, u8,  0x06, 0x00, 0xFF

/*	Register bits definitions
 */
#define HWA_USART_RXC			HWA_UCSRA, 0b1,  7
#define HWA_USART_TXC			HWA_UCSRA, 0b1,  6
#define HWA_USART_UDRE			HWA_UCSRA, 0b1,  5
#define HWA_USART_FE			HWA_UCSRA, 0b1,  4
#define HWA_USART_DOR			HWA_UCSRA, 0b1,  3
#define HWA_USART_UPE			HWA_UCSRA, 0b1,  2
#define HWA_USART_U2X			HWA_UCSRA, 0b1,  1
#define HWA_USART_MPCM			HWA_UCSRA, 0b1,  0

#define HWA_USART_RXCIE			HWA_UCSRB, 0b1,  7
#define HWA_USART_TXCIE			HWA_UCSRB, 0b1,  6
#define HWA_USART_UDRIE			HWA_UCSRB, 0b1,  5
#define HWA_USART_RXEN			HWA_UCSRB, 0b1,  4
#define HWA_USART_TXEN			HWA_UCSRB, 0b1,  3
#define HWA_USART_UCSZ2			HWA_UCSRB, 0b1,  2
#define HWA_USART_RXB8			HWA_UCSRB, 0b1,  1
#define HWA_USART_TXB8			HWA_UCSRB, 0b1,  0

#define HWA_USART_UMSEL1		HWA_UCSRC, 0b1,  7
#define HWA_USART_UMSEL0		HWA_UCSRC, 0b1,  6
#define HWA_USART_UPM1			HWA_UCSRC, 0b1,  5
#define HWA_USART_UPM0			HWA_UCSRC, 0b1,  4
#define HWA_USART_USBS			HWA_UCSRC, 0b1,  3
#define HWA_USART_UCSZ1			HWA_UCSRC, 0b1,  2
#define HWA_USART_UCSZ0			HWA_UCSRC, 0b1,  1
#define HWA_USART_UCPOL			HWA_UCSRC, 0b1,  0

#define HWA_USART_UBRR			HWA_UBRR, 0x0FFF, 0

/*	Convenient registers
 */
#define HWA_USART_HWA_MODE		, u8,  -1, 0, 0xFF
#define HWA_USART_HWA_BAUD		, u32, -1, 0, 0xFFFFFFFF
#define HWA_USART_HWA_BAUDTOL		, u16, -1, 0, 0xFFFF


/*	Parameters
 */
#define HWA_USART_MODE_ASYNC		1
#define HWA_USART_LINES_OFF		0b00
#define HWA_USART_LINES_TX		0b01
#define HWA_USART_LINES_RX		0b10
#define HWA_USART_LINES_RXTX		0b11
#define HWA_USART_NBITS_5BITS		0b000
#define HWA_USART_NBITS_6BITS		0b001
#define HWA_USART_NBITS_7BITS		0b010
#define HWA_USART_NBITS_8BITS		0b011
#define HWA_USART_NBITS_9BITS		0b111
#define HWA_USART_PARITY_NOPARITY	0b00
#define HWA_USART_PARITY_EVENPARITY	0b10
#define HWA_USART_PARITY_ODDPARITY	0b11
#define HWA_USART_STOP_1STOP		0
#define HWA_USART_STOP_2STOP		1

/* #define HWA_USART_IRQ_RX		7 */
/* #define HWA_USART_IRQ_TXC		6 */
/* #define HWA_USART_IRQ_TXQNF		5 */

#define HWA_USART_IRQE_RX		HWA_UCSRB, 0b1,   7
#define HWA_USART_IRQE_RXQNE		HWA_UCSRB, 0b1,   7
#define HWA_USART_IRQE_TXC		HWA_UCSRB, 0b1,   6
#define HWA_USART_IRQE_TXQNF		HWA_UCSRB, 0b1,   5
#define HWA_USART_IRQE_ALL		HWA_UCSRB, 0b111, 5

#define HWA_USART_IRQF_RX		HWA_UCSRA, 0b1,   7
#define HWA_USART_IRQF_RXQNE		HWA_UCSRA, 0b1,   7
#define HWA_USART_IRQF_TXC		HWA_UCSRA, 0b1,   6
#define HWA_USART_IRQF_TXQNF		HWA_UCSRA, 0b1,   5
#define HWA_USART_IRQF_ALL		HWA_UCSRA, 0b111, 5

/*  Pins
 */
#define HWA_PIN_RXD			HWA_PORTD, 0
#define HWA_PIN_TXD			HWA_PORTD, 1

//#define HWA_USART_FLAG_TXQNE		HWA_UCSRA, 0b1,   5
//#define HWA_USART_IRQF_RX		
//#define HWA_USART_IRQF_RX		HWA_UCSRA, 0b1, 7


typedef struct {
  HWA_PDCL();
  HWA_VDCL(HWA_USART, HWA_UCSRA);
  HWA_VDCL(HWA_USART, HWA_UCSRB);
  HWA_VDCL(HWA_USART, HWA_UCSRC);
  HWA_VDCL(HWA_USART, HWA_UBRR);

  HWA_VDCL(HWA_USART, HWA_MODE);
  HWA_VDCL(HWA_USART, HWA_BAUD);
  HWA_VDCL(HWA_USART, HWA_BAUDTOL);
} HWA_USART ;


#define hwa_begin_usart(reset)			\
  hwa_usart_begin(HWA_USART0, reset)

#define hwa_usart_begin(pname, reset)			\
  HWA_PINIT(HWA_USART, pname);				\
  HWA_VINIT(HWA_USART, pname, HWA_UCSRA, reset);	\
  HWA_VINIT(HWA_USART, pname, HWA_UCSRB, reset);	\
  HWA_VINIT(HWA_USART, pname, HWA_UCSRC, reset);	\
  HWA_VINIT(HWA_USART, pname, HWA_UBRR, reset);		\
							\
  HWA_VINIT(HWA_USART, pname, HWA_MODE, reset);		\
  HWA_VINIT(HWA_USART, pname, HWA_BAUD, reset);		\
  HWA_VINIT(HWA_USART, pname, HWA_BAUDTOL, reset);


#define hwa_commit_usart()			\
  hwa_usart_commit(HWA_CORE0, HWA_USART0);


inline void
hwa_usart_commit ( HWA_CORE *core, HWA_USART *p )
{
  if ( !p->used )
    return ;

  //  u8	mode	= HWA_GETVR(p, HWA_MODE, 0);

  u32	syshz	= HWA_GETVR(core, HWA_SYSHZ, 0);

  /*	Mode
   */
  /* if ( HWA_SR(p, HWA_MODE, mmask) ) { */
  /*   if ( mode == 0 ) */
  /*     HWA_ERROR("Usart mode not set."); */
  /*   else if ( mode != HWA_USART_MODE_ASYNC ) */
  /*     HWA_ERROR("Usart mode not supported."); */
  /* } */

  /* if ( mode==0 ) */
  /*   HWA_ERROR("Usart mode not set."); */

  /*	Process baudrate
   */
  if ( HWA_SR(p, HWA_BAUD, mmask) ) {
    u32	baud	= HWA_GETVR(p, HWA_BAUD,    0);
    u32	baudtol	= HWA_GETVR(p, HWA_BAUDTOL, 0);

    u32	ubrr ;
    u8	u2x ;

    u2x = 0 ;
    ubrr = (syshz + 8 * baud) / (16 * baud);

    /*  Try with lower prescaler
     */
    if ( ubrr * 16 * baud != syshz &&
	 ubrr < 2048 ) {
      u2x = 1 ;
      ubrr = (syshz + 4 * baud) / (8 * baud);
    }

    if ( ubrr < 1 || ubrr > 4096 )
      HWA_ERROR("Usart baudrate unreachable.");

    /*  Check tolerance
     */
    s32 b = (syshz + ((4 * (2 - u2x) * ubrr))) / (8 * (2 - u2x) * ubrr) ;
    b = 1000 - (b * 1000 + baud/2) / baud ;
    if ( b < 0 )
      b = -b ;
    if ( (u32)b > baudtol )
      HWA_ERROR("Usart baudrate out of tolerance.");

    HWA_SETVB( HWA_USART, p, HWA_USART_U2X, u2x );
    HWA_SETVB( HWA_USART, p, HWA_USART_UBRR, ubrr-1 );
  }

  HWA_COMMIT(core, HWA_USART, p, HWA_MODE, 0xFF);
  HWA_COMMIT(core, HWA_USART, p, HWA_BAUD);
  HWA_COMMIT(core, HWA_USART, p, HWA_BAUDTOL);

  HWA_COMMIT(core, HWA_USART, p, HWA_UCSRA);
  HWA_COMMIT(core, HWA_USART, p, HWA_UCSRB);
  HWA_COMMIT(core, HWA_USART, p, HWA_UCSRC);
  HWA_COMMIT(core, HWA_USART, p, HWA_UBRR);

  p->used = 0 ;
}




/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Synchronous functions				*
 *										*
 ********************************************************************************/
#define HWA_USART_IRQF_TXQNF		HWA_UCSRA, 0b1,   5


#define hw_usart_test_flag(pname, flag)\
  HW_TSTHB(HWA_USART, pname, HWA_G2(HWA_USART_IRQF, flag))


#define hw_usart_write_safe(pname, c)			\
  do {							\
    while ( !hw_usart_test_flag(pname, TXQNF) ) {}	\
    HW_SETHR(HWA_USART, pname, HWA_UDR, c);		\
  } while(0)

#define hw_usart_write(pname, value)	HW_HR(HWA_USART, pname, HWA_UDR) = value
#define hw_usart_read(pname)		HW_HR(HWA_USART, pname, HWA_UDR)

/*	Note: must read RXB8 first
 */
#define hw_usart_read9(pname)		\
  (((u16)HW_HGET(HWA_USART, pname, HWA_USART_RXB8)<<8) | HW_HR(HWA_USART, pname, HWA_UDR))

#define hw_usart_get_rxb8(pname)	HW_HGET(HWA_USART, pname, RXB8)

#define hw_usart_turn_irq(pname, irq, state)				\
  HW_SETHB(HWA_USART, pname, HWA_UCSRB, 0b1, HWA_USART_IRQ_##irq, HWA_STATE_##state)

#define rem_hw_usart_clr_irq(pname, irq)			\
  HW_SETHB(HWA_USART, pname, HWA_UCSRA, 0b1, HWA_USART_IRQ_##irq, 1)

#define hw_usart_clr_irq(pname, irq)					\
  HW_SETHB(HWA_USART, pname, HWA_USART_IRQF_##irq, HWA_BMSK(HWA_USART_IRQF_##irq))


/********************************************************************************
 *										*
 *				User definitions				*
 *										*
 *				Asynchronous functions				*
 *										*
 ********************************************************************************/


#define rem_hwa_usart_set_mode(pptr, mode, lines, nbits, parity, stop)	\
  do {									\
    HWA_SETVB(HWA_USART, pptr, HWA_MODE, 0xFF, 0, HWA_USART_MODE_##mode);	\
    									\
    if (HWA_USART_MODE_##mode == HWA_USART_MODE_ASYNC) {		\
      HWA_SETVB(HWA_USART, pptr, HWA_USART_UMSEL1, 0);			\
      HWA_SETVB(HWA_USART, pptr, HWA_USART_UMSEL0, 0);			\
    } else {								\
      HWA_ERROR("USART Mode not supported yet.", 1);			\
    }									\
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_RXEN, (HWA_USART_LINES_##lines & 0b10)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_TXEN, (HWA_USART_LINES_##lines & 0b01)!=0); \
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ2, (HWA_USART_NBITS_##nbits & 0b100)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ1, (HWA_USART_NBITS_##nbits & 0b010)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ0, (HWA_USART_NBITS_##nbits & 0b001)!=0); \
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UPM1, (HWA_USART_PARITY_##parity & 0b10)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UPM0, (HWA_USART_PARITY_##parity & 0b01)!=0); \
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_USBS, HWA_USART_STOP_##stop);	\
    									\
  } while(0)


#define hwa_usart_set_mode(pptr, mode, lines)				\
  do {									\
    HWA_SETVB(HWA_USART, pptr, HWA_MODE, 0xFF, 0, HWA_USART_MODE_##mode); \
    									\
    if (HWA_USART_MODE_##mode == HWA_USART_MODE_ASYNC) {		\
      HWA_SETVB(HWA_USART, pptr, HWA_USART_UMSEL1, 0);			\
      HWA_SETVB(HWA_USART, pptr, HWA_USART_UMSEL0, 0);			\
    } else								\
      HWA_ERROR("USART Mode not supported yet.", 1);			\
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_RXEN, (HWA_USART_LINES_##lines & 0b10)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_TXEN, (HWA_USART_LINES_##lines & 0b01)!=0); \
  } while(0)


#define hwa_usart_set_frame(pptr, nbits, parity, stop)			\
  do {									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ2, (HWA_USART_NBITS_##nbits & 0b100)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ1, (HWA_USART_NBITS_##nbits & 0b010)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UCSZ0, (HWA_USART_NBITS_##nbits & 0b001)!=0); \
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UPM1, (HWA_USART_PARITY_##parity & 0b10)!=0); \
    HWA_SETVB(HWA_USART, pptr, HWA_USART_UPM0, (HWA_USART_PARITY_##parity & 0b01)!=0); \
    									\
    HWA_SETVB(HWA_USART, pptr, HWA_USART_USBS, HWA_USART_STOP_##stop);	\
  } while(0)


#define hwa_usart_set_baud(pptr, baudrate, baudtol)		\
  do {								\
    HWA_SETVB(HWA_USART, pptr, HWA_BAUD, -1, 0, baudrate);	\
    HWA_SETVB(HWA_USART, pptr, HWA_BAUDTOL, -1, 0, baudtol);	\
  } while(0)


#define hwa_usart_set_txb8(pptr, bit)			\
  HWA_SETVB(HWA_USART, pptr, HWA_USART_TXB8, bit);	\


#define rem_hwa_usart_turn_irq(pptr, irq, state)				\
  HWA_SETVB(HWA_USART, pptr, HWA_UCSRB, 0b1, HWA_USART_IRQ_##irq, HWA_STATE_##state)

/*	FIXME: TODO: WARNING: what about irq=='ALL'?
 */
#define hwa_usart_turn_irq(pptr, irq, state)				\
  HWA_SETVB(HWA_USART, pptr, HWA_USART_IRQE_##irq, HWA_STATE_##state)

/* #define hwa_usart_clr_irq(pptr, irq, state)				\ */
/*   HWA_SETVB(HWA_USART, pptr, HWA_USART_IRQF_##irq, HWA_STATE_##state) */


#endif
