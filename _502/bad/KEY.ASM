;Time Set		|			-			|		+			|		Audio			|		Mute			|	Volume Down		|	Volume Up		|		Power
;------------------------------------------------------------------------------------------------------
;  Pair     | 播放/暂停 |  快退   |	 快进	      |   下翻      |    上翻       |  Enter      |   Menu    
;------------------------------------------------------------------------------------------------------
;           |           |         |             | Treble Down |  Treble Up    |  Bass Down  |  Bass Up  
;------------------------------------------------------------------------------------------------------
;           |           |         |             |             |               |             |                                      
;------------------------------------------------------------------------------------------------------



;;=====================================================================================================
;;
;;Module Name:	F_KeyDecoder
;;
;;=====================================================================================================
F_KeyDecoder:
	bbc	R_KeyFlag.B_KeyAction,L_KeyDecoder_Exit
	clr1	R_KeyFlag.B_KeyAction
	bbc	R_KeyBuffer.7,L_KeyDecoder
	jmp	F_BreackKeyDecoder
L_KeyDecoder_Exit:
	ret		
	
L_KeyDecoder:	
	ldm	R_KeyTime,#0
	ldm	dpmain+1,#>T_KeyDecoderTable
	ldm	dpmain,#<T_KeyDecoderTable
	lda	R_KeyBuffer
	ldy	#3
	mul
	clrc
	adc	dpmain
	sta	dpmain
	lda	#0
	adc	dpmain+1
	sta	dpmain+1
	jmp	[dpmain]
T_KeyDecoderTable:	
	jmp	L_KeyDecoder_Exit
	jmp	L_KeyDecoder_Exit					;01
	jmp	L_KeyDecoder_Exit					;02
	jmp	L_KeyDecoder_Exit					;03
	jmp	L_KeyDecoder_Exit					;04
	jmp	L_KeyDecoder_Exit					;05
	jmp	L_KeyDecoder_Exit					;06
	jmp	L_KeyDecoder_Exit					;07
	jmp	L_KeyDecoder_Exit					;08
	jmp	L_KeyDecoder_Exit					;09
	jmp	L_KeyDecoder_Exit					;10
	jmp	L_KeyDecoder_Exit					;11
	jmp	L_KeyDecoder_Exit					;12
	jmp	L_KeyDecoder_Exit					;13
	jmp	L_KeyDecoder_Exit					;14
	jmp	L_KeyDecoder_Exit					;15	
	jmp	F_PowerAudioKey						;16
	jmp	L_KeyDecoder_Exit					;17
	jmp	L_KeyDecoder_Exit					;18
	jmp	L_KeyDecoder_Exit					;19
	jmp	L_KeyDecoder_Exit					;20
	jmp	L_KeyDecoder_Exit					;21
	jmp	L_KeyDecoder_Exit					;22
	jmp	L_KeyDecoder_Exit					;23
	jmp	L_KeyDecoder_Exit					;24
	jmp	L_KeyDecoder_Exit					;25
	jmp	L_KeyDecoder_Exit					;26
	jmp	L_KeyDecoder_Exit					;27
	jmp	L_KeyDecoder_Exit					;28
	jmp	L_KeyDecoder_Exit					;29
	jmp	L_KeyDecoder_Exit					;30
	jmp	L_KeyDecoder_Exit					;31
	jmp	L_KeyDecoder_Exit					;32	
	
;;=====================================================================
F_PowerAudioKey:
	ldm	R_KeyTime,#3
L_PowerAudioKey_Exit:
	ret	
	
;;=========================================================================================================
L_PowerKey:
	lda	R_MainMode
	beq	L_PowerOnKey
L_PowerOffKey:
	call	F_PowerOffBT
	call	F_SetVolumeMute
	lda	#3
	call	F_Delay15_625ms	
	ldm	R_SetTimeFlag,#0
	ldm	R_MainMode,#0
	clr1	R_Flag1.B_MuteFlag
	call	F_MuteOnCtrl
	lda	#15
	call	F_Delay15_625ms
	call	F_PowerOffOptical
	call	F_PowerOffAmplify
	call	F_PowerOffLed
	call	F_PowerOffIO
	clr1	R_StandbyCtrl.B_StandbyCtrl
	lda	#20
	call	F_Delay15_625ms
L_PowerOffKey_Exit:		
	ret	
	
L_PowerOnKey:
	lda	R_ModeTemp
	sta	R_MainMode
	set1	R_standbyCtrl.B_standbyCtrl
	call	F_PowerOnIO
	call	F_MuteOnCtrl
	lda	#20
	call	F_Delay15_625ms	
	call	F_PowerOnAmplify
	call	F_SetVolumeMute
	clr1	R_Flag1.B_MuteFlag
	ldm	R_SetTimeFlag,#0
	lda	R_ModeTemp
	sta	R_MainMode
	call	F_DisplayLed
	call	F_SetVolumeChannel
	lda	#C_BTMode
	cmp	R_MainMode
	beq	L_PowerOnBTKey
	lda	#C_AuxMode
	cmp	R_MainMode
	beq	L_PowerOnAuxKey
	call	F_PowerOnOptical
	lda	#3
	call	F_Delay15_625ms
