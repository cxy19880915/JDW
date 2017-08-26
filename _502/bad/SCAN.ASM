;;=====================================================================================
;;
;;Module Name:	F_KeyBoardScan
;;
;;Use:					A,R0~R5,X,Y
;;
;;=====================================================================================
F_KeyBoardScan:
#IF IRFunction
	bbs	R_KeyFlag.B_IRKeyScan,L_KeyBoardScan
	call	F_MainKeyBoardScan
	bbs	R_KeyFlag.B_KeyAction,L_KeyBoardScan_Exit
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_KeyBoardScan_Exit

L_KeyBoardScan:
	lda	R_IRKeyBuffer
	cmp	R_IRKeyTemp
	beq	L_KeyBoardScan_Exit
	cmp	#080H
	bcs	L_IRBreackKey
	bbs	R_IRKeyTemp.7,L_RightPressKey
	set1	R_IRKeyTemp.7
	lda	R_IRKeyTemp
	and	#01111111B
	tay
	lda	!T_GetIRKeyValue+Y
	or	#080H
	sta	R_KeyBuffer
	set1	R_KeyFlag.B_KeyAction
	ldm	R_KeyminderBufferCol0,#0
	ldm	R_KeyminderBufferCol1,#0
	ldm	R_KeyminderBufferCol2,#0
	ldm	R_KeyminderBufferCol3,#0
	clr1	R_KeyFlag.B_IRKeyScan
L_KeyBoardScan_Exit:
	ret

L_RightPressKey:
;	lda	R_IRKeyBuffer
	sta	R_IRKeyTemp
	tay
	lda	!T_GetIRKeyValue+Y
	beq	L_KeyBoardScan_Exit
	sta	R_KeyBuffer
	ldy	#4
	mul	
	tay
	lda	!T_GetKeyColValue+Y
	sta	R_KeyminderBufferCol0
	inc	Y
	lda	!T_GetKeyColValue+Y
	sta	R_KeyminderBufferCol1
	inc	Y
	lda	!T_GetKeyColValue+Y
	sta	R_KeyminderBufferCol2
	inc	Y
	lda	!T_GetKeyColValue+Y
	sta	R_KeyminderBufferCol3
	set1	R_KeyFlag.B_KeyAction
	set1	R_KeyFlag.B_IRKeyScan
	ret

L_IRBreackKey:
	bbs	R_IRKeyTemp.7,L_AllIRBreackKey
	set1	R_IRKeyTemp.7
	lda	R_IRKeyTemp
	and	#01111111B
	tay
	lda	!T_GetIRKeyValue+Y
	or	#080H
	sta	R_KeyBuffer
	set1	R_KeyFlag.B_KeyAction	
	ldm	R_KeyminderBufferCol0,#0
	ldm	R_KeyminderBufferCol1,#0
	ldm	R_KeyminderBufferCol2,#0
	ldm	R_KeyminderBufferCol3,#0
	clr1	R_KeyFlag.B_IRKeyScan	
	ret

L_AllIRBreackKey:
;	lda	R_IRKeyBuffer
	sta	R_IRKeyTemp
	ldm	R_KeyminderBufferCol0,#0
	ldm	R_KeyminderBufferCol1,#0
	ldm	R_KeyminderBufferCol2,#0
	ldm	R_KeyminderBufferCol3,#0
	clr1	R_KeyFlag.B_IRKeyScan
	clr1	R_KeyFlag.B_KeyAction
	ret
#ENDIF	
	
;;=====================================================================================
;;
;;Module Name:	F_MainKeyBoardScan
;;
;;Use:	A,R0~R5,X,Y
;;
;;=====================================================================================
F_MainKeyBoardScan:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	beq	L_MainKeyBoardScan
	jmp	L_MainKeyBoardBreack
	
L_MainKeyBoardScan:	
	call	F_GetADC1Value
	beq	L_MainIOKeyInput
	sta	R5
	ldm	R0,#3
L_MainKeyBoardScan_Loop:
	bbc	R_Flag.B_128Hz,L_MainKeyBoardScan_Loop
	clr1	R_Flag.B_128Hz
	dec	R0
	bne	L_MainKeyBoardScan_Loop
	call	F_GetADC1Value
	cmp	R5
	bne	L_MainIOKeyInput_Exit
	sta	R_KeyBuffer
	jmp	L_KeyPressed
L_MainIOKeyInput_Exit:
	ret	
	
L_MainIOKeyInput:
	ldm	R0,#0
	ldcb	R_KeyIO0.B_KeyIO0
	stc	R0.0
	lda	R0
	beq	L_MainKeyBoardScan_Exit         		;;Illegal keyed in (inactive)
		
	ldm	R1,#3
