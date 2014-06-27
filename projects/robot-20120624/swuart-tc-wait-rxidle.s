
	;; Wait RXD high for (R24) bits
	;;
	;; GCC call-used registers: R18..R27, R30, R31

	.section	.text.wait_rxidle,"ax",@progbits
wait_rxidle:

	.if COUNTW==8
	.error "Not implemented yet."
	.endif

	rcall	wait_ready

	.if DBG_WAITIDLE
	sbi	DBGPORT, DBGBIT
	.endif

	cbi	MATCHENB, XMATCH

	lds	R18, dtn+0
	lds	R19, dtn+1
	in	R20, COUNTL
	in	R21, COUNTH

1:	mov	R25, R24	; How many bits to wait

2:	add	R20, R18
	adc	R21, R19

	out	MATCHH, R21
	out	MATCHL, R20

3:	clear_matchflg R22

4:	sbis	RXDPIN, RXDBIT
	rjmp	1b		; Restart if RXD==0
	sbis	MATCHFLG, XMATCH
	rjmp	4b
	dec	R25
	brne	2b

	.if DBG_WAITIDLE
	cbi	DBGPORT, DBGBIT
	.endif

	ret
