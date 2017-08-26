;;======================================================================================
;;
;;Module Name:	F_SetVolume
;;
;;Input:				R_Volume
;;
;;Use:					A,R0,R1,R2
;;
;;======================================================================================
F_SetVolume:
	lda	R_Volume
	bne	L_SetVolume	
	jmp	F_SetVolumeMute
L_SetVolume:	
	call	F_SetVolume_1
	lda	R2
	bne	F_SetVolume_1
L_SetVolume_Exit:
	ret
	
;;--------------------------------------------------------------------------------------
F_SetVolume_1:
	ldm	R2,#0
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#07fH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					;for total volume
	lda	#098H																			
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#03DH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	R_Volume										
	xcn
	and	#00FH
	ldy	#10
	mul	
	sta	R0
	lda	R_Volume
	and	#00FH
	clrc
	adc	R0
	tay
	lda	!T_VolumeTable+Y						
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					;for total volume
	lda	#098H																			
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#03EH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	R_Volume										
	xcn
	and	#00FH
	ldy	#10
	mul	
	sta	R0
	lda	R_Volume
	and	#00FH
	clrc
	adc	R0
	tay
	lda	!T_VolumeTable+Y						
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	ret		

;;======================================================================================
;;
;;Module Name:	F_SetVolumeMute
;;
;;Use:					A,R0,R1,R2
;;
;;======================================================================================
F_SetVolumeMute:
	call	F_SetVolumeMute_1
	lda	R2
	bne	F_SetVolumeMute_1
L_SetVolumeMute_Exit:
	ret
	
;;--------------------------------------------------------------------------------------
F_SetVolumeMute_1:
	ldm	R2,#0
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#07fH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					;for total volume mute	
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#03DH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#0FFH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
	call	F_D2AudioStartBit					;for total volume mute	
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#03EH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#0FFH												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	ret	

;;======================================================================================
;;
;;Module Name:	F_SetVolumeChannel
;;
;;Use:					A,R0,R1,R2
;;
;;=====================================================================================
F_SetVolumeChannel:
	clr1	R_TC4052A.B_TC4052A
	clr1	R_TC4052B.B_TC4052B
	clr1	R_MixCtrl.B_MixCtrl
	lda	R_MainMode
	beq	L_SetVolumeChannel_Exit
	cmp	#C_AuxMode
	beq	L_SetAuxChannel
	cmp	#C_OpticalMode
	beq	L_SetOpticalChannel
L_SetBTChannel:	
	set1	R_TC4052A.B_TC4052A
	clr1	R_TC4052B.B_TC4052B
	clr1	R_MixCtrl.B_MixCtrl
L_SetVolumeChannel_Exit:
	ret
	
L_SetAuxChannel:
	bbs	R_Flag.B_RCAMode,L_SetRCAChannel
	clr1	R_TC4052A.B_TC4052A
	set1	R_TC4052B.B_TC4052B
	clr1	R_MixCtrl.B_MixCtrl
	ret	
	
L_SetRCAChannel:
	clr1	R_TC4052A.B_TC4052A
	clr1	R_TC4052B.B_TC4052B
	clr1	R_MixCtrl.B_MixCtrl
	ret	

L_SetOpticalChannel:
	clr1	R_TC4052A.B_TC4052A
	set1	R_TC4052B.B_TC4052B
	set1	R_MixCtrl.B_MixCtrl
	ret

;;====================================================================================
;;
;;Module Name:	F_PowerOnAmplify
;;
;;====================================================================================
F_PowerOnAmplify:
	call	!WDTC
	set1	R_TAS5713Power.B_TAS5713Power
	clr1	R_TAS5713Reset.B_TAS5713Reset
	lda	#3
	call	F_Delay7_8125ms
	set1	R_TAS5713Reset.B_TAS5713Reset
	lda	#5
	call	F_Delay7_8125ms
	call	F_TAS5713OSCOn
	lda	#10
	call	F_Delay7_8125ms
	call	F_InitialTAS5713
	lda	#3
	call	F_Delay7_8125ms
L_PowerOnAmplify_Exit:
	ret
	
;;====================================================================================
;;
;;Module Name:	F_PowerOffAmplify
;;
;;====================================================================================
F_PowerOffAmplify:
	call	F_ShutDownTAS5713
	lda	#05
	call	F_Delay7_8125ms
	clr1	R_TAS5713Reset.B_TAS5713Reset
	lda	#2
	call	F_Delay7_8125ms
	clr1	R_TAS5713Power.B_TAS5713Power
	lda	#10
	call	F_Delay7_8125ms
L_PowerOffAmplify_Exit:
	ret	

;;====================================================================================
;;
;;Module Name:	F_TAS5713OSCOn
;;
;;====================================================================================
F_TAS5713OSCOn:
	call	L_TAS5713OSCOn
	lda	R2
	beq	L_TAS5713OSCOn_Exit

L_TAS5713OSCOn:
	ldm	R2,#0
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
;	call	F_D2AudioStartBit							
;	lda	#098H
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	lda	#01BH
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	lda	#000H
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	call	F_D2AudioStopBit
L_TAS5713OSCOn_Exit:
	ret

;;====================================================================================
;;
;;Module Name:	F_InitialTAS5713
;;
;;Use:					A,Y,X,R0~R3,dpmain,dpmain+1
;;
;;====================================================================================
F_InitialTAS5713:
	call	L_InitialTAS5713
	lda	R2
	bne	L_InitialTAS5713
