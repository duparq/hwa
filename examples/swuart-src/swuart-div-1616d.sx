
	;; u16 div_1616d ( u16 num, u16 denom, u8 decimals )
	;; (R25:R24)        (R25:R24) (R22:R23) (R20)
	;;
	;; Returns 2**decimals * num/denum
	;;
	;; Uses R20, R22..R27
	;; 
	.global	div_1616d
	div_1616d = div
	.section	.text.div_1616d,"ax",@progbits
div:				; [3]
	sub	r26, r26	; [1]
	sub	r27, r27	; [1]
	subi	r20, -17	; [1]	Add decimals
	rjmp	ep		; [2]=8

loop:
	adc	r26, r26	; [1]
	adc	r27, r27	; [1]
	cp	r26, r22	; [1]
	cpc	r27, r23	; [1]
	brcs	ep		; [1/2]
	sub	r26, r22	; [1]
	sbc	r27, r23	; [1]
				;    =6/7
ep:
	adc	r24, r24	; [1]
	adc	r25, r25	; [1]
	dec	r20		; [1]
	brne	loop		; [2]=5

	com	r24		; [1]
	com	r25		; [1]
	ret			; [4]

	;; Cycles < 8+12*(15+decimals)+4+6
	;;        < 18+12*(15+decimals)
