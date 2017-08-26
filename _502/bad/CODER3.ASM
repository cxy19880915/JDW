;;====================================================================================
;;
;;Module Name:	F_CoderProcess3		for treble
;;
;;Describe:			B_CoderLFlag3(1:表示IO低，0:表示IO高)
;;							B_CoderRFlag3(1:表示IO低，0:表示IO高)
;;
;;===================================================================================
F_CoderProcess3:
#IF TrebleFunction
	bbs	R_CoderFlag3.B_WaitCoderH3,L_WaitCoderH3
	bbc	R_CoderLPin3.B_CoderLPin3,L_CheckCoderTurn3
	clr1	R_CoderFlag3.B_CoderLFlag3
	bbc	R_CoderRPin3.B_CoderRPin3,L_CoderRFlagHigh3
L_CoderRFlagLow3:
	clr1	R_CoderFlag3.B_CoderRFlag3
	ret
L_CoderRFlagHigh3:
	set1	R_CoderFlag3.B_CoderRFlag3
	ret	
	
L_WaitCoderH3:
	bbc	R_CoderRPin3.B_CoderRPin3,L_WaitCoderH_Exit3
	bbc	R_CoderLPin3.B_CoderLPin3,L_WaitCoderH_Exit3
	jmp	F_ResetCoder3		
L_WaitCoderH_Exit3:
	ret			

L_CheckCoderTurn3:
	bbs	R_CoderFlag3.B_CoderLFlag3,L_CheckCoderTurnRight3
	set1	R_CoderFlag3.B_CoderLFlag3
L_CheckCoderTurnLeft3:
	bbc	R_CoderFlag3.B_CoderRFlag3,L_CoderErrorRPin3
	set1	R_CoderFlag3.B_WaitCoderH3
	ldm	R_CoderTurnL3,#0
	inc	R_CoderTurnR3
	bne	L_CheckCoderTurnLeft_Exit3
	inc	R_CoderTurnR3
L_CheckCoderTurnLeft_Exit3:	
	ret
	
L_CoderErrorRPin3:
	bbs	R_CoderRPin3.B_CoderRPin3,L_CoderErrorRPin_Exit3
	jmp	F_ResetCoder3	
L_CoderErrorRPin_Exit3:
	ret		

L_CheckCoderTurnRight3:	
	bbs	R_CoderRPin3.B_CoderRPin3,L_CoderRFlagLow3
	bbs	R_CoderFlag3.B_CoderRFlag3,L_CoderProcess_Exit3
	set1	R_CoderFlag3.B_CoderRFlag3
	set1	R_CoderFlag3.B_WaitCoderH3
	ldm	R_CoderTurnR3,#0
	inc	R_CoderTurnL3
	bne	L_CoderProcess_Exit3
	inc	R_CoderTurnL3
#ENDIF	
L_CoderProcess_Exit3:
	ret


;;====================================================================================
F_ResetCoder3:
#IF TrebleFunction
	clr1	R_CoderFlag3.B_CoderLFlag3
	bbs	R_CoderLPin3.B_CoderLPin3,L_ResetCoder3
	set1	R_CoderFlag3.B_CoderLFlag3
L_ResetCoder3:
	bbs	R_CoderRPin3.B_CoderRPin3,L_ResetCoder_Over3
	set1	R_CoderFlag3.B_CoderRFlag3
	clr1	R_CoderFlag3.B_WaitCoderH3
	ret
	
L_ResetCoder_Over3:
	clr1	R_CoderFlag3.B_CoderRFlag3
	clr1	R_CoderFlag3.B_WaitCoderH3	
#ENDIF	
L_ResetCoder_Exit3:
	ret
;
;
;;
;;