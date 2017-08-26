;;==================================================================================================
;;
;;Module Name:	F_InitialMC81F4416
;;
;;==================================================================================================
F_InitialMC81F4416:
	ldm	OSCSEL,#00000010B										;启动振动	
	
	ldm	WDTR,#11000000B											;watch dog
	ldm	WDTSR,#00000000B
	ldm	CKCTLR,#00011110B
	
	ldm	PORC,#05AH													;disable POR

	ldm	P0,#11100001B		
	ldm	P0CONH,#01001000B
	ldm	P0CONM,#00100100B
	ldm	P0CONL,#00111100B
	ldm	P0PU,#00100001B											;1->Enable Pull Up

	ldm	P1,#00111111B					
	ldm	P1CONH,#11111111B
	ldm	P1CONM,#00111100B
	ldm	P1CONL,#00000000B
	ldm	P1PU,#00000000B											;1->Enable Pull Up							
	
	ldm	P2,#01111111B	
	ldm	P2CONH,#11010101B
	ldm	P2CONL,#01010101B
	ldm	P2PU,#00000000B											;1->Enable Pull Up											

	ldm	P3,#00111110B				
	ldm	P3CONH,#00000010B
	ldm	P3CONL,#10011100B						

	ldm	P4,#11111111B				
	ldm	P4CONH,#10101010B
	ldm	P4CONL,#10101010B		

	ldm	P5,#00001111B		
	ldm	P5CON,#00011010B

	call	!WDTC
	lda	#255																;wait 32.768Hz Stabilization
	call	!F_DelayXms
	call	!WDTC
	lda	#255
	call	!F_DelayXms
	
	ldm	WTSCR,#00101000B										;off
	
	ldm	T1SCR,#00000000B										;off
;	ldm	T1DR,#127	
	
	ldm	T0DR,#08H
	ldm	T1DR,#3DH
	ldm	T0SCR,#10011101B										;2Hz
	
	ldm	T2SCR,#00011110B										;256Hz
	ldm	T2DR,#60
	
	ldm	T3SCR,#00011001B										;8KHz
	ldm	T3DR,#121
	
	ldm	PWMSCR,#11100000B										;PWM3O
	ldm	PWM2DR,#00000000B
	ldm	PWM3DR,#00000000B
	ldm	PWM4DR,#00000000B
;	ldm	T2DR,#240
	ldm	PWMPDR,#00000000B
;	ldm	T2SCR,#00010000B
	
	ldm	BUZR,#00010000B											;disable Buzzer
	ldm	BUPDR,#00000000B
		
	ldm	ADCM,#(00010000B+C_ADC_KeyChannel)			;disable ADC
	
	ldm	SIOCR,#00000000B										;disable SIO
	
	ldm	IICSCR,#00000000B										;disable IIC	
		
	ldm	UCONL,#00001100B										;enable UART
	ldm	BRDAT,#06				
	ldm	UCONH,#01000000B			
	lda	#2
	call	!F_DelayXms		
	ldm	TXSR0,#0FFH
;	set1	TX0IF
	clr1	RX0IF
		
	ldm	IENH,#10001010B																	
	ldm	IENL,#00000000B											
	ldm	IRQH,#00000000B
	ldm	IRQL,#00000000B
	ldm	INTFH,#00000000B
	ldm	INTFL,#00000000B
	
	ldm	EINT0H,#00000000B
	ldm	EINT0L,#00000000B
	ldm	EINT1,#00000000B
	ldm	ERQ0,#00000000B
	ldm	ERQ1,#00000000B
	ldm	EINTFH,#00000000B
	
	call	F_ResetCoder1
	call	F_ResetCoder2
	call	F_ResetCoder3
	call	F_ResetIR
	EI
L_InitialMC81F4416_Exit:
	ret
	
;;==================================================================================================
;;
;;Module Name:	F_InitialSystem
;;
;;==================================================================================================	
F_InitialSystem:
	set1	R_StandbyCtrl.B_StandbyCtrl
	lda	#20
	call	F_Delay7_8125ms
	call	F_Initial24C02
	clr1	R_StandbyCtrl.B_StandbyCtrl
	lda	#20
	call	F_Delay7_8125ms
	ldm	R_HalfSecond,#0

;	jmp	L_PowerOnKey
L_InitialSystem_Exit:
	ret
	
;;===========================================================================
;;
;;Module Name:	F_PowerOnIO
;;
;;===========================================================================	
F_PowerOnIO:
	
L_PowerOnIO_Exit:
	ret
	
;;===========================================================================
;;
;;Module Name:	F_PowerOffIO
;;
;;===========================================================================	
F_PowerOffIO:
	
L_PowerOffIO_Exit:
	ret		
	