L_PowerOnAuxKey:
	call	F_ClearCoder
	lda	R_VolumeTemp
	sta	R_Volume
	beq	L_PowerOnKey_Exit
	call	F_MuteOffCtrl
	lda	#15
	call	F_Delay15_625ms
#IF VolumeRamUp
	ldm	R_Volume,#1
#ENDIF
	call	F_SetVolume	
L_PowerOnKey_Exit:	
	ret			

L_PowerOnBTKey:
	lda	R_VolumeTemp
	sta	R_Volume
	beq	L_PowerOnBTKey_Over
	call	F_MuteOffCtrl
	lda	#15
	call	F_Delay15_625ms
#IF VolumeRamUp	
	ldm	R_Volume,#1
#ENDIF	
	call	F_SetVolume	
L_PowerOnBTKey_Over:	
	call	F_PowerOnBT
	call	F_ClearCoder
L_PowerOnBTKey_Exit:	
	ret		
	
;;=================================================================
L_TurnToRCAMode:
	bbs	R_Flag.B_RCAMode,L_TurnToOpticalMode
	call	F_PowerOffBT
	set1	R_Flag.B_RCAMode
	jmp	L_TurnToAuxMode	

;;====================================================================================
F_AudioKey:
	lda	R_MainMode
	beq	L_AudioKey_Exit
	lda	R_MainMode
	cmp	#C_AuxMode
	beq	L_TurnToRCAMode
	cmp	#C_BTMode
	bne	L_TurnToBTMode	
	call	F_PowerOffBT
	clr1	R_Flag.B_RCAMode
	jmp	L_TurnToAuxMode
L_TurnToOpticalMode:	
	call	F_PowerOffBT
	ldm	R_MainMode,#C_OpticalMode
	ldm	R_ModeTemp,#C_OpticalMode
	call	F_StoreMode
	ldm	R_SetTimeFlag,#0
	clr1	R_Flag1.B_MuteFlag
	call	F_DisplayLed
	call	F_SetVolumeMute
	lda	#10
	call	F_Delay15_625ms		
	call	F_PowerOnOptical
	call	F_SetVolumeChannel
	lda	#10
	call	F_Delay15_625ms
	call	F_ClearCoder
	lda	R_VolumeTemp
	beq	L_AudioKey_Exit
	call	F_MuteOffCtrl
	lda	#15
	call	F_Delay15_625ms
	lda	R_VolumeTemp
	cmp	R_Volume
	bne	L_AudioKey_Exit
	call	F_SetVolume
L_AudioKey_Exit:
	ret	
	
L_TurnToBTMode:
	ldm	R_MainMode,#C_BTMode
	ldm	R_ModeTemp,#C_BTMode
	call	F_StoreMode
	ldm	R_SetTimeFlag,#0
	clr1	R_Flag1.B_MuteFlag
	call	F_DisplayLed
	call	F_SetVolumeMute
	lda	#10
	call	F_Delay15_625ms	
	call	F_PowerOffOptical
	call	F_SetVolumeChannel
	lda	#10
	call	F_Delay15_625ms
	lda	R_VolumeTemp
	beq	L_TurnToBTMode_Over
	call	F_MuteOffCtrl
	lda	#15
	call	F_Delay15_625ms
	lda	R_VolumeTemp
	cmp	R_Volume
	bne	L_TurnToBTMode_Over
	call	F_SetVolume
L_TurnToBTMode_Over:
	call	F_PowerOnBT	
	call	F_ClearCoder
L_TurnToBTMode_Exit:	
	ret		
	
L_TurnToAuxMode:
;	call	F_PowerOffBT
	ldm	R_MainMode,#C_AuxMode
	ldm	R_ModeTemp,#C_AuxMode
	call	F_StoreFlag
	call	F_StoreMode
	ldm	R_SetTimeFlag,#0
	clr1	R_Flag1.B_MuteFlag
	call	F_DisplayLed
	call	F_SetVolumeMute
	lda	#10
	call	F_Delay15_625ms	
	call	F_PowerOffOptical
	call	F_SetVolumeChannel
	lda	#10
	call	F_Delay15_625ms	
	call	F_ClearCoder
	lda	R_VolumeTemp
	beq	L_TurnToAuxMode_Exit
	call	F_MuteOffCtrl
	lda	#15
	call	F_Delay15_625ms	
	lda	R_VolumeTemp
	cmp	R_Volume
	bne	L_TurnToAuxMode_Exit
	call	F_SetVolume
L_TurnToAuxMode_Exit:	
	ret	

;;=================================================================
L_VolumeUpKey:
L_VolumeDnKey:
	lda	R_MainMode
	beq	L_VolumeKey_Exit
	bbc	R_Flag1.B_MuteFlag,L_VolumeKey
	lda	R_Volume
	beq	L_VolumeKey
	cmp	#1
	bne	L_VolUpDnKey
	bbc	R_KeyminderBufferCol0.1,L_VolumeKey
