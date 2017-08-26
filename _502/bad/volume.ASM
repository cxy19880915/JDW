;;======================================================================================
;;
;;Module Name:	F_CheckVolume
;;
;;=====================================================================================
F_CheckVolume:
	lda	R_MainMode
	beq	L_ClearCoder1
	lda	R_SetTimeFlag
	cmp	#C_SetVolume
	beq	L_CheckVolume
	lda	R_CoderTurnL1
	or	R_CoderTurnR1
	cmp	#1
	bcc	L_CheckVolume_Exit
L_CheckVolume:
	lda	R_KeyminderBufferCol0
	and	#00000110B
	beq	L_CoderAdjustVolume
	jmp	L_ButtomVolume
L_ClearCoder1:
	ldm	R_CoderTurnL1,#0
	ldm	R_CoderTurnR1,#0
L_CheckVolume_Exit:
	ret		

L_CoderAdjustVolume:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_ClearCoder1
	
	lda	R_CoderTurnL1
	or	R_CoderTurnR1
	beq	L_CheckVolume_Exit
	bbc	R_Flag1.B_MuteFlag,L_CoderVolume
	lda	R_Volume
	beq	L_CoderVolume
	cmp	#1
	bne	L_Coder1UpDn
	lda	R_CoderTurnR1
	beq	L_Coder1UpDn
	clr1	R_Flag1.B_MuteFlag	
	call	F_DisplayLed
	jmp	L_TurnVolumeDown
L_Coder1UpDn:	
	call	F_SetVolumeMute
	lda	#02
	call	F_Delay7_8125ms
	call	F_MuteOffCtrl
	lda	#05
	call	F_Delay7_8125ms
L_CoderVolume:		
	clr1	R_Flag1.B_MuteFlag	
	call	F_DisplayLed
	lda	R_CoderTurnR1
	bne	L_TurnVolumeDown
	jmp	L_TurnVolumeUp
L_TurnVolumeDown:
	ldm	R_CoderTurnL1,#0
	ldm	R_CoderTurnR1,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetVolume
	call	F_DisplayLed
	lda	R_Volume
	cmp	#1
	bne	L_TurnVolumeDown1
	ldm	R_Volume,#0		
	call	F_SetVolumeMute
	call	F_MuteOnCtrl
	call	F_PowerOffLed
	lda	#10
	call	F_Delay7_8125ms
	call	F_DisplayLed
	jmp	L_AdjustVolume	
				
L_TurnVolumeDown1:		
	lda	R_Volume
	beq	L_AdjustVolume
	lda	R_Volume
	sta	R0
	lda	#1
	call	F_BCD_Sub
	sta	R_Volume
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed
	jmp	L_AdjustVolume				

;;---------------------------------------------------------------------------	
L_TurnVolumeUp:
	ldm	R_CoderTurnL1,#0
	ldm	R_CoderTurnR1,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetVolume
	call	F_DisplayLed
	lda	R_Volume
	bne	L_TurnVolumeUp1
	inc	R_Volume
	call	F_SetVolumeMute
	call	F_PowerOffLed
	call	F_MuteOffCtrl
	lda	#10
	call	F_Delay7_8125ms
	call	F_DisplayLed
	jmp	L_AdjustVolume		
	
L_TurnVolumeUp1:		
	lda	R_Volume
	cmp	#C_MaxVolume
	bcs	L_AdjustVolume
	ldm	R0,#1
	lda	R_Volume
	call	F_BCD_Add
	sta	R_Volume
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed	
L_AdjustVolume:
	lda	R_Volume
	sta	R_VolumeTemp
	call	F_StoreVolume	
	jmp	F_SetVolume

;;=====================================================================================
L_ButtomVolume:
	ldm	R_CoderTurnL1,#0
	ldm	R_CoderTurnR1,#0
	lda	R_SetTimeFlag
	cmp	#C_SetVolume
	bne	L_ChangeVolume_Exit
	dec	R_VolumeTime
	lda	R_VolumeTime
	cmp	#1
	bcs	L_ChangeVolume_Exit	
