;;======================================================================================
;;
;;Module Name:	F_ReceiveIR
;;
;;======================================================================================
F_ReceiveIR:
#IF IRFunction
	inc	R_IRIntervalLo
	bne	L_IRIntervalNonCarry
	inc	R_IRIntervalHi
L_IRIntervalNonCarry:
	setc
	lda	R_IRIntervalLo
	sbc	#0B0H
	lda	R_IRIntervalHi
	sbc	#004H
	bcc	L_IRIntervalNonBorrow
	dec	R_IRIntervalLo
	set1	R_IRKeyBuffer.7
	ldm	R_IRKeyStore,#00
	
L_IRIntervalNonBorrow:
	lda	R_IRKeyStore
	beq	L_ReceiveIR
	lda	R_IRKeyTemp
	cmp	R_IRKeyBuffer
	bne	L_ReceiveIR
	lda	R_IRKeyStore
	sta	R_IRKeyBuffer
	ldm	R_IRKeyStore,#00
	
L_ReceiveIR:
	lda	R_IRMode
	bne	L_IRProcessMode1	

;;======================================================================================
L_IRProcessMode0:	
	bbs	R_IRPin.B_IRPin,F_RepeatMode0
	inc	R_IRIIRTime
	lda	R_IRIIRTime
	cmp	#2
	bcc	L_IRReceive_Exit
	ldm	R_IRMode,#C_IRMode1							;检查下降沿 
	set1	R_IRFlag.B_IRBitLow
	lda	R_IRIIRTime
	sta	R_IRBitLowTime
	sta	R_IRBitTime
	lda	#00
	sta	R_IRIIRTime
	sta	R_IRBitCounter
	sta	R_IRBit0
	sta	R_IRBit1
	sta	R_IRBit2
	sta	R_IRBit3
L_IRReceive_Exit:	
	ret
	
;;======================================================================================
L_IRProcessMode1:
	bbs	R_IRFlag.B_IRBitLow,L_IRBitProcessLow
	jmp	L_IRBitProcessHigh
L_IRBitProcessLow:	
	bbc	R_IRPin.B_IRPin,L_IRBitProcessLow_1				;检查上升沿 			
	inc	R_IRIIRTime
	lda	R_IRIIRTime
	cmp	#2
	bcc	L_IRBitProcessLow_2
	inc	R_IRBitLowTime
	setc
	lda	R_IRBitLowTime
	sbc	R_IRIIRTime
	sta	R_IRBitLowTime
	ldm	R_IRIIRTime,#0
	clr1	R_IRFlag.B_IRBitLow
	jmp	L_IRBitProcessLow_3

L_IRBitProcessLow_1:	
	ldm	R_IRIIRTime,#0
L_IRBitProcessLow_2:	
	inc	R_IRBitLowTime
L_IRBitProcessLow_3:
	inc	R_IRBitTime
	lda	R_IRBitTime
	cmp	#82
	bcs	F_RepeatMode0						;;F_RepeatIR
L_IRBitProcessLow_Exit:
	ret

;;======================================================================================
F_RepeatMode0:
	clr1	R_IRFlag.B_IRBitLow
	lda	#0
;;	sta	R_IRKeyStore
	sta	R_IRMode
;	sta	R_IRBitCounter
	sta	R_IRIIRTime
	sta	R_IRBitTime
	sta	R_IRBitLowTime
;	sta	R_IRBit0
;	sta	R_IRBit1
;	sta	R_IRBit2
;	sta	R_IRBit3
L_RepeatMode0_Exit:	
	ret

;;======================================================================================
L_IRBitProcessHigh_1:
	ldm	R_IRIIRTime,#0
L_IRBitProcessHigh_2:
	inc	R_IRBitTime
	lda	R_IRBitTime
	cmp	#123
	bcs	F_RepeatMode0						;;F_RepeatIR
L_IRBitProcessHigh_Exit:
	ret

