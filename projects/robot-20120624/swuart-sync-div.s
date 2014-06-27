
	;; u16 syncd ( u8 min_ratio )
	;; 
	;; Measure low-level durations of 1 bit (dt1) and n bits (dtn) to
	;; determine baudrate.
	;; 
	;; Returns dt1 in SYSHZ cycles. min_ratio indicates the lowest dtn/dt1
	;; value acceptable.
	;;
	;; dtn and dt1 are measured in units of 5 cycles.
	;; 
	;; dtn overflows at 65535, i.e. 65535*5 cycles
	;; That means that the longest low-level duration must be < 327675 cycles
	;;
	;; This routine can not synchronize at speeds below SYSHZ/32767 bps
	;; using 10-bits low-level characters.
	;; 
	;; FT232R seems to have a bug under Linux-3.0: at 1 kbps, random
	;; duration of 10 bits low!
	;; 
	;; GCC call-used registers: R18..R27, R30, R31
	;;
	.section	.text.syncd,"ax",@progbits
syncd:
	mov	R21, R24	; Store min dtn/dt1
	ldi	R18, 0xFF	; dt1 = 65535	one bit duration	(R19:R18)
	ldi	R19, 0xFF
	ldi	R30, 0		; dtn = 0	n bits duration		(R31:R30)
	ldi	R31, 0

1:	ldi	R24, 0		; Measure low level duration		(R25:R24)
	ldi	R25, 0		;
2:	sbis	RXDPIN, RXDBIT	;		Wait RXD == 1
	rjmp	2b		;
2:	sbic	RXDPIN, RXDBIT	; [1/2]		Wait RXD == 0
	rjmp	2b		; [2]

	.if DBG_SYNC1
	sbi	DBGPORT, DBGBIT
	.endif

2:	adiw	R24, 1		; [2]	|	Measure (units of 5 cycles)
	sbis	RXDPIN, RXDBIT	; [1]/2	|
	rjmp	2b		; [2]	|= 5

	.if DBG_SYNC2
	cbi	DBGPORT, DBGBIT
	.endif

	;; Update dt1 or dtn
	;;
	ldi	R20, 0
	cp	R24, R18	; IF t < dt1
	cpc	R25, R19
	brcc	2f
	inc	R20
	movw	R18, R24	; THEN dt1 = t

2:	cp	R30, R24	; IF dtn < t
	cpc	R31, R25
	brcc	2f
	inc	R20
	movw	R30, R24	; THEN dtn = t

	;; Measure again if 0 or 2 updates
	;;
2:	cpi	R20, 1
	brne	1b

2:	.if DBG_SYNC3
	sbi	DBGPORT, DBGBIT
	.endif

	;; Compute q=dtn/dt1 with 3 bits for decimals (i.e. q*8)
	;;
	movw	R24, R30	; R25:R24 = dtn
	movw	R22, R18	; R23:R22 = dt1
	ldi	R20, 3		; 3 bits of decimals
	rcall	div_1616d

	.if DBG_SYNC4
	cbi	DBGPORT, DBGBIT
	.endif

	and	R25, R25
	brne	syncd		; Restart from beginning if q*8 >= 256
	subi	R24, -1		; add 0.125 to dtn/dt1
	lsr	R24
	lsr	R24
	brcs	1b
	lsr	R24
	brcs	1b		; Measure again if |decimal| > 0.125
	cp	R24, R21
	brcs	1b		; Measure again if dtn/dt1 < min
	cpi	R24, 11
	brcc	syncd		; Restart from beginning if dtn/dt1 >= 11

	;; Compute dt1 = dtn/q and return dt1 in SYSHZ cycles unit
	;;
	;; dtn and dt1 are measured in units of 5 cycles.
	;;
	;; Multiplying dtn by 5 before calculating dtn/q would reduce the range
	;; over which the computation can be done without overflow.
	;; 
	;; So, calculate dt1=dtn/q with 2 bits for decimals. The result
	;; is actually dt1*4. Then add (dt1*4)/4 to obtain dt1*5.
	;;
	mov	R22, R24	; q
	ldi	R23, 0
	movw	R24, R30	; dtn
	ldi	R20, 2		; 2 decimals
	rcall	div_1616d
	movw	R22, R24
	lsr	R23
	ror	R22
	lsr	R23
	ror	R22
	add	R24, R22	; dt1 in SYSHZ cycles
	adc	R25, R23
	ret


	.section	.text.chksync2,"ax",@progbits
chksync2:
	;; Compute q=dtn/dt1 with 2 bits for decimals (i.e. q*4)
	;;
	movw	R30, R24	; R25:R24 = dtn
	mov	R21, R20	; Store qmin
	ldi	R20, 2		; 2 bits of decimals
	rcall	div_1616d

	and	R25, R25
	brne	1f		; Restart from beginning if q*4 >= 256
	subi	R24, -1		; add 0.25 to dtn/dt1
	lsr	R24
	lsr	R24
	brcs	1f
	cp	R24, R21
	brcs	1f		; Measure again if dtn/dt1 < min
	cpi	R24, 11
	brcc	1f		; Restart from beginning if dtn/dt1 > 10.25

	;; Compute dt1 = dtn/q
	;;
	mov	R22, R24
	ldi	R23, 0
	movw	R24, R30
	ldi	R20, 0
	rcall	div_1616d
	ret

1:	ldi	R24, 0
	ldi	R25, 0
	ret


	.section	.text.chksync3,"ax",@progbits
chksync3:
	;; Compute q=dtn/dt1 with 3 bits for decimals (i.e. q*8)
	;;
	movw	R30, R24	; R25:R24 = dtn
	mov	R21, R20	; Store qmin
	ldi	R20, 3		; 2 bits of decimals
	rcall	div_1616d

	and	R25, R25
	brne	1f		; Restart from beginning if q*8 >= 256
	subi	R24, -1		; add 0.125 to dtn/dt1
	lsr	R24
	lsr	R24
	brcs	1f
	lsr	R24
	brcs	1f
	cp	R24, R21
	brcs	1f		; Measure again if dtn/dt1 < min
	cpi	R24, 11
	brcc	1f		; Restart from beginning if dtn/dt1 > 10

	;; Compute dt1 = dtn/q
	;;
	mov	R22, R24
	ldi	R23, 0
	movw	R24, R30
	ldi	R20, 0
	rcall	div_1616d
	ret

1:	ldi	R24, 0
	ldi	R25, 0
	ret