F_ChangeVolume:	
	ldm	R_VolumeTime,#3
	bbS	R_KeyminderBufferCol0.1,L_TurnVolumeUp
	jmp	L_TurnVolumeDown
L_ChangeVolume_Exit:
	ret	
	
;;======================================================================================
;;
;;Module Name:	F_CheckBass
;;
;;=====================================================================================
F_CheckBass:
#IF BassFunction
	lda	R_MainMode
	beq	L_ClearCoder2
	lda	R_SetTimeFlag
	cmp	#C_SetBass
	beq	L_CheckBass
	lda	R_CoderTurnL2
	or	R_CoderTurnR2
	cmp	#1
	bcc	L_CheckBass_Exit
L_CheckBass:
	lda	R_KeyminderBufferCol2
	and	#00000011B
	beq	L_AdjustBass
	jmp	L_ButtomBass
L_ClearCoder2:
	ldm	R_CoderTurnL2,#0
	ldm	R_CoderTurnR2,#0
L_CheckBass_Exit:
	ret		

L_AdjustBass:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_ClearCoder2
	
	lda	R_CoderTurnL2
	or	R_CoderTurnR2
	beq	L_CheckBass_Exit
	bbc	R_Flag1.B_MuteFlag,L_CoderBass
	lda	R_Volume
	beq	L_CoderBass
	call	F_SetVolumeMute
	lda	#02
	call	F_Delay7_8125ms
	call	F_MuteOffCtrl
	lda	#05
	call	F_Delay7_8125ms
L_CoderBass:		
	clr1	R_Flag1.B_MuteFlag	
	call	F_DisplayLed
	lda	R_CoderTurnR2
	bne	L_TurnBassDown
	jmp	L_TurnBassUp
L_TurnBassDown:
	ldm	R_CoderTurnL2,#0
	ldm	R_CoderTurnR2,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetBass
	call	F_DisplayLed
	lda	R_Bass
	beq	L_SetBass
	dec	R_Bass
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed
L_SetBass:
	call	F_StoreBass
	lda	R_VolumeTemp
	cmp	R_Volume
	bne	L_CheckBass_Exit	
	jmp	F_SetVolume				

;;---------------------------------------------------------------------------	
L_TurnBassUp:
	ldm	R_CoderTurnL2,#0
	ldm	R_CoderTurnR2,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetBass
	call	F_DisplayLed
	lda	R_Bass
	cmp	#C_MaxBass
	bcs	L_SetBass
	inc	R_Bass
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed	
	jmp	L_SetBass

;;=====================================================================================
L_ButtomBass:
	ldm	R_CoderTurnL2,#0
	ldm	R_CoderTurnR2,#0
	lda	R_SetTimeFlag
	cmp	#C_SetBass
	bne	L_ChangeBass_Exit
	dec	R_BassTime
	lda	R_BassTime
	cmp	#1
	bcs	L_ChangeBass_Exit	
F_ChangeBass:	
	ldm	R_BassTime,#3
	bbs	R_KeyminderBufferCol2.0,L_TurnBassUp
	jmp	L_TurnBassDown
#ENDIF	
L_ChangeBass_Exit:
	ret	
	
;;======================================================================================
;;
;;Module Name:	F_CheckTreble
;;
;;=====================================================================================
F_CheckTreble:
#IF TrebleFunction
	lda	R_MainMode
	beq	L_ClearCoder3
	lda	R_SetTimeFlag
	cmp	#C_SetTreble
	beq	L_CheckTreble
	lda	R_CoderTurnL3
	or	R_CoderTurnR3
	cmp	#1
	bcc	L_CheckTreble_Exit
L_CheckTreble:
	lda	R_KeyminderBufferCol2
	and	#00001100B
	beq	L_AdjustTreble
	jmp	L_ButtomTreble
L_ClearCoder3:
	ldm	R_CoderTurnL3,#0
	ldm	R_CoderTurnR3,#0
L_CheckTreble_Exit:
	ret		

