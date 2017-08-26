;;====================================================================================
;;
;;Module Name:	F_CoderProcess2		for bass
;;
;;Describe:			B_CoderLFlag2(1:表示IO低，0:表示IO高)
;;							B_CoderRFlag2(1:表示IO低，0:表示IO高)
;;
;;===================================================================================
F_CoderProcess2:
#IF BassFunction
	bbs	R_CoderFlag2.B_WaitCoderH2,L_WaitCoderH2
	bbc	R_CoderLPin2.B_CoderLPin2,L_CheckCoderTurn2
	clr1	R_CoderFlag2.B_CoderLFlag2
	bbc	R_CoderRPin2.B_CoderRPin2,L_CoderRFlagHigh2
L_CoderRFlagLow2:
	clr1	R_CoderFlag2.B_CoderRFlag2
	ret
L_CoderRFlagHigh2:
	set1	R_CoderFlag2.B_CoderRFlag2
	ret	
	
L_WaitCoderH2:
	bbc	R_CoderRPin2.B_CoderRPin2,L_WaitCoderH_Exit2
	bbc	R_CoderLPin2.B_CoderLPin2,L_WaitCoderH_Exit2
	jmp	F_ResetCoder2		
L_WaitCoderH_Exit2:
	ret			

L_CheckCoderTurn2:
	bbs	R_CoderFlag2.B_CoderLFlag2,L_CheckCoderTurnRight2
	set1	R_CoderFlag2.B_CoderLFlag2
L_CheckCoderTurnLeft2:
	bbc	R_CoderFlag2.B_CoderRFlag2,L_CoderErrorRPin2
	set1	R_CoderFlag2.B_WaitCoderH2
	ldm	R_CoderTurnL2,#0
	inc	R_CoderTurnR2
	bne	L_CheckCoderTurnLeft_Exit2
	inc	R_CoderTurnR2
L_CheckCoderTurnLeft_Exit2:	
	ret
	
L_CoderErrorRPin2:
	bbs	R_CoderRPin2.B_CoderRPin2,L_CoderErrorRPin_Exit2
	jmp	F_ResetCoder2	
L_CoderErrorRPin_Exit2:
	ret		

L_CheckCoderTurnRight2:	
	bbs	R_CoderRPin2.B_CoderRPin2,L_CoderRFlagLow2
	bbs	R_CoderFlag2.B_CoderRFlag2,L_CoderProcess_Exit2
	set1	R_CoderFlag2.B_CoderRFlag2
	set1	R_CoderFlag2.B_WaitCoderH2
	ldm	R_CoderTurnR2,#0
	inc	R_CoderTurnL2
	bne	L_CoderProcess_Exit2
	inc	R_CoderTurnL2
#ENDIF	
L_CoderProcess_Exit2:
	ret


;;====================================================================================
F_ResetCoder2:
#IF BassFunction
	clr1	R_CoderFlag2.B_CoderLFlag2
	bbs	R_CoderLPin2.B_CoderLPin2,L_ResetCoder2
	set1	R_CoderFlag2.B_CoderLFlag2
L_ResetCoder2:
	bbs	R_CoderRPin2.B_CoderRPin2,L_ResetCoder_Over2
	set1	R_CoderFlag2.B_CoderRFlag2
	clr1	R_CoderFlag2.B_WaitCoderH2
	ret
	
L_ResetCoder_Over2:
	clr1	R_CoderFlag2.B_CoderRFlag2
	clr1	R_CoderFlag2.B_WaitCoderH2	
#ENDIF	
L_ResetCoder_Exit2:
	ret
;
;
;;
;;