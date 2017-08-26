;;=================================================================================
;;
;;Module Name:	F_PowerOnOptical
;;
;;=================================================================================
F_PowerOnOptical:
;	set1 R_AuxLedCtrl.B_AuxLedCtrl
	bbs	R_StandbyCtrl.B_StandbyCtrl,L_PowerOnOptical_Exit
;  set1 R_OpticalLedCtrl.B_OpticalLedCtrl
;  set1 R_AuxLedCtrl.B_AuxLedCtrl
;  set1 R_BTLedCtrl.B_BTLedCtrl
	bbc	R_Flag1.B_AudioIn,L_PowerOnOptical_Exit
;	set1 R_OpticalLedCtrl.B_OpticalLedCtrl
	call F_InitialSystem
	jmp	Main_Loop
	
L_PowerOnOptical_Exit:
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