L_AdjustTreble:
	lda	R_KeyminderBufferCol0
	or	R_KeyminderBufferCol1
	or	R_KeyminderBufferCol2
	or	R_KeyminderBufferCol3
	bne	L_ClearCoder3
	
	lda	R_CoderTurnL3
	or	R_CoderTurnR3
	beq	L_CheckTreble_Exit
	bbc	R_Flag1.B_MuteFlag,L_CoderTreble
	lda	R_Volume
	beq	L_CoderTreble
	call	F_SetVolumeMute
	lda	#02
	call	F_Delay7_8125ms
	call	F_MuteOffCtrl
	lda	#05
	call	F_Delay7_8125ms
L_CoderTreble:		
	clr1	R_Flag1.B_MuteFlag	
	call	F_DisplayLed
	lda	R_CoderTurnR3
	bne	L_TurnTrebleDown
	jmp	L_TurnTrebleUp
L_TurnTrebleDown:
	ldm	R_CoderTurnL3,#0
	ldm	R_CoderTurnR3,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetTreble
	call	F_DisplayLed
	lda	R_Treble
	beq	L_SetTreble
	dec	R_Treble
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed
L_SetTreble:
	call	F_StoreTreble
	lda	R_VolumeTemp
	cmp	R_Volume
	bne	L_CheckTreble_Exit	
	jmp	F_SetVolume				

;;---------------------------------------------------------------------------	
L_TurnTrebleUp:
	ldm	R_CoderTurnL3,#0
	ldm	R_CoderTurnR3,#0
	call	F_SetBackNormalTime
	ldm	R_SetTimeFlag,#C_SetTreble
	call	F_DisplayLed
	lda	R_Treble
	cmp	#C_MaxTreble
	bcs	L_SetTreble
	inc	R_Treble
	call	F_PowerOffLed
	lda	#08
	call	F_Delay7_8125ms
	call	F_DisplayLed	
	jmp	L_SetTreble

;;=====================================================================================
L_ButtomTreble:
	ldm	R_CoderTurnL3,#0
	ldm	R_CoderTurnR3,#0
	lda	R_SetTimeFlag
	cmp	#C_SetTreble
	bne	L_ChangeTreble_Exit
	dec	R_TrebleTime
	lda	R_TrebleTime
	cmp	#1
	bcs	L_ChangeTreble_Exit	
F_ChangeTreble:	
	ldm	R_TrebleTime,#3
	bbs	R_KeyminderBufferCol2.2,L_TurnTrebleUp
	jmp	L_TurnTrebleDown
#ENDIF	
L_ChangeTreble_Exit:
	ret		

;;============================================================================
;;
;;Module Name:	F_MuteOffCtrl
;;
;;============================================================================
F_MuteOffCtrl:
	lda	R_MainMode
	beq	L_MuteOffCtrl_Exit
	set1	R_MuteCtrl.B_MuteCtrl
L_MuteOffCtrl_Exit:
	ret
	
;;============================================================================
;;
;;Module Name:	F_MuteOnCtrl
;;
;;============================================================================
F_MuteOnCtrl:
	clr1	R_MuteCtrl.B_MuteCtrl
L_MuteOnCtrl_Exit:
	ret	
	
;;====================================================================================
;;
;;Module Name:	F_VolumeRamUp
;;
;;====================================================================================	
F_VolumeRamUp:
#IF VolumeRamUp
	inc	R_VolumeRamUpTime
	lda	R_VolumeRamUpTime
	cmp	#C_VolumeRamUpTime
	bcc	L_VolumeRamUp_Exit
	ldm	R_VolumeRamUpTime,#00
	lda	R_MainMode
	beq	L_VolumeRamUp_Exit
	bbs	R_Flag1.B_MuteFlag,L_VolumeRamUp_Exit
	lda	R_Volume
	cmp	R_VolumeTemp
	bcs	L_VolumeRamUp_Exit
	clrc
	lda	R_Volume
	adc	#1
	sta	R_Volume
	and	#00FH
	cmp	#00AH
	bcc	L_VolumeRamUp
	clrc
	lda	#6
	adc	R_Volume
	sta	R_Volume
L_VolumeRamUp:	
	call	F_SetVolume	
#ENDIF	
L_VolumeRamUp_Exit:
	ret	
;
;
;;
;;