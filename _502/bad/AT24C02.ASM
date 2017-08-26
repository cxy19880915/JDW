;;===========================================================
;;
;;Module Name:	F_StoreMode
;;
;;Input:				R_ModeTemp
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;===========================================================
F_StoreMode:
#IF EEPROM
	ldx	R_ModeTemp
	ldy	#R_ModeTemp_F
	call	F_WriteDataTo24C02
#ENDIF	
L_StoreMode_Exit:
	ret	
	
;;===========================================================
;;
;;Module Name:	F_StoreFlag
;;
;;Input:				R_Flag
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;===========================================================
F_StoreFlag:
#IF EEPROM
	ldx	R_Flag
	ldy	#R_Flag_F
	call	F_WriteDataTo24C02
#ENDIF	
L_StoreFlag_Exit:
	ret		
	
;;===========================================================
;;
;;Module Name:	F_StoreVolume
;;
;;Input:				R_VolumeTemp
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;===========================================================
F_StoreVolume:
#IF EEPROM
	ldx	R_VolumeTemp
	ldy	#R_VolumeTemp_F
	call	F_WriteDataTo24C02	
#ENDIF	
L_StoreVolume_Exit:
	ret	
	
;;===========================================================
;;
;;Module Name:	F_StoreBass
;;
;;Input:				R_Bass
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;===========================================================
F_StoreBass:
#IF EEPROM
	ldx	R_Bass
	ldy	#R_Bass_F
	call	F_WriteDataTo24C02	
#ENDIF	
L_StoreBass_Exit:
	ret	
		
;;===========================================================
;;
;;Module Name:	F_StoreTreble
;;
;;Input:				R_Treble
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;===========================================================	
F_StoreTreble:
#IF EEPROM	
	ldx	R_Treble
	ldy	#R_Treble_F
	call	F_WriteDataTo24C02	
#ENDIF	
L_StoreTreble_Exit:
	ret	
	
;;========================================================================================================
;;
;;Module Name:	F_Initial24C02
;;
;;Input:				
;;
;;Output:				
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;========================================================================================================
F_Initial24C02:
#IF EEPROM
	ldy	#R_Flag_F
	call	F_ReadDataFrom24C02
	and	#10000000B
	sta	R_Flag
	ldy	#R_ModeTemp_F
	call	F_ReadDataFrom24C02
	sta	R_ModeTemp
	cmp	#C_MinMode
	bcc	L_Initial24C02
	cmp	#(C_MaxMode+1)
	bcs	L_Initial24C02
	ldy	#R_VolumeTemp_F
	call	F_ReadDataFrom24C02
	sta	R_VolumeTemp
	call	F_CheckBCDCode
	bcs	L_Initial24C02
	cmp	#(C_MaxVolume+001H)
	bcs	L_Initial24C02
	ldy	#R_Bass_F
	call	F_ReadDataFrom24C02
	sta	R_Bass
	cmp	#(C_MaxBass+1)	
	bcs	L_Initial24C02
	ldy	#R_Treble_F
	call	F_ReadDataFrom24C02
	sta	R_Treble
	cmp	#(C_MaxTreble+1)	
	bcs	L_Initial24C02
	jmp	L_Initial24C02_Exit
	
L_Initial24C02:
	ldx	#00000000B
	stx	R_Flag
	ldy	#R_Flag_F
	call	F_WriteDataTo24C02
	ldx	#C_InitialMode
	stx	R_ModeTemp
	ldy	#R_ModeTemp_F
	call	F_WriteDataTo24C02
	ldx	#C_InitialVolume
	stx	R_VolumeTemp
	ldy	#R_VolumeTemp_F
	call	F_WriteDataTo24C02
	ldx	#C_InitialBass
	stx	R_Bass
	ldy	#R_Bass_F
	call	F_WriteDataTo24C02
	ldx	#C_InitialTreble
	stx	R_Treble
	ldy	#R_Treble_F
	call	F_WriteDataTo24C02

;;========================================================================================================
#ELSE
	ldm	R_Flag,#00000000B
	ldm	R_ModeTemp,#C_InitialMode
	ldm	R_VolumeTemp,#C_InitialVolume
	ldm	R_Bass,#C_InitialBass
	ldm	R_Treble,#C_InitialTreble
#ENDIF
L_Initial24C02_Exit:
	ret

#IF EEPROM
;;================================================================================================================
;;
;;Module Name:	F_WriteDataTo24C02
;;
;;Input:				X(data),Y(address)
;;
;;Output:				Non
;;
;;Use:					A,R0,R1,R2,X,Y
;;
;;================================================================================================================
F_WriteDataTo24C02:
	call	L_WriteDataTo24C02
	bbc	R2.0,L_WriteDataTo24C02_Exit

L_WriteDataTo24C02:
	ldm	R2,#0
	call	F_EEPROM24C02Start
	lda	#10100000B													;ctrl
	call	F_EEPROM24C02WriteByte
	call	F_EEPROM24C02ACK
	or	R2
	sta	R2
	tya																			;addr
	call	F_EEPROM24C02WriteByte
	call	F_EEPROM24C02ACK
	or	R2
	sta	R2
	txa																			;data
	call	F_EEPROM24C02WriteByte		
	call	F_EEPROM24C02ACK
	or	R2
	sta	R2
	call	F_EEPROM24C02Stop
	lda	#12
	call	F_Delay1ms	
L_WriteDataTo24C02_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_ReadDataFrom24C02
;;
;;Input:				Y(±»¶ÁÈ¡µØÖ·)
;;
;;Output:				A
;;
;;Use:					A,R0,R1,R2,Y
;;
;;================================================================================================================
F_ReadDataFrom24C02:
	call	L_ReadDataFrom24C02
	bbc	R2.0,L_ReadDataFrom24C02_Exit