;;===================================================================================================	
;;
;;Module Name:	F_DelayXms
;;
;;Input:				A(0:256ms,1~255:1~255ms)
;;
;;Output:				Non
;;
;;Use:					A,R0,R1
;;
;;Describe:			指令计算方式
;;
;;===================================================================================================
F_DelayXms:
	sta	R1
	ldm	R0,#250
L_DelayXms_Loop:
	nop
	nop
	nop
	nop
	dec	R0
	bne	L_DelayXms_Loop
	ldm	R0,#250
	dec	R1
	bne	L_DelayXms_Loop
L_DelayXms_Exit:
	ret
	
;;======================================================================================
;;
;;Module Name:	F_Delay7_8125ms
;;
;;Input:				A(A*7.8125ms)
;;
;;Output:				Non
;;
;;======================================================================================	
F_Delay7_8125ms:
	clr1	R_Flag.B_128Hz
L_Delay7_8125ms_Loop:
	call	WDTC
	bbc	R_Flag.B_128Hz,L_Delay7_8125ms_Loop
	clr1	R_Flag.B_128Hz
	dec	A
	bne	L_Delay7_8125ms_Loop
L_Delay7_8125ms_Exit:
	ret	
	
;;========================================================================
;;
;;Module Name:	F_Delay1ms
;;
;;Input:				A(A*1.0ms)
;;
;;Output:				Non
;;
;;Use:					A
;;
;;Describe:			中断计算方式
;;
;;========================================================================
F_Delay1ms:
	push	X
	ldx	#0
	clr1	R_Flag.B_8192Hz
L_Delay1ms_Loop:
	call	WDTC
	bbc	R_Flag.B_8192Hz,L_Delay1ms_Loop
	clr1	R_Flag.B_8192Hz
	inc	X
	cmpx	#9
	bcc	L_Delay1ms_Loop
	ldx	#0
	dec	A
	bne	L_Delay1ms_Loop
	pop	X
L_Delay1ms_Exit:
	ret	
	
;;===================================================================================================
;;
;;Module Name:	WDTC
;;
;;Use:					Non
;;
;;===================================================================================================	
WDTC:
	ldm	WDTR,#11000000B
WDTC_Exit:
	ret
	
;;===================================================================================================
;;
;;Module Name:	F_GetADCValue
;;
;;Input:				A(ADC Channel Number:bit3~bit0-->ADS3~ADS0)
;;
;;Output:				R1,R0(10bits)
;;
;;===================================================================================================	
F_GetADCValue:
	and	#00001111B
	or	#00010000B
	sta	ADCM
	nop
	nop
	nop
	nop
	or	#10000000B
	sta	ADCM
	ldm	R0,#70
L_GetADCValue_Loop:	
	dec	R0
	bne	L_GetADCValue_Loop
	lda	ADCRL
	xcn
	and	#00001111B
	sta	R0
	lda	ADCRH
	xcn
	sta	R1
	and	#11110000B
	or	R0
	sta	R0
	lda	R1
	and	#00001111B
	sta	R1
	lda	#C_ADC_KeyChannel
	and	#00001111B
	or	#00010000B
	sta	ADCM
L_GetADCValue_Exit:
	ret
	
;;====================================================================================
;;
;;Module Name:	F_BCD_Subc		F_BCD_Sub
;;
;;Input:				R0-A-STATUS.C
;;
;;Output:				A,STATUS.C
;;
;;Use:					A,R0,R1,X
;;
;;====================================================================================
F_BCD_Subc:
	bcs	F_BCD_Sub
	inc	R0
	dec	R0
	bne	L_BCD_Sub_One
	sta	R1
	setc
	lda	#099H
	sbc	R1
	clrc
L_BCD_Subc_Exit:
	ret

L_BCD_Sub_One:
	sta	R1
	setc
	lda	R0
	tax
	sbc	#1
	sta	R0
	txa
	and	#00001111B
	bne	L_BCD_Subc_One
	setc
	lda	R0
	sbc	#6
	sta	R0
L_BCD_Subc_One:
	lda	R1
F_BCD_Sub:
	push	A
;	ld	XL,A
	and	#00001111B
	sta	R1
	setc
	lda	R0
	tax
	sbc	R1
	sta	R0
	txa
	and	#00001111B
	cmp	R1
	bcs	L_BCD_Sub
	setc
	lda	R0
	sbc	#6
	sta	R0
L_BCD_Sub:
	lda	R0
	and	#11110000B
	cmp	#0A0H	
	bcc	L_BCD_Sub_Hi
	setc
	lda	R0
	sbc	#060H
	sta	R0
	pop	A
;	ld	A,XL
	and	#11110000B
	sta	R1
	setc
	lda	R0
	sbc	R1
	clrc
	ret
