
	;; -*- asm -*-

	;; Software half-duplex autobaud UART using a timer-counter
	;; 
	;; GCC call-used registers: R18..R27, R30, R31

	DBG_START     = DBG && 1
	DBG_START2    = DBG && 0
	DBG_BIT	      = DBG && 0
	DBG_RXBIT     = DBG && 0
	DBG_RXDATA    = DBG && 0
	DBG_RXSTOP    = DBG && 0
	DBG_RXEOF     = DBG && 0
	DBG_RXIDLE    = DBG && 0
	DBG_TXBIT     = DBG && 0
	DBG_TXEOF     = DBG && 0
	DBG_GETBYTE   = DBG && 0
	DBG_PUTBYTE   = DBG && 0
	DBG_WAITIDLE  = DBG && 1
	DBG_WAITREADY = DBG && 0


	;; Globals
	;;
	.global	swuart_data
	swuart_data = data

	.global	swuart_status
	swuart_status = status

	.global	swuart_dt0
	swuart_dt0 = dt0

	.global	swuart_dtn
	swuart_dtn = dtn

	.global	swuart_wait_ready
 	swuart_wait_ready = wait_ready

	.global swuart_is_busy
	swuart_is_busy = is_busy

	.global swuart_wait_rxidle
	swuart_wait_rxidle = wait_rxidle

	.global swuart_set_dt
	swuart_set_dt = setdt

	.global swuart_getbyte
	swuart_getbyte = getbyte

	.global swuart_putbyte
	swuart_putbyte = putbyte

	.global swuart_config_rx
	swuart_config_rx = config_rx

	.section .bss
	.global __do_clear_bss


	;; Status register bits
	;; 
	;;   bit 0: stop bit (1: normal, 0: break)
	;;   bit 1: idle bit
	;;   bit 2: 1==stop bit received
	;;
	ST_STOP = 0		; stop bit value
	ST_EOF  = 1		; idle state bit (always 1)
	ST_RXNE = 2		; stop bit sampled


data:	.byte	0		; Data register
status:	.byte	0		; Status register
shift:	.byte	0		; Shift register
nbit:	.byte	0		; # of bits to rx/tx


	.if CALLBACK_PTR
cbptr:	.word	0		; C callback function (called after rx/tx done)
	.endif


	.if COUNTW==8
dt0:	.byte	0	; 1.5 bit duration
dtn:	.byte	0	; 1 bit duration
	.elseif COUNTW==16
dt0:	.word	0	; 1.5 bit duration
dtn:	.word	0	; 1 bit duration
	.else
	.error "COUNTW not set?"
	.endif

	.if MATCHW==8
match:	.byte	0	; Next bit rx/tx date
	.elseif MATCHW==16
match:	.word	0	; Next bit rx/tx date
	.else
	.error "MATCHW not set?"
	.endif


	;; Pins
	;;
	.if TXDPORT == RXDPORT && TXDBIT == RXDBIT
	ONEPIN = 1
	.else
	ONEPIN = 0
	.endif


	;; Timer macros
	;;
	.equ HW_ISR(SWUART_TIMER, HW_G2(MATCH, SWUART_TIMER_MATCH)), isr_bit

	.macro enable_match reg ;	Clear 'MATCH' and enable 'MATCH'
	.if MATCHENB < 0x20
	sbi	MATCHFLG, XMATCH ; [2]
	sbi	MATCHENB, XMATCH ; [2]
	TX=TX+4
	.else
	ldi	\reg, 1<<XMATCH ; [1]
	out	MATCHFLG, \reg	; [1]
	in	\reg, MATCHENB	; [1]
	ori	\reg, 1<<XMATCH ; [1]
	out	MATCHENB, \reg	; [1]
	TX=TX+5
	.endif
	;; ldi	\reg, 1<<XMATCH	; [1]
	;; out	MATCHFLG, \reg	; [1]
	;; out	MATCHENB, \reg	; [1]
	;; TX=TX+3
	.endm

	.macro disable_match reg ;	Disable 'MATCH'
	;; in	R31, MATCHENB	; [1]
	;; andi	R31, ~(1<<4)	; [1]
	.if MATCHENB < 0x20
	cbi	MATCHENB, XMATCH; [2]
	TX=TX+2
	.else
	ldi	\reg, 0		; [1]
	out	MATCHENB, \reg	; [1]
	TX=TX+2
	.endif
	.endm

	.macro test_matchenb reg ; Is 'MATCH A' enabled?
	in	\reg, MATCHENB	;
	andi	\reg, 1<<XMATCH	;
	TX=TX+2
	.endm

	.macro test_matchflg reg ; 'MATCH A' flag?
	in	\reg, MATCHFLG	;
	andi	\reg, 1<<XMATCH	;
	TX=TX+2
	.endm

	.macro clear_matchflg reg
	sbi	MATCHFLG, XMATCH
	.endm


	.section .text

	.if SWUART_RX
	;; ISR START: falling edge on RX
	;;
	;;   All interrupts blocked for TSTART1 cycles (until sampling
	;;   of timer COUNT).
	;;   Total isr_start cycles: TSTART2
	;;
	;;  (See at the end of this file for how to get TSTART values)
	;;
