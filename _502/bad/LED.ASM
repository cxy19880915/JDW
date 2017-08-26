;;===============================================================================
;;
;;Module Name:	F_DisplayLed
;;
;;===============================================================================
F_DisplayLed:
	lda	R_MainMode
	bne	L_DisplayLed
	
F_PowerOffLed:
	set1	R_BTLedCtrl.B_BTLedCtrl	
	set1	R_AuxLedCtrl.B_AuxLedCtrl
	set1	R_OpticalLedCtrl.B_OpticalLedCtrl
L_DisplayLed_Exit:
	ret
	
L_DisplayLed:
	lda	R_MainMode
	cmp	#C_BTMode
	beq	L_DisplayBTMode
	cmp	#C_OpticalMode
	beq	L_DisplayOpticalMode
L_DisplayAuxMode:
	bbs	R_Flag.B_RCAMode,L_DisplayRCAMode
	set1	R_BTLedCtrl.B_BTLedCtrl	
	clr1	R_AuxLedCtrl.B_AuxLedCtrl
	set1	R_OpticalLedCtrl.B_OpticalLedCtrl
	ret	
	
L_DisplayRCAMode:
	clr1	R_BTLedCtrl.B_BTLedCtrl	
	set1	R_AuxLedCtrl.B_AuxLedCtrl
	clr1	R_OpticalLedCtrl.B_OpticalLedCtrl
	ret	
	
L_DisplayBTMode:
	clr1	R_BTLedCtrl.B_BTLedCtrl	
	set1	R_AuxLedCtrl.B_AuxLedCtrl
	set1	R_OpticalLedCtrl.B_OpticalLedCtrl
	ret
	
L_DisplayOpticalMode:
	clr1	R_BTLedCtrl.B_BTLedCtrl	
	clr1	R_AuxLedCtrl.B_AuxLedCtrl
	clr1	R_OpticalLedCtrl.B_OpticalLedCtrl
	ret	
	
;;===========================================================================================
;;
;;Module Name:	F_DisplayLcd
;;
;;===========================================================================================	
F_DisplayLcd:

L_DisplayLcd_Exit:
	ret
	
;;==========================================================================
;;
;;Module Name:	F_DisplayBTLed
;;
;;==========================================================================
F_DisplayBTLed:
	inc	R_BTLedTime
	lda	R_BTLedTime
	cmp	#64
	bcc	L_DisplayBTLed
	ldm	R_BTLedTime,#0	
L_DisplayBTLed:
	lda	R_MainMode
	cmp	#C_BTMode
	bne	L_DisplayBTLed_Exit
	lda	R_SetTimeFlag
	cmp	#C_SetVolume
	beq	L_DisplayBTLed_Exit
	cmp	#C_SetTreble
	beq	L_DisplayBTLed_Exit
	cmp	#C_SetBass
	beq	L_DisplayBTLed_Exit
	bbs	R_Flag1.B_MuteFlag,L_DisplayBTLed_Exit
	
	bbs	R_BTSleepDetect.B_BTSleepDetect,L_DisplayBTLed_End
	lda	R_BTLedTime
	cmp	#32
	bcc	L_DisplayBTLed_End
	set1	R_BTLedCtrl.B_BTLedCtrl	
	jmp	L_DisplayBTLed_Exit
L_DisplayBTLed_End:
	clr1	R_BTLedCtrl.B_BTLedCtrl		
L_DisplayBTLed_Exit:
	ret	
;
;
;;
;;