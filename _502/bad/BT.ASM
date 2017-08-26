;;=======================================================================================
;;
;;Module Name:	F_PowerOnBT
;;
;;=======================================================================================
F_PowerOnBT:
	set1	R_BTPowerCtrl.B_BTPowerCtrl
	lda	#15
	call	F_Delay7_8125ms
L_PowerOnBT_Exit:
	ret

;;=======================================================================================
;;
;;Module Name:	F_PowerOffBT
;;
;;=======================================================================================
F_PowerOffBT:
	lda	R_MainMode
	cmp	#C_BTMode
	bne	L_PowerOffBT_Exit
	clr1	R_BTPowerCtrl.B_BTPowerCtrl
	lda	#15
	call	F_Delay7_8125ms
L_PowerOffBT_Exit:
	ret
;
;
;;
;;