isr_start:
	TX=4			; <- call
	SREG_PUSHED = 0

	.if CHECK_START_EDGE && RXDPIN < 0x20
	sbic	RXDPIN, RXDBIT	; [2]
	reti
	TX=TX+2
	.endif

	.if DBG_START
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	push	R24		; [2]
	TX=TX+2

	.if CHECK_START_EDGE && RXDPIN > 0x1F
	in	R24, SREG	; [1]
	push	R24		; [2]
	in	R24, RXDPIN	; [1]
	andi	R24, 1<<RXDBIT  ; [1]
	brne	1f		; [1]
	TX=TX+5
	SREG_PUSHED = 24
	.endif

	.if DBG_START2
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	;; Get start bit date (R25:R24) and enable interrupts
	;;
	.if COUNTW==8
	sei			; [1]
	in	R24, COUNT	; [1]
	TX=TX+2
	TSTART1=TX		; Elapsed cycles between ISR start and date sampling
	.endif

	.if COUNTW==16
	push	R25		; [2]
	in	R24, COUNTL	; [1]=3
	sei			; [1]
	in	R25, COUNTH	; [1]
	TX=TX+5
	TSTART1=TX+3		; Elapsed cycles between ISR start and date sampling
	.endif

	push	R26		; [2]
	TX=TX+2

	.if !SREG_PUSHED
	in	R26, SREG	; [1]
	push	R26		; [2]
	TX=TX+3
	SREG_PUSHED = 26
	.endif

	disable_start R26

	;; Compute first data bit date
	;;
	.if COUNTW==8 && MATCHW==8
	lds	R26, dt0	; [2]
	add	R24, R26	; [1]
	out	MATCH, R24	; [1]
	sts	match, R24	; [2]
	TX=TX+6
	.endif

	.if COUNTW==8 && MATCHW==16
	ldi	R24, 1		; [1]		dec'ed first in isr
	lds	R26, dt0+1	; [2]
	add	R24, R26	; [1]		Do not add carry
	sts	match+1, R24	; [2]
	TX=TX+6
	.endif

	.if COUNTW==16 && MATCHW==16
	lds	R26, dt0+0	; [2]
	add	R24, R26	; [1]
	lds	R26, dt0+1	; [2]
	adc	R25, R26	; [1]
	out	MATCHH, R25	; [1]
	out	MATCHL, R24	; [1]
	sts	match+0, R24	; [2]
	sts	match+1, R25	; [2]
	TX=TX+12
	.endif

	ldi	R24, 8		; [1]		8 data bits to receive
	sts	nbit, R24	; [2]
	TX=TX+3

	enable_match R24

	.if SREG_PUSHED == 26
	pop	R26		; [2]
	out	SREG, R26	; [1]
	.endif

	pop	R26		; [2]
	TX=TX+5
	.if COUNTW==16
	pop	R25		; [2]
	TX=TX+2
	.endif

1:
	.if SREG_PUSHED == 24
	pop	R24		; [2]
	out	SREG, R24	; [1]
	TX=TX+3
	.endif

	pop	R24		; [2]
	TX=TX+2

	.if DBG_START || DBG_START2
	cbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	reti			; [4]
	TX=TX+4
	TSTART2=TX

	.endif			; SWUART_RX


	;; ISR Bit: send/receive one bit
	;;
	;; The priority is to re-enable interrupts as quickly as possible.
	;; 
	;; RX: all interrupts blocked for 20 cycles
	;;     received bit sampled 20 cycles after interrupt
	;; TX: all interrupts blocked for --- cycles
	;;     bit sent --- cycles after interrupt
	;;
