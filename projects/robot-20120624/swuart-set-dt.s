
	;; Set dtn and dt0 in SYSHZ cycles according to calculated delays and
	;; timer prescaler
	;; 
	.section	.text.setdt,"ax",@progbits
setdt:
	movw	R26, R24	; R25:R24 = dtn in cpu cycles

	;; Compute dtn in timer prescaled units
	;;
	.if PSC > 1
	rcall applydiv
	.endif

	;; Store dtn
	;;
	sts	dtn, R24
	.if MATCHW==16
	sts	dtn+1, R25
	.endif

	;; Compute dt0 = dtn + dtn/2 - dtn/8 - delay (cpu cycles)
	;;
	DELAY=TSTART1+TBITRX1
	movw	R24, R26
	lsr	R27
	ror	R26
	add	R24, R26
	adc	R25, R27
	lsr	R27
	ror	R26
	lsr	R27
	ror	R26
	sub	R24, R26
	.if MATCHW==16
	sbc	R25, R27
	.endif
	subi	R24, DELAY & 0xFF
	.if MATCHW==16
	sbci	R25, DELAY >> 8
	.endif

	.if PSC > 1
	rcall applydiv
	.endif

	;; Store dt0
	;; 
	sts	dt0, R24
	.if MATCHW==16
	sts	dt0+1, R25
	.endif
	ret


	.section	.text.applydiv,"ax",@progbits
	.if PSC > 1
applydiv:
	.if PSC==8
	PSCOK=1
	DIVLOOP=1
	ldi	R18, 3
	.elseif PSC==64
	PSCOK=1
	DIVLOOP=1
	ldi	R18, 6
	.elseif PSC==256
	PSCOK=1
	DIVLOOP=0
	.endif
	.if PSCOK==0
	.error "SWUART_TIMER_CLKHZ value not handled."
	.endif
	.if DIVLOOP
1:	lsr	R25
	ror	R24
	dec	R18
	brne	1b
	.else
	mov	R24, R25
	eor	R25, R25
	.endif
	ret
	.endif
