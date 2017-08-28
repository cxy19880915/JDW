;;=================================================================================
;;
;;Module Name:	F_PowerOnOptical
;;
;;=================================================================================
F_PowerOnOptical:
	bbs	R_StandbyCtrl.B_StandbyCtrl,L_PowerOnMute
	bbc	R_Flag1.B_AudioIn,L_PowerOnOptical_Exit
;	call F_InitialSystem
	jmp	Main_Loop
	
L_PowerOnMute:
	bbc	R_Flag1.B_AudioIn,L_PowerOnSignal
	call F_MuteOffCtrl
	ldm	R_OpticalMuteCounter,#0
	ldm	R_OpticalMuteCounterTime,#0
	ldm	R_OpticalMuteMinute,#0
	ret
	
L_PowerOnSignal:
	inc	R_OpticalMuteCounterTime
	lda	R_OpticalMuteCounterTime
	cmp	#250
	bcc	L_PowerOnMute
	ldm	R_OpticalMuteCounterTime,#0
	inc R_OpticalMuteCounter
	lda R_OpticalMuteCounter
	cmp #250
	bcc	L_PowerOnMute
	ldm	R_OpticalMuteCounter,#0
	inc R_OpticalMuteMinute
	lda R_OpticalMuteMinute
	cmp #C_MuteTime
	bcc L_PowerOnMute
	ldm	R_OpticalMuteMinute,#0
	call F_MuteOnCtrl	
	
L_PowerOnOptical_Exit:
;	call F_MuteOnCtrl
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