isr_bit:
	TX=4			; [4]		<- call

	.if DBG_BIT
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	push	R31		; [2]
	in	R31, SREG	; [1]
	push	R31		; [2]
	TX=TX+5

	.if COUNTW==8 && MATCHW==16
	lds	R31, match+1	; [2]
	dec	R31		; [1]
	sts	match+1, R31	; [2]
	brne	L31S		; [1/2]
	TX=TX+6
	.endif

	.if SWUART_TX && SWUART_RX
	sbic	FLAGS, F_RXTX	; [2/1]		TX or RX?
	rjmp	tx		; [2]
	TBITTX=TX+3
	TX=TX+2
	.else
	.error "Not handled."
	.endif

	.if SWUART_RX

	;; Receiving
	;;
	.if DBG_RXBIT
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	sei			; [1]		Sample port of RXD pin
	in	R31, RXDPIN	; [1]		and enable interrupts
	TX=TX+2

	TBITRX1=TX		; Elapsed cycles between interrupt and bit sampling

	bst	R31, RXDBIT	; [1]		Store RXD bit to T
	lds	R31, shift	; [2]		Store T to shift register
	lsr	R31		; [1]
	bld	R31, 7		; [1]
	sts	shift, R31	; [2]
	TX=TX+7

	lds	R31, nbit	; [2]		One more bit received
	subi	R31, 1		; [1]		'dec' would not set the carry!
	sts	nbit, R31	; [2]
	TX=TX+5

	brmi	rxeof		; [1/2]		nbit<0
	brne	next		; [1/2]
	TX=TX+2

	.if DBG_RXDATA
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif
	lds	R31, shift	; [2]		nbit==0: store shift reg to data byte
	sts	data, R31	; [2]
	TX=TX+4
	.endif			; SWUART_RX
	;; Compute next data bit date and set compare accordingly
	;;
next:
	.if COUNTW==8 && MATCHW==8
	push	R30		; [2]
	lds	R30, match	; [2]
	lds	R31, dtn	; [2]
	add	R30, R31	; [1]
	out	MATCH, R30	; [1]
	sts	match, R30	; [2]
	TX=TX+10
	.endif

	.if COUNTW==8 && MATCHW==16
	ldi	R30, 1		; [1]		dec'ed first in isr
	lds	R31, dtn+1	; [2]
	add	R30, R31	; [1]		Do not add carry
	sts	match+1, R30	; [2]
	TX=TX+6
	.endif

	.if COUNTW==16
	push	R30		; [2]
	lds	R30, dtn+0	; [2]
	lds	R31, dtn+1	; [2]
next2:	push	R29		; [2]
	lds	R29, match+0	; [2]
	add	R30, R29	; [1]
	lds	R29, match+1	; [2]
	adc	R31, R29	; [1]
	pop	R29		; [2]
	out	MATCHH, R31	; [1]
	out	MATCHL, R30	; [1]
	sts	match+0, R30	; [2]
	sts	match+1, R31	; [2]
	TX=TX+22
	.endif

L31S30:	pop	R30		; [2]
L31S:	pop	R31		; [2]		Leave ISR
	out	SREG, R31	; [1]
	pop	R31		; [2]
	TX=TX+7

	.if DBG_BIT+DBG_RXBIT+DBG_RXSTOP+DBG_RXEOF+DBG_RXIDLE+DBG_RXDATA+DBG_TXBIT+DBG_TXEOF
	cbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	reti			; [4]
	TX=TX+4
	TBITRX2=TX

rxeof:
	.if SWUART_RX
	.if DBG_RXEOF
	sbi	DBGPORT, DBGBIT	; [2]
	.endif
	ldi	R31, 1<<ST_RXNE	| 1<<ST_EOF ; [1]	Status = "new data received"
	bld	R31, ST_STOP	; [1]				+ stop bit value
	sts	status, R31	; [2]
	sbi	FLAGS, F_WIBTX	; [2]		Need to wait idle before TX

	disable_match R31	; [2]
	enable_start R31	; [2]

	.if HAS_CALLBACK
	rcall	callback
	.endif