;;---------------------------------------------------------------------------------------
F_CheckIRSynBit:
	lda	R_IRBitTime
	cmp	#72		;(70+2)
	bcc	F_RepeatMode0						;;F_RepeatIR
	lda	R_IRBitLowTime
	cmp	#50
	bcc	F_RepeatMode0						;;F_RepeatIR
	ldm	R_IRIntervalLo,#0
	ldm	R_IRIntervalHi,#0
	ldm	R_IRBitCounter,#0
	jmp	L_GetNextIRBit

;;---------------------------------------------------------------------------------------
L_IRBitProcessHigh:	
	bbs	R_IRPin.B_IRPin,L_IRBitProcessHigh_1				;检查一位结束 
	inc	R_IRIIRTime
	lda	R_IRIIRTime
	cmp	#2
	bcc	L_IRBitProcessHigh_2
	inc	R_IRBitTime
	lda	R_IRBitTime
	cmp	#8		;(2+6)
	bcc	F_RepeatMode0						;;F_RepeatIR
	cmp	#30		;(2+28)
	bcs	F_CheckIRSynBit
	lda	R_IRBitCounter
	beq	F_RepeatMode0						;;F_RepeatIR
L_StoreIRBit:
	setc
	lda	R_IRBitTime
	sbc	#16		;(2+14)
	ror	R_IRBit3
	ror	R_IRBit2
	ror	R_IRBit1
	ror	R_IRBit0
	lda	R_IRBitCounter
	cmp	#32
	bcc	L_GetNextIRBit

L_IRHaveReceive:
	lda	#C_IRCustomerCode1
	cmp	R_IRBit1
	bne	L_RepeatIR
	lda	R_IRBit0
	cmp	#C_IRCustomerCode0
	bne	L_RepeatIR
	lda	R_IRBit2
	eor	#0FFH
	cmp	R_IRBit3
	bne	L_RepeatIR
	lda	R_IRBit2
	cmp	#C_MaxIRCode
	bcs	L_RepeatIR
	ldm	R_IRIntervalLo,#0
	ldm	R_IRIntervalHi,#0
	ldm	R_IRKeyStore,#0
	inc	R_IRBit2
	lda	R_IRKeyBuffer
	cmp	R_IRBit2
	bne	L_IsIRPressKey
L_IsIRBreackKey:
#IF ContinueIRSyc
	set1	R_IRKeyBuffer.7			
	lda	R_IRBit2							
	sta	R_IRKeyStore					
#ELSE
#ENDIF
	jmp	F_RepeatMode0

L_IsIRPressKey:
	lda	R_IRBit2
	sta	R_IRKeyBuffer
	jmp	F_RepeatMode0

L_GetNextIRBit:
	inc	R_IRBitCounter
	lda	R_IRIIRTime
	sta	R_IRBitLowTime
	sta	R_IRBitTime
	ldm	R_IRIIRTime,#0
	set1	R_IRFlag.B_IRBitLow
L_IRHaveReceive_Exit:
	ret	

;;-------------------------------------------------------------------------------
L_RepeatIR:
	ldm	R_IRKeyStore,#0
	set1	R_IRKeyBuffer.7	
	jmp	F_RepeatMode0
#ENDIF	
L_RepeatIR_Exit:
	ret	

;;======================================================================================
;;
;;Module Name:	F_ResetIR
;;
;;======================================================================================
F_ResetIR:
#IF IRFunction
	lda	#080H
	sta	R_IRKeyBuffer
	sta	R_IRKeyTemp
	clr1	R_IRFlag.B_IRBitLow	
	lda	#0
	sta	R_IRKeyStore
	sta	R_IRMode
;	sta	R_IRBitCounter
	sta	R_IRIIRTime
	sta	R_IRBitTime
	sta	R_IRBitLowTime
;	sta	R_IRBit0
;	sta	R_IRBit1
;	sta	R_IRBit2
;	sta	R_IRBit3
	sta	R_IRIntervalLo
	sta	R_IRIntervalHi
#ENDIF	
L_ResetIR_Exit:
	ret		
;
;
;;
;;