L_InitialTAS5713_Exit:
	ret	
	
L_InitialTAS5713:
	ldm	R2,#0
																				
	ldx	#0
	ldm dpmain,#<T_InitialTAS5713StartTable   
	ldm dpmain+1,#>T_InitialTAS5713StartTable   
L_InitialTAS5713_Loop:
	call	WDTC
	call	F_D2AudioStartBit
	lda	#098H
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2	
;	lda [dpmain+X] 
	lda	#2  	
	sta	R3
;	inc	dpmain
;	bne	L_InitialTAS5713_Reg
;	inc	(dpmain+1)
L_InitialTAS5713_Reg:
	lda [dpmain+X]
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2	
	inc	dpmain
	bne	L_InitialTAS5713_Skip
	inc	(dpmain+1)				
L_InitialTAS5713_Skip:	
	dec	R3
	bne	L_InitialTAS5713_Reg
	call	F_D2AudioStopBit
	setc
	lda	dpmain
	sbc	#<T_InitialTAS5713EndTable  
	lda	dpmain+1
	sbc	#>T_InitialTAS5713EndTable    
	bcc	L_InitialTAS5713_Loop		
	ret

;;====================================================================================
;;
;;Module Name:	F_ShutDownTAS5713
;;
;;====================================================================================
F_ShutDownTAS5713:
	call	L_ShutDownTAS5713
	lda	R2
	beq	L_ShutDownTAS5713_Exit
	
L_ShutDownTAS5713:
	ldm	R2,#0
	
	call	F_D2AudioStartBit					
	lda	#098H																		
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	lda	#000H												
	call	F_SendD2AudioByte
	call	F_D2AudioACKBit
	or	R2
	sta	R2
	call	F_D2AudioStopBit
	
;	call	F_D2AudioStartBit							
;	lda	#098H
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	lda	#005H
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	lda	#040H
;	call	F_SendD2AudioByte
;	call	F_D2AudioACKBit
;	or	R2
;	sta	R2	
;	call	F_D2AudioStopBit
L_ShutDownTAS5713_Exit:
	ret

;;====================================================================================
;;
;;Module Name: F_D2AudioStartBit
;;
;;Describe:	CK=P0.4
;;		DA=P0.5
;;
;;====================================================================================
F_D2AudioStartBit:
	clr1	R_D2AudioDAO.B_D2AudioDAO
	call	F_DelayD2Audio
	call   F_DelayD2Audio
	clr1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	call   F_DelayD2Audio
L_D2AudioStartBit_Exit:
	ret
	
;;====================================================================================
;;
;;Module Name:	F_D2AudioStopBit
;;
;;Describe:	CK=P0.4
;;		DA=P0.5
;;
;;====================================================================================	
F_D2AudioStopBit:
	clr1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	clr1	R_D2AudioDAO.B_D2AudioDAO
	call   F_DelayD2Audio
	set1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	call   F_DelayD2Audio
	set1	R_D2AudioDAO.B_D2AudioDAO
	call   F_DelayD2Audio
	call   F_DelayD2Audio
L_D2AudioStopBit_Exit:
	ret
	
;;=====================================================================================
;;
;;Module Name:	F_D2AudioACKBit
;;
;;Output:	ACC.0(ACK)
;;
;;Use:		A
;;
;;=====================================================================================	
F_D2AudioACKBit:
	lda	R_D2AudioDAIO
	and	#C_D2AudioDAIOMask
	or	#C_D2AudioDAIOInput
	sta	R_D2AudioDAIO
	call   F_DelayD2Audio
	set1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	call   F_DelayD2Audio
	lda	#0
	bbc	R_D2AudioDAI.B_D2AudioDAI,L_GetD2AudioACKBit
	lda	#1
L_GetD2AudioACKBit:	
	call   F_DelayD2Audio
	call   F_DelayD2Audio
	clr1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	push	A
	lda	R_D2AudioDAIO
	and	#C_D2AudioDAIOMask
	or	#C_D2AudioDAIOOutput
	sta	R_D2AudioDAIO
	call   F_DelayD2Audio
	pop	A
L_D2AudioACKBit_Exit:
	ret
	
;;==============================================================================================
;;
;;Module Name:	F_SendD2AudioByte
;;
;;Input:		A
;;
;;Describe:		CK=P0.4
;;				DA=P0.5
;;
;;Use:			A,R0,R1
;;
;;==============================================================================================	
F_SendD2AudioByte:
	sta	R1
	ldm	R0,#8
L_SendD2AudioByte_Loop:
	asl	R1
	bcs	L_SendD2AudioByte_One
L_SendD2AudioByte_Zero:
	clr1	R_D2AudioDAO.B_D2AudioDAO
	jmp	L_SendD2AudioByte
L_SendD2AudioByte_One:
	set1	R_D2AudioDAO.B_D2AudioDAO
L_SendD2AudioByte:
	call   F_DelayD2Audio
	set1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	clr1	R_D2AudioCK.B_D2AudioCK
	call   F_DelayD2Audio
	dec	R0
	bne	L_SendD2AudioByte_Loop
L_SendD2AudioByte_Exit:
	ret
	
;;=====================================================================================
F_DelayD2Audio:
;	nop
;	nop
;	nop
;	nop		
;	nop
;	nop
L_DelayD2Audio_Exit:
	ret			
;
;
;;
;;	