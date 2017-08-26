;;========================================================================
;;
;;Module Name:	F_CheckAuxSleep
;;
;;========================================================================	
F_CheckAuxSleep:
#IF AuxSleep
	lda	R_MainMode
	cmp	#C_AuxMode
	bne	L_CheckAuxSleep_Over
	bbc	R_Flag1.B_ERPFlag,L_CheckAuxSleep_Over	
	lda	R_AuxSleepMinute
	cmp	#C_AuxSleepTime
	bcs	L_CheckAuxSleep
	inc	R_AuxSleepBaseTime
	lda	R_AuxSleepBaseTime
	cmp	#128
	bcc	L_CheckAuxSignal
	ldm	R_AuxSleepBaseTime,#0
	inc	R_AuxSleepSecond
	lda	R_AuxSleepSecond
	cmp	#60
	bcc	L_CheckAuxSignal
	ldm	R_AuxSleepSecond,#0
	inc	R_AuxSleepMinute
	lda	R_AuxSleepMinute
	cmp	#C_AuxSleepTime
	bcc	L_CheckAuxSignal
L_CheckAuxSleep:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_CheckAuxSignal
	ldm	R_AuxSleepMinute,#0
	ldm	R_AuxSleepCounter,#0
	ldm	R_AuxSleepCounterTime,#0
	jmp	L_PowerOffKey
	
L_CheckAuxSignal:		
	inc	R_AuxSleepCounterTime
	lda	R_AuxSleepCounterTime
	cmp	#250
	bcc	L_CheckAuxSignal_L
	ldm	R_AuxSleepCounterTime,#0
	lda	R_AuxSleepCounter
	cmp	#030
	bcs	L_CheckAuxSleep_Over
	ldm	R_AuxSleepCounter,#0
	
L_CheckAuxSignal_L:	
	bbc	R_Flag1.B_AudioIn,L_CheckAuxSleep_Exit
	inc	R_AuxSleepCounter
	jmp	L_CheckAuxSleep_Exit		
	
L_CheckAuxSleep_Over:
F_InitialAuxSleep:
	lda	#0
	sta	R_AuxSleepBaseTime
	sta	R_AuxSleepSecond
	sta	R_AuxSleepMinute
	sta	R_AuxSleepCounter
	sta	R_AuxSleepCounterTime
#ENDIF	
L_CheckAuxSleep_Exit:
	ret

;;=================================================================================
;;
;;Module Name:	F_CheckOpticalSleep
;;
;;=================================================================================
F_CheckOpticalSleep:
#IF OpticalSleep
	lda	R_MainMode
	cmp	#C_OpticalMode
	bne	L_CheckOpticalSleep_Over
	bbc	R_Flag1.B_ERPFlag,L_CheckOpticalSleep_Over
	lda	R_OpticalSleepMinute
	cmp	#C_OpticalSleepTime
	bcs	L_CheckOpticalSleep
	inc	R_OpticalSleepBaseTime
	lda	R_OpticalSleepBaseTime
	cmp	#128
	bcc	L_CheckOpticalSignal
	ldm	R_OpticalSleepBaseTime,#0
	inc	R_OpticalSleepSecond
	lda	R_OpticalSleepSecond
	cmp	#60
	bcc	L_CheckOpticalSignal
	ldm	R_OpticalSleepSecond,#0
	inc	R_OpticalSleepMinute
	lda	R_OpticalSleepMinute
	cmp	#C_OpticalSleepTime
	bcc	L_CheckOpticalSignal
L_CheckOpticalSleep:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_CheckOpticalSignal
	ldm	R_OpticalSleepMinute,#0
	ldm	R_OpticalSleepCounter,#0
	ldm	R_OpticalSleepCounterTime,#0
	jmp	L_PowerOffKey
	
L_CheckOpticalSignal:		
	inc	R_OpticalSleepCounterTime
	lda	R_OpticalSleepCounterTime
	cmp	#250
	bcc	L_CheckOpticalSignal_L
	ldm	R_OpticalSleepCounterTime,#0
	lda	R_OpticalSleepCounter
	cmp	#030
	bcs	L_CheckOpticalSleep_Over
	ldm	R_OpticalSleepCounter,#0
	
L_CheckOpticalSignal_L:	
	bbc	R_Flag1.B_AudioIn,L_CheckOpticalSleep_Exit
	inc	R_OpticalSleepCounter
	jmp	L_CheckOpticalSleep_Exit		
	