L_BCD_Sub_Hi:
	pop	A
;	ld	A,XL
	and	#11110000B
	sta	R1
	setc
	lda	R0
	sbc	R1
	bcs	L_BCD_Subc_Exit
	setc
	sbc	#060H
	clrc
	ret	

	
;;======================================================================================
;;
;;Module Name:	F_BCD_Addc	F_BCD_Add
;;
;;Input:				R0+A+STATUS.C
;;
;;Output:				A,STATUS.C
;;
;;Use:					A,R0,X
;;
;;=====================================================================================
F_BCD_Addc:
	bcc	F_BCD_Add
	clrc
	adc	#1
	tax
	and	#00FH
	cmp	#00AH
	bcc	L_Enter_BCD_Add
	clrc
	txa
	adc	#006
	tax
	and	#0F0H
	cmp	#0A0H
	bcc	L_Enter_BCD_Add
	lda	R0
	setc
L_BCD_Addc_Exit:
	ret
	
L_Enter_BCD_Add:	
	txa
F_BCD_Add:
	clrc
	tax
	and	#00FH
	adc	R0
	sta	R0
	push	PSW
	pop	A
	and	#00001000B
	beq	L_BCD_Add
	clrc
	lda	#6
	adc	R0
	sta	R0
L_BCD_Add:
	lda	R0
	and	#00FH
	cmp	#00AH
	bcc	L_BCD_AddL
	clrc
	lda	#6
	adc	R0
	sta	R0
L_BCD_AddL:	
	lda	R0
	and	#0F0H
	cmp	#0A0H
	bcs	L_BCD_Addc
	clrc
	txa
	and	#0F0H
	adc	R0
	sta	R0
	bcc	L_BCD_AddH
	clrc
	lda	#060H
	adc	R0
	setc
	ret
	
L_BCD_AddH:	
	lda	R0
	and	#0F0H
	cmp	#0A0H
	bcc	L_BCD_Addnc
	clrc
	lda	#060H
	adc	R0
	setc
	ret		
	
L_BCD_Addnc:
	lda	R0
	clrc
	ret

L_BCD_Addc:
	txa
	and	#0F0H
	sta	R1
	lda	R0
	and	#00FH
	or	R1
	setc
	ret
	
;;=========================================================================
;;
;;Module Name:	F_ChangeBCDtoHEX
;;
;;Input:				A
;;
;;Output:				A
;;
;;Use:					A,Y,R0
;;
;;=========================================================================
F_ChangeBCDtoHEX:
	sta	R0
	xcn
	and	#00FH
	ldy	#10
	mul	
	tay
	lda	R0
	and	#00FH
	sta	R0
	clrc
	tya
	adc	R0
L_ChangeBCDtoHEX_Exit:
	ret
	
;;========================================================================
;;
;;Module Name:	F_CheckBCDCode
;;
;;Input:				A(不会被改变)
;;
;;Output:				Cy(1:表示非BCD Code,	0:表示是BCD Code)
;;
;;Use:					A
;;
;;========================================================================
F_CheckBCDCode:
	push	A
	and	#00FH
	cmp	#00AH
	bcs	L_CheckBCDCode_Over
	pop	A
	push	A
	and	#0F0H
	cmp	#0A0H
L_CheckBCDCode_Over:
	pop	A
L_CheckBCDCode_Exit:	
	ret
	
;;=====================================================================================
;;
;;Module Name:	F_ChangeHEXtoBCD
;;
;;Input:				A(<=63HEX)
;;
;;Output:				A
;;
;;Use:					R0,Y,A
;;
;;=====================================================================================
F_ChangeHEXtoBCD:
	sta	R0
	xcn
	and	#00001111B
	tay
	lda	!T_GetHEXTable+Y
	push	A
	lda	R0
	and	#00FH
	sta	R0
	cmp	#00AH
	bcc	L_ChangeHexadecimal
	clrc
	lda	R0
	adc	#6
	sta	R0
L_ChangeHexadecimal:	
	clrc
	pop	A
	adc	R0
	sta	R0
	push	psw
	pop	A
	and	#00001000B
	beq	L_ChangeHEXtoBCD
	clrc
	lda	#6
	adc	R0
	sta	R0
L_ChangeHEXtoBCD:	
	lda	R0
	and	#00FH
	cmp	#00AH
	bcc	L_ChangeHEXtoBCD_Exit
	clrc
	lda	#6
	adc	R0
	sta	R0
L_ChangeHEXtoBCD_Exit:
	lda	R0
	ret
	
;;-------------------------------------------------------------------------------------
T_GetHEXTable:
	db	00H
	db	16H	
	db	32H
	db	48H
	db	64H
	db	80H
	db	96H			
	
;
;
;;
;;		