;; 	.if COUNT16
;; 	push	R30		; [2]	1/4 bit delay
;; 	lds	R30, dtn+0	; [2]
;; 	lds	R31, dtn+1	; [2]
;; 	lsr	R31		; [1]
;; 	ror	R30		; [1]
;; 	lsr	R31		; [1]
;; 	ror	R30		; [1]
;; 	.endif
;; 	rjmp	next2

	rjmp	next		;		Compute next bit date for idle detection
				;		before tx
	.endif
;; #endif

	
	;; Sending
	;; 
	;;   Send one data bit, or stop bit, or idle bit
	;;
	.if SWUART_TX
tx:
	TX=TBITTX

	lds	R31, shift	; [2]		Send bit and enable ints ASAP
	lsr	R31		; [1]
	TX=TX+3
	
	.if DBG_TXBIT
	sbi	DBGPORT, DBGBIT	; [2]
	TX=TX+2
	.endif

	brcc	tx0		; [1/2]
tx1:	sei			; [1]
	sbi	TXDPORT, TXDBIT	; [2]=4
	rjmp	1f		; [2]
tx0:	sei			; [1]
	cbi	TXDPORT, TXDBIT	; [2]=5
1:	sts	shift, R31	; [2]		Prepare next bits
	TX=TX+5
	TBITTX2=TX

	lds	R31, nbit	; [2]		One more bit sent
	subi	R31, 1		; [1]		'dec' would not set the Carry!
	sts	nbit, R31	; [2]

	brmi	txeof		; [1]/[2]	nbit<0: all data bits sent
	brne	1f		; [1]/[2]	nbit>0: data bits remaining

	lds	R31, status	; [1]		nbit==0: prepare stop and idle bits
	sts	shift, R31	; [2]
1:	rjmp	next

txeof:				; [ ]=15	End of frame
	.if DBG_TXEOF
	sbi	DBGPORT, DBGBIT	; [2]
	.endif
	brcs	1b		;		nbit==-1: sending stop bit
txidle:	
	.if DBG_PUTBYTE
	cbi	DBGPORT, DBGBIT
	.endif
	disable_match R31	; [2]		nbit==-2: sending idle bit, tx done
	.if ONEPIN
	cbi	TXDDR, TXDBIT	;		Release TXD
	cbi	TXDPORT, TXDBIT	;
	ldi	R31, 0x0B	; [1]		Status = idle
	sts	status, R31	; [2]
	in	R31, FLAGS	; [1]
	;; sbrs	R31, F_NORX	; [1]
	;; andi	R31, ~(1<<F_RXTX)	; [1]
	;; out	FLAGS, R31	; [1]
	cbi	FLAGS, F_RXTX	; [2]		Mode = RX
	enable_start R31	;
	.endif

	.if HAS_CALLBACK
	rjmp	callback
	.else
	rjmp	L31S		; [2]
	.endif

	.endif 			; TX

	;; Call the handler from its pointer if not NULL
	;;
	.if CALLBACK_PTR
	.section	.text.callback,"ax",@progbits
callback:
	push	R30
	lds	R30, cbptr+0
	lds	R31, cbptr+1
	push	R0
	mov	R0, R30
	or	R0, R31
	breq	1f
	push	R1
	eor	R1, R1
	push	R18
	push	R19
	push	R20
	push	R21
	push	R22
	push	R23
	push	R24
	push	R25
	push	R26
	push	R27
	icall
	pop	R27
	pop	R26
	pop	R25
	pop	R24
	pop	R23
	pop	R22
	pop	R21
	pop	R20
	pop	R19
	pop	R18
	pop	R1
1:	pop	R0
	rjmp	L31S30
	.endif


	.if CALLBACK
	.section	.text.callback,"ax",@progbits
callback:
	push	R30
	push	R0
	push	R1
	eor	R1, R1
	push	R18
	push	R19
	push	R20
	push	R21
	push	R22
	push	R23
	push	R24
	push	R25
	push	R26
	push	R27
	rcall	cb
	pop	R27
	pop	R26
	pop	R25
	pop	R24
	pop	R23
	pop	R22
	pop	R21
	pop	R20
	pop	R19
	pop	R18
	pop	R1
	pop	R0
	rjmp	L31S30
	.endif


	;; Wait all rx/tx to be done
	;;
	.section	.text.wait_ready,"ax",@progbits
wait_ready:
	.if DBG_WAITREADY
	sbi	DBGPORT, DBGBIT
	.endif
	;; disable_start R25
