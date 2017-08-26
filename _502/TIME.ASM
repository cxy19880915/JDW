;;=====================================================================================
;;
;;Module Name:	F_CheckTime
;;
;;=====================================================================================
F_CheckTime:
	call	F_CheckKeyTime

	lda	R_HalfSecond
	cmp	#2
	bcc	L_CheckTime_Exit
	dec	R_HalfSecond
	dec	R_HalfSecond
L_CheckTime_Exit:
	ret

;;===================================================================================
;;
;;Module Name:	F_CheckKeyTime
;;
;;==================================================================================
F_CheckKeyTime:
	bbc	R_Flag.B_2HzKey,L_CheckKeyTime_Exit
	clr1	R_Flag.B_2HzKey
	lda	R_KeyTime
	beq	L_CheckKeyTime_Exit
	dec	R_KeyTime
	bne	L_CheckKeyTime_Exit
	bbs	R_KeyminderBufferCol1.7,L_PowerKey3s
L_CheckKeyTime_Exit:
	ret	
	
;;========================================================
L_PowerKey3s:
	jmp	L_PowerKey	

;;===========================================================================
;;
;;Module Name:	F_CheckBackNormalTime
;;
;;===========================================================================	
F_CheckBackNormalTime:
	lda	R_SetTimeFlag
	beq	L_CheckBackNormalTime
	lda	R_BackNormalTimeLo
	or	R_BackNormalTimeHi
	beq	L_CheckBackNormalTime
	setc
	lda	R_BackNormalTimeLo
	sbc	#01
	sta	R_BackNormalTimeLo
	lda	R_BackNormalTimeHi
	sbc	#00
	sta	R_BackNormalTimeHi
	bcs	L_CheckBackNormalTime_Exit
L_CheckBackNormalTime:	
	ldm	R_BackNormalTimeLo,#0
	ldm	R_BackNormalTimeHi,#0
	lda	R_SetTimeFlag
	beq	L_CheckBackNormalTime_Exit
	ldm	R_SetTimeFlag,#C_NonSet
	call	F_DisplayLed
L_CheckBackNormalTime_Exit:
	ret				
	
;;===========================================================================
;;
;;Module Name:	F_SetBackNormalTime
;;
;;===========================================================================	
F_SetBackNormalTime:
	ldm	R_BackNormalTimeLo,#040H						;5s
	ldm	R_BackNormalTimeHi,#001H		
L_SetBackNormalTime_Exit:
	ret
;
;
;;
;;