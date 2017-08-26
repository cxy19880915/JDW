;;====================================================================================
;;
;;Module Name:	F_CoderProcess1		for volume
;;
;;Describe:			B_CoderLFlag1(1:表示IO低，0:表示IO高)
;;							B_CoderRFlag1(1:表示IO低，0:表示IO高)
;;
;;===================================================================================
F_CoderProcess1:
	bbs	R_CoderFlag1.B_WaitCoderH1,L_WaitCoderH1
	bbc	R_CoderLPin1.B_CoderLPin1,L_CheckCoderTurn1
	clr1	R_CoderFlag1.B_CoderLFlag1
	bbc	R_CoderRPin1.B_CoderRPin1,L_CoderRFlagHigh1
L_CoderRFlagLow1:
	clr1	R_CoderFlag1.B_CoderRFlag1
	ret
L_CoderRFlagHigh1:
	set1	R_CoderFlag1.B_CoderRFlag1
	ret	
	
L_WaitCoderH1:
	bbc	R_CoderRPin1.B_CoderRPin1,L_WaitCoderH_Exit1
	bbc	R_CoderLPin1.B_CoderLPin1,L_WaitCoderH_Exit1
	jmp	F_ResetCoder1		
L_WaitCoderH_Exit1:
	ret			

L_CheckCoderTurn1:
	bbs	R_CoderFlag1.B_CoderLFlag1,L_CheckCoderTurnRight1
	set1	R_CoderFlag1.B_CoderLFlag1
L_CheckCoderTurnLeft1:
	bbc	R_CoderFlag1.B_CoderRFlag1,L_CoderErrorRPin1
	set1	R_CoderFlag1.B_WaitCoderH1
	ldm	R_CoderTurnL1,#0
	inc	R_CoderTurnR1
	bne	L_CheckCoderTurnLeft_Exit1
	inc	R_CoderTurnR1
L_CheckCoderTurnLeft_Exit1:	
	ret
	
L_CoderErrorRPin1:
	bbs	R_CoderRPin1.B_CoderRPin1,L_CoderErrorRPin_Exit1
	jmp	F_ResetCoder1	
L_CoderErrorRPin_Exit1:
	ret		

L_CheckCoderTurnRight1:	
	bbs	R_CoderRPin1.B_CoderRPin1,L_CoderRFlagLow1
	bbs	R_CoderFlag1.B_CoderRFlag1,L_CoderProcess_Exit1
	set1	R_CoderFlag1.B_CoderRFlag1
	set1	R_CoderFlag1.B_WaitCoderH1
	ldm	R_CoderTurnR1,#0
	inc	R_CoderTurnL1
	bne	L_CoderProcess_Exit1
	inc	R_CoderTurnL1
L_CoderProcess_Exit1:
	ret


;;====================================================================================
F_ResetCoder1:
	clr1	R_CoderFlag1.B_CoderLFlag1
	bbs	R_CoderLPin1.B_CoderLPin1,L_ResetCoder1
	set1	R_CoderFlag1.B_CoderLFlag1
L_ResetCoder1:
	bbs	R_CoderRPin1.B_CoderRPin1,L_ResetCoder_Over1
	set1	R_CoderFlag1.B_CoderRFlag1
	clr1	R_CoderFlag1.B_WaitCoderH1
	ret
	
L_ResetCoder_Over1:
	clr1	R_CoderFlag1.B_CoderRFlag1
	clr1	R_CoderFlag1.B_WaitCoderH1	
L_ResetCoder_Exit1:
	ret
	
;;========================================================================
;;
;;Module Name:	F_ClearCoder
;;
;;========================================================================
F_ClearCoder:
	ldm	R_CoderTurnL,#0
	ldm	R_CoderTurnR,#0
	ldm	R_CoderTurnL1,#0
	ldm	R_CoderTurnR1,#0
	ldm	R_CoderTurnL2,#0
	ldm	R_CoderTurnR2,#0
	ldm	R_CoderTurnL3,#0
	ldm	R_CoderTurnR3,#0
L_ClearCoder_Exit:
	ret
;
;
;;
;;