L_KeyDebounce_Loop:
	bbc	R_Flag.B_128Hz,L_KeyDebounce_Loop
	clr1	R_Flag.B_128Hz
	dec	R1
	bne	L_KeyDebounce_Loop
	
	ldm	R1,#0
	ldcb	R_KeyIO0.B_KeyIO0
	stc	R1.0
	lda	R1
	beq	L_MainKeyBoardScan_Exit         		;;Illegal keyed in (inactive)
  eor	R0
  bne	L_MainKeyBoardScan_Exit
	
  ldm	R_KeyBuffer,#1
	ldm	R1,#00000001B	                  		;;Check bit from bit0
L_CaculateKeyLoop:
  lda	R0
	and	R1			          									;;Exclusive-OR new and old sense data
	bne	L_IsMainIOKey              					;;Key depressed
  inc	R_KeyBuffer               					;;KeyBuffer = KeyBuffer + 1
  asl	R1
	bcc	L_CaculateKeyLoop
L_MainKeyBoardScan_Exit:	
	ret			

L_IsMainIOKey:
	ldy	R_KeyBuffer
	lda	!T_IOKeyValueTable+Y
	beq	L_MainKeyBoardScan_Exit
	sta	R_KeyBuffer
L_KeyPressed:                             			;;Key depressed
	set1	R_KeyFlag.B_KeyAction
	ldy	#4
	lda	R_KeyBuffer
	mul
	tay
	lda	!T_GetKeyColValue+Y
	sta	R_KeyminderBufferCol0
;	inc	Y
	lda	!(T_GetKeyColValue+1)+Y
	sta	R_KeyminderBufferCol1
;	inc	Y
	lda	!(T_GetKeyColValue+2)+Y
	sta	R_KeyminderBufferCol2
;	inc	Y
	lda	!(T_GetKeyColValue+3)+Y
	sta	R_KeyminderBufferCol3
	ret
	
;;===================================================================
L_MainKeyBoardBreack:
	ldm	R0,#32									;×Ü¹²¼üÊý
	ldm	R5,#1
	lda	R_KeyminderBufferCol0
	sta	R1
	lda	R_KeyminderBufferCol1
	sta	R2
	lda	R_KeyminderBufferCol2
	sta	R3
	lda	R_KeyminderBufferCol3
	sta	R4
L_MainKeyBoardBreack_Loop:
	lsr	R4
	ror	R3
	ror	R2
	ror	R1
	bcs	L_CheckMainKeyBoardBreack
	inc	R5
	dec	R0
	bne	L_MainKeyBoardBreack_Loop
L_MainKeyBoardBreack_Exit:
	ret	
	
L_CheckMainKeyBoardBreack:	
	call	F_GetADC1Value
	cmp	R5
	beq	L_MainKeyBoardBreack_Exit
	call	F_IOKeyBreack
	cmp	R5
	beq	L_MainKeyBoardBreack_Exit

	ldm	R0,#3
L_CheckMainKeyBoardBreack_Lp:
	bbc	R_Flag.B_128Hz,L_CheckMainKeyBoardBreack_Lp
	clr1	R_Flag.B_128Hz
	dec	R0
	bne	L_CheckMainKeyBoardBreack_Lp
	
	call	F_GetADC1Value
	cmp	R5
	beq	L_MainKeyBoardBreack_Exit
	call	F_IOKeyBreack
	cmp	R5
	beq	L_MainKeyBoardBreack_Exit
	ldm	R_KeyminderBufferCol0,#0
	ldm	R_KeyminderBufferCol1,#0
	ldm	R_KeyminderBufferCol2,#0
	ldm	R_KeyminderBufferCol3,#0
	lda	R5
	sta	R_KeyBuffer
	set1	R_KeyBuffer.7
	set1	R_KeyFlag.B_KeyAction
	ret
	
;;========================================================================
;;
;;Module Name:	F_IOKeyBreack
;;
;;========================================================================
F_IOKeyBreack:
	ldm	R0,#0
	ldcb	R_KeyIO0.B_KeyIO0
	stc	R0.0

	ldm	R1,#00000001B
	ldm	R2,#1
L_IOKeyBreack_Loop:
	lda	R1
	and	R0
	bne	L_IOKeyBreack
	inc	R2
	asl	R1
	bcc	L_IOKeyBreack_Loop
	ldm	R2,#0
L_IOKeyBreack:	
	ldy	R2
	lda	!T_IOKeyValueTable+Y
L_IOKeyBreack_Exit:
	ret
	
;;========================================================================
;;
;;Module Name:	F_GetADC1Value
;;
;;Input:				Non
;;
;;Output:				A
;;
;;Use:					A,X,Y,R0,R1
;;
;;========================================================================
F_GetADC1Value:
	lda	#C_ADC_KeyChannel
	call	F_GetADCValue
	ldy	#0
L_GetADC1Value_Loop:	
	setc
	lda	R0
	sbc	!T_ADCValueTable+Y
	inc	Y
	lda	R1
	sbc	!T_ADCValueTable+Y
	inc	Y
	bcs	L_GetADC1Value_Loop
	tya
	lsr	A
	tay
	lda	!T_ADCKeyValueTable+Y
L_GetADC1Value_Exit:	
	ret
;
;
;;
;;