1:	test_matchenb R25
	brne	1b
	.if DBG_WAITREADY
	cbi	DBGPORT, DBGBIT
	.endif
	ret


	;; Return non null if UART is busy
	;;
;; 	.section	.text.is_busy,"ax",@progbits
;; is_busy:
;; 	test_matchenb R24
;; 	ret

	.if SWUART_RX
	.section	.text.getbyte,"ax",@progbits
getbyte:
	.if DBG_GETBYTE
	sbi	DBGPORT, DBGBIT
	.endif
1:	lds	R24, status
	sbrs	R24, ST_RXNE
	rjmp	1b
	cli
	lds	R24, status
	andi	R24, ~(1<<ST_RXNE)
	sei
	sts	status, R24
	lds	R24, data
	.if DBG_GETBYTE
	cbi	DBGPORT, DBGBIT
	.endif
	ret
	.endif			; SWUART_RX


	;; Send one byte
	;;
	.if SWUART_TX
	.section	.text.putbyte,"ax",@progbits
putbyte:
	.if DBG_PUTBYTE
	sbi	DBGPORT, DBGBIT
	.endif

	;; sbi	FLAGS, F_NORX
	rcall	wait_ready
	;; cbi	FLAGS, F_NORX

	sbis	FLAGS, F_WIBTX
	rjmp	2f

1:	test_matchflg R25	; wait idle state between rx and tx
	breq	1b
	cbi	FLAGS, F_WIBTX

2:	sts	shift, R24	;		Store data
	ldi	R24, 0x0B	;		Store stop and idle bits
	sts	status, R24	;
	sbi	FLAGS, F_RXTX	;		Mode = TX
	ldi	R24, 8		;		8 bits of data to be sent
	sts	nbit, R24	;

	.if SWUART_RX
	disable_start R24
	.endif

	.if ONEPIN
	sbi	TXDPORT, TXDBIT	; 		Initialize TXD
	sbi	TXDDR, TXDBIT	;
	.endif

	.if COUNTW==8
	cli
	in	R24, COUNT	     ;		Get date
	sei			; [1]|
	cbi	TXDPORT, TXDBIT	; [2]|=3	Send start bit
	lds	R25, dtn	;		Compute first data bit date
	subi	R25, (TBITTX2-3+PSC/2)/PSC ;		Compensate bit isr / send delay
	add	R24, R25
	out	MATCH, R24
	sts	match, R24
	.endif

	.if COUNTW==8 && MATCHW==16
	ldi	R24, 1		; 		dec'ed first in isr
	lds	R25, dtn+1
	add	R24, R25	;		Do not add carry
	sts	match+1, R24
	.endif

	.if COUNTW==16
	cli
	in	R24, COUNTL	     ;		Get date
	in	R25, COUNTH	     ; [1]|
	sei			     ; [1]|
	cbi	TXDPORT, TXDBIT	     ; [2]|=4	Send start bit
	lds	R26, dtn+0	     ;		Compute first data bit date
	lds	R27, dtn+1	     ;
	sbiw	R26, (TBITTX2-4+PSC/2)/PSC ;		Compensate bit isr / send delay
	add	R24, R26
	adc	R25, R27
	out	MATCHH, R25
	out	MATCHL, R24
	sts	match+0, R24
	sts	match+1, R25
	.endif

	enable_match R24
	;; .if DBG_PUTBYTE
	;; cbi	DBGPORT, DBGBIT
	;; .endif

	ret
	.endif			; SWUART_TX


	.if 0
	.fail TSTART1		; Elapsed cycles between start interrupt and date sampling
	.fail TSTART2		; Total isr_start cycles
	.fail TBITRX1		; Elapsed cycles between bit interrupt and bit sampling
	.fail TBITRX2		; Total isr_bit cycles (standard case)
	.fail TBITTX2
	.endif

	.ifdef SWUART_TDATA
 	.section .data
 	.global swuart_tstart1
 	.global swuart_tstart2
 	.global swuart_tbitrx1
 	.global swuart_tbitrx2
 	.global swuart_tbittx2
swuart_tstart1:	.byte	TSTART1
swuart_tstart2:	.byte	TSTART2
swuart_tbitrx1:	.byte	TBITRX1
swuart_tbitrx2:	.byte	TBITRX2
swuart_tbittx2:	.byte	TBITTX2
	.endif
