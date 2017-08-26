;;=================================================================================
;;
;;Module Name:	F_PowerOnOptical
;;
;;=================================================================================
F_PowerOnOptical:
;	set1 R_AuxLedCtrl.B_AuxLedCtrl
	bbs	R_StandbyCtrl.B_StandbyCtrl,L_PowerOnMute
;  set1 R_OpticalLedCtrl.B_OpticalLedCtrl
;  set1 R_AuxLedCtrl.B_AuxLedCtrl
;  set1 R_BTLedCtrl.B_BTLedCtrl
	bbc	R_Flag1.B_AudioIn,L_PowerOnOptical_Exit
;	set1 R_OpticalLedCtrl.B_OpticalLedCtrl
	call F_InitialSystem
	jmp	Main_Loop
	
L_PowerOnMute:
	bbc	R_Flag1.B_AudioIn,L_PowerOnSignal
	call F_MuteOffCtrl
	ret
	
L_PowerOnSignal:
	inc	R_OpticalSleepCounterTime
	lda	R_OpticalSleepCounterTime
	cmp	#250
	bcc	L_PowerOnMute
	inc R_OpticalSleepCounter
	lda R_OpticalSleepCounter
	cmp #C_MuteTime
	bcc L_PowerOnMute
	ldm	R_OpticalSleepCounter,#0
	call F_MuteOnCtrl	
	
L_PowerOnOptical_Exit:
	call F_MuteOnCtrl
	ret
	
;;=================================================================================
;;
;;Module Name:	F_PowerOffOptical
;;
;;=================================================================================
F_PowerOffOptical:
L_PowerOffOptical_Exit:
	ret	
;
;
;;
;;