L_VolUpDnKey:	
	call	F_SetVolumeMute
	lda	#2
	call	F_Delay7_8125ms
	call	F_MuteOffCtrl
	lda	#5
	call	F_Delay15_625ms
	
L_VolumeKey:	
	clr1	R_Flag1.B_MuteFlag
	ldm	R_SetTimeFlag,#C_SetVolume
	call	F_DisplayLed
	call	F_ChangeVolume
	ldm	R_VolumeTime,#30
L_VolumeKey_Exit:
	ret	

;;=====================================================================
L_MuteKey:
	lda	R_MainMode
	beq	L_MuteKey_Exit
	bbc	R_Flag1.B_MuteFlag,L_MuteOnKey
L_MuteOffKey:
	ldm	R_SetTimeFlag,#00
	clr1	R_Flag1.B_MuteFlag
	call	F_DisplayLed
	lda	R_VolumeTemp
	beq	L_MuteKey_Exit
	call	F_SetVolumeMute
	lda	#3
	call	F_Delay15_625ms	
	call	F_MuteOffCtrl
	lda	#10
	call	F_Delay15_625ms	
	lda	R_VolumeTemp
	sta	R_Volume
	call	F_StoreVolume
	call	F_SetVolume
L_MuteKey_Exit:
	ret	
	
L_MuteOnKey:
	ldm	R_SetTimeFlag,#0
	set1	R_Flag1.B_MuteFlag
	call	F_PowerOffLed	
	lda	R_VolumeTemp
	beq	L_MuteKey_Exit
	call	F_SetVolumeMute
	lda	#3
	call	F_Delay15_625ms	
	call	F_MuteOnCtrl
	lda	#10
	call	F_Delay15_625ms	
	lda	R_VolumeTemp
	sta	R_Volume
	call	F_StoreVolume
	ret		
	
;;=================================================================
L_BassUpKey:
L_BassDnKey:
#IF BassFunction
	lda	R_MainMode
	beq	L_BassKey_Exit
	bbc	R_Flag1.B_MuteFlag,L_BassKey
	lda	R_Volume
	beq	L_BassKey
	call	F_SetVolumeMute
	lda	#2
	call	F_Delay15_625ms
	call	F_MuteOffCtrl
	lda	#05
	call	F_Delay15_625ms
L_BassKey:	
	clr1	R_Flag1.B_MuteFlag
	ldm	R_SetTimeFlag,#C_SetBass
	call	F_DisplayLed
	call	F_ChangeBass
	ldm	R_BassTime,#30
#ENDIF	
L_BassKey_Exit:
	ret		
	
;;=================================================================
L_TrebleUpKey:
L_TrebleDnKey:
#IF TrebleFunction
	lda	R_MainMode
	beq	L_TrebleKey_Exit
	bbc	R_Flag1.B_MuteFlag,L_TrebleKey
	lda	R_Volume
	beq	L_TrebleKey
	call	F_SetVolumeMute
	lda	#2
	call	F_Delay15_625ms
	call	F_MuteOffCtrl
	lda	#05
	call	F_Delay15_625ms
L_TrebleKey:	
	clr1	R_Flag1.B_MuteFlag
	ldm	R_SetTimeFlag,#C_SetTreble
	call	F_DisplayLed
	call	F_ChangeTreble
	ldm	R_TrebleTime,#30
#ENDIF	
L_TrebleKey_Exit:
	ret				

;;====================================================================================
;;
;;Module Name:	F_BreackKeyDecoder
;;
;;====================================================================================
F_BreackKeyDecoder:
	clr1	R_KeyBuffer.7
	lda	R_KeyBuffer
	cmp	#16
	beq	L_BreackPowerAudioKey
	ldm	R_KeyTime,#0
L_BreackKeyDecoder_Exit:	
	ret		
	
;;=========================================================
L_BreackPowerAudioKey:
	lda	R_KeyTime
	beq	L_BreackPowerAudioKey_Exit
	ldm	R_KeyTime,#0
	jmp	F_AudioKey
L_BreackPowerAudioKey_Exit:
	ret	
	
;;=====================================================================================
;;
;;Module Name:	F_Delay15_625ms
;;
;;Input:				A(15.625*A(ms))
;;
;;Use:					R0~R7,X,Y
;;
;;=====================================================================================
F_Delay15_625ms:
	push	A
	clr1	R_Flag.B_64Hz
L_Delay15_625ms_Loop:
	call	WDTC
	bbc	R_Flag.B_128Hz,L_Delay15_625ms_Loop
	clr1	R_Flag.B_128Hz
	not1	R_Flag.B_64Hz
	bbc	R_Flag.B_64Hz,L_Delay15_625ms_Loop

	call	F_DisplayLcd

	pop	A
	dec	A
	beq	L_Delay15_625ms_Exit
	push	A
	jmp	L_Delay15_625ms_Loop
L_Delay15_625ms_Exit:
	ret
;
;
;;
;;					