L_CheckOpticalSleep_Over:
F_InitialOpticalSleep:
	lda	#0
	sta	R_OpticalSleepBaseTime
	sta	R_OpticalSleepSecond
	sta	R_OpticalSleepMinute
	sta	R_OpticalSleepCounter
	sta	R_OpticalSleepCounterTime
#ENDIF
L_CheckOpticalSleep_Exit:
	ret

;;=================================================================================
;;
;;Module Name:	F_CheckBTSleep
;;
;;=================================================================================
F_CheckBTSleep:
#IF BTSleep
	lda	R_MainMode
	cmp	#C_BTMode
	bne	L_CheckBTSleep_Over
	bbc	R_Flag1.B_ERPFlag,L_CheckBTSleep_Over
	lda	R_BTSleepMinute
	cmp	#C_BTSleepTime
	bcs	L_CheckBTSleep
	inc	R_BTSleepBaseTime
	lda	R_BTSleepBaseTime
	cmp	#128
	bcc	L_CheckBTSignal
	ldm	R_BTSleepBaseTime,#0
	inc	R_BTSleepSecond
	lda	R_BTSleepSecond
	cmp	#60
	bcc	L_CheckBTSignal
	ldm	R_BTSleepSecond,#0
	inc	R_BTSleepMinute
	lda	R_BTSleepMinute
	cmp	#C_BTSleepTime
	bcc	L_CheckBTSignal
L_CheckBTSleep:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_CheckBTSignal
	ldm	R_BTSleepMinute,#0
	ldm	R_BTSleepCounter,#0
	ldm	R_BTSleepCounterTime,#0
	jmp	L_PowerOffKey
	
L_CheckBTSignal:		
	inc	R_BTSleepCounterTime
	lda	R_BTSleepCounterTime
	cmp	#250
	bcc	L_CheckBTSignal_LR
	ldm	R_BTSleepCounterTime,#0
	lda	R_BTSleepCounter
	cmp	#020
	bcs	L_CheckBTSleep_Over
	ldm	R_BTSleepCounter,#0
	
L_CheckBTSignal_LR:	
	bbc	R_Flag1.B_AudioIn,L_CheckBTSleep_Exit
	inc	R_BTSleepCounter
	jmp	L_CheckBTSleep_Exit	
	
L_CheckBTSleep_Over:
F_InitialBTSleep:
	lda	#0
	sta	R_BTSleepBaseTime
	sta	R_BTSleepSecond
	sta	R_BTSleepMinute
	sta	R_BTSleepCounter
	sta	R_BTSleepCounterTime
#ENDIF	
L_CheckBTSleep_Exit:
	ret
	
;;===================================================================
;;
;;Module Name:	F_CheckAudioIn
;;
;;===================================================================	
F_CheckAudioIn:
	inc	R_ERPIITime
	lda	R_ERPIITime
	cmp	#250
	bcc	L_CheckAudioIn
	ldm	R_ERPIITime,#0
	lda	R_ERPIICount
	cmp	#010
	bcc	L_CheckAudioIn_Over
	cmp	#240
	bcs	L_CheckAudioIn_Over
	ldm	R_ERPIICount,#0
	set1	R_Flag1.B_AudioIn
	jmp	L_CheckAudioIn_Exit
	
L_CheckAudioIn:
	bbc	R_AudioDetPin.B_AudioDetPin,L_CheckAudioIn_Exit
	inc	R_ERPIICount	
	jmp	L_CheckAudioIn_Exit
L_CheckAudioIn_Over:
	ldm	R_ERPIICount,#0		
	clr1	R_Flag1.B_AudioIn
L_CheckAudioIn_Exit:
	ret
	
;;======================================================================
;;
;;Module Name:	F_CheckERP
;;
;;======================================================================	
F_CheckERP:
	lda	#C_ADC_Key1Channel
	call	F_GetADCValue
	setc
	lda	R0
	sbc	#000H
	lda	R1
	sbc	#004H
	bcc	L_CheckERP_Exit
	setc
	lda	R0
	sbc	#000H
	lda	R1
	sbc	#00CH
	bcc	L_CheckERP_Over
	clr1	R_Flag1.B_ERPFlag
	jmp	L_CheckERP_Exit
	
L_CheckERP_Over:
	set1	R_Flag1.B_ERPFlag	
L_CheckERP_Exit:
	ret
;
;
;;
;;