L_ReadDataFrom24C02:
	ldm	R2,#0
	call	F_EEPROM24C02Start
	lda	#10100000B												;ctrl
	call	F_EEPROM24C02WriteByte
	call	F_EEPROM24C02ACK
	or	R2
	sta	R2
	tya																		;addr
	call	F_EEPROM24C02WriteByte
	call	F_EEPROM24C02ACK
	or	R2
	sta	R2

	clr1	R_24C02SDAO.B_24C02SDAO
	call	F_DelayAT24C02
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	set1	R_24C02SDAO.B_24C02SDAO
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	call	F_EEPROM24C02Start
	lda	#10100001B												;ctrl
	call	F_EEPROM24C02WriteByte
	lda	R_24C02DAI_O
	and	#C_24C02DAIOMask
	or	#C_24C02DAIOInput
	sta	R_24C02DAI_O
	call	F_DelayAT24C02
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	lda	#0
	bbc	R_24C02SDAI.B_24C02SDAI,L_ReadDataFrom24C02_ACK
	lda	#1
L_ReadDataFrom24C02_ACK:	
	call	F_DelayAT24C02
	clr1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	or	R2
	sta	R2

	call	F_EEPROM24C02ReadByte						;data
	push	A
	call	F_NonEEPromACK
	call	F_EEPROM24C02Stop
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	pop	A
L_ReadDataFrom24C02_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_EEPROM24C02Start
;;
;;================================================================================================================
F_EEPROM24C02Start:
	clr1	R_24C02SDAO.B_24C02SDAO
	call	F_DelayAT24C02
	clr1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	call	F_DelayAT24C02
L_EEPROM24C02Start_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_EEPROM24C02Stop
;;
;;================================================================================================================
F_EEPROM24C02Stop:
	clr1	R_24C02SDAO.B_24C02SDAO
	call	F_DelayAT24C02
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	set1	R_24C02SDAO.B_24C02SDAO
	call	F_DelayAT24C02
L_EEPROM24C02Stop_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_EEPROM24C02ACK
;;
;;Input:				Non
;;
;;Output:				A
;;
;;Describe:			EEPROM-->CPU
;;
;;================================================================================================================
F_EEPROM24C02ACK:
	lda	R_24C02DAI_O
	and	#C_24C02DAIOMask
	or	#C_24C02DAIOInput
	sta	R_24C02DAI_O
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	lda	#0
	bbc	R_24C02SDAI.B_24C02SDAI,L_EEPROM24C02ACK
	lda	#1
L_EEPROM24C02ACK:	
	clr1	R_24C02SCL.B_24C02SCL
	push	A
	lda	R_24C02DAI_O
	and	#C_24C02DAIOMask
	or	#C_24C02DAIOOutput
	sta	R_24C02DAI_O
	pop	A
	call	F_DelayAT24C02
L_EEPROM24C02ACK_Exit:
	ret

;;=================================================================================================
;;
;;Module Name:	F_NonEEPromACK
;;
;;=================================================================================================	
F_NonEEPromACK:
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	clr1	R_24C02SCL.B_24C02SCL
	lda	R_24C02DAI_O
	and	#C_24C02DAIOMask
	or	#C_24C02DAIOOutput
	sta	R_24C02DAI_O
	call	F_DelayAT24C02
L_NonEEPromACK_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_EEPROM24C02WriteByte
;;
;;Input:	A
;;
;;Use:		R0,R1
;;
;;================================================================================================================
F_EEPROM24C02WriteByte:
	sta	R1
	ldm	R0,#8
L_EEPROM24C02WriteByte_Loop:
	asl	R1
	bcs	L_EEPROM24C02WriteByte_One
L_EEPROM24C02WriteByte_Zero:
	clr1	R_24C02SDAO.B_24C02SDAO
	jmp	L_EEPROM24C02WriteByte
L_EEPROM24C02WriteByte_One:
	set1	R_24C02SDAO.B_24C02SDAO
L_EEPROM24C02WriteByte:
	call	F_DelayAT24C02
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	clr1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	dec	R0
	bne	L_EEPROM24C02WriteByte_Loop
	call	F_DelayAT24C02
	call	F_DelayAT24C02
L_EEPROM24C02WriteByte_Exit:
	ret

;;================================================================================================================
;;
;;Module Name:	F_EEPROM24C02ReadByte
;;
;;Output:	A
;;
;;Input:	Non
;;
;;Use:		R0,R1
;;
;;================================================================================================================
F_EEPROM24C02ReadByte:
	ldm	R0,#8
L_EEPROM24C02ReadByte_Loop:
	set1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	call	F_DelayAT24C02
	clrc	
	bbc	R_24C02SDAI.B_24C02SDAI,L_EEPROM24C02ReadByte
	setc	
L_EEPROM24C02ReadByte:	
	rol	R1
	clr1	R_24C02SCL.B_24C02SCL
	call	F_DelayAT24C02
	dec	R0
	bne	L_EEPROM24C02ReadByte_Loop
	lda	R1
	call	F_DelayAT24C02
	call	F_DelayAT24C02
L_EEPROM24C02ReadByte_Exit:
	ret

;;==============================================================================================
;;
;;Module Name:	F_DelayAT24C02
;;
;;==============================================================================================	
F_DelayAT24C02:
	nop
	nop
	nop
	nop
	nop
L_DelayAT24C02_Exit:
	ret
#ENDIF	
;
;
;;
;;	